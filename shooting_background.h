//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#ifndef _SHOOTINGBACKGROUND_H_//このマクロ定義がされてなかったら
#define _SHOOTINGBACKGROUND_H_//２重インクルード防止のマクロ定義

#define BACKGROUND_WIDTH (200.0f)
#define BACKGROUND_HEIGHT (530.0f)

void InitBackGround(void);
void UninitBackGround(void);
void UpdateBackGround(void);
void DrawBackGround(void);

#endif