//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_background.h"
#include "password_game.h"
#include "crane_score.h"

// グローバル
LPDIRECT3DTEXTURE9 g_pTextureCranePass = { NULL };			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCranePass = NULL;			// 頂点バッファへのポインタ
CranePass g_aCranePass[MAX_NUM_SCORE] = {};					// クレーン
int g_nCranePass;											// パスワードの値

//=========================
//|| パスワードの初期化  ||
//=========================
void InitCranePass(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// デバイスへのポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ballnumber.png",// テクスチャのファイル名
		&g_pTextureCranePass);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCranePass,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCranePass->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntCranePass = 0; nCntCranePass < MAX_NUM_SCORE; nCntCranePass++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(PASSPOSX + nCntCranePass * 20.0f, PASSWORDFIELD_TOP, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PASSPOSX + nCntCranePass * 20.0f + 45.0f, PASSWORDFIELD_TOP, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PASSPOSX + nCntCranePass * 20.0f, PASSWORDFIELD_TOP + 70.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PASSPOSX + nCntCranePass * 20.0f + 45.0f, PASSWORDFIELD_TOP + 70.0f, 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffCranePass->Unlock();

	SetCranePass(0);
}
//=========================
//|| パスワードの終了処理||
//=========================
void UninitCranePass(void)
{
	// テクスチャの破棄
	if (g_pTextureCranePass != NULL)
	{
		g_pTextureCranePass->Release();
		g_pTextureCranePass = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffCranePass != NULL)
	{
		g_pVtxBuffCranePass->Release();
		g_pVtxBuffCranePass = NULL;
	}
}
//=========================
//|| パスワードの更新処理||
//=========================
void UpdateCranePass(void)
{
	VERTEX_2D* pVtx = 0;// 頂点情報へのポインタ
	int nData;
	int nData1 = 0;

	nData = CranePassCounter(g_nCranePass);
	for (nData1 = 0; nData1 < MAX_NUM_SCORE; nData1++)
	{
		if (nData1 >= MAX_NUM_SCORE - nData)
		{
			g_aCranePass[nData1].buse = true;
		}
		else
		{
			g_aCranePass[nData1].buse = false;
		}
	}
}
//=========================
//|| パスワードの描画処理||
//=========================
void DrawCranePass(void)
{

	VERTEX_2D* pVtx = 0;						// 頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffCranePass, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCranePass->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCranePass = 0; nCntCranePass < MAX_NUM_SCORE; nCntCranePass++)
	{
		if (g_aCranePass[nCntCranePass].buse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureCranePass);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの種類
				nCntCranePass * 4,						// 描画する最初の頂点インデックス
				2);										// 描画するプリミティブ数
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffCranePass->Unlock();
}
//=========================
//|| パスワードの設定処理||
//=========================
void SetCranePass(int nCraneAPass) 
{
	VERTEX_2D* pVtx = 0;				// 頂点情報へのポインタ
	int aPosTexU[MAX_NUM_SCORE] = {};	// 各桁の数字を格納
	int n = 1000;
	int n1 = 100;
	aPosTexU[0] = 0;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCranePass->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCranePass = 0; nCntCranePass < MAX_NUM_SCORE; nCntCranePass++)
	{
		if (nCntCranePass == 0)
		{
			aPosTexU[0] = nCraneAPass / n;
		}
		else
		{
			aPosTexU[nCntCranePass] = nCraneAPass % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntCranePass]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntCranePass]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntCranePass]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntCranePass]), 1.0f);
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffCranePass->Unlock();
}
//=====================
//スコアの0をカウント
//=====================
int CranePassCounter(int nPass)
{
	int nNum = nPass;	// スコアの０の部分をカウント
	int nKeepNum = 0;	// スコアの桁数

	while (nNum != 0)	// 割り切れなくなるまで繰り返す(０まで)
	{
		nNum /= 10;		// nNumを10で割っていく
		nKeepNum++;		// 桁数を加算
	}
	if (nPass == 0)
	{
		nKeepNum = 1;	// 1桁目に0が入っているとき
	}
	return nKeepNum;	// スコアの桁数を返す
}