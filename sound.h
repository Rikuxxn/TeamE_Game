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
	SOUND_LABEL_GAMEOVERBGM,
	SOUND_LABEL_TITLEBGM,
	SOUND_LABEL_INSIGHT,
	SOUND_LABEL_WANDERING,
	SOUND_LABEL_PLAYERSTEP1,
	SOUND_LABEL_PLAYERSTEP2,
	SOUND_LABEL_HEART,
	SOUND_LABEL_HEARTQUICK,
	SOUND_LABEL_BALLCATCH,
	SOUND_LABEL_BALLGET,
	SOUND_LABEL_BALLCLEAR,
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
	SOUND_LABEL_FUSEGET,
	SOUND_LABEL_FUSESET,
	SOUND_LABEL_EMPTYBREATH,
	SOUND_LABEL_OPENDOOR,
	SOUND_LABEL_ENEMYCHASE,
	SOUND_LABEL_TASKOK,
	SOUND_LABEL_MENUOPEN,
	SOUND_LABEL_SELECT,
	SOUND_LABEL_OK,
	SOUND_LABEL_RANK,
	SOUND_LABEL_GAMESTART,
	SOUND_LABEL_MINICLEAR,
	SOUND_LABEL_ENEMYSTEP1,
	SOUND_LABEL_ENEMYSTEP2,

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
HRESULT PlaySound3D(SOUND_LABEL label);
void UpdateSoundPosition(SOUND_LABEL label, float x, float y, float z);
void CalculateCustomPanning(SOUND_LABEL label, FLOAT32* matrix);
void UpdateListener(float x, float y, float z);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif