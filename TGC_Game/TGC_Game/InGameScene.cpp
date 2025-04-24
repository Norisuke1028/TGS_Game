#include "InGameScene.h"
#include "InputControl.h"
#include "DxLib.h"

InGameScene::InGameScene() :
	guzai_image()
	,select_image()
	,guzai_select()
	,burger()
	,next()
	,result()
	,check_count()

{
	ingame_cursol = 0;
	counter_time = 0;
	check_count = 0;
	int burger[4] = { 0,1,2,3 };
	next_scene = eSceneType::eInGame;
	next == 0;
	result = 0;
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	guzai_image = LoadGraph("Resource/image/guzai.png");
	select_image = LoadGraph("Resource/image/kettei.png");
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
				if (ingame_cursol > 4)
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
	//DrawFormatString(600, 20, 0xffffff, "%d", ingame_cursol);
	DrawFormatString(600, 40, 0xffffff, "%d", guzai_select[0]);
	DrawFormatString(600, 60, 0xffffff, "%d", guzai_select[1]);
	DrawFormatString(600, 80, 0xffffff, "%d", guzai_select[2]);
	DrawFormatString(600, 100, 0xffffff, "%d", guzai_select[3]);
	DrawFormatString(600, 120, 0xffffff, "%d", check_count);
	DrawFormatString(600, 140, 0xffffff, "%d", result);

	//��ޑI���J�[�\���`��
	DrawBox(19 + (ingame_cursol * 249.9), 519, 249 + (ingame_cursol * 249.9), 669, 0xffffff, false);
	DrawBox(20 + (ingame_cursol * 250), 520, 250 + (ingame_cursol * 250), 670, 0xffffff, false);
	DrawBox(21 + (ingame_cursol * 250.1), 521, 251 + (ingame_cursol * 250.1), 671, 0xffffff, false);
	//��މ摜�̕`��
	DrawRotaGraph(510, 600,1.0,0,guzai_image, true);
	DrawRotaGraph(1100, 600, 0.8, 0, select_image, true);
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
	switch (next)
	{
		case(0):
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
		{
			//guzai_select1 = ingame_cursol;
			guzai_select[0] = ingame_cursol;
			next += 1;
		}
		break;
		case(1):
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
		{
			guzai_select[1] = ingame_cursol;
			next += 1;
		}
		break;
		case(2):
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
		{
			guzai_select[2] = ingame_cursol;
			next += 1;
		}
		break;
		case(3):
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
		{
			guzai_select[3] = ingame_cursol;
				next += 1;
		}
		break;
		case(4):
		if (ingame_cursol == 4 && pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
		{
			check_guzai();
			if (check_count == 4)
			{
				next += 1;
			}
			else {
				check_count = 0;
				next = 0;
			}
		}
		break;
		case(5):
			result++;
			check_count = 0;
			next += 1;
			break;
		case(6):
			next = 0;
			break;
	}

	return 0;
}

//��ރ`�F�b�N����
int InGameScene::check_guzai()
{
	int burger[4] = { 0,1,2,3 };

	//int burger[3] = { 0,1,2 };


	for (int i = 0; i < 4; i++)
	{
		if (burger[i] == guzai_select[i])
		{
			check_count++;
		}
	}


	return check_count;
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}