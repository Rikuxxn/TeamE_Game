//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "crane_game.h"
#include "input.h"
#include "crane_player.h"
#include "crane_fade.h"
#include "crane_effect.h"
#include "crane_particle.h"
#include "crane_block.h"
#include "crane_item.h"
#include "crane_background.h"
#include "time.h"
#include "game.h"
#include "sound.h"
#include "crane_clear.h"
#include "crane_score.h"
#include "password_game.h"

//グローバル
CRANEGAMESTATE g_gameState = CRANEGAMESTATE_NONE;	//ゲームの状態
int g_nCounterCraneGameState = 0;					//状態管理カウンター

void InitCraneGame(void)
{
	//各種オブジェクトの初期化処理
	InitCraneBackGround();	//背景の初期化処理
	InitCraneParticle();	//パーティクルの初期化
	InitCranePlayer();		//プレイヤーの初期化処理
	InitCraneBlock();		//ブロックの初期化処理
	InitCraneEffect();		//エフェクトの初期化
	InitCraneItem();		//アイテムの初期化
	InitCraneClear();		//クリア画面の初期化

	SetCraneBlock(D3DXVECTOR3(FIELD_LEFT + 100.0f, FIELD_UNDER - 30.0f, 0.0f), D3DXVECTOR3(), 40.0f, 30.0f, 0);	//ブロック
	SetCraneItem(D3DXVECTOR3(600.0f, FIELD_UNDER - 15.0f, 0.0f), ITEM_WIDTH + 20.0f, ITEM_HEIGHT + 20.0f, 1);
	SetCraneItem(D3DXVECTOR3(800.0f, FIELD_UNDER - 15.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2);
	//SetCraneItem(D3DXVECTOR3(740.0f, FIELD_UNDER - 15.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3);					//アイテム

	g_gameState = CRANEGAMESTATE_NORMAL;//通常状態に設定
	g_nCounterCraneGameState = 0;

	////サウンドの再生
	//PlaySound(SOUND_LABEL_CRANEGAMEBGM);
}
void UninitCraneGame(void)
{
	////サウンドの停止
	//StopSound(SOUND_LABEL_CRANEGAMEBGM);

	//各種オブジェクトの終了処理
	UninitCraneBackGround();	//背景の終了処理
	UninitCraneParticle();		//パーティクルの終了処理
	UninitCranePlayer();		//プレイヤーの終了処理
	UninitCraneBlock();			//ブロックの終了処理
	UninitCraneEffect();		//エフェクトの終了処理
	UninitCraneItem();			//アイテムの終了処理
	UninitCraneClear();			//クリア画面の終了処理
}
void UpdateCraneGame(void)
{
	CranePlayer* pPlayer = GetCranePlayer();
	int nNum = GetNumItem();

	//各種オブジェクトの更新処理
	UpdateCraneBackGround();	//背景の更新処理
	UpdateCraneParticle();		//パーティクルの更新処理
	UpdateCranePlayer();		//プレイヤーの更新処理
	UpdateCraneEffect();		//エフェクトの更新処理
	UpdateCraneItem();			//アイテムの更新処理

	if (pPlayer->bUse == false || nNum <= 0)//終了条件
	{
		//画面(モード)の設定
		g_gameState = CRANEGAMESTATE_END;
	}

	switch (g_gameState)
	{
	case CRANEGAMESTATE_NORMAL://通常状態
		break;
	case CRANEGAMESTATE_END://終了状態
		if (g_nCounterCraneGameState <= 45)
		{
			g_nCounterCraneGameState++;
		}

		if (g_nCounterCraneGameState == 45 && nNum == 0 && pPlayer->bUse == true)
		{
			PlaySound(SOUND_LABEL_MINICLEAR);
			//UpdateCraneClear();
		}
		break;
	}
}
void DrawCraneGame(void)
{
	//各種オブジェクトの描画処理
	DrawCraneBackGround();	//背景の描画処理
	DrawCraneParticle();	//パーティクルの描画処理
	DrawCranePlayer();		//プレイヤーの描画処理
	DrawCraneItem();		//アイテムの描画処理
	DrawCraneBlock();		//ブロックの描画処理
	DrawCraneEffect();		//エフェクトの描画処理

	//if (g_nCounterCraneGameState >= 45)
	//{
	//	DrawCraneClear();
	//}
}
void SetCraneGameState(CRANEGAMESTATE state)
{
	g_gameState = state;
}
CRANEGAMESTATE GetCraneGameState(void)
{
	return g_gameState;
}