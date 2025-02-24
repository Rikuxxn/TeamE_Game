//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "password_background.h"

//マクロ
#define MAX_ITEM (12)										// アイテムの最大数
#define NUM_ITEM (12)										// 種類
#define ITEM_WIDTH (25.0f)									// 幅
#define ITEM_HEIGHT (25.0f)									// 高さ
#define ITEM_MIN_SCALE (1.0f)								// 拡大率
#define ITEM_POSX_LEFT (PASSWORDFIELD_LEFT + 38.0f)			// 左側120.0f
#define ITEM_POSX_CENTER (ITEM_POSX_LEFT + 60.0f)			// 中央
#define ITEM_POSX_RIGHT (ITEM_POSX_CENTER + 60.0f)			// 右側
#define ITEM_POSY_TOP (PASSWORDFIELD_UNDER - 230.0f)		// 上
#define ITEM_POSY_MIDDLE_UP (PASSWORDFIELD_UNDER - 170.0f)	// 真ん中より上
#define ITEM_POSY_MIDDLE_DOWN (PASSWORDFIELD_UNDER - 110.0f)// 真ん中より下
#define ITEM_POSY_UNDER (PASSWORDFIELD_UNDER - 50.0f)		// 下

typedef enum
{
	NUMTYPE_0 = 0,
	NUMTYPE_1,
	NUMTYPE_2,
	NUMTYPE_3,
	NUMTYPE_4,
	NUMTYPE_5,
	NUMTYPE_6,
	NUMTYPE_7,
	NUMTYPE_8,
	NUMTYPE_9,
	NUMTYPE_ENTER,
	NUMTYPE_DELETE,
	NUMTYPE_MAX
}NUMTYPE;

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 move;	// 移動量
	NUMTYPE type;		// キーの種類
	float fWidth;		// 幅
	float fHeight;		// 高さ
	int nType;			// テクスチャの種類
	bool bUse;			// 使用しているかどうか
	bool bGet;			// 取得したかどうか
	bool bcatch;		// キャッチしたか
}PASSWORDITEM;

//プロト
void InitPasswordItem(void);
void UninitPasswordItem(void);
void UpdatePasswordItem(void);
void DrawPasswordItem(void);
void SetPasswordItem(D3DXVECTOR3 pos,float fWidth,float fHeight,int nType, NUMTYPE type);//ブロックの設置
PASSWORDITEM* GetItem(void);
bool GetJudgment(void);
bool GetReset(void);

#endif