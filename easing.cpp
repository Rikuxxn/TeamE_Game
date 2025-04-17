//=============================================================================
//
// イージング処理 [easing.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "easing.h"

//============================
// イージング関数
//============================
float ease(float t, float start, float end, float duration, EasingType type)
{
    float c = end - start;  // 変化量
    if (t < 0)
    {
        t = 0;
    }
    if (t > duration)
    {
        t = duration;
    }

    switch (type)
    {
    case EASE_INEXPO:

        return (t == 0) ? start : c * powf(2, 10 * (t / duration - 1)) + start;

    case EASE_OUTEXPO:

        return (t == duration) ? end : c * (-powf(2, -10 * t / duration) + 1) + start;

    case EASE_INOUTEXPO:

        if (t == 0)
        {
            return start;
        }
        if (t == duration)
        {
            return end;
        }

        t /= duration / 2;

        if (t < 1)
        {
            return c / 2 * powf(2, 10 * (t - 1)) + start;
        }

        return c / 2 * (-powf(2, -10 * --t) + 2) + start;

    default:
        return start;
    }
}