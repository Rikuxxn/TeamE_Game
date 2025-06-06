//=============================================================================
//
// フェード処理 [fade.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"


//フェードの状態
typedef enum
{
	FADE_NONE=0,      //何もしていない状態
	FADE_IN,          //フェードイン状態
	FADE_OUT,         //フェードアウト状態
	FADE_FOUNDIN,
	FADE_FOUNDOUT,
	FADE_MAX

}FADE;

//プロトタイプ宣言
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(MODE modeNext);
void SetFoundFade(MODE modeNext);
FADE GetFade(void);

#endif
