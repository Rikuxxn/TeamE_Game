//=============================================================================
//
// UI処理 [ui.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "ui.h"
#include "main.h"
#include "player.h"
#include "block.h"
#include "game.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureUI[UITYPE_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;		// 頂点バッファへのポインタ
UI g_aUI[MAX_UI];

//=========================================================
// UIの初期化処理
//=========================================================
void InitUI(void)
{
	int nCntUI;

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < UITYPE_MAX; nCnt++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			UI_TEXTURE[nCnt],
			&g_pTextureUI[nCnt]);
	}

	// UIの情報の初期化
	for (nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{
		g_aUI[nCntUI].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUI[nCntUI].fWidth = 0.0f;
		g_aUI[nCntUI].fHeight = 0.0f;
		g_aUI[nCntUI].nType = UITYPE_GAME;
		g_aUI[nCntUI].bUse = false;

	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUI,
		NULL);


	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		pVtx += 4;//頂点データのポインタを4つ分進める

	}

	//頂点バッファをアンロックする
	g_pVtxBuffUI->Unlock();

}
//==================================================
// UIの終了処理
//==================================================
void UninitUI(void)
{
	for (int nCntUI = 0; nCntUI < UITYPE_MAX; nCntUI++)
	{
		//テクスチャの破棄
		if (g_pTextureUI[nCntUI] != NULL)
		{
			g_pTextureUI[nCntUI]->Release();
			g_pTextureUI[nCntUI] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffUI != NULL)
	{
		g_pVtxBuffUI->Release();
		g_pVtxBuffUI = NULL;
	}
}
//============================================================
// UIの更新処理
//============================================================
void UpdateUI(void)
{

	VERTEX_2D* pVtx;

	MODE pMode = GetMode();
	Block* pBlock = GetBlock();
	Player* pPlayer = GetPlayer();
	GAME* pGame = GetGame();
	//Flags* pFlag = GetFlag();

	int nCntUI;

	bool bArcade = GetArcade();
	bool bCatcher = GetCatcher();
	bool bBall = GetBall();
	bool bKeypad = GetKeypad();
	bool bFuse = GetFuse();
	bool bFusebox = GetFusebox();

	bool bFuseGet = GetFuseGet();
	bool bFuseCmp = GetFuseCmp();
	bool bHintBall = GetHintBall();
	bool bHintBear = GetHintBear();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{

		// アーケードゲームの範囲内
		if (bArcade == true && bFuseCmp == true)
		{
			// UIを表示
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_GAME);
		}
		else// 範囲外
		{
			// falseにする
			g_aUI[nCntUI].bUse = false;
		}

		// UFOキャッチャーの範囲内
		if (bCatcher == true && bFuseCmp == true && pGame->bACClear == false)
		{
			// UIを表示
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_GAME);
		}
		else// 範囲外
		{
			// falseにする
			g_aUI[nCntUI].bUse = false;
		}

		// ボールプールの範囲内
		if (bBall == true && bFuseCmp == true && pGame->bBallClear == false)
		{
			// UIを表示
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_GAME);
		}
		else// 範囲外
		{
			// falseにする
			g_aUI[nCntUI].bUse = false;
		}

		// キーパッドの範囲内
		if (bKeypad == true && pGame->bSTClear == true && pGame->bACClear == true &&
			pGame->bBallClear == true && pGame->bPassClear == false)
		{
			// UIを表示
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_INPUT);
		}
		else// 範囲外
		{
			// falseにする
			g_aUI[nCntUI].bUse = false;
		}

		// ヒューズの範囲内
		if (bFuse == true)
		{
			// UIを表示
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_INTERACT);
		}
		else// 範囲外
		{
			// falseにする
			g_aUI[nCntUI].bUse = false;
		}

		// ヒューズボックスの範囲内
		if (bFusebox == true && bFuseGet == true && bFuseCmp == false)
		{
			// UIを表示
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_USE);
		}
		else// 範囲外
		{
			// falseにする
			g_aUI[nCntUI].bUse = false;
		}

		// ヒントボールの範囲内
		if (bHintBall == true)
		{
			// UIを表示
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_GAME);
		}
		else// 範囲外
		{
			// falseにする
			g_aUI[nCntUI].bUse = false;
		}

		// ヒントくまさんの範囲内
		if (bHintBear == true)
		{
			// UIを表示
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_GAME);
		}
		else// 範囲外
		{
			// falseにする
			g_aUI[nCntUI].bUse = false;
		}

		pVtx[0].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y - g_aUI[nCntUI].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y - g_aUI[nCntUI].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y + g_aUI[nCntUI].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y + g_aUI[nCntUI].fHeight, 0.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffUI->Unlock();

}
//=======================================================
// UIの描画処理
//=======================================================
void DrawUI(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffUI, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{
		if (!g_aUI[nCntUI].bUse)
		{
			continue; // 使用していない UI をスキップ
		}

		// 使用中の UI のみ描画処理を行う
		int nType = g_aUI[nCntUI].nType;

		pDevice->SetTexture(0, g_pTextureUI[nType]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUI * 4, 2);
	}
}
//===================================================
// UIの設定処理
//===================================================
void SetUI(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{

	int nCntUI;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{
		if (g_aUI[nCntUI].bUse == false)
		{
			g_aUI[nCntUI].pos = pos;
			g_aUI[nCntUI].nType = nType;
			g_aUI[nCntUI].fWidth = fWidth;
			g_aUI[nCntUI].fHeight = fHeight;
			g_aUI[nCntUI].bUse = true;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx[0].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y - g_aUI[nCntUI].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y - g_aUI[nCntUI].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y + g_aUI[nCntUI].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y + g_aUI[nCntUI].fHeight, 0.0f);

			break;
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffUI->Unlock();

}
//===================================================
// UI情報の取得
//===================================================
UI* GetUI(void)
{
	return &g_aUI[0];
}