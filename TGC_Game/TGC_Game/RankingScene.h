#pragma once
#include "SceneBase.h"
#include "GameDataManager.h"
#include "RankingManager.h"

// ランキング画面クラス
class RankingScene : public SceneBase
{
private:
	class Fade* fade;
	std::vector<ScoreData> scores;  // 読み込んだスコア一覧
	eSceneType ranking_next_scene; // 遷移先のシーン
	bool push_button_flag;
	int a_button_push;
	int ranking_main_bgm;

	std::vector<int> num_image;

	int ranking_text_image;     // 「順位」画像     
	int correct_text_image;     // 「客」画像
	int sales_text_image;       // 「売上」画像

	
	struct RankData {
		int correct;
		int sales;
	};

public:
	RankingScene();
	~RankingScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const;
	virtual void Finalize() override;
	void DrawNumber(int x, int y, int number) const;

public:
	virtual eSceneType GetNowSceneType() const override;

};
