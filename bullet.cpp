#include "bullet.h"
#include "camera.h"
#include "explosion.h"
#include "effect.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturBullet = NULL;		// テクスチャのポインタ
BULLET g_aBullet[MAX_BULLET];						// 弾

//**************************************
// 弾の初期化
//**************************************
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\billboard\\bullet000.png",
		&g_pVtxTexturBullet);

	// 頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		g_aBullet[nCntBl].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_aBullet[nCntBl].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].bUse = false;

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
	g_pVtxBuffBullet->Unlock();
}

//*****************************
// 弾の破棄
//*****************************
void UninitBullet(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	// テクスチャの破棄
	if (g_pVtxTexturBullet != NULL)
	{
		g_pVtxTexturBullet->Release();
		g_pVtxTexturBullet = NULL;
	}
}

//*****************************
// 弾の更新
//*****************************
void UpdateBullet(void)
{
	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (g_aBullet[nCntBl].bUse == true)
		{

			g_aBullet[nCntBl].pos.x += sinf(g_aBullet[nCntBl].dir.y) * 1.0f;
			g_aBullet[nCntBl].pos.z += cosf(g_aBullet[nCntBl].dir.y) * 1.0f;
			g_aBullet[nCntBl].fLife -= 1.0f;

			if (g_aBullet[nCntBl].fLife <= 0.0f)
			{
				g_aBullet[nCntBl].bUse = false;
				// 爆発設定
				SETEXPLO setExplo;
				setExplo.pos = g_aBullet[nCntBl].pos;
				setExplo.size = D3DXVECTOR3(20.0f,20.0f,0.0f);

				SetExplosion(setExplo);
			}

			// エフェクト出現
			EFFECT setEffect;
			setEffect.pos = g_aBullet[nCntBl].pos;
			setEffect.col = D3DXCOLOR(1.0f,0.3f,0.3f,1.0f);
			setEffect.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
			setEffect.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			setEffect.dir= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			setEffect.fDffAlph = 0.01f;
			setEffect.fLife = 120.0f;
			setEffect.fsizeDiff = 0.01f;

			SetEffect(setEffect);
		}
	}
}

//*****************************
// 弾の描画
//*****************************
void DrawBullet(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,254);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (g_aBullet[nCntBl].bUse == true)
		{// 使ってたら
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCntBl].mtxWorld);

			// ビューマトリックス取得
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// カメラの逆行列を設定
			g_aBullet[nCntBl].mtxWorld._11 = mtxview._11;
			g_aBullet[nCntBl].mtxWorld._12 = mtxview._21;
			g_aBullet[nCntBl].mtxWorld._13 = mtxview._31;
			g_aBullet[nCntBl].mtxWorld._21 = mtxview._12;
			g_aBullet[nCntBl].mtxWorld._22 = mtxview._22;
			g_aBullet[nCntBl].mtxWorld._23 = mtxview._32;
			g_aBullet[nCntBl].mtxWorld._31 = mtxview._13;
			g_aBullet[nCntBl].mtxWorld._32 = mtxview._23;
			g_aBullet[nCntBl].mtxWorld._33 = mtxview._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBl].pos.x, g_aBullet[nCntBl].pos.y, g_aBullet[nCntBl].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBl].mtxWorld, &g_aBullet[nCntBl].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBl].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// テクスチャの設定
			pDevice->SetTexture(0, g_pVtxTexturBullet);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// 弾の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBl, 2);
		}
	}

	// アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//*****************************
// 弾の設定
//*****************************
void SetBullet(SETBULLET setBlt)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (g_aBullet[nCntBl].bUse == false)
		{
			g_aBullet[nCntBl].pos = setBlt.pos;
			g_aBullet[nCntBl].dir = setBlt.dir;
			g_aBullet[nCntBl].fLife = setBlt.fLife;
			g_aBullet[nCntBl].bUse = true;

			// 頂点座標の設定
			pVtx[0].pos.x = -setBlt.size.x;
			pVtx[0].pos.y = setBlt.size.y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = setBlt.size.x;
			pVtx[1].pos.y = setBlt.size.y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -setBlt.size.x;
			pVtx[2].pos.y = -setBlt.size.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = setBlt.size.x;
			pVtx[3].pos.y = -setBlt.size.y;
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
	g_pVtxBuffBullet->Unlock();
}