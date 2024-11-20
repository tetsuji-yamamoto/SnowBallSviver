#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

// �}�N����`
#define PLAYER_MOVE (3.0f)

// �v���C���[���\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 rotDest;	// �ړI�̌���

	bool bMove;				// �������ǂ���
}PLAYER;

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER* GetPlayer(void);
#endif // !_PLAYER_H_
