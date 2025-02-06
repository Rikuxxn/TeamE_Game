//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "input.h"
//#include "ranking.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "pause.h"
//#include "particle.h"
//#include "effect.h"
#include "camera.h"
#include "warning.h"
#include "light.h"
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
#include "password_game.h"
#include "crane_game.h"
#include "ball_game.h"
#include "ui.h"
#include "shadow.h"
#include "map.h"
#include "task.h"
#include "time.h"

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;		// ゲームの状態
int g_nCounterGameState = 0;				// 状態管理カウンター

GAME g_Game;								// ゲームの情報

bool g_bPause = false;	//ポーズ中かどうか

//==============================================
//ゲーム画面の初期化処理
//==============================================
void InitGame(void)
{

	//// カーソルを画面中央に戻す
	//SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);


	//// カーソルを非表示にする
	//SetCursorVisibility(false);


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


	//SetBlock(D3DXVECTOR3(200.0f, 0.0f, -120.0f), D3DXVECTOR3(0.0f, D3DX_PI *0.75f, 0.0f), BLOCKTYPE_TEST);


	//影の初期化
	InitShadow();


	//プレイヤーの初期化処理
	InitPlayer();
	

	//敵の初期化
	InitEnemy();


	//タイムの初期化処理
	InitTime();


	////ビルボードの初期化処理
	//InitBillboard();


	//ゲージの初期化
	InitGuage();


	//UIの初期化
	InitUI();

	//タスクUIの初期化処理
	InitTask();

	SetTask(D3DXVECTOR3(2350.0f, 200.0f, 0.0f), 160.0f, 25.0f, TASKTYPE_ONE);
	SetTask(D3DXVECTOR3(2350.0f, 200.0f, 0.0f), 160.0f, 25.0f, TASKTYPE_TWO);
	SetTask(D3DXVECTOR3(2350.0f, 200.0f, 0.0f), 160.0f, 25.0f, TASKTYPE_THREE);

	SetTask(D3DXVECTOR3(2350.0f, 230.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB1);
	SetTask(D3DXVECTOR3(2350.0f, 260.0f, 0.0f), 130.0f, 20.0f, TASKTYPE_SUB2);

	SetTask(D3DXVECTOR3(2350.0f, 230.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB3);
	SetTask(D3DXVECTOR3(2350.0f, 260.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB4);
	SetTask(D3DXVECTOR3(2350.0f, 290.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB5);

	SetTask(D3DXVECTOR3(2350.0f, 230.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB6);

	//ミニゲームの初期化
	InitShootingGame();
	InitCraneGame();
	InitBallGame();
	InitPasswordGame();

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
	g_Game.nCounter = 0;
	g_Game.nCraneCnt = 0;
	g_Game.nStgCnt = 0;
	g_Game.nBallCnt = 0;
	g_Game.nPassCnt = 0;
	g_Game.bSTClear = false;
	g_Game.bACClear = false;
	g_Game.bBallClear = false;
	g_Game.bPassClear = false;
	g_Game.bMini = false;
	g_Game.bMap = false;

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
	LPDIRECT3DDEVICE9 pDevice; // 事前に作成・初期化されているデバイス

	//デバイスの取得
	pDevice = GetDevice();

	// 霧の無効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

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


	//タイムの終了処理
	UninitTime();


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


	// タスクUIの終了処理
	UninitTask();


	//ミニゲームの終了処理
	UninitShootingGame();
	UninitCraneGame();
	UninitBallGame();
	UninitPasswordGame();
}
//=========================================
//ゲーム画面の更新処理
//=========================================
void UpdateGame(void)
{
	bool bFog = GetFog();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 霧の設定
	SetupVertexFog(pDevice, D3DCOLOR_XRGB(0, 0, 0), D3DFOG_LINEAR, TRUE, 0.0f);

	// 霧の無効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, bFog);

	//int nTime = GetTime();
	bool bExit = GetExit();
	STGSTATE pStgState = GetShootingGameState();
	CRANEGAMESTATE pCraneState = GetCraneGameState();
	BALLGAMESTATE pBallState = GetBallGameState();
	PASSWORDGAMESTATE pPassState = GetPasswordGameState();
	Player* pPlayer = GetPlayer();//プレイヤーの情報へのポインタにプレイヤーの先頭アドレスが代入される
	bool bArcade = GetArcade();
	bool bCatcher = GetCatcher();
	bool bBall = GetBall();
	bool bFuseCmp = GetFuseCmp();
	bool bKeypad = GetKeypad();

	bool bEnd = GetEnd();

	// ミニゲーム中はポーズを開けないようにする
	if (g_Game.bMini == false && g_Game.bMap == false && (KeyboardTrigger(DIK_P) == true || JoyPadTrigger(JOYKEY_START) == true))
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
		if (KeyboardTrigger(DIK_E) == true && 
			pStgState != STGSTATE_END && 
			bArcade == true && 
			g_Game.bMap == false &&
			bFuseCmp == true)
		{
			g_Game.bDraw = g_Game.bDraw ? false : true;
			g_Game.bMini = g_Game.bMini ? false : true;
		}

		// ミニゲーム（アクション）のトリガー
		if (KeyboardTrigger(DIK_E) == true &&
			pCraneState != CRANEGAMESTATE_END &&
			bCatcher == true && 
			g_Game.bMap == false &&
			bFuseCmp == true)
		{
			g_Game.bDraw2 = g_Game.bDraw2 ? false : true;
			g_Game.bMini = g_Game.bMini ? false : true;
		}

		// ボールプールのトリガー
		if (KeyboardTrigger(DIK_E) == true && 
			pBallState != BALLGAMESTATE_END && 
			bBall == true && 
			g_Game.bMap == false &&
			bFuseCmp == true)
		{
			g_Game.bDraw3 = g_Game.bDraw3 ? false : true;
			g_Game.bMini = g_Game.bMini ? false : true;
		}

		// キーパッドのトリガー
		if (KeyboardTrigger(DIK_E) == true/* && 
			pPassState != PASSWORDGAMESTATE_END &&
			bKeypad == true && 
			g_Game.bMap == false &&
			bFuseCmp == true &&
			g_Game.bSTClear == true && g_Game.bACClear == true && g_Game.bBallClear == true*/)
		{
			g_Game.bDraw4 = g_Game.bDraw4 ? false : true;
			g_Game.bMini = g_Game.bMini ? false : true;
		}


		// マップを開けるのはミニゲームがどちらも動いていない場合のみ
		if (g_Game.bMini == false && g_Game.bDraw == false && g_Game.bDraw2 == false && 
			g_Game.bDraw3 == false && g_Game.bDraw4 == false &&
			(KeyboardTrigger(DIK_C) == true || JoyPadTrigger(JOYKEY_BACK) == true))
		{
			g_Game.bMap = g_Game.bMap ? false : true;
		}


		// シューティングゲーム終了時の処理
		if (pStgState == STGSTATE_END)
		{
			if (g_Game.nStgCnt <= 120)
			{
				g_Game.nStgCnt++;
			}

			// 120(2秒)経ったら
			if (g_Game.nStgCnt >= 120)
			{
				g_Game.bDraw = false;
				g_Game.bSTClear = true;
				if (g_Game.bDraw2 == false &&
					g_Game.bDraw3 == false &&
					g_Game.bDraw4 == false) // 他のゲームがクリア済みなら
				{
					g_Game.bMini = false; // ミニゲーム全体を終了
				}
			}
		}

		// クレーンゲーム終了時の処理
		if (pCraneState == CRANEGAMESTATE_END)
		{
			if (g_Game.nCraneCnt <= 120)
			{
				g_Game.nCraneCnt++;
			}

			// 120(2秒)経ったら
			if (g_Game.nCraneCnt >= 120)
			{
				g_Game.bDraw2 = false;
				g_Game.bACClear = true;
				if (g_Game.bDraw == false &&
					g_Game.bDraw3 == false &&
					g_Game.bDraw4 == false) // シューティングゲームが動いていないなら
				{
					g_Game.bMini = false; // ミニゲーム全体を終了
				}
			}
		}

		// ボールプール終了時の処理
		if (pBallState == BALLGAMESTATE_END)
		{
			if (g_Game.nBallCnt <= 120)
			{
				g_Game.nBallCnt++;
			}

			// 120(2秒)経ったら
			if (g_Game.nBallCnt >= 120)
			{
				g_Game.bDraw3 = false;
				g_Game.bBallClear = true;
				if (g_Game.bDraw == false &&
					g_Game.bDraw2 == false &&
					g_Game.bDraw4 == false) // シューティングゲームが動いていないなら
				{
					g_Game.bMini = false; // ミニゲーム全体を終了
				}
			}
		}

		// キーパッド終了時の処理
		if (pPassState == PASSWORDGAMESTATE_END)
		{
			if (g_Game.nPassCnt <= 120)
			{
				g_Game.nPassCnt++;
			}

			// 120(2秒)経ったら
			if (g_Game.nPassCnt >= 60)
			{
				g_Game.bDraw4 = false;
				g_Game.bPassClear = true;
				if (g_Game.bDraw == false &&
					g_Game.bDraw2 == false &&
					g_Game.bDraw3 == false) // シューティングゲームが動いていないなら
				{
					g_Game.bMini = false; // ミニゲーム全体を終了
				}
			}
		}


		// カーソルを非表示する
		SetCursorVisibility(false);


		if (g_Game.bDraw == false && g_Game.bDraw2 == false && g_Game.bDraw3 == false)
		{
			//プレイヤーの更新処理
			UpdatePlayer();

		}
		if (g_Game.bDraw == true)
		{
			//ミニゲーム(シューティング)の更新処理
			UpdateShootingGame();
		}
		if (g_Game.bDraw2 == true)
		{
			//ミニゲーム(アクション)の更新処理
			UpdateCraneGame();
		}
		if (g_Game.bDraw3 == true)
		{
			//ボールプールの更新処理
			UpdateBallGame();

			// カーソルを表示する
			SetCursorVisibility(true);
		}
		if (g_Game.bDraw4 == true)
		{
			//キーパッドの更新処理
			UpdatePasswordGame();

			// カーソルを表示する
			SetCursorVisibility(true);
		}


		//敵の更新処理
		UpdateEnemy();


		//メッシュフィールドの更新処理
		UpdateMeshfield();


		//メッシュシーリングの更新処理
		UpdateMeshCeiling();


		//メッシュシリンダーの更新処理
		UpdateMeshcylinder();

		if (g_Game.bDraw == false && g_Game.bDraw2 == false && g_Game.bDraw3 == false && g_Game.bDraw4 == false)
		{
			//カメラの更新処理
			UpdateCamera();
		}


		//ライトの更新処理
		UpdateLight(0, D3DXVECTOR3(0.0f, 5.0f, -400.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f));


		//ブロックの更新処理
		UpdateBlock();


		//影の更新処理
		UpdateShadow();


		////ビルボードの更新処理
		//UpdateBillboard();


		////エフェクトの更新処理
		//UpdateEffect();


		//タイムの更新処理
		UpdateTime();


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

		// タスクUIの更新処理
		UpdateTask();

		// マップの更新処理
		UpdateMap();
	}


	if ((pPlayer->bDisp == false || bExit == true || bEnd  == true) && g_gameState != GAMESTATE_NONE)
	{
		//モード設定(リザルト画面に移行)
 		g_gameState = GAMESTATE_END;
		g_Game.bDraw = false;
		g_Game.bDraw2 = false;
		g_Game.bDraw3 = false;
		g_Game.bDraw4 = false;
		g_Game.bMap = false;
	}

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
	LPDIRECT3DDEVICE9 pDevice; // 事前に作成・初期化されているデバイス

	//デバイスの取得
	pDevice = GetDevice();

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


	//ブロックの描画処理
	DrawBlock();


	//メッシュシリンダーの描画処理
	DrawMeshcylinder();


	// 霧の無効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);


	////エフェクトの描画処理
	//DrawEffect();


	////パーティクルの描画処理
	//DrawParticle();


	////ビルボードの描画処理
	//DrawBillboard();


	if (pPlayer->bDrawDush == true)
	{
		//ゲージの描画処理
		DrawGuage();
	}

	if (g_Game.bMini == false)
	{
		// タスクUIの描画処理
		DrawTask();

		//UIの描画処理
		DrawUI();
	}

#ifdef _DEBUG

	//タイムの描画処理
	DrawTime();

#endif

	//影の描画処理
	DrawShadow();

	if (g_Game.bMap == true && g_Game.bMini == false)
	{//マップの描画
		DrawMap();
	}
	if (g_bPause == true)
	{//ポーズ中
		//ポーズの描画処理
		DrawPause();
	}

	if (g_Game.bDraw == true && g_Game.nStgCnt <= 120)
	{
		//ミニゲームの描画処理
		DrawShootingGame();
	}
	else if (g_Game.bDraw2 == true && g_Game.nCraneCnt <= 120)
	{
		DrawCraneGame();
	}
	else if (g_Game.bDraw3 == true && g_Game.nBallCnt <= 120)
	{
		DrawBallGame();
	}
	else if (g_Game.bDraw4 == true && g_Game.nPassCnt <= 120)
	{
		DrawPasswordGame();
	}

	// 霧の有効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}
//=============================================
// ゲームの状態の設定
//=============================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//============================================
// ゲーム状態の取得
//============================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
//============================================
// ゲームの取得
//============================================
GAME* GetGame(void)
{
	return &g_Game;
}
//============================================
// ポーズの有効無効設定
//============================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}