#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//�|�[�Y���j���[
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,	//�Q�[���ɖ߂�
	PAUSE_MENU_RETRY,			//�Q�[������蒼��
	PAUSE_MENU_QUIT,			//�^�C�g����ʂɖ߂�
	PAUSE_MENU_MAX,
}PAUSE_MENU;

//�}�N����`
#define MENU_HEIGHT (35)		//���j���[UI�̍���
#define MENU_WIDTH (150)		//���j���[UI�̍���
#define FILE_TEX_PAUSE_CONTENUE "data\\PAUSE\\Continue_001.jpg"
#define FILE_TEX_PAUSE_RETRY "data\\PAUSE\\Retry_001.jpg"
#define FILE_TEX_PAUSE_QUIT "data\\PAUSE\\Quit_001.jpg"

//�|�[�Y���j���[�\����
typedef struct
{
	const char* pFileName;	//�t�@�C���̃p�X
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	int nType;				//���
	float fWidth;			//��
	float fHeight;			//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
}PAUSE;

//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SetPause(const char* pFileName, D3DXVECTOR3 pos, D3DXCOLOR col, PAUSE_MENU type, float fWidth, float fHeight);
#endif
