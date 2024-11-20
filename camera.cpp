#include "camera.h"
#include "mouse.h"
#include "keyboard.h"
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
	PLAYER* pPlayer = GetPlayer();	// �v���C���[�擾

	D3DXVECTOR3 MousePos = GetMousePosition();
	D3DXVECTOR3 MouseMove = GetMouseVelocity();

	//�J�����^�C�v�؂�ւ�
	if (KeyboardTrigger(DIK_F1))
	{
		g_camera.nType++;
		if (g_camera.nType >= CAMERATYPE_MAX)
		{
			g_camera.nType = 0;
		}
	}

	switch (g_camera.nType)
	{
	case CAMERATYPE_NOMAL:
		// �����_�̐���
		if (KeyboardRepeat(DIK_Q))
		{
			g_camera.rot.y -= 0.01f;	// ��]��
		}
		else if (KeyboardRepeat(DIK_E))
		{
			g_camera.rot.y += 0.01f;	// ��]��
		}

		// ���_�̉�]
		if (KeyboardRepeat(DIK_Z))
		{
			g_camera.rot.y -= 0.01f;	// ��]��
		}
		else if (KeyboardRepeat(DIK_C))
		{
			g_camera.rot.y += 0.01f;	// ��]��
		}

		if (KeyboardRepeat(DIK_W))
		{//�܂������ړ�
			g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
			g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;
			g_camera.posR.x += sinf(g_camera.rot.y) * 1.0f;
			g_camera.posR.z += cosf(g_camera.rot.y) * 1.0f;
		}
		else if (KeyboardRepeat(DIK_S))
		{//�܂������ړ�
			g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
			g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;
			g_camera.posR.x -= sinf(g_camera.rot.y) * 1.0f;
			g_camera.posR.z -= cosf(g_camera.rot.y) * 1.0f;
		}

		if (KeyboardRepeat(DIK_D))
		{//�E�Ɉړ�
			g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
			g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
			g_camera.posR.x += sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
			g_camera.posR.z += cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
		}
		else if (KeyboardRepeat(DIK_A))
		{//���Ɉړ�
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
			g_camera.posR.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
			g_camera.posR.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
		}

		if (KeyboardRepeat(DIK_2))
		{// �ォ��̂���
			g_camera.posR.y += 1.0f;
		}
		else if (KeyboardRepeat(DIK_X))
		{// ������̂���
			g_camera.posR.y -= 1.0f;
		}

		if (KeyboardRepeat(DIK_UP))
		{// �ォ��̂���
			g_camera.rot.x += 0.01f;
		}
		else if (KeyboardRepeat(DIK_DOWN))
		{// ������̂���
			g_camera.rot.x -= 0.01f;
		}

		if (KeyboardRepeat(DIK_LEFT))
		{// �ォ��̂���
			g_camera.rot.y += 0.01f;
		}
		else if (KeyboardRepeat(DIK_RIGHT))
		{// ������̂���
			g_camera.rot.y -= 0.01f;
		}

		
		
		break;

	case CAMERATYPE_PLAYER:
		// �v���C���[�Ǐ] 

		g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rotDest.y) * (float)PLAYER_MOVE;
		g_camera.posRDest.y;
		g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rotDest.y) * (float)PLAYER_MOVE;

		g_camera.posVDest.x = pPlayer->pos.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posVDest.y;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(g_camera.rot.y) * g_camera.fDistance;

		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.1f;
		g_camera.posR.y;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.1f;

		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;
		g_camera.posV.y;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
		break;

	}

	// �}�E�X����
	if (MouseButtonRepeat(MOUSEBUTTON_LEFT) == true)
	{// ���N�����_����
		g_camera.rot.y += MouseMove.x * 0.01f;	// ��]��
		g_camera.rot.x += MouseMove.y * 0.01f;	// ��]��

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
	else if (MouseButtonRepeat(MOUSEBUTTON_RIGHT) == true)
	{// �E�N�����_����
		g_camera.rot.y += MouseMove.x * 0.01f;	// ��]��
		g_camera.rot.x += MouseMove.y * 0.01f;	// ��]��

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
	else if (MouseButtonRepeat(MOUSEBUTTON_CENTER) == true)
	{// ���{�^��
		g_camera.posV.x += sinf(g_camera.rot.y) * MouseMove.x;
		g_camera.posV.y += cosf(g_camera.rot.x) * MouseMove.y;
		g_camera.posV.z += sinf(g_camera.rot.y) * MouseMove.x;

		g_camera.posR.x += sinf(g_camera.rot.y) * MouseMove.x;
		g_camera.posR.y += cosf(g_camera.rot.x) * MouseMove.y;
		g_camera.posR.z += sinf(g_camera.rot.y) * MouseMove.x;

	}

	if (MousePos.z > 0)
	{//���ɉ񂵂���
		g_camera.fDistance += 10.0f;

		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else if (MousePos.z < 0)
	{//��O�ɉ񂵂���
		g_camera.fDistance -= 10.0f;

		if (g_camera.fDistance <= 5.0f)
		{// �s���߂��Ȃ��悤��
			g_camera.fDistance = 5.0f;
		}

		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
	g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * g_camera.fDistance;
	g_camera.posV.z = g_camera.posR.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

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