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
#define CLANEITEM_POS (CLANEFIELD_UNDER / 2)

// プロトタイプ宣言
void InitCraneBackGround(void);
void UninitCraneBackGround(void);
void UpdateCraneBackGround(void);
void DrawCraneBackGround(void);

#endif