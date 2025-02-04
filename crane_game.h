#ifndef _CRANE_GAME_H_
#define _CRANE_GAME_H_

#include "main.h"

typedef enum
{
	CRANEGAMESTATE_NONE = 0,//�������Ă��Ȃ����
	CRANEGAMESTATE_NORMAL,	//�ʏ��ԁi�Q�[���i�s���j
	CRANEGAMESTATE_END,		//�I����ԁi�G�S�ŁA�v���C���[���A�^�C���I�[�o�[�Ȃǁj
	CRANEGAMESTATE_MAX
}CRANEGAMESTATE;

//�}�N��
void InitCraneGame(void);
void UninitCraneGame(void);
void UpdateCraneGame(void);
void DrawCraneGame(void);
void SetCraneGameState(CRANEGAMESTATE state);
CRANEGAMESTATE GetCraneGameState(void);

#endif // !1