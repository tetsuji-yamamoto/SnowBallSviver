#include "guide.h"
#include "camera.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGuide = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
D3DXMATRIX g_mtxWorldGuide;						// ���[���h�}�g���b�N�X
GUIDE g_aGude[OLL_VERTEX];					// �K�C�h�����

//**************************************
// �K�C�h�̏�����
//**************************************
void InitGuide(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * OLL_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGuide, NULL);

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffGuide->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	for (int nCnt = 0; nCnt < OLL_VERTEX; nCnt++)
	{
		g_aGude[nCnt].posguide = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGude[nCnt].rotguide = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGude[nCnt].type = GUDETYPE_MAX;
		g_aGude[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGude[nCnt].bUse = false;

		// ���_���W
		pVtx[nCnt].pos = g_aGude[nCnt].posguide;

		// �@��
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[nCnt].col = g_aGude[nCnt].col;

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	// XZ����
	GUIDE gude;
	gude.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	float fA = (float)GUIDE_LINE_INTERVAL;
	float fAStart = fA * (float)(GUIDE_LINE_X / 2);
	float fB = (float)GUIDE_LINE_INTERVAL * (float)(GUIDE_LINE_X / 2);

	for (int nCnt = 0; nCnt <= GUIDE_LINE_X; nCnt++)
	{
		// �s
		SetGude(gude, D3DXVECTOR3(-fAStart + fA * nCnt, 0.0f, fB), D3DXVECTOR3(-fAStart + fA * nCnt, 0.0f, -fB));

		//��
		SetGude(gude, D3DXVECTOR3(fB, 0.0f, -fAStart + fA * nCnt), D3DXVECTOR3(-fB, 0.0f, -fAStart + fA * nCnt));
	}

	// X��
	gude.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	SetGude(gude, D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(100.0f, 0.0f, 0.0f));

	// Y��
	gude.col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	SetGude(gude, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 100.0f, 0.0f));

	// Z��
	gude.col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	SetGude(gude, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 100.0f));

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffGuide->Unlock();
}

//*********************************************
// �K�C�h�̔j��
//*********************************************
void UninitGuide(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffGuide != NULL)
	{
		g_pVtxBuffGuide->Release();
		g_pVtxBuffGuide = NULL;
	}
}

//*********************************************
// �K�C�h�̔j��
//*********************************************
void UpdateGuide(void)
{

}

//*********************************************
// �K�C�h�̕`��
//*********************************************
void DrawGuide(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCnt = 0; nCnt < OLL_VERTEX; nCnt++)
	{
		if (g_aGude[nCnt].bUse == true)
		{// �g���ă^��
			for (int nCntB = 0; nCntB < 2; nCntB++, nCnt++)
			{
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_mtxWorldGuide);

				// �����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGude[nCnt].rotguide.y, g_aGude[nCnt].rotguide.x, g_aGude[nCnt].rotguide.z);
				D3DXMatrixMultiply(&g_mtxWorldGuide, &g_mtxWorldGuide, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aGude[nCnt].posguide.x, g_aGude[nCnt].posguide.y, g_aGude[nCnt].posguide.z);
				D3DXMatrixMultiply(&g_mtxWorldGuide, &g_mtxWorldGuide, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldGuide);

				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffGuide, 0, sizeof(VERTEX_3D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				// �K�C�h�̕`��
				pDevice->DrawPrimitive(D3DPT_LINESTRIP, nCnt - nCntB, 1);
			}
			nCnt--;
		}

	}
}

//*********************************************
// �K�C�h�̐ݒ�
//*********************************************
void SetGude(GUIDE guide, D3DXVECTOR3 sp, D3DXVECTOR3 ep)
{
	int nCntVtx = 0;

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffGuide->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	for (int nCnt = 0; nCnt < OLL_VERTEX; nCnt++)
	{
		if (g_aGude[nCnt].bUse == false)
		{
			// �n�_
			g_aGude[nCnt].posguide = sp;
			g_aGude[nCnt].col = guide.col;
			g_aGude[nCnt].type = GUDETYPE_START;
			g_aGude[nCnt].bUse = true;

			pVtx[nCnt].pos = g_aGude[nCnt].posguide;
			pVtx[nCnt].col = g_aGude[nCnt].col;

			nCnt++;

			//�I�_
			g_aGude[nCnt].posguide = ep;
			g_aGude[nCnt].col = guide.col;
			g_aGude[nCnt].type = GUDETYPE_END;
			g_aGude[nCnt].bUse = true;

			pVtx[nCnt].pos = g_aGude[nCnt].posguide;
			pVtx[nCnt].col = g_aGude[nCnt].col;
			break;
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffGuide->Unlock();
}