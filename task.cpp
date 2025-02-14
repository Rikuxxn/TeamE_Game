//=============================================================================
//
// タスク処理 [task.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "task.h"
#include "block.h"
#include "game.h"
#include "sound.h"

// グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTask[TASKTYPE_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTask = NULL;			//頂点バッファへのポインタ
TASK g_aTask[MAX_TASK];

int g_nCntTask;

//============================================
// タスクUI表示の初期化処理
//============================================
void InitTask(void)
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntTask;

	for (int nCnt = 0; nCnt < TASKTYPE_MAX; nCnt++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			TASK_TEXTURE[nCnt],
			&g_pTextureTask[nCnt]);
	}

	//タスク完了UIの情報の初期化
	for (nCntTask = 0; nCntTask < MAX_TASK; nCntTask++)
	{
		g_aTask[nCntTask].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTask[nCntTask].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTask[nCntTask].fWidth = 0.0f;
		g_aTask[nCntTask].fHeight = 0.0f;
		g_aTask[nCntTask].nType = TASKTYPE_ONE;
		g_aTask[nCntTask].bUse = false;

	}
	g_nCntTask = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TASK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTask,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTask->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTask = 0; nCntTask < MAX_TASK; nCntTask++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(4.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(4.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める

	}

	//頂点バッファをアンロックする
	g_pVtxBuffTask->Unlock();

}
//============================================
//タスクUI表示の終了処理
//============================================
void UninitTask(void)
{

	for (int nCntTask = 0; nCntTask < TASKTYPE_MAX; nCntTask++)
	{
		//テクスチャの破棄
		if (g_pTextureTask[nCntTask] != NULL)
		{
			g_pTextureTask[nCntTask]->Release();
			g_pTextureTask[nCntTask] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTask != NULL)
	{
		g_pVtxBuffTask->Release();
		g_pVtxBuffTask = NULL;
	}
}
//============================================
// タスクUI表示の更新処理
//============================================
void UpdateTask(void)
{
	GAME* pGame = GetGame();
	Flags* pFlag = GetFlag();


	VERTEX_2D* pVtx;

	int nCntTask;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTask->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTask = 0; nCntTask < MAX_TASK; nCntTask++)
	{
		if (pFlag->bFuseCmp == false && g_aTask[nCntTask].nType == TASKTYPE_ONE)
		{
			if (g_aTask[nCntTask].pos.x <= 1130.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}
		else if (pFlag->bFuseCmp == false && g_aTask[nCntTask].nType == TASKTYPE_SUB1)
		{
			if (g_aTask[nCntTask].pos.x <= 1170.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}
		else if (pFlag->bFuseCmp == false && g_aTask[nCntTask].nType == TASKTYPE_SUB2)
		{
			if (g_aTask[nCntTask].pos.x <= 1160.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}
		else if (pFlag->bFuseCmp == true && pGame->bSTClear == false && pGame->bACClear == false &&
			pGame->bBallClear == false && g_aTask[nCntTask].nType == TASKTYPE_TWO)
		{
			if (g_aTask[nCntTask].pos.x <= 1120.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}
		else if (pFlag->bFuseCmp == true && pGame->bSTClear == false && pGame->bACClear == false &&
			pGame->bBallClear == false && g_aTask[nCntTask].nType == TASKTYPE_SUB3)
		{
			if (g_aTask[nCntTask].pos.x <= 1160.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}
		else if (pFlag->bFuseCmp == true && pGame->bSTClear == false && pGame->bACClear == false &&
			pGame->bBallClear == false && g_aTask[nCntTask].nType == TASKTYPE_SUB4)
		{
			if (g_aTask[nCntTask].pos.x <= 1150.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}
		else if (pFlag->bFuseCmp == true && pGame->bSTClear == false && pGame->bACClear == false &&
			pGame->bBallClear == false && g_aTask[nCntTask].nType == TASKTYPE_SUB5)
		{
			if (g_aTask[nCntTask].pos.x <= 1150.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}
		else if (pGame->bSTClear == true && pGame->bACClear == true && pGame->bBallClear == true && g_aTask[nCntTask].nType == TASKTYPE_THREE)
		{
			if (g_aTask[nCntTask].pos.x <= 1120.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}
		else if (pGame->bSTClear == true && pGame->bACClear == true && pGame->bBallClear == true && g_aTask[nCntTask].nType == TASKTYPE_SUB6)
		{
			if (g_aTask[nCntTask].pos.x <= 1150.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}

		// ヒューズを見つけたら
		if (pFlag->bFuseGet == true)
		{
			if (g_aTask[nCntTask].nType == TASKTYPE_SUB1)
			{
				g_aTask[nCntTask].bUse = false;
				SetTask(D3DXVECTOR3(1165.0f, 230.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB1_CMP);
				PlaySound(SOUND_LABEL_TASKOK);
			}
		}

		// ヒューズを付けたら
		if (pFlag->bFuseCmp == true)
		{
			if (g_aTask[nCntTask].nType == TASKTYPE_ONE)
			{
				g_aTask[nCntTask].pos.x += 15.0f;

				if (g_aTask[nCntTask].pos.x >= 2350.0f)
				{
					g_aTask[nCntTask].pos.x += 0.0f;
					g_aTask[nCntTask].bUse = false;
				}
			}

			if (g_aTask[nCntTask].nType == TASKTYPE_SUB1_CMP)
			{
				g_aTask[nCntTask].pos.x += 15.0f;

				if (g_aTask[nCntTask].pos.x >= 2350.0f)
				{
					g_aTask[nCntTask].pos.x += 0.0f;
					g_aTask[nCntTask].bUse = false;
				}
			}
			if (g_aTask[nCntTask].nType == TASKTYPE_SUB2_CMP)
			{
				g_aTask[nCntTask].pos.x += 15.0f;

				if (g_aTask[nCntTask].pos.x >= 2350.0f)
				{
					g_aTask[nCntTask].pos.x += 0.0f;
					g_aTask[nCntTask].bUse = false;
				}
			}

			if (g_aTask[nCntTask].nType == TASKTYPE_SUB2)
			{
				g_aTask[nCntTask].bUse = false;
				SetTask(D3DXVECTOR3(1155.0f, 260.0f, 0.0f), 130.0f, 20.0f, TASKTYPE_SUB2_CMP);
				PlaySound(SOUND_LABEL_TASKOK);
			}
		}

		// クレーンゲームクリアしたら
		if (pGame->bACClear == true)
		{
			if (g_aTask[nCntTask].nType == TASKTYPE_SUB3)
			{
				g_aTask[nCntTask].bUse = false;
				SetTask(D3DXVECTOR3(1150.0f, 230.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB3_CMP);
				PlaySound(SOUND_LABEL_TASKOK);
			}
		}
		// シューティングクリアしたら
		if (pGame->bSTClear == true)
		{
			if (g_aTask[nCntTask].nType == TASKTYPE_SUB4)
			{
				g_aTask[nCntTask].bUse = false;
				SetTask(D3DXVECTOR3(1145.0f, 260.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB4_CMP);
				PlaySound(SOUND_LABEL_TASKOK);
			}
		}
		// ボールプールクリアしたら
		if (pGame->bBallClear == true)
		{
			if (g_aTask[nCntTask].nType == TASKTYPE_SUB5)
			{
				g_aTask[nCntTask].bUse = false;
				SetTask(D3DXVECTOR3(1145.0f, 290.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB5_CMP);
				PlaySound(SOUND_LABEL_TASKOK);
			}
		}

		// 暗証番号を入力完了
		if (pGame->bPassClear == true)
		{
			if (g_aTask[nCntTask].nType == TASKTYPE_SUB6)
			{
				g_aTask[nCntTask].bUse = false;
				SetTask(D3DXVECTOR3(1145.0f, 230.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB6_CMP);
				PlaySound(SOUND_LABEL_TASKOK);
			}
		}

		// ミニゲームをすべてクリアしたら
		if (pGame->bSTClear == true && pGame->bACClear == true && pGame->bBallClear == true)
		{
			if (g_aTask[nCntTask].nType == TASKTYPE_TWO)
			{
				g_aTask[nCntTask].pos.x += 15.0f;

				if (g_aTask[nCntTask].pos.x >= 2350.0f)
				{
					g_aTask[nCntTask].pos.x += 0.0f;
					g_aTask[nCntTask].bUse = false;
				}
			}

			if (g_aTask[nCntTask].nType == TASKTYPE_SUB3_CMP)
			{
				g_aTask[nCntTask].pos.x += 15.0f;

				if (g_aTask[nCntTask].pos.x >= 2350.0f)
				{
					g_aTask[nCntTask].pos.x += 0.0f;
					g_aTask[nCntTask].bUse = false;
				}
			}

			if (g_aTask[nCntTask].nType == TASKTYPE_SUB4_CMP)
			{
				g_aTask[nCntTask].pos.x += 15.0f;

				if (g_aTask[nCntTask].pos.x >= 2350.0f)
				{
					g_aTask[nCntTask].pos.x += 0.0f;
					g_aTask[nCntTask].bUse = false;
				}
			}

			if (g_aTask[nCntTask].nType == TASKTYPE_SUB5_CMP)
			{
				g_aTask[nCntTask].pos.x += 15.0f;

				if (g_aTask[nCntTask].pos.x >= 2350.0f)
				{
					g_aTask[nCntTask].pos.x += 0.0f;
					g_aTask[nCntTask].bUse = false;
				}
			}

		}

		//位置を更新
		g_aTask[nCntTask].pos.x += g_aTask[nCntTask].move.x;
		g_aTask[nCntTask].pos.y += g_aTask[nCntTask].move.y;

		//頂点座標の更新
		pVtx[1].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x + g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y - g_aTask[nCntTask].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x - g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y + g_aTask[nCntTask].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x + g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y + g_aTask[nCntTask].fHeight, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x - g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y - g_aTask[nCntTask].fHeight, 0.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTask->Unlock();

}
//============================================
// タスクUI表示の描画処理
//============================================
void DrawTask(void)
{

	int nCntTask;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTask, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTask = 0; nCntTask < MAX_TASK; nCntTask++)
	{
		if (g_aTask[nCntTask].bUse == true)
		{//ブロックが使用されている

			int nType = g_aTask[nCntTask].nType;

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureTask[nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTask * 4, 2);

		}
	}
}
//============================================
// タスクUI表示の設定処理
//============================================
void SetTask(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{

	int nCntTask;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTask->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTask = 0; nCntTask < MAX_TASK; nCntTask++)
	{

		if (g_aTask[nCntTask].bUse == false)
		{//UIが使用されていない

			g_aTask[nCntTask].pos = pos;
			g_aTask[nCntTask].nType = nType;
			g_aTask[nCntTask].fWidth = fWidth;
			g_aTask[nCntTask].fHeight = fHeight;
			g_aTask[nCntTask].bUse = true;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//頂点座標の更新
			pVtx[1].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x + g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y - g_aTask[nCntTask].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x - g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y + g_aTask[nCntTask].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x + g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y + g_aTask[nCntTask].fHeight, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x - g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y - g_aTask[nCntTask].fHeight, 0.0f);

			break;
		}
		pVtx += 4;

	}

	//頂点バッファをアンロックする
	g_pVtxBuffTask->Unlock();
}
