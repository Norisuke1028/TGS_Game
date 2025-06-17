#pragma once

#include "SceneBase.h"
//#include "Vector2D.h"
#include "Customer.h"
#include "Timer.h"
#include <vector>

enum class GameState
{
	Countdown,
	Playing,
	Result
};


// インゲームシーン
class InGameScene : public SceneBase
{
private:
	GameState gameState = GameState::Countdown;  //ゲームステートをカウントダウンに設定
	Timer countDownTimer;  //カウントダウン用タイマー
	Timer gameTimer;  //ゲームメインタイマー
	class Fade* fade;        // フェード

	Customer customer;
	Timer timer;

	int ingame_cursol;  //具材選択カーソル
	int counter_time;  //時間制限
	int select;
	int guzai_select[4] = {0, 0, 0, 0};  //選んだ具材の番号を格納
	int next;  //具材を選ぶと次の選択へ
	int check_count;  //チェックカウント
	int correct_check;
	int correct;  //正解数
	int total_sales;  //合計売上
	int sales; //売上
	int plus;
	int sozai_count;  //お題の素材数
	int delay;  //ディレイ用カウント
	const double limit = 30.0;  //制限時間
	int countdown;  //カウントダウン用
	int GM_timer;  //ゲームメインタイマー
	double elapsed;  //経過した時間

private:
	int r_burger[4];  //ハンバーガーをランダムに出力
	int random;
	//const int burger_A[4];  //ハンバーガー1
	//int burger_B[4];

private:
	int guzai_image;  //具材の画像
	int select_image;  //決定ボタン画像
	int buns_image;  //バンズの画像
	int back_image;  //背景画像
	int select_guzai_image;
	int arrow_image;  //矢印画像
	int select_burger_image[4];  //選んだ具材画像
	int burger_model[6];  //お題バーガー画像
	int gb_number_image[10];  //ゲーム内で使うナンバー画像(黒) gamebrack
	int gr_number_image[10];  //ゲーム内で使うナンバー画像(赤) gamered
	int sb_image;  //スコアボード画像
	int start_image;  //ゲーム開始画像
	int controller_image;  //操作設定画像
	
	int cursol_se;  //カーソル音
	int correct_se;  //正解音
	int incorrect_se;  //不正解音
	int sales_se;  //売上音
	int select_se;  //選択音
	int GM_bgm;  //ゲームメインBGM

private:
	eSceneType next_scene;

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual eSceneType GetNowSceneType() const override;

	//具材選択処理
	int select_guzai();

	//指定されるハンバーガーをランダム出力
	int rand_burger();

	//具材チェック判定処理
	int check_guzai();

	//カーソルの操作設定
	void CursolControl();
};

