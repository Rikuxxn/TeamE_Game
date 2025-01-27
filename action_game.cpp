//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "action_game.h"
#include "input.h"
#include "action_player.h"
#include "action_fade.h"
#include "action_effect.h"
#include "action_particle.h"
#include "action_block.h"
#include "action_item.h"
#include "action_background.h"
#include "time.h"
//#include "sound.h"
#include "action_clear.h"

//グローバル
ACTSTATE g_gameState = ACTSTATE_NONE;		//ゲームの状態
int g_nCntActionGameState = 0;						//状態管理カウンター

void InitActionGame(void)
{
	//各種オブジェクトの初期化処理
	InitActionBackGround();	//背景の初期化処理
	InitActionParticle();	//パーティクルの初期化
	InitActionPlayer();		//プレイヤーの初期化処理
	InitActionBlock();		//ブロックの初期化処理
	InitActionEffect();		//エフェクトの初期化
	InitActionItem();		//アイテムの初期化
	InitActionClear();		//クリア画面の初期化

	SetActionBlock(D3DXVECTOR3(640.0f, 700.0f, 0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), 240.0f, 20.0f, 1);	//地面
	SetActionBlock(D3DXVECTOR3(640.0f, 300.0f, 0.0f), D3DXVECTOR3(), 20.0f, 20.0f, 0);					//ブロック
	SetActionBlock(D3DXVECTOR3(520.0f, 320.0f, 0.0f),D3DXVECTOR3(), 20.0f, 20.0f, 0);
	SetActionBlock(D3DXVECTOR3(740.0f, 200.0f, 0.0f), D3DXVECTOR3(), 20.0f, 20.0f, 0);
	SetActionBlock(D3DXVECTOR3(430.0f, 440.0f, 0.0f),D3DXVECTOR3(), 30.0f, 20.0f, 0);
	SetActionBlock(D3DXVECTOR3(600.0f, 550.0f, 0.0f), D3DXVECTOR3(), 60.0f, 20.0f, 0);
	SetActionItem(D3DXVECTOR3(740.0f, 50.0f, 0.0f), 10.0f, 10.0f, 0);									//アイテム

	g_gameState = ACTSTATE_NORMAL;//通常状態に設定
	g_nCntActionGameState = 0;

	////サウンドの再生
	//PlaySound(SOUND_LABEL_GAMEBGM);
}
void UninitActionGame(void)
{
	////サウンドの停止
	//StopSound(SOUND_LABEL_GAMEBGM);

	//各種オブジェクトの終了処理
	UninitActionBackGround();	//背景の終了処理
	UninitActionParticle();		//パーティクルの終了処理
	UninitActionPlayer();		//プレイヤーの終了処理
	UninitActionBlock();		//ブロックの終了処理
	UninitActionEffect();		//エフェクトの終了処理
	UninitActionItem();			//アイテムの終了処理
	UninitActionClear();		//クリア画面の終了処理
}
void UpdateActionGame(void)
{
	ActionPlayer* pPlayer = GetActionPlayer();
	bool bItem;
	bItem = GetActionItem();

	//各種オブジェクトの更新処理
	UpdateActionBackGround();	//背景の更新処理
	UpdateActionParticle();		//パーティクルの更新処理
	UpdateActionPlayer();		//プレイヤーの更新処理
	UpdateActionEffect();		//エフェクトの更新処理
	UpdateActionItem();			//アイテムの更新処理

	if (pPlayer->bUse == false || bItem == true)//終了条件
	{
		//画面(モード)の設定
		g_gameState = ACTSTATE_END;
	}

	switch (g_gameState)
	{
	case ACTSTATE_NORMAL:	//通常状態
		break;
	case ACTSTATE_END:		//終了状態
		if (g_nCntActionGameState <= 45)
		{
			g_nCntActionGameState++;
		}

		if (g_nCntActionGameState >= 45 && bItem == true && pPlayer->bUse == true)
		{
			UpdateActionClear();
		}
		break;
	}
}
void DrawActionGame(void)
{
	//各種オブジェクトの描画処理
	DrawActionBackGround();	//背景の描画処理
	DrawActionParticle();		//パーティクルの描画処理
	DrawActionPlayer();		//プレイヤーの描画処理
	DrawActionBlock();		//ブロックの描画処理
	DrawActionEffect();		//エフェクトの描画処理
	DrawActionItem();			//アイテムの描画処理

	if (g_nCntActionGameState >= 45)
	{
		DrawActionClear();
	}
}
void SetGameState(ACTSTATE state)
{
	g_gameState = state;
}
ACTSTATE GetActionGameState(void)
{
	return g_gameState;
}