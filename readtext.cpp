#include "readtext.h"
#include "block.h"

//**************************************************
// �e�L�X�g�t�@�C���̓ǂݍ���
//**************************************************
void ReadText(void)
{
	// �t�@�C���ǂݍ��݃I�[�v��
	FILE* pFile = fopen("date\\text\\stage.txt", "r");
	char astr[256] = {};	// ��������i�[����ϐ�

	// �e�L�X�g��ǂݍ���
	while (1)
	{
		// �e�L�X�g��ǂ�Ō��ʂ���
		int result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "STAGESET") == 0)
		{// �Z�b�g�X�e�[�W���s��
			SetStage(pFile);
		}

		// �ǂݐ؂�����I��
		if (result == EOF)
		{
			break;
		}
	}

	fclose(pFile);
}

//**************************************************
// �X�e�[�W�̓ǂݍ���
//**************************************************
void SetStage(FILE *pFile)
{
	char astr[256] = {};	// ��������i�[����ϐ�

	// �e�L�X�g��ǂݍ���
	while (1)
	{

		// �e�L�X�g��ǂ�Ō��ʂ���
		int result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "SETBLOC") == 0)
		{// �u���b�N����ǂݍ���
			ReadBlockDate(pFile);
		}

		if (strcmp(&astr[0], "ENDSTAGESET") == 0)
		{// �X�e�[�W�Z�b�g���I������
			break;
		}

		// �ǂݐ؂�����I��
		if (result == EOF)
		{
			break;
		}
	}
}

//**************************************************
// �u���b�N�̓ǂݍ���
//**************************************************
void ReadBlockDate(FILE* pFile)
{
	char astr[256] = {};	// ��������i�[����ϐ�
	char astrB[256] = {};	// ��������i�[����ϐ�
	float fNum = 0.0f;		// �����i�[�p
	const char* pFileName = NULL;

	SETBLOCK *seBlock = GetBlock();		// �u���b�N���

	// �u���b�N��񏉊���
	seBlock->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	seBlock->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	seBlock->nType = BLOCKTYPE_MAX;
	seBlock->pFilename = NULL;

	// �e�L�X�g��ǂݍ���
	while (1)
	{
		// �e�L�X�g��ǂ�Ō��ʂ���
		int result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "POS") == 0)
		{// �ʒu��ݒ肷��
			//���l��ǂނ���
			result = fscanf(pFile, "%f", &seBlock->pos.x);
			result = fscanf(pFile, "%f", &seBlock->pos.y);
			result = fscanf(pFile, "%f", &seBlock->pos.z);
		}
		else if (strcmp(&astr[0], "ROT") == 0)
		{// ������ݒ肷��
			result = fscanf(pFile, "%f", &seBlock->rot.x);
			result = fscanf(pFile, "%f", &seBlock->rot.y);
			result = fscanf(pFile, "%f", &seBlock->rot.z);
		}
		else if (strcmp(&astr[0], "BLOCKTYPE") == 0)
		{// �^�C�v��ݒ肷��
			result = fscanf(pFile, "%d", &seBlock->nType);

			//switch (seBlock.nType)
			//{
			//case BLOCKTYPE_SNOW:
			//	seBlock.pFilename = "date/xfile/block/Block_Snow_001.x";
			//	break;
			//	
			//case BLOCKTYPE_ICE:
			//	seBlock.pFilename = "date/xfile/block/Block_Ice_001.x";
			//	break;

			//case BLOCKTYPE_GRAVEL:
			//	seBlock.pFilename = "date/xfile/block/Block_Gravel_001.x";
			//	break;

			//default:
			//	seBlock.pFilename = "date/xfile/block/Block_Snow_001.x";
			//	break;
			//}
		}
		else if (strcmp(&astr[0], "BLOCKFILE") == 0)
		{// �^�C�v��ݒ肷��
			result = fscanf(pFile, "%s", &seBlock->astr[0]);
			seBlock->pFilename = &seBlock->astr[0];
		}
		
		if (strcmp(&astr[0], "ENDSETBLOCK") == 0)
		{// �u���b�N��ݒ肵�u���b�N���̓ǂݍ��݂��I������
			SetBlock(*seBlock);
			break;
		}

		// �ǂݐ؂�����I��
		if (result == EOF)
		{
			break;
		}
	}
}
