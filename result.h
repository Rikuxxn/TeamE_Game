//=============================================================================
//
// ���U���g���� [result.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _RESULT_H_//���̃}�N����`������Ă��Ȃ�������
#define _RESULT_H_//2�d�C���N���[�h�h�~�̃}�N����`

//�}�N����`
#define MAX_RESULT_TIMEDIGIT (2)	//���̍ő吔

//�}�N����`
#define MAX_GAMEOVER (2)//�I�����ڐ�

#define GAMEOVER_MIN_SCALE (1.0f)
#define GAMEOVER_MAX_SCALE (1.2f)
#define GAMEOVER_SCALE_SPEED (0.02f)
#define GAMEOVER_ALPHA_SPEED (0.05f)

// gameover�̑I�����ڂ̎��
typedef enum
{
	GAMEOVER_MENU_RETRY = 0,        //���g���C
	GAMEOVER_MENU_TITLE,			//�^�C�g���ɖ߂�
	GAMEOVER_MENU_MAX
}GAMEOVER_MENU;

static const char* GAMEOVER_TEXTURE[MAX_GAMEOVER] =
{
	"data\\TEXTURE\\retry1.png",
	"data\\TEXTURE\\titleback.png",
};

//�v���g�^�C�v�錾
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

void InitResultTime(void);
void UninitResultTime(void);
void UpdateResultTime(void);
void DrawResultTime(void);

#endif

