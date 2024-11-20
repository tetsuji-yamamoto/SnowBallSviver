#include "meshfield.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturMeshField = NULL;	// �e�N�X�`���̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	// �C���f�b�N�X�ւ̃|�C���^
D3DXVECTOR3 g_posMeshField;							// �ʒu
D3DXVECTOR3 g_rotMeshField;							// ����
D3DXMATRIX g_mtxWorldMeshField;						// ���[���h�}�g���b�N�X

//**************************************
// ���b�V���t�B�[���h�̏�����
//**************************************
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESH_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\test\\image.jpg",
		&g_pVtxTexturMeshField);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESH_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	int a = MESH_PLYGON_AII;
	int b = MESH_VERTEX;
	int c = MESH_INDEX;

	float fX = (float)FIELD_X / (float)MESH_X;
	float fZ = (float)FIELD_Z / (float)MESH_Z;

	float fposX = 0.0f;
	float fposZ = 0.0f;

	float fTexX = 1.0f / (float)MESH_X;
	float fTexY = 1.0f / (float)MESH_Z;

	int nCnt = 0;
	int nIndex = 0;
	int nCntVtx = 0;

	D3DXVECTOR3 aaa[MESH_VERTEX] = {};
	D3DXVECTOR2 ccc[MESH_VERTEX] = {};
	int bbb[MESH_VERTEX] = {};

	for (int nCntZ = 0; nCntZ <= MESH_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= MESH_X; nCntX++)
		{
			fposX = fX * nCntX;
			fposZ = -fZ * nCntZ;

			aaa[nCntVtx].x = fposX;
			aaa[nCntVtx].z = fposZ;

			bbb[nCntVtx] = nCntVtx;

			ccc[nCntVtx].x = fTexX * nCntX;
			ccc[nCntVtx].y = fTexY * nCntZ;

			// ���_���W�̐ݒ�
			pVtx[nCntVtx].pos.x = fposX;
			pVtx[nCntVtx].pos.z = fposZ;

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nCntVtx].tex.x = fTexX * nCntX;
			pVtx[nCntVtx].tex.y = fTexY * nCntZ;

			nCntVtx++;
		}
	}

	int i = 0;

	//for (int nCnt = 0; nCnt < MESH_X + 1; nCnt++)
	//{
	//	for (int nCntX = 0; nCntX < MESH_X + 1; nCntX++)
	//	{
	//		fposX = -fX + fX * nCnt;
	//		fTexX = 0.0f + fColX * nCnt;
	//		nIndex = nCntX * (MESH_Z + 1) + 1 * nCnt;

	//		// ���_���W�̐ݒ�
	//		pVtx[nIndex].pos.x = fposX;

	//		// �e�N�X�`�����W�̐ݒ�
	//		pVtx[nIndex].tex.x = fTexX;
	//	}
	//}

	//for (int nCnt = 0; nCnt < MESH_Z + 1; nCnt++)
	//{
	//	for (int nCntZ = 0; nCntZ < MESH_Z + 1; nCntZ++)
	//	{
	//		fposZ = fX - fX * nCnt;
	//		fTexY = 0.0f + fColZ * nCnt;
	//		nIndex = nCntZ + (MESH_Z + 1) * nCnt;

	//		// ���_���W�̐ݒ�
	//		pVtx[nIndex].pos.z = fposZ;

	//		// �e�N�X�`�����W�̐ݒ�
	//		pVtx[nIndex].tex.y = fTexY;
	//	}
	//}

	//for (int nCnt = 0; nCnt < MESH_VERTEX; nCnt++)
	//{
	//	// ���_���W�̐ݒ�
	//	pVtx[nCnt].pos.y = 0.0f;

	//	// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	//	pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//	// ���_�J���[�̐ݒ�
	//	pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//}
		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		//pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	
		// ���_�J���[�̐ݒ�
		//pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		// �e�N�X�`�����W�̐ݒ�
		//pVtx[nCnt].tex = D3DXVECTOR2(0.0f, 0.0f);

	//// ���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
	//pVtx[2].pos = D3DXVECTOR3(150.0f, 0.0f, 150.0f);
	//pVtx[3].pos = D3DXVECTOR3(-150.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	//pVtx[8].pos = D3DXVECTOR3(150.0f, 0.0f, -150.0f);w

	//// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	//pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//// ���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// �e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	//pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshField->Unlock();

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffMeshField->Lock(0,0,(void**)&pIdx,0);

	int naIdxB[MESH_INDEX];// �C���f�b�N�X�i�[�p

	int nVtx = 0;
	int nIdxA = MESH_X + 1;	// �����C���f�b�N�X
	int nIdxB = 0;		// �E���C���f�b�N�X

	for (int nCntA = 0; nCntA < MESH_Z; nCntA++)
	{
		for (int nCntB = 0; nCntB <= MESH_X; nCntB++)
		{
			pIdx[nVtx] = nIdxA;
			nVtx++;
			pIdx[nVtx] = nIdxB;
			nVtx++;
			nIdxA++;
			nIdxB++;
		}
		pIdx[nVtx] = nIdxB - 1;
		nVtx++;
		pIdx[nVtx] = nIdxA;
		nVtx++;

	}

	int z = 0;
	int nCntNum = 0;
	int nCntIdx = 0;

	//// �E���C���f�b�N�X
	//for (nCnt = 0; nCnt < MESH_INDEX / 2; nCnt++)
	//{
	//		nCntNum++;

	//	if (nCntNum > MESH_X + 1)
	//	{
	//		naIdxB[nCnt] = nCnt + MESH_X + 1;
	//		nCntNum = 0;
	//	}
	//	else
	//	{
	//		naIdxB[nCnt] = nCntIdx;
	//		nCntIdx++;
	//	}
	//	// �����i�Ԃ�����
	//	pIdx[nCnt + nCnt + 1] = naIdxB[nCnt];
	//}

	//nCntNum = 0;
	//nCntIdx = MESH_X + 1;

	//// �����C���f�b�N�X
	//for (nCnt = 0; nCnt < MESH_INDEX / 2; nCnt++)
	//{
	//	nCntNum++;

	//	if (nCntNum > MESH_X + 1)
	//	{
	//		naIdxB[nCnt] = nCntIdx - (MESH_X + 2);
	//		nCntNum = 0;
	//	}
	//	else
	//	{
	//		naIdxB[nCnt] = nCntIdx;
	//		nCntIdx++;
	//	}

	//	// �C���f�b�N�X�̐ݒ�
	//	pIdx[nCnt + nCnt] = naIdxB[nCnt];
	//}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshField->Unlock();
}

//*******************************************
// ���b�V���t�B�[���h�̔j��
//*******************************************
void UninitMeshField(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pVtxTexturMeshField != NULL)
	{
		g_pVtxTexturMeshField->Release();
		g_pVtxTexturMeshField = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//*******************************************
// ���b�V���t�B�[���h�̔j��
//*******************************************
void UpdateMeshField(void)
{

}

//*******************************************
// ���b�V���t�B�[���h�̕`��
//*******************************************
void DrawMeshField(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pVtxTexturMeshField);
	
	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,MESH_VERTEX,0,MESH_PLYGON_AII);
}