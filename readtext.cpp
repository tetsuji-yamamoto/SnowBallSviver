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
	char astrOld[256] = {};	// 古い文字列を格納する変数
	int result = 0;			// EOF判定
	bool bComent = false;	// 読まなくていいもの
	SETBLOCK seBlock;		// ブロック情報

	// ブロック情報初期化
	seBlock.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	seBlock.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	seBlock.nType = BLOCKTYPE_MAX;
	seBlock.pFilename = NULL;

	// テキストを読み込む
	while (1)
	{

		if (bComent)
		{// コメントを読んだら
			for (int nCnt = 0; nCnt < 256; nCnt++)
			{// 前回読み取ったのを代入
				astr[nCnt] = astrOld[nCnt];

				if (astrOld[nCnt] == '\0')
				{// ヌル文字なら終わる
					break;
				}
			}

			bComent = false;	// コメント読んでない状態
		}
		else
		{
			for (int nCnt = 0; nCnt < 256; nCnt++)
			{// 古い文字列を更新
				astrOld[nCnt] = astr[nCnt];

				if (astr[nCnt] == '\0')
				{// ヌル文字なら終わる
					break;
				}
			}

			// テキストを読んで結果を代入
			result = fscanf(pFile, "%s", &astr[0]);
		}

		if (strcmp(&astr[0], "=") == 0)
		{// タイプを設定する
			bComent = true;	// コメント読んだよ
		}
		else if (strcmp(&astr[0], "#") == 0)
		{// 位置を設定する
			bComent = true;	// コメント読んだよ
			result = fscanf(pFile, "%s", &astr[0]);
		}
		else if (strcmp(&astr[0], "POS") == 0)
		{// 位置を設定する
			//数値を読むこむ
			result = fscanf(pFile, "%f", &seBlock.pos.x);
			result = fscanf(pFile, "%f", &seBlock.pos.y);
			result = fscanf(pFile, "%f", &seBlock.pos.z);
		}
		else if (strcmp(&astr[0], "ROT") == 0)
		{// 向きを設定する
			result = fscanf(pFile, "%f", &seBlock.rot.x);
			result = fscanf(pFile, "%f", &seBlock.rot.y);
			result = fscanf(pFile, "%f", &seBlock.rot.z);
		}
		else if (strcmp(&astr[0], "BLOCKTYPE") == 0)
		{// タイプを設定する
			result = fscanf(pFile, "%d", &seBlock.nType);
		}
		else if (strcmp(&astr[0], "BLOCKFILE") == 0)
		{// タイプを設定する
			result = fscanf(pFile, "%s", &seBlock.astr[0]);
		}
		else if (strcmp(&astr[0], "ENDSETBLOCK") == 0)
		{// ブロックを設定しブロック情報の読み込みを終了する
			SetBlock(seBlock);
			break;
		}


		// 読み切ったら終了
		if (result == EOF)
		{
			break;
		}
	}
}
