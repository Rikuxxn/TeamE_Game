//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "main.h"

#define PASSWORDFIELD_LEFT (540.0f)							//幅1280.0f
#define PASSWORDFIELD_RIGHT (PASSWORDFIELD_LEFT + 200.0f)	//高さ720.0f
#define PASSWORDFIELD_TOP (180.0f)
#define PASSWORDFIELD_UNDER (PASSWORDFIELD_TOP + 320.0f)

//プロト
void InitPasswordBackGround(void);
void UninitPasswordBackGround(void);
void UpdatePasswordBackGround(void);
void DrawPasswordBackGround(void);
#endif