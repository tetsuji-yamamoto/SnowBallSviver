#include "polygon.h"
#include "camera.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturPolygon = NULL;		// テクスチャのポインタ
D3DXVECTOR3 g_posPlygon;							// 位置
D3DXVECTOR3 g_rotPolygon;							// 向き
D3DXMATRIX g_mtxWorldPolygon;						// ワールドマトリックス

//**************************************
// ポリゴンの初期化
//**************************************
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\test\\image.jpg",
		&g_pVtxTexturPolygon);

	// 頂点バッファをロック
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = -150.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 150.0f;

	pVtx[1].pos.x = 150.0f;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 150.0f;

	pVtx[2].pos.x = -150.0f;
	pVtx[2].pos.y = 0.0f;
	pVtx[2].pos.z = -150.0f;

	pVtx[3].pos.x = 150.0f;
	pVtx[3].pos.y = 0.0f;
	pVtx[3].pos.z = -150.0f;

	// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffPolygon->Unlock();
}

//======================================
// ポリゴンの破棄
//======================================
void UninitPolygon(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//======================================
// ポリゴンの破棄
//======================================
void UpdatePolygon(void)
{
	
}

//======================================
// ポリゴンの描画
//======================================
void DrawPolygon(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon,&g_mtxWorldPolygon,&mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posPlygon.x, g_posPlygon.y, g_posPlygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon,&g_mtxWorldPolygon,&mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	// テクスチャの設定
	pDevice->SetTexture(0, g_pVtxTexturPolygon);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}