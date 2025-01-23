//=============================================================================
//
// タイトル処理 [title.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _TITLE_H_//このマクロ定義がされていなかったら
#define _TITLE_H_//2重インクルード防止のマクロ定義

#include "main.h"

//マクロ定義
#define MAX_TITLE (2)//選択項目数

#define TITLE_MIN_SCALE (1.0f)
#define TITLE_MAX_SCALE (1.2f)
#define TITLE_SCALE_SPEED (0.02f)
#define TITLE_ALPHA_SPEED (0.05f)

typedef enum
{
	TITLE_MENU_START = 0,           //ゲームスタート
	TITLE_MENU_QUIT,				//ウィンドウを閉じる
	TITLE_MENU_MAX
}TITLE_MENU;


static const char* TITLE_TEXTURE[MAX_TITLE] =
{
	"data\\TEXTURE\\start.png",
	"data\\TEXTURE\\end.png",
};

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif

