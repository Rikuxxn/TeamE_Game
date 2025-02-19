//=======================================
//
// 影の処理 [shadow.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _SHADOW_H_//このマクロ定義がされていなかったら
#define _SHADOW_H_//2重インクルード防止のマクロ定義

#include "main.h"

//影の構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Shadow;

//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void ShadowFalse(int nIdxShadow);

Shadow* GetShadow(void);

#endif
