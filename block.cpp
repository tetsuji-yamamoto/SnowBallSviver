#include "block.h"
#include "player.h"
#include "readtext.h"
#include "writetext.h"
#include "keyboard.h"
#include "edit.h"

// �O���[�o���ϐ��錾
BLOCK g_aBlock[MAX_BLOCK];		// �u���b�N���
BLOCKMANAGER g_blockManager;	// �u���b�N�Ǘ�
BLOCKCONTROLLER g_blockCont;	// �u���b�N������

//********************************************
//�u���b�N�̏�����
//********************************************
void InitBlock(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �u���b�N�Ǘ���񏉊���
	g_blockManager.nBlockNum = 0;

	// �u���b�N�{����񏉊���	
	g_blockCont.nCntNowBlock = 0;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// �e��ϐ��̏�����
		g_aBlock[nCntBlock].apTextureBlock[0] = {};
		g_aBlock[nCntBlock].pMeshBlock = NULL;
		g_aBlock[nCntBlock].pBuffMatBlock = NULL;
		g_aBlock[nCntBlock].dwNumMatBlock = 0;
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f ,0.0f, 0.0f);
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].vtxMaxBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].vtxMinBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nType = BLOCKTYPE_MAX;
		g_aBlock[nCntBlock].bUse = false;
	}

	ReadText();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			int nNumVtx;	// ���_��
			WORD sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y�f�[�^
			BYTE* pVtxBuff;// ���_�o�b�t�@�̃|�C���^
			// ���_���̎擾
			nNumVtx = g_aBlock[nCntBlock].pMeshBlock->GetNumVertices();

			// ���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_aBlock[nCntBlock].pMeshBlock->GetFVF());

			// ���_�o�b�t�@�̃��b�N
			g_aBlock[nCntBlock].pMeshBlock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
			{
				// ���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
				//[���_���W���r���ă��f���̍ő�ŏ����擾]

				if (g_aBlock[nCntBlock].vtxMaxBlock.x <= vtx.x)
				{// �ő�lX
					g_aBlock[nCntBlock].vtxMaxBlock.x = vtx.x;
				}

				if (g_aBlock[nCntBlock].vtxMaxBlock.y <= vtx.y)
				{// �ő�lY
					g_aBlock[nCntBlock].vtxMaxBlock.y = vtx.y;
				}

				if (g_aBlock[nCntBlock].vtxMaxBlock.z <= vtx.z)
				{// �ő�lZ
					g_aBlock[nCntBlock].vtxMaxBlock.z = vtx.z;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.x >= vtx.x)
				{// �ŏ��lX
					g_aBlock[nCntBlock].vtxMinBlock.x = vtx.x;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.y >= vtx.y)
				{// �ŏ��lY
					g_aBlock[nCntBlock].vtxMinBlock.y = vtx.y;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.z >= vtx.z)
				{// �ŏ��lZ
					g_aBlock[nCntBlock].vtxMinBlock.z = vtx.z;
				}

				// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}

			// ���_�o�b�t�@�̃A�����b�N
			g_aBlock[nCntBlock].pMeshBlock->UnlockVertexBuffer();
		}
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
	if (GetEditMode() == EDITMODE_GAME)
	{// �G�f�B�^�[�Q�[�����[�h��������
		BlockControllre();	// �u���b�N����
	}

	if (KeyboardTrigger(DIK_DELETE))
	{
		BlockOllDeliete();
		InitBlock();
	}
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

			if (g_blockCont.nCntNowBlock == nCntBlock)
			{// 
				g_aBlock[nCntBlock].mtxWorld.m[0][0] = 0.5f;
			}

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
// �u���b�N�̓����蔻��
//********************************************
bool CollisionBlock(void)
{
	PLAYER* pPlayer = GetPlayer();	// �v���C���[�擾

	bool bRanding = false;
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPlayer->pos.y + pPlayer->vtxMinPlayer.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
				pPlayer->pos.y + pPlayer->vtxMaxPlayer.y > g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
			{// �㉺�ȓ�
				// X�㉺�̂߂荞�ݔ���
				if (pPlayer->pos.x + pPlayer->vtxMinPlayer.x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
					pPlayer->pos.x + pPlayer->vtxMaxPlayer.x > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
				{// X�̕�
					if (pPlayer->posOld.z + pPlayer->vtxMaxPlayer.z <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z &&
						pPlayer->pos.z + pPlayer->vtxMaxPlayer.z > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
					{// Z����O���牜�ɂ߂荞��
						pPlayer->pos.z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z + pPlayer->vtxMinPlayer.z;
					}
					else if (pPlayer->posOld.z + pPlayer->vtxMinPlayer.z >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
						pPlayer->pos.z + pPlayer->vtxMinPlayer.z < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z)
					{// Z���������O�ɂ߂荞��
						pPlayer->pos.z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z + pPlayer->vtxMaxPlayer.z;
					}
				}

				// Y�̓����蔻��
				if (pPlayer->pos.x + pPlayer->vtxMinPlayer.x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
					pPlayer->pos.x + pPlayer->vtxMaxPlayer.x >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
					pPlayer->pos.z + pPlayer->vtxMinPlayer.z <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
					pPlayer->pos.z + pPlayer->vtxMaxPlayer.z >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
				{// X�̕���Z�̕���
					if (pPlayer->posOld.y + pPlayer->vtxMinPlayer.y >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
						pPlayer->pos.y + pPlayer->vtxMinPlayer.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y)
					{// �ォ�牺
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y - pPlayer->vtxMinPlayer.y;
						pPlayer->move.y = 0.0f;
						bRanding = true;
					}
					else if (pPlayer->posOld.y + pPlayer->vtxMaxPlayer.y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y &&
						pPlayer->pos.y + pPlayer->vtxMaxPlayer.y > g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
					{// �������
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y - pPlayer->vtxMaxPlayer.y;
						pPlayer->move.y = 0.0f;
					}
				}

				// Z���E�̂߂荞�ݔ���
				if (pPlayer->pos.z + pPlayer->vtxMinPlayer.z < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
					pPlayer->pos.z + pPlayer->vtxMaxPlayer.z > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
				{// Z�̕�
					if (pPlayer->posOld.x + pPlayer->vtxMaxPlayer.x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
						pPlayer->pos.x + pPlayer->vtxMaxPlayer.x > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
					{// X��������E�ɂ߂荞��
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x - pPlayer->vtxMaxPlayer.x;
					}
					else if (pPlayer->posOld.x + pPlayer->vtxMinPlayer.x >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
						pPlayer->pos.x + pPlayer->vtxMinPlayer.x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x)
					{// X���E���獶�ɂ߂荞��
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x - pPlayer->vtxMinPlayer.x;
					}
				}
			}
		}
	}
	return bRanding;
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

//********************************************
// �u���b�N�S������
//********************************************
void BlockOllDeliete(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].bUse = false;
		g_blockManager.nBlockNum--;
	}
}

//********************************************
// �u���b�N����
//********************************************
void BlockControllre(void)
{
	if (KeyboardTrigger(DIK_UP))
	{
		int nCntMax = 0;

		while (1)
		{
			g_blockCont.nCntNowBlock++;// ���̓z�փJ�E���g
			nCntMax++;
			if (g_aBlock[g_blockCont.nCntNowBlock].bUse)
			{// ���̃u���b�N���g���Ă���
				break;
			}
			
			if (nCntMax > g_blockManager.nBlockNum)
			{// �o�����Ă���u���b�N���𒴂�����
				g_blockCont.nCntNowBlock = 0;
				break;
			}
		}
	}

	
}