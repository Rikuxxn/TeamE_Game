//=======================================
//
//ブロック配置処理[block.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _BLOCK_H_//このマクロ定義がされていなかったら
#define _BLOCK_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_BLOCK (20)	// ブロックの使う数
//#define MAX_TEXTUREBLOCK (128)

// ブロックの種類
typedef enum
{
	BLOCKTYPE_NORMAL = 0,
	BLOCKTYPE_DOOR,
	BLOCKTYPE_MAX
}BLOCKTYPE;

//ブロックの情報
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[BLOCKTYPE_MAX];	//	テクスチャへのポインタ
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;				//	マテリアルへのポインタ
	DWORD dwNumMat;						//	マテリアル数
}Blockinfo;

// ブロック構造体
typedef struct
{
	D3DXVECTOR3 pos;					//	位置(オフセット)
	D3DXVECTOR3 move;					//移動量
	D3DXVECTOR3 rot;					//	向き
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 size;
	int nType;
	bool bUse;
	D3DXMATRIX mtxWorld;				//	ワールドマトリックス
	bool bScoreAdded;					// スコア加算済みかどうか
	bool bSoundPlayed;					// 音を再生済みかどうか
	Blockinfo blockinfo[BLOCKTYPE_MAX];
}Block;

static const char* BLOCK[BLOCKTYPE_MAX] =
{
	"data/MODEL/wall.x",				//	壁
	"data/MODEL/door.x",				//	ドア
};

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
void CollisionBlock(void);//当たり判定
Block* GetBlock(void);
bool GetExit(void);

#endif

