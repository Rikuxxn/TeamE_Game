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

bool bArcade;					// アーケードゲームの判定
bool bCatcher;					// UFOキャッチャーの判定
bool bKeypad;					// キーパッドの判定

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
	g_bExit = false;

	bArcade = false;
	bCatcher = false;
	bKeypad = false;

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

		g_info[nCnt].blockinfo[nCnt].vtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX); // 最小値を初期化
		g_info[nCnt].blockinfo[nCnt].vtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX); // 最大値を初期化

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
	

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 < BLOCKTYPE_MAX; nCnt2++)
		{
			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCnt].blockinfo[nCnt2].dwNumMat; nCntMat++)
			{
				//テクスチャの破棄
				if (g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat] != NULL)
				{
					g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat] = NULL;
				}
			}

			//メッシュの破棄
			if (g_info[nCnt].blockinfo[nCnt].pMesh != NULL)
			{
				g_info[nCnt].blockinfo[nCnt].pMesh = NULL;
			}

			//マテリアルの破棄
			if (g_info[nCnt].blockinfo[nCnt].pBuffMat != NULL)
			{
				g_info[nCnt].blockinfo[nCnt].pBuffMat = NULL;
			}
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
			// 視錐台中央判定を実行
			CheckBlocksInCenter();

			if (g_aBlock[nCntBlock].bInsight)
			{
				// 中央範囲内のブロックがあれば何か処理をする
				HandleBlockInteraction(&g_aBlock[nCntBlock]);
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

			if (g_aBlock[nCntBlock].nType == BLOCKTYPE_EXIT)
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
						g_bExit = true;

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
	for (int nCnt = 0; nCnt < 3; nCnt++)
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
	for (int Cross = 0; Cross < 3; Cross++)
	{
		for (int Cross2 = 0; Cross2 < 3; Cross2++)
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
	float distance = (float)fabs(D3DXVec3Dot(&centerDiff, &axis));

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
// ブロックインタラクト種類判定処理
//=================================
void HandleBlockInteraction(Block* pBlock)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		UI* pUI = GetUI();

		// ブロックの種類によってインタラクト内容を変更
		switch (pBlock->nType)
		{
		case BLOCKTYPE_ARCADE1:
			break;

		case BLOCKTYPE_UFOCATCHER1:
			break;

		case BLOCKTYPE_KEYPAD:
			break;

		default:

			break;
		}
	}
}
//=================================
// 視錐台(フラスタム)中央判定処理
//=================================
void CheckBlocksInCenter(void)
{
	Player* pPlayer = GetPlayer();
	const float fov = D3DX_PI / 4.0f;  // 視野角 (45度)
	const float centerFovRatio = 0.4f; // 中央範囲の幅
	const float nearDistance = 1.0f;   // 判定する最短距離
	const float farDistance = 90.0f;   // 判定する最長距離
	const float maxAngle = fov * centerFovRatio;
	const float heightTolerance = 1.0f; // 高さの許容範囲（例: ±1.0）

	// プレイヤーの視線方向を正規化
	D3DXVECTOR3 forward = pPlayer->forward;
	D3DXVec3Normalize(&forward, &forward);

	// 全ブロックのbInsightをリセット
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].bInsight = false; // 初期化

		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_UFOCATCHER1)
		{
			bCatcher = false;
		}
		else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_ARCADE1)
		{
			bArcade = false;
		}
		else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_KEYPAD)
		{
			bKeypad = false;
		}

	}

	// 中央範囲判定
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (!g_aBlock[nCntBlock].bUse)
		{
			continue; // 使用されていないブロックはスキップ
		}


		// 特定の種類のみ対象とする
		if (g_aBlock[nCntBlock].nType != BLOCKTYPE_ARCADE1 && g_aBlock[nCntBlock].nType != BLOCKTYPE_UFOCATCHER1 &&
			g_aBlock[nCntBlock].nType != BLOCKTYPE_KEYPAD)
		{
			continue; // 対象外の種類はスキップ
		}

		// ブロックまでのベクトルを計算
		D3DXVECTOR3 toBlock = g_aBlock[nCntBlock].pos - pPlayer->pos;
		float distance = D3DXVec3Length(&toBlock);

		//// 高さ判定
		//if (fabs(toBlock.y) > heightTolerance)
		//{
		//	continue; // 高さが許容範囲外ならスキップ
		//}

		// 距離が範囲外の場合はスキップ
		if (distance < nearDistance || distance > farDistance)
		{
			continue; // 中央判定はしない
		}

		// toBlockを正規化して方向ベクトルを得る
		D3DXVECTOR3 toBlockNormalized;
		D3DXVec3Normalize(&toBlockNormalized, &toBlock);

		// 視線方向を下向きに調整
		D3DXVECTOR3 adjustedForward = forward;

		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_KEYPAD)
		{
			adjustedForward.y += 0.0f; // 少し下向きにする
		}
		else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_ARCADE1)
		{
			adjustedForward.y += 0.4f; // 少し下向きにする
		}
		else
		{
			adjustedForward.y += 0.0f;
		}

		// 視線方向を正規化
		D3DXVec3Normalize(&adjustedForward, &adjustedForward);

		// adjustedForwardを使って中央判定を行う
		float dotProduct = D3DXVec3Dot(&adjustedForward, &toBlockNormalized);
		float angle = acosf(dotProduct); // 視線との角度（ラジアン）

		// 中央範囲内にあるか判定
		if (angle < maxAngle)
		{
			g_aBlock[nCntBlock].bInsight = true; // 中央範囲内

			if (g_aBlock[nCntBlock].nType == BLOCKTYPE_UFOCATCHER1)
			{
				bCatcher = true;
			}
			else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_ARCADE1)
			{
				bArcade = true;
			}
			else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_KEYPAD)
			{
				bKeypad = true;
			}
		}
	}
}
//============================================
//ブロックの取得
//============================================
Block* GetBlock(void)
{
	return &g_aBlock[0];
}
//======================================================
// 出口判定
//======================================================
bool GetExit(void)
{
	return g_bExit;
}
//======================================================
// アーケードゲーム判定
//======================================================
bool GetArcade(void)
{
	return bArcade;
}
//======================================================
// UFOキャッチャー判定
//======================================================
bool GetCatcher(void)
{
	return bCatcher;
}
//======================================================
// キーパッド判定
//======================================================
bool GetKeypad(void)
{
	return bKeypad;
}
