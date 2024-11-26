#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

// マクロ定義
#define PLAYER_MOVE (5.0f)
#define PLAYER_GRAVITY (0.2f)

// プレイヤー情報構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 posOld;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 rotDest;	// 目的の向き
	D3DXVECTOR3 vtxMinPlayer, vtxMaxPlayer;	// モデルの最小値最大値
	float playerSizeTop;		// モデルの大きさ上
	float playerSizeDown;		// モデルの大きさ下
	float playerSizeLeft;		// モデルの大きさ左
	float playerSizeRight;	// モデルの大きさ右
	bool bMove;				// 動くかどうか
	bool bJanp;				// ジャンプしているかどうか
}PLAYER;

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER* GetPlayer(void);
#endif // !_PLAYER_H_
