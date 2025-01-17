//=======================================
//
//プレイヤー処理[player.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _PLAYER_H_//このマクロ定義がされていなかったら
#define _PLAYER_H_//2重インクルード防止のマクロ定義

#include "main.h"
#include "model.h"
#include "motion.h"

//マクロ定義
#define PLAYER_SPEED (1.0f)					//プレイヤーのスピード
#define MAX_JUMP (40)						//ジャンプ力
#define MAX_GRAVITY (0.8)					//重力
#define PLAYER_LIFE (0)						//プレイヤーの体力

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0,					//出現状態(点滅)
	PLAYERSTATE_NORMAL,						//通常状態
	PLAYERSTATE_DAMAGE,						//ダメージ状態
	PLAYERSTATE_DEATH,						//死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤー構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 posOld;						//前の位置
	D3DXVECTOR3 size;						//サイズ
	D3DXVECTOR3 vtxMin;						//サイズ
	D3DXVECTOR3 vtxMax;						//サイズ
	D3DXVECTOR3 move;						//移動量
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 rotDestPlayer;				//向き
	PLAYERSTATE state;						//プレイヤーの状態
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int nLife;								//体力
	bool bJump;								//ジャンプしてるかどうか
	bool bUse;								//使われているかどうか
	bool bDisp;								//表示するかしないか
	Motion motion;
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);

#endif

