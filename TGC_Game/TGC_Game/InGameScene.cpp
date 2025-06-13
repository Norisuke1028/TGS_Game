#include "InGameScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "GameDataManager.h"
#include "Fade.h"
#include "DxLib.h"

#include <string>
#include <iostream>
#include <thread>
#include <fstream>

InGameScene::InGameScene() :
	guzai_image(),select_image(),next(),correct(),total_sales(),check_count(),r_burger(),random(),sb_image(),select()
	,buns_image(),select_burger_image(),burger_model(),sozai_count(),ingame_cursol(),counter_time()
	,back_image(),gb_number_image(),gr_number_image(),start_image(),arrow_image()
	,delay(),countdown(),GM_timer(), elapsed()
{
	next_scene = eSceneType::eInGame;
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	// フェードをインスタンス化
	fade = new Fade();
	// フェードの初期化処理（フェードイン）
	fade->Initialize(true);

	guzai_image = LoadGraph("Resource/image/guzai.png");  //具材の画像
	select_image = LoadGraph("Resource/image/kettei.png");  //決定ボタンの画像
	buns_image = LoadGraph("Resource/image/buns02.png");  //バンズの画像
	arrow_image = LoadGraph("Resource/image/cursor.png");  //矢印画像
	back_image = LoadGraph("Resource/image/main_background3.png");  //背景画像
	sb_image = LoadGraph("Resource/image/denpyo.png");  //スコアボード画像
	start_image = LoadGraph("Resource/image/start.png");  //スタート画像
	controller_image = LoadGraph("Resource/image/controller.png");  //操作設定画像
	plus = LoadGraph("Resource/image/plus.png");
	LoadDivGraph("Resource/image/guzai04.png", 4, 4, 1, 200, 170, select_burger_image);  //選んだ具材画像
	LoadDivGraph("Resource/image/burger_model.png", 6, 6, 1, 266.6, 140, burger_model);  //お題バーガー画像
	LoadDivGraph("Resource/image/number.png", 10, 10, 1, 49, 80, gb_number_image);  //ゲーム内で使用するナンバー画像(黒)
	LoadDivGraph("Resource/image/red_number.png", 10, 10, 1, 50, 80, gr_number_image);  //ゲーム内で使用するナンバー画像(赤)
	cursol_se = LoadSoundMem("Resource/sounds/cursol.mp3");  //カーソル音
	correct_se = LoadSoundMem("Resource/sounds/correct.mp3");  //正解音
	incorrect_se = LoadSoundMem("Resource/sounds/incorrect.mp3");  //不正解音
	sales_se = LoadSoundMem("Resource/sounds/sales.mp3");  //売上音
	GM_bgm = LoadSoundMem("Resource/sounds/MainBGM.mp3");  //ゲームメインBGM
	customer.Initialize();  //客クラスの初期化処理
}

