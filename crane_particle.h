#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//�}�N��
#define MAX_PARTICLE (256)// �ő吔

//�\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	int nLife;			// ����(�\������)
	bool bUse;			// �g���Ă��邩
	int nType;			// �p�[�e�B�N���̎��
}CraneParticle;

//�v���g
void InitCraneParticle(void);
void UninitCraneParticle(void);
void UpdateCraneParticle(void);
void DrawCraneParticle(void);
void SetCraneParticle(D3DXVECTOR3 pos,int nType);//���ˈʒu�ƈړ��ʕK�v�ɉ�����
CraneParticle* GetCraneParticle(void);
#endif