#pragma once

#include "SceneBase.h"


// タイトルシーン
class TitleScene : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	//virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual eSceneType GetNowSceneType() const override;

};

