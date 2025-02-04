//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

typedef enum
{
	PASSWORDGAMESTATE_NONE = 0,	//�������Ă��Ȃ����
	PASSWORDGAMESTATE_NORMAL,	//�ʏ��ԁi�Q�[���i�s���j
	PASSWORDGAMESTATE_END,		//�I����ԁi�G�S�ŁA�v���C���[���A�^�C���I�[�o�[�Ȃǁj
	PASSWORDGAMESTATE_MAX
}PASSWORDGAMESTATE;

//�}�N��
void InitPasswordGame(void);
void UninitPasswordGame(void);
void UpdatePasswordGame(void);
void DrawPasswordGame(void);
void SetPasswordGameState(PASSWORDGAMESTATE state);
PASSWORDGAMESTATE GetPasswordGameState(void);

int GetAnum(void);
int GetAnum2(void);
int GetAnum3(void);
int GetAnum4(void);
#endif