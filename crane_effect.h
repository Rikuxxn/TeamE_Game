#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//プロト
void InitCraneEffect(void);
void UninitCraneEffect(void);
void UpdateCraneEffect(void);
void DrawCraneEffect(void);

void SetCraneEffect(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col ,float fRadius,int nLife,int nType);//D3DXVECTOR3 move//, D3DXVECTOR3 rot, float fLength);//発射位置と移動量
#endif