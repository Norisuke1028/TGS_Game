#pragma once
#include "SceneBase.h"
#include "InputControl.h"

// ���U���g��ʃN���X
class ResultScene : public SceneBase
{
private:
	class Fade* fade;           // �t�F�[�h
	eSceneType result_next_scene;
	int result_cursor;
	Vector2D cursor_pos;		// �J�[�\�����W
	InputControl* pad_input;	// �R���g���[���[�̓��̓C���X�^���X
	int cursor_image;           // �J�[�\���C���[�W
	int result_title_image;     // ���U���g�^�C�g������
	int result_player_title;    // ���g�̃X�R�A��̃^�C�g������
	int result_score_history;   // �P�`�R�ʂ̃^�C�g������

	int cursor_se_move;         // �J�[�\���̈ړ�SE
	int cursor_se_push;         // �J�[�\���̌���SE

	std::vector<int> num_image; // �����p�摜

	int result_bgm;             // ���U���g���C��bgm

	// �Q�[���f�[�^
	int FinalScore;		        // �ŏI�X�R�A
	int LevelReached;	        // �ŏI���x��
	int Misinputs;	            // �~�X��

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

	void LoadHighScores();			// �n�C�X�R�A�f�[�^���t�@�C������擾����
	void SaveHighScores();			// �n�C�X�R�A�f�[�^���t�@�C���ɕۑ�����
	void HandleNewHighScore();		// ����̃X�R�A���ߋ��̃X�R�A��荂�����m�F����
	void DisplayCurrentRunScores() const;	// ����̃X�R�A��`��
	void DisplayHighScores() const;	// �n�C�X�R�A��`�悷��
	void DrawNumber(int x, int y, int number) const;        // �X�R�A���摜�ŕ`��

	int offset_plus;


	int HighScore_SE;               // �n�C�X�R�A��SE

	// �f�[�^����בւ���Z�b�^�[
	void DataSortDescending(std::vector<HighScoreEntry>& arr, int n);


	// UI�{�^�������o�[
	struct Button
	{
		int GraphicHandle;	// �{�^���̉摜�n���h��
		int x, y;			// �{�^���̂��Ƃ����W
		int Width, Height;	// �{�^���̕��ƍ���
		eSceneType TargetScene;	// �{�^����������čs�������V�[��
	};

	std::vector<Button> buttons;

public:
	// ���̃V�[������f�[�^���󂯎��iInGame�V�[���Ŏg���j
	void SetGameData(int score, int level, int misinputs)
	{
		this->FinalScore = score;
		this->LevelReached = level;
		this->Misinputs = misinputs;
	}


public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;
};