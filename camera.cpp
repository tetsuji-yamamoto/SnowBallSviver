#include "camera.h"
#include "mouse.h"
#include "keyboard.h"
#include "joypad.h"
#include "player.h"
#include "mouse.h"

// �O���[�o���ϐ��錾
Camera g_camera;	// �J�������

//*****************************************
// �J�����̏�����
//*****************************************
void InitCamera(void)
{
	// ���_�E�����_�E�������ݒ肷��
	g_camera.posV = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// �Œ�
	g_camera.rot = D3DXVECTOR3(-D3DX_PI * 0.2f, 0.0f, 0.0f);

	g_camera.posVDest = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = 500.0f;	// ���_���璍���_�̋���

	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
	g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * g_camera.fDistance;
	g_camera.posV.z = g_camera.posR.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

	g_camera.nType = CAMERATYPE_NOMAL;
}

//*****************************************
// �J�����̏I������
//*****************************************
void UninitCamera(void)
{

}

//*****************************************
// �J�����̍X�V
//*****************************************
void UpdateCamera(void)
{
	PLAYER* pPlayer = GetPlayer();				// �v���C���[�擾
	XINPUT_STATE* pJoypad = GetJoypadState();	// �W���C�p�b�h���擾

	D3DXVECTOR3 MousePos = GetMousePosition();
	D3DXVECTOR3 MouseMove = GetMouseVelocity();

	bool bVR = true;// true���Ǝn�_����
	//�J�����^�C�v�؂�ւ�
	if (KeyboardTrigger(DIK_F1))
	{
		g_camera.nType++;
		if (g_camera.nType >= CAMERATYPE_MAX)
		{
			g_camera.nType = 0;
		}

		switch (g_camera.nType)
		{

		case CAMERATYPE_PLAYER:
			g_camera.fDistance = 160.0f;
			break;

		}

	}

	switch (g_camera.nType)
	{

	case CAMERATYPE_PLAYER:
		// �v���C���[�Ǐ] 

		g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rotDest.y) * (float)PLAYER_MOVE;
		g_camera.posRDest.y;
		g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rotDest.y) * (float)PLAYER_MOVE;

		g_camera.posVDest.x = pPlayer->pos.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posVDest.y;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(g_camera.rot.y) * g_camera.fDistance;

		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.1f;
		g_camera.posR.y = pPlayer->pos.y + 50;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.1f;

		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;
		g_camera.posV.y = pPlayer->pos.y + 50;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
		break;

	}
	// �L�[�{�[�h����
	
	if (KeyboardRepeat(DIK_RSHIFT))
	{
		if (KeyboardRepeat(DIK_RIGHT))
		{//�E��Ɉړ�
			g_camera.rot.y -= 0.01f;	// ��]��
		}
		else if (KeyboardRepeat(DIK_LEFT))
		{//����Ɉړ�
			g_camera.rot.y += 0.01f;	// ��]��
		}
		else if (KeyboardRepeat(DIK_UP))
		{
			bVR = false;
			g_camera.rot.y -= 0.01f;	// ��]��
		}
		else if (KeyboardRepeat(DIK_DOWN))
		{
			bVR = false;
			g_camera.rot.y += 0.01f;	// ��]��
		}
	}
	else if (KeyboardRepeat(DIK_UP))
	{//�܂������ړ�
		if (KeyboardRepeat(DIK_RIGHT))
		{//�E��Ɉړ�
			g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
			g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
			g_camera.posR.x += sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
			g_camera.posR.z += cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
		}
		else if (KeyboardRepeat(DIK_LEFT))
		{//����Ɉړ�
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
			g_camera.posR.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
			g_camera.posR.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
		}
		else
		{
			g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
			g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;
			g_camera.posR.x += sinf(g_camera.rot.y) * 1.0f;
			g_camera.posR.z += cosf(g_camera.rot.y) * 1.0f;
		}
	}
	else if (KeyboardRepeat(DIK_DOWN))
	{//���Ɉړ�
		if (KeyboardRepeat(DIK_RIGHT))
		{//�E�Ɉړ�
			g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
			g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
			g_camera.posR.x += sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
			g_camera.posR.z += cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
		}
		else if (KeyboardRepeat(DIK_LEFT))
		{//���Ɉړ�
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
			g_camera.posR.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
			g_camera.posR.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
		}
		else
		{
			g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
			g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;
			g_camera.posR.x -= sinf(g_camera.rot.y) * 1.0f;
			g_camera.posR.z -= cosf(g_camera.rot.y) * 1.0f;
		}
	}
	else if (KeyboardRepeat(DIK_RIGHT))
	{//�E�Ɉړ�
		g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
		g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
		g_camera.posR.x += sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
		g_camera.posR.z += cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
	}
	else if (KeyboardRepeat(DIK_LEFT))
	{//���Ɉړ�
		g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
		g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
		g_camera.posR.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
		g_camera.posR.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
	}

	// �}�E�X����
	if (MouseButtonRepeat(MOUSEBUTTON_LEFT) == true)
	{// ���N�����_����
		g_camera.rot.y += MouseMove.x * 0.01f;	// ��]��
		g_camera.rot.x += MouseMove.y * 0.01f;	// ��]��
	}
	else if (MouseButtonRepeat(MOUSEBUTTON_RIGHT) == true)
	{// �E�N�����_����
		g_camera.rot.y += MouseMove.x * 0.01f;	// ��]��
		g_camera.rot.x += MouseMove.y * 0.01f;	// ��]��
		bVR = false;
	}
	else if (MouseButtonRepeat(MOUSEBUTTON_CENTER) == true)
	{// ���{�^��
	
	}

	if (MousePos.z > 0)
	{//���ɉ񂵂���
		g_camera.fDistance += 10.0f;
	}
	else if (MousePos.z < 0)
	{//��O�ɉ񂵂���
		g_camera.fDistance -= 10.0f;

		if (g_camera.fDistance <= 5.0f)
		{// �s���߂��Ȃ��悤��
			g_camera.fDistance = 5.0f;
		}
	}

	// �R���g���[���[
	if (GetJoyStickR())
	{// 32468
		float fJoyAngleX = ((float)pJoypad->Gamepad.sThumbRX / (float)32468);
		float fJoyAngleY = ((float)pJoypad->Gamepad.sThumbRY / (float)32468);
		float fAngleX = D3DX_PI * fJoyAngleX;
		float fAngleY = D3DX_PI * fJoyAngleY;
		g_camera.rot.y += fAngleX * 0.02f;
		g_camera.rot.x -= fAngleY * 0.02f;
	}

	if (bVR == true)
	{// ���_����
		// �p�x�̌��E�l
		if (g_camera.rot.x < -D3DX_PI * 0.9f)
		{
			g_camera.rot.x = -D3DX_PI * 0.9f;
		}
		else 	if (g_camera.rot.x > -D3DX_PI * 0.1f)
		{
			g_camera.rot.x = -D3DX_PI * 0.1f;
		}

		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else
	{// �����_����
		// �p�x�̌��E�n
		if (g_camera.rot.x < -D3DX_PI * 0.9f)
		{
			g_camera.rot.x = -D3DX_PI * 0.9f;
		}
		else 	if (g_camera.rot.x > -D3DX_PI * 0.1f)
		{
			g_camera.rot.x = -D3DX_PI * 0.1f;
		}

		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.y = g_camera.posV.y - cosf(g_camera.rot.x) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z - sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y = -D3DX_PI + (g_camera.rot.y - D3DX_PI);
	}
	else if(g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y = D3DX_PI + (g_camera.rot.y + D3DX_PI);
	}

	if (g_camera.rot.x > D3DX_PI)
	{
		g_camera.rot.x = -D3DX_PI + (g_camera.rot.x - D3DX_PI);
	}
	else if (g_camera.rot.x < -D3DX_PI)
	{
		g_camera.rot.x = D3DX_PI + (g_camera.rot.x + D3DX_PI);
	}
	
}

//*****************************************
// �J�����̐ݒ�
//*****************************************
void SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�b�N�X�̏�����
	D3DXMatrixIsIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,&g_camera.posV,&g_camera.posR,&g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	// �v���W�F�N�g�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//*****************************************
// �J�����̎擾
//*****************************************
Camera* GetCamera(void)
{
	return &g_camera;
}