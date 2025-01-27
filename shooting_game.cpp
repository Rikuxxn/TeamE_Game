//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "shooting_game.h"
#include "input.h"
#include "shooting_player.h"
#include "shooting_bullet.h"
#include "shooting_enemy.h"
#include "shooting_effect.h"
#include "shooting_particle.h"
#include "shooting_clear.h"
//#include "sound.h"

//グローバル
STGSTATE g_gameState = STGSTATE_NONE;	 //ゲームの状態
int g_nCntShootingGameState = 0;						 //状態管理カウンター

void InitShootingGame(void)
{
	//各種オブジェクトの初期化処理

	InitBackGround();		//背景の初期化処理
	InitShootingPlayer();	//プレイヤーの初期化処理
	InitBullet();			//弾の初期化処理
	InitEffect();			//エフェクトの初期化
	InitShootingEnemy();	//敵の初期化
	InitClear();			//クリア表示の初期化
	InitParticle();			//パーティクルの初期化

	SetEnemy(D3DXVECTOR3(470.0f, 200.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(750.0f, 200.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(610.0f, 260.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(610.0f, 360.0f, 0.0f),  D3DXVECTOR3(1.0f, 0.0f, 0.0f),1);

	g_gameState = STGSTATE_NORMAL;//通常状態に設定
	g_nCntShootingGameState = 0;

	////サウンドの再生
	//PlaySound(SOUND_LABEL_GAMEBGM);
}
void UninitShootingGame(void)
{
	//StopSound();	//サウンドの停止

	//各種オブジェクトの終了処理
	UninitBackGround();		//背景の終了処理
	UninitShootingPlayer();	//プレイヤーの終了処理
	UninitBullet();			//弾の終了処理
	UninitEffect();			//エフェクトの終了処理
	UninitShootingEnemy();	//敵の終了処理
	UninitParticle();		//パーティクルの終了処理
	UninitClear();			//クリア表示の終了処理
}
void UpdateShootingGame(void)
{
	int nNum;
	ShootingPlayer* pPlayer = GetShootingPlayer();
	nNum = GetNumEnemy();

	//各種オブジェクトの更新処理
	UpdateBackGround();		//背景の更新処理
	UpdateParticle();		//パーティクルの更新処理
	UpdateShootingPlayer();	//プレイヤーの更新処理
	UpdateShootingEnemy();	//敵の更新処理
	UpdateBullet();			//弾の更新処理
	UpdateEffect();			//エフェクトの更新処理

	if (pPlayer->bUse == false || nNum <= 0)
	{
		//画面(モード)の設定
		g_gameState = STGSTATE_END;
	}
	switch (g_gameState)
	{
	case STGSTATE_NORMAL://通常状態
		break;
	case STGSTATE_END://終了状態
		if (g_nCntShootingGameState <= 90)
		{
			g_nCntShootingGameState++;
		}

		if (g_nCntShootingGameState >= 90 && nNum <= 0 && pPlayer->bUse == true)
		{
			UpdateClear();
		}
		break;
	}
}
void DrawShootingGame(void)
{
	//各種オブジェクトの描画処理
	DrawBackGround();		//背景の描画処理
	DrawBullet();			//弾の描画処理
	DrawShootingPlayer();	//プレイヤーの描画処理
	DrawShootingEnemy();	//敵の描画処理
	DrawEffect();			//エフェクトの描画処理
	DrawParticle();			//パーティクルの描画処理

	if (g_nCntShootingGameState >= 60)
	{
		DrawClear();		//クリア表示の描画処理
	}
}
void SetShootingGameState(STGSTATE state)
{
	g_gameState = state;
}
STGSTATE GetShootingGameState(void)
{
	return g_gameState;
}