#include "TitleScene.h"
#include "DxLib.h"

TitleScene::TitleScene() : background_image(NULL)
{
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	// 画像の読み込み
	background_image = LoadGraph("Resource/images/Title.jpg");

	// エラーチェック
	if (background_image == -1)
	{
		throw ("Resource/images/Title.jpgがありません\n");
	}
}



//eSceneType TitleScene::Update()
//{
//	// 親クラスの更新処理を呼び出す
//	return __super::Update();
//}

void TitleScene::Draw() const
{
	// タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);
}

void TitleScene::Finalize()
{
	// 読み込んだ画像の削除
	DeleteGraph(background_image);
	// リザルトデータの書き込み
	FILE* fp = nullptr;
	// ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが開けません\n");
	}

	// ファイルクローズ
	fclose(fp);
}

// 現在のシーン情報を取得
const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}