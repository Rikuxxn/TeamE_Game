#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//弾の種類
typedef enum
{
	ITEMTYPE_PLAYER=0,//プレイヤーの弾
	ITEMTYPE_ENEMY,//敵の弾
	ITEMTYPE_MAX
}ACTIONITEMTYPE;

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	float fWidth;	//幅
	float fHeight;	//高さ
	int nType;		//テクスチャの種類
	bool bUse;		//使用しているかどうか
	bool bGet;		//取得したかどうか
	bool bDisp;		//表示するか
}ACTIONITEM;

//プロト
void InitActionItem(void);
void UninitActionItem(void);
void UpdateActionItem(void);
void DrawActionItem(void);
void SetActionItem(D3DXVECTOR3 pos,float fWidth,float fHeight,int type);//ブロックの設置
bool CollisionActionItem(D3DXVECTOR3 *pPos,D3DXVECTOR3 *pPosOld,D3DXVECTOR3 *pMove,float fWidth,float fHeight);;
bool GetActionItem(void);

#endif