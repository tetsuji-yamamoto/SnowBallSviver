#include "writetext.h"
#include "block.h"

//**************************************************
// テキストファイルの書き込み
//**************************************************
void WriteText(void)
{
	// ファイル読み込みオープン
	FILE* pFile = fopen("date\\text\\writeStage.txt", "w");
	char astr[256] = {};	// 文字列を格納する変数

	// ステージを書き込む
	WriteStage(pFile);

	fclose(pFile);
}

//**************************************************
// ステージの書き込み
//**************************************************
void WriteStage(FILE* pFile)
{
	// 書き込む
	fprintf(pFile,"%s\n\n","STAGESET");
	WriteBlockDate(pFile);
	fprintf(pFile,"%s\n","ENDSTAGESET");

}

//**************************************************
// ブロックの書きこみ
//**************************************************
void WriteBlockDate(FILE* pFile)
{
	BLOCK* pBlock = GetBlock();	// ブロック情報取得
	BLOCKMANAGER* pBlockMane = GetBlockManager();	// ブロック管理情報取得

	// 使っているブロック分テキストを読み込む
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
