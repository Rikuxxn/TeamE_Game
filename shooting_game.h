#ifndef _SHHOTINGGAME_H_
#define _SHHOTINGGAME_H_

#include "main.h"

typedef enum
{
	STGSTATE_NONE = 0,//何もしていない状態
	STGSTATE_NORMAL,//通常状態（ゲーム進行中）
	STGSTATE_END,//終了状態（敵全滅、プレイヤー減、タイムオーバーなど）
	STGSTATE_MAX
}STGSTATE;

//マクロ
void InitShootingGame(void);
void UninitShootingGame(void);
void UpdateShootingGame(void);
void DrawShootingGame(void);
void SetShootingGameState(STGSTATE state);
STGSTATE GetShootingGameState(void);


#endif // !1