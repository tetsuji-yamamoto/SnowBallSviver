#include "joypad.h"

XINPUT_STATE g_joyKeyState;			// �W���C�p�b�h�̃v���X���
XINPUT_STATE g_aOldJoyKeyState;		// �W���C�p�b�h�̌Â��v���X���
XINPUT_STATE g_joyKeyStateTrigger;	// �W���C�p�b�h�̃g���K�[���
XINPUT_STATE g_joyKeyStateRepeat;	// �W���C�p�b�h�̃��s�[�g���
XINPUT_STATE g_joyKeyStateRelease;	// �W���C�p�b�h�̃����[�X���

//***********************************************
// �W���C�p�b�h�̏���������
//***********************************************
HRESULT InitJoypad(void)
{
	// �������̃N���A
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	// Xinput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//***********************************************
//�W���C�p�b�h�̏I������
//***********************************************
void UninitJoypad(void)
{
	// Xinput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

//***********************************************
// �W���C�p�b�h�̍X�V����
//***********************************************
void UpdataJoypad(void)
{
	int nCntJoy;

	XINPUT_STATE joyKeyState;	// �W���C�p�b�h�̓��͏���

	// �ЂƂO�̃L�[�{�[�h�v���X����ۑ�
	g_aOldJoyKeyState = g_joyKeyState;

	// �W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_joyKeyState = joyKeyState;	// �W���C�p�b�h�̃v���X����ۑ�

		// ����n����
		WORD Button = g_joyKeyState.Gamepad.wButtons;
		WORD OldButton = g_aOldJoyKeyState.Gamepad.wButtons;

		// �v�Z���ʂ���
		g_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;
		g_joyKeyStateRelease.Gamepad.wButtons = OldButton & ~Button;
		g_joyKeyStateRepeat.Gamepad.wButtons = Button;
	}
}

//***********************************************
//�W���C�p�b�h�{�^���������Ă���Ƃ�
//***********************************************
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
//�W���C�p�b�h�{�^�����������u��
//***********************************************
bool GetJoypadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;

	//return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
//�W���C�p�b�h�{�^���𗣂����Ƃ�
//***********************************************
bool GetJoypadRelease(JOYKEY key)
{
	return (g_joyKeyStateRelease.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
//�W���C�p�b�h�{�^���������Ă����
//***********************************************
bool GetJoypadRepeat(JOYKEY key)
{
	return (g_joyKeyStateRepeat.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
//L2,R2����
//***********************************************
bool GetJoyTrigger(JOYKEY key)
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		return (g_joyKeyState.Gamepad.bLeftTrigger) ? true : false;
	}
	else if (key == JOYKEY_R2)
	{
		return (g_joyKeyState.Gamepad.bRightTrigger) ? true : false;
	}
	return JoyStick;

}
bool GetJoyTriggerTrigger(JOYKEY key)//�������Ƃ�
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		if ((g_joyKeyState.Gamepad.bLeftTrigger > 0) && !(g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_R2)
	{
		if ((g_joyKeyState.Gamepad.bRightTrigger > 0) && !(g_aOldJoyKeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}
bool GetJoyTriggerRelease(JOYKEY key)//�������Ƃ�
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0) && !(g_joyKeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_R2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bRightTrigger > 0) && !(g_joyKeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}
bool GetJoyTriggerRepeat(JOYKEY key)//�����Ă����
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0) && (g_joyKeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_R2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bRightTrigger > 0) && (g_joyKeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}

//------------------------
//�X�e�B�b�N����
//------------------------
bool GetJoyStickL()
{
	bool joykey = false;
	//�^�񒆂���Ȃ�������
	if (g_joyKeyState.Gamepad.sThumbLX >= 2000 ||
		g_joyKeyState.Gamepad.sThumbLX <= -2000 ||
		g_joyKeyState.Gamepad.sThumbLY >= 2000 ||
		g_joyKeyState.Gamepad.sThumbLY <= -2000)
	{
		joykey = true;
	}
	return joykey;
}

//------------------------
//�X�e�B�b�N���̎擾
//------------------------
XINPUT_STATE* GetJoySticAngle(void)
{
	return &g_joyKeyState;
}