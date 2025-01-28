//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "map.h"

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureCraneMap = { NULL };//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneMap = NULL;//頂点バッファへのポインタ
float g_aPosCraneTexU;//テクスチャ座標の開始位置（U値）

//背景の初期化処理
void InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\map.png",//テクスチャのファイル名
		&g_pTextureCraneMap);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneMap,
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCraneMap->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(FIELD_LEFT - 50.0f, FIELD_TOP, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(FIELD_RIGHT + 50.f, FIELD_TOP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FIELD_LEFT - 50.0f, FIELD_UNDER + 200.f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(FIELD_RIGHT + 50.f, FIELD_UNDER + 200.f, 0.0f);

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
}
//背景の終了処理
void UninitMap(void)
{
	//テクスチャの破棄
	if (g_pTextureCraneMap != NULL)
	{
		g_pTextureCraneMap->Release();
		g_pTextureCraneMap = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffCraneMap != NULL)
	{
		g_pVtxBuffCraneMap->Release();
		g_pVtxBuffCraneMap = NULL;
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

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffCraneMap, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureCraneMap);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数
}