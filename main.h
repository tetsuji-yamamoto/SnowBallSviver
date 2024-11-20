/////////////////////////////
//
//�_�C���N�gX
//Aouthor tetuji yamamoto
//
/////////////////////////////

#ifndef _MAIN_H_ //���̃}�N����`������ĂȂ�������
#define _MAIN_H_ //��d�C���N���[�h�X�q�̃}�N����`

#include<windows.h>
#include <stdio.h>
#include "d3dx9.h"						//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"						//���͏����ɕK�v
#include "Xinput.h"						//�W���C�p�b�h�����ɕK�v
#include "xaudio2.h"					//�T�E���h�����ɕK�v
#include <stdio.h>
#include <stdlib.h>

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//[d3d9,lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g(���i)�ɕK�v
#pragma comment(lib,"winmm.lib")	//D
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	//�W���C�p�b�h�����ɕK�v

//�}�N����`
#define CLASS_NAME "WindowClass"	//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "ChageZubashu"	//�E�B���h�E�̖��O(�L���v�V�����ɕ\��)
#define SCREEN_WIDTH (1280)			//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)			//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) //���W.�@��.�J���[.�e�N�X�`��

#define RGBA_FULLCOLOR 1.0f,1.0f,1.0f,1.0f
#define TEST_WIDTH_CENTER SCREEN_WIDTH * 0.5f
#define TEST_HEIGHT_CENTER SCREEN_HEIGHT * 0.5f

//��ʁi���[�h�j�̎��
typedef enum
{
	MODE_TITLE = 0,		//�`���[�g���A�����
	MODE_GAME,			//�Q�[�����
	MODE_RESULT,		//���U���g���
	MODE_RANKING,		//�����L���O���
	MODE_TUTORIAL,		//�`���[�g���A�����
	MODE_MAX			
}MODE;

//���_���[2D]�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ϊ��p�W��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

//���_���[3D]�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

//�l���_�\����
typedef struct
{
	D3DXVECTOR2 TopLeft;
	D3DXVECTOR2 TopRight;
	D3DXVECTOR2 BottomLeft;
	D3DXVECTOR2 BottomRight;
	float fLength;			//�Ίp��
	float fAngle;			//����
	float fLot;				//�p�x
}VERTEX;

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPDIRECT3DDEVICE9 GetDevice(void);
void Updata(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);
void DrawFPS(void);
void DrawCamera(void);
void DrawDebPlayer(void);
void DrawDCamera(void);
#endif