#ifndef _BALLGAME_H_
#define _BALLGAME_H_

#include "main.h"

// マクロ
#define BALLPOS (530.0f)// 幅820.0f

typedef enum
{
	BALLGAMESTATE_NONE = 0,	// 何もしていない状態
	BALLGAMESTATE_NORMAL,	// 通常状態（ゲーム進行中）
	BALLGAMESTATE_END,		// 終了状態（敵全滅、プレイヤー減、タイムオーバーなど）
	BALLGAMESTATE_MAX
}BALLGAMESTATE;

// マクロ
void InitBallGame(void);
void UninitBallGame(void);
void UpdateBallGame(void);
void DrawBallGame(void);
void SetBallGameState(BALLGAMESTATE state);
BALLGAMESTATE GetBallGameState(void);

#endif // !1