//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _CRANESCORE_H_
#define _CRANESCORE_H_

#include "main.h"

//�}�N��
#define MAX_NUM_SCORE (4)
#define PASSPOSX (560.0f)
#define PASSPOSY (260.0f)

//�p�X���[�h�̍\����
typedef struct
{
	bool buse;
	int nCountCranePassCounter;
}CranePass;

//�v���g
void InitCranePass(void);				//�@�p�X���[�h�̏�����
void UninitCranePass(void);				//�@�I��
void UpdateCranePass(void);				//�@�X�V
void DrawCranePass(void);				//�@�`��
void SetCranePass(int nCraneAPass);		//�@�ݒu
int CranePassCounter(int nCranePass);	//�@�J�E���^�[

#endif // !_SCORE_H_
