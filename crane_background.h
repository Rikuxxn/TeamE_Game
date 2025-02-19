//================================================
// 
// �N���[���Q�[���̔w�i���� [ crane_background.h ]
// Author:Atsushi Yoshida
// 
//================================================
#ifndef _CRANE_BACKGROUND_H_
#define _CRANE_BACKGROUND_H_

// �C���N���[�h�t�@�C��
#include "main.h"

// �}�N����`
#define CLANEFIELD_LEFT (280.0f)//��720.0f
#define CLANEFIELD_RIGHT (1000.0f)
#define CLANEFIELD_TOP (50.0f)//����400.0f
#define CLANEFIELD_UNDER (450.0f)
#define CLANEITEM_POS (CLANEFIELD_UNDER / 2)

// �v���g�^�C�v�錾
void InitCraneBackGround(void);
void UninitCraneBackGround(void);
void UpdateCraneBackGround(void);
void DrawCraneBackGround(void);

#endif