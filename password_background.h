//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "main.h"

#define PASSWORDFIELD_LEFT (540.0f)							//��1280.0f
#define PASSWORDFIELD_RIGHT (PASSWORDFIELD_LEFT + 200.0f)	//����720.0f
#define PASSWORDFIELD_TOP (180.0f)
#define PASSWORDFIELD_UNDER (PASSWORDFIELD_TOP + 320.0f)

//�v���g
void InitPasswordBackGround(void);		// ������
void UninitPasswordBackGround(void);	// �I��
void UpdatePasswordBackGround(void);	// �X�V
void DrawPasswordBackGround(void);		// �`��
#endif