//=======================================
//
//メッシュフィールド処理[meshfield.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MESHFIELD_H_//このマクロ定義がされていなかったら
#define _MESHFIELD_H_//2重インクルード防止のマクロ定義

#include "main.h"


#define MAX_WIDTH (2400)															// 横幅
#define MAX_HEIGHT (2000)															// 縦幅

#define MESHFIELD_X (20)															// X方向のブロック数
#define MESHFIELD_Z (20)															// Z方向のブロック数

#define MAX_PRIMITIVE (((MESHFIELD_X * MESHFIELD_Z) * 2)) + (4 * (MESHFIELD_Z - 1))	// プリミティブ数
#define MAX_VERTEX ((MESHFIELD_X + 1) * (MESHFIELD_Z + 1))							// 頂点数
#define MAX_INDEX (MAX_PRIMITIVE + 2)												// インデックス数

//プロトタイプ宣言
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

#endif
