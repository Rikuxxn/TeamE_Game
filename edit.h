//=======================================
//
// エディット処理[edit.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _EDIT_H_//このマクロ定義がされていなかったら
#define _EDIT_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define BLOCKPATH_1 ("data/block.txt")
#define WALLPATH_1 ("data/wall.txt")
#define MAX_EDITWORD (4096)

//テクスチャ構造体
typedef struct
{
    LPDIRECT3DTEXTURE9 apTexture[MAX_BLOCKTEXTURE]; //テクスチャへのポインタ
    LPD3DXMESH pMesh;
    LPD3DXBUFFER pBuffMat;				//	マテリアルへのポインタ
    DWORD dwNumMat;						//	マテリアル数
}BlockTex;

//構造体
typedef struct
{
    D3DXVECTOR3 pos;					// 位置(オフセット)
    D3DXVECTOR3 move;					// 移動量
    D3DXVECTOR3 rot;					// 向き
    //D3DXVECTOR3 size;
    int nType;
    bool bUse;
    D3DXMATRIX mtxWorld;				// ワールドマトリックス
    BlockTex blockTex[BLOCKTYPE_MAX];
}Editinfo;

//プロトタイプ宣言
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);
void SaveBlockData(void);
void SaveWallData(void);
void LoadBlockData(void);
void LoadWallData(void);

#endif
