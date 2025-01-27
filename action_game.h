#ifndef _ACTIONGAME_H_
#define _ACTIONGAME_H_

#include "main.h"

typedef enum
{
	ACTSTATE_NONE = 0,	//�������Ă��Ȃ����
	ACTSTATE_NORMAL,		//�ʏ���
	ACTSTATE_END,		//�I�����
	ACTSTATE_MAX
}ACTSTATE;

//�}�N��
void InitActionGame(void);
void UninitActionGame(void);
void UpdateActionGame(void);
void DrawActionGame(void);
void SetActionGameState(ACTSTATE state);
ACTSTATE GetActionGameState(void);

#endif // !1