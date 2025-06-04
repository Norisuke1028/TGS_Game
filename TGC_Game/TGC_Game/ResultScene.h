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
	int result_score_history;   // １～３位のタイトル文字

	int cursor_se_move;         // カーソルの移動SE
	int cursor_se_push;         // カーソルの決定SE

	std::vector<int> num_image; // 数字用画像

	int result_bgm;             // リザルトメインbgm


	void DrawNumber(int x, int y, int number) const;        // スコアを画像で描画
	

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

    void SaveScore(int correct, int sales);

public:
	virtual eSceneType GetNowSceneType() const override;
};