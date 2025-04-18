#include "TitleScene.h"
#include "InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() : menu_image(NULL),
cursor_image(NULL), menu_cursor(0)
{
}

TitleScene::~TitleScene()
{
	
}

void TitleScene::Initialize()
{
	menu_image = LoadGraph("Resource/images/");
	cursor_image = LoadGraph("Resource/images/");
	
	//// �摜�̓ǂݍ���
	//background_image = LoadGraph("Resource/images/Title.jpg");

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

	// �J�[�\�����ړ�
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{
		menu_cursor++;
		// ��ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	// �J�[�\����ړ�
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
	{
		menu_cursor--;
		// ��ԏ�ɓ��B������A��ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}



	// �J�[�\������
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::eInGame;
		case 1:
			return eSceneType::eRanking;
	/*	case 2:
			return eSceneType::help;*/
		default:
			return eSceneType::eEnd;
		}
	}

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update();
}

void TitleScene::Draw() const
{
	// �^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	// ���j���[�摜�̕`��
	DrawGraph(215, 320, menu_image, FALSE);

	// �J�[�\���摜�̕`��
	DrawRotaGraph(185, 340 + menu_cursor * 32, 1.6, DX_PI / 200.0, cursor_image, TRUE);

	// �^�C�g���e�L�X�g�̕\���i���W: x=50, y=50�A�F: ���j
	DrawString(50, 50, "�^�C�g����ʂł�", GetColor(255, 255, 255));
}

void TitleScene::Finalize()
{
	// �ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);

}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}