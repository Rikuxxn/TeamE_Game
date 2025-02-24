//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------
#ifndef _CRANEPLAYER_H_//このマクロ定義がされてなかったら
#define _CRANEPLAYER_H_//２重インクルード防止のマクロ定義

#define WIDTH (50.0f)		// プレイヤー幅
#define HEIGHT (100.0f)		// プレイヤー高さ
#define DOWN (3.0f)			// 降りる速さ
#define UP (-3.0f)			// 上る速さ
#define MAX_SPEED_L (-3.0f)	// 最速左
#define MAX_SPEED_R (3.0f)	// 最速右

#include "crane_block.h"

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0, // 出現状態（点滅）
	PLAYERSTATE_NORMAL,		// 通常
	PLAYERSTATE_DAMAGE,		// ダメージ
	PLAYERSTATE_DEATH,		// 脂肪
	PLAYERSTATE_MUTEKI,		// 無敵状態
	PLAYERSTATE_MAX
}CRANEPLAYERSTATE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;        // 現在の位置
	D3DXVECTOR3 posOld;		// 前回の位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 move;		// 移動量
	CRANEBLOCK* pBlock;		// ブロックへのポインタ
	CRANEPLAYERSTATE state;	// プレイヤーの状態
	int nCounterState;		// 状態管理カウンター
	int nCntAnimState;		// 状態をカウント
	float Length;			// 対角線の長さ
	float Angle;			// 対角線の角度
	bool bUse;				// 使われているか
	bool bMove;				// 動けるか
	bool bUpSound;			// 上に上がっているか
	bool bLeft;				// 左に進むか
	bool bDown;				// 落ちているか
	bool bLanding;			// 着地しているか
	bool bGetItem;			// アイテム取得
	bool bFall;				// アイテムが落ちているか
}CranePlayer;

//プロト
void InitCranePlayer(void);
void UninitCranePlayer(void);
void UpdateCranePlayer(void);
void DrawCranePlayer(void);
CranePlayer* GetCranePlayer(void);
D3DXVECTOR3 GetCranePos(void);
#endif