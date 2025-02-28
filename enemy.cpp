//=======================================
//
// 敵の処理 [enemy.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "fade.h"
#include "block.h"
#include "sound.h"
#include "shadow.h"

// 巡回ポイント配列
D3DXVECTOR3 patrolPoints[] =
{
	D3DXVECTOR3(1000.0f, 0.0f, 110.0f),
	D3DXVECTOR3(850.0f, 0.0f, 475.0f),
	D3DXVECTOR3(520.0f, 0.0f, 490.0f),
	D3DXVECTOR3(220.0f, 0.0f, 675.0f),
	D3DXVECTOR3(12.0f, 0.0f, 590.0f),
	D3DXVECTOR3(-190.0f, 0.0f, 635.0f),

	D3DXVECTOR3(-125.0f, 0.0f, 830.0f),
	D3DXVECTOR3(-225.0f, 0.0f, 830.0f),
	D3DXVECTOR3(-325.0f, 0.0f, 830.0f),
	D3DXVECTOR3(-425.0f, 0.0f, 830.0f),
	D3DXVECTOR3(500.0f, 0.0f, 830.0f),
	D3DXVECTOR3(550.0f, 0.0f, 830.0f),
	D3DXVECTOR3(600.0f, 0.0f, 830.0f),
	D3DXVECTOR3(650.0f, 0.0f, 830.0f),
	D3DXVECTOR3(700.0f, 0.0f, 830.0f),

	D3DXVECTOR3(830.0f, 0.0f, 655.0f),
	D3DXVECTOR3(850.0f, 0.0f, 475.0f),

	D3DXVECTOR3(-975.0f, 0.0f, 860.0f),
	D3DXVECTOR3(-1000.0f, 0.0f, 530.0f),
	D3DXVECTOR3(-1015.0f, 0.0f, 260.0f),
	D3DXVECTOR3(-1060.0f, 0.0f, 135.0f),

	D3DXVECTOR3(-1055.0f, 0.0f, -25.0f),
	D3DXVECTOR3(-1025.0f, 0.0f, -225.0f),
	D3DXVECTOR3(-1025.0f, 0.0f, -420.0f),
	D3DXVECTOR3(-1080.0f, 0.0f, -600.0f),
	D3DXVECTOR3(-1075.0f, 0.0f, -805.0f),
	D3DXVECTOR3(-785.0f, 0.0f, -800.0f),
	D3DXVECTOR3(-525.0f, 0.0f, -800.0f),
	D3DXVECTOR3(-335.0f, 0.0f, -800.0f),
	D3DXVECTOR3(45.0f, 0.0f, -730.0f),
	D3DXVECTOR3(378.0f, 0.0f, -705.0f),
	D3DXVECTOR3(495.0f, 0.0f, -670.0f),
	D3DXVECTOR3(475.0f, 0.0f, -420.0f),
	D3DXVECTOR3(570.0f, 0.0f, -235.0f),
	D3DXVECTOR3(830.0f, 0.0f, -140.0f),
	D3DXVECTOR3(840.0f, 0.0f, -265.0f),
	D3DXVECTOR3(935.0f, 0.0f, -365.0f),
	D3DXVECTOR3(985.0f, 0.0f, -495.0f),
	D3DXVECTOR3(1055.0f, 0.0f, -720.0f),
	D3DXVECTOR3(765.0f, 0.0f, -715.0f),
	D3DXVECTOR3(495.0f, 0.0f, -670.0f),
	D3DXVECTOR3(45.0f, 0.0f, -730.0f),
	D3DXVECTOR3(25.0f, 0.0f, -445.0f),
	D3DXVECTOR3(-225.0f, 0.0f, -425.0f),

	D3DXVECTOR3(-710.0f, 0.0f, -420.0f),
	D3DXVECTOR3(-455.0f, 0.0f, -425.0f),
	D3DXVECTOR3(-225.0f, 0.0f, -425.0f),
	D3DXVECTOR3(-225.0f, 0.0f, -35.0f),
	D3DXVECTOR3(-455.0f, 0.0f, -35.0f),
	D3DXVECTOR3(-705.0f, 0.0f, -35.0f),
	D3DXVECTOR3(-1055.0f, 0.0f, -25.0f),
	D3DXVECTOR3(-1015.0f, 0.0f, 260.0f),
	D3DXVECTOR3(-700.0f, 0.0f, 300.0f),
	D3DXVECTOR3(-695.0f, 0.0f, 510.0f),
	D3DXVECTOR3(-415.0f, 0.0f, 510.0f),
	D3DXVECTOR3(-410.0f, 0.0f, 295.0f),
	D3DXVECTOR3(30.0f, 0.0f, 270.0f),
	D3DXVECTOR3(465.0f, 0.0f, 204.0f),
	D3DXVECTOR3(680.0f, 0.0f, 115.0f),
};

