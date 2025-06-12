#include "RankingScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "GameDataManager.h"
#include "ResourceManager.h"
#include "Fade.h"
#include "DxLib.h"
#include <algorithm>
#include <vector>
#include <fstream>




RankingScene::RankingScene()
	: fade(nullptr)
	, push_button_flag(false)
	, text_image()
	, num_image()
	, certificate_image()
	, ranking_next_scene()
{

}

RankingScene::~RankingScene()
{

}

void RankingScene::Initialize()
{
	/*/ �{�^�������ꂽ�Ƃ���SE�ǂݍ���
	a_button_push = LoadSoundMem("Resource/sounds/SE/");
	// ���C��bgm
	ranking_main_bgm = LoadSoundMem("Resource/sounds/BGM/");*/
	// ���\�[�X�Ǘ��̃C���X�^���X���擾
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// �w�i�摜�ǂݍ���
	background_image = LoadGraph("Resource/image/ranking_background.png");

	/*/ �e�L�X�g�摜�̓ǂݍ���
	text_image = rm->GetImages("Resource/images/");
	tmp = rm->GetImages("Resource/images/");
	text_image.push_back(tmp[0]);

	certificate_image = rm->GetImages("Resource/images/");*/

	// �����摜�i0?9�j�̓ǂݍ���
	num_image = rm->GetImages("Resource/image/number.png");

	/*/ ���ʉ摜�̓ǂݍ���
	ranking_text_image = LoadGraph("Resource/images/");
	// ���x�����摜�̓ǂݍ���
	level_text_image = LoadGraph("Resource/images/");
	// �X�R�A�摜�̓ǂݍ���
	score_text_image = LoadGraph("Resource/images/");
	// �~�X���摜�̓ǂݍ���
	miss_text_image = LoadGraph("Resource/images/");*/

	// �t�F�[�h���C���X�^���X��
	fade = new Fade();
	// �t�F�[�h�̏����������i�t�F�[�h�C���j
	fade->Initialize(true);

	ChangeVolumeSoundMem(255 * 70 / 100, ranking_main_bgm);
	PlaySoundMem(ranking_main_bgm, DX_PLAYTYPE_BACK);

	// �� �����L���O�f�[�^��ǂݍ���
	LoadRankingData();

	ranking_next_scene = eSceneType::eRanking;
}

eSceneType RankingScene::Update()
{
	// �t�F�[�h�A�E�g���Ȃ�A�t�F�[�h�����𑱂���
	if (ranking_next_scene != eSceneType::eRanking) {
		if (fade->GetEndFlag()) {
			// �t�F�[�h�A�E�g������ɃV�[���J��
			return ranking_next_scene;
		}
		fade->Update();
		// �t�F�[�h�A�E�g���̓^�C�g���V�[�����ێ�
		return eSceneType::eRanking;
	}

	if (fade->GetEndFlag() == true)
	{

		// �p�b�h���͐���̃C���X�^���X���擾
		InputControl* pad_input = InputControl::GetInstance();

		if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
		{
			// �t�F�[�h�A�E�g����
			fade->Initialize(false);
			// ���C���̉����~�߂�
			StopSoundMem(ranking_main_bgm);
			// �����ꂽ�Ƃ���SE
			PlaySoundMem(a_button_push, DX_PLAYTYPE_BACK);
			// �^�C�g����ʂɑJ��
			ranking_next_scene = eSceneType::eTitle;
		}
	}
	else
	{
		// �t�F�[�h�X�V
		fade->Update();
	}

	return GetNowSceneType();
}

