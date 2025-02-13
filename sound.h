//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 高宮祐翔
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
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
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
