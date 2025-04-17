//=============================================================================
//
// 視界エフェクト処理 [insight.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "insight.h"
#include "enemy.h"
#include "block.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureInsight = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffInsight = NULL;		// 頂点バッファへのポインタ
Insight g_aInsight;

const float ALPHA_INCREMENT = 0.05f; // アルファ値の増減量
const float MAX_ALPHA = 0.7f;        // 最大アルファ値
const float MIN_ALPHA = 0.0f;        // 最小アルファ値
float InsightAlpha = 0.0f;

//=========================================================
// 視界エフェクトの初期化処理
//=========================================================
void InitInsight(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み(分)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\insight.png",
		&g_pTextureInsight);

	// 初期化
	g_aInsight.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aInsight.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aInsight.fWidth = 0.0f;
	g_aInsight.fHeight = 0.0f;
	g_aInsight.bUse = false;
	g_aInsight.nCounter = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffInsight,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffInsight->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffInsight->Unlock();

}
//=========================================================
// 視界エフェクトの終了処理
//=========================================================
void UninitInsight(void)
{
	//テクスチャの破棄
	if (g_pTextureInsight != NULL)
	{
		g_pTextureInsight->Release();
		g_pTextureInsight = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffInsight != NULL)
	{
		g_pVtxBuffInsight->Release();
		g_pVtxBuffInsight = NULL;
	}
}
//=========================================================
// 視界エフェクトの更新処理
//=========================================================
void UpdateInsight(void)
{
	Flags* pFlag = GetFlag();

	if (isPlayerInSight() && pFlag->bFuseCmp)  // プレイヤーが視界内にいる
	{
		// 徐々に透明度を上げる
		InsightAlpha += ALPHA_INCREMENT;
		if (InsightAlpha > MAX_ALPHA) InsightAlpha = MAX_ALPHA;
	}
	else  // プレイヤーが視界外
	{
		// 徐々に透明度を下げる
		InsightAlpha -= ALPHA_INCREMENT;
		if (InsightAlpha < MIN_ALPHA) InsightAlpha = MIN_ALPHA;
	}

	// 頂点バッファを更新
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffInsight->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, InsightAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, InsightAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, InsightAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, InsightAlpha);

	//頂点バッファをアンロックする
	g_pVtxBuffInsight->Unlock();

}
//=========================================================
// 視界エフェクトの描画処理
//=========================================================
void DrawInsight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffInsight, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureInsight);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//===================================================
// 視界エフェクトの設定処理
//===================================================
void SetInsight(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffInsight->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aInsight.bUse == false)
	{
		g_aInsight.pos = pos;
		g_aInsight.col = col;
		g_aInsight.fWidth = fWidth;
		g_aInsight.fHeight = fHeight;
		g_aInsight.bUse = true;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aInsight.pos.x - g_aInsight.fWidth, g_aInsight.pos.y - g_aInsight.fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aInsight.pos.x + g_aInsight.fWidth, g_aInsight.pos.y - g_aInsight.fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aInsight.pos.x - g_aInsight.fWidth, g_aInsight.pos.y + g_aInsight.fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aInsight.pos.x + g_aInsight.fWidth, g_aInsight.pos.y + g_aInsight.fHeight, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	}

	// 頂点バッファをアンロックする
	g_pVtxBuffInsight->Unlock();

}
//===================================================
// 視界エフェクト情報の取得
//===================================================
Insight* GetInsight(void)
{
	return &g_aInsight;
}