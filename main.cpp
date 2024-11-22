#include "main.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "player.h"
#include "shadow.h"
#include "wall.h"
#include "block.h"
#include "billboard.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "readtext.h"
#include "meshfield.h"
#include "writetext.h"

//グローバル変数宣言
LPDIRECT3D9 g_pD3D = NULL;						//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;						//現在のモード
LPD3DXFONT g_pFont = NULL;						//フォントへのポインタ
int g_nCountFPS = 0;							//fpsカウント用
bool g_isFullscreen = false;					//ウィンドウを切り替えるためのフラグ
RECT g_windowRect;								//ウィンドウを切り替えるための変数
int g_line = 0;

//=======================
//デバイスの取得
//=======================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=======================
//メイン関数
//=======================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{
	WNDCLASSEX wcex =					//ウィンドウクラスの構造体
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						//ウィンドウのスタイル
		WindowProc,						//ウィンドウプロシージャ
		0,								//0にする(通常は使用しない)
		0,								//0にする(通常は使用しない)	
		hInstance,						//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),	//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),		//クライアント領域の背景色
		NULL,							//メニューバー
		CLASS_NAME,						//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)	//ファイルのアイコン
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//画面サイズの構造体
		
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;//現在時刻
	DWORD dwExecLastTime;//現在時刻
	DWORD dwFrameCount;//フレームカウント
	DWORD dwFPSLastTime;//最後にFPSを計測した時刻

	//ウィンドクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,		//拡張ウィンドウスタイル
		CLASS_NAME,					//ウィンドウクラスの名前
		WINDOW_NAME,				//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル
		CW_USEDEFAULT,				//ウィンドウ左上X座標
		CW_USEDEFAULT,				//ウィンドウ左上Y座標
		(rect.right - rect.left),	//ウィンドウの幅
		(rect.bottom - rect.top),	//ウィンドウの高さ
		NULL,						//親ウィンドウのハンドル
		NULL,						//メニューハンドルまたは子ウィンドウのハンドル
		hInstance,					//インスタンスハンドル
		NULL);						//ウィンドウ生成データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗したとき
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);	//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);			//クライアント領域を更新
	
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windoesの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);	//仮想メッセージを文字メッセージへ変換
				DispatchMessage(&msg);	//ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{//DilectXの処理
			dwCurrentTime = timeGetTime();//現在時刻を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;											//FPSを測定したを保存
				dwFrameCount = 0;														//フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))//60フレーム
			{
				dwExecLastTime = dwCurrentTime;
				//更新処理
				Updata();
				//描画処理
				Draw();
				dwFrameCount++;//フレームカウントを加算
			}
		}
	}
	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//==========================================
// ウィンドウをフルスクリーンに変える処理
//==========================================
void ToggleFullscreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}

//==========================================
//ウィンドプロシージャ
//==========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY://ウィンド破棄メッセージ

		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:	//ESCが押されたら

			//ウィンドウを破棄する(EM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
			break;

		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//==========================================
