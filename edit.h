//=======================================
//
// エディット処理[edit.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _EDIT_H_//このマクロ定義がされていなかったら
#define _EDIT_H_//2重インクルード防止のマクロ定義

#include "main.h"
#include "block.h"

#define BLOCKPATH_1 ("data/block.txt")
#define WALLPATH_1 ("data/wall.txt")
#define TITLEPATH_1 ("data/title.txt")

#define MAX_EDITWORD (4096)
#define MAX_SPEED (10.0f)                               // エディター上のブロックの移動量

//テクスチャ構造体
typedef struct
{
    LPDIRECT3DTEXTURE9 apTexture[MAX_BLOCKTEXTURE];     // テクスチャへのポインタ
    LPD3DXMESH pMesh;                                   // メッシュへのポインタ
    LPD3DXBUFFER pBuffMat;				                // マテリアルへのポインタ
    DWORD dwNumMat;						                // マテリアル数
}BlockTex;

//構造体
typedef struct
{
    D3DXVECTOR3 pos;					                // 位置(オフセット)
    D3DXVECTOR3 move;					                // 移動量
    D3DXVECTOR3 rot;					                // 向き
    int nType;                                          // 種類
    bool bUse;                                          // 使用されているかどうか
    D3DXMATRIX mtxWorld;				                // ワールドマトリックス
    BlockTex blockTex[BLOCKTYPE_MAX];
}Editinfo;

//プロトタイプ宣言
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);

void SaveBlockData(void);
void SaveWallData(void);
void SaveTitleData(void);

void LoadBlockData(void);
void LoadWallData(void);
void LoadTitleData(void);

#endif
