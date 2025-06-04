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


	void DrawNumber(int x, int y, int number) const;        // �X�R�A���摜�ŕ`��
	

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

    void SaveScore(int correct, int sales);

public:
	virtual eSceneType GetNowSceneType() const override;
};