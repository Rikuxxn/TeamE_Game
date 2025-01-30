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
}BALLFADE;

//ÉvÉçÉg
void InitBallFade(MODE modeNext);
void UninitBallFade(void);
void UpdateBallFade(void);
void DrawBallFade(void);
void SetBallFade(MODE modeNext);
void SetBallFade(BALLFADE fade);
BALLFADE GetBallFade(void);

#endif // !_FADE_H_
