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

	// ゲームデータ
	int FinalScore;		        // 最終スコア
	int LevelReached;	        // 最終レベル
	int Misinputs;	            // ミス数

	struct HighScoreEntry
	{
		int score;
		int misinputs;
		int level;
	};

	// ハイスコア
	std::vector<HighScoreEntry> HighScores;		// ハイスコアを格納するヴェクター
	const int MaxHighScores = 3;		// ハイスコアを保存する数
	const char* HighScoreFileName = "Resource/ScoreData/Scores.txt";	// ハイスコアデータを保存しているファイルの名前

	void LoadHighScores();			// ハイスコアデータをファイルから取得する
	void SaveHighScores();			// ハイスコアデータをファイルに保存する
	void HandleNewHighScore();		// 今回のスコアが過去のスコアより高いか確認する
	void DisplayCurrentRunScores() const;	// 今回のスコアを描画
	void DisplayHighScores() const;	// ハイスコアを描画する
	void DrawNumber(int x, int y, int number) const;        // スコアを画像で描画

	int offset_plus;


	int HighScore_SE;               // ハイスコアのSE

	// データを並べ替えるセッター
	void DataSortDescending(std::vector<HighScoreEntry>& arr, int n);


	// UIボタンメンバー
	struct Button
	{
		int GraphicHandle;	// ボタンの画像ハンドル
		int x, y;			// ボタンのｘとｙ座標
		int Width, Height;	// ボタンの幅と高さ
		eSceneType TargetScene;	// ボタンが押されて行きたいシーン
	};

	std::vector<Button> buttons;

public:
	// 他のシーンからデータを受け取る（InGameシーンで使う）
	void SetGameData(int score, int level, int misinputs)
	{
		this->FinalScore = score;
		this->LevelReached = level;
		this->Misinputs = misinputs;
	}


public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;
};