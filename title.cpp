#include "title.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"

// �O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_aPTextureTitle[TITLETYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
TITLE g_aTitle[TITLETYPE_MAX];								// �^�C�g���|���S���̏��//�^�C�g���|���S���̃e�N�X�`��
TITLEDIRECTOR g_TitleDirector;

//*********************************************
// �^�C�g����ʂ̏���������
//*********************************************
void InitTitle(void)
{

	int nCntTitle;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLETYPE_MAX, // �K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	// ���o�\���̏�����
	g_TitleDirector.titleDirect = TITLEDIRECT_LOGODOWN;
	g_TitleDirector.nTimer = 0;
	g_TitleDirector.bBrink = false;

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// ���̏�����
	for (nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		g_aTitle[nCntTitle].pFileName = NULL;
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].type = TITLETYPE_MAX;

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	TITLE title;
	title.pFileName = FILE_TEX_TITLE_SBS;
	title.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	title.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	title.type = TITLETYPE_LOGO;
	title.fHeight = SCREEN_HEIGHT * 0.15f;
	title.fWidth = SCREEN_WIDTH * 0.3f;

	// �^�C�g�����S
	SetTitle(title);

}
//*********************************************
// �^�C�g����ʂ̏I������
//*********************************************
void UninitTitle(void)
{
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		// �e�N�X�`���̔j��
		if (g_aPTextureTitle[nCntTitle] != NULL)
		{
			g_aPTextureTitle[nCntTitle]->Release();
			g_aPTextureTitle[nCntTitle] = NULL;
		}
	}

	//�� �_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//*********************************************
// �^�C�g����ʂ̍X�V����
//*********************************************
void UpdateTitle(void)
{
	
	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(MODE_GAME);
	}
}

//*********************************************
// �^�C�g����ʂ̕`�揈��
//*********************************************
void DrawTitle(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aPTextureTitle[nCntTitle]);

			// �v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				4 * nCntTitle,							// �`�悷��ŏ��̒��_�C���f�b�N�X
				2);										// �`�悷��v���~�e�B�u�i�v���C���[�j��
		}
	}


}

//*********************************************
// �^�C�g���̐ݒ�
//*********************************************
void SetTitle(TITLE title)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �T��
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == false)
		{
			g_aTitle[nCntTitle].pFileName = title.pFileName;
			g_aTitle[nCntTitle].pos = title.pos;
			g_aTitle[nCntTitle].col = title.col;
			g_aTitle[nCntTitle].type = title.type;
			g_aTitle[nCntTitle].fWidth = title.fWidth;
			g_aTitle[nCntTitle].fHeight = title.fHeight;
			g_aTitle[nCntTitle].bUse = true;

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				g_aTitle[nCntTitle].pFileName,
				&g_aPTextureTitle[nCntTitle]);

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}