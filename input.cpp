//=============================================================================
//
// インプット処理 [input.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX (256)//キーの最大数

//グローバル変数
XINPUT_STATE g_joyKeyState;//ジョイパッドのプレス情報
XINPUT_STATE g_joyKeyStateTrigger;//ジョイパッドのトリガー情報
XINPUT_STATE g_joyKeyStateRelease;//ジョイパッドのトリガー情報

XINPUT_STATE g_aOldJoyKeyState;//

LPDIRECTINPUT8 g_pInput = NULL;//DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//入力デバイスへのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];//キーボードプレス情報
BYTE g_aOldState[NUM_KEY_MAX];//

//XINPUT_STATE g_joyKeyStateTrigger;//ジョイパッドのプレス情報
bool g_joyKeyFlag[JOYKEY_MAX];

LPDIRECTINPUT8 g_pMouse = NULL;//DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;//入力デバイスへのポインタ

//=============================
//キーボードの初期化処理
//=============================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return S_OK;
	}

}
//=====================================================
//ジョイパッドの初期化処理
//=====================================================
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));


	//メモリのクリア
	memset(&g_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));


	//メモリのクリア
	memset(&g_aOldJoyKeyState, 0, sizeof(XINPUT_STATE));


	//XInputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}
//=============================================
//キーボードの終了処理
//=============================================
void UninitKeyboard(void)
{
	//入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();//キーボードへのアクセス権を破棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}

}
//================================================
//キーボードの更新処理
//================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力情報
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];//ひとつ前のキーボードプレス情報を保存
	}

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//キーボードプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}
//=======================================
//キーボードのプレス情報を取得
//=======================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//
bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//
bool KeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//
bool KeyboardRepeat(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//=====================================================
//ジョイパッドの終了処理
//=====================================================
void UninitJoypad(void)
{

	//XInputのステートを設定(無効にする)
	XInputEnable(false);

}
//=====================================================
//ジョイパッドの更新処理
//=====================================================
void UpdateJoypad(void)
{
	int nCntJoy;

	XINPUT_STATE joyKeyState;//ジョイパッドの入力情報

	g_aOldJoyKeyState = g_joyKeyState;

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		WORD Button = joyKeyState.Gamepad.wButtons;

		WORD OldButton = g_joyKeyState.Gamepad.wButtons;

		g_joyKeyStateTrigger.Gamepad.wButtons=Button&~OldButton;
		g_joyKeyStateRelease.Gamepad.wButtons = OldButton & ~Button;

		g_joyKeyState = joyKeyState;//ジョイパッドのプレス情報を保存
	}

	//Press
	for (nCntJoy = 0; nCntJoy < JOYKEY_MAX; nCntJoy++)
	{
		g_joyKeyFlag[nCntJoy] = (g_joyKeyState.Gamepad.wButtons & (0x01 << nCntJoy)) ? true : false;
	}
}
//=====================================================
//ジョイパッドのプレス情報を取得
//=====================================================
bool GetJoypadPress(JOYKEY Key)
{

	return (g_joyKeyState.Gamepad.wButtons & (0x01 << Key)) ? true : false;

}
bool JoyPadTrigger(JOYKEY Key)
{

	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;

}
bool JoyPadRelease(JOYKEY Key)
{

	return (g_joyKeyStateRelease.Gamepad.wButtons & (0x01 << Key)) ? true : false;

}

