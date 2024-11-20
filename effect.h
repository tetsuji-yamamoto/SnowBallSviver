#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

#define MAX_EFFECT (512)	// �r���{�[�h�̍ő吔

// �G�t�F�N�g�^�C�v
typedef enum
{
	EFFECTTYPE_NOMAL = 0,
	EFFECTTYPE_MAX
}EFFECTTYPE;

// �r���{�[�h�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 size;		// �傫��
	D3DXVECTOR3 dir;		// ����
	D3DXVECTOR3 rot;		// ����
	D3DXCOLOR col;			// �F
	D3DXMATRIX mtxWorld;	// �}�g���N�X
	EFFECTTYPE type;		// �^�C�v
	float fsizeDiff;	// �傫����������
	float fDffAlph;		// �A���t�@�l�̍���
	float fLife;		// ����
	bool bUse;			// �g�p���Ă��邩�ǂ���
}EFFECT;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(EFFECT effect);

#endif // !_BILLBOARD_H_
