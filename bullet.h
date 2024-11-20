#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

#define MAX_BULLET (256)	// �r���{�[�h�̍ő吔

// �ʃZ�b�g�\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 dir;	// �s���Ăق�������
	D3DXVECTOR3 size;	// �傫��
	float fLife;		// ����
}SETBULLET;

// �r���{�[�h�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 dir;		// �s���Ăق�������
	D3DXMATRIX mtxWorld;	// �}�g���N�X
	float fLife;			// ����
	bool bUse;				// �g�p���Ă��邩�ǂ���
}BULLET;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(SETBULLET setBlt);

#endif // !_BILLBOARD_H_
