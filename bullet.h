#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

#define MAX_BULLET (256)	// ビルボードの最大数

// 玉セット構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 dir;	// 行ってほしい方向
	D3DXVECTOR3 size;	// 大きさ
	float fLife;		// 寿命
}SETBULLET;

// ビルボード構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 dir;		// 行ってほしい方向
	D3DXMATRIX mtxWorld;	// マトリクス
	float fLife;			// 寿命
	bool bUse;				// 使用しているかどうか
}BULLET;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(SETBULLET setBlt);

#endif // !_BILLBOARD_H_
