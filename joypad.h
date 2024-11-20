#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "main.h"



//キーの種類
typedef enum
{
	JOYKEY_UP = 0,			//十字キー上
	JOYKEY_DOWN,			//十字キー下
	JOYKEY_LEFT,			//十字キー左
	JOYKEY_RIGHT,			//十字キー右
	JOYKEY_START,			//スタートボタン
	JOYKEY_BACK,			//バックボタン
	JOYKEY_LSTICK_BUTTON,	//Lスティックボタン
	JOYKEY_RSTICK_BUTTON,	//Rスティックボタン
	JOYKEY_L1,				//L1ボタン
	JOYKEY_R1,				//R1ボタン
	JOYKEY_L2,				//L2トリガー
	JOYKEY_R2,				//R2トリガー
	JOYKEY_A,				//Aボタン
	JOYKEY_B,				//Bボタン
	JOYKEY_X,				//Xボタン
	JOYKEY_Y,				//Yボタン
	JOYKEY_MAX
}JOYKEY;

HRESULT InitJoypad(void);
void UpdataJoypad(void);
void UninitJoypad(void);

//ボタン
bool GetJoypadPress(JOYKEY key);	//押しているとき
bool GetJoypadTrigger(JOYKEY key);	//押した瞬間
bool GetJoypadRelease(JOYKEY key);	//離したとき
bool GetJoypadRepeat(JOYKEY key);	//押している間

//トリガー
bool GetJoyTrigger(JOYKEY key);			//押しているとき
bool GetJoyTriggerTrigger(JOYKEY key);	//押したとき
bool GetJoyTriggerRelease(JOYKEY key);	//離したとき
bool GetJoyTriggerRepeat(JOYKEY key);	//押している間

//スティック
bool GetJoyStickL(void);
XINPUT_STATE* GetJoySticAngle(void);

#endif // !_JOYPAD_H_