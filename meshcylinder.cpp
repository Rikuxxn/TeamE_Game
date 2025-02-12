//=======================================
//
// メッシュシリンダー処理[meshcylinder.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "meshcylinder.h"
#include "block.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMeshcylinder = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshcylinder = NULL;//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshcylinder = NULL;//インデックスバッファへのポインタ
Cylinder g_Cylinder[MAX_CYLINDER]; // 複数のメッシュシリンダーを管理

//==================================
//メッシュシリンダーの初期化処理
//==================================
void InitMeshcylinder(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_CYLINDER; nCnt++)
	{
		g_Cylinder[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Cylinder[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Cylinder[nCnt].bUse = false;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHCYLINDER_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshcylinder,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\cylinder.png",
		&g_pTextureMeshcylinder);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHCYLINDER_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshcylinder,
		NULL);

	VERTEX_3D* pVtx = NULL;//頂点情報へのポインタ

	int nCnt = 0;
	float tex = 1.0f / MESHCYLINDER_X;
	float tex2 = 1.0f / MESHCYLINDER_Z;
	int radius = 15;//半径
	D3DXVECTOR3 nor;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshcylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < MESHCYLINDER_V + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < MESHCYLINDER_H + 1; nCntH++)
		{
			float Angle = (D3DX_PI * 2.0f) / MESHCYLINDER_H * nCntH;

			pVtx[nCnt].pos = D3DXVECTOR3(sinf(Angle) * radius, MESHCYLINDER_HEIGHT * nCntV, cosf(Angle) * radius);

			nor.x = pVtx[nCnt].pos.x - 0.0f;
			nor.y = pVtx[nCnt].pos.y - 0.0f;
			nor.z = pVtx[nCnt].pos.z - 0.0f;

			//法線の正規化
			D3DXVec3Normalize(&pVtx[nCnt].nor, &nor);

			////各頂点の法線の設定
			//pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			//テクスチャ座標の設定
			pVtx[nCnt].tex = D3DXVECTOR2(/*tex * */nCntV, /*tex2 * */nCntH);

			nCnt++;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshcylinder->Unlock();

	WORD* pIdx;//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点情報へのポインタを取得
	g_pIdxBuffMeshcylinder->Lock(0, 0, (void**)&pIdx, 0);

	int nCntIdx3 = MESHCYLINDER_X + 1;
	int Num = 0;
	int nCntNum = 0;

	//インデックスの設定
	for (int nCntIdx = 0; nCntIdx < MESHCYLINDER_Z; nCntIdx++)
	{
		for (int nCntIdx2 = 0; nCntIdx2 <= MESHCYLINDER_X; nCntIdx2++, nCntIdx3++, Num++)
		{
			pIdx[nCntNum] = nCntIdx3;

			pIdx[nCntNum + 1] = Num;

			nCntNum += 2;
		}

		// 最後の行かどうか
		// NOTE: 最後の行に縮退ポリゴンが無い
		if (nCntIdx != MESHCYLINDER_Z - 1)
		{
			pIdx[nCntNum] = Num - 1;

			pIdx[nCntNum + 1] = nCntIdx3;

			nCntNum += 2;
		}
	}


	//インデックスバッファをアンロックする
	g_pIdxBuffMeshcylinder->Unlock();

}
//==================================
//メッシュシリンダーの終了処理
//==================================
void UninitMeshcylinder(void)
{

	//インデックスバッファの解放
	if (g_pIdxBuffMeshcylinder != NULL)
	{
		g_pIdxBuffMeshcylinder->Release();
		g_pIdxBuffMeshcylinder = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureMeshcylinder != NULL)
	{
		g_pTextureMeshcylinder->Release();
		g_pTextureMeshcylinder = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshcylinder != NULL)
	{
		g_pVtxBuffMeshcylinder->Release();
		g_pVtxBuffMeshcylinder = NULL;
	}

	// シリンダーのリセット
	for (int i = 0; i < MAX_CYLINDER; i++)
	{
		g_Cylinder[i].bUse = false;
	}
}
//==================================
//メッシュシリンダーの更新処理
//==================================
void UpdateMeshcylinder(void)
{
	Block* pBlock = GetBlock();
	int cylinderIndex = 0;

	// 一度すべてのシリンダーを未使用状態にする
	for (int i = 0; i < MAX_CYLINDER; i++)
	{
		g_Cylinder[i].bUse = false;
	}

	// ブロックをスキャンして、必要なシリンダーだけを再登録
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (pBlock[nCnt].bUse == true && (pBlock[nCnt].nType == BLOCKTYPE_FUSE || 
			pBlock[nCnt].nType == BLOCKTYPE_BALL || pBlock[nCnt].nType == BLOCKTYPE_BEAR))
		{
			if (cylinderIndex < MAX_CYLINDER)
			{
				g_Cylinder[cylinderIndex].pos = pBlock[nCnt].pos;
				g_Cylinder[cylinderIndex].bUse = true;
				cylinderIndex++;
			}
		}
	}

	// Y軸回転処理
	for (int i = 0; i < MAX_CYLINDER; i++)
	{
		if (g_Cylinder[i].bUse)
		{
			// **回転処理**
			g_Cylinder[i].rot.y += D3DX_PI * 0.005f;  // 回転スピード

			if (g_Cylinder[i].rot.y > D3DX_PI * 2.0f)
			{
				g_Cylinder[i].rot.y -= D3DX_PI * 2.0f;
			}
		}
	}
}
//==================================
//メッシュシリンダーの描画処理
//==================================
void DrawMeshcylinder(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCnt = 0; nCnt < MAX_CYLINDER; nCnt++)
	{
		if (g_Cylinder[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Cylinder[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Cylinder[nCnt].rot.y, g_Cylinder[nCnt].rot.x, g_Cylinder[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Cylinder[nCnt].mtxWorld, &g_Cylinder[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Cylinder[nCnt].pos.x, g_Cylinder[nCnt].pos.y, g_Cylinder[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Cylinder[nCnt].mtxWorld, &g_Cylinder[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスを設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Cylinder[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshcylinder, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshcylinder);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshcylinder);

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHCYLINDER_VERTEX, 0, MESHCYLINDER_PRIMITIVE);
		}
	}
}
//==================================
//メッシュシリンダーの設定処理
//==================================
void SetMeshcylinder(D3DXVECTOR3 pos)
{
	int i;

	// すでに同じ位置にシリンダーがあるかチェック
	for (i = 0; i < MAX_CYLINDER; i++)
	{
		if (g_Cylinder[i].bUse &&
			g_Cylinder[i].pos.x == pos.x &&
			g_Cylinder[i].pos.z == pos.z)
		{
			return; // すでにある場合は追加しない
		}
	}

	// 空いているスロットを探して新規登録
	for (i = 0; i < MAX_CYLINDER; i++)
	{
		if (!g_Cylinder[i].bUse)
		{
			g_Cylinder[i].pos = pos;
			g_Cylinder[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Cylinder[i].bUse = true;
			return;
		}
	}
}