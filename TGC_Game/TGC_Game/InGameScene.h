#pragma once

#include "SceneBase.h"
#include <vector>


// �C���Q�[���V�[��
class InGameScene : public SceneBase
{
private:
	int ingame_cursol;  //��ޑI���J�[�\��
	int counter_time;  //���Ԑ���
	int guzai_select[4] = {0};  //�I�񂾋�ނ̔ԍ����i�[
	int next;  //��ނ�I�ԂƎ��̑I����

	//std::vector<int> guzai_select;  //�I�񂾋�ނ̔ԍ����i�[

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

