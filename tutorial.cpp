//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "ui.h"
#include "sound.h"


//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;   //頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;        //タイトル背景テクスチャのポインタ

int nCnt;

//=================================
// チュートリアル画面の初期化
//=================================
void InitTutorial(void)
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial.png",
		&g_pTextureTutorial);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	nCnt = 0;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();

}
//=================================
// チュートリアル画面の終了処理
//=================================
void UninitTutorial(void)
{

	//テクスチャの破棄
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

}
//=================================
// チュートリアル画面の更新処理
//=================================
void UpdateTutorial(void)
{
	FADE g_fade = GetFade(); // 現在の状態

	//nCnt++;

	//if (nCnt >= 120)
	//{
		if (g_fade == FADE_NONE && GetMouseButtonTrigger(0) /*|| JoyPadTrigger(JOYKEY_A)==true*/)
		{//決定キー(ENTERキー)が押された

			nCnt = 0;
			//モード設定(チュートリアル画面2に移行)
			SetFade(MODE_GAME);

			//PlaySound(SOUND_LABEL_TUTORIAL);
		}
	//}
}
//=================================
// チュートリアル画面の更新処理
//=================================
void DrawTutorial(void)
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorial);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}
