//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "main.h"

#define PASSWORDFIELD_LEFT (500.0f)		//��200.0f
#define PASSWORDFIELD_RIGHT (700.0f)	//����320.0f
#define PASSWORDFIELD_TOP (180.0f)
#define PASSWORDFIELD_UNDER (500.0f)

//�v���g
void InitPasswordBackGround(void);
void UninitPasswordBackGround(void);
void UpdatePasswordBackGround(void);
void DrawPasswordBackGround(void);
#endif