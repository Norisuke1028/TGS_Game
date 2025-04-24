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
	int check_count;  //�`�F�b�N�J�E���g
	int result;  //����

private:
	int burger[4];  //�n���o�[�K�[1

private:
	int guzai_image;  //��ނ̉摜
	int select_image;
	int select_burger;

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

	//��ރ`�F�b�N���菈��
	int check_guzai();
};