//初期化しょり
//==========================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//ぢスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ

	//Direc3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータを設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//ゲーム画面サイズ幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//ゲーム画面サイズ高さ
	d3dpp.BackBufferFormat = d3ddm.Format;//バックバッファの形式
	d3dpp.BackBufferCount = 1;//
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//
	d3dpp.EnableAutoDepthStencil = TRUE;//
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//
	d3dpp.Windowed = bWindow;//
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理をハードウェア,頂点処理はCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);//プレイヤーの中に透明度を加える
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//サンブラーステートの設定
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	//ジョイパッドの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//マウス所得処理
	if (FAILED(InitMouse(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//キーボード所得処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	InitShadow();	// 影
	//InitPolygon();	// ポリゴン
	InitMeshField();// メッシュフィールド
	InitCamera();	// カメラ
	InitLight();	// ライト
	InitModel();	// モデル
	InitPlayer();	// プレイヤー
	InitWall();		// 壁
	InitBlock();	// ブロック
	InitBillboard();	// ビルボード
	InitBullet();		// 弾
	InitExplosion();	// 爆発
	InitEffect();		// エフェクト
	InitParticle();		// パーティクル

	//モードの設定
	//SetMode(g_mode);
	//デバッグ用表示フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"terminal", &g_pFont);

	return S_OK;
}

//==========================================
//終了処理
//==========================================
void Uninit(void)
{
	UninitKeyboard();	// キーボードの終了処理
	UninitMouse();		// マウス
	UninitJoypad();		// コントローラー
	//UninitPolygon();	//ポリゴン
	UninitMeshField();	// メッシュフィールド
	UninitCamera();		//カメラ
	UninitLight();		//ライト
	UninitModel();		// モデル
	UninitPlayer();		// プレイヤー
	UninitShadow();		// 影
	UninitWall();		// 壁
	UninitBlock();		// ブロック
	UninitBillboard();	// ビルボード
	UninitBullet();		// 弾
	UninitExplosion();	// 爆発
	UninitEffect();		// エフェクト



	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice = NULL;
	}
	//Direct3Dオブジェクト
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//デバッグ表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//==========================================
// 更新処理
//==========================================
void Updata(void)
{
	UpdataKeyboard();	// キー入力の更新処理
	UpdateMouse();		// コントローラー
	UpdataJoypad();		// ジョイパッド
	UpdatePlayer();		// プレイヤー
	//UpdatePolygon();	//ポリゴン
	UpdateMeshField();	// メッシュフィールド
	UpdateCamera();		//カメラ
	UpdateLight();		//ライト
	UpdateModel();		// モデル
	UpdateShadow();		// 影
	UpdateWall();		// 壁
	UpdateBlock();		// ブロック
	UpdateBillboard();	// ビルボード
	UpdateBullet();		// 弾
	UpdateExplosion();	// 爆発
	UpdateEffect();		// エフェクト
	UpdateParticle();	// パーティクル

#ifdef _DEBUG

	if (KeyboardTrigger(DIK_F2))
	{
		ReadText();
	}
	else if (KeyboardTrigger(DIK_F3))
	{
		WriteText();
	}

#endif

	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面
		break;
	case MODE_GAME:		//ゲーム画面
		break;
	case MODE_RESULT:	//リザルト画面
		break;
	case MODE_RANKING:	//ランキング画面
		break;
	case MODE_TUTORIAL:	//チュートリアル画面
		break;
	}
	
	
}

//==========================================
//描画処理
//==========================================
void Draw(void)
{
	//画面クリア(バッファバッファ&のクリア）
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		 D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		SetCamera();		// カメラ
		//DrawPolygon();		// ポリゴン
		DrawMeshField();	// メッシュフィールド
		DrawWall();			// 壁
		DrawShadow();		// 影
		DrawEffect();		// エフェクト
		DrawModel();		// モデル
		DrawPlayer();		// プレイヤー
		DrawBlock();		// ブロック
		DrawBillboard();	// ビルボード
		DrawBullet();		// 弾
		DrawExplosion();	// 爆発


#ifdef _DEBUG //デバッグビルド時だけ表示

		DrawFPS();			// FPS表示
		DrawCamera();		// カメラ
		DrawDebPlayer();	// pureiya
		DrawDCamera();		// ライト

		g_line = 0;

#endif

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//******************************************
// デバッグ表示
//******************************************
void DrawFPS(void)
{
	RECT rect = { 0,g_line,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	//文字に代入
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);
	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	g_line += 15;
}

//******************************************
// カメラのデバッグ表示
//******************************************
void DrawCamera(void)
{
	Camera* pCamera = GetCamera();	// カメラ取得

	char aStr[256];

	RECT rect = { 0,g_line,SCREEN_WIDTH,SCREEN_HEIGHT };

	//文字に代入
	sprintf(&aStr[0], "g_camera.rot.x:%3fy:%3fz:%3f\n", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));

	g_line += 15;
}

//******************************************
// プレイヤーのデバッグ表示
//******************************************
void DrawDebPlayer(void)
{
	PLAYER* pPlayer = GetPlayer();	// プレイヤー取得


	RECT rect = { 0,g_line,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	//文字に代入
	sprintf(&aStr[0], "g_player.rot.y:%6f\n", pPlayer->rot.y);
	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	g_line += 15;

	RECT rect2 = { 0,g_line,SCREEN_WIDTH,SCREEN_HEIGHT };
	//文字に代入
	sprintf(&aStr[0], "g_player.rotDest.y:%6f\n", pPlayer->rotDest.y);
	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect2, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	g_line += 15;

	RECT rect3 = { 0,g_line,SCREEN_WIDTH,SCREEN_HEIGHT };
	//文字に代入
	sprintf(&aStr[0], "g_player.move:x%6f:y%6f;z%6f\n", pPlayer->move.x, pPlayer->move.y, pPlayer->move.z);
	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect3, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	g_line += 15;
}

//******************************************
// ライトのデバッグ表示
//******************************************
void DrawDCamera(void)
{
	D3DLIGHT9* pLight = GetLight();	// ライト取得


	RECT rect = { 0,g_line,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	//文字に代入
	sprintf(&aStr[0], "g_light.Direction.x:%3fy:%3fz:%3f\n", pLight->Direction.x, pLight->Direction.y, pLight->Direction.z);
	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	g_line += 15;

}
