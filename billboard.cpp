#include "billboard.h"
#include "camera.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturBillboard = NULL;	// テクスチャのポインタ
Billboard g_aBillboard[MAX_BLBD];								// ビルボード

//**************************************
// ビルボードの初期化
//**************************************
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BLBD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\billboard\\bullet000.png",
		&g_pVtxTexturBillboard);

	// 頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BLBD; nCntBl++)
	{
		g_aBillboard[nCntBl].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_aBillboard[nCntBl].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBl].bUse = false;

		// 頂点座標の設定
		pVtx[0].pos.x = -20.0f;
		pVtx[0].pos.y = 20.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 20.0f;
		pVtx[1].pos.y = 20.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -20.0f;
		pVtx[2].pos.y = -20.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 20.0f;
		pVtx[3].pos.y = -20.0f;
		pVtx[3].pos.z = 0.0f;

		// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//*****************************
// ビルボードの破棄
//*****************************
void UninitBillboard(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	// テクスチャの破棄
	if (g_pVtxTexturBillboard != NULL)
	{
		g_pVtxTexturBillboard->Release();
		g_pVtxTexturBillboard = NULL;
	}
}

//*****************************
// ビルボードの更新
//*****************************
void UpdateBillboard(void)
{

}

//*****************************
// ビルボードの描画
//*****************************
void DrawBillboard(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBl = 0; nCntBl < MAX_BLBD; nCntBl++)
	{
		if (g_aBillboard[nCntBl].bUse == true)
		{// 使ってたら
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBillboard[nCntBl].mtxWorld);

			// ビューマトリックス取得
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// カメラの逆行列を設定
			g_aBillboard[nCntBl].mtxWorld._11 = mtxview._11;
			g_aBillboard[nCntBl].mtxWorld._12 = mtxview._21;
			g_aBillboard[nCntBl].mtxWorld._13 = mtxview._31;
			g_aBillboard[nCntBl].mtxWorld._21 = mtxview._12;
			g_aBillboard[nCntBl].mtxWorld._22 = mtxview._22;
			g_aBillboard[nCntBl].mtxWorld._23 = mtxview._32;
			g_aBillboard[nCntBl].mtxWorld._31 = mtxview._13;
			g_aBillboard[nCntBl].mtxWorld._32 = mtxview._23;
			g_aBillboard[nCntBl].mtxWorld._33 = mtxview._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBl].pos.x, g_aBillboard[nCntBl].pos.y, g_aBillboard[nCntBl].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCntBl].mtxWorld, &g_aBillboard[nCntBl].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBl].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// テクスチャの設定
			pDevice->SetTexture(0, g_pVtxTexturBillboard);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ビルボードの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBl, 2);
		}
	}

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//*****************************
// ビルボードの設定
//*****************************
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BLBD; nCntBl++)
	{
		if (g_aBillboard[nCntBl].bUse == false)
		{
			g_aBillboard[nCntBl].pos = pos;
			g_aBillboard[nCntBl].bUse = true;

			// 頂点座標の設定
			pVtx[0].pos.x = -size.x;
			pVtx[0].pos.y = size.y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = size.x;
			pVtx[1].pos.y = size.y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -size.x;
			pVtx[2].pos.y = -size.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = size.x;
			pVtx[3].pos.y = -size.y;
			pVtx[3].pos.z = 0.0f;

			// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffBillboard->Unlock();
}