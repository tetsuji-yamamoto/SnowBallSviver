#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

#define MAX_BLBD (256)	// ビルボードの最大数

// ビルボード構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXMATRIX mtxWorld;	// マトリクス
	bool bUse;				// 使用しているかどうか
}Billboard;

//プロトタイプ宣言
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size);

#endif // !_BILLBOARD_H_
