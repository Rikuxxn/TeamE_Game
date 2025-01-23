//=============================================================================
//
// �^�C�g������ [title.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _TITLE_H_//���̃}�N����`������Ă��Ȃ�������
#define _TITLE_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�}�N����`
#define MAX_TITLE (2)//�I�����ڐ�

#define TITLE_MIN_SCALE (1.0f)
#define TITLE_MAX_SCALE (1.2f)
#define TITLE_SCALE_SPEED (0.02f)
#define TITLE_ALPHA_SPEED (0.05f)

typedef enum
{
	TITLE_MENU_START = 0,           //�Q�[���X�^�[�g
	TITLE_MENU_QUIT,				//�E�B���h�E�����
	TITLE_MENU_MAX
}TITLE_MENU;


static const char* TITLE_TEXTURE[MAX_TITLE] =
{
	"data\\TEXTURE\\start.png",
	"data\\TEXTURE\\end.png",
};

//�v���g�^�C�v�錾
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif

