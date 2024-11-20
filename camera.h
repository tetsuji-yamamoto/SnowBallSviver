#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
// �J�����^�C�v��
typedef enum
{
	CAMERATYPE_NOMAL = 0,
	CAMERATYPE_PLAYER,
	CAMERATYPE_MAX,
}CAMERATYPE;

// �J�����\����
typedef struct
{
	D3DXVECTOR3 posV;			// ���_
	D3DXVECTOR3 posVDest;		// �ړI�̎��_
	D3DXVECTOR3 posR;			// �����_
	D3DXVECTOR3 posRDest;		// �ړI�̒����_
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DXVECTOR3 rot;			// ����
	float fDistance;			// ���_���璍���_�܂ł̋���

	int nType;					// �J�����^�C�v
}Camera;

// �v���^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera* GetCamera(void);
#endif // !_CAMERA_H_
