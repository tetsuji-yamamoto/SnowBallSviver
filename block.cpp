#include "block.h"
#include "player.h"
#include "readtext.h"
#include "writetext.h"
#include "keyboard.h"
#include "edit.h"

// グローバル変数宣言
BLOCK g_aBlock[MAX_BLOCK];		// ブロック情報
BLOCKMANAGER g_blockManager;	// ブロック管理
BLOCKCONTROLLER g_blockCont;	// ブロック操作情報

//********************************************
//ブロックの初期化
//********************************************
void InitBlock(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ブロック管理情報初期化
	g_blockManager.nBlockNum = 0;

	// ブロック捜査情報初期化	
	g_blockCont.nCntNowBlock = 0;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// 各種変数の初期化
		g_aBlock[nCntBlock].apTextureBlock[0] = {};
		g_aBlock[nCntBlock].pMeshBlock = NULL;
		g_aBlock[nCntBlock].pBuffMatBlock = NULL;
		g_aBlock[nCntBlock].dwNumMatBlock = 0;
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f ,0.0f, 0.0f);
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].vtxMaxBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].vtxMinBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nType = BLOCKTYPE_MAX;
		g_aBlock[nCntBlock].bUse = false;
	}

	ReadText();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			int nNumVtx;	// 頂点数
			WORD sizeFVF;	// 頂点フォーマットのサイズデータ
			BYTE* pVtxBuff;// 頂点バッファのポインタ
			// 頂点数の取得
			nNumVtx = g_aBlock[nCntBlock].pMeshBlock->GetNumVertices();

			// 頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_aBlock[nCntBlock].pMeshBlock->GetFVF());

			// 頂点バッファのロック
			g_aBlock[nCntBlock].pMeshBlock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
			{
				// 頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
				//[頂点座標を比較してモデルの最大最小を取得]

				if (g_aBlock[nCntBlock].vtxMaxBlock.x <= vtx.x)
				{// 最大値X
					g_aBlock[nCntBlock].vtxMaxBlock.x = vtx.x;
				}

				if (g_aBlock[nCntBlock].vtxMaxBlock.y <= vtx.y)
				{// 最大値Y
					g_aBlock[nCntBlock].vtxMaxBlock.y = vtx.y;
				}

				if (g_aBlock[nCntBlock].vtxMaxBlock.z <= vtx.z)
				{// 最大値Z
					g_aBlock[nCntBlock].vtxMaxBlock.z = vtx.z;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.x >= vtx.x)
				{// 最小値X
					g_aBlock[nCntBlock].vtxMinBlock.x = vtx.x;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.y >= vtx.y)
				{// 最小値Y
					g_aBlock[nCntBlock].vtxMinBlock.y = vtx.y;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.z >= vtx.z)
				{// 最小値Z
					g_aBlock[nCntBlock].vtxMinBlock.z = vtx.z;
				}

				// 頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}

			// 頂点バッファのアンロック
			g_aBlock[nCntBlock].pMeshBlock->UnlockVertexBuffer();
		}
	}
}

//********************************************
// ブロックの終了処理
//********************************************
void UninitBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// メッシュの破棄
		if (g_aBlock[nCntBlock].pMeshBlock != NULL)
		{
			g_aBlock[nCntBlock].pMeshBlock->Release();
			g_aBlock[nCntBlock].pMeshBlock = NULL;
		}

		// マテリアルの破棄
		if (g_aBlock[nCntBlock].pBuffMatBlock != NULL)
		{
			g_aBlock[nCntBlock].pBuffMatBlock->Release();
			g_aBlock[nCntBlock].pBuffMatBlock = NULL;
		}

		//メッシュの破棄
		if (g_aBlock[nCntBlock].pMeshBlock != NULL)
		{
			g_aBlock[nCntBlock].pMeshBlock->Release();
			g_aBlock[nCntBlock].pMeshBlock = NULL;
		}
	}
}

//********************************************
// ブロックの更新
//********************************************
void UpdateBlock(void)
{
	if (GetEditMode() == EDITMODE_GAME)
	{// エディターゲームモードだったら
		BlockControllre();	// ブロック操作
	}

	if (KeyboardTrigger(DIK_DELETE))
	{
		BlockOllDeliete();
		InitBlock();
	}
}

//********************************************
// ブロックの描画
//********************************************
void DrawBlock(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{// 使っていたら

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBlock[nCntBlock].mtxWorld);

			if (g_blockCont.nCntNowBlock == nCntBlock)
			{// 
				g_aBlock[nCntBlock].mtxWorld.m[0][0] = 0.5f;
			}

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBlock[nCntBlock].rot.y, g_aBlock[nCntBlock].rot.x, g_aBlock[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBlock[nCntBlock].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].pBuffMatBlock->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].dwNumMatBlock; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat->MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_aBlock[nCntBlock].apTextureBlock[nCntMat]);

				// ブロック(パーツの描画)
				g_aBlock[nCntBlock].pMeshBlock->DrawSubset(nCntMat);
			}

			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//********************************************
