#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "pause.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "block.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "guide.h"

//�O���[�o���ϐ��錾
GAMESTATE g_gameState = GAMESTATE_NONE;	//�Q�[�����
int g_nCounterGameState = 0;			//��ԊǗ��J�E���^�[
bool g_bPause = false; 

//===========================================
//�Q�[����ʂ̏���������
//===========================================
void InitGame(void)
{
	InitShadow();	// �e
	InitCamera();	// �J����
	InitLight();	// ���C�g
	InitPlayer();	// �v���C���[
	InitBlock();	// �u���b�N
	InitBullet();		// �e
	InitExplosion();	// ����
	InitEffect();		// �G�t�F�N�g
	InitParticle();		// �p�[�e�B�N��
	InitGuide();		// �K�C�h

	g_gameState = GAMESTATE_NORMAL;	//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;		//�J�E���^�[���[��
	g_bPause = false;				//�|�[�Y����
}

//===========================================
//�Q�[����ʂ̏I������
//===========================================
void UninitGame(void)
{
	UninitCamera();		//�J����
	UninitLight();		//���C�g
	UninitPlayer();		// �v���C���[
	UninitShadow();		// �e
	UninitBlock();		// �u���b�N
	UninitBullet();		// �e
	UninitExplosion();	// ����
	UninitEffect();		// �G�t�F�N�g
	UninitGuide();		// �K�C�h

}

//===========================================
//�Q�[����ʂ̍X�V����
//===========================================
void UpdateGame(void)
{
	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y���̍X�V����
		UpdatePause();
	}
	else
	{//�|�[�Y���łȂ����
		UpdatePlayer();		// �v���C���[
		UpdateCamera();		//�J����
		UpdateLight();		//���C�g
		UpdateShadow();		// �e
		UpdateBlock();		// �u���b�N
		UpdateBullet();		// �e
		UpdateExplosion();	// ����
		UpdateEffect();		// �G�t�F�N�g
		UpdateParticle();	// �p�[�e�B�N��
		UpdateGuide();		// �K�C�h

	}
	
	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_BACK) == true)
	{//�|�[�Y�L�[�iP�j�������ꂽ
		g_bPause = g_bPause ? false : true;
	}

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(MODE_RESULT);
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://�ʏ���

		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	//�������Ă��Ȃ���Ԃɐݒ�
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//===========================================
//�Q�[����ʂ̕`�揈��
//===========================================
void DrawGame(void)
{
	SetCamera();		// �J����

#ifdef _DEBUG
	DrawGuide();		// �K�C�h
#endif

	DrawShadow();		// �e
	DrawEffect();		// �G�t�F�N�g
	DrawPlayer();		// �v���C���[
	DrawBlock();		// �u���b�N
	DrawBullet();		// �e
	DrawExplosion();	// ����


	//�|�[�Y��
	if (g_bPause == true)
	{
		//�|�[�Y�̕`��
		DrawPause();
	}
}

//===========================================
//�Q�[����Ԃ̐ݒ�
//===========================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	g_nCounterGameState = 0;
}

//===========================================
//�Q�[����Ԃ̎擾
//===========================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//===========================================
//�|�[�Y�̗L�������ݒ�
//===========================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}