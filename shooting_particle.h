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
}Particle;

//�v���g
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
Particle* GetParticle(void);

void SetParticle(D3DXVECTOR3 pos,int nType);// , D3DXCOLOR col, float fRadius, int nLife);//���ˈʒu�ƈړ��ʕK�v�ɉ�����
#endif