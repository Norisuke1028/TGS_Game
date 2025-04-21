#include "TutorialScene.h"
#include "Fade.h"
#include "InputControl.h"
#include "DxLib.h"

TutorialScene::TutorialScene() : button_gaid_images(NULL),next_scene()
{
}

TutorialScene::~TutorialScene()
{

}

void TutorialScene::Initialize()
{
	// �t�F�[�h���C���X�^���X��
	fade = new Fade();
	// �t�F�[�h�̏����������i�t�F�[�h�C���j
	fade->Initialize(true);

	next_scene = eSceneType::eTutorial;

	// �摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/");   // �w�i�摜
	button_gaid_images = LoadGraph("Resource/images/"); // �{�^���ē��摜
	
	// �����̓ǂݍ���
	tutorial_bgm = LoadGraph("Resource/sounds/SE/");       // �`���[�g���A��BGM
	cursol_push_se = LoadGraph("Resource/sounds/SE/");     // �J�[�\������SE
}

eSceneType TutorialScene::Update()
{
	// �p�b�h���͐���̃C���X�^���X���擾
	InputControl* pad_input = InputControl::GetInstance();

	// �t�F�[�h�A�E�g���Ȃ�A�t�F�[�h�����𑱂���
	if (next_scene != eSceneType::eTutorial) {
		if (fade->GetEndFlag()) {
			// �t�F�[�h�A�E�g������ɃV�[���J��
			return next_scene;
		}
		fade->Update();
		// �t�F�[�h�A�E�g���̓`���[�g���A���V�[�����ێ�
		return eSceneType::eTutorial;
	}

	// �R���g���[���[�� A �{�^������(�ȗ���)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress) {
		// ��������SE��点��
		PlaySoundMem(cursol_push_se, DX_PLAYTYPE_BACK);
		// BGM���~�߂�
		StopSoundMem(tutorial_bgm);
		// �t�F�[�h������
		fade->Initialize(false);
		// �Q�[�����C���ɑJ��
		next_scene = eSceneType::eInGame;
	}

	// �t�F�[�h�X�V
	fade->Update();

	return GetNowSceneType();

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update();
}

void TutorialScene::Draw() const
{
	// �^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	// ���j���[�摜�̕`��
	DrawGraph(215, 320, button_gaid_images, FALSE);

	// �^�C�g���e�L�X�g�̕\���i���W: x=50, y=50�A�F: ���j
	DrawString(50, 50, "�`���[�g���A����ʂł�", GetColor(255, 255, 255));

	// �t�F�[�h�`��
	fade->Draw();
}

void TutorialScene::Finalize()
{
	// �ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(button_gaid_images);

}

eSceneType TutorialScene::GetNowSceneType() const
{
	return eSceneType::eTutorial;
}