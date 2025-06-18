#pragma once
#include "SceneBase.h"

// �G���h��ʃN���X
class EndScene : public SceneBase
{
private:
	class Fade* fade;        // �t�F�[�h
	int all_end_time;        // �G���h��ʏI���܂ł̎��ԕϐ�

	int background_image;    // �w�i�摜�p
	int cursor_image;		// �J�[�\���摜
	int menu_cursor;		// ���j���[�J�[�\���ԍ�
	int ty_text_image;       // �uthanks you for playing�v��(�g�p�T�C�g)�e�L�X�g�摜�p


	int cursol_push_se;     // �J�[�\������SE
	int End_bgm;             // �G���h�pBGM
	int cursol_move_se;     // �J�[�\���ړ�SE

	eSceneType next_scene; // �J�ڐ�̃V�[��

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

};
