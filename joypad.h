#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "main.h"



//�L�[�̎��
typedef enum
{
	JOYKEY_UP = 0,			//�\���L�[��
	JOYKEY_DOWN,			//�\���L�[��
	JOYKEY_LEFT,			//�\���L�[��
	JOYKEY_RIGHT,			//�\���L�[�E
	JOYKEY_START,			//�X�^�[�g�{�^��
	JOYKEY_BACK,			//�o�b�N�{�^��
	JOYKEY_LSTICK_BUTTON,	//L�X�e�B�b�N�{�^��
	JOYKEY_RSTICK_BUTTON,	//R�X�e�B�b�N�{�^��
	JOYKEY_L1,				//L1�{�^��
	JOYKEY_R1,				//R1�{�^��
	JOYKEY_L2,				//L2�g���K�[
	JOYKEY_R2,				//R2�g���K�[
	JOYKEY_A,				//A�{�^��
	JOYKEY_B,				//B�{�^��
	JOYKEY_X,				//X�{�^��
	JOYKEY_Y,				//Y�{�^��
	JOYKEY_MAX
}JOYKEY;

HRESULT InitJoypad(void);
void UpdataJoypad(void);
void UninitJoypad(void);

//�{�^��
bool GetJoypadPress(JOYKEY key);	//�����Ă���Ƃ�
bool GetJoypadTrigger(JOYKEY key);	//�������u��
bool GetJoypadRelease(JOYKEY key);	//�������Ƃ�
bool GetJoypadRepeat(JOYKEY key);	//�����Ă����

//LTRT
bool GetLTTrigger(void);	//�������Ƃ�
bool GetLTRelease(void);	//�������Ƃ�
bool GetLTRepeat(void);		//�����Ă����
bool GetRTTrigger(void);	//�������Ƃ�
bool GetRTRelease(void);	//�������Ƃ�
bool GetRTRepeat(void);		//�����Ă����


//�X�e�B�b�N
bool GetJoyStickL(void);
bool GetJoyStickR(void);
XINPUT_STATE* GetJoypadState(void);

#endif // !_JOYPAD_H_