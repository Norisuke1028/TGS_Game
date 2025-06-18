#include "EndScene.h"
#include "SceneManager.h"
#include "InputControl.h"
#include "Fade.h"
#include "DxLib.h"

void EndScene::Initialize()
{
	// フェードをインスタンス化
	fade = new Fade();
	// フェードの初期化処理（フェードイン）
	fade->Initialize(true);

	// 画像
	background_image = LoadGraph("Resource/image/end.png");
	cursor_image = LoadGraph("Resource/image/cursor.png");		// カーソル画像
	/*ty_text_image = LoadGraph("Resource/images");*/

	// BGM
	End_bgm = LoadSoundMem("Resource/sounds/BGM/");
	cursol_move_se = LoadSoundMem("Resource/sounds/cursol_move.mp3");  // カーソル移動SE
	PlaySoundMem(End_bgm, DX_PLAYTYPE_BACK);

	// エンド終了保有秒数の初期値
	all_end_time = 0;
}

eSceneType EndScene::Update()
{
	// パッド入力制御のインスタンスを取得
	InputControl* pad_input = InputControl::GetInstance();

	// 十字キー操作(左)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
	{
		menu_cursor--;
		PlaySoundMem(cursol_move_se, DX_PLAYTYPE_BACK);

		if (menu_cursor < 0)
		{
			menu_cursor = 1;
		}
	}
	// 十字キー操作(右)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		menu_cursor++;
		PlaySoundMem(cursol_move_se, DX_PLAYTYPE_BACK);

		if (menu_cursor > 1)
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
			return eSceneType::eRanking;
		case 1:
			return eSceneType::eTitle;
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
		StopSoundMem(End_bgm);
		// フェードアウト
		fade->Initialize(false);

		// カーソル位置に応じてシーン遷移を予約
		if (menu_cursor == 0) {
			next_scene = eSceneType::eRanking;
		}
		else if (menu_cursor == 1) {
			next_scene = eSceneType::eTitle;
		}
	}

	fade->Update();
	return GetNowSceneType();
	// フェード更新
	fade->Update();

	// フェード更新
	fade->Update();

	return GetNowSceneType();
}

void EndScene::Draw() const
{
	// 背景画像
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	// カーソル画像の描画
	DrawRotaGraph(70, 455 + menu_cursor * 80, 0.3, DX_PI / 200.0, cursor_image, TRUE);

	// フェード描画
	fade->Draw();
}

void EndScene::Finalize()
{
	StopSoundMem(End_bgm);

	DeleteGraph(background_image);
	DeleteGraph(cursor_image);

	DeleteSoundMem(cursol_move_se);
}

eSceneType EndScene::GetNowSceneType() const
{
	return eSceneType::eEnd;
}
