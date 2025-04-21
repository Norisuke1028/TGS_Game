#include "EndScene.h"
#include "SceneManager.h"
#include "Fade.h"
#include "DxLib.h"

void EndScene::Initialize()
{
	// �t�F�[�h���C���X�^���X��
	fade = new Fade();
	// �t�F�[�h�̏����������i�t�F�[�h�C���j
	fade->Initialize(true);

	// �摜
	background_image = LoadGraph("Resource/images/");
	ty_text_image = LoadGraph("Resource/images");

	// BGM
	End_bgm = LoadSoundMem("Resource/sounds/BGM/");
	PlaySoundMem(End_bgm, DX_PLAYTYPE_BACK);

	// �G���h�I���ۗL�b���̏����l
	all_end_time = 0;
}

eSceneType EndScene::Update()
{
	// �b�����Z
	all_end_time++;

	// ��5�b�ŏI��
	if (all_end_time == 550.0f)
	{
		exit(0);
	}

	// �t�F�[�h�X�V
	fade->Update();

	return GetNowSceneType();
}

void EndScene::Draw() const
{
	// �w�i�摜
	DrawGraph(0, 0, background_image, FALSE);

	// �uthanks you for playing�v�`��
	DrawRotaGraph(770, 150, 1.5f, DX_PI / 0.5, ty_text_image, TRUE);

	// �G���h�e�L�X�g�̕\���i���W: x=50, y=50�A�F: ���j
	DrawString(50, 50, "�G���h��ʂł�", GetColor(255, 255, 255));

	// �t�F�[�h�`��
	fade->Draw();
}

void EndScene::Finalize()
{
	StopSoundMem(End_bgm);
}

eSceneType EndScene::GetNowSceneType() const
{
	return eSceneType::eEnd;
}
