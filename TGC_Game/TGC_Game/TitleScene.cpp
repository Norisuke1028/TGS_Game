#include "TitleScene.h"
#include "DxLib.h"

TitleScene::TitleScene() : background_image(NULL)
{
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	// �摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Title.jpg");

	// �G���[�`�F�b�N
	if (background_image == -1)
	{
		throw ("Resource/images/Title.jpg������܂���\n");
	}
}



//eSceneType TitleScene::Update()
//{
//	// �e�N���X�̍X�V�������Ăяo��
//	return __super::Update();
//}

void TitleScene::Draw() const
{
	// �^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);
}

void TitleScene::Finalize()
{
	// �ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	// ���U���g�f�[�^�̏�������
	FILE* fp = nullptr;
	// �t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���J���܂���\n");
	}

	// �t�@�C���N���[�Y
	fclose(fp);
}

// ���݂̃V�[�������擾
const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}