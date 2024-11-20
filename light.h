#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//プロトタイプ宣言
void InitLight(void);
void UninitLight(void);
void UpdateLight(void);
D3DLIGHT9* GetLight(void);

#endif // !_LIGHT_H_
