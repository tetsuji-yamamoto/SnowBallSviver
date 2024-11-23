#include "writetext.h"
#include "block.h"

//**************************************************
// �e�L�X�g�t�@�C���̏�������
//**************************************************
void WriteText(void)
{
	// �t�@�C���ǂݍ��݃I�[�v��
	FILE* pFile = fopen("date\\text\\writeStage.txt", "w");
	char astr[256] = {};	// ��������i�[����ϐ�

	// �X�e�[�W����������
	WriteStage(pFile);

	fclose(pFile);
}

//**************************************************
// �X�e�[�W�̏�������
//**************************************************
void WriteStage(FILE* pFile)
{
	// ��������
	fprintf(pFile,"%s\n\n","STAGESET");
	WriteBlockDate(pFile);
	fprintf(pFile,"%s\n","ENDSTAGESET");

}

//**************************************************
// �u���b�N�̏�������
//**************************************************
void WriteBlockDate(FILE* pFile)
{
	BLOCK* pBlock = GetBlock();	// �u���b�N���擾
	BLOCKMANAGER* pBlockMane = GetBlockManager();	// �u���b�N�Ǘ����擾

	// �g���Ă���u���b�N���e�L�X�g��ǂݍ���
	for (int nCnt = 0; nCnt < pBlockMane->nBlockNum; nCnt++)
	{
		fprintf(pFile, "%s\n", "SETBLOCK");
		fprintf(pFile, "POS %0.1f% 0.1f% 0.1f\n", pBlock->pos.x, pBlock->pos.y, pBlock->pos.z);
		fprintf(pFile, "ROT %0.1f% 0.1f% 0.1f\n", pBlock->rot.x, pBlock->rot.y, pBlock->rot.z);
		fprintf(pFile, "BLOCKTYPE %d\n", pBlock->nType);
		fprintf(pFile, "BLOCKFILE %s\n", &pBlock->astr[0]);
		fprintf(pFile, "%s\n\n", "ENDSETBLOCK");
		pBlock++;
	}
}
