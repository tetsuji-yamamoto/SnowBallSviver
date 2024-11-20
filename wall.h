#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

// マクロ
#define MAX_WALL (8)	// 壁の最大枚数

// 壁構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 size;	// 大きさ
	D3DXVECTOR3 rot;	// 向き
	D3DXCOLOR col;		// 色
	D3DXMATRIX mtxWorld;// マトリックス
	bool bFaB;			// 表裏
	bool bUse;			// 使用するかどうか
}WALL;

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 rot);
#endif // !_WALL_H_
