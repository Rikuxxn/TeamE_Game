//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "guage.h"
#include "player.h"
#include "sound.h"

//マクロ
#define NUM_LIFE (5)	 //ライフの種類

//グローバル
//LPDIRECT3DTEXTURE9 g_pTextureGuage = {};				  //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGuage = NULL;		  //頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGuage2 = NULL;
float g_fWidthGuage;
float g_fHeightGuage;
bool g_bLow;

void InitGuage(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	g_fWidthGuage = 470.0f;
	g_fHeightGuage = 650.0f;
	g_bLow = false;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGuage,
		NULL);
	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGuage->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 255);

	//頂点バッファをアンロックする
	g_pVtxBuffGuage->Unlock();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGuage2,
		NULL);
	VERTEX_2D* pVtx2;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGuage2->Lock(0, 0, (void**)&pVtx2, 0);

	//頂点座標の設定
	pVtx2[0].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);
	pVtx2[1].pos = D3DXVECTOR3(g_fWidthGuage + (PLAYER_STAMINA * 1.5f), g_fHeightGuage, 0.0f);
	pVtx2[2].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage + 13.0f, 0.0f);
	pVtx2[3].pos = D3DXVECTOR3(g_fWidthGuage + (PLAYER_STAMINA * 1.5f), g_fHeightGuage + 13.0f, 0.0f);

	//rhwの設定
	pVtx2[0].rhw = 1.0f;
	pVtx2[1].rhw = 1.0f;
	pVtx2[2].rhw = 1.0f;
	pVtx2[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx2[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx2[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx2[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx2[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);

	//頂点バッファをアンロックする
	g_pVtxBuffGuage2->Unlock();
}
void UninitGuage(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffGuage != NULL)
	{
		g_pVtxBuffGuage->Release();
		g_pVtxBuffGuage = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGuage2 != NULL)
	{
		g_pVtxBuffGuage2->Release();
		g_pVtxBuffGuage2 = NULL;
	}
}
void UpdateGuage(void)
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	Player *pPlayer = GetPlayer();
	float fLife = pPlayer->fDush;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGuage->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_fWidthGuage + (fLife * 1.5f), g_fHeightGuage, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage + 13.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_fWidthGuage + (fLife * 1.5f), g_fHeightGuage + 13.0f, 0.0f);

	if (pPlayer->fDush <= 90)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	else if (pPlayer->fDush >= 90 && pPlayer->bEmpty == false)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGuage->Unlock();
}
void DrawGuage(void)
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffGuage2, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGuage2->Lock(0, 0, (void**)&pVtx, 0);

	////テクスチャの設定
	//pDevice->SetTexture(0, g_pTextureGuage);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);									   //描画するプリミティブ数

	//頂点バッファをアンロックする
	g_pVtxBuffGuage2->Unlock();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffGuage, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGuage->Lock(0, 0, (void**)&pVtx, 0);

	////テクスチャの設定
	//pDevice->SetTexture(0, g_pTextureGuage);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);									   //描画するプリミティブ数
	
	//頂点バッファをアンロックする
	g_pVtxBuffGuage->Unlock();
}