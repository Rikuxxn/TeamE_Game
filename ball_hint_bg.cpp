//---------------------------------------------------------
// ボールプール
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "ball_hint.h"

// グローバル
LPDIRECT3DTEXTURE9 g_pTextureBallHint = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBallHint2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallHint = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallHint2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallHint3 = NULL;

// ヒントの初期化
void InitBallHintBG(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ball_red.png",	// テクスチャのファイル名
		&g_pTextureBallHint);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\画像5.png",		// テクスチャのファイル名
		&g_pTextureBallHint2);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallHint,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallHint2,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallHint3,
		NULL);

	VERTEX_2D* pVtx;// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallHint->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(440.0f, 160.0f, 0.0f);// 幅400.0f
	pVtx[1].pos = D3DXVECTOR3(840.0f, 160.0f, 0.0f);// 高さ400.0f
	pVtx[2].pos = D3DXVECTOR3(440.0f, 560.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(840.0f, 560.0f, 0.0f);
	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	// 頂点バッファをアンロックする
	g_pVtxBuffBallHint->Unlock();


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallHint2->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 幅400.0f
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);	// 高さ400.0f
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	// 頂点バッファをアンロックする
	g_pVtxBuffBallHint2->Unlock();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallHint3->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(440.0f, 580.0f, 0.0f);// 幅400.0f
	pVtx[1].pos = D3DXVECTOR3(840.0f, 580.0f, 0.0f);// 高さ400.0f
	pVtx[2].pos = D3DXVECTOR3(440.0f, 630.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(840.0f, 630.0f, 0.0f);
	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);// (u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	// 頂点バッファをアンロックする
	g_pVtxBuffBallHint3->Unlock();
}
// ヒントの終了
void UninitBallHintBG(void)
{
	// テクスチャの破棄
	if (g_pTextureBallHint != NULL)
	{
		g_pTextureBallHint->Release();
		g_pTextureBallHint = NULL;
	}
	if (g_pTextureBallHint2 != NULL)
	{
		g_pTextureBallHint2->Release();
		g_pTextureBallHint2 = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffBallHint != NULL)
	{
		g_pVtxBuffBallHint->Release();
		g_pVtxBuffBallHint = NULL;
	}
	if (g_pVtxBuffBallHint2 != NULL)
	{
		g_pVtxBuffBallHint2->Release();
		g_pVtxBuffBallHint2 = NULL;
	}
	if (g_pVtxBuffBallHint3 != NULL)
	{
		g_pVtxBuffBallHint3->Release();
		g_pVtxBuffBallHint3 = NULL;
	}
}
// ヒントの更新
void UpdateBallHintBG(void)
{

}
// ヒントの描画
void DrawBallHintBG(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// デバイスへのポインタ

	// 背景
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallHint2, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, NULL);
	// 背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
		0,									   // 描画する最初の頂点インデックス
		2);                                    // 描画するプリミティブ数

	// ボール
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallHint, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBallHint);
	// 背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
		0,									   // 描画する最初の頂点インデックス
		2);                                    // 描画するプリミティブ数

	// 何か書かれている
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallHint3, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBallHint2);
	// 背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
		0,									   // 描画する最初の頂点インデックス
		2);                                    // 描画するプリミティブ数
}