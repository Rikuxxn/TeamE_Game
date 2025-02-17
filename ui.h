//=============================================================================
//
// UI処理 [ui.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _UI_H_//このマクロ定義がされていなかったら
#define _UI_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_UI (28)								// UIの最大数

// UIの種類
typedef enum
{
	UITYPE_GAME=0,
	UITYPE_INTERACT,
	UITYPE_INPUT,
	UITYPE_MAP,
	UITYPE_USE,
	UITYPE_DROP,

	UITYPE_MAX
}UITYPE;


// UI構造体
typedef struct
{
	D3DXVECTOR3 pos;							// 位置
	float fWidth;								// UIの幅
	float fHeight;								// UIの高さ
	int nType;									// UIの種類
	int nCounterUI;								// カウンター
	bool bUse;									// 使用しているかどうか
}UI;

static const char* UI_TEXTURE[UITYPE_MAX] =		// UIのテクスチャの設定
{
	"data/TEXTURE/UI3.png",						// ミニゲーム
	"data/TEXTURE/UI2.png",						// 拾う
	"data/TEXTURE/UI1.png",						// 入力する
	"data/TEXTURE/UI4.png",						// マップ
	"data/TEXTURE/UI5.png",						// 使う
	"data/TEXTURE/画像1.png",					// 何かが落ちてきた

};

//プロトタイプ宣言
void InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);
void SetUI(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);
UI* GetUI(void);


#endif