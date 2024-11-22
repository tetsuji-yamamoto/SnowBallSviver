#include "light.h"
#include "keyboard.h"

//�O���[�o���ϐ��錾
D3DLIGHT9 g_light[3];	//���C�g���

//*****************************************
//���C�g�̏�����
//*****************************************
void InitLight(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���C�g�̕����x�N�g��
	D3DXVECTOR3 vecDir[3];

	for (int nCntLight = 0;nCntLight < 3;nCntLight++)
	{
		//���C�g���N���A����
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g�̕�����ݒ�
		vecDir[0] = D3DXVECTOR3(0.2f , -0.8f, -0.4f);
		vecDir[1] = D3DXVECTOR3(-12.0f , -14.0f, 15.0f);
		vecDir[2] = D3DXVECTOR3(-5.0f , -5.57f, -3.3f);

		//���K������(�傫���P�̃x�N�g���ɂ���)
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		g_light[nCntLight].Direction = vecDir[nCntLight];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//*****************************************
//���C�g�̏I��
//*****************************************
void UninitLight(void)
{
	

}

//*****************************************
//���C�g�̍X�V
//*****************************************
void UpdateLight(void)
{
	////�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////���C�g�̕����x�N�g��
	//D3DXVECTOR3 vecDir[3];

	//vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	//vecDir[1] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	//vecDir[2] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

	//////���K������(�傫���P�̃x�N�g���ɂ���)
	////D3DXVec3Normalize(&vecDir[0], &vecDir[0]);
	////g_light[0].Direction = vecDir[0];

	//if (KeyboardRepeat(DIK_R) == true)
	//{
	//	g_light[0].Direction.x += 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_F) == true)
	//{
	//	g_light[0].Direction.x -= 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_V) == true)
	//{
	//	g_light[0].Direction.x = 0.0f;
	//}

	//if (KeyboardRepeat(DIK_T) == true)
	//{
	//	g_light[0].Direction.y += 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_G) == true)
	//{
	//	g_light[0].Direction.y -= 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_B) == true)
	//{
	//	g_light[0].Direction.y = 0.0f;
	//}

	//if (KeyboardRepeat(DIK_Y) == true)
	//{
	//	g_light[0].Direction.z += 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_H) == true)
	//{
	//	g_light[0].Direction.z -= 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_N) == true)
	//{
	//	g_light[0].Direction.z = 0.0f;
	//}
	////���C�g��ݒ肷��
	//pDevice->SetLight(0, &g_light[0]);
}

D3DLIGHT9* GetLight(void)
{
	return &g_light[0];
}