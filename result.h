//=============================================================================
//
// リザルト処理 [result.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _RESULT_H_//このマクロ定義がされていなかったら
#define _RESULT_H_//2重インクルード防止のマクロ定義

//マクロ定義
#define EIGHT (10000000)
#define SEVEN (1000000)
#define MAX_RESULTDIGIT (8)	//桁の最大数


//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif

