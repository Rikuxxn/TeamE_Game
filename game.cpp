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
#include "meshceiling.h"
//#include "sound.h"
#include "guage.h"
#include "shooting_game.h"
#include "crane_game.h"
#include "ui.h"
#include "shadow.h"
#include "map.h"

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;//ゲームの状態
int g_nCounterGameState = 0;//状態管理カウンター

bool g_bPause = false;	//ポーズ中かどうか
bool g_bDraw = false;	//ミニゲームの描画用
bool g_bDraw2 = false;
bool bSTClear;
bool bACClear;
bool bMap;
bool g_bMini;
int nCounter;
int nStgCnt;
int nCraneCnt;

//==============================================
//ゲーム画面の初期化処理
//==============================================
void InitGame(void)
{

	// カーソルを画面中央に戻す
	SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);


	// カーソルを非表示にする
	SetCursorVisibility(false);


	//メッシュフィールドの初期化処理
	InitMeshfield();


	//メッシュシーリングの初期化処理
	InitMeshCeiling();


	//メッシュシリンダーの初期化処理
	InitMeshcylinder();


	//カメラの初期化処理
	InitCamera();


	//ライトの初期化処理
	InitLight();


	//ブロックの初期化処理
	InitBlock();


	//影の初期化
	InitShadow();


	//プレイヤーの初期化処理
	InitPlayer();
	

	//敵の初期化
	InitEnemy();


	////タイムの初期化処理
	//InitTime();


	////ビルボードの初期化処理
	//InitBillboard();


	//ゲージの初期化
	InitGuage();


	//UIの初期化
	InitUI();

	//ミニゲームの初期化
	InitShootingGame();
	InitCraneGame();

	//// 天井の中央付近から特定エリアを照らすスポットライト
	//AddLight(
	//	D3DLIGHT_SPOT,                       // ライトの種類
	//	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),   // 少し明るい光
	//	D3DXVECTOR3(0.0f, -1.0f, 0.0f),      // 真下方向
	//	D3DXVECTOR3(0.0f, 5.0f, 0.0f)       // 天井中央の位置
	//);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                 // ライトの種類
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),    // 暗めの白い光
		D3DXVECTOR3(0.0f, -1.0f, 0.0f),       // 真下方向
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // 天井の位置（無視される）
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ライトの種類
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),    // 暗めの白い光
		D3DXVECTOR3(-1.0f, 0.0f, 0.0f),       // 左方向
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // 天井の位置（無視される）
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ライトの種類
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),    // 暗めの白い光
		D3DXVECTOR3(0.0f, 0.0f, -1.0f),       // 手前方向
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // 天井の位置（無視される）
	);


	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ライトの種類
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),    // 暗めの白い光
		D3DXVECTOR3(1.0f, 0.0f, 0.0f),       // 右方向
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // 天井の位置（無視される）
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ライトの種類
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),    // 暗めの白い光
		D3DXVECTOR3(0.0f, 0.0f, 1.0f),       // 奥方向
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // 天井の位置（無視される）
	);

	// 敵
	SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, 160.0f));


	//ポーズの初期化処理
	InitPause();

	//マップの初期化処理
	InitMap();

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
	nCraneCnt = 0;
	nStgCnt = 0;

	bSTClear = false;
	bACClear = false;
	g_bMini = false;
	bMap = false;

	//エディット読み込み
	LoadBlockData();

	//エディット読み込み
	LoadWallData();

}
//============================================
//ゲーム画面の終了処理
//============================================
void UninitGame(void)
{

	//StopSound(SOUND_LABEL_GAMEBGM);
	//StopSound();

	// カーソルを表示する
	SetCursorVisibility(true);


	//メッシュフィールドの終了処理
	UninitMeshfield();


	//メッシュシーリングの終了処理
	UninitMeshCeiling();


	//メッシュシリンダーの終了処理
	UninitMeshcylinder();


	//カメラの終了処理
	UninitCamera();


	//ライトの終了処理
	UninitLight();


	//ブロックの終了処理
	UninitBlock();


	//影の終了処理
	UninitShadow();


	////ビルボードの終了処理
	//UninitBillboard();


	//プレイヤーの終了処理
	UninitPlayer();


	//敵の終了処理
	UninitEnemy();


	////タイムの終了処理
	//UninitTime();


	//ポーズの終了処理
	UninitPause();


	//マップの終了処理
	UninitMap();

	////エフェクトの終了処理
	//UninitEffect();


	////パーティクルの終了処理
	//UninitParticle();


	//ゲージの終了処理
	UninitGuage();


	//UIの終了処理
	UninitUI();

	//ミニゲームの終了処理
	UninitShootingGame();
	UninitCraneGame();
}
//=========================================
//ゲーム画面の更新処理
//=========================================
void UpdateGame(void)
{
	//int nTime = GetTime();
	bool bExit = GetExit();
	STGSTATE pStgState = GetShootingGameState();
	CRANEGAMESTATE pCraneState = GetCraneGameState();
	Player* pPlayer = GetPlayer();//プレイヤーの情報へのポインタにプレイヤーの先頭アドレスが代入される
	bool bArcade = GetArcade();
	bool bCatcher = GetCatcher();
	bool bEnd = GetEnd();


	// ミニゲーム中はポーズを開けないようにする
	if (g_bMini == false && bMap == false && (KeyboardTrigger(DIK_P) == true || JoyPadTrigger(JOYKEY_START) == true))
	{
		g_bPause = g_bPause ? false : true;

		// PlaySound(SOUND_LABEL_PAUSE); // ポーズ音の再生
	}

	if (g_bPause == true)
	{//ポーズ中

		//ポーズの更新処理
		UpdatePause();

		// カーソルを表示する
		SetCursorVisibility(true);

	}
	else
	{//ポーズ中ではない

		// ミニゲーム（シューティング）のトリガー
		if (KeyboardTrigger(DIK_E) == true && pStgState != STGSTATE_END && bArcade == true && bMap == false)
		{
			g_bDraw = g_bDraw ? false : true;
			g_bMini = g_bMini ? false : true;
		}

		// ミニゲーム（アクション）のトリガー
		if (KeyboardTrigger(DIK_E) == true && pCraneState != CRANEGAMESTATE_END && bCatcher == true && bMap == false)
		{
			g_bDraw2 = g_bDraw2 ? false : true;
			g_bMini = g_bMini ? false : true;
		}

		// マップを開けるのはミニゲームがどちらも動いていない場合のみ
		if (g_bMini == false && g_bDraw == false && g_bDraw2 == false &&
			(KeyboardTrigger(DIK_C) == true || JoyPadTrigger(JOYKEY_BACK) == true))
		{
			bMap = bMap ? false : true;
		}


		// シューティングゲーム終了時の処理
		if (pStgState == STGSTATE_END)
		{
			if (nStgCnt <= 120)
			{
				nStgCnt++;
			}

			// 120(2秒)経ったら
			if (nStgCnt >= 120)
			{
				g_bDraw = false;
				bSTClear = true;
				if (g_bDraw2 == false) // クレーンゲームが動いていないなら
				{
					g_bMini = false; // ミニゲーム全体を終了
				}
			}
		}

		// クレーンゲーム終了時の処理
		if (pCraneState == CRANEGAMESTATE_END)
		{
			if (nCraneCnt <= 120)
			{
				nCraneCnt++;
			}

			// 120(2秒)経ったら
			if (nCraneCnt >= 120)
			{
				g_bDraw2 = false;
				bACClear = true;
				if (g_bDraw == false) // シューティングゲームが動いていないなら
				{
					g_bMini = false; // ミニゲーム全体を終了
				}
			}
		}

		// カーソルを非表示する
		SetCursorVisibility(false);


		if (g_bDraw == false && g_bDraw2 == false)
		{
			//プレイヤーの更新処理
			UpdatePlayer();
		}
		if (g_bDraw == true)
		{
			//ミニゲーム(シューティング)の更新処理
			UpdateShootingGame();
		}
		if (g_bDraw2 == true)
		{
			//ミニゲーム(アクション)の更新処理
			UpdateCraneGame();
		}

		//敵の更新処理
		UpdateEnemy();


		//メッシュフィールドの更新処理
		UpdateMeshfield();


		//メッシュシーリングの更新処理
		UpdateMeshCeiling();


		//メッシュシリンダーの更新処理
		UpdateMeshcylinder();

		if (g_bDraw == false && g_bDraw2 == false)
		{
			//カメラの更新処理
			UpdateCamera();
		}


		////ライトの更新処理
		//UpdateLight(0, D3DXVECTOR3(0.0f, -1.0f, 0.0f));


		//ブロックの更新処理
		UpdateBlock();


		//影の更新処理
		UpdateShadow();


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

		//ゲージの更新処理
		UpdateGuage();

		//UIの更新処理
		UpdateUI();

	}


	if ((pPlayer->bDisp == false || bExit == true /*|| nTime <= 0*/ || bEnd  == true) && g_gameState != GAMESTATE_NONE)
	{

		//モード設定(リザルト画面に移行)
 		g_gameState = GAMESTATE_END;
		g_bDraw = false;
		g_bDraw2 = false;
		bMap = false;
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
	Player* pPlayer = GetPlayer();	//プレイヤー取得

	//プレイヤーの描画処理
	DrawPlayer();


	//敵の描画処理
	DrawEnemy();


	//カメラの設定処理
	SetCamera();


	//メッシュフィールドの描画処理
	DrawMeshfield();


	//メッシュシーリングの描画処理
	DrawMeshCeiling();


	////メッシュシリンダーの描画処理
	//DrawMeshcylinder();


	//ブロックの描画処理
	DrawBlock();


	////エフェクトの描画処理
	//DrawEffect();


	////パーティクルの描画処理
	//DrawParticle();


	////ビルボードの描画処理
	//DrawBillboard();


	////タイムの描画処理
	//DrawTime();

	if (g_bMini == false)
	{
		//UIの描画処理
		DrawUI();
	}
	if (pPlayer->bDrawDush == true)
	{
		//ゲージの描画処理
		DrawGuage();
	}

	//影の描画処理
	DrawShadow();

	if (bMap == true && g_bMini == false)
	{//マップの描画
		DrawMap();
	}
	if (g_bPause == true)
	{//ポーズ中
		//ポーズの描画処理
		DrawPause();
	}

	if (g_bDraw == true && nStgCnt <= 120)
	{
		//ミニゲームの描画処理
		DrawShootingGame();
	}
	else if (g_bDraw2 == true && nCraneCnt <= 120)
	{
		DrawCraneGame();
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
//============================================
// STクリアの取得
//============================================
bool GetSTClear(void)
{
	return bSTClear;
}
//============================================
// ACクリアの取得
//============================================
bool GetACClear(void)
{
	return bACClear;
}



