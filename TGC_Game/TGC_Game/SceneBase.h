#pragma once

/// <summary>
/// �V�[���^�C�v
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
/// �V�[�����N���X
/// </summary>
class SceneBase
{
public:

	SceneBase()
	{

	}

	virtual ~SceneBase()
	{
		// ����Y��h�~
		Finalize();
	}

public:
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize()
	{
	}


	///// <summary>
	///// �X�V����
	///// </summary>
	//virtual eSceneType Update()
	//{

	//}

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() const
	{
	}

	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Finalize()
	{

	}

	/// <summary>
	/// ���݂̃V�[���^�C�v�擾����
	/// </summary>
	/// <returns>���݂̃V�[���^�C�v���</returns>
	virtual const eSceneType GetNowSceneType() const = 0;
};