//=============================================================================
//
// ポーズ処理 [pause.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

#define MAX_PAUSE (4)

#define PAUSE_MIN_SCALE (1.0f)
#define PAUSE_MAX_SCALE (1.2f)
#define PAUSE_SCALE_SPEED (0.02f)
#define PAUSE_ALPHA_SPEED (0.05f)

typedef enum
{
	PAUSE_MENU_CONTINUE=0,						// ゲームに戻る
	PAUSE_MENU_RETRY,							// ゲームをやり直す
	PAUSE_MENU_TUTORIAL,						// 操作確認
	PAUSE_MENU_QUIT,							// タイトル画面に戻る
	PAUSE_MENU_MAX
}PAUSE_MENU;

static const char* PAUSE_TEXTURE[MAX_PAUSE] =
{
	"data\\TEXTURE\\continue.png",				// 続ける
	"data\\TEXTURE\\retry2.png",				// やり直す
	"data\\TEXTURE\\tuto.png",					// 操作確認
	"data\\TEXTURE\\quit.png",					// やめる
};

//プロトタイプ宣言
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SetDraw(bool bDraw);
bool GetTutoDraw(void);

#endif

