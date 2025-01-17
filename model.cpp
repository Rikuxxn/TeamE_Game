//=======================================
//
// モデル処理[model.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "model.h"
#include "player.h"
#include "input.h"
#include "enemy.h"
//#include "score.h"
//#include "particle.h"
//#include "sound.h"

//グローバル変数
Model g_aModel[MAX_MODEL];//モデル情報

//=============================
//モデルの初期化処理
//=============================
void InitModel(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//初期化
		g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
		g_aModel[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//移動量
		g_aModel[nCntModel].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//最小値
		g_aModel[nCntModel].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//最大値
		g_aModel[nCntModel].bUse = false;
		g_aModel[nCntModel].bScoreAdded = false;
		g_aModel[nCntModel].bSoundPlayed = false;
		g_aModel[nCntModel].nType = WALLTYPE_NORMAL;
	}

	for (int nCntModel2 = 0; nCntModel2 < MAX_MODEL; nCntModel2++)
	{

		//Xファイルの読み込み
		D3DXLoadMeshFromX(MODEL[nCntModel2],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aModel[nCntModel2].pBuffMat,
			NULL,
			&g_aModel[nCntModel2].dwNumMat,
			&g_aModel[nCntModel2].pMesh);

	}

	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	for (int nCntModel3 = 0; nCntModel3 < MAX_MODEL; nCntModel3++)
	{

		//頂点数の取得
		nNumVtx = g_aModel[nCntModel3].pMesh->GetNumVertices();

		//頂点フォーマットの取得
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[nCntModel3].pMesh->GetFVF());

		//頂点バッファのロック
		g_aModel[nCntModel3].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値最大値を取得
			if (vtx.x < g_aModel[nCntModel3].vtxMin.x)
			{
				g_aModel[nCntModel3].vtxMin.x = vtx.x;
			}
			else if (vtx.y < g_aModel[nCntModel3].vtxMin.y)
			{
				g_aModel[nCntModel3].vtxMin.y = vtx.y;
			}
			else if (vtx.z < g_aModel[nCntModel3].vtxMin.z)
			{
				g_aModel[nCntModel3].vtxMin.z = vtx.z;
			}

			if (vtx.x > g_aModel[nCntModel3].vtxMax.x)
			{
				g_aModel[nCntModel3].vtxMax.x = vtx.x;
			}
			else if (vtx.y > g_aModel[nCntModel3].vtxMax.y)
			{
				g_aModel[nCntModel3].vtxMax.y = vtx.y;
			}
			else if (vtx.z > g_aModel[nCntModel3].vtxMax.z)
			{
				g_aModel[nCntModel3].vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		g_aModel[nCntModel3].size.x = (g_aModel[nCntModel3].vtxMax.x - g_aModel[nCntModel3].vtxMin.x);
		g_aModel[nCntModel3].size.y = (g_aModel[nCntModel3].vtxMax.y - g_aModel[nCntModel3].vtxMin.y);
		g_aModel[nCntModel3].size.z = (g_aModel[nCntModel3].vtxMax.z - g_aModel[nCntModel3].vtxMin.z);

		//頂点バッファのアンロック
		g_aModel[nCntModel3].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_aModel[nCntModel3].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel3].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャファイルが存在する

				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aModel[nCntModel3].apTexture[nCntMat]);

			}
		}
	}
}
//=============================
//モデルの終了処理
//=============================
void UninitModel(void)
{
	//StopSound(SOUND_LABEL_MONEY);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].dwNumMat; nCntMat++)
		{
			//テクスチャの破棄
			if (g_aModel[nCntModel].apTexture[nCntMat] != NULL)
			{
				g_aModel[nCntModel].apTexture[nCntMat]->Release();
				g_aModel[nCntModel].apTexture[nCntMat] = NULL;
			}
		}

		//メッシュの破棄
		if (g_aModel[nCntModel].pMesh != NULL)
		{
			g_aModel[nCntModel].pMesh->Release();
			g_aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_aModel[nCntModel].pBuffMat != NULL)
		{
			g_aModel[nCntModel].pBuffMat->Release();
			g_aModel[nCntModel].pBuffMat = NULL;
		}
	}
}
//=============================
//モデルの更新処理
//=============================
void UpdateModel(void)
{

	//for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//{
	//	bool bTaskAllCmp = GetTaskAllCmp();
	//	bool bTaskCmp0 = GetTaskCmp0();
	//	bool bTaskCmp = GetTaskCmp();
	//	bool bTaskCmp2 = GetTaskCmp2();
	//	bool bTaskCmp3 = GetTaskCmp3();
	//	bool bTaskCmp4 = GetTaskCmp4();
	//	bool bTaskCmp5 = GetTaskCmp5();

	//	TASKBAR* pTask = GetTaskbar();

	//	if (bTaskAllCmp == true)
	//	{
	//		if (g_aModel[nCntModel].nType == WALLTYPE_DOOR)
	//		{
	//			if (g_aModel[nCntModel].pos.y >= 80)
	//			{
	//				g_aModel[nCntModel].move.y = 0.0f;
	//			}
	//			else
	//			{
	//				g_aModel[nCntModel].move.y += 0.2f;
	//			}
	//		}
	//	}

	//	if (bTaskCmp == true && bTaskCmp2 == true && bTaskCmp3)
	//	{
	//		if (g_aModel[nCntModel].nType == WALLTYPE_ROOM)
	//		{
	//			if (g_aModel[nCntModel].pos.y >= 80)
	//			{
	//				g_aModel[nCntModel].move.y = 0.0f;
	//			}
	//			else
	//			{
	//				g_aModel[nCntModel].move.y += 0.2f;
	//			}
	//		}
	//	}

	//	if (bTaskCmp4 == true)
	//	{
	//		if (g_aModel[nCntModel].bUse == true && g_aModel[nCntModel].nType == WALLTYPE_BOXTOP1)
	//		{
	//			// 音を一度だけ鳴らす
	//			if (!g_aModel[nCntModel].bSoundPlayed)
	//			{
	//				PlaySound(SOUND_LABEL_MONEY);
	//				g_aModel[nCntModel].bSoundPlayed = true; // 音再生済みフラグを立てる
	//			}

	//			if (g_aModel[nCntModel].rot.z <= -1.49f)
	//			{
	//				g_aModel[nCntModel].rot.z -= 0.0f;

	//				if (!g_aModel[nCntModel].bScoreAdded)
	//				{
	//					AddScore(100000);
	//					g_aModel[nCntModel].bScoreAdded = true;
	//				}
	//			}
	//			else if (g_aModel[nCntModel].rot.z < 1.5f)
	//			{
	//				g_aModel[nCntModel].rot.z -= 0.08f;
	//			}
	//		}
	//	}

	//	if (bTaskCmp5 == true)
	//	{
	//		if (g_aModel[nCntModel].bUse == true && g_aModel[nCntModel].nType == WALLTYPE_BOXTOP2)
	//		{
	//			// 音を一度だけ鳴らす
	//			if (!g_aModel[nCntModel].bSoundPlayed)
	//			{
	//				PlaySound(SOUND_LABEL_MONEY);
	//				g_aModel[nCntModel].bSoundPlayed = true;
	//			}

	//			if (g_aModel[nCntModel].rot.z >= 1.49f)
	//			{
	//				g_aModel[nCntModel].rot.z -= 0.0f;

	//				if (!g_aModel[nCntModel].bScoreAdded)
	//				{
	//					AddScore(100000);
	//					g_aModel[nCntModel].bScoreAdded = true;
	//				}
	//			}
	//			else if (g_aModel[nCntModel].rot.z < 1.5f)
	//			{
	//				g_aModel[nCntModel].rot.z += 0.08f;
	//			}
	//		}
	//	}

	//	//位置を更新
	//	g_aModel[nCntModel].pos.x += g_aModel[nCntModel].move.x;
	//	g_aModel[nCntModel].pos.y += g_aModel[nCntModel].move.y;
	//	g_aModel[nCntModel].pos.z += g_aModel[nCntModel].move.z;
	//}
}
//=============================
//モデルの描画処理
//=============================
void DrawModel(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{

		if (g_aModel[nCntModel].bUse == true)
		{

			//計算用マトリックス
			D3DXMATRIX mtxRot, mtxTrans;

			D3DMATERIAL9 matDef;//現在のマテリアル保存用

			D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);

			//ワールドマトリックスを設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);

			//現在のマテリアルの取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].dwNumMat; nCntMat++)
			{

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);

				//テクスチャの設定
				pDevice->SetTexture(0, g_aModel[nCntModel].apTexture[nCntMat]);

				//モデル(パーツ)の描画
				g_aModel[nCntModel].pMesh->DrawSubset(nCntMat);

			}

			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}

}
//=============================
//モデルの設定処理
//=============================
void SetModel(D3DXVECTOR3 pos,int nType)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{

			g_aModel[nCntModel].pos = pos;
			g_aModel[nCntModel].nType = nType;
			g_aModel[nCntModel].bUse = true;

			break;

		}
	}
}
//=============================
//モデルの当たり判定
//=============================
void CollisionModel(void)
{

	//bool bTask = false;//触れているかどうか

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		Player* pPlayer = GetPlayer();
		Enemy* pEnemy = GetEnemy();

		if (g_aModel[nCntModel].nType == WALLTYPE_NORMAL)
		{

			if (pPlayer->posOld.y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y &&
				pPlayer->posOld.y + pPlayer->size.y > g_aModel[nCntModel].pos.y)
			{

				//左右(X方向)の当たり判定
				if (pPlayer->pos.z - pPlayer->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
					pPlayer->pos.z + pPlayer->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
				{
					//左から右に当たった
					if (pPlayer->posOld.x + pPlayer->size.x / 2 < g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2 &&
						pPlayer->pos.x + pPlayer->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
					{
						pPlayer->pos.x = g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2 - pPlayer->size.x / 2 - 0.1f;
					}
					//右から左に当たった
					else if (pPlayer->posOld.x - pPlayer->size.x / 2 > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
						pPlayer->pos.x - pPlayer->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2)
					{
						pPlayer->pos.x = (g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2) + pPlayer->size.x / 2 + 0.1f;
					}

				}

				//前後(Z方向)の当たり判定
				if (pPlayer->pos.x - pPlayer->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
					pPlayer->pos.x + pPlayer->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
				{

					//手前から当たった
					if (pPlayer->posOld.z + pPlayer->size.z / 2 < g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2 &&
						pPlayer->pos.z + pPlayer->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
					{
						pPlayer->pos.z = (g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2) - pPlayer->size.z / 2 - 0.1f;
					}
					//奥から当たった
					else if (pPlayer->posOld.z - pPlayer->size.z / 2 > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
						pPlayer->pos.z - pPlayer->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2)
					{
						pPlayer->pos.z = (g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2) + pPlayer->size.z / 2 + 0.1f;
					}

				}

				//縦(Y方向)の当たり判定
				if (pPlayer->posOld.x - pPlayer->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
					pPlayer->pos.x + pPlayer->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
				{

					if (pPlayer->posOld.z - pPlayer->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
						pPlayer->pos.z + pPlayer->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
					{

						//上から下に当たった
						if (pPlayer->posOld.y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y &&
							pPlayer->pos.y > g_aModel[nCntModel].pos.y - g_aModel[nCntModel].size.y)
						{
							pPlayer->pos.y = (g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y / 2) + pPlayer->size.y / 2 - 0.9f;
							pPlayer->move.y = 0.0f;
						}
						//下から上に当たった
						if (pPlayer->posOld.y - pPlayer->size.y / 2 < g_aModel[nCntModel].pos.y / 2 &&
							pPlayer->pos.y - pPlayer->size.y / 2 > g_aModel[nCntModel].pos.y / 2)
						{
							pPlayer->pos.y = (g_aModel[nCntModel].pos.y - pPlayer->size.y);
							pPlayer->move.y = 0.0f;
						}

					}
				}
			}

		}




		//敵とモデルの当たり判定
		if (g_aModel[nCntModel].nType == WALLTYPE_NORMAL)
		{

			if (pEnemy->posOld.y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y &&
				pEnemy->posOld.y + pEnemy->size.y > g_aModel[nCntModel].pos.y)
			{

				//左右(X方向)の当たり判定
				if (pEnemy->pos.z - pEnemy->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
					pEnemy->pos.z + pEnemy->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
				{
					//左から右に当たった
					if (pEnemy->posOld.x + pEnemy->size.x / 2 < g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2 &&
						pEnemy->pos.x + pEnemy->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
					{
						pEnemy->pos.x = g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2 - pEnemy->size.x / 2 - 0.1f;
					}
					//右から左に当たった
					else if (pEnemy->posOld.x - pEnemy->size.x / 2 > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
						pEnemy->pos.x - pEnemy->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2)
					{
						pEnemy->pos.x = (g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2) + pEnemy->size.x / 2 + 0.1f;
					}

				}

				//前後(Z方向)の当たり判定
				if (pEnemy->pos.x - pEnemy->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
					pEnemy->pos.x + pEnemy->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
				{

					//手前から当たった
					if (pEnemy->posOld.z + pEnemy->size.z / 2 < g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2 &&
						pEnemy->pos.z + pEnemy->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
					{
						pEnemy->pos.z = (g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2) - pEnemy->size.z / 2 - 0.1f;
					}
					//奥から当たった
					else if (pEnemy->posOld.z - pEnemy->size.z / 2 > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
						pEnemy->pos.z - pEnemy->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2)
					{
						pEnemy->pos.z = (g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2) + pEnemy->size.z / 2 + 0.1f;
					}

				}

				//縦(Y方向)の当たり判定
				if (pEnemy->posOld.x - pEnemy->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
					pEnemy->pos.x + pEnemy->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
				{

					if (pEnemy->posOld.z - pEnemy->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
						pEnemy->pos.z + pEnemy->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
					{

						//上から下に当たった
						if (pEnemy->posOld.y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y &&
							pEnemy->pos.y > g_aModel[nCntModel].pos.y - g_aModel[nCntModel].size.y)
						{
							pEnemy->pos.y = (g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y / 2) + pEnemy->size.y / 2 - 0.9f;
							pEnemy->move.y = 0.0f;
						}
						//下から上に当たった
						if (pEnemy->posOld.y - pEnemy->size.y / 2 < g_aModel[nCntModel].pos.y / 2 &&
							pEnemy->pos.y - pEnemy->size.y / 2 > g_aModel[nCntModel].pos.y / 2)
						{
							pEnemy->pos.y = (g_aModel[nCntModel].pos.y - pEnemy->size.y);
							pEnemy->move.y = 0.0f;
						}

					}
				}
			}

		}

	}

	//return bTask;

}