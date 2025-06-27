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
	background_image = LoadGraph("Resource/image/end2.png");

	// BGM
	End_bgm = LoadSoundMem("Resource/sounds/BGM/");
	PlaySoundMem(End_bgm, DX_PLAYTYPE_BACK);

	////音量設定
	//ChangeVolumeSoundMem(170, cursol_move_se);

	// エンド終了保有秒数の初期値
	all_end_time = 0;

	next_scene = eSceneType::eEnd;
}

eSceneType EndScene::Update()
{
	InputControl* pad_input = InputControl::GetInstance();

// 5秒後に自動遷移を開始
			all_end_time++;

	

	if (fade->GetEndFlag() == true)
	{
		
		if (all_end_time >= 300) {
			fade->Initialize(false);
			next_scene = eSceneType::eCredit;

		}
	}
	else
	{
		// フェード更新
		fade->Update();
	}

// フェードアウト処理
	if (next_scene != eSceneType::eEnd) {
		if (fade->GetEndFlag()) {
			return next_scene;
		}
		
		return eSceneType::eCredit;
	}

	return GetNowSceneType();
}


void EndScene::Draw() const
{
	// 背景画像
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	// フェード描画
	fade->Draw();
}

void EndScene::Finalize()
{
	StopSoundMem(End_bgm);

	DeleteGraph(background_image);
}

eSceneType EndScene::GetNowSceneType() const
{
	return eSceneType::eEnd;
}
