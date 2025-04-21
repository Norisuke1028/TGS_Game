#pragma once

#include "SceneBase.h"


// タイトルシーン
class TitleScene : public SceneBase
{
private:
	class Fade* fade;        // フェード

	int menu_image;			// メニュー画像
	int cursor_image;		// カーソル画像
	int menu_cursor;		// メニューカーソル番号
	int title_bgm;          // タイトルBGM
	int cursol_move_se;     // カーソル移動SE
	int cursol_push_se;     // カーソル決定SE

private:
	eSceneType next_scene; // 遷移先のシーン
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual eSceneType GetNowSceneType() const override;

};

