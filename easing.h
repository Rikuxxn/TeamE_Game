//=============================================================================
//
// イージング処理 [easing.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _EASING_H_//このマクロ定義がされていなかったら
#define _EASING_H_//2重インクルード防止のマクロ定義

#include "main.h"

// イージングの種類
typedef enum
{
	EASE_INEXPO = 0,
	EASE_OUTEXPO,
	EASE_INOUTEXPO,
	EASE_MAX
}EasingType;

float ease(float t, float start, float end, float duration, EasingType type);


#endif