#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//�}�N��
#define MAX_PARTICLE (256)//saidaisuu

//�\����
typedef struct
{
	D3DXVECTOR3 pos;//iti
	D3DXVECTOR3 move;//idouryou6
	int nLife;//jumyo(hyoujijikan)
	bool bUse;//siyousiteiruka?
	int nType;//�p�[�e�B�N���̎��
}CraneParticle;

//�v���g
void InitCraneParticle(void);
void UninitCraneParticle(void);
void UpdateCraneParticle(void);
void DrawCraneParticle(void);
void SetCraneParticle(D3DXVECTOR3 pos,int nType);// , D3DXCOLOR col, float fRadius, int nLife);//���ˈʒu�ƈړ��ʕK�v�ɉ�����
CraneParticle* GetCraneParticle(void);
#endif