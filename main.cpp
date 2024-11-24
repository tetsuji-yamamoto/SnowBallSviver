#include "main.h"
#include "camera.h"
#include "light.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "player.h"
#include "shadow.h"
#include "block.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "readtext.h"
#include "writetext.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "guide.h"
#include "fade.h"

//�O���[�o���ϐ��錾
LPDIRECT3D9 g_pD3D = NULL;						//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;						//���݂̃��[�h
LPD3DXFONT g_pFont = NULL;						//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;							//fps�J�E���g�p
bool g_isFullscreen = false;					//�E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;								//�E�B���h�E��؂�ւ��邽�߂̕ϐ�
DEBUGMANAGER g_debMane;							// �f�o�b�O�\���Ǘ�

//***********************************************
// �f�o�C�X�̎擾
//***********************************************
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//***********************************************
// ���C���֐�
//***********************************************
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{
	WNDCLASSEX wcex =					// �E�B���h�E�N���X�̍\����
	{									   
		sizeof(WNDCLASSEX),				// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						// �E�B���h�E�̃X�^�C��
		WindowProc,						// �E�B���h�E�v���V�[�W��
		0,								// 0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,								// 0�ɂ���(�ʏ�͎g�p���Ȃ�)	
		hInstance,						// �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),	// �^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),		// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		// �N���C�A���g�̈�̔w�i�F
		NULL,							// ���j���[�o�[
		CLASS_NAME,						// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	// �t�@�C���̃A�C�R��
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	// ��ʃT�C�Y�̍\����
		
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;	// ���ݎ���
	DWORD dwExecLastTime;	// ���ݎ���
	DWORD dwFrameCount;		// �t���[���J�E���g
	DWORD dwFPSLastTime;	// �Ō��FPS���v����������

	// �E�B���h�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,		// �g���E�B���h�E�X�^�C��
		CLASS_NAME,					// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,				// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,				// �E�B���h�E����X���W
		CW_USEDEFAULT,				// �E�B���h�E����Y���W
		(rect.right - rect.left),	// �E�B���h�E�̕�
		(rect.bottom - rect.top),	// �E�B���h�E�̍���
		NULL,						// �e�E�B���h�E�̃n���h��
		NULL,						// ���j���[�n���h���܂��͎q�E�B���h�E�̃n���h��
		hInstance,					// �C���X�^���X�n���h��
		NULL);						// �E�B���h�E�����f�[�^

	// ����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{// ���������������s�����Ƃ�
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);	// �E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);			// �N���C�A���g�̈���X�V
	
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// windoes�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				// ���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);	// ���z���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	// �E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{// DilectX�̏���
			dwCurrentTime = timeGetTime();	// ���ݎ������擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��
				// FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;											// FPS�𑪒肵����ۑ�
				dwFrameCount = 0;														// �t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 60�t���[��
			{
				dwExecLastTime = dwCurrentTime;
				// �X�V����
				Updata();

				// �`�揈��
				Draw();

				dwFrameCount++;	// �t���[���J�E���g�����Z
			}
		}
	}
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//***********************************************
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//***********************************************
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}

//***********************************************
//�E�B���h�v���V�[�W��
//***********************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:	// �E�B���h�j�����b�Z�[�W

		// WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	// �L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:	// ESC�������ꂽ��

			// �E�B���h�E��j������(EM_DESTROY���b�Z�[�W�𑗂�)
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

