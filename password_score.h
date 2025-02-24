//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _PASSWORDSCORE_H_
#define _PASSWORDSCORE_H_

#include "main.h"

//�}�N��
#define MAX_NUM_SCORE (4)
#define PASSWORDPOS (500.0f)

//�p�X���[�h�̍\����
typedef struct
{
	bool buse;
	int nCountPasswordCounter;
}Password;

//�v���g
void InitPassword(void);		// �p�X���[�h�̏�����
void UninitPassword(void);		// �I��
void UpdatePassword(void);		// �X�V
void DrawPassword(void);		// �`��

void SetPassword(int nPass,int nA, bool bAnswer);	// �ݒu
void AddPassword(int nValue);	// �ǉ�

int PasswordCounter(int nPass);	// �J�E���^�[
int GetPassword(void);			// �擾
int GetPassword2(void);
int GetPassword3(void);
int GetPassword4(void);
bool GetPush1(void);
bool GetPush2(void);
bool GetPush3(void);
bool GetPush4(void);
int GetCntCounter(void);
bool GetJudge(void);			// ����

#endif // !_SCORE_H_
