#include "effect.h"
#include "camera.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturEffect = NULL;		// テクスチャのポインタ
EFFECT g_aEffect[MAX_EFFECT];						// エフェクト

//**************************************
// エフェクトの初期化
//**************************************
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\shadow\\shadow000.jpg",
		&g_pVtxTexturEffect);

	// 頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EFFECT; nCntEX++)
	{
		g_aEffect[nCntEX].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEX].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEX].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEX].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEX].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEX].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aEffect[nCntEX].fLife = 0.0f;
		g_aEffect[nCntEX].fsizeDiff = 0.0f;
		g_aEffect[nCntEX].bUse = false;

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
	g_pVtxBuffEffect->Unlock();
}

//*****************************
// エフェクトの破棄
//*****************************
void UninitEffect(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	// テクスチャの破棄
	if (g_pVtxTexturEffect != NULL)
	{
		g_pVtxTexturEffect->Release();
		g_pVtxTexturEffect = NULL;
	}
}

//*****************************
// エフェクトの更新
//*****************************
void UpdateEffect(void)
{

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EFFECT; nCntEX++)
	{
		if (g_aEffect[nCntEX].bUse == true)
		{
			g_aEffect[nCntEX].fLife -= 1.0f;
			
			g_aEffect[nCntEX].col.a -= g_aEffect[nCntEX].fDffAlph;

			// 頂点座標の設定
			pVtx[0].pos.x -= -g_aEffect[nCntEX].fsizeDiff;
			pVtx[0].pos.y -= g_aEffect[nCntEX].fsizeDiff;
			pVtx[0].pos.z -= 0.0f;

			pVtx[1].pos.x -= g_aEffect[nCntEX].fsizeDiff;
			pVtx[1].pos.y -= g_aEffect[nCntEX].fsizeDiff;
			pVtx[1].pos.z -= 0.0f;

			pVtx[2].pos.x -= -g_aEffect[nCntEX].fsizeDiff;
			pVtx[2].pos.y -= -g_aEffect[nCntEX].fsizeDiff;
			pVtx[2].pos.z -= 0.0f;

			pVtx[3].pos.x -= g_aEffect[nCntEX].fsizeDiff;
			pVtx[3].pos.y -= -g_aEffect[nCntEX].fsizeDiff;
			pVtx[3].pos.z -= 0.0f;

			// 頂点カラーの設定
			pVtx[0].col = g_aEffect[nCntEX].col;
			pVtx[1].col = g_aEffect[nCntEX].col;
			pVtx[2].col = g_aEffect[nCntEX].col;
			pVtx[3].col = g_aEffect[nCntEX].col;

			if (g_aEffect[nCntEX].fLife <= 0.0f)
			{
				g_aEffect[nCntEX].bUse = false;
			}
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//*****************************
// エフェクトの描画
//*****************************
void DrawEffect(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Zの比較方法
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	for (int nCntEX = 0; nCntEX < MAX_EFFECT; nCntEX++)
	{
		if (g_aEffect[nCntEX].bUse == true)
		{// 使ってたら
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCntEX].mtxWorld);

			// ビューマトリックス取得
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// カメラの逆行列を設定
			g_aEffect[nCntEX].mtxWorld._11 = mtxview._11;
			g_aEffect[nCntEX].mtxWorld._12 = mtxview._21;
			g_aEffect[nCntEX].mtxWorld._13 = mtxview._31;
			g_aEffect[nCntEX].mtxWorld._21 = mtxview._12;
			g_aEffect[nCntEX].mtxWorld._22 = mtxview._22;
			g_aEffect[nCntEX].mtxWorld._23 = mtxview._32;
			g_aEffect[nCntEX].mtxWorld._31 = mtxview._13;
			g_aEffect[nCntEX].mtxWorld._32 = mtxview._23;
			g_aEffect[nCntEX].mtxWorld._33 = mtxview._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEX].pos.x, g_aEffect[nCntEX].pos.y, g_aEffect[nCntEX].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEX].mtxWorld, &g_aEffect[nCntEX].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEX].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// テクスチャの設定
			pDevice->SetTexture(0, g_pVtxTexturEffect);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// エフェクトの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEX, 2);
		}
	}

	// アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Zの比較方法
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************************
// エフェクトの設定
//*****************************
void SetEffect(EFFECT effect)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EFFECT; nCntEX++)
	{
		if (g_aEffect[nCntEX].bUse == false)
		{
			
			g_aEffect[nCntEX] = effect;
			g_aEffect[nCntEX].bUse = true;

			// 頂点座標の設定
			pVtx[0].pos.x = -effect.size.x;
			pVtx[0].pos.y = effect.size.y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = effect.size.x;
			pVtx[1].pos.y = effect.size.y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -effect.size.x;
			pVtx[2].pos.y = -effect.size.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = effect.size.x;
			pVtx[3].pos.y = -effect.size.y;
			pVtx[3].pos.z = 0.0f;

			// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 頂点カラーの設定
			pVtx[0].col = g_aEffect[nCntEX].col;
			pVtx[1].col = g_aEffect[nCntEX].col;
			pVtx[2].col = g_aEffect[nCntEX].col;
			pVtx[3].col = g_aEffect[nCntEX].col;

			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}