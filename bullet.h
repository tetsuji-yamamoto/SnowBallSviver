#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

#define MAX_BULLET (256)	// �r���{�[�h�̍ő吔
#define BULLET_GRAVITY (0.2f)	// �e�̏d��
#define BULLET_SPEED (10)	// �e�̑��x
#define BULLET_MAX_DISTANCE (100)	// �e�̍ő�򋗗�

#define FILE_TEX_BULLET_SNOW "date\\texture\\bullet\\SBS_BULLET_SNOW_001.png"
#define FILE_TEX_BULLET_ICE "date\\texture\\bullet\\SBS_BULLET_ICE_001.png"
#define FILE_TEX_BULLET_GRAVEL "date\\texture\\bullet\\SBS_BULLET_GRAVEL_001.png"

// �e�̎��
typedef enum
{
	BULLETTYPE_SNOW = 0,
	BULLETTYPE_ICE,
	BULLETTYPE_GRAVEL,
	BULLETTYPE_GRAVEL_DIFFUSION,
	BULLETTYPE_MAX
}BULLETTYPE;

// �ʃZ�b�g�\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 dir;	// �s���Ăق�������
	D3DXVECTOR3 size;	// �傫��
	D3DXVECTOR3 move;	// �ړ���
	BULLETTYPE type;	// ���
	float fLife;		// ����
}SETBULLET;

// �r���{�[�h�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 dir;		// �s���Ăق�������
	D3DXMATRIX mtxWorld;	// �}�g���N�X
	D3DXVECTOR3 move;		// �ړ���
	BULLETTYPE type;		// ���
	float fLife;			// ����
	bool bUse;				// �g�p���Ă��邩�ǂ���
}BULLET;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SnowBall(int nCntBl);
void IceBall(int nCntBl);
void GravelBall(int nCntBl);
void GravelBallDiffusion(int nCntBl);
void SetBullet(SETBULLET setBlt);

#endif // !_BILLBOARD_H_
