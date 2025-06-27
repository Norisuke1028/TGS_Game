#include "RankingScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "GameDataManager.h"
#include "RankingManager.h"
#include "Fade.h"
#include "DxLib.h"
#include <algorithm>
#include <vector>
#include <fstream>

RankingScene::RankingScene()
	: fade(nullptr)
	, push_button_flag(false)
	, num_image()
	, ranking_next_scene()
{
	
}

RankingScene::~RankingScene()
{

}

void RankingScene::Initialize()
{
	// �{�^�������ꂽ�Ƃ���SE�ǂݍ���
	a_button_push = LoadSoundMem("Resource/sounds/SE/ranking/ranking_button_se.mp3");
	// ���C��bgm
	ranking_main_bgm = LoadSoundMem("Resource/sounds/BGM/ranking/ranking_main_bgm.mp3");
	// ���\�[�X�Ǘ��̃C���X�^���X���擾
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// �w�i�摜�ǂݍ���
	background_image = LoadGraph("Resource/image/ranking_background2.png");

	// �����摜�i0�`9�j�̓ǂݍ���
	num_image = rm->GetImages("Resource/image/number.png");

	// �t�F�[�h���C���X�^���X��
	fade = new Fade();
	// �t�F�[�h�̏����������i�t�F�[�h�C���j
	fade->Initialize(true);

	ChangeVolumeSoundMem(255 * 70 / 100, ranking_main_bgm);
	ChangeVolumeSoundMem(178, ranking_main_bgm);
	PlaySoundMem(ranking_main_bgm, DX_PLAYTYPE_BACK);

	scores = std::vector<ScoreData>(RankingManager::GetInstance().ReadScores());

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

// �`�揈��
void RankingScene::Draw() const
{
	// �w�i�摜�̕`��
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	int baseY = 170;      // �� Y���W�Œ�
	int rowHeight = 160;  // �� ���ʂ��Ƃ̕�

	for (int i = 0; i < scores.size(); ++i) {
		int y = baseY + i * rowHeight;

		DrawNumber(780, y, scores[i].sum);    // ���v�X�R�A
	}

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

// �w��ʒu�ɐ��l���摜�ŕ`�悷��(�����摜�`��p�̏���)
void RankingScene::DrawNumber(int x, int y, int number) const
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