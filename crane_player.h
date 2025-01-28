//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#ifndef _PLAYER_H_//このマクロ定義がされてなかったら
#define _PLAYER_H_//２重インクルード防止のマクロ定義

#define HABA (25.0f)		//プレイヤー幅
#define TAKASA (60.0f)		//プレイヤー高さ
#define DOWN (3.0f)			//降りる速さ
#define UP (-3.0f)			//上る速さ
#define MAX_SPEED_L (-3.0f)	//最速左
#define MAX_SPEED_R (3.0f)	//最速右

#include "crane_block.h"

//プレイヤーの状態2024/08/26
typedef enum
{
	PLAYERSTATE_APPEAR = 0, //出現状態（点滅）
	PLAYERSTATE_NORMAL,		//通常
	PLAYERSTATE_DAMAGE,		//ダメージ
	PLAYERSTATE_DEATH,		//脂肪
	PLAYERSTATE_MUTEKI,		//無敵状態
	PLAYERSTATE_MAX
}CRANEPLAYERSTATE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;        //現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 move;		//移動量
	CRANEBLOCK* pBlock;	//ブロックへのポインタ
	CRANEPLAYERSTATE state;//プレイヤーの状態
	int nCounterState;		//状態管理カウンター
	int nCntAnimState;		//状態をカウント
	int nLife;				//命
	float Length;			//対角線の長さ
	float Angle;			//対角線の角度
	bool bUse;				//使われているか
	bool bMove;				//動けるか
	bool bLeft;				//左に進むか
	bool bLanding;			//着地しているか
	bool bGetItem;			//アイテム取得用のフラグ
}CranePlayer;

//プロト
void InitCranePlayer(void);
void UninitCranePlayer(void);
void UpdateCranePlayer(void);
void DrawCranePlayer(void);
CranePlayer* GetCranePlayer(void);
D3DXVECTOR3 GetCranePos(void);
#endif