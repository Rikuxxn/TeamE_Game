//=============================================================================
//
// インプット処理 [input.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"


//キーの種類
typedef enum
{
	JOYKEY_UP = 0,      //十字キー上
	JOYKEY_DOWN = 1,    //十字キー下
	JOYKEY_LEFT = 2,    //十字キー左
	JOYKEY_RIGHT = 3,   //十字キー右

	JOYKEY_START = 4,   //スタートボタン
	JOYKEY_BACK = 5,    //バックボタン

	JOYKEY_LS = 6,      //左スティック押し込み
	JOYKEY_RS = 7,      //右スティック押し込み

	JOYKEY_LB = 8,      //左ボタン
	JOYKEY_RB = 9,      //右ボタン

	JOYKEY_LT = 10,     //左トリガー
	JOYKEY_RT = 11,     //右トリガー

	JOYKEY_A = 12,      //Aボタン
	JOYKEY_B = 13,      //Bボタン
	JOYKEY_X = 14,      //Xボタン
	JOYKEY_Y = 15,      //Yボタン

	JOYKEY_MAX
}JOYKEY;


//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);


HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY Key);

bool GetJoyStick(void);
bool JoyPadTrigger(JOYKEY Key);
bool JoyPadRelease(JOYKEY Key);
XINPUT_STATE* GetJoyStickAngle(void);

bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);

HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
bool GetMouseState(DIMOUSESTATE* mouseState);
LPDIRECTINPUTDEVICE8 GetMouseDevice(void);

#endif
