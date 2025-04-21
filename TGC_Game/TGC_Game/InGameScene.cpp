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
			ingame_cursol = 3;
		}
	}

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		ingame_cursol++;
		if (ingame_cursol >3)
		{
			ingame_cursol = 0;
		}
	}

	// �e�N���X�̍X�V�������Ăяo��
	return GetNowSceneType();
}

//�`�揈��
void InGameScene::Draw() const
{
	//�C���Q�[���e�L�X�g
	DrawString(50,50,"InGameScene�ł�",GetColor(255,255,255));
	//���Ԑ���
	DrawFormatString(1200, 20, 0xffffff, "%d", counter_time/100);
	//�w�i�i�K���j
	DrawBox(0, 0, 1280, 720, 0xffff00, true);
	//��ޑI���J�[�\���`��
	DrawBox(20 + (ingame_cursol * 250), 520, 250 + (ingame_cursol * 250), 670, 0xffffff, false);
	//��މ摜�̕`��
	DrawRotaGraph(510, 600,1.0,0,guzai_image, true);
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}