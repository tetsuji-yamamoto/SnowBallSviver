#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

#define MAX_EXPOLOSION (256)	// �r���{�[�h�̍ő吔

// �ʃZ�b�g�\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 size;	// �傫��
}SETEXPLO;

// �r���{�[�h�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXMATRIX mtxWorld;	// �}�g���N�X
	int nCntTime;			// �^�C�}�[
	int nCntPtn;			// �p�^�[��
	bool bUse;				// �g�p���Ă��邩�ǂ���
}EXPLOSION;

//�v���g�^�C�v�錾
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(SETEXPLO setExplo);

#endif // !_BILLBOARD_H_
