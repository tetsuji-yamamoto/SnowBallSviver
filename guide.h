#ifndef _GUIDE_H_
#define _GUIDE_H_

#include "main.h"

#define LINE_X (1)
#define LINE_Y (1)
#define LINE_Z (1)
#define GUIDE_LINE_X (50)
#define GUIDE_LINE_Z (50)

#define GUIDE_LINE_INTERVAL (10)

#define OLL_VERTEX (LINE_X * 2 + LINE_Y * 2 + LINE_Z * 2 + (GUIDE_LINE_X + 1) * 2 + (GUIDE_LINE_Z + 1) * 2)


// �K�C�h���^�C�v
typedef enum
{
	GUDETYPE_START = 0,
	GUDETYPE_END,
	GUDETYPE_MAX,
}GUDETYPE;

// �K�C�h���\����
typedef struct
{
	D3DXVECTOR3 posguide;	// �ʒu
	D3DXVECTOR3 rotguide;	// ����
	D3DXCOLOR col;			// �F
	GUDETYPE type;			// ���
	bool bUse;
}GUIDE;

// �K�C�h�Ǘ��\����
typedef struct
{
	bool bDisplay;
}GUDEMANAGER;

//�v���g�^�C�v�錾
void InitGuide(void);
void UninitGuide(void);
void UpdateGuide(void);
void DrawGuide(void);
void SetGude(GUIDE guide,D3DXVECTOR3 sp, D3DXVECTOR3 ep);
#endif // !_POLYGON_H_