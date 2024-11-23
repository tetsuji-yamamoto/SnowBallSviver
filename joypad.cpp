#include "joypad.h"

XINPUT_STATE g_joyKeyState;			// �W���C�p�b�h�̏��
XINPUT_STATE g_JoyKeyStateOld;		// �W���C�p�b�h�̌Â����
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
	g_JoyKeyStateOld = g_joyKeyState;

	// �W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_joyKeyState = joyKeyState;	// �W���C�p�b�h�̃v���X����ۑ�

		// ����n����
		WORD Button = g_joyKeyState.Gamepad.wButtons;		// ��
		WORD OldButton = g_JoyKeyStateOld.Gamepad.wButtons;	// ��

		WORD LT = g_joyKeyState.Gamepad.bLeftTrigger;// ��
		WORD RT = g_joyKeyState.Gamepad.bRightTrigger;// ��
		WORD LTOld = g_JoyKeyStateOld.Gamepad.bLeftTrigger;	// ��
		WORD RTOld = g_JoyKeyStateOld.Gamepad.bRightTrigger;	// ��

		// �v�Z���ʂ���
		g_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;// �������Ƃ�
		g_joyKeyStateRelease.Gamepad.wButtons = OldButton & ~Button;// �������Ƃ�
		g_joyKeyStateRepeat.Gamepad.wButtons = Button;				// �����Ă����

		g_joyKeyStateTrigger.Gamepad.bLeftTrigger = LT & ~LTOld;	// �������Ƃ�
		g_joyKeyStateRelease.Gamepad.bLeftTrigger = LTOld & ~LT;	// �������Ƃ�
		g_joyKeyStateRepeat.Gamepad.bLeftTrigger = LT;				// �����Ă����


		g_joyKeyStateTrigger.Gamepad.bRightTrigger = RT & ~RTOld;	// �������Ƃ�
		g_joyKeyStateRelease.Gamepad.bRightTrigger = RTOld & ~RT;	// �������Ƃ�
		g_joyKeyStateRepeat.Gamepad.bRightTrigger = RT;				// �����Ă����
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
}

//***********************************************
//�W���C�p�b�h�{�^���𗣂����Ƃ�
//***********************************************
bool GetJoypadRelease(JOYKEY key)
{
	return (g_joyKeyStateRelease.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
// �W���C�p�b�h�{�^���������Ă����
//***********************************************
bool GetJoypadRepeat(JOYKEY key)
{
	return (g_joyKeyStateRepeat.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
// LT �������Ƃ�
//***********************************************
bool GetLTTrigger(void)
{
	return (g_joyKeyStateTrigger.Gamepad.bLeftTrigger ? true : false);
}

//***********************************************
// LT �������Ƃ�
//***********************************************
bool GetLTRelease(void)
{
	return (g_joyKeyStateRelease.Gamepad.bLeftTrigger ? true : false);
}

//***********************************************
// LT �����Ă����
//***********************************************
bool GetLTRepeat(void)
{
	return (g_joyKeyStateRepeat.Gamepad.bLeftTrigger ? true : false);
}

//***********************************************
// LR �������Ƃ�
//***********************************************
bool GetRTTrigger(void)
{
	return (g_joyKeyStateTrigger.Gamepad.bRightTrigger ? true : false);
}

//***********************************************
// LR �������Ƃ�
//***********************************************
bool GetRTRelease(void)
{
	return (g_joyKeyStateRelease.Gamepad.bRightTrigger ? true : false);
}

//***********************************************
// LR �����Ă����
//***********************************************
bool GetRTRepeat(void)
{
	return (g_joyKeyStateRepeat.Gamepad.bRightTrigger ? true : false);
}

//********************************************************************
// L�X�e�B�b�N����
//********************************************************************
bool GetJoyStickL(void)
{
	bool joykey = false;
	//�^�񒆂���Ȃ�������
	if (g_joyKeyState.Gamepad.sThumbLX >= 3000 ||
		g_joyKeyState.Gamepad.sThumbLX <= -3000 ||
		g_joyKeyState.Gamepad.sThumbLY >= 3000 ||
		g_joyKeyState.Gamepad.sThumbLY <= -3000)
	{
		joykey = true;
	}
	return joykey;
}

//********************************************************************
// R�X�e�B�b�N����
//********************************************************************
bool GetJoyStickR(void)
{
	bool joykey = false;
	//�^�񒆂���Ȃ�������
	if (g_joyKeyState.Gamepad.sThumbRX >= 3000 ||
		g_joyKeyState.Gamepad.sThumbRX <= -3000 ||
		g_joyKeyState.Gamepad.sThumbRY >= 3000 ||
		g_joyKeyState.Gamepad.sThumbRY <= -3000)
	{
		joykey = true;
	}
	return joykey;
}

//********************************************************************
// �W���C�p�b�h���̎擾
//********************************************************************
XINPUT_STATE* GetJoypadState(void)
{
	return &g_joyKeyState;
}