#include "readtext.h"
#include "block.h"

//**************************************************
// テキストファイルの読み込み
//**************************************************
void ReadText(void)
{
	// ファイル読み込みオープン
	FILE* pFile = fopen("date\\text\\stage.txt", "r");
	char astr[256] = {};	// 文字列を格納する変数

	// テキストを読み込む
	while (1)
	{
		// テキストを読んで結果を代入
		int result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "STAGESET") == 0)
		{// セットステージを行う
			SetStage(pFile);
		}

		// 読み切ったら終了
		if (result == EOF)
		{
			break;
		}
	}

	fclose(pFile);
}

//**************************************************
// ステージの読み込み
//**************************************************
void SetStage(FILE *pFile)
{
	char astr[256] = {};	// 文字列を格納する変数

	// テキストを読み込む
	while (1)
	{

		// テキストを読んで結果を代入
		int result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "SETBLOC") == 0)
		{// ブロック情報を読み込む
			ReadBlockDate(pFile);
		}

		if (strcmp(&astr[0], "ENDSTAGESET") == 0)
		{// ステージセットを終了する
			break;
		}

		// 読み切ったら終了
		if (result == EOF)
		{
			break;
		}
	}
}

//**************************************************
// ブロックの読み込み
//**************************************************
void ReadBlockDate(FILE* pFile)
{
	char astr[256] = {};	// 文字列を格納する変数
	char astrB[256] = {};	// 文字列を格納する変数
	float fNum = 0.0f;		// 数字格納用
	const char* pFileName = NULL;

	SETBLOCK *seBlock = GetBlock();		// ブロック情報

	// ブロック情報初期化
	seBlock->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	seBlock->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	seBlock->nType = BLOCKTYPE_MAX;
	seBlock->pFilename = NULL;

	// テキストを読み込む
	while (1)
	{
		// テキストを読んで結果を代入
		int result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "POS") == 0)
		{// 位置を設定する
			//数値を読むこむ
			result = fscanf(pFile, "%f", &seBlock->pos.x);
			result = fscanf(pFile, "%f", &seBlock->pos.y);
			result = fscanf(pFile, "%f", &seBlock->pos.z);
		}
		else if (strcmp(&astr[0], "ROT") == 0)
		{// 向きを設定する
			result = fscanf(pFile, "%f", &seBlock->rot.x);
			result = fscanf(pFile, "%f", &seBlock->rot.y);
			result = fscanf(pFile, "%f", &seBlock->rot.z);
		}
		else if (strcmp(&astr[0], "BLOCKTYPE") == 0)
		{// タイプを設定する
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
		{// タイプを設定する
			result = fscanf(pFile, "%s", &seBlock->astr[0]);
			seBlock->pFilename = &seBlock->astr[0];
		}
		
		if (strcmp(&astr[0], "ENDSETBLOCK") == 0)
		{// ブロックを設定しブロック情報の読み込みを終了する
			SetBlock(*seBlock);
			break;
		}

		// 読み切ったら終了
		if (result == EOF)
		{
			break;
		}
	}
}
