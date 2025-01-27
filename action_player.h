//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#ifndef _PLAYER_H_//このマクロ定義がされてなかったら
#define _PLAYER_H_//２重インクルード防止のマクロ定義

#define HABA (25.0f)//プレイヤー幅
#define TAKASA (60.0f)//プレイヤー高さ
#define F_JAMP1ST (-19.0f)//ジャンプ1
#define F_JAMP2ND (-10.0f)//ジャンプ2
#define MAX_SPEED_L (-7.0f)//最速左
#define MAX_SPEED_R (7.0f)//最速右

#include "action_block.h"

//プレイヤーの状態2024/08/26
typedef enum
{
	PLAYERSTATE_APPEAR = 0, //出現状態（点滅）
	PLAYERSTATE_NORMAL,		//通常
	PLAYERSTATE_DAMAGE,		//ダメージ
	PLAYERSTATE_DEATH,		//脂肪
	PLAYERSTATE_MUTEKI,		//無敵状態
	PLAYERSTATE_MAX
}ACTIONPLAYERSTATE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;                        //現在の位置
	D3DXVECTOR3 posOld;						//前回の位置
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 move;						//移動量
	ACTIONBLOCK* pBlock;					//ブロックへのポインタ
	ACTIONPLAYERSTATE state;				//プレイヤーの状態
	int nCounterState;						//状態管理カウンター
	int nGuardCnt;							//ガードカウンター
	int nCntAnimState;						//状態をカウント
	int nLife;								//命
	float Length;							//対角線の長さ
	float Angle;							//対角線の角度
	bool bUse;								//使われているか
	bool bHit;								//あたりはんてぇ
	bool bJamp1st;							//ジャンプの使用1度目
	bool bRightMove;						//向き	true=右向き	false=左向き
	bool bStop;								//止まっているか
	bool bDisp;								//表示するかしないか
	bool bGetItem;							//アイテム取得用のフラグ
	bool bBlockUse;							//ブロック当たり判定用
	bool bLanding;							//地面についているか
}ActionPlayer;

//プロト
void InitActionPlayer(void);
void UninitActionPlayer(void);
void UpdateActionPlayer(void);
void DrawActionPlayer(void);
ActionPlayer* GetActionPlayer(void);
D3DXVECTOR3 GetActionPos(void);
#endif