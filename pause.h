//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

#define MAX_PAUSE (3)

#define PAUSE_MIN_SCALE (1.0f)
#define PAUSE_MAX_SCALE (1.2f)
#define PAUSE_SCALE_SPEED (0.02f)
#define PAUSE_ALPHA_SPEED (0.05f)

typedef enum
{
	PAUSE_MENU_CONTINUE=0,						// �Q�[���ɖ߂�
	PAUSE_MENU_RETRY,							// �Q�[������蒼��
	PAUSE_MENU_QUIT,							// �^�C�g����ʂɖ߂�
	PAUSE_MENU_MAX
}PAUSE_MENU;

static const char* PAUSE_TEXTURE[MAX_PAUSE] =
{
	"data\\TEXTURE\\continue.png",				// ������
	"data\\TEXTURE\\retry2.png",					// ��蒼��
	"data\\TEXTURE\\quit.png",					// ��߂�
};

//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#endif