//====================================================
//L2,R2の処理
//====================================================
bool GetJoyTrigger(JOYKEY key)
{
	if (key == JOYKEY_LT)
	{
		return (g_joyKeyState.Gamepad.bLeftTrigger) ? true : false;
	}
	else if (key == JOYKEY_RT)
	{
		return (g_joyKeyState.Gamepad.bRightTrigger) ? true : false;

	}
}
bool GeyJoyTriggerTrigger(JOYKEY key)//押したとき
{
	bool JoyStick = false;

	if (key == JOYKEY_LT)
	{
		if ((g_joyKeyState.Gamepad.bLeftTrigger > 0) && !(g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_RT)
	{
		if ((g_joyKeyState.Gamepad.bRightTrigger > 0) && !(g_aOldJoyKeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}

	}
	return JoyStick;
}
bool GetJoyTriggerRelease(JOYKEY key)
{
	bool JoyStick = false;
	if (key == JOYKEY_LT)
	{
		if ((g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0) && !(g_joyKeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_RT)
	{
		if ((g_aOldJoyKeyState.Gamepad.bRightTrigger > 0) && !(g_joyKeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}

	}
	return JoyStick;

}
//====================================================
//スティック処理
//====================================================
bool GetJoyStick()
{
	bool joykey = false;
	//真ん中じゃなかったら
	if (g_joyKeyState.Gamepad.sThumbLX >= 100 ||
		g_joyKeyState.Gamepad.sThumbLX <= -100 ||
		g_joyKeyState.Gamepad.sThumbLY >= 100 ||
		g_joyKeyState.Gamepad.sThumbLY <= -100)
	{
		joykey = true;
	}
	return joykey;
}
//====================================================
//ゲームパッドのトリガー処理
//====================================================
//bool JoyPadTrigger(JOYKEY Key)
//{
//
//	//bool Trigger = false;
//	//if (g_joyKeyState.Gamepad.wButtons == (0x01 << Key))
//	//{
//
//	//	if (g_joyKeyState.Gamepad.wButtons != g_aOldJoyKeyState.Gamepad.wButtons)
//	//	{
//	//		Trigger = true;
//	//	}
//
//	//}
//
//	//return Trigger;
//
//
//	bool joykey = false;
//	if (g_joyKeyState.Gamepad.wButtons & (0x01 << Key) && !(g_aOldJoyKeyState.Gamepad.wButtons & (0x01 << Key)))
//	{
//
//		joykey = true;
//
//	}
//	return joykey;
//
//}
//====================================================
//スティック情報の取得処理
//====================================================
XINPUT_STATE* GetJoyStickAngle(void)
{

	return &g_joyKeyState;

}
////====================================================
////トリガー情報の取得処理
////====================================================
//bool GetJoyTrigger(JOYKEY Key)
//{
//
//	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
//
//}
//=====================================================
//マウス操作の初期化処理
//=====================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	LPDIRECTINPUT8 pDI;

	// DirectInput オブジェクトの作成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (VOID**)&pDI, NULL)))
	{
		return E_FAIL; // エラーを返す
	}

	//入力デバイス(マウス)の生成
	if (FAILED(g_pMouse->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL; // エラーを返す
	}

	// マウスのデータフォーマットを設定
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL; // エラーを返す
	}

	// マウスの動作モードを設定
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, 
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return S_OK; // エラーを返す
	}

	//// マウスの入力デバイスをアクティブ化
	//if (FAILED(g_pDevMouse->Acquire()))
	//{
	//	return E_FAIL; // エラーを返す
	//}

	// DirectInput オブジェクトを解放（不要なので解放）
	//pDI->Release();

	return S_OK; // 初期化成功
}
//=====================================================
//マウス操作の終了処理
//=====================================================
void UninitMouse(void)
{
	//入力デバイスの破棄
	if (g_pDevMouse)
	{
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pMouse != NULL)
	{
		g_pMouse->Release();
		g_pMouse = NULL;
	}
}
//=====================================================
//マウス操作の判定処理
//=====================================================
bool GetMouseState(DIMOUSESTATE* mouseState)
{
	//LPDIRECTINPUTDEVICE8 pMouse = GetMouseDevice(); // マウスデバイス取得

	//if (pMouse == NULL)
	//{
	//	return false;
	//}

	//HRESULT hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);

	//if (FAILED(hr))
	//{
	//	// 入力デバイスがリセットされている場合、再取得を試みる
	//	if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
	//	{
	//		pMouse->Acquire();
	//	}
	//	return false;
	//}

	//return true;

	IDirectInputDevice8* pMouse = GetMouseDevice(); // マウスデバイスを取得する関数
	if (pMouse)
	{
		HRESULT hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), mouseState);
		if (FAILED(hr))
		{
			// 再取得を試みる
			pMouse->Acquire();
		}
	}

	return true;

}
//=====================================================
//マウス情報の取得
//=====================================================
LPDIRECTINPUTDEVICE8 GetMouseDevice(void)
{
	return g_pDevMouse;
}


