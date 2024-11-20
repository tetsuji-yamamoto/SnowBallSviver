#include "wall.h"
#include "camera.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturWall = NULL;		// テクスチャのポインタ
WALL g_aWall[MAX_WALL];							// 壁情報

//**************************************
// 壁の初期化
//**************************************
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\wall\\wall000.jpg",
		&g_pVtxTexturWall);

	// 頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aWall[nCntWall].size = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aWall[nCntWall].col = D3DXCOLOR(1.0f,1.0f, 1.0f,1.0f);
		g_aWall[nCntWall].bFaB = false;	// 表裏(表)
		g_aWall[nCntWall].bUse = false;

		// 頂点座標の設定
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f;

		// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffWall->Unlock();

	// 壁設定
	SetWall(D3DXVECTOR3(0.0f, 50.0f, 150.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 50.0f, 150.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetWall(D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetWall(D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f + D3DX_PI, 0.0f));

	SetWall(D3DXVECTOR3(-150.0f, 50.0f, 0.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	SetWall(D3DXVECTOR3(-150.0f, 50.0f, 0.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f + D3DX_PI, 0.0f));

	SetWall(D3DXVECTOR3(0.0f, 50.0f, -150.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 50.0f, -150.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, D3DX_PI + D3DX_PI, 0.0f));

}

//**************************************
// 壁の破棄
//**************************************
void UninitWall(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	// テクスチャの破棄
	if (g_pVtxTexturWall != NULL)
	{
		g_pVtxTexturWall->Release();
		g_pVtxTexturWall = NULL;
	}
}

//**************************************
// 壁の更新
//**************************************
void UpdateWall(void)
{
	Camera* pCamera = GetCamera();	// カメラ取得

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//float fAngle = atan2f((g_aWall[nCntWall].pos.x - pCamera->posV.x), (g_aWall[nCntWall].pos.z - pCamera->posV.z));
			//float fDiff = g_aWall[nCntWall].rot.y - fAngle;

			//// 差分調整
			//if (fDiff > D3DX_PI)
			//{
			//	//fDiff = fDiff - D3DX_PI * 2.0f;
			//}
			//else if (fDiff < -D3DX_PI)
			//{
			//	//fDiff = fDiff + D3DX_PI * 2.0f;
			//}

			//// 裏側言ったら
			//if (fDiff < -D3DX_PI * 0.5f || fDiff > D3DX_PI * 0.5f)
			//{
			//	g_aWall[nCntWall].rot.y += D3DX_PI;
			//	g_aWall[nCntWall].bFaB = !g_aWall[nCntWall].bFaB;	// 表裏切り替える
			//}

			//// 静菌
			//if (g_aWall[nCntWall].rot.y > D3DX_PI)
			//{
			//	g_aWall[nCntWall].rot.y = -D3DX_PI + (g_aWall[nCntWall].rot.y - D3DX_PI);
			//}
			//else if (g_aWall[nCntWall].rot.y < -D3DX_PI)
			//{
			//	g_aWall[nCntWall].rot.y = D3DX_PI + (g_aWall[nCntWall].rot.y + D3DX_PI);
			//}

			//
			//if (g_aWall[nCntWall].bFaB == true)
			//{// 裏側見ちゃったら
			//	//// 頂点カラーの設定
			//	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			//	//// テクスチャ座標の設定
			//	//pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			//	//pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
			//	//pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
			//	//pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
			//}
			//else if (g_aWall[nCntWall].bFaB == false)
			//{// 表側見たら
			//	//// 頂点カラーの設定
			//	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			//	//// テクスチャ座標の設定
			//	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			//	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			//}
		}

		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffWall->Unlock();
}

//**************************************
// 壁の描画
//**************************************
void DrawWall(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// テクスチャの設定
			pDevice->SetTexture(0, g_pVtxTexturWall);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// 壁の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntWall, 2);
		}
	}
}

//**************************************
// 壁の設定
//**************************************
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 rot)
{
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].size = size;
			g_aWall[nCntWall].col = col;
			g_aWall[nCntWall].bUse = true;

			// 頂点座標の設定
			pVtx[0].pos.x = -g_aWall[nCntWall].size.x;
			pVtx[0].pos.y = g_aWall[nCntWall].size.y;
			pVtx[0].pos.z = g_aWall[nCntWall].size.z;

			pVtx[1].pos.x = g_aWall[nCntWall].size.x;
			pVtx[1].pos.y = g_aWall[nCntWall].size.y;
			pVtx[1].pos.z = g_aWall[nCntWall].size.z;

			pVtx[2].pos.x = -g_aWall[nCntWall].size.x;
			pVtx[2].pos.y = -g_aWall[nCntWall].size.y;
			pVtx[2].pos.z = -g_aWall[nCntWall].size.z;

			pVtx[3].pos.x = g_aWall[nCntWall].size.x;
			pVtx[3].pos.y = -g_aWall[nCntWall].size.y;
			pVtx[3].pos.z = -g_aWall[nCntWall].size.z;

			// 頂点カラーの設定
			pVtx[0].col = g_aWall[nCntWall].col;
			pVtx[1].col = g_aWall[nCntWall].col;
			pVtx[2].col = g_aWall[nCntWall].col;
			pVtx[3].col = g_aWall[nCntWall].col;
			break;
		}

		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffWall->Unlock();
}