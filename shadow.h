#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

// マクロ定義
#define MAX_SHADOW (256)	// 影の最大数

// 影構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXMATRIX mtxWorld;	// マトリックス
	bool bUse;				// 使用するかどうか
}Shadow;

// プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadw(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);

#endif // !_SHADOW_H_
