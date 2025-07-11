#pragma once
#include "SceneBase.h"

// エンド画面クラス
class EndScene : public SceneBase
{
private:
	class Fade* fade;        // フェード
	int all_end_time;        // エンド画面終わるまでの時間変数

	int background_image;    // 背景画像用

	int End_bgm;             // エンド用BGM
	
	eSceneType next_scene; // 遷移先のシーン

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

};
