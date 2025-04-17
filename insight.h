//=============================================================================
//
// 視界エフェクト処理 [insight.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _INSIGHT_H_//このマクロ定義がされていなかったら
#define _INSIGHT_H_//2重インクルード防止のマクロ定義

#include "main.h"


// 構造体
typedef struct
{
	D3DXVECTOR3 pos;							// 位置
	D3DXCOLOR col;								// 色
	float fWidth;								// 幅
	float fHeight;								// 高さ
	int nCounter;								// カウンター
	bool bUse;									// 使用しているかどうか
}Insight;

//プロトタイプ宣言
void InitInsight(void);
void UninitInsight(void);
void UpdateInsight(void);
void DrawInsight(void);
void SetInsight(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);
Insight* GetInsight(void);

#endif