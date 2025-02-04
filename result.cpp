//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "player.h"
//#include "sound.h"
#include "time.h"
#include "enemy.h"
#include "block.h"


//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;					//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;					//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureResultGameover = NULL;			//テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultGameover = NULL;	//頂点バッファへのポインタ

float g_fAlphaGameover = 0.0f;								// ゲームオーバー用のアルファ値
float g_fAlphaTime = 0.0f;									// タイム用のアルファ値
float g_fAlphaRank = 0.0f;									// ランク用のアルファ値

int g_nRankCnt = 0;
int g_nTimeCnt = 0;


LPDIRECT3DTEXTURE9 g_pTextureResultTimeMinute = NULL;		//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureResultTimeSecond = NULL;		//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureResultColon = NULL;			//テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultTimeMinute = NULL;	//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultTimeSecond = NULL;	//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultColon = NULL;		//頂点バッファへのポインタ


D3DXVECTOR3 g_posResultTime;//タイムの位置
Time g_aResultTime[MAX_RESULT_TIMEDIGIT];

int g_nResultMinutes;		// 分
int g_nResultSeconds;		// 秒

//================================================
//リザルト画面の初期化処理
//================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

<<<<<<< HEAD
	g_fAlphaGameover = 0.0f;		// フェードアルファ値をリセット
	g_fAlphaRank = 0.0f;			// フェードアルファ値をリセット
=======

	g_fAlphaGameover = 0.0f;		// フェードアルファ値をリセット
	g_fAlphaGameover = 0.0f;	// フェードアルファ値をリセット
	g_fAlphaTime = 0.0f;		// フェードアルファ値をリセット
	g_fAlphaRank = 0.0f;		// フェードアルファ値をリセット
