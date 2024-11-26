#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

#define MAX_BLOCK (9)		// 最大ブロック数
#define FILE_XFILE_BLOCK_SNOW "date\\xfile\\block\\Block_Snow_001.x"

// ブロックタイプ列挙型
typedef enum
{
	BLOCKTYPE_SNOW = 0,	// 雪
	BLOCKTYPE_ICE,		// 氷
	BLOCKTYPE_GRAVEL,	// 砂利
	BLOCKTYPE_MAX
}BLOCKTYPE;

// ブロック構造体
typedef struct
{
	LPDIRECT3DTEXTURE9 apTextureBlock[6];	// テクスチャへのポンタ
	LPD3DXMESH pMeshBlock;					// メッシュ(頂点情報へのポインタ)
	LPD3DXBUFFER pBuffMatBlock;				// マテリアルへのポインタ
	DWORD dwNumMatBlock;					// マテリアルの数
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 vtxMinBlock, vtxMaxBlock;	// モデルの最小値最大値
	const char* pFilename;	// ファイル名
	char astr[256];			// 文字格納
	int nType;				// タイプ
	bool bUse;				// 使っているるかどうか
}BLOCK;

// セットブロック構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	const char* pFilename;	// ファイル名
	char astr[256];			// 文字列格納用
	int nType;				// タイプ
}SETBLOCK;

// ブロックコントローラー
typedef struct
{
	int nCntNowBlock;	// 今選んでいるブロック
}BLOCKCONTROLLER;

// ブロックの管理
typedef struct
{
	int nBlockNum;
}BLOCKMANAGER;

// プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(SETBLOCK setBlock);
BLOCK* GetBlock(void);
BLOCKMANAGER* GetBlockManager(void);
void BlockOllDeliete(void);
bool CollisionBlock(void);
void BlockControllre(void);
#endif // !_MODEL_H_
