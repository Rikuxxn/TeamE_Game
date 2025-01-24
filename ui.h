//=============================================================================
//
// UI処理 [ui.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _UI_H_//このマクロ定義がされていなかったら
#define _UI_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_UI (28)      // UIの最大数

// UIの種類
typedef enum
{
	UITYPE_GAME=0,
	UITYPE_INTERACT,
	UITYPE_INPUT,
	UITYPE_MAX
}UITYPE;


// UI構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	float fWidth;			// UIの幅
	float fHeight;			// UIの高さ
	int nType;				// UIの種類
	bool bUse;				// 使用しているかどうか
}UI;

static const char* UI_TEXTURE[UITYPE_MAX] =	// UIのテクスチャの設定
{
	"data/TEXTURE/.x",// ミニゲーム
	"data/TEXTURE/.x",// 拾う
	"data/TEXTURE/.x",// 入力する

};

//プロトタイプ宣言
void InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);
void SetUI(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);


#endif