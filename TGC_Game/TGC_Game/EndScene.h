#pragma once
#include "SceneBase.h"

// エンド画面クラス
class EndScene : public SceneBase
{
private:
	class Fade* fade;        // フェード
	int all_end_time;        // エンド画面終わるまでの時間変数

	int background_image;    // 背景画像用
	int cursor_image;		// カーソル画像
	int menu_cursor;		// メニューカーソル番号
	int ty_text_image;       // 「thanks you for playing」他(使用サイト)テキスト画像用


	int cursol_push_se;     // カーソル決定SE
	int End_bgm;             // エンド用BGM
	int cursol_move_se;     // カーソル移動SE

	eSceneType next_scene; // 遷移先のシーン

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

};
