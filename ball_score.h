//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _BALLSCORE_H_
#define _BALLSCORE_H_

#include "main.h"

//�}�N��
#define MAX_NUM_SCORE (4)
#define PASSPOSX (530.0f)
#define PASSPOSY (260.0f)

//�p�X���[�h�̍\����
typedef struct
{
	bool buse;
	int nCountBallPassCounter;
}BallPass;

//�v���g
void InitBallPass(void);				//�p�X���[�h�̏�����
void UninitBallPass(void);				//�I��
void UpdateBallPass(void);				//�X�V
void DrawBallPass(void);				//�`��
void SetBallPass(int nBallAPass);		//�ݒu
int BallPassCounter(int nBallPass);	//�J�E���^�[

#endif // !_SCORE_H_
