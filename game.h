//=============================================================================
//
// ゲーム処理 [game.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _GAME_H_//このマクロ定義がされていなかったら
#define _GAME_H_//2重インクルード防止のマクロ定義

#include "main.h"

//ゲームの状態
typedef enum
{

	GAMESTATE_NONE = 0,		//何もしていない状態
	GAMESTATE_NORMAL,		//通常状態
	GAMESTATE_END,			//終了状態
	GAMESTATE_MAX

}GAMESTATE;

//ゲーム構造体
typedef struct
{
	bool bDraw;				//　シューティングミニゲームの描画用
	bool bDraw2;			//　クレーン
	bool bDraw3;			//　ボールプール
	bool bDraw4;			//　パスワード
	bool bSTClear;			//　シューティング
	bool bACClear;			//　クレーン
	bool bBallClear;		//　ボールプール
	bool bPassClear;		//　パスワード
	bool bMap;				//　マップ
	bool bMini;				//　ミニゲーム全体
	int nCounter;			//　カウンター
	int nStgCnt;			//　シューティングカウンター
	int nCraneCnt;			//　クレーンカウンター
	int nBallCnt;			//　ボールプールカウンター
	int nPassCnt;			//　パスワードカウンター

}GAME;

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void SetGameState(GAMESTATE state);
void SetEnablePause(bool bPause);
GAMESTATE GetGameState(void);
GAME* GetGame(void);

bool GetSTClear(void);
bool GetACClear(void);
bool GetBallClear(void);
bool GetPassClear(void);


#endif
