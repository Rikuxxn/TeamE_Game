//=======================================
//
// メッシュシーリング処理[meshceiling.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "meshceiling.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMeshCeiling = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCeiling = NULL;//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCeiling = NULL;//インデックスバッファへのポインタ

D3DXVECTOR3 g_posMeshCeiling;//位置
D3DXVECTOR3 g_rotMeshCeiling;//向き
D3DXMATRIX g_mtxWorldMeshCeiling;//ワールドマトリックス

//==================================
//メッシュフィールドの初期化処理
//==================================
void InitMeshCeiling(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_posMeshCeiling = D3DXVECTOR3(0.0f, 260.0f, 0.0f);
	g_rotMeshCeiling = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX_CEILING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCeiling,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall001.jpg",
		&g_pTextureMeshCeiling);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_INDEX_CEILING,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCeiling,
		NULL);

	VERTEX_3D* pVtx = NULL;//頂点情報へのポインタ

	int nCnt = 0;
	float tex = 23.0f / MESHCEILING_X;

	float tex2 = 23.0f / MESHCEILING_Z;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshCeiling->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 <= MESHCEILING_Z; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHCEILING_X; nCnt2++)
		{

			pVtx[nCnt].pos = D3DXVECTOR3(0.0f + ((MAX_WIDTH_CEILING / MESHCEILING_X) * nCnt2) - (MAX_WIDTH_CEILING * 0.5f),
				0.0f,
				MAX_HEIGHT_CEILING - ((MAX_HEIGHT_CEILING / MESHCEILING_Z) * nCnt1) - (MAX_HEIGHT_CEILING * 0.5f));

			//各頂点の法線の設定
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[nCnt].tex = D3DXVECTOR2(tex * nCnt2, tex2 * nCnt1);

			nCnt++;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshCeiling->Unlock();

	WORD* pIdx;//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点情報へのポインタを取得
	g_pIdxBuffMeshCeiling->Lock(0, 0, (void**)&pIdx, 0);

	int nCntIdx3 = MESHCEILING_X + 1;
	int Num = 0;
	int nCntNum = 0;

	for (int nCntIdx = 0; nCntIdx < MESHCEILING_Z; nCntIdx++)
	{
		for (int nCntIdx2 = 0; nCntIdx2 <= MESHCEILING_X; nCntIdx2++, nCntIdx3++, Num++)
		{

			pIdx[nCntNum] = nCntIdx3;

			pIdx[nCntNum + 1] = Num;

			nCntNum += 2;

		}

		//最後の行かどうか
		// NOTE: 最後の行に縮退ポリゴンが無い
		if (nCntIdx != MESHCEILING_Z - 1)
		{

			pIdx[nCntNum] = Num - 1;

			pIdx[nCntNum + 1] = nCntIdx3;

			nCntNum += 2;

		}

	}

	//インデックスバッファをアンロックする
	g_pIdxBuffMeshCeiling->Unlock();

}
//==================================
//メッシュフィールドの終了処理
//==================================
void UninitMeshCeiling(void)
{

	//インデックスバッファの解放
	if (g_pIdxBuffMeshCeiling != NULL)
	{
		g_pIdxBuffMeshCeiling->Release();
		g_pIdxBuffMeshCeiling = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureMeshCeiling != NULL)
	{
		g_pTextureMeshCeiling->Release();
		g_pTextureMeshCeiling = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshCeiling != NULL)
	{
		g_pVtxBuffMeshCeiling->Release();
		g_pVtxBuffMeshCeiling = NULL;
	}

}
//==================================
//メッシュフィールドの更新処理
//==================================
void UpdateMeshCeiling(void)
{



}
//==================================
//メッシュフィールドの描画処理
//==================================
void DrawMeshCeiling(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	// カリング設定を無効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshCeiling);

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCeiling.y, g_rotMeshCeiling.x, g_rotMeshCeiling.z);
	//D3DXMatrixMultiply(&g_mtxWorldMeshCeiling, &g_mtxWorldMeshCeiling, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCeiling.x, g_posMeshCeiling.y, g_posMeshCeiling.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCeiling, &g_mtxWorldMeshCeiling, &mtxTrans);

	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCeiling);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCeiling, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshCeiling);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshCeiling);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_VERTEX_CEILING, 0, MAX_PRIMITIVE_CEILING);

	// カリング設定を有効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}
