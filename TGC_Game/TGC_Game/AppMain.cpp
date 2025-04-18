#include "DxLib.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "SceneManager.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// �E�B���h�E�^�C�g���̐ݒ�
	SetMainWindowText("�€�݂�");

	ChangeWindowMode(TRUE);

	//��ʃT�C�Y�w��
	SetGraphMode(1280, 720, 32);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* manager = nullptr;
	int result = 0;

	try
	{
		// SceneManager�̃I�u�W�F�N�g��
		manager = new SceneManager();

		// SceneManager�̏���������
		manager->Initialize();

		// �p�b�h���͐���̃C���X�^���X���擾
		InputControl* pad_input = InputControl::GetInstance();


		// �}�E�X�J�[�\����\��
		SetMouseDispFlag(FALSE);

		while (ProcessMessage() != -1 && manager->LoopCheck())
		{

			// ���͍X�V����
			pad_input->Update();

			ClearDrawScreen();

			// �V�[���X�V����
			manager->Update();

			// FPS�`��
			//fps.Display_FPS();

			ScreenFlip();

			if (pad_input->GetButtonInputState(XINPUT_BUTTON_BACK) == ePadInputState::eRelease)
			{
				// ESCAPE�L�[��BACK�{�^���ŏI��
				break;
			}
		}
	}
	catch (std::string& error_text)
	{
		OutputDebugString(error_text.c_str());
		result = -1;
	}
	// �p�b�h���͐���̏I������
	InputControl::DeleteInstance();
	// ���\�[�X�Ǘ��̏I������
	ResourceManager::DeleteInstance();

	if (manager != nullptr)
	{
		manager->Finalize();
		// �������̊J��
		delete manager;
	}

	DxLib_End();

	return 0;
}