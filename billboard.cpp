#include "billboard.h"
#include "camera.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturBillboard = NULL;	// �e�N�X�`���̃|�C���^
Billboard g_aBillboard[MAX_BLBD];								// �r���{�[�h

//**************************************
// �r���{�[�h�̏�����
//**************************************
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BLBD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\billboard\\bullet000.png",
		&g_pVtxTexturBillboard);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BLBD; nCntBl++)
	{
		g_aBillboard[nCntBl].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_aBillboard[nCntBl].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBl].bUse = false;

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = -20.0f;
		pVtx[0].pos.y = 20.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 20.0f;
		pVtx[1].pos.y = 20.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -20.0f;
		pVtx[2].pos.y = -20.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 20.0f;
		pVtx[3].pos.y = -20.0f;
		pVtx[3].pos.z = 0.0f;

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//*****************************
// �r���{�[�h�̔j��
//*****************************
void UninitBillboard(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pVtxTexturBillboard != NULL)
	{
		g_pVtxTexturBillboard->Release();
		g_pVtxTexturBillboard = NULL;
	}
}

//*****************************
// �r���{�[�h�̍X�V
//*****************************
void UpdateBillboard(void)
{

}

//*****************************
// �r���{�[�h�̕`��
//*****************************
void DrawBillboard(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBl = 0; nCntBl < MAX_BLBD; nCntBl++)
	{
		if (g_aBillboard[nCntBl].bUse == true)
		{// �g���Ă���
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBillboard[nCntBl].mtxWorld);

			// �r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// �J�����̋t�s���ݒ�
			g_aBillboard[nCntBl].mtxWorld._11 = mtxview._11;
			g_aBillboard[nCntBl].mtxWorld._12 = mtxview._21;
			g_aBillboard[nCntBl].mtxWorld._13 = mtxview._31;
			g_aBillboard[nCntBl].mtxWorld._21 = mtxview._12;
			g_aBillboard[nCntBl].mtxWorld._22 = mtxview._22;
			g_aBillboard[nCntBl].mtxWorld._23 = mtxview._32;
			g_aBillboard[nCntBl].mtxWorld._31 = mtxview._13;
			g_aBillboard[nCntBl].mtxWorld._32 = mtxview._23;
			g_aBillboard[nCntBl].mtxWorld._33 = mtxview._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBl].pos.x, g_aBillboard[nCntBl].pos.y, g_aBillboard[nCntBl].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCntBl].mtxWorld, &g_aBillboard[nCntBl].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBl].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pVtxTexturBillboard);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �r���{�[�h�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBl, 2);
		}
	}

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//*****************************
// �r���{�[�h�̐ݒ�
//*****************************
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BLBD; nCntBl++)
	{
		if (g_aBillboard[nCntBl].bUse == false)
		{
			g_aBillboard[nCntBl].pos = pos;
			g_aBillboard[nCntBl].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = -size.x;
			pVtx[0].pos.y = size.y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = size.x;
			pVtx[1].pos.y = size.y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -size.x;
			pVtx[2].pos.y = -size.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = size.x;
			pVtx[3].pos.y = -size.y;
			pVtx[3].pos.z = 0.0f;

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBillboard->Unlock();
}