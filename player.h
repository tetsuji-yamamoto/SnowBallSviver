#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

// マクロ定義
#define PLAYER_MOVE (3.0f)

// プレイヤー情報構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 rotDest;	// 目的の向き

	bool bMove;				// 動くかどうか
}PLAYER;

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER* GetPlayer(void);
#endif // !_PLAYER_H_
