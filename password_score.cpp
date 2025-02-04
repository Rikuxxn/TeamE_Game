//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_background.h"
#include "password_game.h"
#include "password_item.h"
#include "password_score.h"

//グローバル
LPDIRECT3DTEXTURE9 g_pTexturePassword = { NULL };			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassword = NULL;			//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassword2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassword3 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassword4 = NULL;
int g_nPassword, g_nPassword2, g_nPassword3, g_nPassword4;	//パスワードの値
int g_nCnt;
bool g_bJudge;
Password g_aPassword[MAX_NUM_SCORE] = {};

//=========================
//|| パスワードの初期化  ||
//=========================
void InitPassword(void)
{
	int nCntPassword;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",//テクスチャのファイル名
		&g_pTexturePassword);

	g_nPassword, g_nPassword2, g_nPassword3, g_nPassword4 = 0;
	g_nCnt = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPassword,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPassword2,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPassword3,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPassword4,
		NULL);
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;
	VERTEX_2D* pVtx2;
	VERTEX_2D* pVtx3;
	VERTEX_2D* pVtx4;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 20.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 20.0f + 40.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 20.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 20.0f + 40.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword2->Lock(0, 0, (void**)&pVtx2, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		//頂点座標の設定
		pVtx2[0].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 34.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx2[1].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 34.0f + 40.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx2[2].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 34.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		pVtx2[3].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 34.0f + 40.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		//rhwの設定
		pVtx2[0].rhw = 1.0f;
		pVtx2[1].rhw = 1.0f;
		pVtx2[2].rhw = 1.0f;
		pVtx2[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx2[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx2[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx2[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx2[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx2[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx2[1].tex = D3DXVECTOR2(0.1f, 0.0f);//(u,v)
		pVtx2[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
		pVtx2[3].tex = D3DXVECTOR2(0.1f, 1.0f);//(u,v)
		pVtx2 += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword2->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword3->Lock(0, 0, (void**)&pVtx3, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		//頂点座標の設定
		pVtx3[0].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 48.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx3[1].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 48.0f + 40.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx3[2].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 48.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		pVtx3[3].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 48.0f + 40.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		//rhwの設定
		pVtx3[0].rhw = 1.0f;
		pVtx3[1].rhw = 1.0f;
		pVtx3[2].rhw = 1.0f;
		pVtx3[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx3[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx3[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx3[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx3[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx3[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx3[1].tex = D3DXVECTOR2(0.1f, 0.0f);//(u,v)
		pVtx3[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
		pVtx3[3].tex = D3DXVECTOR2(0.1f, 1.0f);//(u,v)
		pVtx3 += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword3->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword4->Lock(0, 0, (void**)&pVtx4, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		//頂点座標の設定
		pVtx4[0].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 62.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx4[1].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 62.0f + 40.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx4[2].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 62.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		pVtx4[3].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 62.0f + 40.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		//rhwの設定
		pVtx4[0].rhw = 1.0f;
		pVtx4[1].rhw = 1.0f;
		pVtx4[2].rhw = 1.0f;
		pVtx4[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx4[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx4[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx4[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx4[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx4[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx4[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx4[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx4[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx4 += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword3->Unlock();

	SetPassword(0);
}
//=========================
//|| パスワードの終了処理||
//=========================
void UninitPassword(void)
{
	//テクスチャの破棄
	if (g_pTexturePassword != NULL)
	{
		g_pTexturePassword->Release();
		g_pTexturePassword = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPassword != NULL &&
		g_pVtxBuffPassword2 != NULL &&
		g_pVtxBuffPassword3 != NULL &&
		g_pVtxBuffPassword4 != NULL)
	{
		g_pVtxBuffPassword->Release();
		g_pVtxBuffPassword = NULL;
		g_pVtxBuffPassword2->Release();
		g_pVtxBuffPassword2 = NULL;
		g_pVtxBuffPassword3->Release();
		g_pVtxBuffPassword3 = NULL;
		g_pVtxBuffPassword4->Release();
		g_pVtxBuffPassword4 = NULL;
	}
}
//=========================
//|| パスワードの更新処理||
//=========================
void UpdatePassword(void)
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int nData;
	int nData1 = 0;

	nData = PasswordCounter(g_nPassword);
	for (nData1 = 0; nData1 < MAX_NUM_SCORE; nData1++)
	{
		if (nData1 >= MAX_NUM_SCORE - nData)
		{
			g_aPassword[nData1].buse = true;
		}
		else
		{
			g_aPassword[nData1].buse = false;
		}
	}
}
//=========================
//|| パスワードの描画処理||
//=========================
void DrawPassword(void)
{

	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int nCntPassword;
	LPDIRECT3DDEVICE9 pDevice;
	
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPassword, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (g_aPassword[nCntPassword].buse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePassword);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntPassword * 4,						//描画する最初の頂点インデックス
				2);										//描画するプリミティブ数
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPassword->Unlock();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPassword2, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword2->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (g_aPassword[nCntPassword].buse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePassword);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntPassword * 4,						//描画する最初の頂点インデックス
				2);										//描画するプリミティブ数
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword2->Unlock();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPassword3, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword3->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (g_aPassword[nCntPassword].buse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePassword);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntPassword * 4,						//描画する最初の頂点インデックス
				2);										//描画するプリミティブ数
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword3->Unlock();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPassword4, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword4->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (g_aPassword[nCntPassword].buse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePassword);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntPassword * 4,						//描画する最初の頂点インデックス
				2);										//描画するプリミティブ数
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword4->Unlock();
}
//=========================
//|| パスワードの設定処理||
//=========================
void SetPassword(int nPass)
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int aPosTexU[MAX_NUM_SCORE] = {};//各桁の数字を格納
	int aPosTexU2[MAX_NUM_SCORE] = {};
	int aPosTexU3[MAX_NUM_SCORE] = {};
	int aPosTexU4[MAX_NUM_SCORE] = {};
	int nCntPassword;
	int n = 1000;
	int n1 = 100;
	g_bJudge = false;
	aPosTexU[0] = 0;
	aPosTexU2[0] = 0;
	aPosTexU3[0] = 0;
	aPosTexU4[0] = 0;
	g_nPassword = nPass;
	g_nPassword2 = nPass;
	g_nPassword3 = nPass;
	g_nPassword4 = nPass;
	g_nCnt = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (nCntPassword == 0)
		{
			aPosTexU[0] = g_nPassword / n;
		}
		else
		{
			aPosTexU[nCntPassword] = g_nPassword % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword->Unlock();

	n = 1000;
	n1 = 100;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword2->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (nCntPassword == 0)
		{
			aPosTexU2[0] = g_nPassword2 / n;
		}
		else
		{
			aPosTexU2[nCntPassword] = g_nPassword2 % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU2[nCntPassword]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU2[nCntPassword]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU2[nCntPassword]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU2[nCntPassword]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword2->Unlock();

	n = 1000;
	n1 = 100;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword3->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (nCntPassword == 0)
		{
			aPosTexU3[0] = g_nPassword3 / n;
		}
		else
		{
			aPosTexU3[nCntPassword] = g_nPassword3 % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU3[nCntPassword]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU3[nCntPassword]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU3[nCntPassword]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU3[nCntPassword]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword3->Unlock();

	n = 1000;
	n1 = 100;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword4->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (nCntPassword == 0)
		{
			aPosTexU4[0] = g_nPassword4 / n;
		}
		else
		{
			aPosTexU4[nCntPassword] = g_nPassword4 % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU4[nCntPassword]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU4[nCntPassword]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU4[nCntPassword]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU4[nCntPassword]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword4->Unlock();
}
//=========================
//|| パスワードの加算処理||
//=========================
void AddPassword(int nValue)
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int nCntPassword;
	int aPosTexU[MAX_NUM_SCORE] = {};//各桁の数字を格納
	int n = 1000;
	int n1 = 100;
	aPosTexU[0] = {};
	g_nCnt++;
	switch (g_nCnt)
	{
	case 1:
		g_nPassword = nValue;
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);
		for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
		{
			if (nCntPassword == 0)
			{
				aPosTexU[0] = g_nPassword / n;
			}
			else
			{
				aPosTexU[nCntPassword] = g_nPassword % n / n1;
				n = n / 10;
				n1 = n1 / 10;
			}
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx += 4;
		}
		//頂点バッファをアンロックする
		g_pVtxBuffPassword->Unlock();
		break;
	case 2:
		g_nPassword2 = nValue;
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPassword2->Lock(0, 0, (void**)&pVtx, 0);
		for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
		{
			if (nCntPassword == 0)
			{
				aPosTexU[0] = g_nPassword2 / n;
			}
			else
			{
				aPosTexU[nCntPassword] = g_nPassword2 % n / n1;
				n = n / 10;
				n1 = n1 / 10;
			}
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx += 4;
		}
		//頂点バッファをアンロックする
		g_pVtxBuffPassword2->Unlock();
		break;
	case 3:
		g_nPassword3 = nValue;
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPassword3->Lock(0, 0, (void**)&pVtx, 0);
		for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
		{
			if (nCntPassword == 0)
			{
				aPosTexU[0] = g_nPassword3 / n;
			}
			else
			{
				aPosTexU[nCntPassword] = g_nPassword3 % n / n1;
				n = n / 10;
				n1 = n1 / 10;
			}
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx += 4;
		}
		//頂点バッファをアンロックする
		g_pVtxBuffPassword3->Unlock();
		break;
	case 4:
		g_nPassword4 = nValue;
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPassword4->Lock(0, 0, (void**)&pVtx, 0);
		for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
		{
			if (nCntPassword == 0)
			{
				aPosTexU[0] = g_nPassword4 / n;
			}
			else
			{
				aPosTexU[nCntPassword] = g_nPassword4 % n / n1;
				n = n / 10;
				n1 = n1 / 10;
			}
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx += 4;
		}
		//頂点バッファをアンロックする
		g_pVtxBuffPassword4->Unlock();
		break;
	default:
		/*音を流す*/
		break;
	}

}
//=====================
//スコアの0をカウント
//=====================
int PasswordCounter(int nPass)
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
//=========================
//||  パスワードの取得   ||
//=========================
int GetPassword(void)
{
	return g_nPassword;
}
int GetPassword2(void)
{
	return g_nPassword2;
}
int GetPassword3(void)
{
	return g_nPassword3;
}
int GetPassword4(void)
{
	return g_nPassword4;
}
int GetCntCounter(void)
{
	return g_nCnt;
}
bool GetJudge(void)
{
	return g_bJudge;
}