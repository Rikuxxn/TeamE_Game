//========================
//|      パスワード		 |
//|Author:Yoshida Atsushi|
//========================

// インクルードファイル宣言
#include <time.h>
#include "input.h"
#include "password_background.h"
#include "password_block.h"
#include "password_clear.h"
#include "password_effect.h"
#include "password_fade.h"
#include "password_game.h"
#include "password_item.h"
#include "password_particle.h"
#include "password_score.h"
//#include "sound.h"

// グローバル変数宣言
PASSWORDGAMESTATE g_gameState = PASSWORDGAMESTATE_NONE;	//ゲームの状態
int g_nCounterPasswordGameState = 0;					//状態管理カウンター
int g_nA1, g_nA2, g_nA3, g_nA4;							//パスワードの答え

//=========================
//|      初期化処理　     |
//=========================
void InitPasswordGame(void)
{
	//各種オブジェクトの初期化処理
	InitPasswordBackGround();	//背景の初期化処理
	InitPasswordParticle();		//パーティクルの初期化
	InitPassBlock();		//ブロックの初期化処理
	InitPasswordEffect();		//エフェクトの初期化
	InitPasswordItem();			//アイテムの初期化
	InitPasswordClear();		//クリア画面の初期化
	InitPassword();				//パスワードの初期化

	SetPassword(0);
	//アイテム
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_LEFT, ITEM_POSY_TOP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 1, NUMTYPE_1);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_CENTER, ITEM_POSY_TOP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2, NUMTYPE_2);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_RIGHT, ITEM_POSY_TOP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3, NUMTYPE_3);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_LEFT, ITEM_POSY_MIDDLE_UP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 4, NUMTYPE_4);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_CENTER, ITEM_POSY_MIDDLE_UP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 5, NUMTYPE_5);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_RIGHT, ITEM_POSY_MIDDLE_UP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 6, NUMTYPE_6);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_LEFT, ITEM_POSY_MIDDLE_DOWN, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 7, NUMTYPE_7);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_CENTER, ITEM_POSY_MIDDLE_DOWN, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 8, NUMTYPE_8);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_RIGHT, ITEM_POSY_MIDDLE_DOWN, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 9, NUMTYPE_9);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_LEFT, ITEM_POSY_UNDER, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 11, NUMTYPE_DELETE);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_CENTER, ITEM_POSY_UNDER, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 0, NUMTYPE_0);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_RIGHT, ITEM_POSY_UNDER, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 10, NUMTYPE_ENTER);

	srand((unsigned int)time(NULL));		//ランダム
	g_gameState = PASSWORDGAMESTATE_NORMAL;	//通常状態に設定
	g_nCounterPasswordGameState = 0;
	g_nA1 = rand() % 9 + 0;
	g_nA2 = rand() % 9 + 0;
	g_nA3 = rand() % 9 + 0;
	g_nA4 = rand() % 9 + 0;

	////サウンドの再生
	//PlaySound(SOUND_LABEL_GAMEBGM);
}
//=======================
//|      終了処理	    |
//=======================
void UninitPasswordGame(void)
{
	////サウンドの停止
	//StopSound(SOUND_LABEL_GAMEBGM);

	//各種オブジェクトの終了処理
	UninitPasswordBackGround();	//背景の終了処理
	UninitPasswordParticle();	//パーティクルの終了処理
	UninitPassBlock();		//ブロックの終了処理
	UninitPasswordEffect();		//エフェクトの終了処理
	UninitPasswordItem();		//アイテムの終了処理
	UninitPasswordClear();		//クリア画面の終了処理
	UninitPassword();
}
//=======================
//| 	 更新処理	    |
//=======================
void UpdatePasswordGame(void)
{
	int nPass = GetPassword();
	int nPass2 = GetPassword2();
	int nPass3 = GetPassword3();
	int nPass4 = GetPassword4();
	bool bJudge = GetJudgment();

	//各種オブジェクトの更新処理
	UpdatePasswordBackGround();	//背景の更新処理
	UpdatePasswordParticle();	//パーティクルの更新処理
	UpdatePasswordEffect();		//エフェクトの更新処理
	UpdatePasswordItem();		//アイテムの更新処理
	UpdatePassword();

	if (nPass == g_nA1 &&
		nPass2 == g_nA2 &&
		nPass3 == g_nA3 &&
		nPass4 == g_nA4 &&
		bJudge == true)//暗証番号の一致
	{//終了条件
		//画面(モード)の設定
		g_gameState = PASSWORDGAMESTATE_END;
	}
	else if ((nPass == g_nA1 || nPass != g_nA1) &&
		(nPass2 == g_nA2 || nPass2 != g_nA2) &&
		(nPass3 == g_nA3 || nPass3 != g_nA3) &&
		(nPass4 == g_nA4 || nPass4 != g_nA4) &&
		bJudge == true)//暗証番号の不一致
	{
		SetPassword(0);
	}

	switch (g_gameState)
	{
	case PASSWORDGAMESTATE_NORMAL:	//通常状態
		break;
	case PASSWORDGAMESTATE_END:		//終了状態
		if (g_nCounterPasswordGameState <= 45)
		{
			g_nCounterPasswordGameState++;
		}

		if (g_nCounterPasswordGameState >= 45)
		{
			UpdatePasswordClear();
		}
		break;
	}
}
//=======================
//|  ゲームの描画処理   |
//=======================
void DrawPasswordGame(void)
{
	//各種オブジェクトの描画処理
	DrawPasswordBackGround();	//背景の描画処理
	DrawPasswordParticle();		//パーティクルの描画処理
	DrawPasswordItem();			//アイテムの描画処理
	DrawPassBlock();		//ブロックの描画処理
	DrawPasswordEffect();		//エフェクトの描画処理
	DrawPassword();

	if (g_nCounterPasswordGameState >= 45)
	{
		DrawPasswordClear();
	}
}
void SetPasswordGameState(PASSWORDGAMESTATE state)
{
	g_gameState = state;
}
PASSWORDGAMESTATE GetPasswordGameState(void)
{
	return g_gameState;
}
int GetAnum(void)
{
	return g_nA1;
}
int GetAnum2(void)
{
	return g_nA2;
}
int GetAnum3(void)
{
	return g_nA3;
}
int GetAnum4(void)
{
	return g_nA4;
}