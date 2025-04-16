#pragma once

/// <summary>
/// シーンタイプ
/// </summary>
enum class eSceneType
{
	title,
	in_game,
	re_start,
	result,
	exit,
};


/// <summary>
/// シーン基底クラス
/// </summary>
class SceneBase
{
public:

	SceneBase()
	{

	}

	virtual ~SceneBase()
	{
		// 解放忘れ防止
		Finalize();
	}

public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize()
	{
	}


	///// <summary>
	///// 更新処理
	///// </summary>
	//virtual eSceneType Update()
	//{

	//}

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() const
	{
	}

	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize()
	{

	}

	/// <summary>
	/// 現在のシーンタイプ取得処理
	/// </summary>
	/// <returns>現在のシーンタイプ情報</returns>
	virtual const eSceneType GetNowSceneType() const = 0;
};