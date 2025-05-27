#include "InGameScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "DxLib.h"

#include <string>
#include <iostream>
#include <thread>

InGameScene::InGameScene() :
	guzai_image(),select_image(),next(),correct(),sales(),check_count(),r_burger(),random()
	,buns_image(),select_burger_image(),burger_model(),sozai_count(),ingame_cursol(),counter_time(),back_image(),g_number_image()
	,delay()
{
	next_scene = eSceneType::eInGame;
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
	back_image = LoadGraph("Resource/image/background.png");  //�w�i�摜
	LoadDivGraph("Resource/image/guzai04.png", 4, 4, 1, 200, 170, select_burger_image);  //�I�񂾋�މ摜
	LoadDivGraph("Resource/image/burger_model.png", 6, 6, 1, 266.6, 140, burger_model);  //����o�[�K�[�摜
	LoadDivGraph("Resource/image/number.png", 10, 5, 2, 132, 330, g_number_image);  //�Q�[�����Ŏg�p����i���o�[�摜
	customer.Initialize();  //�q�N���X�̏���������
}

eSceneType InGameScene::Update()
{
	//�Q�[���̐i�s����
	switch (gameState)
	{
	//�n�߂�3�J�E���g����
	case GameState::Countdown:
	{
		double elapsed = countDownTimer.GetElapsedSeconds();

		ClearDrawScreen();
		Draw(); // �w�i�`��Ȃ�

		//3�J�E���g�p
		if (elapsed < 3.0) {
			int count = 3 - static_cast<int>(elapsed);
			DrawRotaGraph(640, 360, 2.0, 0, g_number_image[count-1], true);
			//DrawFormatString(600, 300, 0xFFFFFF, "%d", count);
		}
		else if (elapsed < 3.8) {
			DrawString(600, 300, "�X�^�[�g�I", 0xFFFFFF);
		}
		else {
			timer.Start();  // �{�҂̃^�C�}�[�J�n
			gameState = GameState::Playing; // ���̏�Ԃ֑J��
		}

		ScreenFlip();
		break;
	}
	//�Q�[�����C���X�^�[�g
	case GameState::Playing:
	{
		ClearDrawScreen();
		//�J�[�\������ݒ�
		CursolControl();

		//�`�揈��
		Draw();
		//�����x�点�ĕ`�悷��
		if (next >= 1 && next < 7) {
			//�q�Ɛ����o���̕`�揈��
			customer.Draw();
		}

		select_guzai();

		// �������ԃ`�F�b�N
		if (timer.IsTimeUp(limit)) {
			gameState = GameState::Result;
		}

		ScreenFlip();
		break;
	}
	//���U���g��
	case GameState::Result:
	{
		//30�b�o�ƃ��U���g��ʂ֑J�ڂ���	
		return eSceneType::eResult;
	}
	}
	return eSceneType::eInGame;
}

