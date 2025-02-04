#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//弾の種類
typedef enum
{
	BLOCKTYPE_PLAYER=0,	//プレイヤーの弾
	BLOCKTYPE_ENEMY,	//敵の弾
	BLOCKTYPE_MAX
}BALLBLOCKTYPE;

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//動き
	float fWidth;		//幅
	float fHeight;		//高さ
	int nType;			//テクスチャの種類
	bool bUse;			//使用しているかどうか
	int nMoveCnt;		//動きカウンター
}BALLBLOCK;

//プロト
void InitBallBlock(void);
void UninitBallBlock(void);
void UpdateBallBlock(void);
void DrawBallBlock(void);
void SetBallBlock(D3DXVECTOR3 pos,D3DXVECTOR3 move,float fWidth,float fHeight,int type);//ブロックの設置
BALLBLOCK* GetBlock(void);

#endif