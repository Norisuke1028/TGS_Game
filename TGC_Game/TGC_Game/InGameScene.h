#pragma once

#include "SceneBase.h"
//#include "Vector2D.h"
#include <vector>


// インゲームシーン
class InGameScene : public SceneBase
{
private:
	int ingame_cursol;  //具材選択カーソル
	int counter_time;  //時間制限
	int guzai_select[4] = {-1, -1, -1, -1};  //選んだ具材の番号を格納
	int next;  //具材を選ぶと次の選択へ
	int check_count;  //チェックカウント
	int correct;  //正解数
	int sales;  //売上
	int sozai_count;  

private:
	int r_burger[4];  //ハンバーガーをランダムに出力
	int random;
	//const int burger_A[4];  //ハンバーガー1
	//int burger_B[4];

private:
	int guzai_image;  //具材の画像
	int select_image;
	int buns_image;
	int select_guzai_image;
	int select_burger_image[4];

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
};

