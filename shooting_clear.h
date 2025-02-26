//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#ifndef _CLEAR_H_
#define _CLEAR_H_

#include "main.h"

// マクロ定義
#define CLEARPOSX (640.0f)
#define CLEARPOSY (200.0f)

//プロト
void InitClear(void);
void UninitClear(void);
void UpdateClear(void);
void DrawClear(void);

#endif