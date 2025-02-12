//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "ball_background.h"

//マクロ
#define NUM_BG (2)//背景の数

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureBallBG[NUM_BG] = { NULL };	//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBallBG3 = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallBG = NULL;		//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallBG2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallBG3 = NULL;
float g_aBallPosTexU[NUM_BG];//テクスチャ座標の開始位置（U値）

//背景の初期化処理
void InitBallBackGround(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();//デバイスへのポインタ
	int nCntBG;

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ball_bg2.png",//テクスチャのファイル名
		&g_pTextureBallBG[0]);

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Mini_Ball_Tutorial.png",//テクスチャのファイル名
		&g_pTextureBallBG3);

	//
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aBallPosTexU[nCntBG] = 0.0f;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallBG,
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG;nCntBG++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(BALLFIELD_LEFT, BALLFIELD_TOP, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BALLFIELD_RIGHT, BALLFIELD_TOP, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(BALLFIELD_LEFT, BALLFIELD_UNDER, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BALLFIELD_RIGHT, BALLFIELD_UNDER, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(g_aBallPosTexU[nCntBG], 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(g_aBallPosTexU[nCntBG] + 1.0f, 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(g_aBallPosTexU[nCntBG], 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(g_aBallPosTexU[nCntBG] + 1.0f, 1.0f);//(u,v)

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBallBG->Unlock();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallBG2,
		NULL);

	VERTEX_2D* pVtx2;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallBG2->Lock(0, 0, (void**)&pVtx2, 0);

	//頂点座標の設定
	pVtx2[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx2[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx2[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx2[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	pVtx2[0].rhw = 1.0f;
	pVtx2[1].rhw = 1.0f;
	pVtx2[2].rhw = 1.0f;
	pVtx2[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx2[0].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx2[1].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx2[2].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx2[3].col = D3DCOLOR_RGBA(100, 100, 100, 100);

	//頂点バッファをアンロックする
	g_pVtxBuffBallBG2->Unlock();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallBG3,
		NULL);

	VERTEX_2D* pVtx3;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallBG3->Lock(0, 0, (void**)&pVtx3, 0);

	//頂点座標の設定
	pVtx3[0].pos = D3DXVECTOR3(1065.0f, 125.0f, 0.0f);//幅200.0f
	pVtx3[1].pos = D3DXVECTOR3(1265.0f, 125.0f, 0.0f);//高さ500.0f
	pVtx3[2].pos = D3DXVECTOR3(1065.0f, 625.0f, 0.0f);
	pVtx3[3].pos = D3DXVECTOR3(1265.0f, 625.0f, 0.0f);

	//rhwの設定
	pVtx3[0].rhw = 1.0f;
	pVtx3[1].rhw = 1.0f;
	pVtx3[2].rhw = 1.0f;
	pVtx3[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx3[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx3[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx3[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx3[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx3[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx3[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx3[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx3[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	//頂点バッファをアンロックする
	g_pVtxBuffBallBG3->Unlock();
}
//背景の終了処理
void UninitBallBackGround(void)
{
	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャの破棄
		if (g_pTextureBallBG[nCntBG] != NULL)
		{
			g_pTextureBallBG[nCntBG]->Release();
			g_pTextureBallBG[nCntBG] = NULL;
		}
	}
	//テクスチャの破棄
	if (g_pTextureBallBG3 != NULL)
	{
		g_pTextureBallBG3->Release();
		g_pTextureBallBG3 = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBallBG != NULL &&
		g_pVtxBuffBallBG2 != NULL &&
		g_pVtxBuffBallBG3 != NULL)
	{
		g_pVtxBuffBallBG->Release();
		g_pVtxBuffBallBG = NULL;
		g_pVtxBuffBallBG2->Release();
		g_pVtxBuffBallBG2 = NULL;
		g_pVtxBuffBallBG3->Release();
		g_pVtxBuffBallBG3 = NULL;
	}
}
//背景の更新処理
void UpdateBallBackGround(void)
{

}
//背景の描画処理
void DrawBallBackGround(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();//デバイスへのポインタ

	//透明
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallBG2, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数

	//チュートリアル
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallBG3, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBallBG3);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数

	//3枚目
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBallBG[0]);

		//背景の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
			0,									   //描画する最初の頂点インデックス
			2);                                    //描画するプリミティブ数
	}
}