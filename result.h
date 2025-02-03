//=============================================================================
//
// リザルト処理 [result.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _RESULT_H_//このマクロ定義がされていなかったら
#define _RESULT_H_//2重インクルード防止のマクロ定義

//マクロ定義
#define MAX_RESULT_TIMEDIGIT (2)	//桁の最大数


//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

void InitResultTime(void);
void UninitResultTime(void);
void UpdateResultTime(void);
void DrawResultTime(void);
void SetResultTime(void);

#endif

