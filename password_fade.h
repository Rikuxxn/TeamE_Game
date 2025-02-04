//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

typedef enum
{
	FADE_NONE=0,
	FADE_IN,
	FADE_OUT,
	FADE_DAMAGE,
	FADE_MAX
}PASSWORDFADE;

//プロト
void InitPasswordFade(MODE modeNext);
void UninitPasswordFade(void);
void UpdatePasswordFade(void);
void DrawPasswordFade(void);
//void SetPasswordFade(MODE modeNext);
void SetPasswordFade(PASSWORDFADE fade);
PASSWORDFADE GetPasswordFade(void);

#endif // !_FADE_H_
