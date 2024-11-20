#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

// �}�N����`
#define MAX_SHADOW (256)	// �e�̍ő吔

// �e�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXMATRIX mtxWorld;	// �}�g���b�N�X
	bool bUse;				// �g�p���邩�ǂ���
}Shadow;

// �v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadw(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);

#endif // !_SHADOW_H_
