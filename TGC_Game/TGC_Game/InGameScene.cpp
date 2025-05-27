#include "InGameScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "DxLib.h"

#include <string>
#include <iostream>
#include <thread>

InGameScene::InGameScene() :
	guzai_image(),select_image(),next(),correct(),sales(),check_count(),r_burger(),random()
	,buns_image(),select_burger_image(),burger_model(),sozai_count(),ingame_cursol(),counter_time(),back_image(),g_number_image()
	,delay()
{
	next_scene = eSceneType::eInGame;
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	guzai_image = LoadGraph("Resource/image/guzai.png");  //具材の画像
	select_image = LoadGraph("Resource/image/kettei.png");  //決定ボタンの画像
	buns_image = LoadGraph("Resource/image/buns02.png");  //バンズの画像
	back_image = LoadGraph("Resource/image/background.png");  //背景画像
	LoadDivGraph("Resource/image/guzai04.png", 4, 4, 1, 200, 170, select_burger_image);  //選んだ具材画像
	LoadDivGraph("Resource/image/burger_model.png", 6, 6, 1, 266.6, 140, burger_model);  //お題バーガー画像
	LoadDivGraph("Resource/image/number.png", 10, 5, 2, 132, 330, g_number_image);  //ゲーム内で使用するナンバー画像
	customer.Initialize();  //客クラスの初期化処理
}

eSceneType InGameScene::Update()
{
	//ゲームの進行順序
	switch (gameState)
	{
	//始めに3カウントする
	case GameState::Countdown:
	{
		double elapsed = countDownTimer.GetElapsedSeconds();

		ClearDrawScreen();
		Draw(); // 背景描画など

		//3カウント用
		if (elapsed < 3.0) {
			int count = 3 - static_cast<int>(elapsed);
			DrawRotaGraph(640, 360, 2.0, 0, g_number_image[count-1], true);
			//DrawFormatString(600, 300, 0xFFFFFF, "%d", count);
		}
		else if (elapsed < 3.8) {
			DrawString(600, 300, "スタート！", 0xFFFFFF);
		}
		else {
			timer.Start();  // 本編のタイマー開始
			gameState = GameState::Playing; // 次の状態へ遷移
		}

		ScreenFlip();
		break;
	}
	//ゲームメインスタート
	case GameState::Playing:
	{
		ClearDrawScreen();
		//カーソル操作設定
		CursolControl();

		//描画処理
		Draw();
		//少し遅らせて描画する
		if (next >= 1 && next < 7) {
			//客と吹き出しの描画処理
			customer.Draw();
		}

		select_guzai();

		// 制限時間チェック
		if (timer.IsTimeUp(limit)) {
			gameState = GameState::Result;
		}

		ScreenFlip();
		break;
	}
	//リザルトへ
	case GameState::Result:
	{
		//30秒経つとリザルト画面へ遷移する	
		return eSceneType::eResult;
	}
	}
	return eSceneType::eInGame;
}

//描画処理
void InGameScene::Draw() const
{
	//背景（適当）
	DrawRotaGraph(640, 360, 1.0, 0, back_image, true);

	//Playingになると実行
	if (gameState == GameState::Playing)
	{
		//時間制限
		DrawFormatString(1150, 50, 0x000000, "制限時間　　%d", static_cast<int>(timer.GetElapsedSeconds()));

		//具材選択カーソル描画
		DrawBox(19 + (ingame_cursol * 249.9), 519, 249 + (ingame_cursol * 249.9), 669, 0xffffff, false);
		DrawBox(20 + (ingame_cursol * 250), 520, 250 + (ingame_cursol * 250), 670, 0xffffff, false);
		DrawBox(21 + (ingame_cursol * 250.1), 521, 251 + (ingame_cursol * 250.1), 671, 0xffffff, false);

		//ディレイをかけて表示する
		if (next >= 1 && next < 7) {
			//お題のバーガーの表示
			DrawRotaGraph(870, 100, 3.0, 0, burger_model[random], true);
		}
	}

	//選択した具材(画像表示)
	DrawRotaGraph(200, 275, 1.3, 0, select_burger_image[guzai_select[0]], true);
	DrawRotaGraph(200, 235, 1.3, 0, select_burger_image[guzai_select[1]], true);
	DrawRotaGraph(200, 195, 1.3, 0, select_burger_image[guzai_select[2]], true);
	DrawRotaGraph(200, 155, 1.3, 0, select_burger_image[guzai_select[3]], true);

	//具材選択描画
	DrawBox(110, 150, 290, 180, 0xffffff, false);
	DrawBox(110, 190, 290, 220, 0xffffff, false);
	DrawBox(110, 230, 290, 260, 0xffffff, false);
	DrawBox(110, 270, 290, 300, 0xffffff, false);

	DrawFormatString(1150, 140, 0x000000, "正解数　　%d", correct);  //正解数
	DrawFormatString(1150, 180, 0x000000, "売上　　　%d", sales);  //売り上げ

	DrawRotaGraph(510, 600, 1.0, 0, guzai_image, true);  //具材画像の描画
	DrawRotaGraph(1135, 590, 0.8, 0, select_image, false);  //決定ボタンの描画
	DrawRotaGraph(180, 220, 1.0, 0, buns_image, true);  //バンズの画像の描画

}

