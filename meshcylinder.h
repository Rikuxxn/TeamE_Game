//=======================================
//
//メッシュシリンダー処理[meshcylinder.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MESHCYLINDER_H_//このマクロ定義がされていなかったら
#define _MESHCYLINDER_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_CYLINDER (5)					// シリンダーの最大数

#define MESHCYLINDER_WIDTH (150.0f)			// 横幅
#define MESHCYLINDER_HEIGHT (120.0f)		// 縦幅

#define MESHCYLINDER_X (8)					// X方向のブロック数
#define MESHCYLINDER_Z (1)					// Z方向のブロック数

#define MESHCYLINDER_V (1)					// 垂直方向の分割数
#define MESHCYLINDER_H (8)					// 水平方向の分割数

#define MESHCYLINDER_PRIMITIVE (((MESHCYLINDER_X * MESHCYLINDER_Z) * 2)) + (4 * (MESHCYLINDER_Z - 1))//プリミティブ数
#define MESHCYLINDER_VERTEX ((MESHCYLINDER_X + 1) * (MESHCYLINDER_Z + 1))//頂点数
#define MESHCYLINDER_INDEX (MESHCYLINDER_PRIMITIVE + 2)//インデックス数

// メッシュシリンダー構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Cylinder;

//プロトタイプ宣言
void InitMeshcylinder(void);
void UninitMeshcylinder(void);
void UpdateMeshcylinder(void);
void DrawMeshcylinder(void);
void SetMeshcylinder(D3DXVECTOR3 pos);

#endif
