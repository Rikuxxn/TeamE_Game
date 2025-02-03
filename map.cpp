//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "map.h"
#include "player.h"
#include "input.h"
#include "meshfield.h"

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureMap = { NULL };//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayerIcon = NULL;//テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMap = NULL;//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerIcon = NULL;//頂点バッファへのポインタ

float g_aPosCraneTexU;//テクスチャ座標の開始位置（U値）

//背景の初期化処理
void InitMap(void)
{
	Player* pPlayer = GetPlayer();

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\map.png",//テクスチャのファイル名
		&g_pTextureMap);

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\playerpos.png",//テクスチャのファイル名
		&g_pTexturePlayerIcon);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMap,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerIcon,
		NULL);

	float PlayerPosX = pPlayer->pos.x;  // プレイヤーの位置を取得
	float PlayerPosY = pPlayer->pos.y;	// プレイヤーの位置を取得


	// フィールドの幅と高さ
	float fieldWidth = MAX_WIDTH;
	float fieldHeight = MAX_HEIGHT;

	// ミニマップの幅と高さ
	float miniMapWidth = MINIMAP_RIGHT - MINIMAP_LEFT;
	float miniMapHeight = MINIMAP_UNDER - MINIMAP_TOP;

	// スケール（縮尺）の計算
	float scaleX = miniMapWidth / fieldWidth;
	float scaleY = miniMapHeight / fieldHeight;

	// プレイヤーの座標をミニマップの座標に変換
	float miniMapPlayerX = MINIMAP_LEFT + (pPlayer->pos.x / fieldWidth) * miniMapWidth;
	float miniMapPlayerY = MINIMAP_TOP + (pPlayer->pos.y / fieldHeight) * miniMapHeight;

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(MINIMAP_LEFT - 50.0f, MINIMAP_TOP, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(MINIMAP_RIGHT + 50.f, MINIMAP_TOP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(MINIMAP_LEFT - 50.0f, MINIMAP_UNDER + 200.f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MINIMAP_RIGHT + 50.f, MINIMAP_UNDER + 200.f, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	//頂点バッファをアンロックする
	g_pVtxBuffMap->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayerIcon->Lock(0, 0, (void**)&pVtx, 0);

	float size = 5.0f; // ミニマップ上でのプレイヤーアイコンの大きさ

	// ミニマップ上の座標でプレイヤーアイコンの頂点を設定
	pVtx[0].pos = D3DXVECTOR3(miniMapPlayerX - size, miniMapPlayerY - size, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(miniMapPlayerX + size, miniMapPlayerY - size, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(miniMapPlayerX - size, miniMapPlayerY + size, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(miniMapPlayerX + size, miniMapPlayerY + size, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	//頂点バッファをアンロックする
	g_pVtxBuffPlayerIcon->Unlock();

}
//背景の終了処理
void UninitMap(void)
{
	//テクスチャの破棄
	if (g_pTextureMap != NULL)
	{
		g_pTextureMap->Release();
		g_pTextureMap = NULL;
	}

	//テクスチャの破棄
	if (g_pTexturePlayerIcon != NULL)
	{
		g_pTexturePlayerIcon->Release();
		g_pTexturePlayerIcon = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMap != NULL)
	{
		g_pVtxBuffMap->Release();
		g_pVtxBuffMap = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayerIcon != NULL)
	{
		g_pVtxBuffPlayerIcon->Release();
		g_pVtxBuffPlayerIcon = NULL;
	}

}
//背景の更新処理
void UpdateMap(void)
{





}
//背景の描画処理
void DrawMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();


	//===============
	// マップの描画
	//===============

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffMap, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMap);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数


	//==========================
	// プレイヤーアイコンの描画
	//==========================

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerIcon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayerIcon);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数

}