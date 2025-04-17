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

#define MAX_EDITWORD (4096)
#define MAX_SPEED (6.0f)                               // エディター上のブロックの移動量

// ファイルパスの種類
typedef enum
{
    PATH_BLOCK=0,
    PATH_WALL,
    PATH_TITLE,
    PATH_TEST,

    PATH_MAX
}PathType;

//テクスチャ構造体
typedef struct
{
    LPDIRECT3DTEXTURE9 apTexture[MAX_BLOCKTEXTURE];     // テクスチャへのポインタ
    LPD3DXMESH pMesh;                                   // メッシュへのポインタ
    LPD3DXBUFFER pBuffMat;				                // マテリアルへのポインタ
    DWORD dwNumMat;						                // マテリアル数
}BlockTex;

//エディター構造体
typedef struct
{
    D3DXVECTOR3 pos;					                // 位置(オフセット)
    D3DXVECTOR3 move;					                // 移動量
    D3DXVECTOR3 rot;					                // 向き
    int nType;                                          // 種類
    int nPathType;                                          // ファイルパスの種類
    bool bUse;                                          // 使用されているかどうか
    D3DXMATRIX mtxWorld;				                // ワールドマトリックス
    BlockTex blockTex[BLOCKTYPE_MAX];
}Editinfo;

// ファイルパス
static const char* PATH[PATH_MAX] =
{
    "data/block.txt",				
    "data/wall.txt",
    "data/title.txt",
    "data/test.txt",
};

//プロトタイプ宣言
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);

void SaveBlockData(void);
void LoadBlockData(void);
void LoadParticular(int nPathType);
void SelectBlockByMouse(void);
void MoveEditBlock(void);
void TurnEditBlock(void);
void OperationEdit(void);
void NormalizeEditBlock(void);
const char* GetCurrentSaveFilePath(void);
const char* GetCurrentLoadFilePath(void);

#endif
