#ifndef _ACTIONGAME_H_
#define _ACTIONGAME_H_

#include "main.h"

typedef enum
{
	ACTSTATE_NONE = 0,	//何もしていない状態
	ACTSTATE_NORMAL,		//通常状態
	ACTSTATE_END,		//終了状態
	ACTSTATE_MAX
}ACTSTATE;

//マクロ
void InitActionGame(void);
void UninitActionGame(void);
void UpdateActionGame(void);
void DrawActionGame(void);
void SetActionGameState(ACTSTATE state);
ACTSTATE GetActionGameState(void);

#endif // !1