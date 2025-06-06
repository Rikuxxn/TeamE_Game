//=============================================================================
//
// インプット処理 [input.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX (256)						// キーの最大数
#define CURSOR_SPEED (0.7f)						// カーソル移動速度

//グローバル変数
XINPUT_STATE g_joyKeyState;						// ジョイパッドのプレス情報
XINPUT_STATE g_joyKeyStateTrigger;				// ジョイパッドのトリガー情報
XINPUT_STATE g_joyKeyStateRelease;				// ジョイパッドのトリガー情報

XINPUT_STATE g_aOldJoyKeyState;

LPDIRECTINPUT8 g_pInput = NULL;					// DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		// 入力デバイスへのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];					// キーボードプレス情報
BYTE g_aOldState[NUM_KEY_MAX];

bool g_joyKeyFlag[JOYKEY_MAX];

//LPDIRECTINPUT8 g_pMouse = NULL;				// DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;		// 入力デバイスへのポインタ
DIMOUSESTATE g_mouseState;

//=============================
// キーボードの初期化処理
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

	return S_OK;
}
//=====================================================
// ジョイパッドの初期化処理
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
// キーボードの終了処理
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
// キーボードの更新処理
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
// キーボードのプレス情報を取得
//=======================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//===========================================
// 何かしらのキーが押されているかチェック
//===========================================
bool GetAnyKeyPress(void)
{
	for (int i = 0; i < NUM_KEY_MAX; i++)
	{
		if (g_aKeyState[i] & 0x80) // キーが押されている
		{
			return true;
		}
	}
	return false;
}
//=======================================
// キーボードのトリガー情報を取得
//=======================================
bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//============================================
// 何かしらのキーが新しく押されたかチェック
//============================================
bool GetAnyKeyTrigger(void)
{
	for (int i = 0; i < NUM_KEY_MAX; i++)
	{
		if ((g_aKeyState[i] & 0x80) && !(g_aOldState[i] & 0x80)) // 新しく押されたキーがある
		{
			return true;
		}
	}
	return false;
}
//=======================================
// キーボードのリリース情報を取得
//=======================================
bool KeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//============================================
// 何かしらのキーが離されたかチェック
//============================================
bool GetAnyKeyRelease(void)
{
	for (int i = 0; i < NUM_KEY_MAX; i++)
	{
		if ((g_aOldState[i] & 0x80) && !(g_aKeyState[i] & 0x80)) // 離されたキーがある
		{
			return true;
		}
	}
	return false;
}
//=======================================
// キーボードのリピート情報を取得
//=======================================
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
// ジョイパッドの終了処理
//=====================================================
void UninitJoypad(void)
{

	//XInputのステートを設定(無効にする)
	XInputEnable(false);

}
//=====================================================
// ジョイパッドの更新処理
//=====================================================
void UpdateJoypad(void)
{
	XINPUT_STATE joyKeyState;

	g_aOldJoyKeyState = g_joyKeyState; // 前フレームの状態を保存

	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		WORD Button = joyKeyState.Gamepad.wButtons;
		WORD OldButton = g_joyKeyState.Gamepad.wButtons;

		g_joyKeyStateTrigger.Gamepad.wButtons = (Button & ~OldButton); // 新しく押されたボタン
		g_joyKeyStateRelease.Gamepad.wButtons = (OldButton & ~Button); // 離されたボタン

		g_joyKeyState = joyKeyState;
	}
}
//=====================================================
// ジョイパッドのプレス
//=====================================================
bool GetJoypadPress(JOYKEY Key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
//=====================================================
// 何かしらのボタンが押されているか判定（プレス）
//=====================================================
bool GetAnyJoypadPress(void)
{
	return g_joyKeyState.Gamepad.wButtons != 0;
}
//=====================================================
// ジョイパッドのトリガー
//=====================================================
bool JoyPadTrigger(JOYKEY Key)
{
	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
//=====================================================
// 何かしらのボタンが押されているか判定（トリガー）
//=====================================================
bool GetAnyJoypadTrigger(void)
{
	return g_joyKeyStateTrigger.Gamepad.wButtons != 0;
}
//=====================================================
// ジョイパッドのリリース
//=====================================================
bool JoyPadRelease(JOYKEY Key)
{
	bool released = (g_joyKeyStateRelease.Gamepad.wButtons & (0x01 << Key)) ? true : false;

	return released;
}
//=====================================================
// 何かしらのボタンが押されているか判定（リリース）
//=====================================================
bool GetAnyJoypadRelease(void)
{
	return g_joyKeyStateRelease.Gamepad.wButtons != 0;
}
//====================================================
// スティック処理
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
// スティック情報の取得処理
//====================================================
XINPUT_STATE* GetJoyStickAngle(void)
{

	return &g_joyKeyState;

}
////====================================================
//// トリガー情報の取得処理
////====================================================
//bool GetJoyTrigger(JOYKEY Key)
//{
//
//	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
//
//}
//=====================================================
// マウス操作の初期化処理
//=====================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	LPDIRECTINPUT8 pDI;

	// DirectInput オブジェクトの作成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&pDI, NULL)))
	{
		MessageBox(NULL, "DirectInput8Create に失敗しました", "エラー", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	// 入力デバイス(マウス)の生成
	if (FAILED(pDI->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		MessageBox(NULL, "マウスデバイスの作成に失敗しました", "エラー", MB_OK | MB_ICONERROR);
		pDI->Release();
		return E_FAIL;
	}

	// マウスのデータフォーマットを設定
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		MessageBox(NULL, "マウスのデータフォーマット設定に失敗しました", "エラー", MB_OK | MB_ICONERROR);
		pDI->Release();
		return E_FAIL;
	}

	// ウィンドウが非アクティブでもマウスを使用可能にする
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd,
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		MessageBox(NULL, "SetCooperativeLevel に失敗しました", "エラー", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	// マウスの入力デバイスをアクティブ化
	if (FAILED(g_pDevMouse->Acquire()))
	{
		MessageBox(NULL, "マウスデバイスのアクティブ化に失敗しました", "エラー", MB_OK | MB_ICONERROR);
		pDI->Release();
		return E_FAIL;
	}

	return S_OK; // 初期化成功
}
//=====================================================
// マウス操作の終了処理
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

	////DirectInputオブジェクトの破棄
	//if (g_pMouse != NULL)
	//{
	//	g_pMouse->Release();
	//	g_pMouse = NULL;
	//}
}
//=====================================================
// マウス操作の更新処理
//=====================================================
void UpdateMouse(void)
{
	if (g_pDevMouse)
	{
		HRESULT hr = g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_mouseState);
		if (FAILED(hr))
		{
			if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
			{
				g_pDevMouse->Acquire();
			}
		}
	}
}
//=====================================================
// マウスの状態
//=====================================================
bool GetMouseState(DIMOUSESTATE* mouseState)
{
	// マウスデバイスを取得
	LPDIRECTINPUTDEVICE8 pMouse = GetMouseDevice();
	if (pMouse == NULL)
	{
		return false;
	}

	// マウスの状態を取得(長いから代入した)
	HRESULT hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);

	if (FAILED(hr))
	{
		// 入力デバイスがリセットされている場合、再取得を試みる
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		{
			pMouse->Acquire();

			// 再取得を試みる
			hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);
			if (FAILED(hr))
			{
				return false;
			}
		}
		else
		{
			//エラーの場合
			return false;
		}
	}

	return true; // 正常に取得できた場合
}
//=====================================================
// マウスのプレス情報
//=====================================================
bool GetMouseButtonPress(int button)
{
	return (g_mouseState.rgbButtons[button] & 0x80) != 0;
}
//=====================================================
// マウスのトリガー情報
//=====================================================
bool GetMouseButtonTrigger(int button)
{
	static DIMOUSESTATE oldState = {};

	bool trigger = (g_mouseState.rgbButtons[button] & 0x80) &&
		!(oldState.rgbButtons[button] & 0x80);

	oldState = g_mouseState;  // Update previous state
	return trigger;
}
//=====================================================
// マウスのリリース情報
//=====================================================
bool GetMouseButtonRelease(int button)
{
	static DIMOUSESTATE oldState = {};

	bool release = !(g_mouseState.rgbButtons[button] & 0x80) &&
		(oldState.rgbButtons[button] & 0x80);

	oldState = g_mouseState;  // Update previous state
	return release;
}
//=====================================================
// マウスホイールのスクロール量を取得する関数
//=====================================================
int GetMouseWheel(void)
{
	const int ScrollUnit = 120; // 通常のスクロール単位

	int wheelValue = g_mouseState.lZ;

	// スクロール単位に基づいて正規化
	if (wheelValue != 0)
	{
		wheelValue /= ScrollUnit; // 正規化されたスクロール量を返す
	}

	return wheelValue; // 正（上スクロール）、負（下スクロール）、0（スクロールなし）
}
//=====================================================
// ゲームパッドでマウス移動処理
//=====================================================
void UpdateCursorWithGamepad(void)
{
	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	// マウスカーソルの現在位置を取得
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	// 左スティックの入力値を取得 (-1000 〜 1000 の範囲)
	float moveX = pStick->Gamepad.sThumbLX / 1000.0f;
	float moveY = pStick->Gamepad.sThumbLY / 1000.0f;

	// 一定の閾値を超えた場合にカーソルを移動
	if (fabs(moveX) > 0.1f || fabs(moveY) > 0.1f)
	{
		cursorPos.x += (LONG)(moveX * CURSOR_SPEED);
		cursorPos.y -= (LONG)(moveY * CURSOR_SPEED);

		// カーソル位置を更新
		SetCursorPos(cursorPos.x, cursorPos.y);
	}
}
//=====================================================
// マウスカーソル表示処理
//=====================================================
void SetCursorVisibility(bool visible)
{
	static int cursorCount = 0;

	if (visible)
	{
		// カーソルを表示
		while (cursorCount < 0)
		{
			ShowCursor(TRUE);
			cursorCount++;
		}
	}
	else
	{
		// カーソルを非表示
		while (cursorCount >= 0)
		{
			ShowCursor(FALSE);
			cursorCount--;
		}
	}
}
//=====================================================
// マウス情報の取得
//=====================================================
LPDIRECTINPUTDEVICE8 GetMouseDevice(void)
{
	return g_pDevMouse;
}