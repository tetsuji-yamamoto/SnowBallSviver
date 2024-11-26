#include "camera.h"
#include "mouse.h"
#include "keyboard.h"
#include "joypad.h"
#include "player.h"
#include "mouse.h"

// グローバル変数宣言
Camera g_camera;	// カメラ情報

//*****************************************
// カメラの初期化
//*****************************************
void InitCamera(void)
{
	// 視点・中視点・上方向を設定する
	g_camera.posV = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 固定
	g_camera.rot = D3DXVECTOR3(-D3DX_PI * 0.2f, 0.0f, 0.0f);

	g_camera.posVDest = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = 500.0f;	// 視点から注視点の距離

	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
	g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * g_camera.fDistance;
	g_camera.posV.z = g_camera.posR.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

	g_camera.nType = CAMERATYPE_NOMAL;
}

//*****************************************
// カメラの終了処理
//*****************************************
void UninitCamera(void)
{

}

//*****************************************
// カメラの更新
//*****************************************
void UpdateCamera(void)
{
	PLAYER* pPlayer = GetPlayer();				// プレイヤー取得
	XINPUT_STATE* pJoypad = GetJoypadState();	// ジョイパッド情報取得

	D3DXVECTOR3 MousePos = GetMousePosition();
	D3DXVECTOR3 MouseMove = GetMouseVelocity();

	bool bVR = true;// trueだと始点操作
	//カメラタイプ切り替え
	if (KeyboardTrigger(DIK_F1))
	{
		g_camera.nType++;
		if (g_camera.nType >= CAMERATYPE_MAX)
		{
			g_camera.nType = 0;
		}

		switch (g_camera.nType)
		{

		case CAMERATYPE_PLAYER:
			g_camera.fDistance = 160.0f;
			break;

		}

	}

	switch (g_camera.nType)
	{

	case CAMERATYPE_PLAYER:
		// プレイヤー追従 

		g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rotDest.y) * (float)PLAYER_MOVE;
		g_camera.posRDest.y;
		g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rotDest.y) * (float)PLAYER_MOVE;

		g_camera.posVDest.x = pPlayer->pos.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posVDest.y;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(g_camera.rot.y) * g_camera.fDistance;

		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.1f;
		g_camera.posR.y = pPlayer->pos.y + 50;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.1f;

		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;
		g_camera.posV.y = pPlayer->pos.y + 50;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
		break;

	}
	// キーボード操作
	
	//if (KeyboardRepeat(DIK_RSHIFT))
	//{
	//	if (KeyboardRepeat(DIK_RIGHT))
	//	{//右上に移動
	//		g_camera.rot.y -= 0.01f;	// 回転量
	//	}
	//	else if (KeyboardRepeat(DIK_LEFT))
	//	{//左上に移動
	//		g_camera.rot.y += 0.01f;	// 回転量
	//	}
	//	else if (KeyboardRepeat(DIK_UP))
	//	{
	//		bVR = false;
	//		g_camera.rot.y -= 0.01f;	// 回転量
	//	}
	//	else if (KeyboardRepeat(DIK_DOWN))
	//	{
	//		bVR = false;
	//		g_camera.rot.y += 0.01f;	// 回転量
	//	}
	//}
	//else if (KeyboardRepeat(DIK_UP))
	//{//まっすぐ移動
	//	if (KeyboardRepeat(DIK_RIGHT))
	//	{//右上に移動
	//		g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
	//		g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
	//		g_camera.posR.x += sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
	//		g_camera.posR.z += cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
	//	}
	//	else if (KeyboardRepeat(DIK_LEFT))
	//	{//左上に移動
	//		g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
	//		g_camera.posR.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
	//		g_camera.posR.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
	//	}
	//	else
	//	{
	//		g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posR.x += sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posR.z += cosf(g_camera.rot.y) * 1.0f;
	//	}
	//}
	//else if (KeyboardRepeat(DIK_DOWN))
	//{//下に移動
	//	if (KeyboardRepeat(DIK_RIGHT))
	//	{//右に移動
	//		g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
	//		g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
	//		g_camera.posR.x += sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
	//		g_camera.posR.z += cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * 0.5f;
	//	}
	//	else if (KeyboardRepeat(DIK_LEFT))
	//	{//左に移動
	//		g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
	//		g_camera.posR.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
	//		g_camera.posR.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * 0.5f;
	//	}
	//	else
	//	{
	//		g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posR.x -= sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posR.z -= cosf(g_camera.rot.y) * 1.0f;
	//	}
	//}
	//else if (KeyboardRepeat(DIK_RIGHT))
	//{//右に移動
	//	g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
	//	g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
	//	g_camera.posR.x += sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
	//	g_camera.posR.z += cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
	//}
	//else if (KeyboardRepeat(DIK_LEFT))
	//{//左に移動
	//	g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
	//	g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
	//	g_camera.posR.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
	//	g_camera.posR.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.0f;
	//}

	// マウス操作
	if (MouseButtonRepeat(MOUSEBUTTON_LEFT) == true)
	{// 左クリ視点旋回
		g_camera.rot.y += MouseMove.x * 0.01f;	// 回転量
		g_camera.rot.x += MouseMove.y * 0.01f;	// 回転量
	}
	else if (MouseButtonRepeat(MOUSEBUTTON_RIGHT) == true)
	{// 右クリ視点旋回
		g_camera.rot.y += MouseMove.x * 0.01f;	// 回転量
		g_camera.rot.x += MouseMove.y * 0.01f;	// 回転量
		bVR = false;
	}
	else if (MouseButtonRepeat(MOUSEBUTTON_CENTER) == true)
	{// 中ボタン
	
	}

	if (MousePos.z > 0)
	{//奥に回したら
		g_camera.fDistance += 10.0f;
	}
	else if (MousePos.z < 0)
	{//手前に回したら
		g_camera.fDistance -= 10.0f;

		if (g_camera.fDistance <= 5.0f)
		{// 行き過ぎないように
			g_camera.fDistance = 5.0f;
		}
	}

	// コントローラー
	if (GetJoyStickR())
	{// 32468
		float fJoyAngleX = ((float)pJoypad->Gamepad.sThumbRX / (float)32468);
		float fJoyAngleY = ((float)pJoypad->Gamepad.sThumbRY / (float)32468);
		float fAngleX = D3DX_PI * fJoyAngleX;
		float fAngleY = D3DX_PI * fJoyAngleY;
		g_camera.rot.y += fAngleX * 0.02f;
		g_camera.rot.x -= fAngleY * 0.02f;
	}

	if (bVR == true)
	{// 視点旋回
		// 角度の限界値
		if (g_camera.rot.x < -D3DX_PI * 0.9f)
		{
			g_camera.rot.x = -D3DX_PI * 0.9f;
		}
		else 	if (g_camera.rot.x > -D3DX_PI * 0.1f)
		{
			g_camera.rot.x = -D3DX_PI * 0.1f;
		}

		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else
	{// 注視点旋回
		// 角度の限界地
		if (g_camera.rot.x < -D3DX_PI * 0.9f)
		{
			g_camera.rot.x = -D3DX_PI * 0.9f;
		}
		else 	if (g_camera.rot.x > -D3DX_PI * 0.1f)
		{
			g_camera.rot.x = -D3DX_PI * 0.1f;
		}

		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.y = g_camera.posV.y - cosf(g_camera.rot.x) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z - sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y = -D3DX_PI + (g_camera.rot.y - D3DX_PI);
	}
	else if(g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y = D3DX_PI + (g_camera.rot.y + D3DX_PI);
	}

	if (g_camera.rot.x > D3DX_PI)
	{
		g_camera.rot.x = -D3DX_PI + (g_camera.rot.x - D3DX_PI);
	}
	else if (g_camera.rot.x < -D3DX_PI)
	{
		g_camera.rot.x = D3DX_PI + (g_camera.rot.x + D3DX_PI);
	}
	
}

//*****************************************
// カメラの設定
//*****************************************
void SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマックスの初期化
	D3DXMatrixIsIdentity(&g_camera.mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,&g_camera.posV,&g_camera.posR,&g_camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	// プロジェクトマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//*****************************************
// カメラの取得
//*****************************************
Camera* GetCamera(void)
{
	return &g_camera;
}