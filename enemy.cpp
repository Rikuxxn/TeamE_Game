//=======================================
//
//敵の処理[enemy.cpp]
//Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "fade.h"
#include "block.h"
//#include "sound.h"
//#include "shadow.h"
//#include "billboard.h"

// 巡回ポイント配列
D3DXVECTOR3 patrolPoints[] =
{//左回りのポイント

	D3DXVECTOR3(280.0f, 0.0f, 270.0f),		// 右上のポイント
	D3DXVECTOR3(-260.0f, 0.0f, 270.0f),		// 左上のポイント
	D3DXVECTOR3(-260.0f, 0.0f, -300.0f),	// 左下のポイント
	D3DXVECTOR3(270.0f, 0.0f, -300.0f)		// 右下のポイント

};

//グローバル変数
Enemy g_aEnemy;						//敵情報
bool g_bEnd;						//捕まった判定
bool Inside;						//視界に入ったか
bool isPlayerInSightPrev = false;
bool isReversePatrol = false;		// 巡回の方向（false: 順回り, true: 逆回り）

int currentPatrolPoint = 0;			// 現在の巡回ポイント
int g_nIdxShadowEnemy;

//=============================
//敵の初期化処理
//=============================
void InitEnemy(void)
{

    LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

    //デバイスの取得
    pDevice = GetDevice();


    //初期化
    g_aEnemy.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置を初期化する
    g_aEnemy.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前の位置を初期化する
	g_aEnemy.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    g_aEnemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量を初期化する
    g_aEnemy.motion.bLoopMotion = true;
    g_aEnemy.motion.nCounterMotion = 0;
	g_aEnemy.RadiusEnemy = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	g_aEnemy.posRadiusEnemy = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	g_aEnemy.state = ENEMYSTATE_PATROLLING;
	g_aEnemy.bUse = false;
	g_aEnemy.sightRange = 165.0f;							//視界距離
	g_aEnemy.sightAngle = D3DXToRadian(110.0f);				//視界範囲
	g_bEnd = false;
	Inside = false;
	currentPatrolPoint = 0;

	LoadEnemyTEXT();

	//g_nIdxShadowEnemy = SetShadow(D3DXVECTOR3(g_aEnemy.pos.x, g_aEnemy.pos.y, g_aEnemy.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//オフセット考慮
	for (int nCntOff = 0; nCntOff < g_aEnemy.motion.nNumModel; nCntOff++)
	{
		g_aEnemy.motion.aModel[nCntOff].Offpos = g_aEnemy.motion.aModel[nCntOff].pos;
		g_aEnemy.motion.aModel[nCntOff].Offrot = g_aEnemy.motion.aModel[nCntOff].rot;
	}

	for (int nCntVtx = 0; nCntVtx < MAX_PARTS; nCntVtx++)
	{

		int nNumVtx;//頂点数
		DWORD sizeFVF;//頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = g_aEnemy.motion.aModel[nCntVtx].pMesh->GetNumVertices();

		//頂点フォーマットの取得
		sizeFVF = D3DXGetFVFVertexSize(g_aEnemy.motion.aModel[nCntVtx].pMesh->GetFVF());

		//頂点バッファのロック
		g_aEnemy.motion.aModel[nCntVtx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値最大値を取得
			if (vtx.x < g_aEnemy.vtxMin.x)
			{
				g_aEnemy.vtxMin.x = vtx.x;
			}
			else if (vtx.y < g_aEnemy.vtxMin.y)
			{
				g_aEnemy.vtxMin.y = vtx.y;
			}
			else if (vtx.z < g_aEnemy.vtxMin.z)
			{
				g_aEnemy.vtxMin.z = vtx.z;
			}

			if (vtx.x > g_aEnemy.vtxMax.x)
			{
				g_aEnemy.vtxMax.x = vtx.x;
			}
			else if (vtx.y > g_aEnemy.vtxMax.y)
			{
				g_aEnemy.vtxMax.y = vtx.y;
			}
			else if (vtx.z > g_aEnemy.vtxMax.z)
			{
				g_aEnemy.vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		g_aEnemy.size.x = (g_aEnemy.vtxMax.x - g_aEnemy.vtxMin.x);
		g_aEnemy.size.y = (g_aEnemy.vtxMax.y - g_aEnemy.vtxMin.y);
		g_aEnemy.size.z = (g_aEnemy.vtxMax.z - g_aEnemy.vtxMin.z);

		//頂点バッファのアンロック
		g_aEnemy.motion.aModel[nCntVtx].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_aEnemy.motion.aModel[nCntVtx].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aEnemy.motion.aModel[nCntVtx].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャファイルが存在する

				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aEnemy.motion.aModel[nCntVtx].apTexture[nCntMat]);

			}
		}

	}

}
//=============================
//敵の終了処理
//=============================
void UninitEnemy(void)
{
	//StopSound(SOUND_LABEL_DENKI);
	//StopSound(SOUND_LABEL_STEP1);
	//StopSound(SOUND_LABEL_STEP2);

	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		for (int nCntMat = 0; nCntMat < (int)g_aEnemy.motion.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			//テクスチャの破棄
			if (g_aEnemy.motion.aModel[nCntModel].apTexture[nCntMat] != NULL)
			{
				g_aEnemy.motion.aModel[nCntModel].apTexture[nCntMat]->Release();
				g_aEnemy.motion.aModel[nCntModel].apTexture[nCntMat] = NULL;
			}
		}

		//メッシュの破棄
		if (g_aEnemy.motion.aModel[nCntModel].pMesh != NULL)
		{
			g_aEnemy.motion.aModel[nCntModel].pMesh->Release();
			g_aEnemy.motion.aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_aEnemy.motion.aModel[nCntModel].pBuffMat != NULL)
		{
			g_aEnemy.motion.aModel[nCntModel].pBuffMat->Release();
			g_aEnemy.motion.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}
//=============================
//敵の更新処理
//=============================
void UpdateEnemy(void)
{
	if (g_aEnemy.bUse == true)
	{
		bool isPlayerInSightNow = isPlayerInSight(); // 現在の視界判定

		// 視界外から視界内に変化した瞬間
		if (isPlayerInSightNow && !isPlayerInSightPrev)
		{
			// プレイヤーが視界に入った瞬間
			//PlaySound(SOUND_LABEL_WARNING); // SEを再生
			SetFoundFade(MODE_FOUND);
		}

		// フラグを更新して次のフレームに備える
		isPlayerInSightPrev = isPlayerInSightNow;

		Player* pPlayer = GetPlayer();


		//移動量を更新(減衰させる)
		g_aEnemy.move.x += (0.0f - g_aEnemy.move.x) * 0.3f;
		g_aEnemy.move.z += (0.0f - g_aEnemy.move.z) * 0.3f;
		g_aEnemy.move.y += (0.0f - g_aEnemy.move.y) * 0.1f;

		//前回の位置を更新
		g_aEnemy.posOld = g_aEnemy.pos;

		//位置を更新
		g_aEnemy.pos.x += g_aEnemy.move.x;
		g_aEnemy.pos.z += g_aEnemy.move.z;
		g_aEnemy.pos.y += g_aEnemy.move.y;


		//CollisionModel();

		CollisionBlock(&g_aEnemy.pos,&g_aEnemy.posOld,&g_aEnemy.move,&g_aEnemy.size);


		D3DXVECTOR3 PlayerRadius(12.0f, 12.0f, 12.0f);

		float fDistance =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadius =
			(g_aEnemy.RadiusEnemy.x + PlayerRadius.x) * (g_aEnemy.RadiusEnemy.x + PlayerRadius.x) +
			(g_aEnemy.RadiusEnemy.y + PlayerRadius.y) * (g_aEnemy.RadiusEnemy.y + PlayerRadius.y) +
			(g_aEnemy.RadiusEnemy.z + PlayerRadius.z) * (g_aEnemy.RadiusEnemy.z + PlayerRadius.z);


		if (fDistance <= fRadius)
		{
			pPlayer->pos = pPlayer->posOld;
			g_aEnemy.pos = g_aEnemy.posOld;
			g_aEnemy.motion.motionType = MOTIONTYPE_NEUTRAL2;
			g_bEnd = true;
		}

		D3DXVECTOR3 posPlayerRadius(1.0f, 1.0f, 1.0f);

		float fDistancePlayer =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadiusPlayer =
			(g_aEnemy.posRadiusEnemy.x + posPlayerRadius.x) * (g_aEnemy.posRadiusEnemy.x + posPlayerRadius.x) +
			(g_aEnemy.posRadiusEnemy.y + posPlayerRadius.y) * (g_aEnemy.posRadiusEnemy.y + posPlayerRadius.y) +
			(g_aEnemy.posRadiusEnemy.z + posPlayerRadius.z) * (g_aEnemy.posRadiusEnemy.z + posPlayerRadius.z);


		//範囲内に入った
		if (fDistancePlayer <= fRadiusPlayer)
		{
			g_aEnemy.state = ENEMYSTATE_CHASING;
		}

		if (isPlayerInSight())
		{
			Inside = true;
		}
		else
		{
			Inside = false;
		}


		if (g_aEnemy.pos.y <= 0)
		{
			g_aEnemy.pos.y = 0.0f;
		}


		//SetPositionShadow(g_nIdxShadowEnemy, D3DXVECTOR3(g_aEnemy.pos.x, 0.0f, g_aEnemy.pos.z));


		//敵の足音
		if (g_aEnemy.motion.motionType == MOTIONTYPE_NEUTRAL && g_aEnemy.motion.nKey == 1 && g_aEnemy.motion.nCounterMotion == 9)
		{
			//PlaySound(SOUND_LABEL_STEP1);
		}
		else if (g_aEnemy.motion.motionType == MOTIONTYPE_NEUTRAL && g_aEnemy.motion.nKey == 3 && g_aEnemy.motion.nCounterMotion == 5)
		{
			//PlaySound(SOUND_LABEL_STEP2);
		}

		if (g_aEnemy.motion.motionType == MOTIONTYPE_MOVE && g_aEnemy.motion.nKey == 1 && g_aEnemy.motion.nCounterMotion == 8)
		{
			//PlaySound(SOUND_LABEL_STEP1);
		}
		else if (g_aEnemy.motion.motionType == MOTIONTYPE_MOVE && g_aEnemy.motion.nKey == 3 && g_aEnemy.motion.nCounterMotion == 5)
		{
			//PlaySound(SOUND_LABEL_STEP2);
		}

		//全モデルの更新
		for (int nCntModel = 0; nCntModel < g_aEnemy.motion.nNumModel; nCntModel++)
		{

			int nNextKey = (g_aEnemy.motion.nKey + 1) % g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].nNumKey;

			// 境界チェック
			if (g_aEnemy.motion.nKey >= g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].nNumKey ||
				nNextKey >= g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].nNumKey)
			{
				g_aEnemy.motion.nKey = 0;
			}

			D3DXVECTOR3 Mpos, Mrot;
			D3DXVECTOR3 MAnswer, MAnswer2;//計算結果用

			//キー情報から位置・向きを算出
			Mpos.x = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosX - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosX;
			Mpos.y = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosY - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosY;
			Mpos.z = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosZ - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosZ;

			Mrot.x = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotX - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotX;
			Mrot.y = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotY - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotY;
			Mrot.z = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotZ - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotZ;

			//補間係数を計算
			float t = (float)g_aEnemy.motion.nCounterMotion / g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].nFrame;

			//求める値
			MAnswer.x = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosX + Mpos.x * t;
			MAnswer.y = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosY + Mpos.y * t;
			MAnswer.z = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosZ + Mpos.z * t;

			MAnswer2.x = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotX + Mrot.x * t;
			MAnswer2.y = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotY + Mrot.y * t;
			MAnswer2.z = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotZ + Mrot.z * t;


			//全パーツの位置・向きを設定
			g_aEnemy.motion.aModel[nCntModel].pos = g_aEnemy.motion.aModel[nCntModel].Offpos + MAnswer;

			g_aEnemy.motion.aModel[nCntModel].rot = g_aEnemy.motion.aModel[nCntModel].Offrot + MAnswer2;

		}

		g_aEnemy.motion.nCounterMotion++;//再生フレーム数に達したら現在のキーを1つ進める

		if (g_aEnemy.motion.nCounterMotion >= g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].nFrame)
		{
			g_aEnemy.motion.nCounterMotion = 0;

			g_aEnemy.motion.nKey++;
		}

		float moveSpeed = 0.0f;
		static int lostSightTimer = 0;			// 視界外タイマー
		float distanceToTarget = 0.0f;
		float angleToTarget = 0.0f;
		float fAngle = 0.0f;

		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		static int patrolTimer = 0;				// 捜索タイマー

		switch (g_aEnemy.state)
		{
		case ENEMYSTATE_PATROLLING:

			g_aEnemy.motion.motionType = MOTIONTYPE_NEUTRAL;

			// 現在の巡回ポイントに向かう
			target = patrolPoints[currentPatrolPoint];

			distanceToTarget = sqrt
			(
				(target.x - g_aEnemy.pos.x) * (target.x - g_aEnemy.pos.x) +
				(target.y - g_aEnemy.pos.y) * (target.y - g_aEnemy.pos.y) +
				(target.z - g_aEnemy.pos.z) * (target.z - g_aEnemy.pos.z)
			);

			if (currentPatrolPoint < 0 || currentPatrolPoint >= sizeof(patrolPoints) / sizeof(patrolPoints[0]))
			{
				currentPatrolPoint = 0; // 範囲外アクセスを防ぐ
			}

			// 近づく
			moveSpeed = 0.4f; // 巡回速度

			if (distanceToTarget > 5.0f)
			{ // 到達判定
				angleToTarget = atan2f(target.x - g_aEnemy.pos.x, target.z - g_aEnemy.pos.z);
				g_aEnemy.move.x += sinf(angleToTarget) * moveSpeed;
				g_aEnemy.move.z += cosf(angleToTarget) * moveSpeed;

				g_aEnemy.rot.y = angleToTarget + D3DX_PI;
			}
			else
			{
				// 一定確率で逆回りに切り替える
				if (rand() % 100 < 30) // 30%の確率で方向を切り替える
				{
					isReversePatrol = !isReversePatrol;
				}

				// 巡回ポイントの更新
				if (isReversePatrol)
				{
					currentPatrolPoint = (currentPatrolPoint - 1 + (sizeof(patrolPoints) / sizeof(patrolPoints[0]))) % (sizeof(patrolPoints) / sizeof(patrolPoints[0]));
				}
				else
				{
					currentPatrolPoint = (currentPatrolPoint + 1) % (sizeof(patrolPoints) / sizeof(patrolPoints[0]));
				}
			}

			// プレイヤーを視界内で検出したら追跡に切り替える
			if (isPlayerInSight())
			{
				g_aEnemy.state = ENEMYSTATE_CHASING;
			}

			break;

		case ENEMYSTATE_CHASING:

			fAngle = atan2f(pPlayer->pos.x - g_aEnemy.pos.x, pPlayer->pos.z - g_aEnemy.pos.z);

			g_aEnemy.move.x += sinf(fAngle) * 1.15f;
			g_aEnemy.move.z += cosf(fAngle) * 1.15f;

			g_aEnemy.rot.y = fAngle + D3DX_PI;

			g_aEnemy.motion.motionType = MOTIONTYPE_MOVE;


			// プレイヤーが視界外に出たら捜索状態に切り替える
			if (!isPlayerInSight())
			{
				g_aEnemy.state = ENEMYSTATE_SEARCHING; // 捜索状態へ
			}

			if (!isPlayerInSight())
			{
				lostSightTimer++;

				if (lostSightTimer > 180)
				{ // 180フレーム経過
					currentPatrolPoint = GetNearestPatrolPoint(g_aEnemy.pos);

					g_aEnemy.state = ENEMYSTATE_PATROLLING;

					lostSightTimer = 0; // タイマーをリセット
				}
			}
			else
			{
				lostSightTimer = 0; // 視界内に戻ったらタイマーをリセット
			}

			break;

		case ENEMYSTATE_SEARCHING:

			g_aEnemy.motion.motionType = MOTIONTYPE_ACTION;

			if (isPlayerInSight())
			{
				g_aEnemy.state = ENEMYSTATE_CHASING;
			}

			// 一定時間経過後巡回に戻る
			patrolTimer++;

			if (patrolTimer > 180)
			{
				currentPatrolPoint = GetNearestPatrolPoint(g_aEnemy.pos);

				g_aEnemy.state = ENEMYSTATE_PATROLLING;
				patrolTimer = 0;
			}

			break;

		case ENEMYSTATE_IDLE:

			break;
		}
	}
}
//=============================
//敵の描画処理
//=============================
void DrawEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	if (g_aEnemy.bUse == true)
	{

		//計算用マトリックス
		D3DXMATRIX mtxRot, mtxTrans, mtxSize;

		D3DMATERIAL9 matDef;//現在のマテリアル保存用

		D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aEnemy.mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy.rot.y, g_aEnemy.rot.x, g_aEnemy.rot.z);
		D3DXMatrixMultiply(&g_aEnemy.mtxWorld, &g_aEnemy.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aEnemy.pos.x, g_aEnemy.pos.y, g_aEnemy.pos.z);
		D3DXMatrixMultiply(&g_aEnemy.mtxWorld, &g_aEnemy.mtxWorld, &mtxTrans);

		//ワールドマトリックスを設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy.mtxWorld);

		//現在のマテリアルの取得
		pDevice->GetMaterial(&matDef);

		//全モデル(パーツ)の描画
		for (int nCntModel = 0; nCntModel < g_aEnemy.motion.nNumModel; nCntModel++)
		{

			D3DXMATRIX mtxRotModel, mtxTransModel;//計算用マトリックス

			D3DXMATRIX mtxParent;//親のマトリックス

			//パーツのワールドマトリックスも初期化
			D3DXMatrixIdentity(&g_aEnemy.motion.aModel[nCntModel].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy.motion.aModel[nCntModel].rot.y, g_aEnemy.motion.aModel[nCntModel].rot.x, g_aEnemy.motion.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aEnemy.motion.aModel[nCntModel].mtxWorld, &g_aEnemy.motion.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_aEnemy.motion.aModel[nCntModel].pos.x, g_aEnemy.motion.aModel[nCntModel].pos.y, g_aEnemy.motion.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aEnemy.motion.aModel[nCntModel].mtxWorld, &g_aEnemy.motion.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの親のマトリックスを設定
			if (g_aEnemy.motion.aModel[nCntModel].nIdxModelParent != -1)
			{//親モデルがある場合

				mtxParent = g_aEnemy.motion.aModel[g_aEnemy.motion.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//親モデルがない場合

				mtxParent = g_aEnemy.mtxWorld;
			}

			//算出したパーツのワールドマトリックスと親のマトリックスをかけ合わせる
			D3DXMatrixMultiply(&g_aEnemy.motion.aModel[nCntModel].mtxWorld, &g_aEnemy.motion.aModel[nCntModel].mtxWorld, &mtxParent);

			//パーツのワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy.motion.aModel[nCntModel].mtxWorld);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aEnemy.motion.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aEnemy.motion.aModel[nCntModel].dwNumMat; nCntMat++)
			{

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_aEnemy.motion.aModel[nCntModel].apTexture[nCntMat]);

				//モデル(パーツ)の描画
				g_aEnemy.motion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);

			}

		}

		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}
