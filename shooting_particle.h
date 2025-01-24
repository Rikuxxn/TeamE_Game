#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//マクロ
#define MAX_PARTICLE (256)//saidaisuu

//構造体
typedef struct
{
	D3DXVECTOR3 pos;//iti
	D3DXVECTOR3 move;//idouryou6
	int nLife;//jumyo(hyoujijikan)
	bool bUse;//siyousiteiruka?
	int nType;//パーティクルの種類
}Particle;

//プロト
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
Particle* GetParticle(void);

void SetParticle(D3DXVECTOR3 pos,int nType);// , D3DXCOLOR col, float fRadius, int nLife);//発射位置と移動量必要に応じて
#endif