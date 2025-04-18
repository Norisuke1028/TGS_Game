#pragma once
#include "Vector2D.h"

#define		PAD_BUTTON_MAX	(16)						// �Q�[���p�b�h�̃{�^���̍ő吔
#define		PAD_STICK_MAX	(32767.0f)					// �X�e�B�b�N���X�����Ƃ��̍ő�l

enum class ePadInputState : unsigned char
{
	eNone,					// ���͖���
	ePress,					// �{�^�����������u��
	eRelease,				// �{�^���𗣂����u��
	eHeld,					// �{�^�������������Ă���
};

class InputControl
{
private:
	static InputControl* instance;

	unsigned char now_button[PAD_BUTTON_MAX] = {};		// ���݂̃{�^���̓���
	unsigned char old_button[PAD_BUTTON_MAX] = {};		// �O��̃{�^���̓���

	Vector2D left_stick = 0.0f;							// ���X�e�B�b�N
	Vector2D right_stick = 0.0f;						// �E�X�e�B�b�N

	int left_trigger = 0;								// ���g���K�[
	int right_trigger = 0;								// �E�g���K�[

private:
	// ���̂Ƃ��납��I�u�W�F�N�g���ł��Ȃ��悤�ɃR���X�g���N�^��private
	InputControl() = default;
	// �R�s�[�K�[�h
	// �R�s�[�R���X�g���N�^�̍폜
	InputControl(const InputControl&) = delete;
	// �R�s�[������Z�q�̍폜
	InputControl& operator = (const InputControl&) = delete;

public:
	~InputControl() = default;

public:
	// �C���X�^���X���擾
	static InputControl* GetInstance();
	// �C���X�^���X�̍폜
	static void DeleteInstance();

public:
	void Update();

public:
	// �{�^���̓��͏�Ԃ��擾
	ePadInputState GetButtonInputState(int button);

	// ���X�e�B�b�N�̒l���擾
	Vector2D GetLeftStick() const;
	// �E�X�e�B�b�N�̒l���擾
	Vector2D GetRightStick() const;

	// ���g���K�[�̒l���擾
	int GetLeftTrigger() const;
	// �E�g���K�[�̒l���擾
	int GetRightTrigger() const;

	// ���X�e�B�b�N�̌X���̊������擾
	Vector2D GetLeftStickTiltPercentage();
	// �E�X�e�B�b�N�̌X���̊������擾
	Vector2D GetRightStickTiltPercentage();

private:
	// ���͂��L���Ȕ͈͂��`�F�b�N
	bool CheckButtonRange(int button);

};

