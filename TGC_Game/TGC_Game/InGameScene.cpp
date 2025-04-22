#include "InGameScene.h"
#include "InputControl.h"
#include "DxLib.h"

InGameScene::InGameScene() :
	guzai_image()
{
	ingame_cursol = 0;
	counter_time = 0;
	next_scene = eSceneType::eInGame;

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	guzai_image = LoadGraph("Resource/image/guzai.png");
}

eSceneType InGameScene::Update()
{
	//�������ԏ���
	if (counter_time <= 3000)
	{
		counter_time++;
	}

	// �p�b�h���͐���̃C���X�^���X���擾
	InputControl* pad_input = InputControl::GetInstance();
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
	{
		ingame_cursol--;
		if (ingame_cursol < 0)
		{
			ingame_cursol = 4;
		}
	}

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		ingame_cursol++;
		if (ingame_cursol >4)
		{
			ingame_cursol = 0;
		}
	}
		select_guzai();

	// �e�N���X�̍X�V�������Ăяo��
	return GetNowSceneType();
}

//�`�揈��
void InGameScene::Draw() const
{
	//�C���Q�[���e�L�X�g
	DrawString(50,50,"InGameScene�ł�",GetColor(255,255,255));
	//�w�i�i�K���j
	DrawBox(0, 0, 1280, 720, 0xffff00, true);
	//���Ԑ���
	//DrawFormatString(1200, 20, 0xffffff, "%d", counter_time / 100);
	//��ޑI��
	DrawFormatString(600, 20, 0xffffff, "%d", ingame_cursol);
	//DrawFormatString(600, 40, 0xffffff, "%d", guzai_select);
	//��ޑI���J�[�\���`��
	DrawBox(19 + (ingame_cursol * 249.9), 519, 249 + (ingame_cursol * 249.9), 669, 0xffffff, false);
	DrawBox(20 + (ingame_cursol * 250), 520, 250 + (ingame_cursol * 250), 670, 0xffffff, false);
	DrawBox(21 + (ingame_cursol * 250.1), 521, 251 + (ingame_cursol * 250.1), 671, 0xffffff, false);
	//��މ摜�̕`��
	DrawRotaGraph(510, 600,1.0,0,guzai_image, true);
}

void InGameScene::Finalize()
{
}

//��ޑI������
int InGameScene::select_guzai()
{
	// �p�b�h���͐���̃C���X�^���X���擾
	InputControl* pad_input = InputControl::GetInstance();
	//��ނ�4��I��
	for (int i = 0; i < 3;i++)
	{
		if (ingame_cursol <4 && (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::eRelease))
		{
			//�I��������ނ�z��Ɋi�[����
		}
	}
	return 0;
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}