int map[MAP_HEIGHT][MAP_WIDTH] = 
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// グローバル変数
Enemy g_aEnemy;						// 敵情報
bool g_bEnd;						// 捕まった判定
bool Inside;						// 視界に入ったか
bool isPlayerInSightPrev;
bool isReversePatrol;				// 巡回の方向（false: 順回り, true: 逆回り）

int currentPatrolPoint;				// 現在の巡回ポイント
int g_nIdxShadowEnemy;

bool SoundRange = false;			// 前フレームで範囲内だったか
float soundTimer = 0.0f;			// 心音のタイマー
const float minInterval = 0.67f;	// 心音の最速間隔（プレイヤーが超接近時）
const float maxInterval = 1.2f;		// 心音の最遅間隔（遠い時）
const float closeDistance = 320.0f; // 近いと判定する距離（ここに近づくと最速の心音）
const float farDistance = 700.0f;   // 遠いと判定する距離（ここでは最遅の心音）

//=============================
// 敵の初期化処理
//=============================
void InitEnemy(void)
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

    //初期化
    g_aEnemy.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置を初期化する
    g_aEnemy.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前の位置を初期化する
	g_aEnemy.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    g_aEnemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量を初期化する
    g_aEnemy.enemymotion.bLoopMotion = true;
    g_aEnemy.enemymotion.nCounterMotion = 0;
	g_aEnemy.RadiusEnemy = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	g_aEnemy.posRadiusEnemy = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	g_aEnemy.state = ENEMYSTATE_PATROLLING;
	g_aEnemy.bUse = false;
	g_aEnemy.sightRange = 310.0f;							//視界距離
	g_aEnemy.sightAngle = D3DXToRadian(90.0f);				//視界範囲
	g_bEnd = false;
	Inside = false;
	isPlayerInSightPrev = false;
	isReversePatrol = false;
	currentPatrolPoint = 0;

	LoadEnemyTEXT();

	//g_nIdxShadowEnemy = SetShadow(D3DXVECTOR3(g_aEnemy.pos.x, g_aEnemy.pos.y, g_aEnemy.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//オフセット考慮
	for (int nCntOff = 0; nCntOff < g_aEnemy.enemymotion.nNumModel; nCntOff++)
	{
		g_aEnemy.enemymotion.aModel[nCntOff].Offpos = g_aEnemy.enemymotion.aModel[nCntOff].pos;
		g_aEnemy.enemymotion.aModel[nCntOff].Offrot = g_aEnemy.enemymotion.aModel[nCntOff].rot;
	}

	for (int nCntVtx = 0; nCntVtx < MAX_PARTS; nCntVtx++)
	{

		int nNumVtx;//頂点数
		DWORD sizeFVF;//頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->GetNumVertices();

		//頂点フォーマットの取得
		sizeFVF = D3DXGetFVFVertexSize(g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->GetFVF());

		//頂点バッファのロック
		g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

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
		g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_aEnemy.enemymotion.aModel[nCntVtx].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aEnemy.enemymotion.aModel[nCntVtx].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャファイルが存在する

				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aEnemy.enemymotion.aModel[nCntVtx].apTexture[nCntMat]);

			}
		}

	}

}
//=============================
// 敵の終了処理
//=============================
void UninitEnemy(void)
{
	StopSound(SOUND_LABEL_INSIGHT);
	StopSound(SOUND_LABEL_ENEMYSTEP1);
	StopSound(SOUND_LABEL_ENEMYSTEP2);

	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		for (int nCntMat = 0; nCntMat < (int)g_aEnemy.enemymotion.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			//テクスチャの破棄
			if (g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat] != NULL)
			{
				g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat]->Release();
				g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat] = NULL;
			}
		}

		//メッシュの破棄
		if (g_aEnemy.enemymotion.aModel[nCntModel].pMesh != NULL)
		{
			g_aEnemy.enemymotion.aModel[nCntModel].pMesh->Release();
			g_aEnemy.enemymotion.aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat != NULL)	
		{
			g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat->Release();
			g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}
