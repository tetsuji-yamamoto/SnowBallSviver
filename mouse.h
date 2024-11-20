#ifndef _MOUSE_H
#define _MOUSE_H

#include "main.h"

// �}�E�X�{�^���̎�ޗ�
typedef enum
{
	MOUSEBUTTON_LEFT = 0,	// ���N���b�N
	MOUSEBUTTON_RIGHT,		// �͋[�N���b�N
	MOUSEBUTTON_CENTER,		// �z�C�[���{�^��
	MOUSEBUTTON_MAX
}MOUSEBUTTON;

//�v���g�^�C�v�錾
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UpdateMouse(void);
void UninitMouse(void);
bool MouseButtonRepeat(MOUSEBUTTON mouseButtton);
bool MouseButtonTrigger(MOUSEBUTTON mouseButtton);
bool MouseButtonRelease(MOUSEBUTTON mouseButtton);
D3DXVECTOR3 GetMouseVelocity(void);
D3DXVECTOR3 GetMousePosition(void);
#endif // !_MOUSE_H