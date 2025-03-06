//================================================
// 
// クレーンゲームの背景処理 [ crane_background2.h ]
// Author:Atsushi Yoshida
// 
//================================================
#ifndef _CRANE_BACKGROUND2_H_
#define _CRANE_BACKGROUND2_H_

// インクルードファイル
#include "main.h"

// マクロ定義
#define CLANEFIELD_LEFT (280.0f)//幅720.0f
#define CLANEFIELD_RIGHT (1000.0f)

// プロトタイプ宣言
void InitCraneBackGround2(void);
void UninitCraneBackGround2(void);
void UpdateCraneBackGround2(void);
void DrawCraneBackGround2(void);

#endif