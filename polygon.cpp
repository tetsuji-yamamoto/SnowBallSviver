#include "polygon.h"
#include "camera.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturPolygon = NULL;		// �e�N�X�`���̃|�C���^
D3DXVECTOR3 g_posPlygon;							// �ʒu
D3DXVECTOR3 g_rotPolygon;							// ����
D3DXMATRIX g_mtxWorldPolygon;						// ���[���h�}�g���b�N�X

//**************************************
// �|���S���̏�����
//**************************************
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\test\\image.jpg",
		&g_pVtxTexturPolygon);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = -150.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 150.0f;

	pVtx[1].pos.x = 150.0f;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 150.0f;

	pVtx[2].pos.x = -150.0f;
	pVtx[2].pos.y = 0.0f;
	pVtx[2].pos.z = -150.0f;

	pVtx[3].pos.x = 150.0f;
	pVtx[3].pos.y = 0.0f;
	pVtx[3].pos.z = -150.0f;

	// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPolygon->Unlock();
}

//======================================
// �|���S���̔j��
//======================================
void UninitPolygon(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//======================================
// �|���S���̔j��
//======================================
void UpdatePolygon(void)
{
	
}

//======================================
// �|���S���̕`��
//======================================
void DrawPolygon(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon,&g_mtxWorldPolygon,&mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posPlygon.x, g_posPlygon.y, g_posPlygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon,&g_mtxWorldPolygon,&mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pVtxTexturPolygon);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}