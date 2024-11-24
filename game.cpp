#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "pause.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "block.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "guide.h"

//グローバル変数宣言
GAMESTATE g_gameState = GAMESTATE_NONE;	//ゲーム状態
int g_nCounterGameState = 0;			//状態管理カウンター
bool g_bPause = false; 

//===========================================
//ゲーム画面の初期化処理
//===========================================
void InitGame(void)
{
	InitShadow();	// 影
	InitCamera();	// カメラ
	InitLight();	// ライト
	InitPlayer();	// プレイヤー
	InitBlock();	// ブロック
	InitBullet();		// 弾
	InitExplosion();	// 爆発
	InitEffect();		// エフェクト
	InitParticle();		// パーティクル
	InitGuide();		// ガイド

	g_gameState = GAMESTATE_NORMAL;	//通常状態に設定
	g_nCounterGameState = 0;		//カウンターをゼロ
	g_bPause = false;				//ポーズ解除
}

//===========================================
//ゲーム画面の終了処理
//===========================================
void UninitGame(void)
{
	UninitCamera();		//カメラ
	UninitLight();		//ライト
	UninitPlayer();		// プレイヤー
	UninitShadow();		// 影
	UninitBlock();		// ブロック
	UninitBullet();		// 弾
	UninitExplosion();	// 爆発
	UninitEffect();		// エフェクト
	UninitGuide();		// ガイド

}

//===========================================
//ゲーム画面の更新処理
//===========================================
void UpdateGame(void)
{
	if (g_bPause == true)
	{//ポーズ中
		//ポーズ中の更新処理
		UpdatePause();
	}
	else
	{//ポーズ中でなければ
		UpdatePlayer();		// プレイヤー
		UpdateCamera();		//カメラ
		UpdateLight();		//ライト
		UpdateShadow();		// 影
		UpdateBlock();		// ブロック
		UpdateBullet();		// 弾
		UpdateExplosion();	// 爆発
		UpdateEffect();		// エフェクト
		UpdateParticle();	// パーティクル
		UpdateGuide();		// ガイド

	}
	
	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_BACK) == true)
	{//ポーズキー（P）が押された
		g_bPause = g_bPause ? false : true;
	}

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(MODE_RESULT);
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://通常状態

		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	//何もしていない状態に設定
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//===========================================
//ゲーム画面の描画処理
//===========================================
void DrawGame(void)
{
	SetCamera();		// カメラ

#ifdef _DEBUG
	DrawGuide();		// ガイド
#endif

	DrawShadow();		// 影
	DrawEffect();		// エフェクト
	DrawPlayer();		// プレイヤー
	DrawBlock();		// ブロック
	DrawBullet();		// 弾
	DrawExplosion();	// 爆発


	//ポーズ中
	if (g_bPause == true)
	{
		//ポーズの描画
		DrawPause();
	}
}

//===========================================
//ゲーム状態の設定
//===========================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	g_nCounterGameState = 0;
}

//===========================================
//ゲーム状態の取得
//===========================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//===========================================
//ポーズの有効無効設定
//===========================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}