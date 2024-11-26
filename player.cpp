#include "player.h"
#include "keyboard.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "particle.h"
#include "joypad.h"
#include "block.h"
#include "wall.h"

// グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTexturePlayer[6] = {};		// テクスチャへのポンタ
LPD3DXMESH g_pMeshPlayer = NULL;					// メッシュ(頂点情報へのポインタ)
LPD3DXBUFFER g_pBuffMatPlayer = NULL;				// マテリアルへのポインタ
DWORD g_dwNumMatPlayer = 0;							// マテリアルの数
D3DXMATRIX g_mtxWorldPlayer;						// ワールドマトリックス
PLAYER g_player;	// プレイヤー情報
int nIdxShadow = 0;

//************************************************
// プレイヤー初期化
//************************************************
void InitPlayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// プレイヤー情報初期化
	
	// 各種変数の初期化
	g_player.pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);		// 位置
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目的向き
	g_player.bMove = false;		// 動くかどうか

	// Xファイルの読み込み
	D3DXLoadMeshFromX("date\\xfile\\player\\testPlayer_002.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	//マテリアルデータへのポインタを取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// テクスチャファイルが存在する

			// このファイル名を使用してテクスチャを読み込む
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTexturePlayer[nCntMat]);
		}
	}

	// 影の設定
	SetShadw(g_player.pos, g_player.rot);
}

//************************************************
// プレイヤーの終了
//************************************************
void UninitPlayer(void)
{
	// メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	// マテリアルの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}

	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}
}

