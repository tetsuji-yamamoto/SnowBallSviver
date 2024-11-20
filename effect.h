#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

#define MAX_EFFECT (512)	// ビルボードの最大数

// エフェクトタイプ
typedef enum
{
	EFFECTTYPE_NOMAL = 0,
	EFFECTTYPE_MAX
}EFFECTTYPE;

// ビルボード構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 size;		// 大きさ
	D3DXVECTOR3 dir;		// 方向
	D3DXVECTOR3 rot;		// 向き
	D3DXCOLOR col;			// 色
	D3DXMATRIX mtxWorld;	// マトリクス
	EFFECTTYPE type;		// タイプ
	float fsizeDiff;	// 大きさ引く差分
	float fDffAlph;		// アルファ値の差分
	float fLife;		// 寿命
	bool bUse;			// 使用しているかどうか
}EFFECT;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(EFFECT effect);

#endif // !_BILLBOARD_H_
