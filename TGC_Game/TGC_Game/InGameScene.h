#pragma once

#include "SceneBase.h"


// インゲームシーン
class InGameScene : public SceneBase
{
private:
	int ingame_cursol;  //具材選択カーソル
	int counter_time;  //時間制限
	int guzai_select[4];

private:
	int guzai_image;  //具材の画像

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
};

