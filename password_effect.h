//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//マクロ
#define MAX_EFFECT (1024)//エフェクトの最大数 

//プロト
void InitPasswordEffect(void);
void UninitPasswordEffect(void);
void UpdatePasswordEffect(void);
void DrawPasswordEffect(void);

void SetPasswordEffect(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col ,float fRadius,int nLife,int nType);//発射位置と移動量
#endif