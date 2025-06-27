#pragma once
#include "SceneBase.h"

// Credit�N���X
class CreditScene : public SceneBase
{
private:
	class Fade* fade;        // �t�F�[�h
	int all_credit_time;        // �N���W�b�g��ʏI���܂ł̎��ԕϐ�

	int background_image;    // �w�i�摜�p

	eSceneType next_scene; // �J�ڐ�̃V�[��

public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

};

