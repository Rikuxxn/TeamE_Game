//=======================================
//
// メッシュシーリング処理[meshceiling.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MESHCEILING_H_//このマクロ定義がされていなかったら
#define _MESHCEILING_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_WIDTH_CEILING (2400.0f)																	// 横幅
#define MAX_HEIGHT_CEILING (2000.0f)																// 縦幅

#define MESHCEILING_X (20)																			// X方向のブロック数
#define MESHCEILING_Z (20)																			// Z方向のブロック数

#define MAX_PRIMITIVE_CEILING (((MESHCEILING_X * MESHCEILING_Z) * 2)) + (4 * (MESHCEILING_Z - 1))	// プリミティブ数
#define MAX_VERTEX_CEILING ((MESHCEILING_X + 1) * (MESHCEILING_Z + 1))								// 頂点数
#define MAX_INDEX_CEILING (MAX_PRIMITIVE_CEILING + 2)												// インデックス数

//プロトタイプ宣言
void InitMeshCeiling(void);
void UninitMeshCeiling(void);
void UpdateMeshCeiling(void);
void DrawMeshCeiling(void);

#endif
