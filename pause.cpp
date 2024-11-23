#include "pause.h"
#include "main.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePause[PAUSE_MENU_MAX] = {};	//Direct3D�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//���_�o�b�t�@�ւ̃|�C���^
PAUSE g_aPause[PAUSE_MENU_MAX];								//�|�[�Y���
int g_nSelect;

//======================================
//�|�[�Y�̏���������
//======================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	int nCntPause;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSE_MENU_MAX, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	g_nSelect = PAUSE_MENU_CONTINUE;

	//�|�[�Y����������
	for (nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{
		g_aPause[nCntPause].pFileName = NULL;
		g_aPause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[nCntPause].col = D3DXCOLOR(RGBA_FULLCOLOR);
		g_aPause[nCntPause].nType = PAUSE_MENU_MAX;
		g_aPause[nCntPause].fWidth = 0.0f;
		g_aPause[nCntPause].fHeight = 0.0f;
		g_aPause[nCntPause].bUse = false;

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			g_aPause[nCntPause].pFileName,
			&g_pTexturePause[nCntPause]);

		pVtx[0].pos.x = g_aPause[nCntPause].pos.x - MENU_WIDTH / 2;
		pVtx[0].pos.y = g_aPause[nCntPause].pos.y - MENU_HEIGHT / 2;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aPause[nCntPause].pos.x + MENU_WIDTH / 2;
		pVtx[1].pos.y = g_aPause[nCntPause].pos.y - MENU_HEIGHT / 2;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aPause[nCntPause].pos.x - MENU_WIDTH / 2;
		pVtx[2].pos.y = g_aPause[nCntPause].pos.y + MENU_HEIGHT / 2;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aPause[nCntPause].pos.x + MENU_WIDTH / 2;
		pVtx[3].pos.y = g_aPause[nCntPause].pos.y + MENU_HEIGHT / 2;
		pVtx[3].pos.z = 0.0f;
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	//�R���e�j���[
	SetPause(FILE_TEX_PAUSE_CONTENUE,													//�p�X
		D3DXVECTOR3(TEST_WIDTH_CENTER , TEST_HEIGHT_CENTER - MENU_HEIGHT * 2.0f, 0.0f),	//�ʒu
		D3DXCOLOR(RGBA_FULLCOLOR),														//�F
		PAUSE_MENU_CONTINUE,															//���
		MENU_WIDTH,																		//��
		MENU_HEIGHT);																	//����

	//���g���C
	SetPause(FILE_TEX_PAUSE_RETRY,									//�p�X
		D3DXVECTOR3(TEST_WIDTH_CENTER, TEST_HEIGHT_CENTER, 0.0f),	//�ʒu
		D3DXCOLOR(RGBA_FULLCOLOR),									//�F
		PAUSE_MENU_RETRY,											//���
		MENU_WIDTH,													//��
		MENU_HEIGHT);												//����

	//�N�C�b�g
	SetPause(FILE_TEX_PAUSE_QUIT,														//�p�X
		D3DXVECTOR3(TEST_WIDTH_CENTER, TEST_HEIGHT_CENTER + MENU_HEIGHT * 2.0f, 0.0f),	//�ʒu
		D3DXCOLOR(RGBA_FULLCOLOR),														//�F
		PAUSE_MENU_QUIT,																//���
		MENU_WIDTH,																		//��
		MENU_HEIGHT);																	//����
}

