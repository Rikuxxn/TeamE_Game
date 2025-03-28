//=======================================================
// 
// クレーンゲームの背景処理 [ crane_background2.cpp ]
// Author:Yoshida Atsushi
// 
//=======================================================

// インクルードファイル
#include "crane_background2.h"

// グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureCraneBG3 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneBG3 = NULL;

// 背景の初期化処理
void InitCraneBackGround2(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// デバイスへのポインタ

	// テクスチャ(ゲーム画面)の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Clane_Board2.png",// テクスチャのファイル名
		&g_pTextureCraneBG3);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneBG3,
		NULL);

	VERTEX_2D* pVtx;// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCraneBG3->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(CLANEFIELD_LEFT - 30.0f, 0.0f, 0.0f);// 幅400.0f
	pVtx[1].pos = D3DXVECTOR3(CLANEFIELD_RIGHT + 30.0f, 0.0f, 0.0f);// 高さ150.0f
	pVtx[2].pos = D3DXVECTOR3(CLANEFIELD_LEFT - 30.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(CLANEFIELD_RIGHT + 30.0f, 720.0f, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);// (u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffCraneBG3->Unlock();
}
// 背景の終了処理
void UninitCraneBackGround2(void)
{
	// テクスチャの破棄
	if (g_pTextureCraneBG3 != NULL)
	{
		g_pTextureCraneBG3->Release();
		g_pTextureCraneBG3 = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffCraneBG3 != NULL)
	{
		g_pVtxBuffCraneBG3->Release();
		g_pVtxBuffCraneBG3 = NULL;
	}
}
// 背景の更新処理
void UpdateCraneBackGround2(void)
{

}
// 背景の描画処理
void DrawCraneBackGround2(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ
	// チュートリアル
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffCraneBG3, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureCraneBG3);

	// 背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
		0,									   // 描画する最初の頂点インデックス
		2);                                    // 描画するプリミティブ数
}