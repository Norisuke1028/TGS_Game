#include "TitleScene.h"
#include "Fade.h"
#include "InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() : menu_image(NULL),cursor_image(NULL), menu_cursor(0),next_scene()
{
}

TitleScene::~TitleScene()
{
	
}

void TitleScene::Initialize()
{
	// �t�F�[�h���C���X�^���X��
	fade = new Fade();
	// �t�F�[�h�̏����������i�t�F�[�h�C���j
	fade->Initialize(true);

	next_scene = eSceneType::eTitle;
	
	// �摜�̓ǂݍ���
	background_image = LoadGraph("Resource/image/title2.png");   // �w�i�摜
	cursor_image = LoadGraph("Resource/image/cursor.png");		// �J�[�\���摜

	// �����̓ǂݍ���
	title_bgm = LoadSoundMem("Resource/sounds/titleBGM.mp3");       // �^�C�g��BGM
	cursol_move_se = LoadSoundMem("Resource/sounds/cursol_move.mp3");  // �J�[�\���ړ�SE
	cursol_push_se = LoadSoundMem("Resource/sounds/SE/");  // �J�[�\������SE
	PlaySoundMem(title_bgm, DX_PLAYTYPE_LOOP); // ���[�v�Đ�����

	//���ʐݒ�
	ChangeVolumeSoundMem(255,title_bgm);
	ChangeVolumeSoundMem(170, cursol_move_se);

	//// �G���[�`�F�b�N
	//if (background_image == -1)
	//{
	//	throw ("Resource/images/Title.jpg������܂���\n");
	//}
}

eSceneType TitleScene::Update()
{
	// �p�b�h���͐���̃C���X�^���X���擾
	InputControl* pad_input = InputControl::GetInstance();

	// �\���L�[����(��)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
	{
		menu_cursor--;
		PlaySoundMem(cursol_move_se, DX_PLAYTYPE_BACK);

		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}
	// �\���L�[����(��)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{
		menu_cursor++;
		PlaySoundMem(cursol_move_se, DX_PLAYTYPE_BACK);

		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	// �J�[�\������
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::eInGame;
		}
	}

	// �t�F�[�h�A�E�g���Ȃ�A�t�F�[�h�����𑱂���
	if (next_scene != eSceneType::eTitle) {
		if (fade->GetEndFlag()) {
			// �t�F�[�h�A�E�g������ɃV�[���J��
			return next_scene;
		}
		fade->Update();
		// �t�F�[�h�A�E�g���̓^�C�g���V�[�����ێ�
		return eSceneType::eTitle;
	}

	// �R���g���[���[�� B �{�^������(�ȗ���)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress) {
		// ��������SE��点��
		PlaySoundMem(cursol_push_se, DX_PLAYTYPE_BACK);
		// BGM���~�߂�
		StopSoundMem(title_bgm);
		// �t�F�[�h�A�E�g
		fade->Initialize(false);

		// �J�[�\���ʒu�ɉ����ăV�[���J�ڂ�\��
		if (menu_cursor == 0) {
			next_scene = eSceneType::eInGame;
		}
		else if (menu_cursor == 1) {
			next_scene = eSceneType::eTutorial;;
		}
		else if (menu_cursor == 2) {
			next_scene = eSceneType::eRanking;
		}
		else if (menu_cursor == 3) {
			next_scene = eSceneType::eEnd;
		}
	}

	fade->Update();
	return GetNowSceneType();
	// �t�F�[�h�X�V
	fade->Update();

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update();
}

void TitleScene::Draw() const
{
	// �^�C�g���摜�̕`��
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	// �J�[�\���摜�̕`��
	DrawRotaGraph(70, 455 + menu_cursor * 80, 0.3, DX_PI / 200.0, cursor_image, TRUE);

	// �t�F�[�h�`��
	fade->Draw();
}

void TitleScene::Finalize()
{
	// �ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);

	DeleteSoundMem(title_bgm);
	DeleteSoundMem(cursol_move_se);
	DeleteSoundMem(cursol_push_se);

	delete fade;
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}