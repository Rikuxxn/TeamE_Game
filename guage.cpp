//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "guage.h"
#include "player.h"

//マクロ
#define NUM_LIFE (5)	 //ライフの種類

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureGuage = {};				  //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGuage = NULL;		  //頂点バッファへのポインタ
float g_fWidthGuage;
float g_fHeightGuage;
bool g_bLow;

void InitGuage(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	g_fWidthGuage = 200.0f;
	g_fHeightGuage = 500.0f;
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
	pVtx[1].pos = D3DXVECTOR3(g_fWidthGuage/* + 180.0f*/, g_fHeightGuage, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage/* + 200.0f*/, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_fWidthGuage/* + 180.0f*/, g_fHeightGuage/* + 200.0f*/, 0.0f);

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

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	//頂点バッファをアンロックする
	g_pVtxBuffGuage->Unlock();
}
void UninitGuage(void)
{
	//テクスチャの破棄
	if (g_pTextureGuage != NULL)
	{
		g_pTextureGuage->Release();
		g_pTextureGuage = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffGuage != NULL)
	{
		g_pVtxBuffGuage->Release();
		g_pVtxBuffGuage = NULL;
	}
}
void UpdateGuage(void)
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	Player *pPlayer = GetPlayer();
	int nLife = pPlayer->nDush;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGuage->Lock(0, 0, (void**)&pVtx, 0);

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage - 10.0f * fLife - 650.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_fWidthGuage + 20.0f, g_fHeightGuage - 10.0f * fLife - 650.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage + 650.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_fWidthGuage + 20.0f, g_fHeightGuage + 650.0f, 0.0f);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_fWidthGuage + (nLife * 2)/* + 220.0f*/, g_fHeightGuage, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage + 20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_fWidthGuage + (nLife * 2)/* + 220.0f*/, g_fHeightGuage + 20.0f, 0.0f);

	//if (pPlayer->nDush >= 160)
	//{
	//	//頂点カラーの設定
	//	pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 200);
	//	pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 200);
	//	pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 200);
	//	pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 200);
	//}

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
	pDevice->SetStreamSource(0, g_pVtxBuffGuage, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGuage->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGuage);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);									   //描画するプリミティブ数
	
	//頂点バッファをアンロックする
	g_pVtxBuffGuage->Unlock();
}