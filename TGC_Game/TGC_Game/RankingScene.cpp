#include "RankingScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "GameDataManager.h"
#include "ResourceManager.h"
#include "Fade.h"
#include "DxLib.h"
#include <algorithm>
#include <vector>
#include <fstream>




RankingScene::RankingScene()
	: fade(nullptr)
	, push_button_flag(false)
	, text_image()
	, num_image()
	, certificate_image()
	, ranking_next_scene()
{

}

RankingScene::~RankingScene()
{

}

void RankingScene::Initialize()
{
	/*/ ボタン押されたときのSE読み込み
	a_button_push = LoadSoundMem("Resource/sounds/SE/");
	// メインbgm
	ranking_main_bgm = LoadSoundMem("Resource/sounds/BGM/");*/
	// リソース管理のインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// 背景画像読み込み
	background_image = LoadGraph("Resource/image/ranking_background.png");

	/*/ テキスト画像の読み込み
	text_image = rm->GetImages("Resource/images/");
	tmp = rm->GetImages("Resource/images/");
	text_image.push_back(tmp[0]);

	certificate_image = rm->GetImages("Resource/images/");*/

	// 数字画像（0?9）の読み込み
	num_image = rm->GetImages("Resource/image/number.png");

	/*/ 順位画像の読み込み
	ranking_text_image = LoadGraph("Resource/images/");
	// レベル数画像の読み込み
	level_text_image = LoadGraph("Resource/images/");
	// スコア画像の読み込み
	score_text_image = LoadGraph("Resource/images/");
	// ミス数画像の読み込み
	miss_text_image = LoadGraph("Resource/images/");*/

	// フェードをインスタンス化
	fade = new Fade();
	// フェードの初期化処理（フェードイン）
	fade->Initialize(true);

	ChangeVolumeSoundMem(255 * 70 / 100, ranking_main_bgm);
	PlaySoundMem(ranking_main_bgm, DX_PLAYTYPE_BACK);

	// ↓ ランキングデータを読み込む
	LoadRankingData();

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

void RankingScene::Draw() 
{
	// ランキングテキストの表示（座標: x=50, y=50、色: 白）
	DrawString(50, 50, "ランキング画面です", GetColor(255, 255, 255));
	DrawString(10, 26, "A : Title", GetColor(255, 255, 255));
	
	// 背景画像の描画
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	/*
	DrawRotaGraphF(640.0f, 390.0f, 1.0, 0.0, certificate_image[0], TRUE);

	// "ランキング"テキスト描画
	DrawRotaGraphF(640.0f, 70.0f, 1.0, 0.0, text_image[0], TRUE);
	// ボタン案内表示
	DrawRotaGraphF(1150.0f, 680.0f, 1.0, 0.0, text_image[1], TRUE);

	// ランキング
	DrawRotaGraph(280, 240, 0.7f, DX_PI / 0.5, ranking_text_image, TRUE);

	// レベル数
	DrawRotaGraph(400, 240, 0.7f, DX_PI / 0.5, level_text_image, TRUE);

	// スコア
	DrawRotaGraph(620, 240, 0.7f, DX_PI / 0.5, score_text_image, TRUE);

	// ミス数
	DrawRotaGraph(950, 240, 0.7f, DX_PI / 0.5, miss_text_image, TRUE);*/

	/*/ ランキング描画
	DrawRankingData();*/

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

// ランキングデータ読み込み & ソート（売上→接客数の順で降順）
void RankingScene::LoadRankingData()
{
	std::ifstream file("Resource/ScoreData/ranking.txt");
	rankList.clear();

	if (file.is_open()) {
		int correct, sales;
		while (file >> correct >> sales) {
			rankList.push_back({ correct, sales });
		}
		file.close();
	}

	// 売上（sales）→ 接客数（correct）の順に降順ソート
	std::sort(rankList.begin(), rankList.end(), [](const RankData& a, const RankData& b) {
		if (a.sales != b.sales) return a.sales > b.sales;
		return a.correct > b.correct;
		});
}

void RankingScene::DrawRankingData()
{
	if (rankList.empty()) return;

	int y = 100;

	// 最大3位まで描画
	int drawCount = static_cast<int>(rankList.size());
	if (drawCount > 3) drawCount = 3;

	for (int i = 0; i < drawCount; ++i)
	{
		// ランク位置（例: 1位）
		DrawFormatString(50, y + 20, GetColor(255, 255, 255), "%d位:", i + 1);

		// 接客数（テキスト + 画像数字）
		DrawString(150, y, "接客数:", GetColor(255, 255, 255));
		DrawNumber(250, y, rankList[i].correct);

		// 売上（テキスト + 画像数字）
		DrawString(400, y, "売上:", GetColor(255, 255, 255));
		DrawNumber(470, y, rankList[i].sales);

		y += 70; // 次の行へ
	}
}




// 指定位置に数値を画像で描画する
void RankingScene::DrawNumber(int x, int y, int number) 
{
	if (num_image.empty()) return;  // 画像が未ロードなら描画しない

	int image_width, image_height;
	GetGraphSize(num_image[0], &image_width, &image_height);  // 画像のサイズ取得

	int digit_width = image_width / 10;  // 各数字の幅（10桁に分割）
	int digit_height = image_height;  // 画像の高さ

	std::string numStr = std::to_string(number); // 数字を文字列に変換

	for (size_t i = 0; i < numStr.length(); ++i)
	{
		int digit = numStr[i] - '0';  // 文字から数値へ変換
		int srcX = digit * digit_width;  // 画像内のX座標
		int srcY = 0;  // Y座標（1行の画像なら0）

		// 画像の一部を切り取って描画
		DrawRectGraph(x + i * digit_width, y, srcX, srcY, digit_width, digit_height, num_image[0], TRUE, FALSE);
	}
}