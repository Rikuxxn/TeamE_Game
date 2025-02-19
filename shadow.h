//=======================================
//
// �e�̏��� [shadow.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _SHADOW_H_//���̃}�N����`������Ă��Ȃ�������
#define _SHADOW_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Shadow;

//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void ShadowFalse(int nIdxShadow);

Shadow* GetShadow(void);

#endif
