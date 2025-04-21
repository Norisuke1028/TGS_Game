#include "EndScene.h"
#include "SceneManager.h"
#include "Fade.h"
#include "DxLib.h"

void EndScene::Initialize()
{
	// フェードをインスタンス化
	fade = new Fade();
	// フェードの初期化処理（フェードイン）
	fade->Initialize(true);

	// 画像
	background_image = LoadGraph("Resource/images/");
	ty_text_image = LoadGraph("Resource/images");

	// BGM
	End_bgm = LoadSoundMem("Resource/sounds/BGM/");
	PlaySoundMem(End_bgm, DX_PLAYTYPE_BACK);

	// エンド終了保有秒数の初期値
	all_end_time = 0;
}

eSceneType EndScene::Update()
{
	// 秒数加算
	all_end_time++;

	// 約5秒で終了
	if (all_end_time == 550.0f)
	{
		exit(0);
	}

	// フェード更新
	fade->Update();

	return GetNowSceneType();
}

void EndScene::Draw() const
{
	// 背景画像
	DrawGraph(0, 0, background_image, FALSE);

	// 「thanks you for playing」描写
	DrawRotaGraph(770, 150, 1.5f, DX_PI / 0.5, ty_text_image, TRUE);

	// エンドテキストの表示（座標: x=50, y=50、色: 白）
	DrawString(50, 50, "エンド画面です", GetColor(255, 255, 255));

	// フェード描画
	fade->Draw();
}

void EndScene::Finalize()
{
	StopSoundMem(End_bgm);
}

eSceneType EndScene::GetNowSceneType() const
{
	return eSceneType::eEnd;
}
