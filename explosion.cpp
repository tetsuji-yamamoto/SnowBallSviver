#include "explosion.h"
#include "camera.h"
#include "particle.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturExplosion = NULL;		// �e�N�X�`���̃|�C���^
EXPLOSION g_aExplosion[MAX_EXPOLOSION];					// ����

//**************************************
// �����̏�����
//**************************************
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPOLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\billboard\\explosion000.png",
		&g_pVtxTexturExplosion);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EXPOLOSION; nCntEX++)
	{
		g_aExplosion[nCntEX].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_aExplosion[nCntEX].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntEX].bUse = false;

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//*****************************
// �����̔j��
//*****************************
void UninitExplosion(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pVtxTexturExplosion != NULL)
	{
		g_pVtxTexturExplosion->Release();
		g_pVtxTexturExplosion = NULL;
	}
}

//*****************************
// �����̍X�V
//*****************************
void UpdateExplosion(void)
{

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EXPOLOSION; nCntEX++)
	{
		if (g_aExplosion[nCntEX].bUse == true)
		{
			g_aExplosion[nCntEX].nCntTime++;

			if (g_aExplosion[nCntEX].nCntTime >= 5)
			{// �^�C�}�[
				g_aExplosion[nCntEX].nCntTime = 0;
				g_aExplosion[nCntEX].nCntPtn++;

				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.125f * g_aExplosion[nCntEX].nCntPtn, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + 0.125f * g_aExplosion[nCntEX].nCntPtn, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + 0.125f * g_aExplosion[nCntEX].nCntPtn, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f * g_aExplosion[nCntEX].nCntPtn, 1.0f);

				if (g_aExplosion[nCntEX].nCntPtn >= 8)
				{// ������������
					// �e�N�X�`�����W�̐ݒ�
					g_aExplosion[nCntEX].bUse = false;
				}
			}
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//*****************************
// �����̕`��
//*****************************
void DrawExplosion(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	for (int nCntEX = 0; nCntEX < MAX_EXPOLOSION; nCntEX++)
	{
		if (g_aExplosion[nCntEX].bUse == true)
		{// �g���Ă���
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aExplosion[nCntEX].mtxWorld);

			// �r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// �J�����̋t�s���ݒ�
			g_aExplosion[nCntEX].mtxWorld._11 = mtxview._11;
			g_aExplosion[nCntEX].mtxWorld._12 = mtxview._21;
			g_aExplosion[nCntEX].mtxWorld._13 = mtxview._31;
			g_aExplosion[nCntEX].mtxWorld._21 = mtxview._12;
			g_aExplosion[nCntEX].mtxWorld._22 = mtxview._22;
			g_aExplosion[nCntEX].mtxWorld._23 = mtxview._32;
			g_aExplosion[nCntEX].mtxWorld._31 = mtxview._13;
			g_aExplosion[nCntEX].mtxWorld._32 = mtxview._23;
			g_aExplosion[nCntEX].mtxWorld._33 = mtxview._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntEX].pos.x, g_aExplosion[nCntEX].pos.y, g_aExplosion[nCntEX].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntEX].mtxWorld, &g_aExplosion[nCntEX].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntEX].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pVtxTexturExplosion);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �����̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEX, 2);
		}
	}

	// �A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//*****************************
// �����̐ݒ�
//*****************************
void SetExplosion(SETEXPLO setExplo)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EXPOLOSION; nCntEX++)
	{
		if (g_aExplosion[nCntEX].bUse == false)
		{
			g_aExplosion[nCntEX].pos = setExplo.pos;
			g_aExplosion[nCntEX].nCntPtn = 0;
			g_aExplosion[nCntEX].nCntTime = 0;
			g_aExplosion[nCntEX].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = -setExplo.size.x;
			pVtx[0].pos.y = setExplo.size.y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = setExplo.size.x;
			pVtx[1].pos.y = setExplo.size.y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -setExplo.size.x;
			pVtx[2].pos.y = -setExplo.size.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = setExplo.size.x;
			pVtx[3].pos.y = -setExplo.size.y;
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
	g_pVtxBuffExplosion->Unlock();
}