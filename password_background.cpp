//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_background.h"

//マクロ
#define NUM_BG (2)//背景の数

//グローバル
LPDIRECT3DTEXTURE9 g_pTexturePasswordBG4 = NULL;		//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePasswordBG5 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG = NULL;	//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG3 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG4 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG5 = NULL;

//背景の初期化処理
void InitPasswordBackGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//「離れる」の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UIKai6.png",//テクスチャのファイル名
		&g_pTexturePasswordBG4);

	//ヒントの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Pass_answer2.png",//テクスチャのファイル名
		&g_pTexturePasswordBG5);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG,
		NULL);
	VERTEX_2D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPasswordBG->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT, PASSWORDFIELD_TOP, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT, PASSWORDFIELD_TOP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT, PASSWORDFIELD_UNDER, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT, PASSWORDFIELD_UNDER, 0.0f);
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	pVtx[1].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	pVtx[2].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	pVtx[3].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	//頂点バッファをアンロックする
	g_pVtxBuffPasswordBG->Unlock();


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG2,
		NULL);
	VERTEX_2D* pVtx2;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPasswordBG2->Lock(0, 0, (void**)&pVtx2, 0);
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
	pVtx2[0].col = D3DCOLOR_RGBA(255, 100, 100, 100);
	pVtx2[1].col = D3DCOLOR_RGBA(255, 100, 100, 100);
	pVtx2[2].col = D3DCOLOR_RGBA(255, 100, 100, 100);
	pVtx2[3].col = D3DCOLOR_RGBA(255, 100, 100, 100);
	//頂点バッファをアンロックする
	g_pVtxBuffPasswordBG2->Unlock();


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG3,
		NULL);
	VERTEX_2D* pVtx3;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPasswordBG3->Lock(0, 0, (void**)&pVtx3, 0);
	//頂点座標の設定
	pVtx3[0].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT + 7.0f, PASSWORDFIELD_TOP + 7.0f, 0.0f);	//幅200.0f
	pVtx3[1].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT - 7.0f, PASSWORDFIELD_TOP + 7.0f, 0.0f);	//高さ500.0f
	pVtx3[2].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT + 7.0f, PASSWORDFIELD_TOP + 59.0f, 0.0f);
	pVtx3[3].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT - 7.0f, PASSWORDFIELD_TOP + 59.0f, 0.0f);
	//rhwの設定
	pVtx3[0].rhw = 1.0f;
	pVtx3[1].rhw = 1.0f;
	pVtx3[2].rhw = 1.0f;
	pVtx3[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx3[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx3[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx3[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx3[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	//頂点バッファをアンロックする
	g_pVtxBuffPasswordBG3->Unlock();


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG4,
		NULL);
	VERTEX_2D* pVtx4;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPasswordBG4->Lock(0, 0, (void**)&pVtx4, 0);
	//頂点座標の設定
	pVtx4[0].pos = D3DXVECTOR3(510.0f, 550.0f, 0.0f);//幅150.0f
	pVtx4[1].pos = D3DXVECTOR3(810.0f, 550.0f, 0.0f);//高さ40.0f
	pVtx4[2].pos = D3DXVECTOR3(510.0f, 630.0f, 0.0f);
	pVtx4[3].pos = D3DXVECTOR3(810.0f, 630.0f, 0.0f);
	//rhwの設定
	pVtx4[0].rhw = 1.0f;
	pVtx4[1].rhw = 1.0f;
	pVtx4[2].rhw = 1.0f;
	pVtx4[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx4[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx4[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx4[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx4[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ座標の設定
	pVtx4[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx4[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx4[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx4[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファをアンロックする
	g_pVtxBuffPasswordBG4->Unlock();


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG5,
		NULL);
	VERTEX_2D* pVtx5;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPasswordBG5->Lock(0, 0, (void**)&pVtx5, 0);
	//頂点座標の設定
	pVtx5[0].pos = D3DXVECTOR3(850.0f, 220.0f, 0.0f);//幅360.0f
	pVtx5[1].pos = D3DXVECTOR3(1210.0f, 220.0f, 0.0f);//高さ130.0f
	pVtx5[2].pos = D3DXVECTOR3(850.0f, 350.0f, 0.0f);
	pVtx5[3].pos = D3DXVECTOR3(1210.0f, 350.0f, 0.0f);
	//rhwの設定
	pVtx5[0].rhw = 1.0f;
	pVtx5[1].rhw = 1.0f;
	pVtx5[2].rhw = 1.0f;
	pVtx5[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx5[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx5[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx5[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx5[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ座標の設定
	pVtx5[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx5[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx5[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx5[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファをアンロックする
	g_pVtxBuffPasswordBG5->Unlock();
}
//背景の終了処理
void UninitPasswordBackGround(void)
{
	//テクスチャ
	if (g_pTexturePasswordBG4 != NULL)
	{
		g_pTexturePasswordBG4->Release();
		g_pTexturePasswordBG4 = NULL;
	}
	if (g_pTexturePasswordBG5 != NULL)
	{
		g_pTexturePasswordBG5->Release();
		g_pTexturePasswordBG5 = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPasswordBG != NULL)
	{
		g_pVtxBuffPasswordBG->Release();
		g_pVtxBuffPasswordBG = NULL;
	}
	if (g_pVtxBuffPasswordBG2 != NULL)
	{
		g_pVtxBuffPasswordBG2->Release();
		g_pVtxBuffPasswordBG2 = NULL;
	}
	if (g_pVtxBuffPasswordBG3 != NULL)
	{
		g_pVtxBuffPasswordBG3->Release();
		g_pVtxBuffPasswordBG3 = NULL;
	}
	if (g_pVtxBuffPasswordBG4 != NULL)
	{
		g_pVtxBuffPasswordBG4->Release();
		g_pVtxBuffPasswordBG4 = NULL;
	}
}
//背景の更新処理
void UpdatePasswordBackGround(void)
{

}
//背景の描画処理
void DrawPasswordBackGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//透明
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG2, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数


	//入力画面
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数


	//出力画面
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG3, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数


	//離れる
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG4, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePasswordBG4);
	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数


	//ヒント
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG5, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePasswordBG5);
	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数
}