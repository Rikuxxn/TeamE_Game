//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_background.h"
#include "password_game.h"
#include "shooting_score.h"

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureSTPass = { NULL };			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSTPass = NULL;		//頂点バッファへのポインタ
int g_nSTPass;											//パスワードの値
STPass g_aSTPass[MAX_NUM_SCORE] = {};

//=========================
//|| パスワードの初期化  ||
//=========================
void InitSTPass(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ballnumber.png",//テクスチャのファイル名
		&g_pTextureSTPass);

	//g_nSTPass = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSTPass,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSTPass->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntSTPass = 0; nCntSTPass < MAX_NUM_SCORE; nCntSTPass++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(PASSPOSX + nCntSTPass * 20.0f, PASSPOSY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PASSPOSX + nCntSTPass * 20.0f + 100.0f, PASSPOSY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PASSPOSX + nCntSTPass * 20.0f, PASSPOSY + 110.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PASSPOSX + nCntSTPass * 20.0f + 100.0f, PASSPOSY + 110.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffSTPass->Unlock();

	SetSTPass(0);
}
//=========================
//|| パスワードの終了処理||
//=========================
void UninitSTPass(void)
{
	//テクスチャの破棄
	if (g_pTextureSTPass != NULL)
	{
		g_pTextureSTPass->Release();
		g_pTextureSTPass = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSTPass != NULL)
	{
		g_pVtxBuffSTPass->Release();
		g_pVtxBuffSTPass = NULL;
	}
}
//=========================
//|| パスワードの更新処理||
//=========================
void UpdateSTPass(void)
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int nData;
	int nData1 = 0;

	nData = STPassCounter(g_nSTPass);
	for (nData1 = 0; nData1 < MAX_NUM_SCORE; nData1++)
	{
		if (nData1 >= MAX_NUM_SCORE - nData)
		{
			g_aSTPass[nData1].buse = true;
		}
		else
		{
			g_aSTPass[nData1].buse = false;
		}
	}
}
//=========================
//|| パスワードの描画処理||
//=========================
void DrawSTPass(void)
{

	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int nCntSTPass;
	LPDIRECT3DDEVICE9 pDevice;
	
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffSTPass, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSTPass->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSTPass = 0; nCntSTPass < MAX_NUM_SCORE; nCntSTPass++)
	{
		if (g_aSTPass[nCntSTPass].buse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSTPass);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntSTPass * 4,						//描画する最初の頂点インデックス
				2);										//描画するプリミティブ数
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSTPass->Unlock();
}
//=========================
//|| パスワードの設定処理||
//=========================
void SetSTPass(int nSTAPass) 
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int aPosTexU[MAX_NUM_SCORE] = {};//各桁の数字を格納
	int n = 1000;
	int n1 = 100;
	aPosTexU[0] = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSTPass->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntSTPass = 0; nCntSTPass < MAX_NUM_SCORE; nCntSTPass++)
	{
		if (nCntSTPass == 0)
		{
			aPosTexU[0] = nSTAPass / n;
		}
		else
		{
			aPosTexU[nCntSTPass] = nSTAPass % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntSTPass]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntSTPass]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntSTPass]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntSTPass]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffSTPass->Unlock();
}
//=====================
//スコアの0をカウント
//=====================
int STPassCounter(int nPass)
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