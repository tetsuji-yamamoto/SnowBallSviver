#ifndef _FADE_H_                                                                                                                                                                                                                                                                                                                                                                                                                                 //�R�{�N�i
#define _FADE_H_

#include "main.h"

//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE = 0,	//�������Ă��Ȃ����
	FADE_IN,		//�t�F�[�h�C�����
	FADE_OUT,		//�t�F�[�h�A�E�g���
	FADE_MAX
}FADE;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          //�R�{�N�i
//�v���g�^�C�v�錾
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext);
FADE GetFade(void);
#endif