//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_background.h"
#include "password_game.h"
#include "ball_score.h"

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureBallPass = { NULL };			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallPass = NULL;			//頂点バッファへのポインタ
int g_nBallPass;											//パスワードの値
BallPass g_aBallPass[MAX_NUM_SCORE] = {};

//=========================
//|| パスワードの初期化  ||
//=========================
void InitBallPass(void)
{
	int nCntBallPass;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ballnum.png",//テクスチャのファイル名
		&g_pTextureBallPass);

	//g_nBallPass = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallPass,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallPass->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBallPass = 0; nCntBallPass < MAX_NUM_SCORE; nCntBallPass++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(PASSPOSX + nCntBallPass * 20.0f, 160.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PASSPOSX + nCntBallPass * 20.0f + 200.0f, 160.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PASSPOSX + nCntBallPass * 20.0f, 560.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PASSPOSX + nCntBallPass * 20.0f + 200.0f, 560.0f, 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBallPass->Unlock();

	SetBallPass(0);
}
//=========================
//|| パスワードの終了処理||
//=========================
void UninitBallPass(void)
{
	//テクスチャの破棄
	if (g_pTextureBallPass != NULL)
	{
		g_pTextureBallPass->Release();
		g_pTextureBallPass = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBallPass != NULL)
	{
		g_pVtxBuffBallPass->Release();
		g_pVtxBuffBallPass = NULL;
	}
}
//=========================
//|| パスワードの更新処理||
//=========================
void UpdateBallPass(void)
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int nData;
	int nData1 = 0;

	nData = BallPassCounter(g_nBallPass);
	for (nData1 = 0; nData1 < MAX_NUM_SCORE; nData1++)
	{
		if (nData1 >= MAX_NUM_SCORE - nData)
		{
			g_aBallPass[nData1].buse = true;
		}
		else
		{
			g_aBallPass[nData1].buse = false;
		}
	}
}
//=========================
//|| パスワードの描画処理||
//=========================
void DrawBallPass(void)
{

	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int nCntBallPass;
	LPDIRECT3DDEVICE9 pDevice;
	
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallPass, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallPass->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBallPass = 0; nCntBallPass < MAX_NUM_SCORE; nCntBallPass++)
	{
		if (g_aBallPass[nCntBallPass].buse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBallPass);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntBallPass * 4,						//描画する最初の頂点インデックス
				2);										//描画するプリミティブ数
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBallPass->Unlock();
}
//=========================
//|| パスワードの設定処理||
//=========================
void SetBallPass(int nBallAPass) 
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int aPosTexU[MAX_NUM_SCORE] = {};//各桁の数字を格納
	int n = 1000;
	int n1 = 100;
	aPosTexU[0] = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallPass->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBallPass = 0; nCntBallPass < MAX_NUM_SCORE; nCntBallPass++)
	{
		if (nCntBallPass == 0)
		{
			aPosTexU[0] = nBallAPass / n;
		}
		else
		{
			aPosTexU[nCntBallPass] = nBallAPass % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntBallPass]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntBallPass]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntBallPass]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntBallPass]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBallPass->Unlock();
}
//=====================
//|スコアの0をカウント|
//=====================
int BallPassCounter(int nPass)
{
	int nNum = nPass;//スコアの０の部分をカウント
	int nKeepNum = 0;//スコアの桁数

	while (nNum != 0)//割り切れなくなるまで繰り返す(０まで)
	{
		nNum /= 10;//nNumを10で割っていく
		nKeepNum++;//桁数を加算
	}
	if (nPass == 0)
	{
		//1桁目に0が入っているとき
		nKeepNum = 1;
	}
	return nKeepNum;//スコアの桁数を返す
}