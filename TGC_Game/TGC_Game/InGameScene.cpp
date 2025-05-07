#include "InGameScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "DxLib.h"

InGameScene::InGameScene() :
	guzai_image()
	,select_image()
	,next()
	,correct()
	,sales()
	,check_count()
	,r_burger()
	,random()
	,buns_image()
	,select_burger_image()
	,sozai_count()
{
	ingame_cursol = 0;
	counter_time = 0;
	check_count = 0;
	next_scene = eSceneType::eInGame;
	next = 0;
	correct = 0;
	sales = 0;
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	guzai_image = LoadGraph("Resource/image/guzai.png");  //��ނ̉摜
	select_image = LoadGraph("Resource/image/kettei.png");  //����{�^���̉摜
	buns_image = LoadGraph("Resource/image/buns02.png");  //�o���Y�̉摜
	LoadDivGraph("Resource/image/guzai04.png", 4, 4, 1, 200, 170, select_burger_image);
}

eSceneType InGameScene::Update()
{
	//�������ԏ���
	if (counter_time <= 6000)
	{
		counter_time++;
		if (counter_time >= 6000)
		{
			//30�b�o�ƃ��U���g��ʂ֑J�ڂ���
			return eSceneType::eEnd;
		}

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
	//DrawString(50,50,"InGameScene�ł�",GetColor(255,255,255));
	//�w�i�i�K���j
	DrawBox(0, 0, 1280, 720, 0xffff00, true);
	//���Ԑ���
	DrawFormatString(1200, 20, 0x000000, "%d", counter_time / 100);
	
	//�I���������(�摜�\��)
	DrawRotaGraph(200,275,1.3,0, select_burger_image[guzai_select[0]],true);
	DrawRotaGraph(200, 235, 1.3, 0, select_burger_image[guzai_select[1]], true);
	DrawRotaGraph(200, 195, 1.3, 0, select_burger_image[guzai_select[2]], true);
	DrawRotaGraph(200, 155, 1.3, 0, select_burger_image[guzai_select[3]], true);

	//�w�肳���n���o�[�K�[
	DrawFormatString(300, 40, 0x000000, "%d", r_burger[0]);
	DrawFormatString(300, 60, 0x000000, "%d", r_burger[1]);
	DrawFormatString(300, 80, 0x000000, "%d", r_burger[2]);
	DrawFormatString(300, 100, 0x000000, "%d", r_burger[3]);

	DrawFormatString(600, 160, 0x000000, "%d", check_count);  //�W���b�W
	//DrawFormatString(600, 140, 0x000000, "%d", correct);  //����
	DrawFormatString(600, 180, 0x000000, "%d", sales);

	//��ޑI���J�[�\���`��
	DrawBox(19 + (ingame_cursol * 249.9), 519, 249 + (ingame_cursol * 249.9), 669, 0xffffff, false);
	DrawBox(20 + (ingame_cursol * 250), 520, 250 + (ingame_cursol * 250), 670, 0xffffff, false);
	DrawBox(21 + (ingame_cursol * 250.1), 521, 251 + (ingame_cursol * 250.1), 671, 0xffffff, false);

	//��ޑI��`��
	DrawBox(110, 150, 290, 180, 0xffffff, false);
	DrawBox(110, 190, 290, 220, 0xffffff, false);
	DrawBox(110, 230, 290, 260, 0xffffff, false);
	DrawBox(110, 270, 290, 300, 0xffffff, false);

	//��މ摜�̕`��
	DrawRotaGraph(510, 600,1.0,0,guzai_image, true);
	DrawRotaGraph(1135, 590, 0.8, 0, select_image, false);
	DrawRotaGraph(180, 220, 1.0, 0, buns_image, true);
}

void InGameScene::Finalize()
{
	DeleteGraph(background_image);
	DeleteGraph(guzai_image);
	DeleteGraph(select_image);
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
			//�I�񂾋�ނ̏���������
			for (int i = 0; i < 4; ++i) {
				guzai_select[i] = -1;
			}
			rand_burger();
			next += 1;
		case(1):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				if (ingame_cursol == 4)
				{
					next = 5;
				}
				else
				{
					guzai_select[0] = ingame_cursol;
					next += 1;
				}
			}
		break;
		case(2):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				if (ingame_cursol == 4)
				{
					next = 5;
				}
				else
				{
					guzai_select[1] = ingame_cursol;
					next += 1;
				}
			}
		break;
		case(3):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				if (ingame_cursol == 4)
				{
					next = 5;
				}
				else
				{
					guzai_select[2] = ingame_cursol;
					next += 1;
				}
			}
		break;
		case(4):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				// ����{�^����������Ă��ăJ�[�\�����f�ޑI���ʒu�Ȃ�f�ނ�I��
				if (ingame_cursol < 4)
				{
					guzai_select[3] = ingame_cursol;
				}
				// ����{�^����������Ă��ăJ�[�\��������ʒu�Ȃ�W���b�W��
				else if (ingame_cursol == 4)
				{
					next += 1;
				}
			}
			break;
		case(5):
			//����{�^���������Ƌ�ރ`�F�b�N
			check_guzai();
			if (check_count == sozai_count)
			{
				//�n���o�[�K�[�ɂ���Ĕ���z��ύX����
				sales += 200 + (random * 50);
				//�X�R�A��1���Z����
				correct++;

				next += 1;
			}
			else {
				check_count = 0;
				next = 0;
			}
		break;
		case(6):
			check_count = 0;
			next += 1;
			break;
		case(7):
				next = 0;
			break;
	}

	return 0;
}


//�w�肳���n���o�[�K�[�������_���ɏo��
int InGameScene::rand_burger()
{
	//�n���o�[�K�[�̃p�^�[��
	const int p_burger[6][4] = {
		{3,-1,-1,-1},  //�p�e�B�A��A��A��
		{3,1,-1,-1},   //�p�e�B�A�`�[�Y�A��A��
		{3,1,2,-1},    //�p�e�B�A�`�[�Y�A���^�X�A��
		{1,0,3,-1},    //�`�[�Y�A�g�}�g�A�p�e�B�A��
		{2,3,0,1},     //���^�X�A�p�e�B�A�g�}�g�A�`�[�Y
		{3,0,2,1}      //�p�e�B�A�g�}�g�A���^�X�A�`�[�Y
	};
	//�����_���ɐ������o��
	random = 0 + rand() % 6;

	sozai_count = 0;
	//�o�͂��ꂽ�����ɂ���ăn���o�[�K�[���o�͂���
	for (int j = 0; j < 4; ++j)
	{
		r_burger[j] = p_burger[random][j];
		if (r_burger[j] != -1)
		{
			sozai_count++;
		}
	}

	return 0;
}

//��ރ`�F�b�N����
int InGameScene::check_guzai()
{
	check_count = 0;

	for (int i = 0; i < sozai_count; i++)
	{
		if (guzai_select[i] != -1 && r_burger[i] == guzai_select[i])
		{
			check_count++;
		}
	}

	//��̕����ɂȂɂ���ނ��I������Ă�����s�����ɂ���
	for (int i = sozai_count; i < 4; i++)
	{
		if (guzai_select[i] != -1) //��m�F
		{
			check_count = -1; // �����s����
			break;
		}
	}

	return check_count;
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}