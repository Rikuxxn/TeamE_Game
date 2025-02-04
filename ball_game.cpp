//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "ball_game.h"
#include "input.h"
#include "ball_fade.h"
#include "ball_effect.h"
#include "ball_particle.h"
#include "ball_block.h"
#include "ball_item.h"
#include "ball_background.h"
#include "time.h"
//#include "sound.h"
#include "ball_clear.h"

//グローバル
BALLGAMESTATE g_gameState = BALLGAMESTATE_NONE;	  //ゲームの状態
int g_nCounterBallGameState = 0;				  //状態管理カウンター

void InitBallGame(void)
{
	//各種オブジェクトの初期化処理
	InitBallBackGround();	//背景の初期化処理
	InitBallParticle();		//パーティクルの初期化
	InitBallBlock();		//ブロックの初期化処理
	InitBallEffect();		//エフェクトの初期化
	InitBallItem();			//アイテムの初期化
	InitBallClear();		//クリア画面の初期化

	SetBallBlock(D3DXVECTOR3(BALLFIELD_LEFT + 100.0f, BALLFIELD_UNDER - 30.0f, 0.0f), D3DXVECTOR3(), 50.0f, 30.0f, 0);	//ブロック
	
	SetBallItem(D3DXVECTOR3(740.0f, BALLFIELD_UNDER - 160.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 0);					//アイテム
	SetBallItem(D3DXVECTOR3(540.0f, BALLFIELD_UNDER - 69.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 1);
	SetBallItem(D3DXVECTOR3(640.0f, BALLFIELD_UNDER - 161.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2);
	SetBallItem(D3DXVECTOR3(840.0f, BALLFIELD_UNDER - 475.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3);

	SetBallItem(D3DXVECTOR3(340.0f, BALLFIELD_UNDER - 304.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3);
	SetBallItem(D3DXVECTOR3(564.0f, BALLFIELD_UNDER - 121.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 1);
	SetBallItem(D3DXVECTOR3(792.0f, BALLFIELD_UNDER - 207.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 0);
	SetBallItem(D3DXVECTOR3(284.0f, BALLFIELD_UNDER - 94.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2);

	//SetBallItem(D3DXVECTOR3(313.0f, BALLFIELD_UNDER - 571.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 1);
	//SetBallItem(D3DXVECTOR3(207.0f, BALLFIELD_UNDER - 432.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3);
	//SetBallItem(D3DXVECTOR3(580.0f, BALLFIELD_UNDER - 389.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2);
	//SetBallItem(D3DXVECTOR3(703.0f, BALLFIELD_UNDER - 249.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 0);

	SetBallItem(D3DXVECTOR3(452.0f, BALLFIELD_UNDER - 571.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 1);
	SetBallItem(D3DXVECTOR3(513.0f, BALLFIELD_UNDER - 432.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3);
	SetBallItem(D3DXVECTOR3(637.0f, BALLFIELD_UNDER - 389.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2);
	SetBallItem(D3DXVECTOR3(870.0f, BALLFIELD_UNDER - 209.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 0);

	g_gameState = BALLGAMESTATE_NORMAL;//通常状態に設定
	g_nCounterBallGameState = 0;

	////サウンドの再生
	//PlaySound(SOUND_LABEL_GAMEBGM);
}
void UninitBallGame(void)
{
	////サウンドの停止
	//StopSound(SOUND_LABEL_GAMEBGM);

	//各種オブジェクトの終了処理
	UninitBallBackGround();	//背景の終了処理
	UninitBallParticle();		//パーティクルの終了処理
	UninitBallBlock();			//ブロックの終了処理
	UninitBallEffect();		//エフェクトの終了処理
	UninitBallItem();			//アイテムの終了処理
	UninitBallClear();			//クリア画面の終了処理
}
void UpdateBallGame(void)
{
	int nNum = GetNumBallItem();

	//各種オブジェクトの更新処理
	UpdateBallBackGround();	//背景の更新処理
	UpdateBallParticle();	//パーティクルの更新処理
	UpdateBallEffect();		//エフェクトの更新処理
	UpdateBallItem();		//アイテムの更新処理

	if (nNum==0)//終了条件
	{
		//画面(モード)の設定
		g_gameState = BALLGAMESTATE_END;
	}

	switch (g_gameState)
	{
	case BALLGAMESTATE_NORMAL://通常状態
		break;
	case BALLGAMESTATE_END://終了状態
		if (g_nCounterBallGameState <= 45)
		{
			g_nCounterBallGameState++;
		}

		if (g_nCounterBallGameState >= 45 && nNum == 0)
		{
			UpdateBallClear();
		}
		break;
	}
}
void DrawBallGame(void)
{
	//各種オブジェクトの描画処理
	DrawBallBackGround();	//背景の描画処理
	DrawBallParticle();		//パーティクルの描画処理
	DrawBallItem();			//アイテムの描画処理
	DrawBallBlock();		//ブロックの描画処理
	DrawBallEffect();		//エフェクトの描画処理

	if (g_nCounterBallGameState >= 45)
	{
		DrawBallClear();
	}
}
void SetBallGameState(BALLGAMESTATE state)
{
	g_gameState = state;
}
BALLGAMESTATE GetBallGameState(void)
{
	return g_gameState;
}