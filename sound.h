//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���{�S��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_GAMEBGM = 0,
	SOUND_LABEL_STEP1,
	SOUND_LABEL_STEP2,
	SOUND_LABEL_CRANEDOWN,
	SOUND_LABEL_CRANEUP,
	SOUND_LABEL_CRANEGET,
	SOUND_LABEL_STSHOT,
	SOUND_LABEL_STHIT,
	SOUND_LABEL_STDEAD,
	SOUND_LABEL_STCLEAR,
	SOUND_LABEL_PASSPUSH,
	SOUND_LABEL_PASSWRONG,
	SOUND_LABEL_PASSCORRECT,

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
