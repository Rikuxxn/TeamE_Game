//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
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
}PasswordParticle;

//�v���g
void InitPasswordParticle(void);
void UninitPasswordParticle(void);
void UpdatePasswordParticle(void);
void DrawPasswordParticle(void);
void SetPasswordParticle(D3DXVECTOR3 pos,int nType);//���ˈʒu�ƈړ��ʕK�v�ɉ�����
PasswordParticle* GetPasswordParticle(void);
#endif