void InGameScene::Finalize()
{
	DeleteGraph(background_image);
	DeleteGraph(guzai_image);
	DeleteGraph(select_image);
}

//具材選択処理
int InGameScene::select_guzai()
{
	// パッド入力制御のインスタンスを取得
	InputControl* pad_input = InputControl::GetInstance();
	//具材を4回選ぶ
	switch (next)
	{
		case(0):
				//選んだ具材の初期化処理
				for (int i = 0; i < 4; ++i) {
					guzai_select[i] = -1;
				}

				//ディレイをかける
				if (delay < 150)
				{
					delay++;
				}
				else {
					//少し遅らせて実行する
					delay = 0;
					rand_burger();
					next += 1;
				}
		//具材一枠目
		case(1):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				//決定ボタンを押すとジャッジ処理へ
				if (ingame_cursol == 4)
				{
					next = 5;
				}
				//具材を選択すると1つ目に具材を選択
				else
				{
					guzai_select[0] = ingame_cursol;
					next += 1;
				}
			}
		break;
		//具材二枠目
		case(2):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				//決定ボタンを押すとジャッジ処理へ
				if (ingame_cursol == 4)
				{
					next = 5;
				}
				//具材を選択すると2つ目に具材を選択
				else
				{
					guzai_select[1] = ingame_cursol;
					next += 1;
				}
			}
		break;
		//具材三枠目
		case(3):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				//決定ボタンを押すとジャッジ処理へ
				if (ingame_cursol == 4)
				{
					next = 5;
				}
				//具材を選択すると3つ目に具材を選択
				else
				{
					guzai_select[2] = ingame_cursol;
					next += 1;
				}
			}
		break;
		//具材四枠目
		case(4):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				// 決定ボタンが押されていてカーソルが素材選択位置なら素材を選択
				//4つ目に具材を選択
				if (ingame_cursol < 4)
				{
					guzai_select[3] = ingame_cursol;
				}
				// 決定ボタンが押されていてカーソルが決定位置ならジャッジへ
				else if (ingame_cursol == 4)
				{
					next += 1;
				}
			}
			break;
		case(5):
			//決定ボタンを押すと具材チェック
			check_guzai();

			//お題の素材の数とチェックカウントが同じ(ジャッジ判定に成功)だったら
			if (check_count == sozai_count)
			{
				//ハンバーガーによって売上額を変更する
				sales += 200 + (random * 50);
				//スコアを1加算する
				correct++;

				next += 1;
			}
			//ジャッジ判定に失敗するとリセット
			else {
				check_count = 0;
				next = 0;
			}
		break;
		case(6):
			check_count = 0;
			next += 1;
			break;
		case(7):
			
			next = 0;
		
			break;
	}

	return 0;
}


//指定されるハンバーガーをランダムに出力
int InGameScene::rand_burger()
{
	//ハンバーガーのパターン
	const int p_burger[6][4] = {
		{3,-1,-1,-1},  //パティ、空、空、空
		{3,1,-1,-1},   //パティ、チーズ、空、空
		{3,1,2,-1},    //パティ、チーズ、レタス、空
		{1,0,3,-1},    //チーズ、トマト、パティ、空
		{2,3,0,1},     //レタス、パティ、トマト、チーズ
		{3,0,2,1}      //パティ、トマト、レタス、チーズ
	};
	//ランダムに数字を出力
	random = 0 + rand() % 6;

	sozai_count = 0;
	//出力された数字によってハンバーガーを出力する
	for (int j = 0; j < 4; ++j)
	{
		//お題の素材数をカウントする
		r_burger[j] = p_burger[random][j];
		if (r_burger[j] != -1)
		{
			sozai_count++;
		}
	}

	return 0;
}

//具材チェック処理
int InGameScene::check_guzai()
{
	check_count = 0;

	//お題の素材の数分ジャッジ判定を行う
	for (int i = 0; i < sozai_count; i++)
	{
		//お題通りに選択できればカウントする
		if (guzai_select[i] != -1 && r_burger[i] == guzai_select[i])
		{
			check_count++;
		}
	}

	//空の部分になにか具材が選択されていたら不正解にする
	for (int i = sozai_count; i < 4; i++)
	{
		if (guzai_select[i] != -1) //空確認
		{
			check_count = -1; // 強制不正解
			break;
		}
	}

	return check_count;
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

//カーソル操作設定
void InGameScene::CursolControl()
{
	// パッド入力制御のインスタンスを取得
	InputControl* pad_input = InputControl::GetInstance();

	//十字キーの操作
		//左用
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
	{
		ingame_cursol--;
		if (ingame_cursol < 0)
		{
			ingame_cursol = 4;
		}
	}
	//右用
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		ingame_cursol++;
		if (ingame_cursol > 4)
		{
			ingame_cursol = 0;
		}
	}
}