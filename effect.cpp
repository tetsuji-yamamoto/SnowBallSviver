#include "effect.h"
#include "camera.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturEffect = NULL;		// �e�N�X�`���̃|�C���^
EFFECT g_aEffect[MAX_EFFECT];						// �G�t�F�N�g

//**************************************
// �G�t�F�N�g�̏�����
//**************************************
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\shadow\\shadow000.jpg",
		&g_pVtxTexturEffect);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EFFECT; nCntEX++)
	{
		g_aEffect[nCntEX].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEX].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEX].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEX].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEX].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEX].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aEffect[nCntEX].fLife = 0.0f;
		g_aEffect[nCntEX].fsizeDiff = 0.0f;
		g_aEffect[nCntEX].bUse = false;

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
	g_pVtxBuffEffect->Unlock();
}

//*****************************
// �G�t�F�N�g�̔j��
//*****************************
void UninitEffect(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pVtxTexturEffect != NULL)
	{
		g_pVtxTexturEffect->Release();
		g_pVtxTexturEffect = NULL;
	}
}

//*****************************
// �G�t�F�N�g�̍X�V
//*****************************
void UpdateEffect(void)
{

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EFFECT; nCntEX++)
	{
		if (g_aEffect[nCntEX].bUse == true)
		{
			g_aEffect[nCntEX].fLife -= 1.0f;
			
			g_aEffect[nCntEX].col.a -= g_aEffect[nCntEX].fDffAlph;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x -= -g_aEffect[nCntEX].fsizeDiff;
			pVtx[0].pos.y -= g_aEffect[nCntEX].fsizeDiff;
			pVtx[0].pos.z -= 0.0f;

			pVtx[1].pos.x -= g_aEffect[nCntEX].fsizeDiff;
			pVtx[1].pos.y -= g_aEffect[nCntEX].fsizeDiff;
			pVtx[1].pos.z -= 0.0f;

			pVtx[2].pos.x -= -g_aEffect[nCntEX].fsizeDiff;
			pVtx[2].pos.y -= -g_aEffect[nCntEX].fsizeDiff;
			pVtx[2].pos.z -= 0.0f;

			pVtx[3].pos.x -= g_aEffect[nCntEX].fsizeDiff;
			pVtx[3].pos.y -= -g_aEffect[nCntEX].fsizeDiff;
			pVtx[3].pos.z -= 0.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCntEX].col;
			pVtx[1].col = g_aEffect[nCntEX].col;
			pVtx[2].col = g_aEffect[nCntEX].col;
			pVtx[3].col = g_aEffect[nCntEX].col;

			if (g_aEffect[nCntEX].fLife <= 0.0f)
			{
				g_aEffect[nCntEX].bUse = false;
			}
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//*****************************
// �G�t�F�N�g�̕`��
//*****************************
void DrawEffect(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Z�̔�r���@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	for (int nCntEX = 0; nCntEX < MAX_EFFECT; nCntEX++)
	{
		if (g_aEffect[nCntEX].bUse == true)
		{// �g���Ă���
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEX].mtxWorld);

			// �r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// �J�����̋t�s���ݒ�
			g_aEffect[nCntEX].mtxWorld._11 = mtxview._11;
			g_aEffect[nCntEX].mtxWorld._12 = mtxview._21;
			g_aEffect[nCntEX].mtxWorld._13 = mtxview._31;
			g_aEffect[nCntEX].mtxWorld._21 = mtxview._12;
			g_aEffect[nCntEX].mtxWorld._22 = mtxview._22;
			g_aEffect[nCntEX].mtxWorld._23 = mtxview._32;
			g_aEffect[nCntEX].mtxWorld._31 = mtxview._13;
			g_aEffect[nCntEX].mtxWorld._32 = mtxview._23;
			g_aEffect[nCntEX].mtxWorld._33 = mtxview._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEX].pos.x, g_aEffect[nCntEX].pos.y, g_aEffect[nCntEX].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEX].mtxWorld, &g_aEffect[nCntEX].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEX].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pVtxTexturEffect);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �G�t�F�N�g�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEX, 2);
		}
	}

	// �A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z�̔�r���@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************************
// �G�t�F�N�g�̐ݒ�
//*****************************
void SetEffect(EFFECT effect)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EFFECT; nCntEX++)
	{
		if (g_aEffect[nCntEX].bUse == false)
		{
			
			g_aEffect[nCntEX] = effect;
			g_aEffect[nCntEX].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = -effect.size.x;
			pVtx[0].pos.y = effect.size.y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = effect.size.x;
			pVtx[1].pos.y = effect.size.y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -effect.size.x;
			pVtx[2].pos.y = -effect.size.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = effect.size.x;
			pVtx[3].pos.y = -effect.size.y;
			pVtx[3].pos.z = 0.0f;

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCntEX].col;
			pVtx[1].col = g_aEffect[nCntEX].col;
			pVtx[2].col = g_aEffect[nCntEX].col;
			pVtx[3].col = g_aEffect[nCntEX].col;

			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}