#include "bullet.h"
#include "camera.h"
#include "explosion.h"
#include "effect.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturBullet = NULL;		// �e�N�X�`���̃|�C���^
BULLET g_aBullet[MAX_BULLET];						// �e

//**************************************
// �e�̏�����
//**************************************
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\billboard\\bullet000.png",
		&g_pVtxTexturBullet);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		g_aBullet[nCntBl].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_aBullet[nCntBl].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].bUse = false;

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
	g_pVtxBuffBullet->Unlock();
}

//*****************************
// �e�̔j��
//*****************************
void UninitBullet(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pVtxTexturBullet != NULL)
	{
		g_pVtxTexturBullet->Release();
		g_pVtxTexturBullet = NULL;
	}
}

//*****************************
// �e�̍X�V
//*****************************
void UpdateBullet(void)
{
	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (g_aBullet[nCntBl].bUse == true)
		{

			g_aBullet[nCntBl].pos.x += sinf(g_aBullet[nCntBl].dir.y) * 1.0f;
			g_aBullet[nCntBl].pos.z += cosf(g_aBullet[nCntBl].dir.y) * 1.0f;
			g_aBullet[nCntBl].fLife -= 1.0f;

			if (g_aBullet[nCntBl].fLife <= 0.0f)
			{
				g_aBullet[nCntBl].bUse = false;
				// �����ݒ�
				SETEXPLO setExplo;
				setExplo.pos = g_aBullet[nCntBl].pos;
				setExplo.size = D3DXVECTOR3(20.0f,20.0f,0.0f);

				SetExplosion(setExplo);
			}

			// �G�t�F�N�g�o��
			EFFECT setEffect;
			setEffect.pos = g_aBullet[nCntBl].pos;
			setEffect.col = D3DXCOLOR(1.0f,0.3f,0.3f,1.0f);
			setEffect.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
			setEffect.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			setEffect.dir= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			setEffect.fDffAlph = 0.01f;
			setEffect.fLife = 120.0f;
			setEffect.fsizeDiff = 0.01f;

			SetEffect(setEffect);
		}
	}
}

//*****************************
// �e�̕`��
//*****************************
void DrawBullet(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,254);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (g_aBullet[nCntBl].bUse == true)
		{// �g���Ă���
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCntBl].mtxWorld);

			// �r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// �J�����̋t�s���ݒ�
			g_aBullet[nCntBl].mtxWorld._11 = mtxview._11;
			g_aBullet[nCntBl].mtxWorld._12 = mtxview._21;
			g_aBullet[nCntBl].mtxWorld._13 = mtxview._31;
			g_aBullet[nCntBl].mtxWorld._21 = mtxview._12;
			g_aBullet[nCntBl].mtxWorld._22 = mtxview._22;
			g_aBullet[nCntBl].mtxWorld._23 = mtxview._32;
			g_aBullet[nCntBl].mtxWorld._31 = mtxview._13;
			g_aBullet[nCntBl].mtxWorld._32 = mtxview._23;
			g_aBullet[nCntBl].mtxWorld._33 = mtxview._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBl].pos.x, g_aBullet[nCntBl].pos.y, g_aBullet[nCntBl].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBl].mtxWorld, &g_aBullet[nCntBl].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBl].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pVtxTexturBullet);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBl, 2);
		}
	}

	// �A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//*****************************
// �e�̐ݒ�
//*****************************
void SetBullet(SETBULLET setBlt)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (g_aBullet[nCntBl].bUse == false)
		{
			g_aBullet[nCntBl].pos = setBlt.pos;
			g_aBullet[nCntBl].dir = setBlt.dir;
			g_aBullet[nCntBl].fLife = setBlt.fLife;
			g_aBullet[nCntBl].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = -setBlt.size.x;
			pVtx[0].pos.y = setBlt.size.y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = setBlt.size.x;
			pVtx[1].pos.y = setBlt.size.y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -setBlt.size.x;
			pVtx[2].pos.y = -setBlt.size.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = setBlt.size.x;
			pVtx[3].pos.y = -setBlt.size.y;
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
	g_pVtxBuffBullet->Unlock();
}