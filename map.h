//=========================================================
// 
// ミニマップ表示処理 [map.h]
// Author : TANEKAWA RIKU
// 
//=========================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

// マクロ定義
#define MINIMAP_LEFT (300.0f)
#define MINIMAP_RIGHT (940.0f)
#define MINIMAP_TOP (100.0f)
#define MINIMAP_UNDER (450.0f)

// アイコン構造体
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 rot;			// 向き
	float fWidth;				// 幅
	float fHeight;				// 高さ
}Icon;

// ミニマップ構造体
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	float fWidth;				// 幅
	float fHeight;				// 高さ
}Map;

// プロトタイプ宣言
void InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);
#endif