#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//マクロ
#define MAX_PARTICLE (256)// 最大数

//構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 move;	// 移動量
	int nLife;			// 寿命(表示時間)
	bool bUse;			// 使われているか
	int nType;			// パーティクルの種類
}CraneParticle;

//プロト
void InitCraneParticle(void);
void UninitCraneParticle(void);
void UpdateCraneParticle(void);
void DrawCraneParticle(void);
void SetCraneParticle(D3DXVECTOR3 pos,int nType);//発射位置と移動量必要に応じて
CraneParticle* GetCraneParticle(void);
#endif