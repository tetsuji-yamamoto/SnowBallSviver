#include "player.h"
#include "keyboard.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "particle.h"
#include "joypad.h"
#include "block.h"
#include "wall.h"

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
	Camera* pCamera = GetCamera();				// �J�����̎擾
	XINPUT_STATE* pJoypad = GetJoypadState();	// �R���g���[���[���擾
	g_player.bMove = false;	// �����Ȃ���	

	// �L�[����
	if (KeyboardRepeat(DIK_W))
	{// �O�ړ�
		g_player.bMove = true;	// ������

		if (KeyboardRepeat(DIK_A))
		{// ���ړ�
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;	// �ړI�̊p�x��ݒ�
		}
		else if (KeyboardRepeat(DIK_D))
		{// �E�ړ�		
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;	// �ړI�̊p�x��ݒ�
		}
		else
		{
			g_player.rotDest.y = pCamera->rot.y;	// �ړI�̊p�x��ݒ�
		}
	}
	else if (KeyboardRepeat(DIK_S))
	{// ���ړ�
		g_player.bMove = true;	// ������
		if (KeyboardRepeat(DIK_A))
		{// ���ړ�
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;	// �ړI�̊p�x��ݒ�
		}
		else if (KeyboardRepeat(DIK_D))
		{// �E�ړ�		
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;	// �ړI�̊p�x��ݒ�
		}
		else
		{
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI;	// �ړI�̊p�x��ݒ�
		}
	}
	else if (KeyboardRepeat(DIK_A))
	{// ���ړ�
		g_player.bMove = true;	// ������

		g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;	// �ړI�̊p�x��ݒ�
	}
	else if (KeyboardRepeat(DIK_D))
	{// �E�ړ�		
		g_player.bMove = true;	// ������

		g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;	// �ړI�̊p�x��ݒ�
	}

	// �R���g���[���[����
	if (GetJoyStickL())
	{// ���X�e�B�b�N
		g_player.bMove = true;	// ������
		// �ړI�̊p�x���Z�o
		g_player.rotDest.y = pCamera->rot.y + atan2f(pJoypad->Gamepad.sThumbLX, pJoypad->Gamepad.sThumbLY);
	}

	if (KeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A))
	{// A�W�����v
		if (g_player.bJanp == false)
		{// �W�����v���ĂȂ�������
			g_player.move.y = 8.0f;
			g_player.bJanp = true;	// �W�����v���
		}
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

	// �Â��ʒu���X�V
	g_player.posOld.x = g_player.pos.x;
	g_player.posOld.y = g_player.pos.y;
	g_player.posOld.z = g_player.pos.z;

	if (g_player.bJanp == true)
	{
		g_player.move.y -= PLAYER_GRAVITY;
	}

	// ����
	g_player.move.x += (0 - g_player.move.x) * 0.3f;
	g_player.move.z += (0 - g_player.move.z) * 0.3f;


	// �ړ��ʒǉ�
	g_player.pos.x += g_player.move.x;
	CollisionBlock();	// �����蔻��

	g_player.pos.y += g_player.move.y;
	g_player.bJanp = !CollisionBlock();	// �����蔻��

	g_player.pos.z += g_player.move.z;
	CollisionBlock();	// �����蔻��

	CollisionWall();	// �ǂ̓����蔻��

	if (g_player.pos.y <= 0.0f)
	{// �n�ʓ˂�����
		g_player.pos.y = 0.0f;
		g_player.bJanp = false;	// �W�����v���ĂȂ���
	}

	if (KeyboardTrigger(DIK_V) || GetJoypadTrigger(JOYKEY_X))
	{// �e����

		// �e�ݒ�
		SETBULLET setBlt;

		// �����
		setBlt.pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 10.0f, g_player.pos.z);
		setBlt.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		setBlt.type = BULLETTYPE_SNOW;
		setBlt.fLife = 120.0f;

		//float fX = (float)BULLET_MAX_DISTANCE / 2.0f;
		//float fY = (float)BULLET_MAX_DISTANCE / (float)BULLET_SPEED;	// �������̂Ă��؂�
		//float fAngle = atan2f(fX, fY);

		setBlt.dir.x = pCamera->rot.x + D3DX_PI;
		setBlt.dir.y = g_player.rotDest.y;
		setBlt.dir.z = g_player.rotDest.z;
		//setBlt.dir.x = D3DX_PI*0.5f;

		// �����ɂԂ�����ŃZ�b�g����
		SetBullet(setBlt);

		//// �p�[�e�B�N���ݒ�
		//PARTICLE particle;

		//// ������
		//particle.effect.pos = g_player.pos;
		//particle.effect.col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		//particle.effect.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		//particle.effect.dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//particle.effect.col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		//particle.effect.fDffAlph = 0.01f;
		//particle.effect.fLife = 120.0f;
		//particle.effect.fsizeDiff = 0.01f;
		//SetParticle(particle);
	}
	else if (KeyboardTrigger(DIK_B) || GetJoypadTrigger(JOYKEY_Y))
	{// �X�ʔ���
		// �e�ݒ�
		SETBULLET setBlt;

		// �����
		setBlt.pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 10.0f, g_player.pos.z);
		setBlt.dir.x = pCamera->rot.x + D3DX_PI;
		setBlt.dir.y = g_player.rotDest.y;
		setBlt.dir.z = g_player.rotDest.z;
		setBlt.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		setBlt.type = BULLETTYPE_ICE;
		setBlt.fLife = 60.0f;

		// �����ɂԂ�����ŃZ�b�g����
		SetBullet(setBlt);

	}
	else if (KeyboardTrigger(DIK_N) || GetJoypadTrigger(JOYKEY_B))
	{// �����ʔ���
		// �e�ݒ�
		SETBULLET setBlt;

		// �����
		setBlt.pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 10.0f, g_player.pos.z);
		setBlt.dir.x = pCamera->rot.x + D3DX_PI;
		setBlt.dir.y = g_player.rotDest.y;
		setBlt.dir.z = g_player.rotDest.z;
		setBlt.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		setBlt.type = BULLETTYPE_GRAVEL;
		setBlt.fLife = 90.0f;

		// �����ɂԂ�����ŃZ�b�g����
		SetBullet(setBlt);

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