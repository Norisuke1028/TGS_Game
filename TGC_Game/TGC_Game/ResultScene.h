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
	int result_sum_title;       // ���g�̍��v�X�R�A��̃^�C�g������
	int result_score_history;   // �P�`�R�ʂ̃^�C�g������
	int result_collect_font;    //  �ڋq���摜
	int sb_result_image;  //���U���g�̃X�R�A�{�[�h�摜
	int result_sales_font;      //  ����摜
	int result_button_image;    //�V�[���J�ډ摜
	int sum_background;         //  �h�������[��SE
	int result_se;              //���U���gSE(���W��)

	int result_score_time;      // �X�R�A���b��

	int result_bronze_font;
	int result_bronze_badge;
	int result_gold_font;
	int result_gold_badge;
	int result_diamond_font;
	int result_diamond_badge;


	int cursor_se_move;         // �J�[�\���̈ړ�SE
	int cursor_se_push;         // �J�[�\���̌���SE
	int result_badge_se;        // �o�b�W�\����SE

	std::vector<int> num_image; // �����p�摜


	int result_bgm;             // ���U���g���C��bgm


	void DrawNumber(int x, int y, int number, float scale) const;        // �X�R�A���摜�ŕ`��
	void SumDrawNumber(int x, int y, int number, float scale) const;

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

    void SaveScore(int correct, int sales);

public:
	virtual eSceneType GetNowSceneType() const override;
};