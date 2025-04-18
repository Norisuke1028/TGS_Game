#include "ResultScene.h"
#include "DxLib.h"

ResultScene::ResultScene() : background_image(NULL), score(0)
{
}

ResultScene::~ResultScene()
{
}

// ������
void ResultScene::Initialize()
{
	// �摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/title.jpg");

	// �G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/title.jpg������܂���\n");
	}

	// �Q�[�����ʂ̓ǂݍ���
	ReadResultData();

}

//// �X�V����
//eSceneType ResultScene::Update()
//{
//	// A�{�^���Ń����L���O�ɑJ�ڂ���
//	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
//	{
//		return eSceneType::E_RANKING_INPUT;
//	}
//
//	return GetNowScene();
//}

void ResultScene::Draw() const
{

	// �w�i�摜��`��
	DrawGraph(0, 0, background_image, TRUE);

}

// �I��������
void ResultScene::Finalize()
{
	// �ǂݍ��񂾉摜���폜
	DeleteGraph(background_image);
}

//eSceneType ResultScene::GetNowScene() const
//{
//	return eSceneType::E_RESULT;
//}

void ResultScene::ReadResultData()
{
	// �t�@�C���I�[�v��
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���ǂݍ��߂܂���\n");
	}

	// ���ʂ�ǂݍ���
	fscanf_s(fp, "%6d,\n", &score);

	// ���������Ɠ��_���擾
	for (int i = 0; i < 3; i++) {
		fscanf_s(fp, "%6d\n");
	}
	fclose(fp);
}
