#pragma once
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	/// <summary>
	/// ����������
	/// </summary>
	void WakeUp();

	/// <summary>
	///  ���s����(�X�V����)
	/// </summary>
	void Run();

	/// <summary>
	/// �I��������
	/// </summary>
	void Shutdown();   //Finalize�Ɠ���

};

