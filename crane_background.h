//================================================
// 
// クレーンゲームの背景処理 [ crane_background.h ]
// Author:Atsushi Yoshida
// 
//================================================
#ifndef _CRANE_BACKGROUND_H_
#define _CRANE_BACKGROUND_H_

// インクルードファイル
#include "main.h"

// マクロ定義
#define CLANEFIELD_LEFT (280.0f)//幅720.0f
#define CLANEFIELD_RIGHT (1000.0f)
#define CLANEFIELD_TOP (50.0f)//高さ400.0f
#define CLANEFIELD_UNDER (450.0f)
#define CLANEITEM_POS (CLANEFIELD_UNDER / 2)

// プロトタイプ宣言
void InitCraneBackGround(void);
void UninitCraneBackGround(void);
void UpdateCraneBackGround(void);
void DrawCraneBackGround(void);

#endif