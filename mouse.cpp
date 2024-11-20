#include "mouse.h"

// �O���[�o���ϐ��錾
LPDIRECTINPUT8 g_mouseInput;
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;
DIMOUSESTATE g_mouse;			// �}�E�X���
DIMOUSESTATE g_mouseMove;		// �}�E�X�̈ړ��ʏ��
DIMOUSESTATE g_mouseOld;		// �Â��}�E�X���
DIMOUSESTATE g_mouseTrigger;	// �}�E�X�g���K�[���
DIMOUSESTATE g_mouseRelease;	// �}�E�X�����[�X���

//******************************************
// �}�E�X�̏���������
//******************************************
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_mouseInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X(�}�E�X)�̐���
	if (FAILED(g_mouseInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�𐶐�
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�}�E�X�ւ̃A�N�Z�X�����l��
	g_pDevMouse->Acquire();

	return S_OK;
}

//******************************************
// �}�E�X�̏I������
//******************************************
void UninitMouse(void)
{
	//���̓f�o�C�X�L�[�{�[�h�̔j��
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}
	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_mouseInput != NULL)
	{
		g_mouseInput->Release();
		g_mouseInput = NULL;
	}
}

//******************************************
// �}�E�X�̍X�V����
//******************************************
void UpdateMouse(void)
{
	// �Â��}�E�X�����X�V
	g_mouseOld = g_mouse;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_mouse)))
	{
		for (int nCntButn = 0; nCntButn < MOUSEBUTTON_MAX; nCntButn++)
		{
			g_mouseTrigger.rgbButtons[nCntButn] = g_mouse.rgbButtons[nCntButn] & ~g_mouseOld.rgbButtons[nCntButn];
			g_mouseRelease.rgbButtons[nCntButn] = g_mouseOld.rgbButtons[nCntButn] & ~g_mouse.rgbButtons[nCntButn];
		}
	}
	else
	{
		g_pDevMouse->Acquire();// �}�E�X�̃A�N�Z�X�����l��
	}

	// �}�E�X���W���擾����
	POINT p;
	GetCursorPos(&p);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
	if (ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p))
	{
		g_mouse.lX = p.x;
		g_mouse.lY = p.y;

		// �ړ��ʂ��v�Z
		g_mouseMove.lX = g_mouse.lX - g_mouseOld.lX;
		g_mouseMove.lY = g_mouse.lY - g_mouseOld.lY;
	}
}

//******************************************
// �}�E�X�̃{�^���������Ă����
//******************************************
bool MouseButtonRepeat(MOUSEBUTTON mouseButtton)
{
	return g_mouse.rgbButtons[mouseButtton] & (0x80) ? true : false;
}

//******************************************
// �}�E�X�̃{�^�����������u��
//******************************************
bool MouseButtonTrigger(MOUSEBUTTON mouseButtton)
{
	return g_mouseTrigger.rgbButtons[mouseButtton] & (0x80) ? true : false;
}

//******************************************
// �}�E�X�̃{�^���𗣂����u��
//******************************************
bool MouseButtonRelease(MOUSEBUTTON mouseButtton)
{
	return g_mouseRelease.rgbButtons[mouseButtton] & (0x80) ? true : false;
}

//******************************************
// �}�E�X�̈ړ��ʂ��擾
//******************************************
D3DXVECTOR3 GetMouseVelocity(void)
{
	return D3DXVECTOR3((float)g_mouseMove.lX, (float)g_mouseMove.lY, (float)g_mouseMove.lZ);
}

//******************************************
// �}�E�X�̈ʒu���擾
//******************************************
D3DXVECTOR3 GetMousePosition(void)
{
	return D3DXVECTOR3((float)g_mouse.lX, (float)g_mouse.lY, (float)g_mouse.lZ);
}