#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "effect.h"

#define MAX_PARTICLE (256)	// 最大パーティクル数

// パーティクルタイプ
typedef enum
{
	PATITYPE_RADIATION = 0,
	PATITYPE_MAX
}PATITIPE;

// パーティクル構造体
typedef struct
{
	EFFECT effect;		// エフェクト情報
	int nAmount;		// 出す量
	bool bUse;
}PARTICLE;

// プロトタイプ宣言
void InitParticle(void);
void UpdateParticle(void);
void SetParticle(PARTICLE pati);

#endif // !_PARTICLE_H_