void RankingScene::Draw() 
{
	// �����L���O�e�L�X�g�̕\���i���W: x=50, y=50�A�F: ���j
	DrawString(50, 50, "�����L���O��ʂł�", GetColor(255, 255, 255));
	DrawString(10, 26, "A : Title", GetColor(255, 255, 255));
	
	// �w�i�摜�̕`��
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	/*
	DrawRotaGraphF(640.0f, 390.0f, 1.0, 0.0, certificate_image[0], TRUE);

	// "�����L���O"�e�L�X�g�`��
	DrawRotaGraphF(640.0f, 70.0f, 1.0, 0.0, text_image[0], TRUE);
	// �{�^���ē��\��
	DrawRotaGraphF(1150.0f, 680.0f, 1.0, 0.0, text_image[1], TRUE);

	// �����L���O
	DrawRotaGraph(280, 240, 0.7f, DX_PI / 0.5, ranking_text_image, TRUE);

	// ���x����
	DrawRotaGraph(400, 240, 0.7f, DX_PI / 0.5, level_text_image, TRUE);

	// �X�R�A
	DrawRotaGraph(620, 240, 0.7f, DX_PI / 0.5, score_text_image, TRUE);

	// �~�X��
	DrawRotaGraph(950, 240, 0.7f, DX_PI / 0.5, miss_text_image, TRUE);*/

	/*/ �����L���O�`��
	DrawRankingData();*/

	// �t�F�[�h�`��
	fade->Draw();
}

void RankingScene::Finalize()
{
	
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}

// �����L���O�f�[�^�ǂݍ��� & �\�[�g�i���と�ڋq���̏��ō~���j
void RankingScene::LoadRankingData()
{
	std::ifstream file("Resource/ScoreData/ranking.txt");
	rankList.clear();

	if (file.is_open()) {
		int correct, sales;
		while (file >> correct >> sales) {
			rankList.push_back({ correct, sales });
		}
		file.close();
	}

	// ����isales�j�� �ڋq���icorrect�j�̏��ɍ~���\�[�g
	std::sort(rankList.begin(), rankList.end(), [](const RankData& a, const RankData& b) {
		if (a.sales != b.sales) return a.sales > b.sales;
		return a.correct > b.correct;
		});
}

void RankingScene::DrawRankingData()
{
	if (rankList.empty()) return;

	int y = 100;

	// �ő�3�ʂ܂ŕ`��
	int drawCount = static_cast<int>(rankList.size());
	if (drawCount > 3) drawCount = 3;

	for (int i = 0; i < drawCount; ++i)
	{
		// �����N�ʒu�i��: 1�ʁj
		DrawFormatString(50, y + 20, GetColor(255, 255, 255), "%d��:", i + 1);

		// �ڋq���i�e�L�X�g + �摜�����j
		DrawString(150, y, "�ڋq��:", GetColor(255, 255, 255));
		DrawNumber(250, y, rankList[i].correct);

		// ����i�e�L�X�g + �摜�����j
		DrawString(400, y, "����:", GetColor(255, 255, 255));
		DrawNumber(470, y, rankList[i].sales);

		y += 70; // ���̍s��
	}
}




// �w��ʒu�ɐ��l���摜�ŕ`�悷��
void RankingScene::DrawNumber(int x, int y, int number) 
{
	if (num_image.empty()) return;  // �摜�������[�h�Ȃ�`�悵�Ȃ�

	int image_width, image_height;
	GetGraphSize(num_image[0], &image_width, &image_height);  // �摜�̃T�C�Y�擾

	int digit_width = image_width / 10;  // �e�����̕��i10���ɕ����j
	int digit_height = image_height;  // �摜�̍���

	std::string numStr = std::to_string(number); // �����𕶎���ɕϊ�

	for (size_t i = 0; i < numStr.length(); ++i)
	{
		int digit = numStr[i] - '0';  // �������琔�l�֕ϊ�
		int srcX = digit * digit_width;  // �摜����X���W
		int srcY = 0;  // Y���W�i1�s�̉摜�Ȃ�0�j

		// �摜�̈ꕔ��؂����ĕ`��
		DrawRectGraph(x + i * digit_width, y, srcX, srcY, digit_width, digit_height, num_image[0], TRUE, FALSE);
	}
}