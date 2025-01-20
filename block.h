//=======================================
//
//ブロック配置処理[block.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _BLOCK_H_//このマクロ定義がされていなかったら
#define _BLOCK_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_BLOCK (100)	// ブロックの使う数
#define MAX_BLOCKTEXTURE (256)//ブロックの最大テクスチャ

// ブロックの種類
typedef enum
{
	BLOCKTYPE_WALL = 0,
	BLOCKTYPE_WALL_TATE,
	BLOCKTYPE_UFOCATCHER1,
	BLOCKTYPE_UFOCATCHER2,
	BLOCKTYPE_BALLPOOL,
	BLOCKTYPE_ARCADE1,
	BLOCKTYPE_ARCADE2,
	BLOCKTYPE_SWEETLAND,
	BLOCKTYPE_GASYAPON1,

	BLOCKTYPE_MAX
}BLOCKTYPE;

//ブロックの情報
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[MAX_BLOCKTEXTURE];	//	テクスチャへのポインタ
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;				//	マテリアルへのポインタ
	DWORD dwNumMat;						//	マテリアル数
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
}Blockinfo;

// ブロック構造体
typedef struct
{
	D3DXVECTOR3 pos;					//	位置(オフセット)
	D3DXVECTOR3 move;					//移動量
	D3DXVECTOR3 rot;					//	向き
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
	"data/MODEL/wall.x",				//	縦壁
	"data/MODEL/wall_tate.x",			//	横壁
	"data/MODEL/Crane_game000.x",		// クレーンゲーム1
	"data/MODEL/UFO.x",					// クレーンゲーム2
	"data/MODEL/Ball_pool.x",			// ボールプール
	"data/MODEL/arcade.x",				// アーケード1
	"data/MODEL/Fightng_game000.x",		// アーケード2
	"data/MODEL/SweetLand.x",			// スイートランド
	"data/MODEL/gasyapon00.x",			// ガシャポン

};

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
void CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3* pPosOld,D3DXVECTOR3* pMove, D3DXVECTOR3* pSize);//当たり判定
Block* GetBlock(void);
bool GetExit(void);

#endif

