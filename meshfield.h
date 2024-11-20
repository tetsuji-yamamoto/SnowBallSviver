#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

#define FIELD_X (150)
#define FIELD_Z (150)
#define MESH_X (200)	// 横
#define MESH_Z (20)	// 縦
//#define MESH_PLYGON_HID (4 * (MESH_Z - 1))								// 縮退ポリゴン
//#define MESH_PLYGON_APP ((MESH_X * MESH_Z) * 2)							// 見えるポリゴン
#define MESH_PLYGON_AII (((MESH_X * MESH_Z) * 2) + (4 * (MESH_Z - 1)))		// 合計ポリゴン
#define MESH_VERTEX ((MESH_X + 1) * (MESH_Z + 1))							// 頂点数
#define MESH_INDEX (MESH_PLYGON_AII + 2)									// インデックスの

//プロトタイプ宣言
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif // !_POLYGON_H_
