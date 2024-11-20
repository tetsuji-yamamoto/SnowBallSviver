#include "meshfield.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturMeshField = NULL;	// テクスチャのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	// インデックスへのポインタ
D3DXVECTOR3 g_posMeshField;							// 位置
D3DXVECTOR3 g_rotMeshField;							// 向き
D3DXMATRIX g_mtxWorldMeshField;						// ワールドマトリックス

//**************************************
// メッシュフィールドの初期化
//**************************************
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESH_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\test\\image.jpg",
		&g_pVtxTexturMeshField);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESH_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	// 頂点バッファをロック
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	int a = MESH_PLYGON_AII;
	int b = MESH_VERTEX;
	int c = MESH_INDEX;

	float fX = (float)FIELD_X / (float)MESH_X;
	float fZ = (float)FIELD_Z / (float)MESH_Z;

	float fposX = 0.0f;
	float fposZ = 0.0f;

	float fTexX = 1.0f / (float)MESH_X;
	float fTexY = 1.0f / (float)MESH_Z;

	int nCnt = 0;
	int nIndex = 0;
	int nCntVtx = 0;

	D3DXVECTOR3 aaa[MESH_VERTEX] = {};
	D3DXVECTOR2 ccc[MESH_VERTEX] = {};
	int bbb[MESH_VERTEX] = {};

	for (int nCntZ = 0; nCntZ <= MESH_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= MESH_X; nCntX++)
		{
			fposX = fX * nCntX;
			fposZ = -fZ * nCntZ;

			aaa[nCntVtx].x = fposX;
			aaa[nCntVtx].z = fposZ;

			bbb[nCntVtx] = nCntVtx;

			ccc[nCntVtx].x = fTexX * nCntX;
			ccc[nCntVtx].y = fTexY * nCntZ;

			// 頂点座標の設定
			pVtx[nCntVtx].pos.x = fposX;
			pVtx[nCntVtx].pos.z = fposZ;

			// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[nCntVtx].tex.x = fTexX * nCntX;
			pVtx[nCntVtx].tex.y = fTexY * nCntZ;

			nCntVtx++;
		}
	}

	int i = 0;

	//for (int nCnt = 0; nCnt < MESH_X + 1; nCnt++)
	//{
	//	for (int nCntX = 0; nCntX < MESH_X + 1; nCntX++)
	//	{
	//		fposX = -fX + fX * nCnt;
	//		fTexX = 0.0f + fColX * nCnt;
	//		nIndex = nCntX * (MESH_Z + 1) + 1 * nCnt;

	//		// 頂点座標の設定
	//		pVtx[nIndex].pos.x = fposX;

	//		// テクスチャ座標の設定
	//		pVtx[nIndex].tex.x = fTexX;
	//	}
	//}

	//for (int nCnt = 0; nCnt < MESH_Z + 1; nCnt++)
	//{
	//	for (int nCntZ = 0; nCntZ < MESH_Z + 1; nCntZ++)
	//	{
	//		fposZ = fX - fX * nCnt;
	//		fTexY = 0.0f + fColZ * nCnt;
	//		nIndex = nCntZ + (MESH_Z + 1) * nCnt;

	//		// 頂点座標の設定
	//		pVtx[nIndex].pos.z = fposZ;

	//		// テクスチャ座標の設定
	//		pVtx[nIndex].tex.y = fTexY;
	//	}
	//}

	//for (int nCnt = 0; nCnt < MESH_VERTEX; nCnt++)
	//{
	//	// 頂点座標の設定
	//	pVtx[nCnt].pos.y = 0.0f;

	//	// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
	//	pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//	// 頂点カラーの設定
	//	pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//}
		// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
		//pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	
		// 頂点カラーの設定
		//pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		// テクスチャ座標の設定
		//pVtx[nCnt].tex = D3DXVECTOR2(0.0f, 0.0f);

	//// 頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
	//pVtx[2].pos = D3DXVECTOR3(150.0f, 0.0f, 150.0f);
	//pVtx[3].pos = D3DXVECTOR3(-150.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	//pVtx[8].pos = D3DXVECTOR3(150.0f, 0.0f, -150.0f);w

	//// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
	//pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//// 頂点カラーの設定
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	//pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffMeshField->Unlock();

	// インデックスバッファをロック
	WORD* pIdx;
	g_pIdxBuffMeshField->Lock(0,0,(void**)&pIdx,0);

	int naIdxB[MESH_INDEX];// インデックス格納用

	int nVtx = 0;
	int nIdxA = MESH_X + 1;	// 左側インデックス
	int nIdxB = 0;		// 右側インデックス

	for (int nCntA = 0; nCntA < MESH_Z; nCntA++)
	{
		for (int nCntB = 0; nCntB <= MESH_X; nCntB++)
		{
			pIdx[nVtx] = nIdxA;
			nVtx++;
			pIdx[nVtx] = nIdxB;
			nVtx++;
			nIdxA++;
			nIdxB++;
		}
		pIdx[nVtx] = nIdxB - 1;
		nVtx++;
		pIdx[nVtx] = nIdxA;
		nVtx++;

	}

	int z = 0;
	int nCntNum = 0;
	int nCntIdx = 0;

	//// 右側インデックス
	//for (nCnt = 0; nCnt < MESH_INDEX / 2; nCnt++)
	//{
	//		nCntNum++;

	//	if (nCntNum > MESH_X + 1)
	//	{
	//		naIdxB[nCnt] = nCnt + MESH_X + 1;
	//		nCntNum = 0;
	//	}
	//	else
	//	{
	//		naIdxB[nCnt] = nCntIdx;
	//		nCntIdx++;
	//	}
	//	// 完成品ぶち込む
	//	pIdx[nCnt + nCnt + 1] = naIdxB[nCnt];
	//}

	//nCntNum = 0;
	//nCntIdx = MESH_X + 1;

	//// 左側インデックス
	//for (nCnt = 0; nCnt < MESH_INDEX / 2; nCnt++)
	//{
	//	nCntNum++;

	//	if (nCntNum > MESH_X + 1)
	//	{
	//		naIdxB[nCnt] = nCntIdx - (MESH_X + 2);
	//		nCntNum = 0;
	//	}
	//	else
	//	{
	//		naIdxB[nCnt] = nCntIdx;
	//		nCntIdx++;
	//	}

	//	// インデックスの設定
	//	pIdx[nCnt + nCnt] = naIdxB[nCnt];
	//}

	// インデックスバッファのアンロック
	g_pIdxBuffMeshField->Unlock();
}

//*******************************************
// メッシュフィールドの破棄
//*******************************************
void UninitMeshField(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// テクスチャの破棄
	if (g_pVtxTexturMeshField != NULL)
	{
		g_pVtxTexturMeshField->Release();
		g_pVtxTexturMeshField = NULL;
	}

	// インデックスバッファの解放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//*******************************************
// メッシュフィールドの破棄
//*******************************************
void UpdateMeshField(void)
{

}

//*******************************************
// メッシュフィールドの描画
//*******************************************
void DrawMeshField(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pVtxTexturMeshField);
	
	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,MESH_VERTEX,0,MESH_PLYGON_AII);
}