//=============================
//敵の設定処理
//=============================
void SetEnemy(D3DXVECTOR3 pos)
{
	if (g_aEnemy.bUse == false)
	{

		g_aEnemy.pos = pos;
		g_aEnemy.bUse = true;

	}
}
//============================================
//敵の取得
//============================================
Enemy* GetEnemy(void)
{
	return &g_aEnemy;
}
//=============================
//視界内判定
//=============================
bool isPlayerInSight(void) 
{
	Player* pPlayer = GetPlayer();

	// 敵の正面ベクトルを計算
	D3DXVECTOR3 enemyFront;

	enemyFront.x = -sinf(g_aEnemy.rot.y);
	enemyFront.y = 0.0f;
	enemyFront.z = -cosf(g_aEnemy.rot.y);

	// プレイヤーとの方向ベクトル
	D3DXVECTOR3 toPlayer;

	toPlayer.x = pPlayer->pos.x - g_aEnemy.pos.x;
	toPlayer.y = 0.0f;
	toPlayer.z = pPlayer->pos.z - g_aEnemy.pos.z;

	// プレイヤー方向ベクトルを正規化
	D3DXVec3Normalize(&toPlayer, &toPlayer);

	// 敵の正面ベクトルも正規化
	D3DXVec3Normalize(&enemyFront, &enemyFront);

	// ベクトルの内積を計算
	float dotProduct = D3DXVec3Dot(&enemyFront, &toPlayer);

	// 内積から視野内か判定
	if (dotProduct > cosf(g_aEnemy.sightAngle * 0.5f)) // 視野角の半分で判定
	{
		// プレイヤーとの距離を計算
		float distanceSquared =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		if (distanceSquared <= g_aEnemy.sightRange * g_aEnemy.sightRange)
		{
			return true; // プレイヤーは視界内
		}
	}

	return false; // 視界外
}
//======================================================
//一番近い巡回ポイントの算出処理
//======================================================
int GetNearestPatrolPoint(D3DXVECTOR3 currentPos) 
{
	float minDistance = FLT_MAX; // 非常に大きな値で初期化
	int nearestPoint = 0;

	for (int i = 0; i < sizeof(patrolPoints) / sizeof(patrolPoints[0]); i++) 
	{
		float distance = sqrt(
			(patrolPoints[i].x - currentPos.x) * (patrolPoints[i].x - currentPos.x) +
			(patrolPoints[i].y - currentPos.y) * (patrolPoints[i].y - currentPos.y) +
			(patrolPoints[i].z - currentPos.z) * (patrolPoints[i].z - currentPos.z)
		);

		if (distance < minDistance) 
		{
			minDistance = distance;
			nearestPoint = i;
		}
	}

	return nearestPoint; // 最も近い巡回ポイントのインデックスを返す
}
//======================================================
//捕まった判定
//======================================================
bool GetEnd(void)
{
	return g_bEnd;
}
//======================================================
//視界に入ったか判定
//======================================================
bool GetInside(void)
{
	return Inside;
}