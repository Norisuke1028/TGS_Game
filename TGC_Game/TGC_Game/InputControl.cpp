#include "InputControl.h"
#include "DxLib.h"

// �ÓI�����o�ϐ��̏�����
InputControl* InputControl::instance = nullptr;

// �C���X�^���X���擾
InputControl* InputControl::GetInstance()
{
	if (instance == nullptr)
	{
		// �ŏ���1�񂾂��I�u�W�F�N�g�𐶐�����
		instance = new InputControl();
	}

	// ���̂�Ԃ�
	return instance;
}

// �C���X�^���X�̍폜
void InputControl::DeleteInstance()
{
	if (instance != nullptr)
	{
		// �������̊J��
		delete instance;
		instance = nullptr;
	}
}

void InputControl::Update()
{
	// �Q�[���p�b�h�̏��
	XINPUT_STATE input;

	// �Q�[���p�b�h�̏�Ԃ��擾
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	// �������̈���R�s�[
	memcpy(old_button, now_button, (sizeof(char) * PAD_BUTTON_MAX));
	for (int i = 0; i < PAD_BUTTON_MAX; i++)
	{
		// ���݉����Ă���{�^���̍X�V
		now_button[i] = input.Buttons[i];
	}

	// ���X�e�B�b�N�̍X�V
	left_stick.x = input.ThumbLX;
	left_stick.y = input.ThumbLY;

	// �E�X�e�B�b�N�̍X�V
	right_stick.x = input.ThumbRX;
	right_stick.y = input.ThumbRY;

	// ���g���K�[�̍X�V
	left_trigger = (int)input.LeftTrigger;

	// �E�g���K�[�̍X�V
	right_trigger = (int)input.RightTrigger;
}

// �{�^���̓��͏�Ԃ��擾
ePadInputState InputControl::GetButtonInputState(int button)
{
	// �{�^�����͂��L���Ȕ͈͂������珈�����s��
	if (CheckButtonRange(button))
	{
		if (old_button[button] == TRUE)
		{
			if (now_button[button] == TRUE)
			{
				// ���������Ă���
				return ePadInputState::eHeld;
			}
			else
			{
				// �������u��
				return ePadInputState::eRelease;
			}
		}
		else
		{
			if (now_button[button] == TRUE)
			{
				// �������u��
				return ePadInputState::ePress;
			}
			else
			{
				// ���͖���
				return ePadInputState::eNone;
			}
		}
	}

	return ePadInputState::eNone;
}

// ���X�e�B�b�N�̒l���擾
Vector2D InputControl::GetLeftStick() const
{
	return left_stick;
}

// �E�X�e�B�b�N�̒l���擾
Vector2D InputControl::GetRightStick() const
{
	return right_stick;
}

// ���g���K�[�̒l���擾
int InputControl::GetLeftTrigger() const
{
	return left_trigger;
}

// �E�g���K�[�̒l���擾
int InputControl::GetRightTrigger() const
{
	return right_trigger;
}

// ���X�e�B�b�N�̌X���̊������擾
Vector2D InputControl::GetLeftStickTiltPercentage()
{
	// ���X�e�B�b�N�̌X��
	Vector2D left_stick_tilt;

	// ���X�e�B�b�N�̌X����-1.0f �` 1.0f�̊Ԃɕϊ�
	// x���l�̕ϊ�
	left_stick_tilt.x = left_stick.x / PAD_STICK_MAX;
	if (left_stick_tilt.x < -1.0f)
	{
		left_stick_tilt.x = -1.0f;
	}
	// y���l�̕ϊ�
	left_stick_tilt.y = left_stick.y / PAD_STICK_MAX;
	if (left_stick_tilt.y < -1.0f)
	{
		left_stick_tilt.y = -1.0f;
	}

	return left_stick_tilt;
}

// �E�X�e�B�b�N�̌X���̊������擾
Vector2D InputControl::GetRightStickTiltPercentage()
{
	// �E�X�e�B�b�N�̌X��
	Vector2D right_stick_tilt;

	// �E�X�e�B�b�N�̌X����-1.0f �` 1.0f�̊Ԃɕϊ�
	// x���l�̕ϊ�
	right_stick_tilt.x = right_stick.x / PAD_STICK_MAX;
	if (right_stick_tilt.x < -1.0f)
	{
		right_stick_tilt.x = -1.0f;
	}
	// y���l�̕ϊ�
	right_stick_tilt.y = right_stick.y / PAD_STICK_MAX;
	if (right_stick_tilt.y < -1.0f)
	{
		right_stick_tilt.y = -1.0f;
	}

	return right_stick_tilt;
}

// ���͂��L���Ȕ͈͂��`�F�b�N
bool InputControl::CheckButtonRange(int button)
{
	// ���݂̓��͒l��true��false���Ԃ�
	return (0 <= button && button < PAD_BUTTON_MAX);
}
