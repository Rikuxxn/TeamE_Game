//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

typedef enum
{
	PASSWORDGAMESTATE_NONE = 0,	//何もしていない状態
	PASSWORDGAMESTATE_NORMAL,	//通常状態（ゲーム進行中）
	PASSWORDGAMESTATE_END,		//終了状態（敵全滅、プレイヤー減、タイムオーバーなど）
	PASSWORDGAMESTATE_MAX
}PASSWORDGAMESTATE;

//マクロ
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