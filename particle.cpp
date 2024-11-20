#include "effect.h"
#include "particle.h"

// グローバル変数宣言
PARTICLE g_aParticle[MAX_PARTICLE];						// パーティクル

//**************************************
// パーティクルの初期化
//**************************************
void InitParticle(void)
{
	for (int nCntEX = 0; nCntEX < MAX_PARTICLE; nCntEX++)
	{
		// 設定したい値をぶち込む
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
// パーティクルの更新
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
// パーティクルの設定
//*****************************
void SetParticle(PARTICLE pati)
{
	
	for (int nCntEX = 0; nCntEX < MAX_PARTICLE; nCntEX++)
	{
		if (g_aParticle[nCntEX].bUse == false)
		{
			// 設定したい値をぶち込む
			g_aParticle[nCntEX] = pati;
			g_aParticle[nCntEX].bUse = true;
			break;
		}
	}
}