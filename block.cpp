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
#include "ui.h"
#include "camera.h"

//グローバル変数
Block g_aBlock[MAX_BLOCK];		//ブロック情報
Block g_info[BLOCKTYPE_MAX];	//ブロックの素材情報

bool g_bExit;					//出口に入ったか

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
		// 初期化
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].bScoreAdded = false;
		g_aBlock[nCntBlock].bSoundPlayed = false;
		g_aBlock[nCntBlock].bInsight = false;
		g_aBlock[nCntBlock].nType = BLOCKTYPE_WALL;
	}

	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(BLOCK[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_info[nCnt].blockinfo[nCnt].pBuffMat,
			NULL,
			&g_info[nCnt].blockinfo[nCnt].dwNumMat,
			&g_info[nCnt].blockinfo[nCnt].pMesh);

	}

	int nNumVtx;					//頂点数
	DWORD sizeFVF;					//頂点フォーマットのサイズ
	BYTE* pVtxBuff;					//頂点バッファへのポインタ

	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		g_info[nCnt].bUse = true;

		//頂点数の取得
		nNumVtx = g_info[nCnt].blockinfo[nCnt].pMesh->GetNumVertices();

		//頂点フォーマットの取得
		sizeFVF = D3DXGetFVFVertexSize(g_info[nCnt].blockinfo[nCnt].pMesh->GetFVF());

		//頂点バッファのロック
		g_info[nCnt].blockinfo[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (vtx.x < g_info[nCnt].blockinfo[nCnt].vtxMin.x)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMin.x = vtx.x;
			}
			if (vtx.y < g_info[nCnt].blockinfo[nCnt].vtxMin.y)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMin.y = vtx.y;
			}
			if (vtx.z < g_info[nCnt].blockinfo[nCnt].vtxMin.z)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMin.z = vtx.z;
			}

			if (vtx.x > g_info[nCnt].blockinfo[nCnt].vtxMax.x)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMax.x = vtx.x;
			}
			if (vtx.y > g_info[nCnt].blockinfo[nCnt].vtxMax.y)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMax.y = vtx.y;
			}
			if (vtx.z > g_info[nCnt].blockinfo[nCnt].vtxMax.z)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		g_info[nCnt].size.x = (g_info[nCnt].blockinfo[nCnt].vtxMax.x - g_info[nCnt].blockinfo[nCnt].vtxMin.x);
		g_info[nCnt].size.y = (g_info[nCnt].blockinfo[nCnt].vtxMax.y - g_info[nCnt].blockinfo[nCnt].vtxMin.y);
		g_info[nCnt].size.z = (g_info[nCnt].blockinfo[nCnt].vtxMax.z - g_info[nCnt].blockinfo[nCnt].vtxMin.z);

		//頂点バッファのアンロック
		g_info[nCnt].blockinfo[nCnt].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_info[nCnt].blockinfo[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_info[nCnt].blockinfo[nCnt].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャファイルが存在する

				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat]);

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

	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{

		for (int nCntMat = 0; nCntMat < (int)g_info[nCnt].blockinfo[nCnt].dwNumMat; nCntMat++)
		{
			//テクスチャの破棄
			if (g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat] != NULL)
			{
				g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat]->Release();
				g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat] = NULL;
			}
		}

		//メッシュの破棄
		if (g_info[nCnt].blockinfo[nCnt].pMesh != NULL)
		{
			g_info[nCnt].blockinfo[nCnt].pMesh->Release();
			g_info[nCnt].blockinfo[nCnt].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_info[nCnt].blockinfo[nCnt].pBuffMat != NULL)
		{
			g_info[nCnt].blockinfo[nCnt].pBuffMat->Release();
			g_info[nCnt].blockinfo[nCnt].pBuffMat = NULL;
		}
	}
	
}
//=============================
//ブロックの更新処理
//=============================
void UpdateBlock(void)
{

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		Player* pPlayer = GetPlayer(); // プレイヤー情報の取得
		Camera* pCamera = GetCamera();

		if (g_aBlock[nCntBlock].bUse == true)
		{
			// 回転角度の正規化
			if (g_aBlock[nCntBlock].rot.y > D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.y -= D3DX_PI * 2.0f;
			}
			if (g_aBlock[nCntBlock].rot.y < -D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.y += D3DX_PI * 2.0f;
			}

			if (g_aBlock[nCntBlock].rot.x > D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.x -= D3DX_PI * 2.0f;
			}
			if (g_aBlock[nCntBlock].rot.x < -D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.x += D3DX_PI * 2.0f;
			}

			if (g_aBlock[nCntBlock].rot.z > D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.z -= D3DX_PI * 2.0f;
			}
			if (g_aBlock[nCntBlock].rot.z < -D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.z += D3DX_PI * 2.0f;
			}


			// 視線方向を計算
			D3DXMATRIX rotMatrix;
			D3DXMatrixRotationYawPitchRoll(&rotMatrix, pCamera->rot.y, pCamera->rot.x, 0.0f);
			pPlayer->forward = D3DXVECTOR3(rotMatrix._31, rotMatrix._32, rotMatrix._33); // Z軸が視線方向

			// --- ここからレイキャスト処理 ---
			D3DXVECTOR3 rayOrigin, rayDirection;
			GetRayFromScreenCenter(&rayOrigin, &rayDirection);

			Block* pBlock = RaycastToBlocks(pPlayer->pos, pPlayer->forward);

			if (pBlock != NULL)
			{
				// インタラクト範囲内のブロックに照準を合わせた場合の処理
				HandleBlockInteraction(pBlock);
				g_aBlock[nCntBlock].bInsight = true;

			}
			else
			{
				// 照準範囲内にブロックがない場合
				for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
				{
					g_aBlock[nCntBlock].bInsight = false;
				}
			}

			////位置を更新
			//g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
			//g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;
			//g_aBlock[nCntBlock].pos.z += g_aBlock[nCntBlock].move.z;
		}
	}
}
//=============================
//ブロックの描画処理
//=============================
void DrawBlock(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

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


			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].blockinfo[nType].dwNumMat; nCntMat++) 
			{
				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].blockinfo[nType].pBuffMat->GetBufferPointer();

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
	
}
//=============================
//ブロックの設定処理
//=============================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			// 現在の g_info[nType] をコピー
			g_aBlock[nCntBlock] = g_info[nType];

			// 明示的に回転情報をリセットして設定
			g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].rot = rot;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bUse = true;

			break;
		}
	}
}
//=============================
//ブロックの当たり判定
//=============================
void CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, D3DXVECTOR3* pSize)
{

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse)
		{
			// ブロック OBB の情報を取得
			D3DXMATRIX blockWorld = g_aBlock[nCntBlock].mtxWorld;
			D3DXVECTOR3 blockSize = g_aBlock[nCntBlock].size;

			// プレイヤー OBB の情報を取得
			D3DXMATRIX playerWorld;
			D3DXMatrixTranslation(&playerWorld, pPos->x, pPos->y, pPos->z);

			if (g_aBlock[nCntBlock].nType == BLOCKTYPE_UFOCATCHER1)
			{
				// OBB 衝突判定
				if (CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
				{
					// Z軸の衝突補正
					pPos->z = pPosOld->z;
					playerWorld._43 = pPos->z;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// 衝突解消できたら、Z軸方向の移動量を滑らかに減衰
						pMove->z *= 0.5f;  // Z軸移動を減速して滑りを再現
						continue;
					}

					// X軸の衝突補正
					pPos->x = pPosOld->x;
					playerWorld._41 = pPos->x;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// 衝突解消できたら、X軸方向の移動量を滑らかに減衰
						pMove->x *= 0.5f;  // X軸移動を減速して滑りを再現
						continue;
					}

					// Y軸の衝突補正
					pPos->y = pPosOld->y;
					playerWorld._42 = pPos->y;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// 衝突解消できたら、Y軸方向の移動量を滑らかに減衰
						pMove->y *= 0.5f;  // Y軸移動を減速して滑りを再現
						continue;
					}

					// 最後に全軸を停止 (衝突解消できなかった場合)
					pMove->x = 0.0f;
					pMove->y = 0.0f;
					pMove->z = 0.0f;
				}
			}

			if (g_aBlock[nCntBlock].nType == BLOCKTYPE_ARCADE1)
			{
				// OBB 衝突判定
				if (CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
				{
					// Z軸の衝突補正
					pPos->z = pPosOld->z;
					playerWorld._43 = pPos->z;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// 衝突解消できたら、Z軸方向の移動量を滑らかに減衰
						pMove->z *= 0.5f;  // Z軸移動を減速して滑りを再現
						continue;
					}

					// X軸の衝突補正
					pPos->x = pPosOld->x;
					playerWorld._41 = pPos->x;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// 衝突解消できたら、X軸方向の移動量を滑らかに減衰
						pMove->x *= 0.5f;  // X軸移動を減速して滑りを再現
						continue;
					}

					// Y軸の衝突補正
					pPos->y = pPosOld->y;
					playerWorld._42 = pPos->y;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// 衝突解消できたら、Y軸方向の移動量を滑らかに減衰
						pMove->y *= 0.5f;  // Y軸移動を減速して滑りを再現
						continue;
					}

					// 最後に全軸を停止 (衝突解消できなかった場合)
					pMove->x = 0.0f;
					pMove->y = 0.0f;
					pMove->z = 0.0f;
				}
			}
			else
			{
				// OBB 衝突判定
				if (CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
				{
					// Z軸の衝突補正
					pPos->z = pPosOld->z;
					playerWorld._43 = pPos->z;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// 衝突解消できたら、Z軸方向の移動量を滑らかに減衰
						pMove->z *= 0.5f;  // Z軸移動を減速して滑りを再現
						continue;
					}

					// X軸の衝突補正
					pPos->x = pPosOld->x;
					playerWorld._41 = pPos->x;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// 衝突解消できたら、X軸方向の移動量を滑らかに減衰
						pMove->x *= 0.5f;  // X軸移動を減速して滑りを再現
						continue;
					}

					// Y軸の衝突補正
					pPos->y = pPosOld->y;
					playerWorld._42 = pPos->y;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// 衝突解消できたら、Y軸方向の移動量を滑らかに減衰
						pMove->y *= 0.5f;  // Y軸移動を減速して滑りを再現
						continue;
					}

					// 最後に全軸を停止 (衝突解消できなかった場合)
					pMove->x = 0.0f;
					pMove->y = 0.0f;
					pMove->z = 0.0f;
				}

			}

		}
	}
}
//==============================================
//ブロックの当たり判定(OBBを使用して回転を考慮)
//==============================================
bool CheckOBBCollision(const D3DXMATRIX& world1, const D3DXVECTOR3& size1,
	const D3DXMATRIX& world2, const D3DXVECTOR3& size2)
{
	// 各 OBB の中心座標を計算
	D3DXVECTOR3 center1(world1._41, world1._42, world1._43);
	D3DXVECTOR3 center2(world2._41, world2._42, world2._43);

	// 各 OBB の軸を取得
	D3DXVECTOR3 axes1[3] = 
	{
		{world1._11, world1._12, world1._13}, // X軸
		{world1._21, world1._22, world1._23}, // Y軸
		{world1._31, world1._32, world1._33}  // Z軸
	};

	D3DXVECTOR3 axes2[3] = 
	{
		{world2._11, world2._12, world2._13}, // X軸
		{world2._21, world2._22, world2._23}, // Y軸
		{world2._31, world2._32, world2._33}  // Z軸
	};

	// 分離軸定理 (Separating Axis Theorem) を用いて判定
	for (int nCnt = 0; nCnt < 3; ++nCnt)
	{
		if (!OverlapOnAxis(center1, axes1, size1, center2, axes2, size2, axes1[nCnt]))
		{
			return false; // 分離軸が見つかったら衝突していない
		}
		if (!OverlapOnAxis(center1, axes1, size1, center2, axes2, size2, axes2[nCnt]))
		{
			return false; // 分離軸が見つかったら衝突していない
		}
	}

	// クロス軸のチェック
	for (int Cross = 0; Cross < 3; ++Cross)
	{
		for (int Cross2 = 0; Cross2 < 3; ++Cross2)
		{
			D3DXVECTOR3 crossAxis;
			D3DXVec3Cross(&crossAxis, &axes1[Cross], &axes2[Cross2]);
			if (D3DXVec3Length(&crossAxis) > 0.001f) 
			{ // ゼロベクトルのチェック
				if (!OverlapOnAxis(center1, axes1, size1, center2, axes2, size2, crossAxis)) 
				{
					return false; // 分離軸が見つかったら衝突していない
				}
			}
		}
	}

	return true; // 分離軸がないため衝突している
}
//=================================
//OBB投影範囲計算処理
//=================================
bool OverlapOnAxis(const D3DXVECTOR3& center1, const D3DXVECTOR3 axes1[3], const D3DXVECTOR3& size1,
	const D3DXVECTOR3& center2, const D3DXVECTOR3 axes2[3], const D3DXVECTOR3& size2, const D3DXVECTOR3& axis)
{
	// 各 OBB を指定された軸に投影した時の半径を計算
	float radius1 = GetProjectionRadius(size1, axes1, axis);
	float radius2 = GetProjectionRadius(size2, axes2, axis);

	// OBB の中心の距離を指定された軸に投影
	D3DXVECTOR3 centerDiff = center2 - center1;
	float distance = fabs(D3DXVec3Dot(&centerDiff, &axis));

	// 投影の重なりを判定
	return distance <= (radius1 + radius2);
}
//=================================
//OBBに必要な範囲計算処理
//=================================
float GetProjectionRadius(const D3DXVECTOR3& size, const D3DXVECTOR3 axes[3], const D3DXVECTOR3& axis)
{
	// 各軸を指定された軸に投影し、その絶対値を足し合わせる
	return fabs(D3DXVec3Dot(&axes[0], &axis)) * size.x / 2 +
		fabs(D3DXVec3Dot(&axes[1], &axis)) * size.y / 2 +
		fabs(D3DXVec3Dot(&axes[2], &axis)) * size.z / 2;
}
//=================================
//イベント判定処理
//=================================
bool BlockInteraction()
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		Player* pPlayer = GetPlayer(); // プレイヤー情報の取得

		if (g_aBlock[nCntBlock].bUse == true)
		{
			// プレイヤーの前方方向を取得
			D3DXVECTOR3 forward = pPlayer->forward; // プレイヤーの視線方向
			D3DXVec3Normalize(&forward, &forward);  // 念のため正規化

			// ブロックとプレイヤーの距離ベクトル
			D3DXVECTOR3 toBlock = g_aBlock[nCntBlock].pos - pPlayer->pos;
			float distanceSquared = D3DXVec3LengthSq(&toBlock);

			// 距離範囲内にあるか確認
			if (distanceSquared > (pPlayer->interactionRange * pPlayer->interactionRange))
			{
				return false;
			}

			// 距離ベクトルを正規化
			D3DXVECTOR3 toBlockNormalized;
			D3DXVec3Normalize(&toBlockNormalized, &toBlock);

			// 視線方向とブロックへの方向の角度を計算
			float dotProduct = D3DXVec3Dot(&forward, &toBlockNormalized);

			// acosf の値を安全に計算（丸め誤差対策）
			if (dotProduct < -1.0f) dotProduct = -1.0f;
			if (dotProduct > 1.0f) dotProduct = 1.0f;

			float angleToBlock = acosf(dotProduct);

			// 照準範囲内かどうか確認
			if (angleToBlock <= pPlayer->interactionAngle)
			{
				return true;
			}
		}

	}

	return false; // 照準範囲内にインタラクト可能なブロックがない
}
//=================================
// ブロックインタラクト種類判定処理
//=================================
void HandleBlockInteraction(Block* pBlock)
{
	//for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	//{
		// ブロックの種類によってインタラクト内容を変更
		switch (pBlock->nType)
		{
		case BLOCKTYPE_ARCADE1:
			// アーケードブロックの動作
			if (KeyboardTrigger(DIK_E))
			{
				SetUI(D3DXVECTOR3(660.0f, 600.0f, 0.0f), 150.0f, 40.0f, UITYPE_GAME);
			}
			break;

		case BLOCKTYPE_UFOCATCHER1:
			// UFOキャッチャーブロックの動作
			// ミニゲーム開始
			break;

		default:
			break;
		}
	//}
}
//===================================
// ブロックのレイキャスト処理
//===================================
Block* RaycastToBlocks(const D3DXVECTOR3& rayOrigin, const D3DXVECTOR3& rayDirection)
{
	Block* closestBlock = NULL;
	float closestDistance = FLT_MAX; // 非常に大きな値で初期化

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++) 
	{
		if (!g_aBlock[nCntBlock].bUse) 
		{
			continue; // 使用中でないブロックはスキップ
		}

		// ブロックのOBB情報を取得
		D3DXMATRIX blockWorld = g_aBlock[nCntBlock].mtxWorld;
		D3DXVECTOR3 blockSize = g_aBlock[nCntBlock].size;

		// レイとOBBの交差判定
		float distance = 0.0f;
		if (CheckRayOBBCollision(rayOrigin, rayDirection, blockWorld, blockSize, &distance)) 
		{
			// レイキャスト結果が交差している場合
			if (distance < closestDistance && distance > 0.0f) 
			{
				closestDistance = distance; // 最も近いブロックを記録
				closestBlock = &g_aBlock[nCntBlock];
			}
		}
	}

	return closestBlock; // 最も近いブロックを返す（見つからなければNULL）
}
//===================================
// レイとOBBの交差判定処理
//===================================
bool CheckRayOBBCollision(const D3DXVECTOR3& rayOrigin, const D3DXVECTOR3& rayDirection,
	const D3DXMATRIX& obbWorld, const D3DXVECTOR3& obbSize, float* distance)
{
	D3DXVECTOR3 obbCenter(obbWorld._41, obbWorld._42, obbWorld._43);
	D3DXVECTOR3 obbAxes[3] =
	{
		{obbWorld._11, obbWorld._12, obbWorld._13}, // X軸
		{obbWorld._21, obbWorld._22, obbWorld._23}, // Y軸
		{obbWorld._31, obbWorld._32, obbWorld._33}  // Z軸
	};

	D3DXVECTOR3 delta = obbCenter - rayOrigin;

	// 各軸について投影を計算して交差判定
	for (int i = 0; i < 3; i++)
	{
		float e = D3DXVec3Dot(&delta, &obbAxes[i]);
		float f = D3DXVec3Dot(&rayDirection, &obbAxes[i]);

		if (fabs(f) < 0.001f) // レイが平行な場合
		{
			if (fabs(e) > obbSize[i]) return false; // 平行で範囲外
		}
		else
		{
			float t1 = (e - obbSize[i]) / f;
			float t2 = (e + obbSize[i]) / f;

			// 入れ替え処理
			if (t1 > t2) 
			{
				float temp = t1;
				t1 = t2;
				t2 = temp;
			}

			if (t1 > *distance) *distance = t1;
			if (t2 < *distance) return false;
		}
	}

	return true;
}
//=======================================
// 画面中心にレイキャストを設定する処理
//=======================================
void GetRayFromScreenCenter(D3DXVECTOR3* rayOrigin, D3DXVECTOR3* rayDirection)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// デバイスの取得
	D3DVIEWPORT9 viewport;
	D3DXMATRIX viewMatrix, projMatrix, viewProjMatrix, invViewProjMatrix;

	pDevice->GetViewport(&viewport);
	pDevice->GetTransform(D3DTS_VIEW, &viewMatrix);
	pDevice->GetTransform(D3DTS_PROJECTION, &projMatrix);

	// ViewProjection 行列を計算
	D3DXMatrixMultiply(&viewProjMatrix, &viewMatrix, &projMatrix);

	// ViewProjection 行列の逆行列を計算
	if (D3DXMatrixInverse(&invViewProjMatrix, NULL, &viewProjMatrix) == NULL) 
	{
		return;
	}

	// スクリーン中央の座標
	float screenX = viewport.Width * 0.5f;
	float screenY = viewport.Height * 0.5f;

	// スクリーン座標を正規化デバイス座標 (NDC) に変換
	float ndcX = (screenX / viewport.Width) * 2.0f - 1.0f;
	float ndcY = 1.0f - (screenY / viewport.Height) * 2.0f;

	// NDCからクリップ空間 (clip space) への変換
	D3DXVECTOR3 nearPoint(ndcX, ndcY, 0.0f);  // 近クリップ面
	D3DXVECTOR3 farPoint(ndcX, ndcY, 1.0f);   // 遠クリップ面

	// 逆行列を用いてワールド空間に変換
	D3DXVec3TransformCoord(&nearPoint, &nearPoint, &invViewProjMatrix);
	D3DXVec3TransformCoord(&farPoint, &farPoint, &invViewProjMatrix);

	// レイの方向を計算
	*rayOrigin = nearPoint;
	*rayDirection = farPoint - nearPoint;
	D3DXVec3Normalize(rayDirection, rayDirection); // 正規化
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