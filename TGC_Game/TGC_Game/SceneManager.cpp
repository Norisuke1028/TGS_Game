#include "SceneManager.h"
#include "ResourceManager.h"
#include "DxLib.h"

#include "TitleScene.h"
#include "InGameScene.h"

#define SCREEN_HEIGHT 1280	// ��ʂ̍���
#define SCREEN_WIDTH 720	// ��ʂ̕�
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
	while (ProcessMessage() == 0)
	{
		// �V�[���̍X�V
		eSceneType next_scene_type = current_scene->Update();

		// �`�揈��
		Graph();

		// ���݂̃V�[���^�C�v�����̃V�[���^�C�v�ƈ���Ă��邩�H
		if (current_scene->GetNowSceneType() != next_scene_type)
		{
			// �V�[���؂�ւ�����
			ChangeScene(next_scene_type);
		}
		if (current_scene->GetNowSceneType() == eSceneType::in_game)
		{

		}
	}
}

/// <summary>
/// �I��������
/// </summary>
void SceneManager::Shutdown()
{
	// �V�[����񂪐�������Ă���΁A�폜����
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	// Dx���C�u�����̎g�p���I������
	DxLib_End();
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Graph() const
{
	// ��ʂ̏�����
	//ClearDrawScreen();

	// �V�[���̕`�揈��
	current_scene->Draw();

	// ����ʂ̓��e��\��ʂɔ��f����
	ScreenFlip();
}

/// <summary>
/// �V�[���؂�ւ�����
/// </summary>
/// <param name="next_type">���̃V�[���^�C�v</param>
void SceneManager::ChangeScene(eSceneType next_type)
{
	// ���̃V�[���𐶐�����
	SceneBase* next_scene = CreateScene(next_type);

	// �G���[�`�F�b�N
	if (next_scene == nullptr)
	{
		throw ("�V�[���������ł��܂���ł���\n");
	}

	// �V�[����񂪊i�[����Ă�����A�폜����
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	// ���̃V�[���̏�����
	next_scene->Initialize();
	// ���݃V�[���̏㏑��
	current_scene = next_scene;
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