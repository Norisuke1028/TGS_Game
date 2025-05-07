#pragma once

#include "SceneBase.h"
//#include "Vector2D.h"
#include <vector>


// �C���Q�[���V�[��
class InGameScene : public SceneBase
{
private:
	int ingame_cursol;  //��ޑI���J�[�\��
	int counter_time;  //���Ԑ���
	int guzai_select[4] = {-1, -1, -1, -1};  //�I�񂾋�ނ̔ԍ����i�[
	int next;  //��ނ�I�ԂƎ��̑I����
	int check_count;  //�`�F�b�N�J�E���g
	int correct;  //����
	int sales;  //����
	int sozai_count;  

private:
	int r_burger[4];  //�n���o�[�K�[�������_���ɏo��
	int random;
	//const int burger_A[4];  //�n���o�[�K�[1
	//int burger_B[4];

private:
	int guzai_image;  //��ނ̉摜
	int select_image;
	int buns_image;
	int select_guzai_image;
	int select_burger_image[4];

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

	//�w�肳���n���o�[�K�[�������_���o��
	int rand_burger();

	//��ރ`�F�b�N���菈��
	int check_guzai();
};