//=============================
// 敵の更新処理
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
			PlaySound(SOUND_LABEL_INSIGHT); // SEを再生
		}
		
		// フラグを更新して次のフレームに備える
		isPlayerInSightPrev = isPlayerInSightNow;

		Player* pPlayer = GetPlayer();

		//移動量を更新(減衰させる)
		g_aEnemy.move.x += (0.0f - g_aEnemy.move.x) * 0.25f;
		g_aEnemy.move.z += (0.0f - g_aEnemy.move.z) * 0.25f;
		g_aEnemy.move.y += (0.0f - g_aEnemy.move.y) * 0.1f;

		//前回の位置を更新
		g_aEnemy.posOld = g_aEnemy.pos;

		//位置を更新
		g_aEnemy.pos.x += g_aEnemy.move.x;
		g_aEnemy.pos.z += g_aEnemy.move.z;
		g_aEnemy.pos.y += g_aEnemy.move.y;


		//CollisionModel();

		CollisionBlock(&g_aEnemy.pos,&g_aEnemy.posOld,&g_aEnemy.move,&g_aEnemy.size);


		D3DXVECTOR3 PlayerRadius(40.0f, 40.0f, 40.0f);				// 捕まる距離
		D3DXVECTOR3 PlayerInsightRadius(80.0f, 80.0f, 80.0f);		// バレる距離
		D3DXVECTOR3 SoundRadius1(420.0f, 420.0f, 420.0f);			// 心音の鳴る距離

		float fDistance =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadius =
			(g_aEnemy.RadiusEnemy.x + PlayerRadius.x) * (g_aEnemy.RadiusEnemy.x + PlayerRadius.x) +
			(g_aEnemy.RadiusEnemy.y + PlayerRadius.y) * (g_aEnemy.RadiusEnemy.y + PlayerRadius.y) +
			(g_aEnemy.RadiusEnemy.z + PlayerRadius.z) * (g_aEnemy.RadiusEnemy.z + PlayerRadius.z);


		// 捕まった
		if (fDistance <= fRadius)
		{
			pPlayer->pos = pPlayer->posOld;
			g_aEnemy.pos = g_aEnemy.posOld;
			g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_ACTION;
			g_bEnd = true;
		}

		float fDistance2 =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadius2 =
			(g_aEnemy.RadiusEnemy.x + PlayerInsightRadius.x) * (g_aEnemy.RadiusEnemy.x + PlayerInsightRadius.x) +
			(g_aEnemy.RadiusEnemy.y + PlayerInsightRadius.y) * (g_aEnemy.RadiusEnemy.y + PlayerInsightRadius.y) +
			(g_aEnemy.RadiusEnemy.z + PlayerInsightRadius.z) * (g_aEnemy.RadiusEnemy.z + PlayerInsightRadius.z);


		// 追跡モードにする
		if (fDistance2 <= fRadius2)
		{
			g_aEnemy.state = ENEMYSTATE_CHASING;
		}

		float fDistanceSound1 =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadiusSound1 =
			(g_aEnemy.RadiusEnemy.x + SoundRadius1.x) * (g_aEnemy.RadiusEnemy.x + SoundRadius1.x) +
			(g_aEnemy.RadiusEnemy.y + SoundRadius1.y) * (g_aEnemy.RadiusEnemy.y + SoundRadius1.y) +
			(g_aEnemy.RadiusEnemy.z + SoundRadius1.z) * (g_aEnemy.RadiusEnemy.z + SoundRadius1.z);

		// 2乗距離を通常の距離に変換
		float distance = sqrtf(fDistanceSound1);

		bool SoundRangeNow = (fDistanceSound1 <= fRadiusSound1);

		// intervalを距離に応じて変化させる
		float dynamicInterval = maxInterval;

		if (distance < farDistance)
		{
			float t = (distance - closeDistance) / (farDistance - closeDistance);	// 0.0 ~ 1.0 の範囲に正規化
			t = max(0.0f, min(1.0f, t));											// 範囲を超えないように
			dynamicInterval = minInterval + (maxInterval - minInterval) * t;		// 線形補間
		}

		// 範囲内にいる間は一定間隔で音を鳴らす
		if (SoundRangeNow)
		{
			soundTimer += 0.016f;						// 前フレームからの経過時間を加算

			if (soundTimer >= dynamicInterval)
			{
				PlaySound(SOUND_LABEL_HEART);
				soundTimer = 0.0f;						// タイマーをリセット
			}
		}

		// 範囲外に出た瞬間はタイマーをリセット（SEを鳴らさない
		if (!SoundRangeNow && SoundRange)
		{
			soundTimer = 0.0f;							// タイマーをリセット
		}

		// フラグを更新
		SoundRange = SoundRangeNow;


		D3DXVECTOR3 posPlayerRadius(1.0f, 1.0f, 1.0f);

		float fDistancePlayer =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadiusPlayer =
			(g_aEnemy.posRadiusEnemy.x + posPlayerRadius.x) * (g_aEnemy.posRadiusEnemy.x + posPlayerRadius.x) +
			(g_aEnemy.posRadiusEnemy.y + posPlayerRadius.y) * (g_aEnemy.posRadiusEnemy.y + posPlayerRadius.y) +
			(g_aEnemy.posRadiusEnemy.z + posPlayerRadius.z) * (g_aEnemy.posRadiusEnemy.z + posPlayerRadius.z);


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
		if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_NEUTRAL && g_aEnemy.enemymotion.nKey == 1 && 
			g_aEnemy.enemymotion.nCounterMotion == 10)
		{
			PlaySound3D(SOUND_LABEL_ENEMYSTEP1);
		}
		else if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_NEUTRAL && g_aEnemy.enemymotion.nKey == 3 &&
			g_aEnemy.enemymotion.nCounterMotion == 5)
		{
			PlaySound3D(SOUND_LABEL_ENEMYSTEP2);
		}

		if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_MOVE && g_aEnemy.enemymotion.nKey == 1 &&
			g_aEnemy.enemymotion.nCounterMotion == 9)
		{
			PlaySound3D(SOUND_LABEL_ENEMYSTEP1);
		}
		else if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_MOVE && g_aEnemy.enemymotion.nKey == 3 && 
			g_aEnemy.enemymotion.nCounterMotion == 5)
		{
			PlaySound3D(SOUND_LABEL_ENEMYSTEP2);
		}

		//全モデルの更新
		for (int nCntModel = 0; nCntModel < g_aEnemy.enemymotion.nNumModel; nCntModel++)
		{
			int nNextKey = (g_aEnemy.enemymotion.nKey + 1) % g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].nNumKey;

			// 境界チェック
			if (g_aEnemy.enemymotion.nKey >= g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].nNumKey ||
				nNextKey >= g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].nNumKey)
			{
				g_aEnemy.enemymotion.nKey = 0;
			}

			D3DXVECTOR3 Mpos, Mrot;
			D3DXVECTOR3 MAnswer, MAnswer2;//計算結果用

			//キー情報から位置・向きを算出
			Mpos.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fPosX - 
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosX;
			Mpos.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fPosY -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosY;
			Mpos.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fPosZ -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosZ;

			Mrot.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fRotX -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotX;
			Mrot.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fRotY -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotY;
			Mrot.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fRotZ -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotZ;

			//補間係数を計算
			float t = (float)g_aEnemy.enemymotion.nCounterMotion / g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].nFrame;

			//求める値
			MAnswer.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosX + Mpos.x * t;
			MAnswer.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosY + Mpos.y * t;
			MAnswer.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosZ + Mpos.z * t;

			MAnswer2.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotX + Mrot.x * t;
			MAnswer2.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotY + Mrot.y * t;
			MAnswer2.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotZ + Mrot.z * t;


			//全パーツの位置・向きを設定
			g_aEnemy.enemymotion.aModel[nCntModel].pos = g_aEnemy.enemymotion.aModel[nCntModel].Offpos + MAnswer;

			g_aEnemy.enemymotion.aModel[nCntModel].rot = g_aEnemy.enemymotion.aModel[nCntModel].Offrot + MAnswer2;

		}

		g_aEnemy.enemymotion.nCounterMotion++;//再生フレーム数に達したら現在のキーを1つ進める

		if (g_aEnemy.enemymotion.nCounterMotion >= g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].nFrame)
		{
			g_aEnemy.enemymotion.nCounterMotion = 0;

			g_aEnemy.enemymotion.nKey++;
		}

		// 状態遷移
		switch (g_aEnemy.state)
		{
		case ENEMYSTATE_PATROLLING:
			// 巡回モード
			Patrol();

			break;

		case ENEMYSTATE_CHASING:
			// 追跡モード
			Chase();

			break;

		case ENEMYSTATE_SEARCHING:
			// 捜索モード
			Search();

			break;
		}
	}
}
//=============================
// 敵の描画処理
//=============================
void DrawEnemy(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

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
		for (int nCntModel = 0; nCntModel < g_aEnemy.enemymotion.nNumModel; nCntModel++)
		{

			D3DXMATRIX mtxRotModel, mtxTransModel;//計算用マトリックス

			D3DXMATRIX mtxParent;//親のマトリックス

			//パーツのワールドマトリックスも初期化
			D3DXMatrixIdentity(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy.enemymotion.aModel[nCntModel].rot.y, g_aEnemy.enemymotion.aModel[nCntModel].rot.x, g_aEnemy.enemymotion.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_aEnemy.enemymotion.aModel[nCntModel].pos.x, g_aEnemy.enemymotion.aModel[nCntModel].pos.y, g_aEnemy.enemymotion.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの親のマトリックスを設定
			if (g_aEnemy.enemymotion.aModel[nCntModel].nIdxModelParent != -1)
			{//親モデルがある場合

				mtxParent = g_aEnemy.enemymotion.aModel[g_aEnemy.enemymotion.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//親モデルがない場合

				mtxParent = g_aEnemy.mtxWorld;
			}

			//算出したパーツのワールドマトリックスと親のマトリックスをかけ合わせる
			D3DXMatrixMultiply(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &mtxParent);

			//パーツのワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aEnemy.enemymotion.aModel[nCntModel].dwNumMat; nCntMat++)
			{

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat]);

				//モデル(パーツ)の描画
				g_aEnemy.enemymotion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);

			}

		}

		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}
