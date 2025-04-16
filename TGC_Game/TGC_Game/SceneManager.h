#pragma once
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void WakeUp();

	/// <summary>
	///  実行処理(更新処理)
	/// </summary>
	void Run();

	/// <summary>
	/// 終了時処理
	/// </summary>
	void Shutdown();   //Finalizeと同じ

};

