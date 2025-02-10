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
#define MAX_CLEAR (1)			// clear�I�����ڐ�
#define MAX_GAMEOVER (2)		// gameover�I�����ڐ�

#define CLEAR_MIN_SCALE (1.0f)
#define CLEAR_MAX_SCALE (1.2f)
#define CLEAR_SCALE_SPEED (0.02f)
#define CLEAR_ALPHA_SPEED (0.05f)

#define GAMEOVER_MIN_SCALE (1.0f)
#define GAMEOVER_MAX_SCALE (1.2f)
#define GAMEOVER_SCALE_SPEED (0.02f)
#define GAMEOVER_ALPHA_SPEED (0.05f)

// clear�̑I�����ڂ̎��
typedef enum
{
	CLEAR_MENU_TITLE = 0,        // �^�C�g���ɖ߂�
	CLEAR_MENU_MAX
}CLEAR_MENU;

// gameover�̑I�����ڂ̎��
typedef enum
{
	GAMEOVER_MENU_RETRY = 0,        //���g���C
	GAMEOVER_MENU_TITLE,			//�^�C�g���ɖ߂�
	GAMEOVER_MENU_MAX
}GAMEOVER_MENU;

static const char* CLEAR_TEXTURE[MAX_CLEAR] =
{
	"data\\TEXTURE\\titleback.png",
};

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

