//=========================================================
// 
// ミニマップ表示処理[map.cpp]
// Author:TANEKAWA RIKU
// 
//=========================================================
#include "map.h"
#include "player.h"
#include "input.h"
#include "meshfield.h"
#include "camera.h"

//// アイコン構造体
//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 rot;
//	float fWidth;
//	float fHeight;
//}Icon;
//
//// ミニマップ構造体
//typedef struct
//{
//	D3DXVECTOR3 pos;
//	float fWidth;
//	float fHeight;
//}Map;
//
//Icon g_Icon;// アイコンの情報
//
//Map g_Map;// マップの情報

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMap = { NULL };						// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayerIcon = NULL;						// テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMap = NULL;						// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerIcon = NULL;				// 頂点バッファへのポインタ

D3DXVECTOR3 miniMapBasePos;	// ミニマップの基準位置

//===============================
// ミニマップの初期化処理
//===============================
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

	miniMapBasePos = D3DXVECTOR3(1180.0f, 0.0f, 1480.0f);	// アイコンの初期位置
	float PlayerPosX = pPlayer->pos.x;						// プレイヤーの位置を取得
	float PlayerPosY = pPlayer->pos.y;						// プレイヤーの位置を取得

	// フィールドの幅と高さ
	float fieldWidth = MAX_WIDTH;
	float fieldHeight = MAX_HEIGHT;

	// ミニマップの幅と高さ
	float miniMapWidth = MINIMAP_RIGHT - MINIMAP_LEFT;
	float miniMapHeight = MINIMAP_UNDER - MINIMAP_TOP;

	// スケール（縮尺）の計算
	float scaleX = miniMapWidth / fieldWidth;
	float scaleY = miniMapHeight / fieldHeight;

	// ミニマップのX座標を変換
	float miniMapPlayerX = MINIMAP_LEFT + (((pPlayer->pos.x + miniMapBasePos.x) / fieldWidth) * miniMapWidth);

	// ミニマップのY座標を変換
	float miniMapPlayerY = MINIMAP_TOP - ((((pPlayer->pos.z - 100) - miniMapBasePos.z) / fieldHeight) * miniMapHeight);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(MINIMAP_LEFT - 5.0f, MINIMAP_TOP + 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(MINIMAP_RIGHT - 10.0f, MINIMAP_TOP + 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(MINIMAP_LEFT - 5.0f, MINIMAP_UNDER + 115.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MINIMAP_RIGHT - 10.0f, MINIMAP_UNDER + 115.0f, 0.0f);

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

	float size = 15.0f; // ミニマップ上でのプレイヤーアイコンの大きさ

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
//===============================
// ミニマップの終了処理
//===============================
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
//===============================
// ミニマップの更新処理
//===============================
void UpdateMap(void)
{

	Player* pPlayer = GetPlayer();
	Camera* pCamera = GetCamera();

	// フィールドの幅と高さ
	float fieldWidth = MAX_WIDTH;
	float fieldHeight = MAX_HEIGHT;

	// ミニマップの幅と高さ
	float miniMapWidth = MINIMAP_RIGHT - MINIMAP_LEFT;
	float miniMapHeight = MINIMAP_UNDER - MINIMAP_TOP;

	// ミニマップ上の移動量
	float miniMapScale = 0.5f;

	// ミニマップのX座標を変換
	float miniMapPlayerX = MINIMAP_LEFT + (((pPlayer->pos.x + miniMapBasePos.x) / fieldWidth) * miniMapWidth);

	// ミニマップのY座標を変換
	float miniMapPlayerY = MINIMAP_TOP - ((((pPlayer->pos.z - 100) - miniMapBasePos.z) / fieldHeight) * miniMapHeight);

	// 頂点バッファを更新
	VERTEX_2D* pVtx;

	float angle = pCamera->rot.y;

	// 頂点バッファのロック
	g_pVtxBuffPlayerIcon->Lock(0, 0, (void**)&pVtx, 0);

	float size = 15.0f; // アイコンのサイズ

	// 回転行列
	D3DXMATRIX matRot;
	D3DXMatrixRotationZ(&matRot, angle); // Z軸回転（2D回転）

	// アイコンの頂点を回転
	D3DXVECTOR3 v[4] =
	{
		{  size,  size, 0.0f },
		{ -size,  size, 0.0f },
		{  size, -size, 0.0f },
		{ -size, -size, 0.0f }
	};

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		D3DXVec3TransformCoord(&v[nCnt], &v[nCnt], &matRot);
		pVtx[nCnt].pos = D3DXVECTOR3(miniMapPlayerX + v[nCnt].x, miniMapPlayerY + v[nCnt].y, 0.0f);
	}

	// 頂点バッファのアンロック
	g_pVtxBuffPlayerIcon->Unlock();
}
//===============================
// ミニマップの描画処理
//===============================
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