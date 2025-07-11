#include "RankingScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "GameDataManager.h"
#include "RankingManager.h"
#include "Fade.h"
#include "DxLib.h"
#include <algorithm>
#include <vector>
#include <fstream>

RankingScene::RankingScene()
	: fade(nullptr)
	, push_button_flag(false)
	, num_image()
	, ranking_next_scene()
{
	
}

RankingScene::~RankingScene()
{

}

void RankingScene::Initialize()
{
	// ボタン押されたときのSE読み込み
	a_button_push = LoadSoundMem("Resource/sounds/SE/ranking/ranking_button_se.mp3");
	// メインbgm
	ranking_main_bgm = LoadSoundMem("Resource/sounds/BGM/ranking/ranking_main_bgm.mp3");
	// リソース管理のインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// 背景画像読み込み
	background_image = LoadGraph("Resource/image/ranking_background.png");

	// 数字画像（0〜9）の読み込み
	num_image = rm->GetImages("Resource/image/number2.png");

	// フェードをインスタンス化
	fade = new Fade();
	// フェードの初期化処理（フェードイン）
	fade->Initialize(true);

	ChangeVolumeSoundMem(255 * 70 / 100, ranking_main_bgm);
	ChangeVolumeSoundMem(178, ranking_main_bgm);
	PlaySoundMem(ranking_main_bgm, DX_PLAYTYPE_BACK);

	scores = std::vector<ScoreData>(RankingManager::GetInstance().ReadScores());

	ranking_next_scene = eSceneType::eRanking;
}

eSceneType RankingScene::Update()
{
	// フェードアウト中なら、フェード処理を続ける
	if (ranking_next_scene != eSceneType::eRanking) {
		if (fade->GetEndFlag()) {
			// フェードアウト完了後にシーン遷移
			return ranking_next_scene;
		}
		fade->Update();
		// フェードアウト中はタイトルシーンを維持
		return eSceneType::eRanking;
	}

	if (fade->GetEndFlag() == true)
	{

		// パッド入力制御のインスタンスを取得
		InputControl* pad_input = InputControl::GetInstance();

		if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
		{
			// フェードアウト処理
			fade->Initialize(false);
			// メインの音を止める
			StopSoundMem(ranking_main_bgm);
			// 押されたときのSE
			PlaySoundMem(a_button_push, DX_PLAYTYPE_BACK);
			// タイトル画面に遷移
			ranking_next_scene = eSceneType::eTitle;
		}
	}
	else
	{
		// フェード更新
		fade->Update();
	}

	return GetNowSceneType();
}

// 描画処理
void RankingScene::Draw() const
{
	// 背景画像の描画
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	int baseY = 160;      // ← Y座標固定
	int rowHeight = 165;  // ← 順位ごとの幅

	for (int i = 0; i < scores.size(); ++i) {
		int y = baseY + i * rowHeight;

		DrawNumber(600, y, scores[i].sum,0.8f);    // 合計スコア
	}

	// フェード描画
	fade->Draw();
}

void RankingScene::Finalize()
{
	
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}

// 指定位置に数値を画像で描画する(数字画像描画用の処理)
void RankingScene::DrawNumber(int x, int y, int number, float scale) const
{
	if (num_image.empty()) return;

	int image_width, image_height;
	GetGraphSize(num_image[0], &image_width, &image_height);

	int digit_width = image_width / 10;
	int digit_height = image_height;

	std::string numStr = std::to_string(number);

	for (size_t i = 0; i < numStr.length(); ++i)
	{
		int digit = numStr[i] - '0';
		int srcX = digit * digit_width;
		int srcY = 0;

		int drawX = x + static_cast<int>(i * digit_width * scale);
		int drawY = y;

		// ここがポイント！
		DrawRectExtendGraph(
			drawX, drawY,
			drawX + static_cast<int>(digit_width * scale),
			drawY + static_cast<int>(digit_height * scale),
			srcX, srcY, digit_width, digit_height,
			num_image[0],
			TRUE
		);
	}
}