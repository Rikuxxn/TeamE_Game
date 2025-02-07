//==============================================
//
// メッシュフィールド処理[meshfield.cpp]
// Author : TANEKAWA RIKU
//
//==============================================
#include "main.h"
#include "meshfield.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;		// インデックスバッファへのポインタ

D3DXVECTOR3 g_posMeshfield;								// 位置
D3DXVECTOR3 g_rotMeshfield;								// 向き
D3DXMATRIX g_mtxWorldMeshfield;							// ワールドマトリックス

//==================================
//メッシュフィールドの初期化処理
//==================================
void InitMeshfield(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ground.png",
		&g_pTextureMeshfield);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	VERTEX_3D* pVtx = NULL;//頂点情報へのポインタ

	int nCnt = 0;
	float tex = 23.0f / MESHFIELD_X;

	float tex2 = 23.0f / MESHFIELD_Z;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 <= MESHFIELD_Z; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHFIELD_X; nCnt2++)
		{

			pVtx[nCnt].pos = D3DXVECTOR3(0.0f + ((MAX_WIDTH / MESHFIELD_X) * nCnt2) - (MAX_WIDTH * 0.5f),
				0.0f,
				MAX_HEIGHT - ((MAX_HEIGHT / MESHFIELD_Z) * nCnt1) - (MAX_HEIGHT * 0.5f));

			//各頂点の法線の設定
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[nCnt].tex = D3DXVECTOR2(tex * nCnt2, tex2 * nCnt1);

			nCnt++;
		}
	}

	//pVtx[6].pos.y = 50.0f;
	//pVtx[12].pos.y = 50.0f;

	//頂点バッファをアンロックする
	g_pVtxBuffMeshfield->Unlock();

	WORD* pIdx;//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点情報へのポインタを取得
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	int nCntIdx3 = MESHFIELD_X + 1;
	int Num = 0;
	int nCntNum = 0;

	for (int nCntIdx = 0; nCntIdx < MESHFIELD_Z; nCntIdx++)
	{
		for (int nCntIdx2 = 0; nCntIdx2 <= MESHFIELD_X; nCntIdx2++, nCntIdx3++, Num++)
		{

			pIdx[nCntNum] = nCntIdx3;

			pIdx[nCntNum + 1] = Num;

			nCntNum += 2;

		}

		//最後の行かどうか
		// NOTE: 最後の行に縮退ポリゴンが無い
		if (nCntIdx != MESHFIELD_Z - 1)
		{

			pIdx[nCntNum] = Num - 1;

			pIdx[nCntNum + 1] = nCntIdx3;

			nCntNum += 2;

		}

	}

	////インデックスの設定
	//pIdx[0] = 3;
	//pIdx[1] = 0;

	//pIdx[2] = 4;
	//pIdx[3] = 1;

	//pIdx[4] = 5;
	//pIdx[5] = 2;

	//pIdx[6] = 2;
	//pIdx[7] = 6;

	//pIdx[8] = 6;
	//pIdx[9] = 3;

	//pIdx[10] = 7;
	//pIdx[11] = 4;

	//pIdx[12] = 8;
	//pIdx[13] = 5;

	//インデックスバッファをアンロックする
	g_pIdxBuffMeshfield->Unlock();

}
//==================================
//メッシュフィールドの終了処理
//==================================
void UninitMeshfield(void)
{

	//インデックスバッファの解放
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

}
//==================================
//メッシュフィールドの更新処理
//==================================
void UpdateMeshfield(void)
{



}
//==================================
//メッシュフィールドの描画処理
//==================================
void DrawMeshfield(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	//D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshfield);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_VERTEX, 0, MAX_PRIMITIVE);

}
