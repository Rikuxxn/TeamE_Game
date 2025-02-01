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
//#include "score.h"
#include "time.h"
#include "time.h"
#include "enemy.h"
#include "block.h"

typedef struct
{
	bool bUse;
	float fAlpha;     // 透明度
	float fPosY;      // Y座標
	int nTimer;       // アニメーション用タイマー
}ResultScore;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;					//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureResultCrear = NULL;			//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureResultGameover = NULL;			//テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultCrear = NULL;		//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultGameover = NULL;	//頂点バッファへのポインタ

float g_fAlphaGameover = 0.0f;								// ゲームオーバー用のアルファ値
int g_nRankCnt = 0;

//================================================
//リザルト画面の初期化処理
//================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();


	g_fAlphaGameover = 0.0f;	// フェードアルファ値をリセット

	Player* pPlayer = GetPlayer();//プレイヤーの情報へのポインタ

	bool bEnd = GetEnd();
	bool bExit = GetExit();
	//nScore = GetScore();
	//nTime = GetTime();

	if (bExit == true)
	{//脱出したら

		////リザルト(ゲームクリア)画面に遷移
		//PlaySound(SOUND_LABEL_SCORE);

		//テクスチャの読み込み(背景)
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\exit.png",
			&g_pTextureResult);

	}
	else if (bEnd == true /*|| nTime == 0*/)
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
		&g_pVtxBuffResultCrear,
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
	g_pVtxBuffResultCrear->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(380.0f, 640.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(500.0f, 640.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(380.0f, 710.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(500.0f, 710.0f, 0.0f);

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
	g_pVtxBuffResultCrear->Unlock();


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
	if (g_pTextureResultCrear != NULL)
	{
		g_pTextureResultCrear->Release();
		g_pTextureResultCrear = NULL;
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
	if (g_pVtxBuffResultCrear != NULL)
	{
		g_pVtxBuffResultCrear->Release();
		g_pVtxBuffResultCrear = NULL;
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
		else if ((pPlayer->bDisp == false || bExit == false /*|| nTime <= 0*/) &&
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


	//====================================
    //お金の総額の描画
    //====================================


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