//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#ifndef _BALL_TUTORIAL_H_
#define _BALL_TUTORIAL_H_

#include "main.h"

#define TUTORIAL_WIDTH (400.0f)
#define TUTORIAL_HEIGHT (150.0f)

// ÉvÉçÉg
void InitBallTutorial(void);
void UninitBallTutorial(void);
void UpdateBallTutorial(void);
void DrawBallTutorial(void);
bool GetStart(void);

#endif