#ifndef _ITEM_H_
#define _ITEM_H_

#include "ball_game.h"

// マクロ
#define MAX_ITEM (16)							// アイテムの最大数
#define NUM_ITEM (4)							// アイテムの種類
#define ITEM_WIDTH (25.0f)						// アイテムの幅
#define ITEM_HEIGHT (25.0f)						// アイテムの高さ
#define ITEM_CLEARZONEX (75.0f)					// 片づけ先の範囲(X)
#define ITEM_CLEARZONEY (50.0f)					// 片づけ先の範囲(Y)
#define ITEM_CLEARPOSX (BALLPOS + 100.0f)		// アイテムの場所(X)
#define ITEM_CLEARPOSY (BALLFIELD_UNDER - 30.0f)// アイテムの場所(Y)
#define ITEM_MIN_SCALE (1.0f)					// アイテムの拡大率


// アイテム構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	float fWidth;			// 幅
	float fHeight;			// 高さ
	int nType;				// テクスチャの種類
	bool bUse;				// 使用しているかどうか
	bool bGet;				// 取得したかどうか
	bool bcatch;			// キャッチしたか
	D3DXVECTOR3 dragOffset;	// マウスを押した位置のオフセット
}BALLITEM;

//プロト
void InitBallItem(void);
void UninitBallItem(void);
void UpdateBallItem(void);
void DrawBallItem(void);
void SetBallItem(D3DXVECTOR3 pos,float fWidth,float fHeight,int type);// アイテムの設置
int GetNumBallItem(void);

#endif