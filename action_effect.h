#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//ƒvƒƒg
void InitActionEffect(void);
void UninitActionEffect(void);
void UpdateActionEffect(void);
void DrawActionEffect(void);

void SetActionEffect(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col ,float fRadius,int nLife,int nType);//D3DXVECTOR3 move//, D3DXVECTOR3 rot, float fLength);//”­ËˆÊ’u‚ÆˆÚ“®—Ê
#endif