//=============================
// 敵の設定処理
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
// 敵の取得
//============================================
Enemy* GetEnemy(void)
{
	return &g_aEnemy;
}
//=============================
// 視界内判定
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

	// 内積から視野内か判定(0.5fはしきい値)
	if (dotProduct > cosf(g_aEnemy.sightAngle * 0.5f)) // 視野角の半分で判定 1 → 完全に同じ方向（正面）0 → 直角（真横）- 1 → 真逆（背後）
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
// 一番近い巡回ポイントの算出処理
//======================================================
int GetNearestPatrolPoint(D3DXVECTOR3 currentPos) 
{
	float minDistance = FLT_MAX; // 非常に大きな値で初期化
	int nearestPoint = 0;

	for (int nCnt = 0; nCnt < sizeof(patrolPoints) / sizeof(patrolPoints[0]); nCnt++)
	{
		float distance = sqrtf
		(
			(patrolPoints[nCnt].x - currentPos.x) * (patrolPoints[nCnt].x - currentPos.x) +
			(patrolPoints[nCnt].y - currentPos.y) * (patrolPoints[nCnt].y - currentPos.y) +
			(patrolPoints[nCnt].z - currentPos.z) * (patrolPoints[nCnt].z - currentPos.z)
		);

		if (distance < minDistance) 
		{
			minDistance = distance;
			nearestPoint = nCnt;
		}
	}

	return nearestPoint; // 最も近い巡回ポイントのインデックスを返す
}
//======================================================
// 巡回処理
//======================================================
void Patrol(void)
{
	g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_NEUTRAL;

	float moveSpeed = 0.0f;
	float distanceToTarget = 0.0f;
	float angleToTarget = 0.0f;
	float fAngle = 0.0f;

	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);

	// 現在の巡回ポイントに向かう
	target = patrolPoints[currentPatrolPoint];

	distanceToTarget = sqrtf
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
		if (rand() % 100 < 25) // 25%の確率で方向を切り替える
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
}
//======================================================
// 追跡処理
//======================================================
void Chase(void)
{
	Player* pPlayer = GetPlayer();

	g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_MOVE;

	float fAngle = 0.0f;
	static int lostSightTimer = 0;				// 視界外タイマー

	fAngle = atan2f(pPlayer->pos.x - g_aEnemy.pos.x, pPlayer->pos.z - g_aEnemy.pos.z);

	g_aEnemy.move.x += sinf(fAngle) * 1.151f;
	g_aEnemy.move.z += cosf(fAngle) * 1.151f;

	g_aEnemy.rot.y = fAngle + D3DX_PI;

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
}
//======================================================
// 探索処理
//======================================================
void Search(void)
{
	g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_SEARCH;

	static int patrolTimer = 0;				// 捜索タイマー

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
}
void pixelToGrid(int px, int py, int* gx, int* gy) 
{
	*gx = px / GRID_SIZE;  // 50px単位で変換
	*gy = py / GRID_SIZE;
}
void gridToPixel(int gx, int gy, int* px, int* py) 
{
	*px = gx * GRID_SIZE + GRID_SIZE / 2;
	*py = gy * GRID_SIZE + GRID_SIZE / 2;
}
//==============================================
// ヒューリスティック関数（マンハッタン距離）
//==============================================
float heuristic(int x1, int y1, int x2, int y2) 
{
	return fabsf(x1 - x2) + fabsf(y1 - y2);
}
Node* find_path(int startX, int startY, int goalX, int goalY) 
{
	Node* openList[MAX_NODES];
	int openCount = 0;
	bool closedList[MAP_HEIGHT][MAP_WIDTH] = { false };

	// 開始ノードを作成
	Node* start = (Node*)malloc(sizeof(Node));
	if (!start) 
	{
		return NULL;
	}
	start->x = startX;
	start->y = startY;
	start->g = 0;
	start->h = heuristic(startX, startY, goalX, goalY);
	start->f = start->g + start->h;
	start->parent = NULL;

	openList[openCount++] = start;

	while (openCount > 0) 
	{
		// 最小 f 値のノードを探す
		int minIndex = 0;
		for (int i = 1; i < openCount; i++)
		{
			if (openList[i]->f < openList[minIndex]->f) 
			{
				minIndex = i;
			}
		}

		// 現在のノード
		Node* current = openList[minIndex];

		// ゴールに到達
		if (current->x == goalX && current->y == goalY) 
		{
			return current;
		}

		// 開いたリストから削除し、閉じたリストに追加
		openCount--;
		openList[minIndex] = openList[openCount];
		closedList[current->y][current->x] = true;

		// 移動方向（上下左右）
		int dx[] = { 1, -1, 0, 0 };
		int dy[] = { 0, 0, 1, -1 };

		for (int i = 0; i < 4; i++) 
		{
			int newX = current->x + dx[i];
			int newY = current->y + dy[i];

			if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT)
			{
				continue;
			}
			if (map[newY][newX] == 1 || closedList[newY][newX])
			{
				continue;
			}

			float gNew = current->g + 1;
			float hNew = heuristic(newX, newY, goalX, goalY);
			float fNew = gNew + hNew;

			Node* newNode = (Node*)malloc(sizeof(Node));
			if (!newNode) 
			{
				return NULL;
			}

			newNode->x = newX;
			newNode->y = newY;
			newNode->g = gNew;
			newNode->h = hNew;
			newNode->f = fNew;
			newNode->parent = current;

			openList[openCount++] = newNode;
		}
	}

	return NULL; // 経路が見つからなかった
}
//======================================================
// 捕まった判定
//======================================================
bool GetEnd(void)
{
	return g_bEnd;
}
//======================================================
// 視界に入ったか判定
//======================================================
bool GetInside(void)
{
	return Inside;
}