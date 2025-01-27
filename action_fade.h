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
}ACTIONFADE;

//ÉvÉçÉg
void InitActionFade(MODE modeNext);
void UninitActionFade(void);
void UpdateActionFade(void);
void DrawActionFade(void);
void SetActionFade(MODE modeNext);
void SetActionFade(ACTIONFADE fade);
ACTIONFADE GetActionFade(void);

#endif // !_FADE_H_
