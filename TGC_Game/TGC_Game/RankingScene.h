#pragma once
#include "SceneBase.h"

// �����L���O��ʃN���X
class RankingScene : public SceneBase
{
private:
	class Fade* fade;
	eSceneType ranking_next_scene; // �J�ڐ�̃V�[��
	bool push_button_flag;
	int a_button_push;
	int ranking_main_bgm;

	std::vector<int> text_image;
	std::vector<int> num_image;
	std::vector<int> certificate_image;

	int ranking_text_image;     // �u���ʁv�摜     
	int level_text_image;       // �u���x���v�摜
	int score_text_image;       // �u�X�R�A�v�摜
	int miss_text_image;        // �u�~�X���v�摜

	// �Q�[���f�[�^
	int FinalScore;		// �ŏI�X�R�A
	int LevelReached;	// �ŏI���x��
	int Misinputs;	    // �~�X��

	struct HighScoreEntry
	{
		int score;
		int misinputs;
		int level;
	};

	// �n�C�X�R�A
	std::vector<HighScoreEntry> HighScores;		// �n�C�X�R�A���i�[���郔�F�N�^�[
	const int MaxHighScores = 3;		// �n�C�X�R�A��ۑ����鐔
	const char* HighScoreFileName = "Resource/ScoreData/Scores.txt";	// �n�C�X�R�A�f�[�^��ۑ����Ă���t�@�C���̖��O

	void LoadHighScores();			                        // �n�C�X�R�A�f�[�^���t�@�C������擾����
	void SaveHighScores();			                        // �n�C�X�R�A�f�[�^���t�@�C���ɕۑ�����
	void HandleNewHighScore();		                        // ����̃X�R�A���ߋ��̃X�R�A��荂�����m�F����
	void DisplayHighScores() const;	                        // �n�C�X�R�A��`�悷��
	void DrawNumber(int x, int y, int number) const;        // �X�R�A���摜�ŕ`��

	// �f�[�^����בւ���Z�b�^�[
	void DataSortDescending(std::vector<HighScoreEntry>& arr, int n);


public:
	// ���̃V�[������f�[�^���󂯎��iInGame�V�[���Ŏg���j
	void SetGameData(int score, int level, int misinputs)
	{
		this->FinalScore = score;
		this->LevelReached = level;
		this->Misinputs = misinputs;
	}

public:
	RankingScene();
	~RankingScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

};
