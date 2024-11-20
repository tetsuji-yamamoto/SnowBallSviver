#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

#define FIELD_X (150)
#define FIELD_Z (150)
#define MESH_X (200)	// ��
#define MESH_Z (20)	// �c
//#define MESH_PLYGON_HID (4 * (MESH_Z - 1))								// �k�ރ|���S��
//#define MESH_PLYGON_APP ((MESH_X * MESH_Z) * 2)							// ������|���S��
#define MESH_PLYGON_AII (((MESH_X * MESH_Z) * 2) + (4 * (MESH_Z - 1)))		// ���v�|���S��
#define MESH_VERTEX ((MESH_X + 1) * (MESH_Z + 1))							// ���_��
#define MESH_INDEX (MESH_PLYGON_AII + 2)									// �C���f�b�N�X��

//�v���g�^�C�v�錾
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif // !_POLYGON_H_
