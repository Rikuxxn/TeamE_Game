#ifndef _CRANE_GAME_H_
#define _CRANE_GAME_H_

#include "main.h"

typedef enum
{
	CRANEGAMESTATE_NONE = 0,//何もしていない状態
	CRANEGAMESTATE_NORMAL,	//通常状態（ゲーム進行中）
	CRANEGAMESTATE_END,		//終了状態（敵全滅、プレイヤー減、タイムオーバーなど）
	CRANEGAMESTATE_MAX
}CRANEGAMESTATE;

//マクロ
void InitCraneGame(void);
void UninitCraneGame(void);
void UpdateCraneGame(void);
void DrawCraneGame(void);
void SetCraneGameState(CRANEGAMESTATE state);
CRANEGAMESTATE GetCraneGameState(void);

#endif // !1