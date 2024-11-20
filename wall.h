#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

// �}�N��
#define MAX_WALL (8)	// �ǂ̍ő喇��

// �Ǎ\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 size;	// �傫��
	D3DXVECTOR3 rot;	// ����
	D3DXCOLOR col;		// �F
	D3DXMATRIX mtxWorld;// �}�g���b�N�X
	bool bFaB;			// �\��
	bool bUse;			// �g�p���邩�ǂ���
}WALL;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 rot);
#endif // !_WALL_H_
