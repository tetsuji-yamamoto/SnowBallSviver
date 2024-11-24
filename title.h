#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

// �}�N����`
#define FILE_TEX_TITLE_SBS "date\\texture\\title\\SBS_TITLE_001.png"

// �^�C�g���|���S���^�C�v
typedef enum
{
	TITLETYPE_TEST = 0,	// �^�C�g���̃e�X�g
	TITLETYPE_BG,		// �^�C�g����BG
	TITLETYPE_LOGO,		// �^�C�g���̃��S
	TITLETYPE_START,	// �^�C�g���̃X�^�[�g�{�^��
	TITLETYPE_MAX
}TITLETYPE;

// �^�C�g�����o��
typedef enum
{
	TITLEDIRECT_LOGODOWN = 0,			// ���S���������Ă���
	TITLEDIRECT_STARTAPPEAR,			// �X�^�[�g�o��
	TITLEDIRECT_STARTBRINK,				// �X�^�[�g�_��
	TITLEDIRECT_STARTBRINK_QUICKLY,		// �X�^�[�g�f�����_��quickly
}TITLEDIRECT;

// �^�C�g���\����
typedef struct
{
	const char* pFileName;	// �t�@�C���l�[��
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �F
	TITLETYPE type;			// �^�C�v
	float fWidth;			// ��
	float fHeight;			// ����
	bool bUse;				// �g�p���Ă��邩�ǂ���
}TITLE;

// �^�C�g���̉��o�\����
typedef struct
{
	TITLEDIRECT titleDirect;	// �^�C�g�����o��
	int nTimer;					// �^�C�}�[
	bool bBrink;				// �_�łǂ����H
}TITLEDIRECTOR;

// �v���g�^�C�v�錾
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(TITLE title);
#endif