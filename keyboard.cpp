#include "mouse.h"

//�}�N����`
#define NUM_KEY_MAX (256) //�L�[�̍ő吔

//�O���[�o���ϐ��錾
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h�̃v���X���
BYTE g_aOldState[NUM_KEY_MAX];	//�L�[�{�[�h�̌Â��v���X���

//***********************************************
// �L�[�{�[�h�̏���������
//***********************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�𐶐�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//***********************************************
// �L�[�{�[�h�̏I������
//***********************************************
void UninitKeyboard(void)
{
	// ���̓f�o�C�X�L�[�{�[�h�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//***********************************************
// �L�[�{�[�h�̍X�V����
//***********************************************
void UpdataKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏���
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];	// �ЂƂO�̃L�[�{�[�h�v���X����ۑ�
	}

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];	// ���[�ځ[�ǂ̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//***********************************************
// �L�[�{�[�h�������Ă����
//***********************************************
bool GetKeyboardPress(int nKey)//�����Ă��
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//***********************************************
// �L�[�{�[�h���������Ƃ�
//***********************************************
bool KeyboardTrigger(int nKey)//�������Ƃ�
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//***********************************************
// �L�[�{�[�h�𗣂����Ƃ�
//***********************************************
bool KeyboardRelease(int nKey)//��������
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//***********************************************
// �L�[�{�[�h�������Ă����
//***********************************************
bool KeyboardRepeat(int nKey)//������Ă����
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}