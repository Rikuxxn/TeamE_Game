#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

typedef enum
{
	FADE_NONE=0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
}SHOOTINGFADE;

//ÉvÉçÉg
void InitShootingFade(MODE modeNext);
void UninitShootingFade(void);
void UpdateShootingFade(void);
void DrawShootingFade(void);

void SetShootingFade(MODE modeNext);
SHOOTINGFADE GetShootingFade(void);

#endif // !_FADE_H_
