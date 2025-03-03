//=============================================================================
//
// �C���v�b�g���� [input.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX (256)						// �L�[�̍ő吔
#define CURSOR_SPEED (0.7f)						// �J�[�\���ړ����x

//�O���[�o���ϐ�
XINPUT_STATE g_joyKeyState;						// �W���C�p�b�h�̃v���X���
XINPUT_STATE g_joyKeyStateTrigger;				// �W���C�p�b�h�̃g���K�[���
XINPUT_STATE g_joyKeyStateRelease;				// �W���C�p�b�h�̃g���K�[���

XINPUT_STATE g_aOldJoyKeyState;

LPDIRECTINPUT8 g_pInput = NULL;					// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		// ���̓f�o�C�X�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];					// �L�[�{�[�h�v���X���
BYTE g_aOldState[NUM_KEY_MAX];

bool g_joyKeyFlag[JOYKEY_MAX];

//LPDIRECTINPUT8 g_pMouse = NULL;				// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;		// ���̓f�o�C�X�ւ̃|�C���^
DIMOUSESTATE g_mouseState;

//=============================
// �L�[�{�[�h�̏���������
//=============================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return S_OK;
	}

}
//=====================================================
// �W���C�p�b�h�̏���������
//=====================================================
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));


	//�������̃N���A
	memset(&g_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));


	//�������̃N���A
	memset(&g_aOldJoyKeyState, 0, sizeof(XINPUT_STATE));


	//XInput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}
