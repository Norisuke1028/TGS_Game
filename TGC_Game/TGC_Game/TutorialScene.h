#pragma once

#include "SceneBase.h"


// �^�C�g���V�[��
class TutorialScene : public SceneBase
{
private:
	class Fade* fade;        // �t�F�[�h

	// �摜�p
	int button_gaid_images; // �{�^�������摜

	// �����p
	int tutorial_bgm;       // �^�C�g��BGM
	int cursol_push_se;     // �J�[�\������SE

private:
	eSceneType next_scene; // �J�ڐ�̃V�[��
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual eSceneType GetNowSceneType() const override;

};

