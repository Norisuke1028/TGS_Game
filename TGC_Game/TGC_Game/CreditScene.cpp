#include "CreditScene.h"
#include "SceneManager.h"
#include "Fade.h"
#include "DxLib.h"

void CreditScene::Initialize()
{
	// �t�F�[�h���C���X�^���X��
	fade = new Fade();
	// �t�F�[�h�̏����������i�t�F�[�h�C���j
	fade->Initialize(true);

	// �摜
	background_image = LoadGraph("Resource/image/credit.png");

	// �N���W�b�g�I���ۗL�b���̏����l
	all_credit_time = 0;
}

eSceneType CreditScene::Update()
{
	// �b�����Z
	all_credit_time++;

	// ��5�b�ŏI��
	if (all_credit_time == 295.0f)
	{
		exit(0);
	}

	// �t�F�[�h�X�V
	fade->Update();

	return GetNowSceneType();
}


void CreditScene::Draw() const
{
	// �w�i�摜
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	// �t�F�[�h�`��
	fade->Draw();
}

void CreditScene::Finalize()
{
	DeleteGraph(background_image);
}

eSceneType CreditScene::GetNowSceneType() const
{
	return eSceneType::eCredit;
}
