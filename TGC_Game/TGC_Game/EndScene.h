#pragma once
#include "SceneBase.h"

// �G���h��ʃN���X
class EndScene : public SceneBase
{
private:
	class Fade* fade;        // �t�F�[�h
	int all_end_time;        // �G���h��ʏI���܂ł̎��ԕϐ�

	int background_image;    // �w�i�摜�p
	int ty_text_image;       // �uthanks you for playing�v��(�g�p�T�C�g)�e�L�X�g�摜�p

	int End_bgm;             // �G���h�pBGM


public:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

};
