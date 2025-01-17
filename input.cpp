//=============================================================================
//
// �C���v�b�g���� [input.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

//�O���[�o���ϐ�
XINPUT_STATE g_joyKeyState;//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_joyKeyStateTrigger;//�W���C�p�b�h�̃g���K�[���
XINPUT_STATE g_joyKeyStateRelease;//�W���C�p�b�h�̃g���K�[���

XINPUT_STATE g_aOldJoyKeyState;//

LPDIRECTINPUT8 g_pInput = NULL;//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//���̓f�o�C�X�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�v���X���
BYTE g_aOldState[NUM_KEY_MAX];//

//XINPUT_STATE g_joyKeyStateTrigger;//�W���C�p�b�h�̃v���X���
bool g_joyKeyFlag[JOYKEY_MAX];

LPDIRECTINPUT8 g_pMouse = NULL;//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;//���̓f�o�C�X�ւ̃|�C���^

//=============================
//�L�[�{�[�h�̏���������
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
//�W���C�p�b�h�̏���������
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
//�L�[�{�[�h�̏I������
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
//�L�[�{�[�h�̍X�V����
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
//�L�[�{�[�h�̃v���X�����擾
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
//�W���C�p�b�h�̏I������
//=====================================================
void UninitJoypad(void)
{

	//XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);

}
//=====================================================
//�W���C�p�b�h�̍X�V����
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
//�W���C�p�b�h�̃v���X�����擾
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
//L2,R2�̏���
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
bool GeyJoyTriggerTrigger(JOYKEY key)//�������Ƃ�
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
//�X�e�B�b�N����
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
//�Q�[���p�b�h�̃g���K�[����
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
//�X�e�B�b�N���̎擾����
//====================================================
XINPUT_STATE* GetJoyStickAngle(void)
{

	return &g_joyKeyState;

}
////====================================================
////�g���K�[���̎擾����
////====================================================
//bool GetJoyTrigger(JOYKEY Key)
//{
//
//	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
//
//}
//=====================================================
//�}�E�X����̏���������
//=====================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	LPDIRECTINPUT8 pDI;

	// DirectInput �I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (VOID**)&pDI, NULL)))
	{
		return E_FAIL; // �G���[��Ԃ�
	}

	//���̓f�o�C�X(�}�E�X)�̐���
	if (FAILED(g_pMouse->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL; // �G���[��Ԃ�
	}

	// �}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL; // �G���[��Ԃ�
	}

	// �}�E�X�̓��샂�[�h��ݒ�
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, 
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return S_OK; // �G���[��Ԃ�
	}

	//// �}�E�X�̓��̓f�o�C�X���A�N�e�B�u��
	//if (FAILED(g_pDevMouse->Acquire()))
	//{
	//	return E_FAIL; // �G���[��Ԃ�
	//}

	// DirectInput �I�u�W�F�N�g������i�s�v�Ȃ̂ŉ���j
	//pDI->Release();

	return S_OK; // ����������
}
//=====================================================
//�}�E�X����̏I������
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

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pMouse != NULL)
	{
		g_pMouse->Release();
		g_pMouse = NULL;
	}
}
//=====================================================
//�}�E�X����̔��菈��
//=====================================================
bool GetMouseState(DIMOUSESTATE* mouseState)
{
	//LPDIRECTINPUTDEVICE8 pMouse = GetMouseDevice(); // �}�E�X�f�o�C�X�擾

	//if (pMouse == NULL)
	//{
	//	return false;
	//}

	//HRESULT hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);

	//if (FAILED(hr))
	//{
	//	// ���̓f�o�C�X�����Z�b�g����Ă���ꍇ�A�Ď擾�����݂�
	//	if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
	//	{
	//		pMouse->Acquire();
	//	}
	//	return false;
	//}

	//return true;

	IDirectInputDevice8* pMouse = GetMouseDevice(); // �}�E�X�f�o�C�X���擾����֐�
	if (pMouse)
	{
		HRESULT hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), mouseState);
		if (FAILED(hr))
		{
			// �Ď擾�����݂�
			pMouse->Acquire();
		}
	}

	return true;

}
//=====================================================
//�}�E�X���̎擾
//=====================================================
LPDIRECTINPUTDEVICE8 GetMouseDevice(void)
{
	return g_pDevMouse;
}


