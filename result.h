#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

#define FILE_TEX_RESULT_GAMEOVER "date\\texture\\result\\SBS_RESULT_GAMEOVER_001.png"
#define FILE_TEX_RESULT_GAMECREAR "date\\texture\\result\\SBS_RESULT_GAMECREAR_001.png"
#define FILE_TEX_RESULT_TIMEOVER "date\\texture\\result\\SBS_RESULT_GAMECREAR_001.png"
#define FILE_TEX_RESULT_DEFAULT "date\\texture\\billboard\\wood.png"

// ���U���g��
typedef enum
{
	RESULTTYPE_GAMEOVER = 0,
	RESULTTYPE_GAMECREAR,
	RESULTTYPE_TIMEOVER,
	RESULTTYPE_MAX
}RESULTTYPE;

// ���U���g���
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	const char* pFileTex;	// �e�N�X�`���p�X
	RECT rect;				// �l���_
	RESULTTYPE resultType;	// ���U���g�^�C�v
}RESULT;

//�v���g�^�C�v�錾
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(RESULTTYPE resultType);
#endif