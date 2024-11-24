#include "title.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"

// グローバル変数宣言
LPDIRECT3DTEXTURE9 g_aPTextureTitle[TITLETYPE_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				// 頂点バッファへのポインタ
TITLE g_aTitle[TITLETYPE_MAX];								// タイトルポリゴンの情報//タイトルポリゴンのテクスチャ
TITLEDIRECTOR g_TitleDirector;

//*********************************************
// タイトル画面の初期化処理
//*********************************************
void InitTitle(void)
{

	int nCntTitle;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLETYPE_MAX, // 必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	// 演出構造体初期化
	g_TitleDirector.titleDirect = TITLEDIRECT_LOGODOWN;
	g_TitleDirector.nTimer = 0;
	g_TitleDirector.bBrink = false;

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 情報の初期化
	for (nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		g_aTitle[nCntTitle].pFileName = NULL;
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].type = TITLETYPE_MAX;

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	TITLE title;
	title.pFileName = FILE_TEX_TITLE_SBS;
	title.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	title.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	title.type = TITLETYPE_LOGO;
	title.fHeight = SCREEN_HEIGHT * 0.15f;
	title.fWidth = SCREEN_WIDTH * 0.3f;

	// タイトルロゴ
	SetTitle(title);

}
//*********************************************
// タイトル画面の終了処理
//*********************************************
void UninitTitle(void)
{
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		// テクスチャの破棄
		if (g_aPTextureTitle[nCntTitle] != NULL)
		{
			g_aPTextureTitle[nCntTitle]->Release();
			g_aPTextureTitle[nCntTitle] = NULL;
		}
	}

	//頂 点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//*********************************************
// タイトル画面の更新処理
//*********************************************
void UpdateTitle(void)
{
	
	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(MODE_GAME);
	}
}

//*********************************************
// タイトル画面の描画処理
//*********************************************
void DrawTitle(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_aPTextureTitle[nCntTitle]);

			// プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの種類
				4 * nCntTitle,							// 描画する最初の頂点インデックス
				2);										// 描画するプリミティブ（プレイヤー）数
		}
	}


}

//*********************************************
// タイトルの設定
//*********************************************
void SetTitle(TITLE title)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 探す
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == false)
		{
			g_aTitle[nCntTitle].pFileName = title.pFileName;
			g_aTitle[nCntTitle].pos = title.pos;
			g_aTitle[nCntTitle].col = title.col;
			g_aTitle[nCntTitle].type = title.type;
			g_aTitle[nCntTitle].fWidth = title.fWidth;
			g_aTitle[nCntTitle].fHeight = title.fHeight;
			g_aTitle[nCntTitle].bUse = true;

			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				g_aTitle[nCntTitle].pFileName,
				&g_aPTextureTitle[nCntTitle]);

			// 頂点座標の設定
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// 頂点カラーの設定
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}