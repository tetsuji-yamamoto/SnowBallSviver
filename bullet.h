#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

#define MAX_BULLET (256)	// ビルボードの最大数
#define BULLET_GRAVITY (0.2f)	// 弾の重力
#define BULLET_SPEED (10)	// 弾の速度
#define BULLET_MAX_DISTANCE (100)	// 弾の最大飛距離

#define FILE_TEX_BULLET_SNOW "date\\texture\\bullet\\SBS_BULLET_SNOW_001.png"
#define FILE_TEX_BULLET_ICE "date\\texture\\bullet\\SBS_BULLET_ICE_001.png"
#define FILE_TEX_BULLET_GRAVEL "date\\texture\\bullet\\SBS_BULLET_GRAVEL_001.png"

// 弾の種類
typedef enum
{
	BULLETTYPE_SNOW = 0,
	BULLETTYPE_ICE,
	BULLETTYPE_GRAVEL,
	BULLETTYPE_GRAVEL_DIFFUSION,
	BULLETTYPE_MAX
}BULLETTYPE;

// 玉セット構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 dir;	// 行ってほしい方向
	D3DXVECTOR3 size;	// 大きさ
	D3DXVECTOR3 move;	// 移動量
	BULLETTYPE type;	// 種類
	float fLife;		// 寿命
}SETBULLET;

// ビルボード構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 dir;		// 行ってほしい方向
	D3DXMATRIX mtxWorld;	// マトリクス
	D3DXVECTOR3 move;		// 移動量
	BULLETTYPE type;		// 種類
	float fLife;			// 寿命
	bool bUse;				// 使用しているかどうか
}BULLET;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SnowBall(int nCntBl);
void IceBall(int nCntBl);
void GravelBall(int nCntBl);
void GravelBallDiffusion(int nCntBl);
void SetBullet(SETBULLET setBlt);

#endif // !_BILLBOARD_H_
