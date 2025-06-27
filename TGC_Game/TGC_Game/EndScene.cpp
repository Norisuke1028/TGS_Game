#include "EndScene.h"
#include "SceneManager.h"
#include "InputControl.h"
#include "Fade.h"
#include "DxLib.h"

void EndScene::Initialize()
{
	// �t�F�[�h���C���X�^���X��
	fade = new Fade();
	// �t�F�[�h�̏����������i�t�F�[�h�C���j
	fade->Initialize(true);

	// �摜
	background_image = LoadGraph("Resource/image/end2.png");

	// BGM
	End_bgm = LoadSoundMem("Resource/sounds/BGM/");
	PlaySoundMem(End_bgm, DX_PLAYTYPE_BACK);

	////���ʐݒ�
	//ChangeVolumeSoundMem(170, cursol_move_se);

	// �G���h�I���ۗL�b���̏����l
	all_end_time = 0;

	next_scene = eSceneType::eEnd;
}

eSceneType EndScene::Update()
{
	InputControl* pad_input = InputControl::GetInstance();

// 5�b��Ɏ����J�ڂ��J�n
			all_end_time++;

	

	if (fade->GetEndFlag() == true)
	{
		
		if (all_end_time >= 300) {
			fade->Initialize(false);
			next_scene = eSceneType::eCredit;

		}
	}
	else
	{
		// �t�F�[�h�X�V
		fade->Update();
	}

// �t�F�[�h�A�E�g����
	if (next_scene != eSceneType::eEnd) {
		if (fade->GetEndFlag()) {
			return next_scene;
		}
		
		return eSceneType::eCredit;
	}

	return GetNowSceneType();
}


void EndScene::Draw() const
{
	// �w�i�摜
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	// �t�F�[�h�`��
	fade->Draw();
}

void EndScene::Finalize()
{
	StopSoundMem(End_bgm);

	DeleteGraph(background_image);
}

eSceneType EndScene::GetNowSceneType() const
{
	return eSceneType::eEnd;
}