//=============================================
// �L�[�{�[�h�̏I������
//=============================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();//�L�[�{�[�h�ւ̃A�N�Z�X����j��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}

}
//================================================
// �L�[�{�[�h�̍X�V����
//================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];//�ЂƂO�̃L�[�{�[�h�v���X����ۑ�
	}

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}
//=======================================
// �L�[�{�[�h�̃v���X�����擾
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
// �W���C�p�b�h�̏I������
//=====================================================
void UninitJoypad(void)
{

	//XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);

}
//=====================================================
// �W���C�p�b�h�̍X�V����
//=====================================================
void UpdateJoypad(void)
{
	int nCntJoy;

	XINPUT_STATE joyKeyState;//�W���C�p�b�h�̓��͏��

	g_aOldJoyKeyState = g_joyKeyState;

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		WORD Button = joyKeyState.Gamepad.wButtons;

		WORD OldButton = g_joyKeyState.Gamepad.wButtons;

		g_joyKeyStateTrigger.Gamepad.wButtons=Button&~OldButton;
		g_joyKeyStateRelease.Gamepad.wButtons = OldButton & ~Button;

		g_joyKeyState = joyKeyState;//�W���C�p�b�h�̃v���X����ۑ�
	}

	//Press
	for (nCntJoy = 0; nCntJoy < JOYKEY_MAX; nCntJoy++)
	{
		g_joyKeyFlag[nCntJoy] = (g_joyKeyState.Gamepad.wButtons & (0x01 << nCntJoy)) ? true : false;
	}
}
//=====================================================
// �W���C�p�b�h�̃v���X
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
////====================================================
//// L2,R2�̏���
////====================================================
//bool GetJoyTrigger(JOYKEY key)
//{
//	if (key == JOYKEY_LT)
//	{
//		return (g_joyKeyState.Gamepad.bLeftTrigger) ? true : false;
//	}
//	else if (key == JOYKEY_RT)
//	{
//		return (g_joyKeyState.Gamepad.bRightTrigger) ? true : false;
//	}
//}
//bool GeyJoyTriggerTrigger(JOYKEY key)//�������Ƃ�
//{
//	bool JoyStick = false;
//
//	if (key == JOYKEY_LT)
//	{
//		if ((g_joyKeyState.Gamepad.bLeftTrigger > 0) && !(g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0))
//		{
//			JoyStick = true;
//		}
//	}
//	else if (key == JOYKEY_RT)
//	{
//		if ((g_joyKeyState.Gamepad.bRightTrigger > 0) && !(g_aOldJoyKeyState.Gamepad.bRightTrigger > 0))
//		{
//			JoyStick = true;
//		}
//
//	}
//	return JoyStick;
//}
//bool GetJoyTriggerRelease(JOYKEY key)
//{
//	bool JoyStick = false;
//	if (key == JOYKEY_LT)
//	{
//		if ((g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0) && !(g_joyKeyState.Gamepad.bLeftTrigger > 0))
//		{
//			JoyStick = true;
//		}
//	}
//	else if (key == JOYKEY_RT)
//	{
//		if ((g_aOldJoyKeyState.Gamepad.bRightTrigger > 0) && !(g_joyKeyState.Gamepad.bRightTrigger > 0))
//		{
//			JoyStick = true;
//		}
//
//	}
//	return JoyStick;
//
//}
//====================================================
// �X�e�B�b�N����
//====================================================
bool GetJoyStick()
{
	bool joykey = false;
	//�^�񒆂���Ȃ�������
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
// �X�e�B�b�N���̎擾����
//====================================================
XINPUT_STATE* GetJoyStickAngle(void)
{

	return &g_joyKeyState;

}
////====================================================
//// �g���K�[���̎擾����
////====================================================
//bool GetJoyTrigger(JOYKEY Key)
//{
//
//	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
//
//}
//=====================================================
// �}�E�X����̏���������
//=====================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	LPDIRECTINPUT8 pDI;

	// DirectInput �I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&pDI, NULL)))
	{
		MessageBox(NULL, "DirectInput8Create �Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	// ���̓f�o�C�X(�}�E�X)�̐���
	if (FAILED(pDI->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		MessageBox(NULL, "�}�E�X�f�o�C�X�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);
		pDI->Release();
		return E_FAIL;
	}

	// �}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		MessageBox(NULL, "�}�E�X�̃f�[�^�t�H�[�}�b�g�ݒ�Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);
		pDI->Release();
		return E_FAIL;
	}

	// �E�B���h�E����A�N�e�B�u�ł��}�E�X���g�p�\�ɂ���
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd,
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		MessageBox(NULL, "SetCooperativeLevel �Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	// �}�E�X�̓��̓f�o�C�X���A�N�e�B�u��
	if (FAILED(g_pDevMouse->Acquire()))
	{
		MessageBox(NULL, "�}�E�X�f�o�C�X�̃A�N�e�B�u���Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);
		pDI->Release();
		return E_FAIL;
	}

	return S_OK; // ����������
}
//=====================================================
// �}�E�X����̏I������
//=====================================================
void UninitMouse(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pDevMouse)
	{
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	////DirectInput�I�u�W�F�N�g�̔j��
	//if (g_pMouse != NULL)
	//{
	//	g_pMouse->Release();
	//	g_pMouse = NULL;
	//}
}
//=====================================================
// �}�E�X����̍X�V����
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
// �}�E�X�̏��
//=====================================================
bool GetMouseState(DIMOUSESTATE* mouseState)
{
	// �}�E�X�f�o�C�X���擾
	LPDIRECTINPUTDEVICE8 pMouse = GetMouseDevice();
	if (pMouse == NULL)
	{
		return false;
	}

	// �}�E�X�̏�Ԃ��擾(��������������)
	HRESULT hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);

	if (FAILED(hr))
	{
		// ���̓f�o�C�X�����Z�b�g����Ă���ꍇ�A�Ď擾�����݂�
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		{
			pMouse->Acquire();

			// �Ď擾�����݂�
			hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);
			if (FAILED(hr))
			{
				return false;
			}
		}
		else
		{
			//�G���[�̏ꍇ
			return false;
		}
	}

	return true; // ����Ɏ擾�ł����ꍇ
}
//=====================================================
// �}�E�X�̃v���X���
//=====================================================
bool GetMouseButtonPress(int button)
{
	return (g_mouseState.rgbButtons[button] & 0x80) != 0;
}
//=====================================================
// �}�E�X�̃g���K�[���
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
// �}�E�X�̃����[�X���
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
// �}�E�X�z�C�[���̃X�N���[���ʂ��擾����֐�
//=====================================================
int GetMouseWheel(void)
{
	const int ScrollUnit = 120; // �ʏ�̃X�N���[���P��

	int wheelValue = g_mouseState.lZ;

	// �X�N���[���P�ʂɊ�Â��Đ��K��
	if (wheelValue != 0)
	{
		wheelValue /= ScrollUnit; // ���K�����ꂽ�X�N���[���ʂ�Ԃ�
	}

	return wheelValue; // ���i��X�N���[���j�A���i���X�N���[���j�A0�i�X�N���[���Ȃ��j
}
//=====================================================
// �Q�[���p�b�h�Ń}�E�X�ړ�����
//=====================================================
void UpdateCursorWithGamepad(void)
{
	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	// �}�E�X�J�[�\���̌��݈ʒu���擾
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	// ���X�e�B�b�N�̓��͒l���擾 (-1000 �` 1000 �͈̔�)
	float moveX = pStick->Gamepad.sThumbLX / 1000.0f;
	float moveY = pStick->Gamepad.sThumbLY / 1000.0f;

	// ����臒l�𒴂����ꍇ�ɃJ�[�\�����ړ�
	if (fabs(moveX) > 0.1f || fabs(moveY) > 0.1f)
	{
		cursorPos.x += (LONG)(moveX * CURSOR_SPEED);
		cursorPos.y -= (LONG)(moveY * CURSOR_SPEED);

		// �J�[�\���ʒu���X�V
		SetCursorPos(cursorPos.x, cursorPos.y);
	}
}
//=====================================================
// �}�E�X�J�[�\���\������
//=====================================================
void SetCursorVisibility(bool visible)
{
	static int cursorCount = 0;

	if (visible)
	{
		// �J�[�\����\��
		while (cursorCount < 0)
		{
			ShowCursor(TRUE);
			cursorCount++;
		}
	}
	else
	{
		// �J�[�\�����\��
		while (cursorCount >= 0)
		{
			ShowCursor(FALSE);
			cursorCount--;
		}
	}
}
//=====================================================
// �}�E�X���̎擾
//=====================================================
LPDIRECTINPUTDEVICE8 GetMouseDevice(void)
{
	return g_pDevMouse;
}