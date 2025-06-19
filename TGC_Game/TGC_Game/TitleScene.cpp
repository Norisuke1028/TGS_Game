#include "TitleScene.h"
#include "Fade.h"
#include "InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() : menu_image(NULL),cursor_image(NULL), menu_cursor(0),next_scene()
{
}

TitleScene::~TitleScene()
{
	
}

void TitleScene::Initialize()
{
	// フェードをインスタンス化
	fade = new Fade();
	// フェードの初期化処理（フェードイン）
	fade->Initialize(true);

	next_scene = eSceneType::eTitle;
	
	// 画像の読み込み
	background_image = LoadGraph("Resource/image/title2.png");   // 背景画像
	cursor_image = LoadGraph("Resource/image/cursor.png");		// カーソル画像

	// 音源の読み込み
	title_bgm = LoadSoundMem("Resource/sounds/titleBGM.mp3");       // タイトルBGM
	cursol_move_se = LoadSoundMem("Resource/sounds/cursol_move.mp3");  // カーソル移動SE
	cursol_push_se = LoadSoundMem("Resource/sounds/SE/");  // カーソル決定SE
	PlaySoundMem(title_bgm, DX_PLAYTYPE_LOOP); // ループ再生する

	//音量設定
	ChangeVolumeSoundMem(255,title_bgm);
	ChangeVolumeSoundMem(170, cursol_move_se);

	//// エラーチェック
	//if (background_image == -1)
	//{
	//	throw ("Resource/images/Title.jpgがありません\n");
	//}
}

eSceneType TitleScene::Update()
{
	// パッド入力制御のインスタンスを取得
	InputControl* pad_input = InputControl::GetInstance();

	// 十字キー操作(上)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
	{
		menu_cursor--;
		PlaySoundMem(cursol_move_se, DX_PLAYTYPE_BACK);

		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}
	// 十字キー操作(下)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{
		menu_cursor++;
		PlaySoundMem(cursol_move_se, DX_PLAYTYPE_BACK);

		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	// カーソル決定
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::eInGame;
		}
	}

	// フェードアウト中なら、フェード処理を続ける
	if (next_scene != eSceneType::eTitle) {
		if (fade->GetEndFlag()) {
			// フェードアウト完了後にシーン遷移
			return next_scene;
		}
		fade->Update();
		// フェードアウト中はタイトルシーンを維持
		return eSceneType::eTitle;
	}

	// コントローラーの B ボタン処理(簡略化)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress) {
		// 押したらSEを鳴らせる
		PlaySoundMem(cursol_push_se, DX_PLAYTYPE_BACK);
		// BGMを止める
		StopSoundMem(title_bgm);
		// フェードアウト
		fade->Initialize(false);

		// カーソル位置に応じてシーン遷移を予約
		if (menu_cursor == 0) {
			next_scene = eSceneType::eInGame;
		}
		else if (menu_cursor == 1) {
			next_scene = eSceneType::eTutorial;;
		}
		else if (menu_cursor == 2) {
			next_scene = eSceneType::eRanking;
		}
		else if (menu_cursor == 3) {
			next_scene = eSceneType::eEnd;
		}
	}

	fade->Update();
	return GetNowSceneType();
	// フェード更新
	fade->Update();

	// 親クラスの更新処理を呼び出す
	return __super::Update();
}

void TitleScene::Draw() const
{
	// タイトル画像の描画
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	// カーソル画像の描画
	DrawRotaGraph(70, 455 + menu_cursor * 80, 0.3, DX_PI / 200.0, cursor_image, TRUE);

	// フェード描画
	fade->Draw();
}

void TitleScene::Finalize()
{
	// 読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);

	DeleteSoundMem(title_bgm);
	DeleteSoundMem(cursol_move_se);
	DeleteSoundMem(cursol_push_se);

	delete fade;
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}