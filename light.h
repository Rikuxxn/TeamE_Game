//=======================================
//
// ライト処理[light.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _LIGHT_H_//このマクロ定義がされていなかったら
#define _LIGHT_H_//2重インクルード防止のマクロ定義

#include "main.h"

//プロトタイプ宣言
void InitLight(void);
int AddLight(D3DLIGHTTYPE type, D3DXCOLOR diffuse, D3DXVECTOR3 direction, D3DXVECTOR3 position);
void RemoveLight(int index);
void UninitLight(void);
void UpdateLight(int index, D3DXVECTOR3 newPosition, D3DXVECTOR3 newDirection);
void UpdateLightBlinking(float deltaTime);
void AddLightPlayer(D3DLIGHTTYPE type, D3DXCOLOR diffuse);
void AddPointlightToBlock(void);

#endif

