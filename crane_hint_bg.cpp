//---------------------------------------------------------
// ボールプール
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "crane_hint.h"

// グローバル
LPDIRECT3DTEXTURE9 g_pTextureCraneHint = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureCraneHint2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneHint = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneHint2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneHint3 = NULL;

// ヒントの初期化
void InitCraneHintBG(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bear.png",		// テクスチャのファイル名
		&g_pTextureCraneHint);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\画像2.png",		// テクスチャのファイル名
		&g_pTextureCraneHint2);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneHint,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneHint2,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneHint3,
		NULL);

	VERTEX_2D* pVtx;// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCraneHint->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffCraneHint->Unlock();


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCraneHint2->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//幅400.0f
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);	//高さ400.0f
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
	g_pVtxBuffCraneHint2->Unlock();


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCraneHint3->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(440.0f, 580.0f, 0.0f);//幅400.0f
	pVtx[1].pos = D3DXVECTOR3(840.0f, 580.0f, 0.0f);//高さ400.0f
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffCraneHint3->Unlock();
}
// ヒントの終了
void UninitCraneHintBG(void)
{
	// テクスチャの破棄
	if (g_pTextureCraneHint != NULL)
	{
		g_pTextureCraneHint->Release();
		g_pTextureCraneHint = NULL;
	}
	if (g_pTextureCraneHint2 != NULL)
	{
		g_pTextureCraneHint2->Release();
		g_pTextureCraneHint2 = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffCraneHint != NULL)
	{
		g_pVtxBuffCraneHint->Release();
		g_pVtxBuffCraneHint = NULL;
	}
	if (g_pVtxBuffCraneHint2 != NULL)
	{
		g_pVtxBuffCraneHint2->Release();
		g_pVtxBuffCraneHint2 = NULL;
	}
	if (g_pVtxBuffCraneHint3 != NULL)
	{
		g_pVtxBuffCraneHint3->Release();
		g_pVtxBuffCraneHint3 = NULL;
	}
}
// ヒントの更新
void UpdateCraneHintBG(void)
{

}
// ヒントの描画
void DrawCraneHintBG(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// デバイスへのポインタ

	// 背景
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffCraneHint2, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, NULL);
	// 背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
		0,									   // 描画する最初の頂点インデックス
		2);                                    // 描画するプリミティブ数

	// 熊
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffCraneHint, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureCraneHint);
	// 熊の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
		0,									   // 描画する最初の頂点インデックス
		2);                                    // 描画するプリミティブ数

	// 何か書かれている
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffCraneHint3, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureCraneHint2);
	// 背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
		0,									   // 描画する最初の頂点インデックス
		2);                                    // 描画するプリミティブ数
}