//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _SHOOTINGSCORE_H_
#define _SHOOTINGSCORE_H_

#include "main.h"

// �}�N����`
#define MAX_NUM_SCORE (4)
#define PASSPOSX (550.0f)
#define PASSPOSY (230.0f)

// �p�X���[�h�̍\����
typedef struct
{
	bool buse;
	int nCountSTPassCounter;
}STPass;

// �v���g�^�C�v�錾
void InitSTPass(void);				// �p�X���[�h�̏�����
void UninitSTPass(void);			// �I��
void UpdateSTPass(void);			// �X�V
void DrawSTPass(void);				// �`��
void SetSTPass(int nSTAPass);		// �ݒu
int STPassCounter(int nSTPass);		// �J�E���^�[

#endif // !_SCORE_H_
