//---------------------------------------------------------
// 
// Author:Yoshida Atyushi
//---------------------------------------------------------

#include "main.h"
#include "shooting_background2.h"

// グローバル
LPDIRECT3DTEXTURE9 g_pTextureBG3 = { NULL };		// 操作画面テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG3 = NULL;		// 操作画面頂点バッファへのポインタ

// 背景の初期化処理
void InitBackGround2(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	// 操作画面テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Shooting_Board のコピー.png",	// テクスチャのファイル名
		&g_pTextureBG3);

	// 操作画面頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG3,
		NULL);

	VERTEX_2D* pVtx;// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG3->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(640.0f - BACKGROUNDTUTORIAL_WIDTH, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(640.0f + BACKGROUNDTUTORIAL_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(640.0f - BACKGROUNDTUTORIAL_WIDTH, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(640.0f + BACKGROUNDTUTORIAL_WIDTH, 720.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffBG3->Unlock();
}
// 背景の終了処理
void UninitBackGround2(void)
{
	// テクスチャの破棄
	if (g_pTextureBG3 != NULL)
	{
		g_pTextureBG3->Release();
		g_pTextureBG3 = NULL;
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffBG3 != NULL)
	{
		g_pVtxBuffBG3->Release();
		g_pVtxBuffBG3 = NULL;
	}
}
// 背景の更新処理
void UpdateBackGround2(void)
{

}
// 背景の描画処理
void DrawBackGround2(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// デバイスへのポインタ

	// 操作画面
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBG3, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBG3);
	// 描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
		0,									   // 描画する最初の頂点インデックス
		2);                                    // 描画するプリミティブ数

}