#include "result.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"

// グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	// 頂点バッファへのポインタ
RESULT g_result;									// リザルトの情報

//*********************************************
//リザルト画面の初期化処理
//*********************************************
void InitResult(void)
{
	SetResult(RESULTTYPE_GAMEOVER);
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, // 必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	g_result.pFileTex = FILE_TEX_RESULT_GAMEOVER;

	switch (g_result.resultType)
	{
	case RESULTTYPE_GAMEOVER:
		g_result.pFileTex = FILE_TEX_RESULT_GAMEOVER;
		break;

	case RESULTTYPE_GAMECREAR:
		g_result.pFileTex = FILE_TEX_RESULT_GAMECREAR;
		break;

	case RESULTTYPE_TIMEOVER:
		g_result.pFileTex = FILE_TEX_RESULT_TIMEOVER;
		break;

	default:
		g_result.pFileTex = FILE_TEX_RESULT_DEFAULT;
		break;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		g_result.pFileTex,
		&g_pTextureResult);

	g_result.rect.bottom = (float)SCREEN_HEIGHT * 0.1f;
	g_result.rect.left = (float)SCREEN_WIDTH * 0.3f;
	g_result.rect.right = (float)SCREEN_WIDTH * 0.3f;
	g_result.rect.top = (float)SCREEN_HEIGHT * 0.1f;
	g_result.pos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f,(float)SCREEN_HEIGHT * 0.5f,0.0f);

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = g_result.pos + D3DXVECTOR3(-g_result.rect.left, -g_result.rect.top, 0.0f);
	pVtx[1].pos = g_result.pos + D3DXVECTOR3(g_result.rect.right, -g_result.rect.top, 0.0f);
	pVtx[2].pos = g_result.pos + D3DXVECTOR3(-g_result.rect.left, g_result.rect.bottom, 0.0f);
	pVtx[3].pos = g_result.pos + D3DXVECTOR3(g_result.rect.right, g_result.rect.bottom, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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

	// 頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

}

//*********************************************
// リザルト画面の終了処理
//*********************************************
void UninitResult(void)
{
	// テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//*********************************************
// リザルト画面の更新処理
//*********************************************
void UpdateResult(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{
		SetFade(MODE_TITLE);
	}

}

//*********************************************
// リザルト画面の描画処理
//*********************************************
void DrawResult(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	// プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,										// 描画する最初の頂点インデックス
		2);										// 描画するプリミティブ（プレイヤー）数
}

//*********************************************
// リザルト設定
//*********************************************
void SetResult(RESULTTYPE resultType)
{
	g_result.resultType = resultType;
}