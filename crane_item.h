#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//マクロ
#define MAX_ITEM (4)								//アイテムの最大数
#define NUM_ITEM (4)								//アイテムの種類
#define ITEM_WIDTH (20.0f)							//アイテムの幅
#define ITEM_HEIGHT (15.0f)							//アイテムの高さ
#define ITEM_CLEARZONE (50.0f)						//アイテムの範囲
#define ITEM_CLEARPOSX (CLANEFIELD_LEFT + 120.0f)	//アイテムの場所(X)
#define ITEM_CLEARPOSY (CLANEFIELD_UNDER - 40.0f)	//アイテムの場所(Y)

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	float fWidth;		//幅
	float fHeight;		//高さ
	int nType;			//テクスチャの種類
	bool bUse;			//使用しているかどうか
	bool bGet;			//取得したかどうか
	bool bcatch;		//キャッチしたか
	//bool bDisp;			//表示するか
}CRANEITEM;

//プロト
void InitCraneItem(void);
void UninitCraneItem(void);
void UpdateCraneItem(void);
void DrawCraneItem(void);
void SetCraneItem(D3DXVECTOR3 pos,float fWidth,float fHeight,int type);//ブロックの設置
int GetNumItem(void);
CRANEITEM GetItem(void);
bool CollisionCraneItem(D3DXVECTOR3 *pPos,D3DXVECTOR3 *pPosOld,D3DXVECTOR3 *pMove,float fWidth,float fHeight);;

#endif