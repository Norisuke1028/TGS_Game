#pragma once
#include "SceneBase.h"

// Creditクラス
class CreditScene : public SceneBase
{
private:
	class Fade* fade;        // フェード
	int all_credit_time;        // クレジット画面終わるまでの時間変数

	int background_image;    // 背景画像用

	eSceneType next_scene; // 遷移先のシーン

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

};

