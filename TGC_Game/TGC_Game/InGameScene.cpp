#include "InGameScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "GameDataManager.h"
#include "DxLib.h"

#include <string>
#include <iostream>
#include <thread>
#include <fstream>

InGameScene::InGameScene() :
	guzai_image(),select_image(),next(),correct(),sales(),check_count(),r_burger(),random(),sb_image()
	,buns_image(),select_burger_image(),burger_model(),sozai_count(),ingame_cursol(),counter_time()
	,back_image(),gb_number_image(),gr_number_image(),start_image()
	,delay(),countdown(),GM_timer(), elapsed()
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
	back_image = LoadGraph("Resource/image/main_background.png");  //�w�i�摜
	sb_image = LoadGraph("Resource/image/denpyo.png");  //�X�R�A�{�[�h�摜
	start_image = LoadGraph("Resource/image/start.png");  //�X�^�[�g�摜
	LoadDivGraph("Resource/image/guzai04.png", 4, 4, 1, 200, 170, select_burger_image);  //�I�񂾋�މ摜
	LoadDivGraph("Resource/image/burger_model.png", 6, 6, 1, 266.6, 140, burger_model);  //����o�[�K�[�摜
	LoadDivGraph("Resource/image/Num.png", 10, 10, 1, 49, 80, gb_number_image);  //�Q�[�����Ŏg�p����i���o�[�摜(��)
	LoadDivGraph("Resource/image/red_number.png", 10, 10, 1, 50, 80, gr_number_image);  //�Q�[�����Ŏg�p����i���o�[�摜(��)
	cursol_se = LoadSoundMem("Resource/sounds/cursol.mp3");  //�J�[�\����
	correct_se = LoadSoundMem("Resource/sounds/correct.mp3");  //������
	incorrect_se = LoadSoundMem("Resource/sounds/incorrect.mp3");  //�s������
	sales_se = LoadSoundMem("Resource/sounds/sales.mp3");  //���㉹
	GM_bgm = LoadSoundMem("Resource/sounds/MainBGM.mp3");  //�Q�[�����C��BGM
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
		elapsed = countDownTimer.GetElapsedSeconds();

		ClearDrawScreen();
		PlaySoundMem(GM_bgm, DX_PLAYTYPE_LOOP);
		Draw(); // �w�i�`��Ȃ�

		//3�J�E���g�p
		if (elapsed < 4.0) {
			countdown = 4 - static_cast<int>(elapsed);
		}
		else if (elapsed > 5.1) {
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
		if (next != 0) {
			//�J�[�\������ݒ�
			CursolControl();
		}

		//�`�揈��
		Draw();

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
		GameDataManager::GetInstance().SetCorrect(correct);
		GameDataManager::GetInstance().SetSales(sales);

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

	//Countdown�ɂȂ�Ǝ��s
	if (gameState == GameState::Countdown)
	{
		//3�J�E���g�_�E���p
		if (elapsed < 4.0) {
			DrawRotaGraph(640, 340, 3.0, 0, gr_number_image[countdown], true);
		}
		//�X�^�[�g�\���p
		else if (elapsed < 4.8) {
			DrawRotaGraph(640, 340, 2.0, 0, start_image, true);
		}
	}

	//Playing�ɂȂ�Ǝ��s
	if (gameState == GameState::Playing)
	{
		//�������Ԃ̒l���󂯎��
		int GM_timer = 30-static_cast<int>(timer.GetElapsedSeconds());

		int t_tens = (GM_timer / 10) % 10;  // �\�̈�(��������)
		int t_ones = GM_timer % 10;        // ��̈�(��������)

		//���Ԑ���
		DrawCircle(1175, 80, 75, 0x000000, true);
		DrawCircle(1175, 80, 70, 0xffffff, true);
		DrawRotaGraph(1155, 80, 1.0, 0, gb_number_image[t_tens], true);
		DrawRotaGraph(1200, 80, 1.0, 0, gb_number_image[t_ones], true);

		//��ޑI���J�[�\���`��
		DrawBox(19 + (ingame_cursol * 249.9), 519, 249 + (ingame_cursol * 249.9), 669, 0xffffff, false);
		DrawBox(20 + (ingame_cursol * 250), 520, 250 + (ingame_cursol * 250), 670, 0xffffff, false);
		DrawBox(21 + (ingame_cursol * 250.1), 521, 251 + (ingame_cursol * 250.1), 671, 0xffffff, false);

		DrawRotaGraph(1155, 330, 1.0, 0, sb_image, true);  //�X�R�A�{�[�h(�`�[)�̉摜


		DrawRotaGraph(1180, 315, 1.0, 0, gb_number_image[correct], true);  //����

		int s_thousands = (sales / 1000) % 10;   // ��̈�(����)
		int s_hundreds = (sales / 100) % 10;    // �S�̈�(����)
		int s_tens = (sales / 10) % 10;     // �\�̈�(����)
		int s_ones = sales % 10;            // ��̈�(����)
		if (sales >= 1000)DrawRotaGraph(1095, 430, 1.0, 0, gb_number_image[s_thousands], true);  // ��̈�(����)
		if (sales >= 100)DrawRotaGraph(1140, 430, 1.0, 0, gb_number_image[s_hundreds], true);  // �S�̈�(����)
		if (sales >= 10)DrawRotaGraph(1185, 430, 1.0, 0, gb_number_image[s_tens], true);  // �\�̈�(����)
		DrawRotaGraph(1230, 430, 1.0, 0, gb_number_image[s_ones], true);  // ��̈�(����)

		//�f�B���C�������ĕ\������
		if (next >= 1 && next < 7) {
			//�q�Ɛ����o���̕`�揈��
			customer.Draw();
			//����̃o�[�K�[�̕\��
			DrawRotaGraph(790, 150, 3.0, 0, burger_model[random], true);
		}
	}

	//�I���������(�摜�\��)
	DrawRotaGraph(200, 195, 1.3, 0, select_burger_image[guzai_select[0]], true);
	DrawRotaGraph(200, 155, 1.3, 0, select_burger_image[guzai_select[1]], true);
	DrawRotaGraph(200, 115, 1.3, 0, select_burger_image[guzai_select[2]], true);
	DrawRotaGraph(200, 75, 1.3, 0, select_burger_image[guzai_select[3]], true);

	//��ޑI��`��
	DrawBox(110, 100, 290, 80, 0xffffff, false);
	DrawBox(110, 140, 290, 120, 0xffffff, false);
	DrawBox(110, 180, 290, 160, 0xffffff, false);
	DrawBox(110, 220, 290, 200, 0xffffff, false);

	DrawRotaGraph(510, 600, 1.0, 0, guzai_image, true);  //��މ摜�̕`��
	DrawBox(1035, 535, 1235, 645, 0x000000, true);  //����{�^���O�g
	DrawRotaGraph(1135, 590, 0.8, 0, select_image, false);  //����{�^���̕`��
	DrawRotaGraph(180, 140, 1.0, 0, buns_image, true);  //�o���Y�̉摜�̕`��

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
				if (delay < 50)
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
				PlaySoundMem(correct_se, DX_PLAYTYPE_BACK);

				next += 1;
			}
			//�W���b�W����Ɏ��s����ƃ��Z�b�g
			else {
				PlaySoundMem(incorrect_se, DX_PLAYTYPE_BACK);
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
		PlaySoundMem(cursol_se, DX_PLAYTYPE_BACK);
		if (ingame_cursol < 0)
		{
			ingame_cursol = 4;
		}
	}
	//�E�p
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		ingame_cursol++;
		PlaySoundMem(cursol_se, DX_PLAYTYPE_BACK);
		if (ingame_cursol > 4)
		{
			ingame_cursol = 0;
		}
	}
}

