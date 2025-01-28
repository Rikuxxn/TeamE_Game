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
}CRANEFADE;

//ÉvÉçÉg
void InitCraneFade(MODE modeNext);
void UninitCraneFade(void);
void UpdateCraneFade(void);
void DrawCraneFade(void);
void SetCraneFade(MODE modeNext);
void SetCraneFade(CRANEFADE fade);
CRANEFADE GetCraneFade(void);

#endif // !_FADE_H_
