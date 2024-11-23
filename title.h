#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//タイトルポリゴンタイプ
typedef enum
{
	TITLETYPE_TEST = 0,	//タイトルのテスト
	TITLETYPE_BG,		//タイトルのBG
	TITLETYPE_LOGO,		//タイトルのロゴ
	TITLETYPE_START,	//タイトルのスタートボタン
	TITLETYPE_MAX
}TITLETYPE;

//タイトル演出列挙
typedef enum
{
	TITLEDIRECT_LOGODOWN = 0,			//ロゴが下がってくる
	TITLEDIRECT_STARTAPPEAR,			//スタート出現
	TITLEDIRECT_STARTBRINK,				//スタート点滅
	TITLEDIRECT_STARTBRINK_QUICKLY,		//スタート素早く点滅quickly
}TITLEDIRECT;

//タイトル構造体
typedef struct
{
	const char* pFileName;	//ファイルネーム
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nType;				//タイプ
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bUse;				//使用しているかどうか
}TITLE;

//タイトルの演出構造体
typedef struct
{
	TITLEDIRECT titleDirect;	//タイトル演出順
	int nTimer;					//タイマー
	bool bBrink;				//点滅どっち？
}TITLEDIRECTOR;

//マクロ定義
#define FILE_TEX_TITLE_TEST "data\\TITLE\\texture\\TitleTest_001.jpg"

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(const char* pFileName, D3DXVECTOR3 pos, TITLETYPE type, D3DXCOLOR col, float fWidth, float fHeight);
#endif