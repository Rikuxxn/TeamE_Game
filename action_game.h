#ifndef _ACTIONGAME_H_
#define _ACTIONGAME_H_

#include "main.h"

typedef enum
{
	ACTSTATE_NONE = 0,	//âΩÇ‡ÇµÇƒÇ¢Ç»Ç¢èÛë‘
	ACTSTATE_NORMAL,		//í èÌèÛë‘
	ACTSTATE_END,		//èIóπèÛë‘
	ACTSTATE_MAX
}ACTSTATE;

//É}ÉNÉç
void InitActionGame(void);
void UninitActionGame(void);
void UpdateActionGame(void);
void DrawActionGame(void);
void SetActionGameState(ACTSTATE state);
ACTSTATE GetActionGameState(void);

#endif // !1