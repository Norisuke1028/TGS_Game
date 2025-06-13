#pragma once
#include "SceneBase.h"
#include "GameDataManager.h"

// ランキング画面クラス
class RankingScene : public SceneBase
{
private:
	class Fade* fade;
	std::vector<std::pair<int, int>> rankingList; // <correct, sales>
	eSceneType ranking_next_scene; // 遷移先のシーン
	bool push_button_flag;
	int a_button_push;
	int ranking_main_bgm;

	std::vector<int> text_image;
	std::vector<int> num_image;
	std::vector<int> certificate_image;

	int ranking_text_image;     // 「順位」画像     
	int level_text_image;       // 「レベル」画像
	int score_text_image;       // 「スコア」画像
	int miss_text_image;        // 「ミス数」画像

	// ゲームデータ
	int FinalScore;		// 最終スコア
	int LevelReached;	// 最終レベル
	int Misinputs;	    // ミス数

	struct RankData {
		int correct;
		int sales;
	};

	
	void DrawNumber(int x, int y, int number);        // スコアを画像で描画

	

public:
	RankingScene();
	~RankingScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

};
