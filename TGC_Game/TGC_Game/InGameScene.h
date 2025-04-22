#pragma once

#include "SceneBase.h"


// �C���Q�[���V�[��
class InGameScene : public SceneBase
{
private:
	int ingame_cursol;  //��ޑI���J�[�\��
	int counter_time;  //���Ԑ���
	int guzai_select[4];

private:
	int guzai_image;  //��ނ̉摜

private:
	eSceneType next_scene;

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual eSceneType GetNowSceneType() const override;

	//��ޑI������
	int select_guzai();
};

