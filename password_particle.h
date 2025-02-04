//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//マクロ
#define MAX_PARTICLE (256)//saidaisuu

//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//iti
	D3DXVECTOR3 move;	//idouryou6
	int nLife;			//jumyo(hyoujijikan)
	bool bUse;			//siyousiteiruka?
	int nType;			//パーティクルの種類
}PasswordParticle;

//プロト
void InitPasswordParticle(void);
void UninitPasswordParticle(void);
void UpdatePasswordParticle(void);
void DrawPasswordParticle(void);
void SetPasswordParticle(D3DXVECTOR3 pos,int nType);//発射位置と移動量必要に応じて
PasswordParticle* GetPasswordParticle(void);
#endif