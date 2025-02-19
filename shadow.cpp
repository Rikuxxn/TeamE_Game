//=======================================
//
// 影の処理 [shadow.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "shadow.h"
#include "player.h"

#define MAX_SHADOW (10)								// 影の最大数
#define SHADOW_WIDTH (25.0f)						// 影の横幅
#define SHADOW_HEGIHT (0.1f)						// 影の縦幅
#define SHADOW_DEPTH (25.0f)						// 影の奥行

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// 頂点バッファへのポインタ

Shadow g_aShadow[MAX_SHADOW];						// 影情報

//=============================
// 影の初期化処理
//=============================
void InitShadow(void)
{

	int nCntShadow;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);


	//影の初期化
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D* pVtx = NULL;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x - SHADOW_WIDTH, g_aShadow[nCntShadow].pos.y + SHADOW_HEGIHT, g_aShadow[nCntShadow].pos.z + SHADOW_DEPTH);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x + SHADOW_WIDTH, g_aShadow[nCntShadow].pos.y + SHADOW_HEGIHT, g_aShadow[nCntShadow].pos.z + SHADOW_DEPTH);
		pVtx[2].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x - SHADOW_WIDTH, g_aShadow[nCntShadow].pos.y + SHADOW_HEGIHT, g_aShadow[nCntShadow].pos.z - SHADOW_DEPTH);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x + SHADOW_WIDTH, g_aShadow[nCntShadow].pos.y + SHADOW_HEGIHT, g_aShadow[nCntShadow].pos.z - SHADOW_DEPTH);


		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255,255,255,80);
		pVtx[1].col = D3DCOLOR_RGBA(255,255,255,80);
		pVtx[2].col = D3DCOLOR_RGBA(255,255,255,80);
		pVtx[3].col = D3DCOLOR_RGBA(255,255,255,80);


		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		pVtx += 4;//頂点データのポインタを4つ分進める

	}


	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

}
//=============================
// 影の終了処理
//=============================
void UninitShadow(void)
{

	//テクスチャの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

}
//=============================
// 影の更新処理
//=============================
void UpdateShadow(void)
{




}
//=============================
// 影の描画処理
//=============================
void DrawShadow(void)
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//αブレンディングを減算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{

			//計算用マトリックス
			D3DXMATRIX mtxRot, mtxTrans;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//ワールドマトリックスを設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);

		}
	}

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//=============================
// 影の設定
//=============================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{

			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;


			break;

		}

		//pVtx += 4;
	}

	return nCntShadow;//影の番号(index)を返す
}
//=============================
// 影の位置の更新処理
//=============================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{

		//引数で指定された番号のかげのposを設定
		g_aShadow[nIdxShadow].pos = pos;

	}
}
//=============================
// 影情報の取得
//=============================
Shadow* GetShadow(void)
{
	return g_aShadow;
}
//=============================
// 影の削除処理
//=============================
void ShadowFalse(int nIdxShadow)
{//消したいオブジェクトの影
	g_aShadow[nIdxShadow].bUse = false;
}
