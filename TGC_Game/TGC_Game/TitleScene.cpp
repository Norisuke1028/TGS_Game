#include "TitleScene.h"
#include "InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() : menu_image(NULL),
cursor_image(NULL), menu_cursor(0)
{
}

TitleScene::~TitleScene()
{
	
}

void TitleScene::Initialize()
{
	menu_image = LoadGraph("Resource/images/");
	cursor_image = LoadGraph("Resource/images/");
	
	//// 画像の読み込み
	//background_image = LoadGraph("Resource/images/Title.jpg");

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

	// カーソル下移動
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{
		menu_cursor++;
		// 一番下に到達したら、一番上にする
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	// カーソル上移動
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
	{
		menu_cursor--;
		// 一番上に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}



	// カーソル決定
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::eInGame;
		case 1:
			return eSceneType::eRanking;
	/*	case 2:
			return eSceneType::help;*/
		default:
			return eSceneType::eEnd;
		}
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update();
}

void TitleScene::Draw() const
{
	// タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	// メニュー画像の描画
	DrawGraph(215, 320, menu_image, FALSE);

	// カーソル画像の描画
	DrawRotaGraph(185, 340 + menu_cursor * 32, 1.6, DX_PI / 200.0, cursor_image, TRUE);

	// タイトルテキストの表示（座標: x=50, y=50、色: 白）
	DrawString(50, 50, "タイトル画面です", GetColor(255, 255, 255));
}

void TitleScene::Finalize()
{
	// 読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);

}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}