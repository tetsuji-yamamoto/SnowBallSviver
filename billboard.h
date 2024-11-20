#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

#define MAX_BLBD (256)	// �r���{�[�h�̍ő吔

// �r���{�[�h�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXMATRIX mtxWorld;	// �}�g���N�X
	bool bUse;				// �g�p���Ă��邩�ǂ���
}Billboard;

//�v���g�^�C�v�錾
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size);

#endif // !_BILLBOARD_H_
