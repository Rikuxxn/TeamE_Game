//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _PASSWORDSCORE_H_
#define _PASSWORDSCORE_H_

#include "main.h"

//�}�N��
#define MAX_NUM_SCORE (4)
#define PASSWORDPOS (459.0f)

//�p�X���[�h�̍\����
typedef struct
{
	bool buse;
	int nCountPasswordCounter;
}Password;

//�v���g
void InitPassword(void);
void UninitPassword(void);
void UpdatePassword(void);
void DrawPassword(void);

void SetPassword(int nPass);
void AddPassword(int nValue);

int PasswordCounter(int nPass);
int GetPassword(void);
int GetPassword2(void);
int GetPassword3(void);
int GetPassword4(void);
int GetCntCounter(void);
bool GetJudge(void);

#endif // !_SCORE_H_
