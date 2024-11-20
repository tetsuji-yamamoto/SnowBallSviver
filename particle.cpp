#include "effect.h"
#include "particle.h"

// �O���[�o���ϐ��錾
PARTICLE g_aParticle[MAX_PARTICLE];						// �p�[�e�B�N��

//**************************************
// �p�[�e�B�N���̏�����
//**************************************
void InitParticle(void)
{
	for (int nCntEX = 0; nCntEX < MAX_PARTICLE; nCntEX++)
	{
		// �ݒ肵�����l���Ԃ�����
		g_aParticle[nCntEX].effect.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntEX].effect.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntEX].effect.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntEX].effect.fLife = 0.0f;
		g_aParticle[nCntEX].effect.fsizeDiff = 0.0f;
		g_aParticle[nCntEX].effect.bUse = false;
		g_aParticle[nCntEX].nAmount = 0;
		g_aParticle[nCntEX].bUse = false;
	}
}

//*****************************
// �p�[�e�B�N���̍X�V
//*****************************
void UpdateParticle(void)
{
	for (int nCntEX = 0; nCntEX < MAX_PARTICLE; nCntEX++)
	{
		if (g_aParticle[nCntEX].bUse == true)
		{
			for (int nCnt = 0; nCnt < g_aParticle[nCntEX].nAmount; nCnt++)
			{
				//float fDirX = ((float)rand() % 628 + 314) * 0.01f;
			}
		}
	}
}

//*****************************
// �p�[�e�B�N���̐ݒ�
//*****************************
void SetParticle(PARTICLE pati)
{
	
	for (int nCntEX = 0; nCntEX < MAX_PARTICLE; nCntEX++)
	{
		if (g_aParticle[nCntEX].bUse == false)
		{
			// �ݒ肵�����l���Ԃ�����
			g_aParticle[nCntEX] = pati;
			g_aParticle[nCntEX].bUse = true;
			break;
		}
	}
}