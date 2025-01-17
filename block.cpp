//=======================================
//
// ブロック配置処理[block.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "block.h"
#include "player.h"
#include "input.h"
#include "enemy.h"
#include "edit.h"
#include <stdio.h>

//グローバル変数
Block g_aBlock[MAX_BLOCK];//ブロック情報
bool g_bExit;//出口に入ったか

//=============================
//ブロックの初期化処理
//=============================
void InitBlock(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//初期化
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//移動量
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].bScoreAdded = false;
		g_aBlock[nCntBlock].bSoundPlayed = false;
		g_aBlock[nCntBlock].nType = BLOCKTYPE_NORMAL;

		for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX(BLOCK[nCnt],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aBlock[nCntBlock].blockinfo[nCnt].pBuffMat,
				NULL,
				&g_aBlock[nCntBlock].blockinfo[nCnt].dwNumMat,
				&g_aBlock[nCntBlock].blockinfo[nCnt].pMesh);


			int nNumVtx;//頂点数
			DWORD sizeFVF;//頂点フォーマットのサイズ
			BYTE* pVtxBuff;//頂点バッファへのポインタ

			//頂点数の取得

			nNumVtx = g_aBlock[nCntBlock].blockinfo[nCnt].pMesh->GetNumVertices();

			//頂点フォーマットの取得
			sizeFVF = D3DXGetFVFVertexSize(g_aBlock[nCntBlock].blockinfo[nCnt].pMesh->GetFVF());

			//頂点バッファのロック
			g_aBlock[nCntBlock].blockinfo[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				if (vtx.x < g_aBlock[nCntBlock].vtxMin.x)
				{
					g_aBlock[nCntBlock].vtxMin.x = vtx.x;
				}
				if (vtx.y < g_aBlock[nCntBlock].vtxMin.y)
				{
					g_aBlock[nCntBlock].vtxMin.y = vtx.y;
				}
				if (vtx.z < g_aBlock[nCntBlock].vtxMin.z)
				{
					g_aBlock[nCntBlock].vtxMin.z = vtx.z;
				}

				if (vtx.x > g_aBlock[nCntBlock].vtxMax.x)
				{
					g_aBlock[nCntBlock].vtxMax.x = vtx.x;
				}
				if (vtx.y > g_aBlock[nCntBlock].vtxMax.y)
				{
					g_aBlock[nCntBlock].vtxMax.y = vtx.y;
				}
				if (vtx.z > g_aBlock[nCntBlock].vtxMax.z)
				{
					g_aBlock[nCntBlock].vtxMax.z = vtx.z;
				}

				//頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}

			g_aBlock[nCntBlock].size.x = (g_aBlock[nCntBlock].vtxMax.x - g_aBlock[nCntBlock].vtxMin.x);
			g_aBlock[nCntBlock].size.y = (g_aBlock[nCntBlock].vtxMax.y - g_aBlock[nCntBlock].vtxMin.y);
			g_aBlock[nCntBlock].size.z = (g_aBlock[nCntBlock].vtxMax.z - g_aBlock[nCntBlock].vtxMin.z);

			//頂点バッファのアンロック
			g_aBlock[nCntBlock].blockinfo[nCnt].pMesh->UnlockVertexBuffer();

			D3DXMATERIAL* pMat;//マテリアルへのポインタ

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].blockinfo[nCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].blockinfo[nCnt].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//テクスチャファイルが存在する

					//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_aBlock[nCntBlock].blockinfo[nCnt].apTexture[nCntMat]);

				}
			}
		}
	}

	g_bExit = false;

}
//=============================
//ブロックの終了処理
//=============================
void UninitBlock(void)
{
	//StopSound(SOUND_LABEL_MONEY);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
		{

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].blockinfo[nCnt].dwNumMat; nCntMat++)
			{
				//テクスチャの破棄
				if (g_aBlock[nCntBlock].blockinfo[nCnt].apTexture[nCntMat] != NULL)
				{
					g_aBlock[nCntBlock].blockinfo[nCnt].apTexture[nCntMat]->Release();
					g_aBlock[nCntBlock].blockinfo[nCnt].apTexture[nCntMat] = NULL;
				}
			}

			//メッシュの破棄
			if (g_aBlock[nCntBlock].blockinfo[nCnt].pMesh != NULL)
			{
				g_aBlock[nCntBlock].blockinfo[nCnt].pMesh->Release();
				g_aBlock[nCntBlock].blockinfo[nCnt].pMesh = NULL;
			}

			//マテリアルの破棄
			if (g_aBlock[nCntBlock].blockinfo[nCnt].pBuffMat != NULL)
			{
				g_aBlock[nCntBlock].blockinfo[nCnt].pBuffMat->Release();
				g_aBlock[nCntBlock].blockinfo[nCnt].pBuffMat = NULL;
			}
		}
	}
	
}
//=============================
//ブロックの更新処理
//=============================
void UpdateBlock(void)
{
	//UpdateEdit();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{

		////位置を更新
		//g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
		//g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;
		//g_aBlock[nCntBlock].pos.z += g_aBlock[nCntBlock].move.z;
	}

}
//=============================
//ブロックの描画処理
//=============================
void DrawBlock(void)
{
	//DrawEdit();

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	//{
		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse == true) 
			{
				int nType = g_aBlock[nCntBlock].nType;

				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aBlock[nCntBlock].mtxWorld);

				// 向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBlock[nCntBlock].rot.y, g_aBlock[nCntBlock].rot.x, g_aBlock[nCntBlock].rot.z);
				D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
				D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxTrans);

				// ワールドマトリックスを設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aBlock[nCntBlock].mtxWorld);

				// 現在のマテリアルの取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].blockinfo[nType].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].blockinfo[nType].dwNumMat; nCntMat++) {
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャの設定
					pDevice->SetTexture(0, g_aBlock[nCntBlock].blockinfo[nType].apTexture[nCntMat]);

					// モデル(パーツ)の描画
					g_aBlock[nCntBlock].blockinfo[nType].pMesh->DrawSubset(nCntMat);
				}

				// 保存していたマテリアルを戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	//}
	
}
//=============================
//ブロックの設定処理
//=============================
void SetBlock(D3DXVECTOR3 pos, int nType)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{

			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bUse = true;

			break;

		}
	}
}
//=============================
//ブロックの当たり判定
//=============================
void CollisionBlock(void)
{

	//bool bTask = false;//触れているかどうか

	//for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	//{
		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			Player* pPlayer = GetPlayer();
			Enemy* pEnemy = GetEnemy();

			if (g_aBlock[nCntBlock].bUse == true)
			{

				if (g_aBlock[nCntBlock].nType == BLOCKTYPE_NORMAL)
				{

					if (pPlayer->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
						pPlayer->posOld.y + pPlayer->size.y > g_aBlock[nCntBlock].pos.y)
					{

						//左右(X方向)の当たり判定
						if (pPlayer->pos.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
							pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
						{
							//左から右に当たった
							if (pPlayer->posOld.x + pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 &&
								pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
							{
								pPlayer->pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 - pPlayer->size.x / 2 - 0.1f;
							}
							//右から左に当たった
							else if (pPlayer->posOld.x - pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
								pPlayer->pos.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2)
							{
								pPlayer->pos.x = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2) + pPlayer->size.x / 2 + 0.1f;
							}

						}

						//前後(Z方向)の当たり判定
						if (pPlayer->pos.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							//手前から当たった
							if (pPlayer->posOld.z + pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{
								pPlayer->pos.z = (g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2) - pPlayer->size.z / 2 - 0.1f;
							}
							//奥から当たった
							else if (pPlayer->posOld.z - pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2)
							{
								pPlayer->pos.z = (g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2) + pPlayer->size.z / 2 + 0.1f;
							}

						}

						//縦(Y方向)の当たり判定
						if (pPlayer->posOld.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							if (pPlayer->posOld.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{

								//上から下に当たった
								if (pPlayer->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
									pPlayer->pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].size.y)
								{
									pPlayer->pos.y = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y / 2) + pPlayer->size.y / 2 - 0.9f;
									pPlayer->move.y = 0.0f;
								}
								//下から上に当たった
								if (pPlayer->posOld.y - pPlayer->size.y / 2 < g_aBlock[nCntBlock].pos.y / 2 &&
									pPlayer->pos.y - pPlayer->size.y / 2 > g_aBlock[nCntBlock].pos.y / 2)
								{
									pPlayer->pos.y = (g_aBlock[nCntBlock].pos.y - pPlayer->size.y);
									pPlayer->move.y = 0.0f;
								}

							}
						}
					}

				}

				if (g_aBlock[nCntBlock].nType == BLOCKTYPE_DOOR)
				{

					if (pPlayer->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
						pPlayer->posOld.y + pPlayer->size.y > g_aBlock[nCntBlock].pos.y)
					{

						//左右(X方向)の当たり判定
						if (pPlayer->pos.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
							pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
						{
							//左から右に当たった
							if (pPlayer->posOld.x + pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 &&
								pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
							{
								pPlayer->pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 - pPlayer->size.x / 2 - 0.1f;
							}
							//右から左に当たった
							else if (pPlayer->posOld.x - pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
								pPlayer->pos.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2)
							{
								pPlayer->pos.x = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2) + pPlayer->size.x / 2 + 0.1f;
							}

						}

						//前後(Z方向)の当たり判定
						if (pPlayer->pos.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							//手前から当たった
							if (pPlayer->posOld.z + pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{
								pPlayer->pos.z = (g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2) - pPlayer->size.z / 2 - 0.1f;
							}
							//奥から当たった
							else if (pPlayer->posOld.z - pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2)
							{
								pPlayer->pos.z = (g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2) + pPlayer->size.z / 2 + 0.1f;
							}

						}

						//縦(Y方向)の当たり判定
						if (pPlayer->posOld.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							if (pPlayer->posOld.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{

								//上から下に当たった
								if (pPlayer->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
									pPlayer->pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].size.y)
								{
									pPlayer->pos.y = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y / 2) + pPlayer->size.y / 2 - 0.9f;
									pPlayer->move.y = 0.0f;
								}
								//下から上に当たった
								if (pPlayer->posOld.y - pPlayer->size.y / 2 < g_aBlock[nCntBlock].pos.y / 2 &&
									pPlayer->pos.y - pPlayer->size.y / 2 > g_aBlock[nCntBlock].pos.y / 2)
								{
									pPlayer->pos.y = (g_aBlock[nCntBlock].pos.y - pPlayer->size.y);
									pPlayer->move.y = 0.0f;
								}

							}
						}
					}

				}



				//敵とモデルの当たり判定
				if (g_aBlock[nCntBlock].nType == BLOCKTYPE_NORMAL)
				{

					if (pEnemy->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
						pEnemy->posOld.y + pEnemy->size.y > g_aBlock[nCntBlock].pos.y)
					{

						//左右(X方向)の当たり判定
						if (pEnemy->pos.z - pEnemy->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
							pEnemy->pos.z + pEnemy->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
						{
							//左から右に当たった
							if (pEnemy->posOld.x + pEnemy->size.x / 2 < g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 &&
								pEnemy->pos.x + pEnemy->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
							{
								pEnemy->pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 - pEnemy->size.x / 2 - 0.1f;
							}
							//右から左に当たった
							else if (pEnemy->posOld.x - pEnemy->size.x / 2 > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
								pEnemy->pos.x - pEnemy->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2)
							{
								pEnemy->pos.x = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2) + pEnemy->size.x / 2 + 0.1f;
							}

						}

						//前後(Z方向)の当たり判定
						if (pEnemy->pos.x - pEnemy->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pEnemy->pos.x + pEnemy->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							//手前から当たった
							if (pEnemy->posOld.z + pEnemy->size.z / 2 < g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2 &&
								pEnemy->pos.z + pEnemy->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{
								pEnemy->pos.z = (g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2) - pEnemy->size.z / 2 - 0.1f;
							}
							//奥から当たった
							else if (pEnemy->posOld.z - pEnemy->size.z / 2 > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pEnemy->pos.z - pEnemy->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2)
							{
								pEnemy->pos.z = (g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2) + pEnemy->size.z / 2 + 0.1f;
							}

						}

						//縦(Y方向)の当たり判定
						if (pEnemy->posOld.x - pEnemy->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pEnemy->pos.x + pEnemy->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							if (pEnemy->posOld.z - pEnemy->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pEnemy->pos.z + pEnemy->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{

								//上から下に当たった
								if (pEnemy->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
									pEnemy->pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].size.y)
								{
									pEnemy->pos.y = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y / 2) + pEnemy->size.y / 2 - 0.9f;
									pEnemy->move.y = 0.0f;
								}
								//下から上に当たった
								if (pEnemy->posOld.y - pEnemy->size.y / 2 < g_aBlock[nCntBlock].pos.y / 2 &&
									pEnemy->pos.y - pEnemy->size.y / 2 > g_aBlock[nCntBlock].pos.y / 2)
								{
									pEnemy->pos.y = (g_aBlock[nCntBlock].pos.y - pEnemy->size.y);
									pEnemy->move.y = 0.0f;
								}

							}
						}
					}

				}
			}
		}
	//}
	//return bTask;

}
//============================================
//ブロックの取得
//============================================
Block* GetBlock(void)
{
	return &g_aBlock[0];
}
//======================================================
//出口判定
//======================================================
bool GetExit(void)
{
	return g_bExit;
}
