#include "RankingScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "Fade.h"
#include "DxLib.h"

RankingScene::RankingScene()
	: fade(nullptr)
	, push_button_flag(false)
	, text_image()
	, num_image()
	, certificate_image()
{

}

RankingScene::~RankingScene()
{

}

void RankingScene::Initialize()
{
	// �{�^�������ꂽ�Ƃ���SE�ǂݍ���
	a_button_push = LoadSoundMem("Resource/Sounds/SE/cursol_push_se.mp3");
	// ���C��bgm
	ranking_main_bgm = LoadSoundMem("Resource/Sounds/BGM/main_sound1.mp3");
	// ���\�[�X�Ǘ��̃C���X�^���X���擾
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// �w�i�摜�ǂݍ���
	background_image = LoadGraph("Resource/Images/Scene/Tutorial/Background.png");
	// �e�L�X�g�摜�̓ǂݍ���
	text_image = rm->GetImages("Resource/Images/Scene/Ranking/Text/Ranking.png");
	tmp = rm->GetImages("Resource/Images/Scene/Ranking/Text/Back1.png");
	text_image.push_back(tmp[0]);

	certificate_image = rm->GetImages("Resource/Images/Scene/Ranking/Certificate.png");

	// �����摜�i0?9�j�̓ǂݍ���
	num_image = rm->GetImages("Resource/Images/Scene/InGame/Text/Num.png");

	// ���ʉ摜�̓ǂݍ���
	ranking_text_image = LoadGraph("Resource/Images/Scene/Ranking/Text/number_ranking.png");
	// ���x�����摜�̓ǂݍ���
	level_text_image = LoadGraph("Resource/Images/Scene/Ranking/Text/level.png");
	// �X�R�A�摜�̓ǂݍ���
	score_text_image = LoadGraph("Resource/Images/Scene/Ranking/Text/score.png");
	// �~�X���摜�̓ǂݍ���
	miss_text_image = LoadGraph("Resource/Images/Scene/Ranking/Text/miss.png");

	// �t�F�[�h���C���X�^���X��
	fade = new Fade();
	// �t�F�[�h�̏����������i�t�F�[�h�C���j
	fade->Initialize(true);

	// �n�C�X�R�A�f�[�^���擾
	LoadHighScores();

	ChangeVolumeSoundMem(255 * 70 / 100, ranking_main_bgm);
	PlaySoundMem(ranking_main_bgm, DX_PLAYTYPE_BACK);

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

		if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
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

void RankingScene::Draw() const
{
	DrawString(10, 10, "Ranking", GetColor(255, 255, 255));
	DrawString(10, 26, "Z : Title", GetColor(255, 255, 255));

	DrawGraph(0, 0, background_image, TRUE);

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
	DrawRotaGraph(950, 240, 0.7f, DX_PI / 0.5, miss_text_image, TRUE);

	// �n�C�X�R�A��`��
	DisplayHighScores();

	// �t�F�[�h�`��
	fade->Draw();
}

void RankingScene::Finalize()
{
	// �X�R�A��ۑ�
	SaveHighScores();
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}

// �n�C�X�R�A���\�[�g����
void RankingScene::DataSortDescending(std::vector<HighScoreEntry>& arr, int n)
{
	int i, j;
	HighScoreEntry key;

	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j].score < key.score)  /***** ���בւ������ *****/
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}

		arr[j + 1] = key;
	}
}

// �n�C�X�R�A�̃f�[�^���擾����
void RankingScene::LoadHighScores()
{
	// �t�@�C�����J����
	FILE* inputFile;
	fopen_s(&inputFile, HighScoreFileName, "r");

	//�G���[�`�F�b�N
	if (inputFile != NULL)
	{
		HighScoreEntry entry;
		int i = 0;

		// �t�@�C�����烌�x���A�X�R�A�A�~�X���̏��Ԃœǂݍ���
		while (fscanf_s(inputFile, "%d %d %d", &entry.level, &entry.score, &entry.misinputs) == 3 && i < MaxHighScores)
		{
			HighScores.push_back(entry);
			i++;
		}
		fclose(inputFile);

		// �X�R�A���\�[�g����
		if (HighScores.size() > 1)
		{
			DataSortDescending(HighScores, HighScores.size());
		}
	}
}

// �n�C�X�R�A��ۑ�����
void RankingScene::SaveHighScores()
{
	// ����̃X�R�A���n�C�X�R�A��荂�����`�F�b�N
	HandleNewHighScore();

	FILE* outputFile;
	fopen_s(&outputFile, HighScoreFileName, "w");

	// �G���[�`�F�b�N
	if (outputFile != NULL)
	{
		// ���x���A�X�R�A�A�~�X���̏��ԂŃt�@�C���ɏ�������
		for (size_t i = 0; i < HighScores.size(); ++i)
		{
			fprintf_s(outputFile, "%d %d %d\n", HighScores[i].level, HighScores[i].score, HighScores[i].misinputs);
		}

		fclose(outputFile);
	}
}


// �X�R�A���n�C�X�R�A��荂�����m�F
void RankingScene::HandleNewHighScore()
{
	HighScoreEntry newEntry;
	newEntry.level = LevelReached;
	newEntry.score = FinalScore;
	newEntry.misinputs = Misinputs;

	if (HighScores.size() < MaxHighScores || FinalScore > HighScores.back().score)
	{
		HighScores.push_back(newEntry);

		// �f�[�^����בւ���
		if (HighScores.size() > 1)
		{
			DataSortDescending(HighScores, HighScores.size());
		}

		// �f�[�^�����ۑ��ł��鐔��葽����΁A��ԉ��̃f�[�^����������
		if (HighScores.size() > MaxHighScores)
		{
			HighScores.pop_back();
		}
	}
}

// �n�C�X�R�A�̕`��
void RankingScene::DisplayHighScores() const
{
	int yOffset = 290;      // y���I�t�Z�b�g
	int rankX = 250;        // ���ʂ�X���W
	int levelX = 350;       // ���x����X���W
	int scoreX = 500;       // �X�R�A��X���W
	int missX = 800;        // �~�X��X���W
	int rowSpacing = 100;    // �s�Ԃ̃X�y�[�X
	int digitWidth = 32;    // 1���̕��i�g�p����t�H���g�摜�ɍ��킹��j

	for (size_t i = 0; i < HighScores.size(); ++i)
	{
		// ���ʂ�`��i�摜�Łj
		DrawNumber(rankX, yOffset, i + 1);

		// ���x����`��
		DrawNumber(levelX, yOffset, HighScores[i].level);

		// �X�R�A��`��
		DrawNumber(scoreX, yOffset, HighScores[i].score);

		// �~�X�̉񐔂�`��
		DrawNumber(missX, yOffset, HighScores[i].misinputs);

		yOffset += rowSpacing; // ���̍s��
	}
}

// �w��ʒu�ɐ��l���摜�ŕ`�悷��
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