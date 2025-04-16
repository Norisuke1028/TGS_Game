#include"DxLib.h"
#include"SceneManager.h"

//プログラムはここから始まります
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCm)
{
	//ローカル変数定義
	SceneManager* scene_manager = nullptr;
	int result = 0;

	try
	{
		//オブジェクトの生成
		scene_manager = new SceneManager();

		//初期化処理
		scene_manager->WakeUp();

		//更新処理
		scene_manager->Run();

		//終了処理
		scene_manager->Shutdown();
	}
	catch (const char* error_log)
	{
		//エラー情報を出力
		OutputDebugString(error_log);
		//終了状態を異常に設定する
		result = -1;
	}

	//シーンマネージャーを生成していたら、削除する
	if (scene_manager != nullptr)
	{
		scene_manager->Shutdown();
		delete scene_manager;
		scene_manager = nullptr;
	}

	//終了状態を通知
	return result;
}