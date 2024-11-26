#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

// �}�N����`
#define PLAYER_MOVE (5.0f)
#define PLAYER_GRAVITY (0.2f)

// �v���C���[���\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 posOld;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 rotDest;	// �ړI�̌���
	D3DXVECTOR3 vtxMinPlayer, vtxMaxPlayer;	// ���f���̍ŏ��l�ő�l
	float playerSizeTop;		// ���f���̑傫����
	float playerSizeDown;		// ���f���̑傫����
	float playerSizeLeft;		// ���f���̑傫����
	float playerSizeRight;	// ���f���̑傫���E
	bool bMove;				// �������ǂ���
	bool bJanp;				// �W�����v���Ă��邩�ǂ���
}PLAYER;

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER* GetPlayer(void);
#endif // !_PLAYER_H_
