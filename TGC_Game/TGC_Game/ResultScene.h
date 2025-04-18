#pragma once
#include "SceneBase.h"
#include "InputControl.h"

// ���U���g��ʃN���X
class ResultScene : public SceneBase
{
private:
	Vector2D cursor_pos;		// �J�[�\�����W
	InputControl* pad_input;	// �R���g���[���[�̓��̓C���X�^���X
	Vector2D LeftStickTilt;		// ���X�e�B�b�N���͒l
	bool cursorOnButton;	// �J�[�\����UI�{�^���̏�ɂ���n���h��
	int cursor_blank_Graph;		// �J�[�\���摜�n���h��
	int cursor_on_Graph;		// �I���J�[�\���摜�n���h��
	int cursor_shadow_Graph;	// �J�[�\���e�摜�n���h��

	int cursor_se_move;         // �J�[�\���̈ړ�SE
	int cursor_se_push;         // �J�[�\���̌���SE

	int BackgroundGraph;	// �w�i�摜�n���h��

	std::vector<int> num_image;

	// ���U���g�V�[���摜�n���h��
	int ResultTitle_Graph;		// ���U���g�̃^�C�g���摜�n���h��
	int rank1_Graph;			// �����L���O�P�ʉ摜�n���h��
	int rank2_Graph;			// �����L���O�Q�ʉ摜�n���h��
	int rank3_Graph;			// �����L���O�R�ʉ摜�n���h��
	int YourScoreGraph;			// ���Ȃ��̃X�R�A�t�H���g�摜�n���h��
	int HighScoreHistory;		// �n�C�X�R�A���t�H���g�摜�n���h��
	int ReplayButton_Graph;		// ���v���C�{�^���摜�n���h��
	int TitleButton_Graph;		// �^�C�g���{�^���摜�n���h��

	// �w�i�摜�n���h��
	int backgroundWaves[4];
	float backgroundY[4];
	const int screenHeight = 720;
	float scrollSpeedY = 5;

	int result_bgm;             // ���U���g���C��bgm

	// �Q�[���f�[�^
	int FinalScore;		// �ŏI�X�R�A
	int LevelReached;	// �ŏI���x��
	int Misinputs;	// �~�X��

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

	// �����w�i�`��
	void DrawBackground();
	int offset_plus;


	int HighScore_SE;               // �n�C�X�R�A��SE

	// �f�[�^����בւ���Z�b�^�[
	void DataSortDescending(std::vector<HighScoreEntry>& arr, int n);

	// �J�[�\���`��
	void DrawCursor() const;


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