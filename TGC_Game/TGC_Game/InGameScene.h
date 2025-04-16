#pragma once

#include "SceneBase.h"


// インゲームシーン
class InGameScene : public SceneBase
{
public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	//virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

};

