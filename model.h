//=======================================
//
// モデル処理[model.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MODEL_H_//このマクロ定義がされていなかったら
#define _MODEL_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_MODEL (1)									//	モデルの使う数
#define MAX_TEXTUREMODEL (128)

//壁の種類
typedef enum
{
	WALLTYPE_NORMAL=0,
	WALLTYPE_MAX
}WALLTYPE;

//モデル構造体
typedef struct
{
	D3DXVECTOR3 pos;									// 位置(オフセット)
	LPDIRECT3DTEXTURE9 apTexture[MAX_TEXTUREMODEL];		// テクスチャへのポインタ
	D3DXVECTOR3 move;									// 移動量
	D3DXVECTOR3 rot;									// 向き
	D3DXVECTOR3 vtxMin;									// 最大値
	D3DXVECTOR3 vtxMax;									// 最小値
	D3DXVECTOR3 size;									// サイズ
	int nType;											// 種類
	int Index;											// インデックス番号
	bool bUse;											// 使用されているかどうか
	LPD3DXMESH pMesh;									// メッシュへのポインタ
	LPD3DXBUFFER pBuffMat;								// マテリアルへのポインタ
	DWORD dwNumMat;										// マテリアル数
	int nIdxModelParent;								// 親モデルのインデックス
	D3DXMATRIX mtxWorld;								// ワールドマトリックス
	D3DXVECTOR3 Offpos;									// オフセット(pos)
	D3DXVECTOR3 Offrot;									// オフセット(rot)
	bool bScoreAdded;									// スコア加算済みかどうか
	bool bSoundPlayed;									// 音を再生済みかどうか
}Model;

static const char* MODEL[MAX_MODEL] =
{

	"data/MODEL/wall.x",								//	壁

};

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void SetModel(D3DXVECTOR3 pos, int nType);
void CollisionModel(void);//当たり判定

#endif

