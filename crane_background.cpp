//=======================================================
// 
// クレーンゲームの背景処理 [ crane_background.cpp ]
// Author:Yoshida Atsushi
// 
//=======================================================

// インクルードファイル
#include "crane_background.h"

// マクロ定義
#define NUM_BG (2)// 背景の数

// グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureCraneBG[NUM_BG] = { NULL };// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureCraneBG3 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneBG = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneBG2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneBG3 = NULL;
float g_aPosCraneTexU[NUM_BG];							// テクスチャ座標の開始位置（U値）

// 背景の初期化処理
void InitCraneBackGround(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();// デバイスへのポインタ
	int nCntBG;

	// テクスチャ(ゲーム画面)の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Clane_Back.jpg",// テクスチャのファイル名
		&g_pTextureCraneBG[0]);

	// テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Clane_Board.jpg",// テクスチャのファイル名
		&g_pTextureCraneBG3);

	//
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosCraneTexU[nCntBG] = 0.0f;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneBG,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneBG2,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneBG3,
		NULL);

	VERTEX_2D* pVtx;// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCraneBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG;nCntBG++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(CLANEFIELD_LEFT, CLANEFIELD_TOP, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(CLANEFIELD_RIGHT, CLANEFIELD_TOP, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(CLANEFIELD_LEFT, CLANEFIELD_UNDER, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(CLANEFIELD_RIGHT, CLANEFIELD_UNDER, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(g_aPosCraneTexU[nCntBG], 0.0f);// (u,v)
		pVtx[1].tex = D3DXVECTOR2(g_aPosCraneTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosCraneTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosCraneTexU[nCntBG] + 1.0f, 1.0f);

		pVtx += 4;// 頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffCraneBG->Unlock();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCraneBG2->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 150);

	// 頂点バッファをアンロックする
	g_pVtxBuffCraneBG2->Unlock();

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
void UninitCraneBackGround(void)
{
	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		// テクスチャの破棄
		if (g_pTextureCraneBG[nCntBG] != NULL)
		{
			g_pTextureCraneBG[nCntBG]->Release();
			g_pTextureCraneBG[nCntBG] = NULL;
		}
	}
	if (g_pTextureCraneBG3 != NULL)
	{
		g_pTextureCraneBG3->Release();
		g_pTextureCraneBG3 = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffCraneBG != NULL)
	{
		g_pVtxBuffCraneBG->Release();
		g_pVtxBuffCraneBG = NULL;
	}
	if (g_pVtxBuffCraneBG2 != NULL)
	{
		g_pVtxBuffCraneBG2->Release();
		g_pVtxBuffCraneBG2 = NULL;
	}
	if (g_pVtxBuffCraneBG3 != NULL)
	{
		g_pVtxBuffCraneBG3->Release();
		g_pVtxBuffCraneBG3 = NULL;
	}
}
// 背景の更新処理
void UpdateCraneBackGround(void)
{

}
// 背景の描画処理
void DrawCraneBackGround(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	// 半透明
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffCraneBG2, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// 背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
		0,									   // 描画する最初の頂点インデックス
		2);                                    // 描画するプリミティブ数

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

	// 3枚目
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffCraneBG, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureCraneBG[0]);

		// 背景の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
			0,									   // 描画する最初の頂点インデックス
			2);                                    // 描画するプリミティブ数
	}
}