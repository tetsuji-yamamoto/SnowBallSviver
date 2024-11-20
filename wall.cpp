#include "wall.h"
#include "camera.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturWall = NULL;		// �e�N�X�`���̃|�C���^
WALL g_aWall[MAX_WALL];							// �Ǐ��

//**************************************
// �ǂ̏�����
//**************************************
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\wall\\wall000.jpg",
		&g_pVtxTexturWall);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aWall[nCntWall].size = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aWall[nCntWall].col = D3DXCOLOR(1.0f,1.0f, 1.0f,1.0f);
		g_aWall[nCntWall].bFaB = false;	// �\��(�\)
		g_aWall[nCntWall].bUse = false;

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f;

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();

	// �ǐݒ�
	SetWall(D3DXVECTOR3(0.0f, 50.0f, 150.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 50.0f, 150.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetWall(D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetWall(D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f + D3DX_PI, 0.0f));

	SetWall(D3DXVECTOR3(-150.0f, 50.0f, 0.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	SetWall(D3DXVECTOR3(-150.0f, 50.0f, 0.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f + D3DX_PI, 0.0f));

	SetWall(D3DXVECTOR3(0.0f, 50.0f, -150.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 50.0f, -150.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, D3DX_PI + D3DX_PI, 0.0f));

}

//**************************************
// �ǂ̔j��
//**************************************
void UninitWall(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pVtxTexturWall != NULL)
	{
		g_pVtxTexturWall->Release();
		g_pVtxTexturWall = NULL;
	}
}

//**************************************
// �ǂ̍X�V
//**************************************
void UpdateWall(void)
{
	Camera* pCamera = GetCamera();	// �J�����擾

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//float fAngle = atan2f((g_aWall[nCntWall].pos.x - pCamera->posV.x), (g_aWall[nCntWall].pos.z - pCamera->posV.z));
			//float fDiff = g_aWall[nCntWall].rot.y - fAngle;

			//// ��������
			//if (fDiff > D3DX_PI)
			//{
			//	//fDiff = fDiff - D3DX_PI * 2.0f;
			//}
			//else if (fDiff < -D3DX_PI)
			//{
			//	//fDiff = fDiff + D3DX_PI * 2.0f;
			//}

			//// ������������
			//if (fDiff < -D3DX_PI * 0.5f || fDiff > D3DX_PI * 0.5f)
			//{
			//	g_aWall[nCntWall].rot.y += D3DX_PI;
			//	g_aWall[nCntWall].bFaB = !g_aWall[nCntWall].bFaB;	// �\���؂�ւ���
			//}

			//// �Ë�
			//if (g_aWall[nCntWall].rot.y > D3DX_PI)
			//{
			//	g_aWall[nCntWall].rot.y = -D3DX_PI + (g_aWall[nCntWall].rot.y - D3DX_PI);
			//}
			//else if (g_aWall[nCntWall].rot.y < -D3DX_PI)
			//{
			//	g_aWall[nCntWall].rot.y = D3DX_PI + (g_aWall[nCntWall].rot.y + D3DX_PI);
			//}

			//
			//if (g_aWall[nCntWall].bFaB == true)
			//{// ���������������
			//	//// ���_�J���[�̐ݒ�
			//	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			//	//// �e�N�X�`�����W�̐ݒ�
			//	//pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			//	//pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
			//	//pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
			//	//pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
			//}
			//else if (g_aWall[nCntWall].bFaB == false)
			//{// �\��������
			//	//// ���_�J���[�̐ݒ�
			//	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			//	//// �e�N�X�`�����W�̐ݒ�
			//	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			//	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			//}
		}

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();
}

//**************************************
// �ǂ̕`��
//**************************************
void DrawWall(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pVtxTexturWall);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �ǂ̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntWall, 2);
		}
	}
}

//**************************************
// �ǂ̐ݒ�
//**************************************
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 rot)
{
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].size = size;
			g_aWall[nCntWall].col = col;
			g_aWall[nCntWall].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = -g_aWall[nCntWall].size.x;
			pVtx[0].pos.y = g_aWall[nCntWall].size.y;
			pVtx[0].pos.z = g_aWall[nCntWall].size.z;

			pVtx[1].pos.x = g_aWall[nCntWall].size.x;
			pVtx[1].pos.y = g_aWall[nCntWall].size.y;
			pVtx[1].pos.z = g_aWall[nCntWall].size.z;

			pVtx[2].pos.x = -g_aWall[nCntWall].size.x;
			pVtx[2].pos.y = -g_aWall[nCntWall].size.y;
			pVtx[2].pos.z = -g_aWall[nCntWall].size.z;

			pVtx[3].pos.x = g_aWall[nCntWall].size.x;
			pVtx[3].pos.y = -g_aWall[nCntWall].size.y;
			pVtx[3].pos.z = -g_aWall[nCntWall].size.z;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aWall[nCntWall].col;
			pVtx[1].col = g_aWall[nCntWall].col;
			pVtx[2].col = g_aWall[nCntWall].col;
			pVtx[3].col = g_aWall[nCntWall].col;
			break;
		}

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();
}