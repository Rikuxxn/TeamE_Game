//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "ball_tutorial.h"

//グローバル
LPDIRECT3DTEXTURE9 g_apTextureBallTutorial = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallTutorial = NULL;	//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallTutorial2 = NULL;

//クリアの初期化処理
void InitBallTutorial(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();//デバイスへのポインタ

	////テクスチャ1の読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\Complete.png",//テクスチャのファイル名
	//	&g_apTextureBallTutorial);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallTutorial,
		NULL);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallTutorial2,
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallTutorial->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(440.0f, 260.0f, 0.0f);//幅400.0f
	pVtx[1].pos = D3DXVECTOR3(840.0f, 260.0f, 0.0f);//高さ150.0f
	pVtx[2].pos = D3DXVECTOR3(440.0f, 410.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(840.0f, 410.0f, 0.0f);
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
	g_pVtxBuffBallTutorial->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallTutorial2->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//幅400.0f
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);//高さ150.0f
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファをアンロックする
	g_pVtxBuffBallTutorial2->Unlock();
}
//クリアの終了処理
void UninitBallTutorial(void)
{
	//テクスチャの破棄
	if (g_apTextureBallTutorial != NULL)
	{
		g_apTextureBallTutorial->Release();
		g_apTextureBallTutorial = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBallTutorial != NULL)
	{
		g_pVtxBuffBallTutorial->Release();
		g_pVtxBuffBallTutorial = NULL;
	}

}
//クリアの更新処理
void UpdateBallTutorial(void)
{

}
//クリアの描画処理
void DrawBallTutorial(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();//デバイスへのポインタ

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallTutorial2, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallTutorial, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureBallTutorial);
	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数
}