//�`�揈��
void InGameScene::Draw() const
{
	//�w�i�i�K���j
	DrawRotaGraph(640, 360, 1.0, 0, back_image, true);

	//Playing�ɂȂ�Ǝ��s
	if (gameState == GameState::Playing)
	{
		//���Ԑ���
		DrawFormatString(1150, 50, 0x000000, "�������ԁ@�@%d", static_cast<int>(timer.GetElapsedSeconds()));

		//��ޑI���J�[�\���`��
		DrawBox(19 + (ingame_cursol * 249.9), 519, 249 + (ingame_cursol * 249.9), 669, 0xffffff, false);
		DrawBox(20 + (ingame_cursol * 250), 520, 250 + (ingame_cursol * 250), 670, 0xffffff, false);
		DrawBox(21 + (ingame_cursol * 250.1), 521, 251 + (ingame_cursol * 250.1), 671, 0xffffff, false);

		//�f�B���C�������ĕ\������
		if (next >= 1 && next < 7) {
			//����̃o�[�K�[�̕\��
			DrawRotaGraph(870, 100, 3.0, 0, burger_model[random], true);
		}
	}

	//�I���������(�摜�\��)
	DrawRotaGraph(200, 275, 1.3, 0, select_burger_image[guzai_select[0]], true);
	DrawRotaGraph(200, 235, 1.3, 0, select_burger_image[guzai_select[1]], true);
	DrawRotaGraph(200, 195, 1.3, 0, select_burger_image[guzai_select[2]], true);
	DrawRotaGraph(200, 155, 1.3, 0, select_burger_image[guzai_select[3]], true);

	//��ޑI��`��
	DrawBox(110, 150, 290, 180, 0xffffff, false);
	DrawBox(110, 190, 290, 220, 0xffffff, false);
	DrawBox(110, 230, 290, 260, 0xffffff, false);
	DrawBox(110, 270, 290, 300, 0xffffff, false);

	DrawFormatString(1150, 140, 0x000000, "���𐔁@�@%d", correct);  //����
	DrawFormatString(1150, 180, 0x000000, "����@�@�@%d", sales);  //����グ

	DrawRotaGraph(510, 600, 1.0, 0, guzai_image, true);  //��މ摜�̕`��
	DrawRotaGraph(1135, 590, 0.8, 0, select_image, false);  //����{�^���̕`��
	DrawRotaGraph(180, 220, 1.0, 0, buns_image, true);  //�o���Y�̉摜�̕`��

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

				//�f�B���C��������
				if (delay < 150)
				{
					delay++;
				}
				else {
					//�����x�点�Ď��s����
					delay = 0;
					rand_burger();
					next += 1;
				}
		//��ވ�g��
		case(1):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				//����{�^���������ƃW���b�W������
				if (ingame_cursol == 4)
				{
					next = 5;
				}
				//��ނ�I�������1�ڂɋ�ނ�I��
				else
				{
					guzai_select[0] = ingame_cursol;
					next += 1;
				}
			}
		break;
		//��ޓ�g��
		case(2):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				//����{�^���������ƃW���b�W������
				if (ingame_cursol == 4)
				{
					next = 5;
				}
				//��ނ�I�������2�ڂɋ�ނ�I��
				else
				{
					guzai_select[1] = ingame_cursol;
					next += 1;
				}
			}
		break;
		//��ގO�g��
		case(3):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				//����{�^���������ƃW���b�W������
				if (ingame_cursol == 4)
				{
					next = 5;
				}
				//��ނ�I�������3�ڂɋ�ނ�I��
				else
				{
					guzai_select[2] = ingame_cursol;
					next += 1;
				}
			}
		break;
		//��ގl�g��
		case(4):
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				// ����{�^����������Ă��ăJ�[�\�����f�ޑI���ʒu�Ȃ�f�ނ�I��
				//4�ڂɋ�ނ�I��
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

			//����̑f�ނ̐��ƃ`�F�b�N�J�E���g������(�W���b�W����ɐ���)��������
			if (check_count == sozai_count)
			{
				//�n���o�[�K�[�ɂ���Ĕ���z��ύX����
				sales += 200 + (random * 50);
				//�X�R�A��1���Z����
				correct++;

				next += 1;
			}
			//�W���b�W����Ɏ��s����ƃ��Z�b�g
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
		//����̑f�ސ����J�E���g����
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

	//����̑f�ނ̐����W���b�W������s��
	for (int i = 0; i < sozai_count; i++)
	{
		//����ʂ�ɑI���ł���΃J�E���g����
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

//�J�[�\������ݒ�
void InGameScene::CursolControl()
{
	// �p�b�h���͐���̃C���X�^���X���擾
	InputControl* pad_input = InputControl::GetInstance();

	//�\���L�[�̑���
		//���p
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
	{
		ingame_cursol--;
		if (ingame_cursol < 0)
		{
			ingame_cursol = 4;
		}
	}
	//�E�p
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		ingame_cursol++;
		if (ingame_cursol > 4)
		{
			ingame_cursol = 0;
		}
	}
}