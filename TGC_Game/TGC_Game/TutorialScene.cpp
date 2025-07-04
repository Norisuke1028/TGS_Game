#include "TutorialScene.h"
#include "Fade.h"
#include "InputControl.h"
#include "DxLib.h"

TutorialScene::TutorialScene() : button_gaid_images(NULL),next_scene()
{
}

TutorialScene::~TutorialScene()
{

}

void TutorialScene::Initialize()
{
	// フェードをインスタンス化
	fade = new Fade();
	// フェードの初期化処理（フェードイン）
	fade->Initialize(true);

	next_scene = eSceneType::eTutorial;

	// 画像の読み込み
	background_image = LoadGraph("Resource/image/tutorial2.png");   // 背景画像
	button_gaid_images = LoadGraph("Resource/images/"); // ボタン案内画像
	
	// 音源の読み込み
	tutorial_bgm = LoadGraph("Resource/sounds/SE/");       // チュートリアルBGM
	cursol_push_se = LoadSoundMem("Resource/sounds/SE/ranking/ranking_button_se.mp3");;     // カーソル決定SE
	
}

eSceneType TutorialScene::Update()
{
	// パッド入力制御のインスタンスを取得
	InputControl* pad_input = InputControl::GetInstance();

	// フェードアウト中なら、フェード処理を続ける
	if (next_scene != eSceneType::eTutorial) {
		if (fade->GetEndFlag()) {
			// フェードアウト完了後にシーン遷移
			return next_scene;
		}
		fade->Update();
		// フェードアウト中はチュートリアルシーンを維持
		return eSceneType::eTutorial;
	}

	// コントローラーの A ボタン処理(簡略化)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress) {
		// 押されたときのSE
		PlaySoundMem(cursol_push_se, DX_PLAYTYPE_BACK);
		// BGMを止める
		StopSoundMem(tutorial_bgm);
		// フェード初期化
		fade->Initialize(false);
		// ゲームメインに遷移
		next_scene = eSceneType::eTitle;
	}

	// フェード更新
	fade->Update();

	return GetNowSceneType();

	// 親クラスの更新処理を呼び出す
	return __super::Update();
}

void TutorialScene::Draw() const
{
	// タイトルテキストの表示（座標: x=50, y=50、色: 白）
	//DrawString(50, 50, "チュートリアル画面です", GetColor(255, 255, 255));
	
	// タイトル画像の描画
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	// フェード描画
	fade->Draw();
}

void TutorialScene::Finalize()
{
	// 読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(button_gaid_images);

}

eSceneType TutorialScene::GetNowSceneType() const
{
	return eSceneType::eTutorial;
}