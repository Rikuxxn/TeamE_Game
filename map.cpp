//=========================================================
// 
// ミニマップ表示処理 [map.cpp]
// Author : TANEKAWA RIKU
// 
//=========================================================
#include "map.h"
#include "player.h"
#include "input.h"
#include "meshfield.h"
#include "camera.h"

// グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMap = { NULL };						// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayerIcon = NULL;						// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureNone = NULL;							// テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMap = NULL;						// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerIcon = NULL;				// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNone = NULL;						// 頂点バッファへのポインタ

Icon g_Icon;														// アイコンの情報
Map g_Map;															// マップの情報

//===============================
// ミニマップの初期化処理
//===============================
void InitMap(void)
{
	Player* pPlayer = GetPlayer();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\minimap.png",			// テクスチャのファイル名
		&g_pTextureMap);

	// テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\playerpos.png",			// テクスチャのファイル名
		&g_pTexturePlayerIcon);

	// テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\.png",					// テクスチャのファイル名
		&g_pTextureNone);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMap,
		NULL);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerIcon,
		NULL);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNone,
		NULL);

	g_Map.pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f); // 初期位置

	// フィールドの幅と高さ
	g_Map.fWidth = MAX_WIDTH / 3.0f;
	g_Map.fHeight = MAX_HEIGHT / 3.0f;

	// アイコンのサイズ設定
	g_Icon.fWidth = 15.0f;
	g_Icon.fHeight = 15.0f;

	// ミニマップの左上座標を計算
	float miniMapLeft	= g_Map.pos.x - g_Map.fWidth / 2.0f;
	float miniMapTop	= g_Map.pos.y - g_Map.fHeight / 2.0f;

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(miniMapLeft, miniMapTop, 0.0f);									// 左上
	pVtx[1].pos = D3DXVECTOR3(miniMapLeft + g_Map.fWidth, miniMapTop, 0.0f);					// 右上
	pVtx[2].pos = D3DXVECTOR3(miniMapLeft, miniMapTop + g_Map.fHeight, 0.0f);					// 左下
	pVtx[3].pos = D3DXVECTOR3(miniMapLeft + g_Map.fWidth, miniMapTop + g_Map.fHeight, 0.0f);	// 右下

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	// 頂点バッファをアンロックする
	g_pVtxBuffMap->Unlock();


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayerIcon->Lock(0, 0, (void**)&pVtx, 0);

	float size = g_Icon.fWidth;// プレイヤーアイコンの大きさ

	// プレイヤーアイコンの頂点を設定
	pVtx[0].pos = D3DXVECTOR3(g_Icon.pos.x - size, g_Icon.pos.y - size, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Icon.pos.x + size, g_Icon.pos.y - size, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Icon.pos.x - size, g_Icon.pos.y + size, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Icon.pos.x + size, g_Icon.pos.y + size, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	// 頂点バッファをアンロックする
	g_pVtxBuffPlayerIcon->Unlock();


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffNone->Lock(0, 0, (void**)&pVtx, 0);

	// 薄暗い背景の頂点を設定
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
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	// 頂点バッファをアンロックする
	g_pVtxBuffNone->Unlock();

}
//===============================
// ミニマップの終了処理
//===============================
void UninitMap(void)
{
	// テクスチャの破棄
	if (g_pTextureMap != NULL)
	{
		g_pTextureMap->Release();
		g_pTextureMap = NULL;
	}

	// テクスチャの破棄
	if (g_pTexturePlayerIcon != NULL)
	{
		g_pTexturePlayerIcon->Release();
		g_pTexturePlayerIcon = NULL;
	}

	// テクスチャの破棄
	if (g_pTextureNone != NULL)
	{
		g_pTextureNone->Release();
		g_pTextureNone = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffMap != NULL)
	{
		g_pVtxBuffMap->Release();
		g_pVtxBuffMap = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffPlayerIcon != NULL)
	{
		g_pVtxBuffPlayerIcon->Release();
		g_pVtxBuffPlayerIcon = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffNone != NULL)
	{
		g_pVtxBuffNone->Release();
		g_pVtxBuffNone = NULL;
	}

}
//===============================
// ミニマップの更新処理
//===============================
void UpdateMap(void)
{

	Player* pPlayer = GetPlayer();
	Camera* pCamera = GetCamera();

	// ミニマップの左上の座標
	float miniMapLeft	= g_Map.pos.x - g_Map.fWidth / 2.0f;
	float miniMapTop	= g_Map.pos.y - g_Map.fHeight / 2.0f;

	// スケール（ワールド座標 → ミニマップ座標変換用）
	float scaleX = g_Map.fWidth / MAX_WIDTH;   // 600 / 2400 = 0.25
	float scaleY = g_Map.fHeight / MAX_HEIGHT; // 500 / 2000 = 0.25

	// プレイヤーの座標をミニマップ座標に変換
	g_Icon.pos.x = miniMapLeft + (pPlayer->pos.x + (MAX_WIDTH / 2.0f)) * scaleX;
	g_Icon.pos.y = miniMapTop - (pPlayer->pos.z - (MAX_HEIGHT / 2.0f)) * scaleY;
	g_Icon.pos.z = 0.0f;

	// プレイヤーの回転をアイコンに反映
	g_Icon.rot.y = pCamera->rot.y; // カメラのY軸回転

	// 頂点バッファを更新
	VERTEX_2D* pVtx;

	// 頂点バッファのロック
	g_pVtxBuffPlayerIcon->Lock(0, 0, (void**)&pVtx, 0);

	// 回転行列
	D3DXMATRIX matRot;
	D3DXMatrixRotationZ(&matRot, g_Icon.rot.y); // Z軸回転（2D回転）

	// アイコンの頂点を回転
	D3DXVECTOR3 v[4] =
	{
		{  g_Icon.fWidth,  g_Icon.fHeight, 0.0f },
		{ -g_Icon.fWidth,  g_Icon.fHeight, 0.0f },
		{  g_Icon.fWidth, -g_Icon.fHeight, 0.0f },
		{ -g_Icon.fWidth, -g_Icon.fHeight, 0.0f }
	};

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		D3DXVec3TransformCoord(&v[nCnt], &v[nCnt], &matRot);
		pVtx[nCnt].pos = D3DXVECTOR3(g_Icon.pos.x + v[nCnt].x, g_Icon.pos.y + v[nCnt].y, 0.0f);
	}

	// 頂点バッファのアンロック
	g_pVtxBuffPlayerIcon->Unlock();
}
//===============================
// ミニマップの描画処理
//===============================
void DrawMap(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//====================
	// 薄暗い背景の描画
	//====================

	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffNone, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// 背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数


	//===============
	// マップの描画
	//===============

	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffMap, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMap);

	// 背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数


	//==========================
	// プレイヤーアイコンの描画
	//==========================

	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerIcon, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayerIcon);

	// 背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数

}