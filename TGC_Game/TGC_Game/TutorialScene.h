#pragma once

#include "SceneBase.h"


// タイトルシーン
class TutorialScene : public SceneBase
{
private:
	class Fade* fade;        // フェード

	// 画像用
	int button_gaid_images; // ボタン説明画像

	// 音源用
	int tutorial_bgm;       // タイトルBGM
	int cursol_push_se;     // カーソル決定SE

private:
	eSceneType next_scene; // 遷移先のシーン
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual eSceneType GetNowSceneType() const override;

};

