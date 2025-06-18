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
	background_image = LoadGraph("Resource/image/end.png");
	cursor_image = LoadGraph("Resource/image/cursor.png");		// �J�[�\���摜
	/*ty_text_image = LoadGraph("Resource/images");*/

	// BGM
	End_bgm = LoadSoundMem("Resource/sounds/BGM/");
	cursol_move_se = LoadSoundMem("Resource/sounds/cursol_move.mp3");  // �J�[�\���ړ�SE
	PlaySoundMem(End_bgm, DX_PLAYTYPE_BACK);

	// �G���h�I���ۗL�b���̏����l
	all_end_time = 0;
}

eSceneType EndScene::Update()
{
	// �p�b�h���͐���̃C���X�^���X���擾
	InputControl* pad_input = InputControl::GetInstance();

	// �\���L�[����(��)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
	{
		menu_cursor--;
		PlaySoundMem(cursol_move_se, DX_PLAYTYPE_BACK);

		if (menu_cursor < 0)
		{
			menu_cursor = 1;
		}
	}
	// �\���L�[����(�E)
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		menu_cursor++;
		PlaySoundMem(cursol_move_se, DX_PLAYTYPE_BACK);

		if (menu_cursor > 1)
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
			return eSceneType::eRanking;
		case 1:
			return eSceneType::eTitle;
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
		StopSoundMem(End_bgm);
		// �t�F�[�h�A�E�g
		fade->Initialize(false);

		// �J�[�\���ʒu�ɉ����ăV�[���J�ڂ�\��
		if (menu_cursor == 0) {
			next_scene = eSceneType::eRanking;
		}
		else if (menu_cursor == 1) {
			next_scene = eSceneType::eTitle;
		}
	}

	fade->Update();
	return GetNowSceneType();
	// �t�F�[�h�X�V
	fade->Update();

	// �t�F�[�h�X�V
	fade->Update();

	return GetNowSceneType();
}

void EndScene::Draw() const
{
	// �w�i�摜
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	// �J�[�\���摜�̕`��
	DrawRotaGraph(70, 455 + menu_cursor * 80, 0.3, DX_PI / 200.0, cursor_image, TRUE);

	// �t�F�[�h�`��
	fade->Draw();
}

void EndScene::Finalize()
{
	StopSoundMem(End_bgm);

	DeleteGraph(background_image);
	DeleteGraph(cursor_image);

	DeleteSoundMem(cursol_move_se);
}

eSceneType EndScene::GetNowSceneType() const
{
	return eSceneType::eEnd;
}
