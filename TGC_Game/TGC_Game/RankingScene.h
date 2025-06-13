#pragma once
#include "SceneBase.h"
#include "GameDataManager.h"

// �����L���O��ʃN���X
class RankingScene : public SceneBase
{
private:
	class Fade* fade;
	std::vector<std::pair<int, int>> rankingList; // <correct, sales>
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

	struct RankData {
		int correct;
		int sales;
	};

	
	void DrawNumber(int x, int y, int number);        // �X�R�A���摜�ŕ`��

	

public:
	RankingScene();
	~RankingScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

};