>>>>>>> 3a86f006f54aff85320f4cf4156d77e82acf56c4
	g_nRankCnt = 0;

	Player* pPlayer = GetPlayer();	//プレイヤーの情報へのポインタ

	bool bEnd = GetEnd();
	bool bExit = GetExit();
	int nTimeMinutes = GetTimeMinutes();
	int nTimeSeconds = GetTimeSeconds();

	if (bExit == true)
	{//脱出したら

		////リザルト(ゲームクリア)画面に遷移
		//PlaySound(SOUND_LABEL_SCORE);

		//テクスチャの読み込み(背景)
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\resultBG.png",
			&g_pTextureResult);

		// 2分切ったら
		if (nTimeMinutes < 2 && nTimeSeconds >= 0)
		{// ランクA

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\rankA.png",
				&g_pTextureRank);

		}
		// 2分以上3分未満
		else if (nTimeMinutes >= 2 && nTimeMinutes < 3 && nTimeSeconds >= 0 && nTimeSeconds <= 59)
		{// ランクB

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\rankB.png",
				&g_pTextureRank);

		}
		// 3分以上
		else if (nTimeMinutes >= 3 && nTimeSeconds >= 0)
		{// ランクC

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\rankC.png",
				&g_pTextureRank);

		}

	}
	else if (bEnd == true)
	{//捕まったらまたはタイムが0になったら

		////リザルト(ゲームオーバー)画面に遷移
		//PlaySound(SOUND_LABEL_GAMEOVER);

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\wall001.jpg",
			&g_pTextureResult);


		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\gameover.png",
			&g_pTextureResultGameover);

	}
	

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultGameover,
		NULL);


	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(200,200,200,255);
	pVtx[1].col = D3DCOLOR_RGBA(200,200,200,255);
	pVtx[2].col = D3DCOLOR_RGBA(200,200,200,255);
	pVtx[3].col = D3DCOLOR_RGBA(200,200,200,255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(500.0f, 640.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(630.0f, 640.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(500.0f, 710.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(630.0f, 710.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffRank->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultGameover->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(320.0f, 300.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(960.0f, 300.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(320.0f, 470.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(960.0f, 470.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffResultGameover->Unlock();

}
//=====================================================
//リザルト画面の終了処理
//=====================================================
void UninitResult(void)
{

	////サウンドの停止
	//StopSound(SOUND_LABEL_CLEAR);
	//StopSound(SOUND_LABEL_GAMEOVER);
	//StopSound(SOUND_LABEL_RANK);

	//テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureResultGameover != NULL)
	{
		g_pTextureResultGameover->Release();
		g_pTextureResultGameover = NULL;
	}



	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResultGameover != NULL)
	{
		g_pVtxBuffResultGameover->Release();
		g_pVtxBuffResultGameover = NULL;
	}

}
//=====================================================
//リザルト画面の更新処理
//=====================================================
void UpdateResult(void)
{
	FADE g_fade = GetFade(); // 現在の状態

	bool bExit = GetExit();
	//nTime = GetTime();

	Player* pPlayer = GetPlayer();

	g_nRankCnt++;

	// ランク表示フェード
	if (g_nRankCnt >= 210)
	{
		if (g_fAlphaRank < 255.0f)
		{
			g_fAlphaRank += 2.0f; // フェード速度調整

			if (g_fAlphaRank > 255.0f)
			{
				g_fAlphaRank = 255.0f;
			}
		}
	}
	if (g_nRankCnt <= 210 && bExit == true)
	{
		//PlaySound(SOUND_LABEL_RANK);
	}

	// ゲームオーバーテキストのフェード
	if (g_nRankCnt >= 30)
	{
		if (g_fAlphaGameover < 255.0f)
		{
			g_fAlphaGameover += 5.0f; // フェード速度調整

			if (g_fAlphaGameover > 255.0f)
			{
				g_fAlphaGameover = 255.0f;
			}
		}
	}
	

	if (g_nRankCnt >= 180)
	{
		if (pPlayer->bDisp == true && bExit == true &&
			(g_fade == FADE_NONE && GetMouseButtonTrigger(0) /*|| JoyPadTrigger(JOYKEY_A) == true)*/))
		{//決定キー(ENTERキー)が押された

			//モード設定(タイトル画面に移行)
			SetFade(MODE_TITLE);

		}
		else if ((pPlayer->bDisp == false || bExit == false) &&
			(g_fade == FADE_NONE && GetMouseButtonTrigger(0) /*|| JoyPadTrigger(JOYKEY_A) == true)*/))
		{

			//モード設定(タイトル画面に移行)
			SetFade(MODE_TITLE);

		}
	}
}
//=====================================================
//リザルト画面の描画処理
//=====================================================
void DrawResult(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();//プレイヤーの情報へのポインタ


	bool bExit = GetExit();
	int nTimeMinutes = GetTimeMinutes();
	int nTimeSeconds = GetTimeSeconds();

	VERTEX_2D* pVtx;

	//====================================
	// 背景の描画
	//====================================

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	if (bExit == true)
	{
		//====================================
		//ランク描画
		//====================================

		if (nTimeMinutes < 2 && nTimeSeconds >= 0)
		{

			// 頂点バッファをロック
			g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

			// アルファ値を反映
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);

			// 頂点バッファをアンロック
			g_pVtxBuffRank->Unlock();

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRank);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}
		else if (nTimeMinutes >= 2 && nTimeMinutes < 3 && nTimeSeconds >= 0 && nTimeSeconds <= 59)
		{

			// 頂点バッファをロック
			g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

			// アルファ値を反映
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);

			// 頂点バッファをアンロック
			g_pVtxBuffRank->Unlock();

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRank);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}
		else if (nTimeMinutes >= 3 && nTimeSeconds >= 0)
		{

			// 頂点バッファをロック
			g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

			// アルファ値を反映
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);

			// 頂点バッファをアンロック
			g_pVtxBuffRank->Unlock();

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRank);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}

	}

	if (bExit == false)
	{
		// 頂点バッファをロック
		g_pVtxBuffResultGameover->Lock(0, 0, (void**)&pVtx, 0);

		// アルファ値を反映
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaGameover);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaGameover);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaGameover);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaGameover);

		// 頂点バッファをアンロック
		g_pVtxBuffResultGameover->Unlock();

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffResultGameover, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResultGameover);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

}
//=============================
// リザルトタイムの初期化処理
//=============================
void InitResultTime(void)
{

	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み(分)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&g_pTextureResultTimeMinute);

	//テクスチャの読み込み(秒)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&g_pTextureResultTimeSecond);

	//テクスチャの読み込み(コロン)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\colon.png",
		&g_pTextureResultColon);

	//初期化
	g_posResultTime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置を初期化する(始まりの位置)
	g_nResultMinutes = 0;
	g_nResultSeconds = 0;

	g_fAlphaTime = 0.0f;			// フェードアルファ値をリセット
	g_nTimeCnt = 0;

	nCnt = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMEDIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultTimeMinute,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMEDIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultTimeSecond,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultColon,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultTimeMinute->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{

		g_aResultTime[nCnt].bUse = true;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(800.0f + nCnt * 70.0f, 190.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f + nCnt * 70.0f + 80.0f, 190.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(800.0f + nCnt * 70.0f, 280.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f + nCnt * 70.0f + 80.0f, 280.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResultTimeMinute->Unlock();

	// コロンの頂点バッファをロック
	g_pVtxBuffResultColon->Lock(0, 0, (void**)&pVtx, 0);

<<<<<<< HEAD
	float colonX = 970.0f;	// コロンのX座標
	float colonY = 190.0f;	// コロンのY座標
=======
	//float colonX = 920.0f;	// コロンのX座標
	//float colonY = 150.0f;	// コロンのY座標
	float colonX = 960.0f; // コロンのX座標
	float colonY = 190.0f;  // コロンのY座標
>>>>>>> 3a86f006f54aff85320f4cf4156d77e82acf56c4

	// コロンの頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(colonX, colonY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(colonX + 40.0f, colonY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(colonX, colonY + 90.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(colonX + 40.0f, colonY + 90.0f, 0.0f);

	for (int nCntColon = 0; nCntColon < 4; nCntColon++)
	{
		pVtx[nCntColon].rhw = 1.0f;
		pVtx[nCntColon].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	// コロンのテクスチャ座標設定（1枚の画像の場合は固定）
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffResultColon->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultTimeSecond->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{

		g_aResultTime[nCnt].bUse = true;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(1020.0f + nCnt * 70.0f, 190.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1020.0f + nCnt * 70.0f + 80.0f, 190.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1020.0f + nCnt * 70.0f, 280.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1020.0f + nCnt * 70.0f + 80.0f, 280.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResultTimeSecond->Unlock();

}
//=============================
// リザルトタイムの終了処理
//=============================
void UninitResultTime(void)
{

	//テクスチャの破棄(分)
	if (g_pTextureResultTimeMinute != NULL)
	{
		g_pTextureResultTimeMinute->Release();
		g_pTextureResultTimeMinute = NULL;
	}

	//テクスチャの破棄(秒)
	if (g_pTextureResultTimeSecond != NULL)
	{
		g_pTextureResultTimeSecond->Release();
		g_pTextureResultTimeSecond = NULL;
	}

	//テクスチャの破棄(コロン)
	if (g_pTextureResultColon != NULL)
	{
		g_pTextureResultColon->Release();
		g_pTextureResultColon = NULL;
	}

	//頂点バッファの破棄(分)
	if (g_pVtxBuffResultTimeMinute != NULL)
	{
		g_pVtxBuffResultTimeMinute->Release();
		g_pVtxBuffResultTimeMinute = NULL;
	}

	//頂点バッファの破棄(秒)
	if (g_pVtxBuffResultTimeSecond != NULL)
	{
		g_pVtxBuffResultTimeSecond->Release();
		g_pVtxBuffResultTimeSecond = NULL;
	}

	//頂点バッファの破棄(コロン)
	if (g_pVtxBuffResultColon != NULL)
	{
		g_pVtxBuffResultColon->Release();
		g_pVtxBuffResultColon = NULL;
	}

}
//=============================
// リザルトタイムの更新処理
//=============================
void UpdateResultTime(void)
{
	g_nTimeCnt++;

	if (g_nTimeCnt >= 120)
	{
		if (g_fAlphaTime < 255.0f)
		{
			g_fAlphaTime += 2.0f; // フェード速度調整

			if (g_fAlphaTime > 255.0f)
			{
				g_fAlphaTime = 255.0f;
			}
		}
	}

	int nMinutes = GetTimeMinutes();
	int nSeconds = GetTimeSeconds();

	VERTEX_2D* pVtx;

	g_nResultMinutes = nMinutes;
	g_nResultSeconds = nSeconds;

	int min10 = g_nResultMinutes / 10;	// 分の10の位
	int min1 = g_nResultMinutes % 10;	// 分の1の位
	int sec10 = g_nResultSeconds / 10;	// 秒の10の位
	int sec1 = g_nResultSeconds % 10;	// 秒の1の位

	float texOffset = 0.1f;				// 1桁分のテクスチャ範囲（0.0～1.0を10分割）

	//===============================
	// 分のテクスチャ設定
	//===============================

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultTimeMinute->Lock(0, 0, (void**)&pVtx, 0);

	// 分の10の位
	pVtx[0].tex = D3DXVECTOR2(texOffset * min10, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texOffset * min10 + texOffset, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(texOffset * min10, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(texOffset * min10 + texOffset, 1.0f);

	// 分の1の位
	pVtx[4].tex = D3DXVECTOR2(texOffset * min1, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(texOffset * min1 + texOffset, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(texOffset * min1, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(texOffset * min1 + texOffset, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffResultTimeMinute->Unlock();

	//===============================
	// 秒のテクスチャ設定
	//===============================

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultTimeSecond->Lock(0, 0, (void**)&pVtx, 0);

	// 秒の10の位
	pVtx[0].tex = D3DXVECTOR2(texOffset * sec10, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texOffset * sec10 + texOffset, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(texOffset * sec10, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(texOffset * sec10 + texOffset, 1.0f);

	// 秒の1の位
	pVtx[4].tex = D3DXVECTOR2(texOffset * sec1, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(texOffset * sec1 + texOffset, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(texOffset * sec1, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(texOffset * sec1 + texOffset, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffResultTimeSecond->Unlock();

}
//=============================
// リザルトタイムの描画処理
//=============================
void DrawResultTime(void)
{

	VERTEX_2D* pVtx;

	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//=================
	// 分
	//=================

	// 頂点バッファをロック
	g_pVtxBuffResultTimeMinute->Lock(0, 0, (void**)&pVtx, 0);

	// アルファ値を反映
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// 頂点バッファをアンロック
	g_pVtxBuffResultTimeMinute->Unlock();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultTimeMinute, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{
		if (g_aResultTime[nCnt].bUse == true)
		{

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureResultTimeMinute);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}

	//=================
	// コロン
	//=================

	// 頂点バッファをロック
	g_pVtxBuffResultColon->Lock(0, 0, (void**)&pVtx, 0);

	// アルファ値を反映
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// 頂点バッファをアンロック
	g_pVtxBuffResultColon->Unlock();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultColon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultColon);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//=================
	// 秒
	//=================

	// 頂点バッファをロック
	g_pVtxBuffResultTimeSecond->Lock(0, 0, (void**)&pVtx, 0);

	// アルファ値を反映
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// 頂点バッファをアンロック
	g_pVtxBuffResultTimeSecond->Unlock();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultTimeSecond, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{
		if (g_aResultTime[nCnt].bUse == true)
		{

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureResultTimeSecond);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}

}