//***********************************************
// �����������
//***********************************************
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^

	// Direc3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^��ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// �p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		// �Q�[����ʃT�C�Y��
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// �Q�[����ʃT�C�Y����
	d3dpp.BackBufferFormat = d3ddm.Format;		// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;					//
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//
	d3dpp.EnableAutoDepthStencil = TRUE;		//
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//
	d3dpp.Windowed = bWindow;					//
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//

	// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		// Direct3D�f�o�C�X�̐���(�`�揈�����n�[�h�E�F�A,���_������CPU�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
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

	// �����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// �J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);			// �v���C���[�̒��ɓ����x��������
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	// �T���u���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	// �W���C�p�b�h�̏���������
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	// �}�E�X��������
	if (FAILED(InitMouse(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h��������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	g_debMane.nDebugLine = 0;
	g_debMane.nLineDistance = 15;

	InitFade(g_mode);	// �t�F�[�h

	// ���[�h�̐ݒ�
	SetMode(g_mode);

	// �f�o�b�O�p�\���t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"terminal", &g_pFont);

	return S_OK;
}

//***********************************************
// �I������
//***********************************************
void Uninit(void)
{
	UninitKeyboard();	// �L�[�{�[�h�̏I������
	UninitMouse();		// �}�E�X
	UninitJoypad();		// �R���g���[���[
	UninitFade();		// �t�F�[�h
	
	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//***********************************************
// �X�V����
//***********************************************
void Updata(void)
{
	UpdataKeyboard();	// �L�[���͂̍X�V����
	UpdateMouse();		// �R���g���[���[
	UpdataJoypad();		// �W���C�p�b�h
	UpdateFade();		// �t�F�[�h

	// ���̏�Ԃ̍X�V����
	switch (g_mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		UpdateTitle();
		break;

	case MODE_GAME:		//�Q�[�����
		UpdateGame();
		break;

	case MODE_RESULT:	//���U���g���
		UpdateResult();
		break;
	}

#ifdef _DEBUG

	if (KeyboardTrigger(DIK_F2))
	{//�@�I�u�W�F�N�g�̃e�L�X�g�ւ̓ǂݍ���
		ReadText();
	}
	else if (KeyboardTrigger(DIK_F3))
	{// �I�u�W�F�N�g�̃e�L�X�g�ւ̏�������
		WriteText();
	}

	// ���[�h�ؑ�
	if (KeyboardTrigger(DIK_F10))
	{
		// ���̃��[�h�ɐ؂�ւ���
		switch (g_mode)
		{
		case MODE_TITLE:	//�^�C�g�����
			SetMode(MODE_GAME);
			break;

		case MODE_GAME:		//�Q�[�����
			SetMode(MODE_RESULT);
			break;

		case MODE_RESULT:	//���U���g���
			SetMode(MODE_TITLE);
			break;
		}
	}

#endif
}

//***********************************************
// �`�揈��
//***********************************************
void Draw(void)
{
	// ��ʃN���A(�o�b�t�@�o�b�t�@&�̃N���A�j
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		 D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{// �`��J�n�����������ꍇ


		// ���̏�Ԃ̕`��
		switch (g_mode)
		{
		case MODE_TITLE:	//�^�C�g�����
			DrawTitle();
			break;

		case MODE_GAME:		//�Q�[�����
			DrawGame();
			break;

		case MODE_RESULT:	//���U���g���
			DrawResult();
			break;
		}

		DrawFade();	// �t�F�[�h

#ifdef _DEBUG // �f�o�b�O�r���h�������\��

		DrawFPS();			// FPS�\��
		DrawGameMode();		// �Q�[�����[�h
		DrawCamera();		// �J����
		DrawDebPlayer();	// pureiya
		//DrawDCamera();		// ���C�g

		g_debMane.nDebugLine = 0;

#endif

		// �`��I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//******************************************
// ���[�h�ؑ�
//******************************************
void SetMode(MODE mode)
{
	// ���̏�Ԃ��I��������
	switch (g_mode)
	{
	case MODE_TITLE:	// �^�C�g�����
		UninitTitle();
		break;

	case MODE_GAME:		// �Q�[�����
		UninitGame();
		break;

	case MODE_RESULT:	// ���U���g���
		UninitResult();
		break;
	}

	// ���̃��[�h�ɏ�����
	switch (mode)
	{
	case MODE_TITLE:	// �^�C�g�����
		InitTitle();		   
		break;			   
						   
	case MODE_GAME:		// �Q�[�����
		InitGame();		   
		break;			   
						   
	case MODE_RESULT:	// ���U���g���
		InitResult();
		break;
	}

	// ���̃��[�h�ɂ���
	g_mode = mode;
}

//******************************************
// ���[�h�擾
//******************************************
MODE GetMode(void)
{
	return g_mode;
}

//******************************************
// �f�o�b�O�\��
//******************************************
void DrawFPS(void)
{
	char aStr[256];

	// �����ɑ��
	wsprintf(&aStr[0], "FPS:%0.3d\n", g_nCountFPS);

	RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
	// �e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 255, 0, 255));

	g_debMane.nDebugLine += g_debMane.nLineDistance * 2;
}

//******************************************
// �Q�[�����[�h�̃f�o�b�O�\��
//******************************************
void DrawGameMode(void)
{
	MODE mode = GetMode();

	char aStr[256];

	switch (mode)
	{
	case MODE_TITLE:
		// �����ɑ��
		wsprintf(&aStr[0], "[MODE]<TITLE>");
		break;

	case MODE_GAME:
		// �����ɑ��
		wsprintf(&aStr[0], "[MODE]<GAME>");
		break;

	case MODE_RESULT:
		// �����ɑ��
		wsprintf(&aStr[0], "[MODE]<RESULT>");
		break;
	}

	
	RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
	// �e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 255, 0, 255));

	g_debMane.nDebugLine += g_debMane.nLineDistance * 2;
}

//******************************************
// �J�����̃f�o�b�O�\��
//******************************************
void DrawCamera(void)
{
	Camera* pCamera = GetCamera();	// �J�����擾
	char aStr[7][256];
	int nCntA = 0;

	// �����ɑ��
	sprintf(&aStr[nCntA][0], "[CAMERA]\n");
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.rot.x:%0.3fy:%0.3fz:%0.3f\n", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.posV.x:%0.3fy:%0.3fz:%0.3f\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.posR.x:%0.3fy:%0.3fz:%0.3f\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.posVDest.x:%0.3fy:%0.3fz:%0.3f\n", pCamera->posVDest.x, pCamera->posVDest.y, pCamera->posVDest.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.posRDest.x:%0.3fy:%0.3fz:%0.3f\n", pCamera->posRDest.x, pCamera->posRDest.y, pCamera->posRDest.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.fDistance:%0.3f\n", pCamera->fDistance);

	for (int nCntB = 0; nCntB <= nCntA; nCntB++)
	{
		RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
		// �e�L�X�g�̕`��
		g_pFont->DrawText(NULL, &aStr[nCntB][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 255, 0, 255));
		g_debMane.nDebugLine += g_debMane.nLineDistance;
	}
	g_debMane.nDebugLine += g_debMane.nLineDistance;
}

//******************************************
// �v���C���[�̃f�o�b�O�\��
//******************************************
void DrawDebPlayer(void)
{
	PLAYER* pPlayer = GetPlayer();	// �v���C���[�擾

	char aStr[5][256];
	int nCntA = 0;

	// �����ɑ��
	sprintf(&aStr[nCntA][0], "[PLAYER]\n");
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.pos.x:%0.3fy:%0.3fz:%0.3f\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.rot.x:%0.3fy:%0.3fz:%0.3f\n", pPlayer->rot.x, pPlayer->rot.y, pPlayer->rot.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.rotDest.x:%0.3fy:%0.3fz:%0.3f\n", pPlayer->rotDest.x, pPlayer->rotDest.y, pPlayer->rotDest.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.move.x:%0.3fy:%0.3fz:%0.3f\n", pPlayer->move.x, pPlayer->move.y, pPlayer->move.z);

	for (int nCnt = 0; nCnt <= nCntA; nCnt++)
	{
		RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
		// �e�L�X�g�̕`��
		g_pFont->DrawText(NULL, &aStr[nCnt][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 255, 0, 255));
		g_debMane.nDebugLine += g_debMane.nLineDistance;
	}
	g_debMane.nDebugLine += g_debMane.nLineDistance;
}

//******************************************
// ���C�g�̃f�o�b�O�\��
//******************************************
void DrawDCamera(void)
{
	//D3DLIGHT9* pLight = GetLight();	// ���C�g�擾

	//char aStr[5][256];
	//int nCntA = 0;

	//// �����ɑ��
	//sprintf(&aStr[nCntA][0], "[LIGHT]\n");
	//nCntA++; sprintf(&aStr[nCntA][0], "g_player.pos.x:%0.3fy:%0.3fz:%0.3f\n", pLight->pos.x, pPlayer->pos.y, pPlayer->pos.z);

	//for (int nCnt = 0; nCnt < nCntA; nCnt++)
	//{
	//	RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
	//	// �e�L�X�g�̕`��
	//	g_pFont->DrawText(NULL, &aStr[nCnt][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 255, 0, 255));
	//	g_debMane.nDebugLine += g_debMane.nLineDistance;
	//}
	//g_debMane.nDebugLine += g_debMane.nLineDistance;
}
