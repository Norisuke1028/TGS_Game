#include "SceneManager.h"
#include "ResourceManager.h"
#include "DxLib.h"

#include "TitleScene.h"
#include "InGameScene.h"

#define SCREEN_HEIGHT 480	// ��ʂ̍���
#define SCREEN_WIDTH 640	// ��ʂ̕�
#define REFRESHRATE 32		// ���t���b�V�����[�g

SceneManager::SceneManager() : current_scene(nullptr)
{

}

SceneManager::~SceneManager()
{
	// ����Y��h�~
	Shutdown();
}

/// <summary>
/// ����������
/// </summary>
void SceneManager::WakeUp()
{
	//// �E�B���h�E���[�h�ŋN������
	ChangeWindowMode(TRUE);


	// �E�B���h�E�T�C�Y�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, REFRESHRATE);


	// �E�B���h�E�^�C�g���̐ݒ�
	SetWindowText("TGS Game Yagimine");

	// �����������s��Ȃ�
	SetWaitVSyncFlag(FALSE);

	// �`����\��ʂɔ��f����
	SetDrawScreen(DX_SCREEN_BACK);

	// �ŏ��̃V�[�����^�C�g����ʂɂ���
	//ChangeScene(eSceneType::title);
	ChangeScene(eSceneType::in_game);

	// ��A�N�e�B�u��Ԃł����삳����
	SetAlwaysRunFlag(TRUE);
}

/// <summary>
///  ���s����
/// </summary>
void SceneManager::Run()
{
	// ���C�����[�v
	while (ProcessMessage() != -1)
	{

	}
}

/// <summary>
/// �I��������
/// </summary>
void SceneManager::Shutdown()
{
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Graph() const
{
}

/// <summary>
/// �V�[���؂�ւ�����
/// </summary>
/// <param name="next_type">���̃V�[���^�C�v</param>
void SceneManager::ChangeScene(eSceneType next_type)
{
}

/// <summary>
/// �V�[����������
/// </summary>
/// <param name="next_type">���̃V�[���^�C�v</param>
/// <returns>���������V�[�����̃|�C���^</returns>
SceneBase* SceneManager::CreateScene(eSceneType next_type)
{
	// �V�[���^�C�v�ɂ���āA��������V�[����؂�ւ���
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