//************************************************
// プレイヤーの更新
//************************************************
void UpdatePlayer(void)
{
	Camera* pCamera = GetCamera();				// カメラの取得
	XINPUT_STATE* pJoypad = GetJoypadState();	// コントローラー情報取得
	g_player.bMove = false;	// 動かないよ	

	// キー操作
	if (KeyboardRepeat(DIK_W))
	{// 前移動
		g_player.bMove = true;	// 動くよ

		if (KeyboardRepeat(DIK_A))
		{// 左移動
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;	// 目的の角度を設定
		}
		else if (KeyboardRepeat(DIK_D))
		{// 右移動		
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;	// 目的の角度を設定
		}
		else
		{
			g_player.rotDest.y = pCamera->rot.y;	// 目的の角度を設定
		}
	}
	else if (KeyboardRepeat(DIK_S))
	{// 後ろ移動
		g_player.bMove = true;	// 動くよ
		if (KeyboardRepeat(DIK_A))
		{// 左移動
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;	// 目的の角度を設定
		}
		else if (KeyboardRepeat(DIK_D))
		{// 右移動		
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;	// 目的の角度を設定
		}
		else
		{
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI;	// 目的の角度を設定
		}
	}
	else if (KeyboardRepeat(DIK_A))
	{// 左移動
		g_player.bMove = true;	// 動くよ

		g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;	// 目的の角度を設定
	}
	else if (KeyboardRepeat(DIK_D))
	{// 右移動		
		g_player.bMove = true;	// 動くよ

		g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;	// 目的の角度を設定
	}

	// コントローラー操作
	if (GetJoyStickL())
	{// 左スティック
		g_player.bMove = true;	// 動くよ
		// 目的の角度を算出
		g_player.rotDest.y = pCamera->rot.y + atan2f(pJoypad->Gamepad.sThumbLX, pJoypad->Gamepad.sThumbLY);
	}

	if (KeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A))
	{// Aジャンプ
		if (g_player.bJanp == false)
		{// ジャンプしてなかったら
			g_player.move.y = 8.0f;
			g_player.bJanp = true;	// ジャンプ状態
		}
	}

	if (g_player.rotDest.y > D3DX_PI)
	{
		g_player.rotDest.y = -D3DX_PI + (g_player.rotDest.y - D3DX_PI);
	}
	else if (g_player.rotDest.y < -D3DX_PI)
	{
		g_player.rotDest.y = D3DX_PI + (g_player.rotDest.y + D3DX_PI);
	}

	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y = -D3DX_PI + (g_player.rot.y - D3DX_PI);
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y = D3DX_PI + (g_player.rot.y + D3DX_PI);
	}

	if (g_player.bMove == true)
	{
		g_player.move.x = sinf(g_player.rotDest.y) * PLAYER_MOVE;
		g_player.move.z = cosf(g_player.rotDest.y) * PLAYER_MOVE;
	}

	// モデルの角度を目的の角度に近づける

	float fDiff = g_player.rotDest.y - g_player.rot.y;

	if (fDiff > D3DX_PI)
	{
		fDiff = fDiff - D3DX_PI * 2;
	}
	else if (fDiff < -D3DX_PI)
	{
		fDiff = fDiff + D3DX_PI * 2;
	}
	g_player.rot.y += (fDiff) * 0.1f;

	// 古い位置を更新
	g_player.posOld.x = g_player.pos.x;
	g_player.posOld.y = g_player.pos.y;
	g_player.posOld.z = g_player.pos.z;

	if (g_player.bJanp == true)
	{
		g_player.move.y -= PLAYER_GRAVITY;
	}

	// 慣性
	g_player.move.x += (0 - g_player.move.x) * 0.3f;
	g_player.move.z += (0 - g_player.move.z) * 0.3f;


	// 移動量追加
	g_player.pos.x += g_player.move.x;
	CollisionBlock();	// 当たり判定

	g_player.pos.y += g_player.move.y;
	g_player.bJanp = !CollisionBlock();	// 当たり判定

	g_player.pos.z += g_player.move.z;
	CollisionBlock();	// 当たり判定

	CollisionWall();	// 壁の当たり判定

	if (g_player.pos.y <= 0.0f)
	{// 地面突いたら
		g_player.pos.y = 0.0f;
		g_player.bJanp = false;	// ジャンプしてないよ
	}

	if (KeyboardTrigger(DIK_V) || GetJoypadTrigger(JOYKEY_X))
	{// 弾発射

		// 弾設定
		SETBULLET setBlt;

		// 情報代入
		setBlt.pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 10.0f, g_player.pos.z);
		setBlt.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		setBlt.type = BULLETTYPE_SNOW;
		setBlt.fLife = 120.0f;

		//float fX = (float)BULLET_MAX_DISTANCE / 2.0f;
		//float fY = (float)BULLET_MAX_DISTANCE / (float)BULLET_SPEED;	// 放物線のてっぺん
		//float fAngle = atan2f(fX, fY);

		setBlt.dir.x = pCamera->rot.x + D3DX_PI;
		setBlt.dir.y = g_player.rotDest.y;
		setBlt.dir.z = g_player.rotDest.z;
		//setBlt.dir.x = D3DX_PI*0.5f;

		// 引数にぶち込んでセットする
		SetBullet(setBlt);

		//// パーティクル設定
		//PARTICLE particle;

		//// 情報入力
		//particle.effect.pos = g_player.pos;
		//particle.effect.col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		//particle.effect.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		//particle.effect.dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//particle.effect.col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		//particle.effect.fDffAlph = 0.01f;
		//particle.effect.fLife = 120.0f;
		//particle.effect.fsizeDiff = 0.01f;
		//SetParticle(particle);
	}
	else if (KeyboardTrigger(DIK_B) || GetJoypadTrigger(JOYKEY_Y))
	{// 氷玉発射
		// 弾設定
		SETBULLET setBlt;

		// 情報代入
		setBlt.pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 10.0f, g_player.pos.z);
		setBlt.dir.x = pCamera->rot.x + D3DX_PI;
		setBlt.dir.y = g_player.rotDest.y;
		setBlt.dir.z = g_player.rotDest.z;
		setBlt.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		setBlt.type = BULLETTYPE_ICE;
		setBlt.fLife = 60.0f;

		// 引数にぶち込んでセットする
		SetBullet(setBlt);

	}
	else if (KeyboardTrigger(DIK_N) || GetJoypadTrigger(JOYKEY_B))
	{// 砂利玉発射
		// 弾設定
		SETBULLET setBlt;

		// 情報代入
		setBlt.pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 10.0f, g_player.pos.z);
		setBlt.dir.x = pCamera->rot.x + D3DX_PI;
		setBlt.dir.y = g_player.rotDest.y;
		setBlt.dir.z = g_player.rotDest.z;
		setBlt.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		setBlt.type = BULLETTYPE_GRAVEL;
		setBlt.fLife = 90.0f;

		// 引数にぶち込んでセットする
		SetBullet(setBlt);

	}

	// 影の更新
	SetPositionShadow(0, g_player.pos);
	
}

//************************************************
// プレイヤーの表示
//************************************************
void DrawPlayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);

		// モデル(パーツの描画)
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);


}

//************************************************
// プレイヤーの取得
//************************************************
PLAYER* GetPlayer(void)
{
	return &g_player;
}