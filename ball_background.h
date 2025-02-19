#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_


#include "main.h"

//マクロ定義
#define BALLFIELD_LEFT (230.0f)//幅820.0f
#define BALLFIELD_RIGHT (1050.0f)
#define BALLFIELD_TOP (50.0f)//高さ400.0f
#define BALLFIELD_UNDER (650.0f)

// プロト
void InitBallBackGround(void);
void UninitBallBackGround(void);
void UpdateBallBackGround(void);
void DrawBallBackGround(void);
#endif