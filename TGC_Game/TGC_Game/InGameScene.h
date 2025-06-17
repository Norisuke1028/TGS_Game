#pragma once

#include "SceneBase.h"
//#include "Vector2D.h"
#include "Customer.h"
#include "Timer.h"
#include <vector>

enum class GameState
{
	Countdown,
	Playing,
	Result
};


// �C���Q�[���V�[��
class InGameScene : public SceneBase
{
private:
	GameState gameState = GameState::Countdown;  //�Q�[���X�e�[�g���J�E���g�_�E���ɐݒ�
	Timer countDownTimer;  //�J�E���g�_�E���p�^�C�}�[
	Timer gameTimer;  //�Q�[�����C���^�C�}�[
	class Fade* fade;        // �t�F�[�h

	Customer customer;
	Timer timer;

	int ingame_cursol;  //��ޑI���J�[�\��
	int counter_time;  //���Ԑ���
	int select;
	int guzai_select[4] = {0, 0, 0, 0};  //�I�񂾋�ނ̔ԍ����i�[
	int next;  //��ނ�I�ԂƎ��̑I����
	int check_count;  //�`�F�b�N�J�E���g
	int correct_check;
	int correct;  //����
	int total_sales;  //���v����
	int sales; //����
	int plus;
	int sozai_count;  //����̑f�ސ�
	int delay;  //�f�B���C�p�J�E���g
	const double limit = 30.0;  //��������
	int countdown;  //�J�E���g�_�E���p
	int GM_timer;  //�Q�[�����C���^�C�}�[
	double elapsed;  //�o�߂�������

private:
	int r_burger[4];  //�n���o�[�K�[�������_���ɏo��
	int random;
	//const int burger_A[4];  //�n���o�[�K�[1
	//int burger_B[4];

private:
	int guzai_image;  //��ނ̉摜
	int select_image;  //����{�^���摜
	int buns_image;  //�o���Y�̉摜
	int back_image;  //�w�i�摜
	int select_guzai_image;
	int arrow_image;  //���摜
	int select_burger_image[4];  //�I�񂾋�މ摜
	int burger_model[6];  //����o�[�K�[�摜
	int gb_number_image[10];  //�Q�[�����Ŏg���i���o�[�摜(��) gamebrack
	int gr_number_image[10];  //�Q�[�����Ŏg���i���o�[�摜(��) gamered
	int sb_image;  //�X�R�A�{�[�h�摜
	int start_image;  //�Q�[���J�n�摜
	int controller_image;  //����ݒ�摜
	
	int cursol_se;  //�J�[�\����
	int correct_se;  //������
	int incorrect_se;  //�s������
	int sales_se;  //���㉹
	int select_se;  //�I����
	int GM_bgm;  //�Q�[�����C��BGM

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

	//�J�[�\���̑���ݒ�
	void CursolControl();
};

