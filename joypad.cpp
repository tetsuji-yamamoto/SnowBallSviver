#include "joypad.h"

XINPUT_STATE g_joyKeyState;			// ジョイパッドのプレス情報
XINPUT_STATE g_aOldJoyKeyState;		// ジョイパッドの古いプレス情報
XINPUT_STATE g_joyKeyStateTrigger;	// ジョイパッドのトリガー情報
XINPUT_STATE g_joyKeyStateRepeat;	// ジョイパッドのリピート情報
XINPUT_STATE g_joyKeyStateRelease;	// ジョイパッドのリリース情報

//***********************************************
// ジョイパッドの初期化処理
//***********************************************
HRESULT InitJoypad(void)
{
	// メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	// Xinputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}

//***********************************************
//ジョイパッドの終了処理
//***********************************************
void UninitJoypad(void)
{
	// Xinputのステートを設定(無効にする)
	XInputEnable(false);
}

//***********************************************
// ジョイパッドの更新処理
//***********************************************
void UpdataJoypad(void)
{
	int nCntJoy;

	XINPUT_STATE joyKeyState;	// ジョイパッドの入力処理

	// ひとつ前のキーボードプレス情報を保存
	g_aOldJoyKeyState = g_joyKeyState;

	// ジョイパッドの状態を取得
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_joyKeyState = joyKeyState;	// ジョイパッドのプレス情報を保存

		// 情報を渡して
		WORD Button = g_joyKeyState.Gamepad.wButtons;
		WORD OldButton = g_aOldJoyKeyState.Gamepad.wButtons;

		// 計算結果を代入
		g_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;
		g_joyKeyStateRelease.Gamepad.wButtons = OldButton & ~Button;
		g_joyKeyStateRepeat.Gamepad.wButtons = Button;
	}
}

//***********************************************
//ジョイパッドボタンを押しているとき
//***********************************************
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
//ジョイパッドボタンを押した瞬間
//***********************************************
bool GetJoypadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;

	//return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
//ジョイパッドボタンを離したとき
//***********************************************
bool GetJoypadRelease(JOYKEY key)
{
	return (g_joyKeyStateRelease.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
//ジョイパッドボタンを押している間
//***********************************************
bool GetJoypadRepeat(JOYKEY key)
{
	return (g_joyKeyStateRepeat.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
//L2,R2処理
//***********************************************
bool GetJoyTrigger(JOYKEY key)
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		return (g_joyKeyState.Gamepad.bLeftTrigger) ? true : false;
	}
	else if (key == JOYKEY_R2)
	{
		return (g_joyKeyState.Gamepad.bRightTrigger) ? true : false;
	}
	return JoyStick;

}
bool GetJoyTriggerTrigger(JOYKEY key)//押したとき
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		if ((g_joyKeyState.Gamepad.bLeftTrigger > 0) && !(g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_R2)
	{
		if ((g_joyKeyState.Gamepad.bRightTrigger > 0) && !(g_aOldJoyKeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}
bool GetJoyTriggerRelease(JOYKEY key)//離したとき
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0) && !(g_joyKeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_R2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bRightTrigger > 0) && !(g_joyKeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}
bool GetJoyTriggerRepeat(JOYKEY key)//押している間
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0) && (g_joyKeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_R2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bRightTrigger > 0) && (g_joyKeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}

//------------------------
//スティック処理
//------------------------
bool GetJoyStickL()
{
	bool joykey = false;
	//真ん中じゃなかったら
	if (g_joyKeyState.Gamepad.sThumbLX >= 2000 ||
		g_joyKeyState.Gamepad.sThumbLX <= -2000 ||
		g_joyKeyState.Gamepad.sThumbLY >= 2000 ||
		g_joyKeyState.Gamepad.sThumbLY <= -2000)
	{
		joykey = true;
	}
	return joykey;
}

//------------------------
//スティック情報の取得
//------------------------
XINPUT_STATE* GetJoySticAngle(void)
{
	return &g_joyKeyState;
}