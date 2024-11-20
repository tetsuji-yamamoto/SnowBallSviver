#include "main.h"

// グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureModel[6] = {};	// テクスチャへのポンタ
LPD3DXMESH g_pMeshModel = NULL;					// メッシュ(頂点情報へのポインタ)
LPD3DXBUFFER g_pBuffMatModel = NULL;			// マテリアルへのポインタ
DWORD g_dwNumMatModel = 0;						// マテリアルの数
D3DXVECTOR3 g_posModel;							// 位置
D3DXVECTOR3 g_rotModel;							// 向き
D3DXMATRIX g_mtxWorldModel;						// ワールドマトリックス

//********************************************
//モデルの初期化
//********************************************
void InitModel(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 各種変数の初期化
	g_posModel = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotModel = D3DXVECTOR3(0.0f,0.0f,0.0f);

	// Xファイルの読み込み
	D3DXLoadMeshFromX("date\\xfile\\TestBox.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_dwNumMatModel,
		&g_pMeshModel);

	//マテリアルデータへのポインタを取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// テクスチャファイルが存在する

			// このファイル名を使用してテクスチャを読み込む
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureModel[nCntMat]);
		}
	}
}

//********************************************
// モデルの終了処理
//********************************************
void UninitModel(void)
{
	// メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	// マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}

	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}
	
}

//********************************************
// モデルの更新
//********************************************
void UpdateModel(void)
{

}

//********************************************
// モデルの描画
//********************************************
void DrawModel(void)
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
	D3DXMatrixIdentity(&g_mtxWorldModel);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

		// モデル(パーツの描画)
		g_pMeshModel->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}