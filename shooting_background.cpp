//---------------------------------------------------------
// 
// Author:Yoshida Atyushi
//---------------------------------------------------------

#include "main.h"
#include "shooting_player.h"

//マクロ
#define NUM_BG (3)//背景の数

//グローバル
<<<<<<< HEAD
LPDIRECT3DTEXTURE9 g_pTextureBG[NUM_BG] = { NULL };	//テクスチャへのポインタ
//LPDIRECT3DTEXTURE9 g_pTextureBG = { NULL };		//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBG4 = { NULL };
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG3 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG4 = NULL;
=======
LPDIRECT3DTEXTURE9 g_pTextureBG = { NULL };		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBG2 = { NULL };
LPDIRECT3DTEXTURE9 g_pTextureBG3 = { NULL };
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;	// 背景頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG2 = NULL;	// 薄暗い背景
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG3 = NULL;	// チュートリアル

>>>>>>> 7fd670f0b80d135596a51d0b229c4c4209f68d37
float g_aPosTexU[NUM_BG];//テクスチャ座標の開始位置（U値）

//背景の初期化処理
void InitBackGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

<<<<<<< HEAD
	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg100.png",						//テクスチャのファイル名
		&g_pTextureBG[0]);
	//テクスチャ2の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg101.png",						//テクスチャのファイル名
		&g_pTextureBG[1]);
	//テクスチャ3の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg102.png",						//テクスチャのファイル名
		&g_pTextureBG[2]);
		//テクスチャ1の読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\space_bg.png",						//テクスチャのファイル名
	//	&g_pTextureBG);
	//チュートリアルテクスチャの読み込み
=======
	// 背景テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\space_bg.png",						//テクスチャのファイル名
		&g_pTextureBG);

	// 薄暗い背景テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\.png",						//テクスチャのファイル名
		&g_pTextureBG2);

	// チュートリアルテクスチャの読み込み
>>>>>>> 7fd670f0b80d135596a51d0b229c4c4209f68d37
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Mini_Shooting_Tutorial.png",	//テクスチャのファイル名
		&g_pTextureBG3);

	//
	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] = 0.0f;
	}

	//頂点バッファの生成
<<<<<<< HEAD
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);
	VERTEX_2D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBG = 0; nCntBG < NUM_BG;nCntBG++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(360.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(920.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(360.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(920.0f, 720.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);
		pVtx += 4;//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();


	//頂点バッファの生成
=======
>>>>>>> 7fd670f0b80d135596a51d0b229c4c4209f68d37
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG2,
		NULL);
<<<<<<< HEAD
	VERTEX_2D* pVtx2;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG2->Lock(0, 0, (void**)&pVtx2, 0);
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
	pVtx2[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);
	pVtx2[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);
	pVtx2[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);
	pVtx2[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);
	//頂点バッファをアンロックする
	g_pVtxBuffBG2->Unlock();
=======
>>>>>>> 7fd670f0b80d135596a51d0b229c4c4209f68d37

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG3,
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG2->Lock(0, 0, (void**)&pVtx, 0);

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
<<<<<<< HEAD
	pVtx3[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx3[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx3[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx3[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
=======
	pVtx[0].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	pVtx[1].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	pVtx[2].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	pVtx[3].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);

	//頂点バッファをアンロックする
	g_pVtxBuffBG2->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < NUM_BG;nCntBG++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(360.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(920.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(360.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(920.0f, 720.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG3->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(950.0f, 200.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1200.0f, 200.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(950.0f, 600.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1200.0f, 600.0f, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

>>>>>>> 7fd670f0b80d135596a51d0b229c4c4209f68d37
	//頂点バッファをアンロックする
	g_pVtxBuffBG3->Unlock();
}
//背景の終了処理
void UninitBackGround(void)
{
<<<<<<< HEAD
	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
=======
	//for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	//{
	//	//テクスチャの破棄
	//	if (g_pTextureBG[nCntBG] != NULL)
	//	{
	//		g_pTextureBG[nCntBG]->Release();
	//		g_pTextureBG[nCntBG] = NULL;
	//	}
	//}

	if (g_pTextureBG != NULL)
>>>>>>> 7fd670f0b80d135596a51d0b229c4c4209f68d37
	{
		//テクスチャの破棄
		if (g_pTextureBG[nCntBG] != NULL)
		{
			g_pTextureBG[nCntBG]->Release();
			g_pTextureBG[nCntBG] = NULL;
		}
	}
<<<<<<< HEAD
	//if (g_pTextureBG != NULL)
	//{
	//	g_pTextureBG->Release();
	//	g_pTextureBG = NULL;
	//}
	if (g_pTextureBG4 != NULL)
=======
	if (g_pTextureBG2 != NULL)
>>>>>>> 7fd670f0b80d135596a51d0b229c4c4209f68d37
	{
		g_pTextureBG2->Release();
		g_pTextureBG2 = NULL;
	}
	if (g_pTextureBG3 != NULL)
	{
		g_pTextureBG3->Release();
		g_pTextureBG3 = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
	if (g_pVtxBuffBG2 != NULL)
	{
		g_pVtxBuffBG2->Release();
		g_pVtxBuffBG2 = NULL;
	}
	if (g_pVtxBuffBG3 != NULL)
	{
		g_pVtxBuffBG3->Release();
		g_pVtxBuffBG3 = NULL;
	}

}
//背景の更新処理
void UpdateBackGround(void)
{
	VERTEX_2D* pVtx=0;//頂点情報へのポインタ
	int nCntBG;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] += 0.007f;

		//テクスチャ座標の設定(縦)
		pVtx[0].tex = D3DXVECTOR2(0.0f, g_aPosTexU[nCntBG] + 1.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(1.0f, g_aPosTexU[nCntBG] + 1.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, g_aPosTexU[nCntBG]);
		pVtx[3].tex = D3DXVECTOR2(1.0f, g_aPosTexU[nCntBG]);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}
//背景の描画処理
void DrawBackGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//やや透明
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBG2, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
<<<<<<< HEAD
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
	//描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数


	//背景
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBG3, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
	//描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数


	//チュートリアル
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBG4, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
=======
>>>>>>> 7fd670f0b80d135596a51d0b229c4c4209f68d37
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
	//描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数


		//背景
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
<<<<<<< HEAD
	////テクスチャの設定
	//pDevice->SetTexture(0, g_pTextureBG);
	////背景の描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	0,									   //描画する最初の頂点インデックス
	//	2);                                    //描画するプリミティブ数
	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBG[0]);
		pDevice->SetTexture(0, g_pTextureBG[1]);
		pDevice->SetTexture(0, g_pTextureBG[2]);
		//背景の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
			0,									   //描画する最初の頂点インデックス
			2);                                    //描画するプリミティブ数
	}
=======
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBG);
	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数


	//チュートリアル
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBG3, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBG3);
	//描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数

>>>>>>> 7fd670f0b80d135596a51d0b229c4c4209f68d37
}
