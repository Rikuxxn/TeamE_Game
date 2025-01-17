//=============================================================================
//
// �C���v�b�g���� [input.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"


//�L�[�̎��
typedef enum
{
	JOYKEY_UP = 0,      //�\���L�[��
	JOYKEY_DOWN = 1,    //�\���L�[��
	JOYKEY_LEFT = 2,    //�\���L�[��
	JOYKEY_RIGHT = 3,   //�\���L�[�E

	JOYKEY_START = 4,   //�X�^�[�g�{�^��
	JOYKEY_BACK = 5,    //�o�b�N�{�^��

	JOYKEY_LS = 6,      //���X�e�B�b�N��������
	JOYKEY_RS = 7,      //�E�X�e�B�b�N��������

	JOYKEY_LB = 8,      //���{�^��
	JOYKEY_RB = 9,      //�E�{�^��

	JOYKEY_LT = 10,     //���g���K�[
	JOYKEY_RT = 11,     //�E�g���K�[

	JOYKEY_A = 12,      //A�{�^��
	JOYKEY_B = 13,      //B�{�^��
	JOYKEY_X = 14,      //X�{�^��
	JOYKEY_Y = 15,      //Y�{�^��

	JOYKEY_MAX
}JOYKEY;


//�v���g�^�C�v�錾
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
