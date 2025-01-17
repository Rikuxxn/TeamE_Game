//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "input.h"
//#include "score.h"
//#include "ranking.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "pause.h"
#include "time.h"
//#include "particle.h"
//#include "effect.h"
#include "camera.h"
#include "warning.h"
//#include "wall.h"
//#include "billboard.h"
#include "light.h"
//#include "meshwall.h"
//#include "shadow.h"
#include "meshfield.h"
//#include "rankingscore.h"
#include "model.h"
#include "enemy.h"
#include "meshcylinder.h"
#include "block.h"
#include "edit.h"
//#include "sound.h"

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;//ゲームの状態
int g_nCounterGameState = 0;//状態管理カウンター

bool g_bPause = false;//ポーズ中かどうか
int nCounter;

//==============================================
//ゲーム画面の初期化処理
//==============================================
void InitGame(void)
{

	//メッシュフィールドの初期化処理
	InitMeshfield();


	//メッシュシリンダーの初期化処理
	InitMeshcylinder();


	//カメラの初期化処理
	InitCamera();


	//ライトの初期化処理
	InitLight();


	////モデルの初期化処理
	//InitModel();


	//ブロックの初期化処理
	InitBlock();


	////影の初期化
	//InitShadow();


	//プレイヤーの初期化処理
	InitPlayer();


	//敵の初期化
	InitEnemy();


	////タイムの初期化処理
	//InitTime();


	////ビルボードの初期化処理
	//InitBillboard();


	//ブロック
	SetBlock(D3DXVECTOR3(-220.0f, 0.0f, 325.0f), BLOCKTYPE_NORMAL);		//	壁
	//SetBlock(D3DXVECTOR3(-220.0f, 0.0f, 85.0f), BLOCKTYPE_NORMAL);		//	ドア


	//SetModel(D3DXVECTOR3(-220.0f, 0.0f, 285.0f), WALLTYPE_NORMAL);		//	壁


	//// 壁のposが真ん中の時のやつ
	////奥壁
	//SetWall(D3DXVECTOR3(-350.0f, 50.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////右壁
	//SetWall(D3DXVECTOR3(350.0f, 50.0f, 350.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////手前壁
	//SetWall(D3DXVECTOR3(350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////左壁
	//SetWall(D3DXVECTOR3(-350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);


	////壁のposが端の時のやつ
	////奥壁
	//SetWall(D3DXVECTOR3(-350.0f, 50.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////右壁
	//SetWall(D3DXVECTOR3(350.0f, 50.0f, 350.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////手前壁
	//SetWall(D3DXVECTOR3(350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////左壁
	//SetWall(D3DXVECTOR3(-350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);



	//// 敵
	//SetEnemy(D3DXVECTOR3(280.0f, 0.0f, 260.0f));


	//ポーズの初期化処理
	InitPause();


	////エフェクトの初期化処理
	//InitEffect();


	////パーティクルの初期化処理
	//InitParticle();


	////サウンドの再生
	//PlaySound(SOUND_LABEL_GAMEBGM);


	////サウンドの停止
	//StopSound(SOUND_LABEL_RANK);


	g_gameState = GAMESTATE_NORMAL;//通常状態に設定
	g_nCounterGameState = 0;
	g_bPause = false;//ポーズ解除
	nCounter = 0;

	////エディット読み込み
	//LoadBlockData();

}
//============================================
//ゲーム画面の終了処理
//============================================
void UninitGame(void)
{

	//StopSound(SOUND_LABEL_GAMEBGM);
	//StopSound();

	//メッシュフィールドの終了処理
	UninitMeshfield();


	//メッシュシリンダーの終了処理
	UninitMeshcylinder();


	//カメラの終了処理
	UninitCamera();


	//ライトの終了処理
	UninitLight();


	////モデルの終了処理
	//UninitModel();


	//ブロックの終了処理
	UninitBlock();


	////影の終了処理
	//UninitShadow();


	////ビルボードの終了処理
	//UninitBillboard();


	//プレイヤーの終了処理
	UninitPlayer();


	//敵の終了処理
	UninitEnemy();


	////タイムの終了処理
	//UninitTime();


	////エフェクトの終了処理
	//UninitEffect();


	////パーティクルの終了処理
	//UninitParticle();

}
//=========================================
//ゲーム画面の更新処理
//=========================================
void UpdateGame(void)
{
	//int nTime = GetTime();
	bool bExit = GetExit();

	Player* pPlayer = GetPlayer();//プレイヤーの情報へのポインタにプレイヤーの先頭アドレスが代入される

	if (KeyboardTrigger(DIK_P) == true|| JoyPadTrigger(JOYKEY_START)==true)
	{//ESCAPE(ポーズ)キーが押された
		g_bPause = g_bPause ? false : true;

		//PlaySound(SOUND_LABEL_PAUSE);

	}

	if (g_bPause == true)
	{//ポーズ中

		//ポーズの更新処理
		UpdatePause();

	}
	else
	{

		//プレイヤーの更新処理
		UpdatePlayer();


		//敵の更新処理
		UpdateEnemy();


		//メッシュフィールドの更新処理
		UpdateMeshfield();


		//メッシュシリンダーの更新処理
		UpdateMeshcylinder();


		//カメラの更新処理
		UpdateCamera();


		//ライトの更新処理
		UpdateLight();


		////モデルの更新処理
		//UpdateModel();


		//ブロックの更新処理
		UpdateBlock();


		////影の更新処理
		//UpdateShadow();


		////ビルボードの更新処理
		//UpdateBillboard();


		////エフェクトの更新処理
		//UpdateEffect();


		////タイムの更新処理
		//UpdateTime();


		////パーティクルの更新処理
		//UpdateParticle();

		//if (KeyboardTrigger(DIK_F5) == true)
		//{
		//	onWireFrame();
		//}
		//else if (KeyboardTrigger(DIK_F6) == true)
		//{
		//	offWireFrame();
		//}
	}

	bool bEnd = GetEnd();

	if ((pPlayer->bDisp == false || bExit == true /*|| nTime <= 0*/ || bEnd  == true) && g_gameState != GAMESTATE_NONE)
	{

		//モード設定(リザルト画面に移行)
 		g_gameState = GAMESTATE_END;

	}

	int nResultScore;
	//nResultScore = GetScore();
	//nTime = GetTime();

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://通常状態
		break;

	case GAMESTATE_END://終了状態
		g_nCounterGameState++;

		if (g_nCounterGameState >= 60)
		{
			
			g_nCounterGameState = 0;

			g_gameState = GAMESTATE_NONE;

			//モード設定(リザルト画面に移行)
			SetFade(MODE_RESULT);

			if (bExit == true)
			{

				////タイムに応じてスコア加算
				//AddScore((nTime* GetScore()) * 0.2f);


				////リザルトスコアの設定
				//SetResultScore(GetScore());


				////ランキングのリセット
				//ResetRanking();


				////ランキングの設定
				//SetRanking(GetScore());

			}

		}
		break;
	}

}
//===========================================
//ゲーム画面の描画処理
//===========================================
void DrawGame(void)
{

	//プレイヤーの描画処理
	DrawPlayer();


	//敵の描画処理
	DrawEnemy();


	//カメラの設定処理
	SetCamera();


	//メッシュフィールドの描画処理
	DrawMeshfield();


	//メッシュシリンダーの描画処理
	DrawMeshcylinder();


	////モデルの描画処理
	DrawModel();


	//ブロックの描画処理
	DrawBlock();


	////影の描画処理
	//DrawShadow();


	////エフェクトの描画処理
	//DrawEffect();


	////パーティクルの描画処理
	//DrawParticle();


	////ビルボードの描画処理
	//DrawBillboard();


	////タイムの描画処理
	//DrawTime();

	if (g_bPause == true)
	{//ポーズ中
		//ポーズの描画処理
		DrawPause();
	}

}
//=============================================
//ゲームの状態の設定
//=============================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//============================================
//ゲーム状態の取得
//============================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
//============================================
//ポーズの有効無効設定
//============================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}



