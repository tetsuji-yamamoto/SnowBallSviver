#include "result.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�ւ̃|�C���^
RESULT g_result;									//���U���g�̏��

//===========================================
//���U���g��ʂ̏���������
//===========================================
void InitResult(void)
{
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	g_result.pFileTex = FILE_TEX_RESULT_GAMEOVER;

	switch (g_result.resultType)
	{
	case RESULTTYPE_GAMEOVER:
		g_result.pFileTex = FILE_TEX_RESULT_GAMEOVER;
		break;

	case RESULTTYPE_GAMECREAR:
		g_result.pFileTex = FILE_TEX_RESULT_GAMECREAR;
		break;

	case RESULTTYPE_TIMEOVER:
		g_result.pFileTex = FILE_TEX_RESULT_TIMEOVER;
		break;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		g_result.pFileTex,
		&g_pTextureResult);

	g_result.rect.bottom = SCREEN_HEIGHT;
	g_result.rect.left = 0.0f;
	g_result.rect.right = SCREEN_WIDTH;
	g_result.rect.top = 0.0f;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_result.rect.left, g_result.rect.top, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_result.rect.right, g_result.rect.top, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_result.rect.left, g_result.rect.bottom, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_result.rect.right, g_result.rect.bottom, 0.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

}

//===========================================
//���U���g��ʂ̏I������
//===========================================
void UninitResult(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//===========================================
//���U���g��ʂ̍X�V����
//===========================================
void UpdateResult(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{
		SetFade(MODE_TITLE);
	}

}

//===========================================
//���U���g��ʂ̕`�揈��
//===========================================
void DrawResult(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,										//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);										//�`�悷��v���~�e�B�u�i�v���C���[�j��
}

//===========================================
//���U���g�ݒ�
//===========================================
void SetResult(RESULTTYPE resultType)
{
	g_result.resultType = resultType;
}