eSceneType InGameScene::Update()
{
	// フェードアウト中なら、フェード処理を続ける
	if (next_scene != eSceneType::eInGame) {
		if (fade->GetEndFlag()) {
			// フェードアウト完了後にシーン遷移
			return next_scene;
		}
		fade->Update();
		// フェードアウト中はゲームメインシーンを維持
		return eSceneType::eInGame;
	}
	fade->Update();

	//ゲームの進行順序
	switch (gameState)
	{
	//始めに3カウントする
	case GameState::Countdown:
	{
		elapsed = countDownTimer.GetElapsedSeconds();

		ClearDrawScreen();
		PlaySoundMem(GM_bgm, DX_PLAYTYPE_LOOP);
		Draw(); // 背景描画など

		//3カウント用
		if (elapsed < 4.0) {
			countdown = 4 - static_cast<int>(elapsed);
		}
		else if (elapsed > 5.1) {
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
		if (next != 0) {
			//カーソル操作設定
			CursolControl();
		}

		//描画処理
		Draw();

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
		GameDataManager::GetInstance().SetCorrect(correct);
		GameDataManager::GetInstance().SetSales(total_sales);
		// フェードアウト
		fade->Initialize(false);

		//30秒経つとリザルト画面へ遷移する	
		return eSceneType::eResult;

	}
	}
	return eSceneType::eInGame;
}

//描画処理
void InGameScene::Draw() const
{
	//背景
	DrawRotaGraph(640, 360, 1.0, 0, back_image, true);
	//背景(選んだ具材)
	DrawBox(70, 5, 295, 280, 0x561B24, true);
	DrawBox(75, 10, 290, 275, 0xffffff, true);

	//操作確認用背景
	DrawRotaGraph(730, 47, 1.0, 0, controller_image, true);

	//Countdownになると実行
	if (gameState == GameState::Countdown)
	{
		//3カウントダウン用
		if (elapsed < 4.0) {
			DrawRotaGraph(640, 340, 2.5, 0, gr_number_image[countdown], true);
		}
		//スタート表示用
		else if (elapsed < 4.8) {
			DrawRotaGraph(640, 340, 1.7, 0, start_image, true);
		}
	}

	//Playingになると実行
	if (gameState == GameState::Playing)
	{
		//制限時間の値を受け取る
		int GM_timer = 30-static_cast<int>(timer.GetElapsedSeconds());

		int t_tens = (GM_timer / 10) % 10;  // 十の位(制限時間)
		int t_ones = GM_timer % 10;        // 一の位(制限時間)

		//時間制限
		DrawCircle(1175, 80, 75, 0x000000, true);
		DrawCircle(1175, 80, 70, 0xffffff, true);
		DrawRotaGraph(1155, 80, 1.0, 0, gb_number_image[t_tens], true);
		DrawRotaGraph(1200, 80, 1.0, 0, gb_number_image[t_ones], true);

		//具材選択カーソル描画
		DrawBox(19 + (ingame_cursol * 249.9), 519, 249 + (ingame_cursol * 249.9), 669, 0xffffff, false);
		DrawBox(20 + (ingame_cursol * 250), 520, 250 + (ingame_cursol * 250), 670, 0xffffff, false);
		DrawBox(21 + (ingame_cursol * 250.1), 521, 251 + (ingame_cursol * 250.1), 671, 0xffffff, false);


		//矢印の描画
		if (next >= 1 && next < 5)DrawRotaGraph(330, 210 - (select * 40), 0.2, 3.142, arrow_image, true);

		//選択した具材(画像表示)
		if (next >= 2 && guzai_select[0] != 4)DrawRotaGraph(180, 200, 1.3, 0, select_burger_image[guzai_select[0]], true);  //四枠目
		if (next >= 3 && guzai_select[1] != 4)DrawRotaGraph(180, 160, 1.3, 0, select_burger_image[guzai_select[1]], true);  //三枠目
		if (next >= 4 && guzai_select[2] != 4)DrawRotaGraph(180, 120, 1.3, 0, select_burger_image[guzai_select[2]], true);  //二枠目
		if (next >= 5 && guzai_select[3] != 4)DrawRotaGraph(180, 80, 1.3, 0, select_burger_image[guzai_select[3]], true);  //一枠目

		DrawRotaGraph(1155, 330, 1.0, 0, sb_image, true);  //スコアボード(伝票)の画像

		int c_tens = (correct / 10) % 10;
		int c_ones = correct % 10;

		if (correct >= 10)DrawRotaGraph(1130, 315, 1.0, 0, gb_number_image[c_tens], true);  //正解数(十の位)
		DrawRotaGraph(1180, 315, 1.0, 0, gb_number_image[c_ones], true);  //正解数(一の位)

		int ts_thousands = (total_sales / 1000) % 10;   // 千の位(合計売上)
		int ts_hundreds = (total_sales / 100) % 10;    // 百の位(合計売上)
		int ts_tens = (total_sales / 10) % 10;     // 十の位(合計売上)
		int ts_ones = total_sales % 10;            // 一の位(合計売上)
		if (total_sales >= 1000)DrawRotaGraph(1095, 430, 1.0, 0, gb_number_image[ts_thousands], true);  // 千の位(合計売上)
		if (total_sales >= 100)DrawRotaGraph(1140, 430, 1.0, 0, gb_number_image[ts_hundreds], true);  // 百の位(合計売上)
		if (total_sales >= 10)DrawRotaGraph(1185, 430, 1.0, 0, gb_number_image[ts_tens], true);  // 十の位(合計売上)
		DrawRotaGraph(1230, 430, 1.0, 0, gb_number_image[ts_ones], true);  // 一の位(合計売上)

		int s_hundreds = (sales / 100) % 10;    // 百の位(売上)
		int s_tens = (sales / 10) % 10;     // 十の位(売上)
		int s_ones = sales % 10;            // 一の位(売上)
		if (next == 0 && sales >= 100 && correct_check == 1) {
			DrawRotaGraph(1150, 377, 0.4, 0, plus, true);  //プラス記号
			DrawRotaGraph(1180, 380, 0.5, 0, gr_number_image[s_hundreds], true);  // 百の位(売上)
			DrawRotaGraph(1205, 380, 0.5, 0, gr_number_image[s_tens], true);  // 十の位(売上)
			DrawRotaGraph(1230, 380, 0.5, 0, gr_number_image[s_ones], true);  // 一の位(売上)
		}

		//ディレイをかけて表示する
		if (next >= 1 && next < 7) {
			//客と吹き出しの描画処理
			customer.Draw();
			//お題のバーガーの表示
			DrawRotaGraph(790, 150, 3.0, 0, burger_model[random], true);
		}
	}

	//具材選択描画
	DrawBox(90, 100, 270, 80, 0x000000, false);
	DrawBox(90, 140, 270, 120, 0x000000, false);
	DrawBox(90, 180, 270, 160, 0x000000, false);
	DrawBox(90, 220, 270, 200, 0x000000, false);

	DrawRotaGraph(510, 600, 1.0, 0, guzai_image, true);  //具材画像の描画
	DrawBox(1035, 535, 1235, 645, 0x000000, true);  //決定ボタン外枠
	DrawRotaGraph(1135, 590, 0.8, 0, select_image, false);  //決定ボタンの描画
	DrawRotaGraph(160, 145, 1.0, 0, buns_image, true);  //バンズの画像の描画

	// フェード描画
	fade->Draw();

}

void InGameScene::Finalize()
{
	DeleteGraph(background_image);
	DeleteGraph(guzai_image);
	DeleteGraph(select_image);
	delete fade;
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
				for (select = 0; select < 4; ++select) {
					guzai_select[select] = 4;
				}
				ingame_cursol = 0;

				//ディレイをかける
				if (delay < 50)
				{
					delay++;
				}
				else {
					//少し遅らせて実行する
					delay = 0;
					rand_burger();
					customer.RandomCustomer();
					select = 0;
					correct_check = 0;
					next += 1;
				}
		//具材一枠目
		case(1):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				//具材を選択すると1つ目に具材を選択
				guzai_select[select] = ingame_cursol;
				select += 1;
				next += 1;
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
					guzai_select[select] = ingame_cursol;
					select += 1;
					next += 1;
				}
			}
			//Aボタンを押すと具材をまた選べるようになる(一枠目)
			else if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress) {
				if (select > 0) {
					select -= 1;
					guzai_select[select] = -1;
					next -= 1;
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
					guzai_select[select] = ingame_cursol;
					select += 1;
					next += 1;
				}
			}
			//Aボタンを押すと具材をまた選べるようになる(二枠目)
			else if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress) {
				select -= 1;
				guzai_select[select] = -1;
				next -= 1;
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
					guzai_select[select] = ingame_cursol;
					select += 1;
					next += 1;
				}
				// 決定ボタンが押されていてカーソルが決定位置ならジャッジへ
				else if (ingame_cursol == 4)
				{
					next += 1;
				}
			}
			//Aボタンを押すと具材をまた選べるようになる(三枠目)
			else if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress) {
				select -= 1;
				guzai_select[select] = -1;
				next -= 1;
			}
			break;
		case(5):
			//Aボタンを押すと具材をまた選べるようになる(四枠目)
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress) {
				select -= 1;
				guzai_select[select] = -1;
				next -= 1;
			}
			//決定ボタンを選んでる時にBボタンを押すとジャッジへ
			else if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress && ingame_cursol == 4 || select < 4) {

				//決定ボタンを押すと具材チェック
				check_guzai();

				//お題の素材の数とチェックカウントが同じ(ジャッジ判定に成功)だったら
				if (check_count == sozai_count)
				{
					//ハンバーガーによって売上額を変更する
					sales = 200 + (random * 50);
					//売上額の合計
					total_sales += sales;
					correct_check = 1;
					//スコアを1加算する
					correct++;
					PlaySoundMem(correct_se, DX_PLAYTYPE_BACK);

					next += 1;
				}
				//ジャッジ判定に失敗するとリセット
				else {
					PlaySoundMem(incorrect_se, DX_PLAYTYPE_BACK);
					check_count = 0;
					next = 0;
				}
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
		{3,4,4,4},  //パティ、空、空、空
		{3,1,4,4},   //パティ、チーズ、空、空
		{3,1,2,4},    //パティ、チーズ、レタス、空
		{1,0,3,4},    //チーズ、トマト、パティ、空
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
		PlaySoundMem(cursol_se, DX_PLAYTYPE_BACK);

		//具材が一つも選ばれていないときは決定ボタンを押せないようにする
		if (ingame_cursol < 0)
		{
			if (next > 1) {
				ingame_cursol = 4;
			}
			else {
				ingame_cursol = 3;
			}
		}
	}
	//右用
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		ingame_cursol++;
		PlaySoundMem(cursol_se, DX_PLAYTYPE_BACK);

		//具材が一つも選ばれていないときは決定ボタンを押せないようにする
		if (next > 1) {
			if (ingame_cursol > 4)
			{
				ingame_cursol = 0;
			}
		}
		else {
			if (ingame_cursol > 3)
			{
				ingame_cursol = 0;
			}
		}
	}
}

