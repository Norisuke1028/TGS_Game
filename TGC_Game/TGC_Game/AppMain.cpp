#include"DxLib.h"
#include"SceneManager.h"

//�v���O�����͂�������n�܂�܂�
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCm)
{
	//���[�J���ϐ���`
	SceneManager* scene_manager = nullptr;
	int result = 0;

	try
	{
		//�I�u�W�F�N�g�̐���
		scene_manager = new SceneManager();

		//����������
		scene_manager->WakeUp();

		//�X�V����
		scene_manager->Run();

		//�I������
		scene_manager->Shutdown();
	}
	catch (const char* error_log)
	{
		//�G���[�����o��
		OutputDebugString(error_log);
		//�I����Ԃ��ُ�ɐݒ肷��
		result = -1;
	}

	//�V�[���}�l�[�W���[�𐶐����Ă�����A�폜����
	if (scene_manager != nullptr)
	{
		scene_manager->Shutdown();
		delete scene_manager;
		scene_manager = nullptr;
	}

	//�I����Ԃ�ʒm
	return result;
}