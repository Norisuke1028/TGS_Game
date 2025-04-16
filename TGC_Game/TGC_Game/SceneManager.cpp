#include "SceneManager.h"
#include "ResourceManager.h"
#include "DxLib.h"

#include "TitleScene.h"
#include "InGameScene.h"

#define SCREEN_HEIGHT 480	// 画面の高さ
#define SCREEN_WIDTH 640	// 画面の幅
#define REFRESHRATE 32		// リフレッシュレート

SceneManager::SceneManager() : current_scene(nullptr)
{

}

SceneManager::~SceneManager()
{
	// 解放忘れ防止
	Shutdown();
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneManager::WakeUp()
{
	//// ウィンドウモードで起動する
	ChangeWindowMode(TRUE);


	// ウィンドウサイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, REFRESHRATE);


	// ウィンドウタイトルの設定
	SetWindowText("TGS Game Yagimine");

	// 垂直同期を行わない
	SetWaitVSyncFlag(FALSE);

	// 描画先を表画面に反映する
	SetDrawScreen(DX_SCREEN_BACK);

	// 最初のシーンをタイトル画面にする
	//ChangeScene(eSceneType::title);
	ChangeScene(eSceneType::in_game);

	// 非アクティブ状態でも動作させる
	SetAlwaysRunFlag(TRUE);
}

/// <summary>
///  実行処理
/// </summary>
void SceneManager::Run()
{
	// メインループ
	while (ProcessMessage() != -1)
	{

	}
}

/// <summary>
/// 終了時処理
/// </summary>
void SceneManager::Shutdown()
{
}

/// <summary>
/// 描画処理
/// </summary>
void SceneManager::Graph() const
{
}

/// <summary>
/// シーン切り替え処理
/// </summary>
/// <param name="next_type">次のシーンタイプ</param>
void SceneManager::ChangeScene(eSceneType next_type)
{
}

/// <summary>
/// シーン生成処理
/// </summary>
/// <param name="next_type">次のシーンタイプ</param>
/// <returns>生成したシーン情報のポインタ</returns>
SceneBase* SceneManager::CreateScene(eSceneType next_type)
{
	// シーンタイプによって、生成するシーンを切り替える
	switch (next_type)
	{
	case eSceneType::title:
		return dynamic_cast<SceneBase*>(new TitleScene());
	case eSceneType::in_game:
		return dynamic_cast<SceneBase*>(new InGameScene());
		/*case eSceneType::re_start:;;
			return dynamic_cast<SceneBase*>(new InGameScene());*/
	default:
		return nullptr;
	}
}