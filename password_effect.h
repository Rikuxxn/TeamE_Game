//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//�}�N��
#define MAX_EFFECT (1024)//�G�t�F�N�g�̍ő吔 

//�v���g
void InitPasswordEffect(void);
void UninitPasswordEffect(void);
void UpdatePasswordEffect(void);
void DrawPasswordEffect(void);

void SetPasswordEffect(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col ,float fRadius,int nLife,int nType);//���ˈʒu�ƈړ���
#endif