//======================================
//�|�[�Y�̏I������
//======================================
void UninitPause(void)
{
	int nCntPause;

	for (nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePause[nCntPause] != NULL)
		{
			g_pTexturePause[nCntPause]->Release();
			g_pTexturePause[nCntPause] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//======================================
//�|�[�Y�X�V����
//======================================
void UpdatePause(void)
{
	int nCntPause;

	VERTEX_2D* pVtx;
	XINPUT_STATE* pStick = GetJoySticAngle();	//�X�e�B�b�N�擾

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{//��x���ׂĂ𔼓�����
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.6f, 0.8f, 0.6f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.6f, 0.8f, 0.6f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.6f, 0.8f, 0.6f, 0.5f);
		pVtx[3].col = D3DXCOLOR(0.6f, 0.8f, 0.6f, 0.5f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	if (KeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP) == true)//W�A��
	{//W�L�[�������ꂽ
		g_nSelect--;
	}
	else if (KeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN) == true)//S�A��
	{//S�L�[�������ꂽ
		g_nSelect++;
	}
	//�͈͂𒴂��Ȃ��悤�ɂ���
	if (g_nSelect < PAUSE_MENU_CONTINUE)
	{//�[����菬����
		g_nSelect = PAUSE_MENU_QUIT;
	}
	else if (g_nSelect >= PAUSE_MENU_MAX)
	{//�ő�l�ȏ�
		g_nSelect = PAUSE_MENU_CONTINUE;
	}

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//g_nSelect����Ƀ|���S����s�����ɂ���
	pVtx += 4 * g_nSelect;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{//����L�[�������ꂽ
		//���j���[�ɍ��킹�ă��[�h�̐؂�ւ�
		switch (g_nSelect)
		{
		case PAUSE_MENU_CONTINUE:
			if (GetMode() == MODE_TUTORIAL)
			{
			}
			else
			{
			//	SetEnablePause(false);
			}
			break;

		case PAUSE_MENU_RETRY:
			//SetGameState(GAMESTATE_END);
			if (GetMode() == MODE_TUTORIAL)
			{
				SetFade(MODE_TUTORIAL);
			}
			else
			{
				SetFade(MODE_GAME);
			}
			break;

		case PAUSE_MENU_QUIT:
			//SetGameState(GAMESTATE_END);
			SetFade(MODE_TITLE);
			break;
		}

	}
}
//======================================
//�|�[�Y�̕`�揈��
//======================================
void DrawPause(void)
{
	int nCntPause;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�G�t�F�N�g�̕`��
	for (nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{
		if (g_aPause[nCntPause].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePause[nCntPause]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntPause,							//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);
		}
	}
}

//===============================
//�|�[�Y�̐ݒ�
//===============================
void SetPause(const char* pFileName, D3DXVECTOR3 pos, D3DXCOLOR col, PAUSE_MENU type, float fWidth, float fHeight)
{

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//�T��
	for (int nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{
		if (g_aPause[nCntPause].bUse == false)
		{
			g_aPause[nCntPause].pFileName = pFileName;
			g_aPause[nCntPause].pos = pos;
			g_aPause[nCntPause].col = col;
			g_aPause[nCntPause].nType = type;
			g_aPause[nCntPause].fWidth = fWidth;
			g_aPause[nCntPause].fHeight = fHeight;
			g_aPause[nCntPause].bUse = true;

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				g_aPause[nCntPause].pFileName,
				&g_pTexturePause[nCntPause]);

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aPause[nCntPause].pos.x - g_aPause[nCntPause].fWidth;
			pVtx[0].pos.y = g_aPause[nCntPause].pos.y - g_aPause[nCntPause].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aPause[nCntPause].pos.x + g_aPause[nCntPause].fWidth;
			pVtx[1].pos.y = g_aPause[nCntPause].pos.y - g_aPause[nCntPause].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aPause[nCntPause].pos.x - g_aPause[nCntPause].fWidth;
			pVtx[2].pos.y = g_aPause[nCntPause].pos.y + g_aPause[nCntPause].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aPause[nCntPause].pos.x + g_aPause[nCntPause].fWidth;
			pVtx[3].pos.y = g_aPause[nCntPause].pos.y + g_aPause[nCntPause].fHeight;
			pVtx[3].pos.z = 0.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aPause[nCntPause].col;
			pVtx[1].col = g_aPause[nCntPause].col;
			pVtx[2].col = g_aPause[nCntPause].col;
			pVtx[3].col = g_aPause[nCntPause].col;

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}