#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

typedef enum
{
	GAMESTATE_NONE = 0,//何もしていない状態
	GAMESTATE_NORMAL,//通常状態（ゲーム進行中）
	GAMESTATE_END,//終了状態（敵全滅、プレイヤー減、タイムオーバーなど）
	GAMESTATE_MAX
}SHOOTINGGAMESTATE;

//マクロ
void InitShootingGame(void);
void UninitShootingGame(void);
void UpdateShootingGame(void);
void DrawShootingGame(void);
void SetShootingGameState(SHOOTINGGAMESTATE state);
SHOOTINGGAMESTATE GetGameState(void);


#endif // !1