//=======================================
//
// 推奨画面処理[recommendation.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "recommendation.h"
#include "fade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRecommend = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRecommend = NULL;		// 頂点バッファへのポインタ

int g_fadeCount;	// フェードカウント

//================================================
// 推奨画面の初期化処理
//================================================
void InitRecommendation(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\recommendation.png",
		&g_pTextureRecommend);

	g_fadeCount = 0;//初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRecommend,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRecommend->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffRecommend->Unlock();

}
//=====================================================
// 推奨画面の終了処理
//=====================================================
void UninitRecommendation(void)
{
	//テクスチャの破棄
	if (g_pTextureRecommend != NULL)
	{
		g_pTextureRecommend->Release();
		g_pTextureRecommend = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRecommend != NULL)
	{
		g_pVtxBuffRecommend->Release();
		g_pVtxBuffRecommend = NULL;
	}
}
//=====================================================
// 推奨画面の更新処理
//=====================================================
void UpdateRecommendation(void)
{
	GetFade();//フェードの取得

	FADE g_fade = GetFade();//現在の状態

	g_fadeCount++;		// カウント加算

	if (g_fadeCount >= 180)
	{
		//時間経過
		SetFade(MODE_TITLE);
	}
}
//=====================================================
// 推奨画面の描画処理
//=====================================================
void DrawRecommendation(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRecommend, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRecommend);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

