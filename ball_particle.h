#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//�}�N��
#define MAX_PARTICLE (256)//saidaisuu

//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//iti
	D3DXVECTOR3 move;	//idouryou6
	int nLife;			//jumyo(hyoujijikan)
	bool bUse;			//siyousiteiruka?
	int nType;			//�p�[�e�B�N���̎��
}BallParticle;

//�v���g
void InitBallParticle(void);
void UninitBallParticle(void);
void UpdateBallParticle(void);
void DrawBallParticle(void);
void SetBallParticle(D3DXVECTOR3 pos,int nType);// , D3DXCOLOR col, float fRadius, int nLife);//���ˈʒu�ƈړ��ʕK�v�ɉ�����
BallParticle* GetBallParticle(void);
#endif