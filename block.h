#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

#define MAX_BLOCK (9)		// �ő�u���b�N��
#define FILE_XFILE_BLOCK_SNOW "date\\xfile\\block\\Block_Snow_001.x"

// �u���b�N�^�C�v�񋓌^
typedef enum
{
	BLOCKTYPE_SNOW = 0,	// ��
	BLOCKTYPE_ICE,		// �X
	BLOCKTYPE_GRAVEL,	// ����
	BLOCKTYPE_MAX
}BLOCKTYPE;

// �u���b�N�\����
typedef struct
{
	LPDIRECT3DTEXTURE9 apTextureBlock[6];	// �e�N�X�`���ւ̃|���^
	LPD3DXMESH pMeshBlock;					// ���b�V��(���_���ւ̃|�C���^)
	LPD3DXBUFFER pBuffMatBlock;				// �}�e���A���ւ̃|�C���^
	DWORD dwNumMatBlock;					// �}�e���A���̐�
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 vtxMinBlock, vtxMaxBlock;	// ���f���̍ŏ��l�ő�l
	const char* pFilename;	// �t�@�C����
	char astr[256];			// �����i�[
	int nType;				// �^�C�v
	bool bUse;				// �g���Ă���邩�ǂ���
}BLOCK;

// �Z�b�g�u���b�N�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	const char* pFilename;	// �t�@�C����
	char astr[256];			// ������i�[�p
	int nType;				// �^�C�v
}SETBLOCK;

// �u���b�N�R���g���[���[
typedef struct
{
	int nCntNowBlock;	// ���I��ł���u���b�N
}BLOCKCONTROLLER;

// �u���b�N�̊Ǘ�
typedef struct
{
	int nBlockNum;
}BLOCKMANAGER;

// �v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(SETBLOCK setBlock);
BLOCK* GetBlock(void);
BLOCKMANAGER* GetBlockManager(void);
void BlockOllDeliete(void);
bool CollisionBlock(void);
void BlockControllre(void);
#endif // !_MODEL_H_
