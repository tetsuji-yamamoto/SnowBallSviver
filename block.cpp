#include "block.h"

// �O���[�o���ϐ��錾
BLOCK g_aBlock[MAX_BLOCK];			// �u���b�N���
BLOCKMANAGER g_blockManager;			// �u���b�N�Ǘ�
//********************************************
//�u���b�N�̏�����
//********************************************
void InitBlock(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_blockManager.nBlockNum = 0;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// �e��ϐ��̏�����
		g_aBlock[nCntBlock].apTextureBlock[0] = {};
		g_aBlock[nCntBlock].pMeshBlock = NULL;
		g_aBlock[nCntBlock].pBuffMatBlock = NULL;
		g_aBlock[nCntBlock].dwNumMatBlock = 0;
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f ,0.0f, 0.0f);
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].pFilename = NULL;
		g_aBlock[nCntBlock].nType = BLOCKTYPE_MAX;
		g_aBlock[nCntBlock].bUse = false;
	}
}

//********************************************
// �u���b�N�̏I������
//********************************************
void UninitBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// ���b�V���̔j��
		if (g_aBlock[nCntBlock].pMeshBlock != NULL)
		{
			g_aBlock[nCntBlock].pMeshBlock->Release();
			g_aBlock[nCntBlock].pMeshBlock = NULL;
		}

		// �}�e���A���̔j��
		if (g_aBlock[nCntBlock].pBuffMatBlock != NULL)
		{
			g_aBlock[nCntBlock].pBuffMatBlock->Release();
			g_aBlock[nCntBlock].pBuffMatBlock = NULL;
		}

		//���b�V���̔j��
		if (g_aBlock[nCntBlock].pMeshBlock != NULL)
		{
			g_aBlock[nCntBlock].pMeshBlock->Release();
			g_aBlock[nCntBlock].pMeshBlock = NULL;
		}
	}
}

//********************************************
// �u���b�N�̍X�V
//********************************************
void UpdateBlock(void)
{

}

//********************************************
// �u���b�N�̕`��
//********************************************
void DrawBlock(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{// �g���Ă�����

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBlock[nCntBlock].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBlock[nCntBlock].rot.y, g_aBlock[nCntBlock].rot.x, g_aBlock[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBlock[nCntBlock].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].pBuffMatBlock->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].dwNumMatBlock; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat->MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_aBlock[nCntBlock].apTextureBlock[nCntMat]);

				// �u���b�N(�p�[�c�̕`��)
				g_aBlock[nCntBlock].pMeshBlock->DrawSubset(nCntMat);
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//********************************************
// �u���b�N�̐ݒ�
//********************************************
void SetBlock(SETBLOCK setBlock)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{// �g���ĂȂ�������
			// �ϐ��̐ݒ�
			g_aBlock[nCntBlock].pos = setBlock.pos;
			g_aBlock[nCntBlock].rot = setBlock.rot;
			g_aBlock[nCntBlock].nType = setBlock.nType;
			g_aBlock[nCntBlock].pFilename = &setBlock.astr[0];
			g_aBlock[nCntBlock].bUse = true;

			for (int nCnt = 0; nCnt < 256; nCnt++)
			{
				g_aBlock[nCntBlock].astr[nCnt] = setBlock.astr[nCnt];
				if (setBlock.astr[nCnt] == '\n')
				{
					break;
				}
			}
			g_blockManager.nBlockNum++;	// �u���b�N�J�E���g

			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(g_aBlock[nCntBlock].pFilename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aBlock[nCntBlock].pBuffMatBlock,
				NULL,
				&g_aBlock[nCntBlock].dwNumMatBlock,
				&g_aBlock[nCntBlock].pMeshBlock);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].pBuffMatBlock->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].dwNumMatBlock; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{// �e�N�X�`���t�@�C�������݂���

					// ���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_aBlock[nCntBlock].apTextureBlock[nCntMat]);
				}
			}

			break;
		}
	}
}

//********************************************
// �u���b�N�̎擾
//********************************************
BLOCK* GetBlock(void)
{
	return &g_aBlock[0];
}

//********************************************
// �u���b�N�Ǘ��̎擾
//********************************************
BLOCKMANAGER* GetBlockManager(void)
{
	return &g_blockManager;
}