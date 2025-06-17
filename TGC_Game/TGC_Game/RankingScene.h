#pragma once
#include "SceneBase.h"
#include "GameDataManager.h"
#include "RankingManager.h"

// �����L���O��ʃN���X
class RankingScene : public SceneBase
{
private:
	class Fade* fade;
	std::vector<ScoreData> scores;  // �ǂݍ��񂾃X�R�A�ꗗ
	eSceneType ranking_next_scene; // �J�ڐ�̃V�[��
	bool push_button_flag;
	int a_button_push;
	int ranking_main_bgm;

	std::vector<int> num_image;

	int ranking_text_image;     // �u���ʁv�摜     
	int correct_text_image;     // �u�q�v�摜
	int sales_text_image;       // �u����v�摜
	int button_gaid_image;      // �{�^���ē��p�摜
	

	// �f�[�^
	struct RankData {
		int correct;
		int sales;
	};

public:
	RankingScene();
	~RankingScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const;
	virtual void Finalize() override;
	void DrawNumber(int x, int y, int number) const; //const�̗��R��Draw�Ɏ����Ă�������

public:
	virtual eSceneType GetNowSceneType() const override;

};