// ブロックの設定
//********************************************
void SetBlock(SETBLOCK setBlock)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{// 使ってなかったら
			// 変数の設定
			g_aBlock[nCntBlock].pos = setBlock.pos;
			g_aBlock[nCntBlock].rot = setBlock.rot;
			g_aBlock[nCntBlock].nType = setBlock.nType;
			g_aBlock[nCntBlock].pFilename = &setBlock.astr[0];
			g_aBlock[nCntBlock].bUse = true;

			for (int nCnt = 0; nCnt < 256; nCnt++)
			{
				g_aBlock[nCntBlock].astr[nCnt] = setBlock.astr[nCnt];
				if (setBlock.astr[nCnt] == '\n')
				{
					break;
				}
			}

			g_blockManager.nBlockNum++;	// ブロックカウント

			// Xファイルの読み込み
			D3DXLoadMeshFromX(g_aBlock[nCntBlock].pFilename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aBlock[nCntBlock].pBuffMatBlock,
				NULL,
				&g_aBlock[nCntBlock].dwNumMatBlock,
				&g_aBlock[nCntBlock].pMeshBlock);

			//マテリアルデータへのポインタを取得
			D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].pBuffMatBlock->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].dwNumMatBlock; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{// テクスチャファイルが存在する

					// このファイル名を使用してテクスチャを読み込む
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_aBlock[nCntBlock].apTextureBlock[nCntMat]);
				}
			}

			break;
		}
	}
}

//********************************************
// ブロックの当たり判定
//********************************************
bool CollisionBlock(void)
{
	PLAYER* pPlayer = GetPlayer();	// プレイヤー取得

	bool bRanding = false;
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPlayer->pos.y + pPlayer->vtxMinPlayer.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
				pPlayer->pos.y + pPlayer->vtxMaxPlayer.y > g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
			{// 上下以内
				// X上下のめり込み判定
				if (pPlayer->pos.x + pPlayer->vtxMinPlayer.x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
					pPlayer->pos.x + pPlayer->vtxMaxPlayer.x > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
				{// Xの幅
					if (pPlayer->posOld.z + pPlayer->vtxMaxPlayer.z <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z &&
						pPlayer->pos.z + pPlayer->vtxMaxPlayer.z > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
					{// Zが手前から奥にめり込んだ
						pPlayer->pos.z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z + pPlayer->vtxMinPlayer.z;
					}
					else if (pPlayer->posOld.z + pPlayer->vtxMinPlayer.z >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
						pPlayer->pos.z + pPlayer->vtxMinPlayer.z < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z)
					{// Zが奥から手前にめり込んだ
						pPlayer->pos.z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z + pPlayer->vtxMaxPlayer.z;
					}
				}

				// Yの当たり判定
				if (pPlayer->pos.x + pPlayer->vtxMinPlayer.x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
					pPlayer->pos.x + pPlayer->vtxMaxPlayer.x >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
					pPlayer->pos.z + pPlayer->vtxMinPlayer.z <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
					pPlayer->pos.z + pPlayer->vtxMaxPlayer.z >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
				{// Xの幅内Zの幅内
					if (pPlayer->posOld.y + pPlayer->vtxMinPlayer.y >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
						pPlayer->pos.y + pPlayer->vtxMinPlayer.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y)
					{// 上から下
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y - pPlayer->vtxMinPlayer.y;
						pPlayer->move.y = 0.0f;
						bRanding = true;
					}
					else if (pPlayer->posOld.y + pPlayer->vtxMaxPlayer.y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y &&
						pPlayer->pos.y + pPlayer->vtxMaxPlayer.y > g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
					{// 下から上
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y - pPlayer->vtxMaxPlayer.y;
						pPlayer->move.y = 0.0f;
					}
				}

				// Z左右のめり込み判定
				if (pPlayer->pos.z + pPlayer->vtxMinPlayer.z < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
					pPlayer->pos.z + pPlayer->vtxMaxPlayer.z > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
				{// Zの幅
					if (pPlayer->posOld.x + pPlayer->vtxMaxPlayer.x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
						pPlayer->pos.x + pPlayer->vtxMaxPlayer.x > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
					{// Xが左から右にめり込んだ
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x - pPlayer->vtxMaxPlayer.x;
					}
					else if (pPlayer->posOld.x + pPlayer->vtxMinPlayer.x >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
						pPlayer->pos.x + pPlayer->vtxMinPlayer.x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x)
					{// Xが右から左にめり込んだ
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x - pPlayer->vtxMinPlayer.x;
					}
				}
			}
		}
	}
	return bRanding;
}

//********************************************
// ブロックの取得
//********************************************
BLOCK* GetBlock(void)
{
	return &g_aBlock[0];
}

//********************************************
// ブロック管理の取得
//********************************************
BLOCKMANAGER* GetBlockManager(void)
{
	return &g_blockManager;
}

//********************************************
// ブロック全部消す
//********************************************
void BlockOllDeliete(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].bUse = false;
		g_blockManager.nBlockNum--;
	}
}

//********************************************
// ブロック操作
//********************************************
void BlockControllre(void)
{
	if (KeyboardTrigger(DIK_UP))
	{
		int nCntMax = 0;

		while (1)
		{
			g_blockCont.nCntNowBlock++;// 次の奴へカウント
			nCntMax++;
			if (g_aBlock[g_blockCont.nCntNowBlock].bUse)
			{// 次のブロックが使ってたら
				break;
			}
			
			if (nCntMax > g_blockManager.nBlockNum)
			{// 出現しているブロック数を超えたら
				g_blockCont.nCntNowBlock = 0;
				break;
			}
		}
	}

	
}