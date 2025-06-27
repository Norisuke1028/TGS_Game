#include "CreditScene.h"
#include "SceneManager.h"
#include "Fade.h"
#include "DxLib.h"

void CreditScene::Initialize()
{
	// フェードをインスタンス化
	fade = new Fade();
	// フェードの初期化処理（フェードイン）
	fade->Initialize(true);

	// 画像
	background_image = LoadGraph("Resource/image/credit.png");

	// クレジット終了保有秒数の初期値
	all_credit_time = 0;
}

eSceneType CreditScene::Update()
{
	// 秒数加算
	all_credit_time++;

	// 約5秒で終了
	if (all_credit_time == 295.0f)
	{
		exit(0);
	}

	// フェード更新
	fade->Update();

	return GetNowSceneType();
}


void CreditScene::Draw() const
{
	// 背景画像
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	// フェード描画
	fade->Draw();
}

void CreditScene::Finalize()
{
	DeleteGraph(background_image);
}

eSceneType CreditScene::GetNowSceneType() const
{
	return eSceneType::eCredit;
}
