//=============================================================================
//
// �^�C������ [time.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//�}�N����`
#define MAX_TIMEDIGIT (2)//���̍ő吔

//�^�C���\����
typedef struct
{
	bool bUse;
}Time;

//�v���g�^�C�v�錾
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);

int GetTimeMinutes(void);
int GetTimeSeconds(void);

#endif

