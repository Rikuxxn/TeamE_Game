//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "action_clear.h"

//グローバル
LPDIRECT3DTEXTURE9 g_apTextureActionClear = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffActionClear = NULL;	  //頂点バッファへのポインタ

//クリアの初期化処理
void InitActionClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBG;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\CLEAR.png",//テクスチャのファイル名
		&g_apTextureActionClear);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffActionClear,
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffActionClear->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < 3; nCntBG++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(440.0f, 310.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(840.0f, 310.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(440.0f, 460.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(840.0f, 460.0f, 0.0f);

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

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffActionClear->Unlock();
}
//クリアの終了処理
void UninitActionClear(void)
{
	//テクスチャの破棄
	if (g_apTextureActionClear != NULL)
	{
		g_apTextureActionClear->Release();
		g_apTextureActionClear = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffActionClear != NULL)
	{
		g_pVtxBuffActionClear->Release();
		g_pVtxBuffActionClear = NULL;
	}

}
//クリアの更新処理
void UpdateActionClear(void)
{

}
//クリアの描画処理
void DrawActionClear(void)
{
	//テクスチャ3枚の描画+(必要なら)何かしら背景
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffActionClear, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureActionClear);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数
}