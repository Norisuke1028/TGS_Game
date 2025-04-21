#pragma once

#include "SceneBase.h"


// �^�C�g���V�[��
class TitleScene : public SceneBase
{
private:
	class Fade* fade;        // �t�F�[�h

	int menu_image;			// ���j���[�摜
	int cursor_image;		// �J�[�\���摜
	int menu_cursor;		// ���j���[�J�[�\���ԍ�
	int title_bgm;          // �^�C�g��BGM
	int cursol_move_se;     // �J�[�\���ړ�SE
	int cursol_push_se;     // �J�[�\������SE

private:
	eSceneType next_scene; // �J�ڐ�̃V�[��
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual eSceneType GetNowSceneType() const override;

};

