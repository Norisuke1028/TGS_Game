#pragma once
#include "SceneBase.h"
#include "InputControl.h"

// リザルト画面クラス
class ResultScene : public SceneBase
{
private:
	class Fade* fade;           // フェード
	eSceneType result_next_scene;
	int result_cursor;
	Vector2D cursor_pos;		// カーソル座標
	InputControl* pad_input;	// コントローラーの入力インスタンス
	int cursor_image;           // カーソルイメージ
	int result_title_image;     // リザルトタイトル文字
	int result_player_title;    // 自身のスコア上のタイトル文字
	int result_sum_title;       // 自身の合計スコア上のタイトル文字
	int result_score_history;   // １～３位のタイトル文字
	int result_collect_font;    //  接客数画像
	int sb_result_image;  //リザルトのスコアボード画像
	int result_sales_font;      //  売上画像
	int result_button_image;    //シーン遷移画像
	int sum_background;         //  ドラムロールSE
	int result_se;              //リザルトSE(レジ音)

	int result_score_time;      // スコア等秒数

	int result_bronze_font;
	int result_bronze_badge;
	int result_gold_font;
	int result_gold_badge;
	int result_diamond_font;
	int result_diamond_badge;


	int cursor_se_move;         // カーソルの移動SE
	int cursor_se_push;         // カーソルの決定SE
	int result_badge_se;        // バッジ表示時SE

	std::vector<int> num_image; // 数字用画像


	int result_bgm;             // リザルトメインbgm


	void DrawNumber(int x, int y, int number, float scale) const;        // スコアを画像で描画
	void SumDrawNumber(int x, int y, int number, float scale) const;

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

    void SaveScore(int correct, int sales);

public:
	virtual eSceneType GetNowSceneType() const override;
};