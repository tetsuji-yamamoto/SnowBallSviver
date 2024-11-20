#include "player.h"
#include "keyboard.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "particle.h"

// �O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTexturePlayer[6] = {};		// �e�N�X�`���ւ̃|���^
LPD3DXMESH g_pMeshPlayer = NULL;					// ���b�V��(���_���ւ̃|�C���^)
LPD3DXBUFFER g_pBuffMatPlayer = NULL;				// �}�e���A���ւ̃|�C���^
DWORD g_dwNumMatPlayer = 0;							// �}�e���A���̐�
D3DXMATRIX g_mtxWorldPlayer;						// ���[���h�}�g���b�N�X
PLAYER g_player;	// �v���C���[���
int nIdxShadow = 0;

//************************************************
// �v���C���[������
//************************************************
void InitPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v���C���[��񏉊���
	
	// �e��ϐ��̏�����
	g_player.pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);		// �ʒu
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI����
	g_player.bMove = false;		// �������ǂ���

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("date\\xfile\\player\\testPlayer_002.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// �e�N�X�`���t�@�C�������݂���

			// ���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTexturePlayer[nCntMat]);
		}
	}

	// �e�̐ݒ�
	SetShadw(g_player.pos, g_player.rot);
}

//************************************************
// �v���C���[�̏I��
//************************************************
void UninitPlayer(void)
{
	// ���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	// �}�e���A���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}

	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}
}

//************************************************
// �v���C���[�̍X�V
//************************************************
void UpdatePlayer(void)
{
	Camera* pCamera = GetCamera();	// �J�����̎擾

	g_player.bMove = false;	// �����Ȃ���	

	if (KeyboardRepeat(DIK_I))
	{// �O�ړ�
		g_player.bMove = true;	// ������

		g_player.rotDest.y = pCamera->rot.y;	// �ړI�̊p�x��ݒ�
	}
	else if (KeyboardRepeat(DIK_K))
	{// ���ړ�
		g_player.bMove = true;	// ������

		g_player.rotDest.y = pCamera->rot.y + D3DX_PI;	// �ړI�̊p�x��ݒ�
	}

	if (KeyboardRepeat(DIK_J))
	{// ���ړ�
		g_player.bMove = true;	// ������

		g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;	// �ړI�̊p�x��ݒ�

	}
	else if (KeyboardRepeat(DIK_L))
	{// �E�ړ�		
		g_player.bMove = true;	// ������

		g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;	// �ړI�̊p�x��ݒ�
	}

	if (g_player.rotDest.y > D3DX_PI)
	{
		g_player.rotDest.y = -D3DX_PI + (g_player.rotDest.y - D3DX_PI);
	}
	else if (g_player.rotDest.y < -D3DX_PI)
	{
		g_player.rotDest.y = D3DX_PI + (g_player.rotDest.y + D3DX_PI);
	}

	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y = -D3DX_PI + (g_player.rot.y - D3DX_PI);
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y = D3DX_PI + (g_player.rot.y + D3DX_PI);
	}

	if (g_player.bMove == true)
	{
		g_player.move.x = sinf(g_player.rotDest.y) * PLAYER_MOVE;
		g_player.move.z = cosf(g_player.rotDest.y) * PLAYER_MOVE;
	}

	// ���f���̊p�x��ړI�̊p�x�ɋ߂Â���

	float fDiff = g_player.rotDest.y - g_player.rot.y;

	if (fDiff > D3DX_PI)
	{
		fDiff = fDiff - D3DX_PI * 2;
	}
	else if (fDiff < -D3DX_PI)
	{
		fDiff = fDiff + D3DX_PI * 2;
	}
	g_player.rot.y += (fDiff) * 0.1f;

	// ����
	g_player.move.x += (0 - g_player.move.x) * 0.3f;
	g_player.move.y += (0 - g_player.move.y) * 0.3f;
	g_player.move.z += (0 - g_player.move.z) * 0.3f;
	
	// �ړ��ʒǉ�
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	g_player.pos.z += g_player.move.z;

	if (KeyboardTrigger(DIK_RSHIFT))
	{// �E�ړ�		

		// �e�ݒ�
		SETBULLET setBlt;

		// �����
		setBlt.pos = g_player.pos;
		setBlt.dir = g_player.rot;
		setBlt.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		setBlt.fLife = 120.0f;

		// �����ɂԂ�����ŃZ�b�g����
		SetBullet(setBlt);

		// �p�[�e�B�N���ݒ�
		PARTICLE particle;

		// ������
		particle.effect.pos = g_player.pos;
		particle.effect.col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		particle.effect.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		particle.effect.dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		particle.effect.col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		particle.effect.fDffAlph = 0.01f;
		particle.effect.fLife = 120.0f;
		particle.effect.fsizeDiff = 0.01f;
		SetParticle(particle);
	}

	// �e�̍X�V
	SetPositionShadow(0, g_player.pos);
	
}

//************************************************
// �v���C���[�̕\��
//************************************************
void DrawPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);

		// ���f��(�p�[�c�̕`��)
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//************************************************
// �v���C���[�̎擾
//************************************************
PLAYER* GetPlayer(void)
{
	return &g_player;
}