//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "sound.h"
#include "time.h"
#include "enemy.h"
#include "block.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;						// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;						// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureClearSelect[MAX_GAMEOVER] = {};	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureGameoverSelect[MAX_GAMEOVER] = {};	// テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;				// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;					// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClearSelect = NULL;			// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameoverSelect = NULL;		// 頂点バッファへのポインタ

CLEAR_MENU g_clearMenu;											// クリアメニュー
GAMEOVER_MENU g_gameoverMenu;									// ゲームオーバーメニュー

// 項目の拡大率を管理する配列
float gameoverScales[MAX_GAMEOVER] = { GAMEOVER_MIN_SCALE, GAMEOVER_MIN_SCALE };
float clearScales[MAX_CLEAR] = { CLEAR_MIN_SCALE };

// 項目ごとの透明度を保持する配列
float clearAlphas[MAX_CLEAR] = { 0.3f };						// 初期は全て半透明（範囲外状態）
float gameoverAlphas[MAX_GAMEOVER] = { 0.3f, 0.3f };			// 初期は全て半透明（範囲外状態）

float g_fAlphaTime = 0.0f;										// タイム用のアルファ値
float g_fAlphaRank = 0.0f;										// ランク用のアルファ値

int g_nRankCnt = 0;
int g_nTimeCnt = 0;

LPDIRECT3DTEXTURE9 g_pTextureResultTimeMinute = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureResultTimeSecond = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureResultColon = NULL;				// テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultTimeMinute = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultTimeSecond = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultColon = NULL;			// 頂点バッファへのポインタ

D3DXVECTOR3 g_posResultTime;									// タイムの位置
Time g_aResultTime[MAX_RESULT_TIMEDIGIT];

int g_nResultMinutes;											// 分
int g_nResultSeconds;											// 秒

//================================================
//リザルト画面の初期化処理
//================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_fAlphaRank = 0.0f;			// フェードアルファ値をリセット
	g_nRankCnt = 0;

	Player* pPlayer = GetPlayer();	//プレイヤーの情報へのポインタ
	Block* pBlock = GetBlock();
	//Flags* pFlag = GetFlag();
	bool bEnd = GetEnd();
	bool bExit = GetExit();
	int nTimeMinutes = GetTimeMinutes();
	int nTimeSeconds = GetTimeSeconds();

	if (bExit == true)
	{//脱出したら

		////リザルト(ゲームクリア)画面に遷移
		//PlaySound(SOUND_LABEL_SCORE);

		//テクスチャの読み込み(背景)
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\resultBG.png",
			&g_pTextureResult);

		// 2分切ったら
		if (nTimeMinutes < 2 && nTimeSeconds >= 0)
		{// ランクA

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\rankA.png",
				&g_pTextureRank);

		}
		// 2分以上3分未満
		else if (nTimeMinutes >= 2 && nTimeMinutes < 3 && nTimeSeconds >= 0 && nTimeSeconds <= 59)
		{// ランクB

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\rankB.png",
				&g_pTextureRank);

		}
		// 3分以上
		else if (nTimeMinutes >= 3 && nTimeSeconds >= 0)
		{// ランクC

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\rankC.png",
				&g_pTextureRank);

		}

		for (int clear = 0; clear < MAX_CLEAR; clear++)
		{
			D3DXCreateTextureFromFile(pDevice,
				CLEAR_TEXTURE[clear],
				&g_pTextureClearSelect[clear]);
		}

	}
	else if (bEnd == true)
	{//捕まったらまたはタイムが0になったら

		////リザルト(ゲームオーバー)画面に遷移
		//PlaySound(SOUND_LABEL_GAMEOVER);

		//テクスチャの読み込み(背景)
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\gameoverBG.png",
			&g_pTextureResult);


		for (int gameover = 0; gameover < MAX_GAMEOVER; gameover++)
		{
			D3DXCreateTextureFromFile(pDevice,
				GAMEOVER_TEXTURE[gameover],
				&g_pTextureGameoverSelect[gameover]);
		}

	}
	

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CLEAR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffClearSelect,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GAMEOVER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameoverSelect,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(200,200,200,255);
	pVtx[1].col = D3DCOLOR_RGBA(200,200,200,255);
	pVtx[2].col = D3DCOLOR_RGBA(200,200,200,255);
	pVtx[3].col = D3DCOLOR_RGBA(200,200,200,255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	float rankX = 1110.0f; // ランクのX座標
	float rankY = 370.0f;  // ランクのY座標

	// ランクの頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(rankX, rankY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(rankX + 50.0f, rankY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(rankX, rankY + 70.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(rankX + 50.0f, rankY + 70.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffRank->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffClearSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntClear = 0; nCntClear < MAX_CLEAR; nCntClear++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(500.0f, (110.0f + nCntClear * 150), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f, (110.0f + nCntClear * 150), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, (210.0f + nCntClear * 150), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, (210.0f + nCntClear * 150), 0.0f);

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
	g_pVtxBuffClearSelect->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGameoverSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGameover = 0; nCntGameover < MAX_GAMEOVER; nCntGameover++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(500.0f, (110.0f + nCntGameover * 150), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f, (110.0f + nCntGameover * 150), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, (210.0f + nCntGameover * 150), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, (210.0f + nCntGameover * 150), 0.0f);

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
	g_pVtxBuffGameoverSelect->Unlock();

	g_clearMenu = CLEAR_MENU_TITLE;
	g_gameoverMenu = GAMEOVER_MENU_RETRY;

}
//=====================================================
//リザルト画面の終了処理
//=====================================================
void UninitResult(void)
{

	////サウンドの停止
	//StopSound(SOUND_LABEL_CLEAR);
	//StopSound(SOUND_LABEL_GAMEOVER);
	//StopSound(SOUND_LABEL_RANK);

	//テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_CLEAR; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureClearSelect[nCnt] != NULL)
		{
			g_pTextureClearSelect[nCnt]->Release();
			g_pTextureClearSelect[nCnt] = NULL;
		}
	}

	for (int nCnt2 = 0; nCnt2 < MAX_GAMEOVER; nCnt2++)
	{
		//テクスチャの破棄
		if (g_pTextureGameoverSelect[nCnt2] != NULL)
		{
			g_pTextureGameoverSelect[nCnt2]->Release();
			g_pTextureGameoverSelect[nCnt2] = NULL;
		}
	}


	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffClearSelect != NULL)
	{
		g_pVtxBuffClearSelect->Release();
		g_pVtxBuffClearSelect = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGameoverSelect != NULL)
	{
		g_pVtxBuffGameoverSelect->Release();
		g_pVtxBuffGameoverSelect = NULL;
	}

}
//=====================================================
//リザルト画面の更新処理
//=====================================================
void UpdateResult(void)
{
	FADE g_fade = GetFade(); // 現在の状態
	Block* pBlock = GetBlock();
	//Flags* pFlag = GetFlag();
	VERTEX_2D* pVtx;

	// マウスカーソルの位置を取得
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	// ウィンドウハンドルを取得
	HWND hwnd = GetActiveWindow();

	// スクリーン座標をクライアント座標に変換
	ScreenToClient(hwnd, &cursorPos);

	// クライアントサイズを取得
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	bool bExit = GetExit();
	//nTime = GetTime();

	Player* pPlayer = GetPlayer();

	g_nRankCnt++;

	// ランク表示フェード
	if (g_nRankCnt >= 300)
	{
		if (g_fAlphaRank < 255.0f)
		{
			g_fAlphaRank += 2.0f; // フェード速度調整

			if (g_fAlphaRank > 255.0f)
			{
				g_fAlphaRank = 255.0f;
			}
		}
	}
	if (g_nRankCnt <= 300 && bExit == true)
	{
		//PlaySound(SOUND_LABEL_RANK);
	}
	
	// ウィンドウスケールを計算
	float screenWidth = 1280.0f; // ゲームの解像度
	float screenHeight = 720.0f;
	float scaleX = screenWidth / (clientRect.right - clientRect.left);
	float scaleY = screenHeight / (clientRect.bottom - clientRect.top);

	// マウス座標をスケール
	float mouseX = cursorPos.x * scaleX;
	float mouseY = cursorPos.y * scaleY;

	// マウスカーソルが当たっている項目を探す
	int selectedByMouse = -1; // -1は未選択

	if (bExit == true)
	{
		for (int nCnt = 0; nCnt < MAX_CLEAR; nCnt++)
		{
			float scale = clearScales[nCnt];
			float centerX = 980.0f; // 中心X座標
			float centerY = 600.0f + nCnt * 150.0f; // 中心Y座標

			// 領域の計算
			float left = centerX - 78.0f * scale;
			float right = centerX + 78.0f * scale;
			float top = centerY - 10.0f * scale;
			float bottom = centerY + 10.0f * scale;

			// 範囲内判定
			if (mouseX >= left && mouseX <= right &&
				mouseY >= top && mouseY <= bottom)
			{
				selectedByMouse = nCnt; // 項目のインデックスを記録
				g_clearMenu = static_cast<CLEAR_MENU>(nCnt); // 選択状態を更新
			}
		}

		// 項目の透明度を更新
		for (int nCnt = 0; nCnt < MAX_CLEAR; nCnt++)
		{
			if (selectedByMouse == -1)
			{
				// 範囲外ならすべて半透明
				clearAlphas[nCnt] -= 0.2f; // 徐々に薄く
				if (clearAlphas[nCnt] < 0.3f)
				{
					clearAlphas[nCnt] = 0.3f;
				}
			}
			else if (nCnt == g_clearMenu)
			{
				// 選択中の項目は濃くする
				clearAlphas[nCnt] += 0.2f; // 徐々に濃く
				if (clearAlphas[nCnt] > 1.0f)
				{
					clearAlphas[nCnt] = 1.0f;
				}
			}
			else
			{
				// 非選択の項目は薄く
				clearAlphas[nCnt] -= 0.1f; // 徐々に薄く

				if (clearAlphas[nCnt] < 0.3f)
				{
					clearAlphas[nCnt] = 0.3f;
				}
			}
		}

		// 頂点バッファのロック
		g_pVtxBuffClearSelect->Lock(0, 0, (void**)&pVtx, 0);

		// 項目の描画設定
		for (int nCntClear = 0; nCntClear < MAX_CLEAR; nCntClear++)
		{
			float scale = clearScales[nCntClear];
			float centerX = 980.0f;
			float centerY = 600.0f + nCntClear * 150.0f;

			// 頂点座標を設定
			pVtx[0].pos = D3DXVECTOR3(centerX - 78.0f * scale, centerY - 10.0f * scale, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(centerX + 78.0f * scale, centerY - 10.0f * scale, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(centerX - 78.0f * scale, centerY + 10.0f * scale, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(centerX + 78.0f * scale, centerY + 10.0f * scale, 0.0f);

			// カラー設定
			D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, clearAlphas[nCntClear]);

			// 頂点カラーを設定
			for (int nCntClear2 = 0; nCntClear2 < 4; nCntClear2++)
			{
				pVtx[nCntClear2].col = color;
			}

			// 頂点ポインタを次の項目に進める
			pVtx += 4;
		}

		// 頂点バッファのアンロック
		g_pVtxBuffClearSelect->Unlock();

		// 範囲内クリックの場合のみ処理を実行
		if (g_fade == FADE_NONE && GetMouseButtonTrigger(0))
		{
			if (selectedByMouse != -1)
			{
				// 範囲内の項目がクリックされた場合
				switch (g_clearMenu)
				{
				case CLEAR_MENU_TITLE:

					// タイトル画面に移行
					SetFade(MODE_TITLE);

					break;
				}
			}
			// 範囲外をクリックした場合は何もしない
		}

	}
	else if (bExit == false)
	{
		for (int nCnt = 0; nCnt < MAX_GAMEOVER; nCnt++)
		{
			float scale = gameoverScales[nCnt];
			float centerX = 1010.0f; // 中心X座標
			float centerY = 300.0f + nCnt * 150.0f; // 中心Y座標

			// 領域の計算
			float left = centerX - 150.0f * scale;
			float right = centerX + 150.0f * scale;
			float top = centerY - 20.0f * scale;
			float bottom = centerY + 20.0f * scale;

			// 範囲内判定
			if (mouseX >= left && mouseX <= right &&
				mouseY >= top && mouseY <= bottom)
			{
				selectedByMouse = nCnt; // 項目のインデックスを記録
				g_gameoverMenu = static_cast<GAMEOVER_MENU>(nCnt); // 選択状態を更新
			}
		}

		// 項目の透明度を更新
		for (int nCnt = 0; nCnt < MAX_GAMEOVER; nCnt++)
		{
			if (selectedByMouse == -1)
			{
				// 範囲外ならすべて半透明
				gameoverAlphas[nCnt] -= 0.1f; // 徐々に薄く
				if (gameoverAlphas[nCnt] < 0.3f) gameoverAlphas[nCnt] = 0.3f;
			}
			else if (nCnt == g_gameoverMenu)
			{
				// 選択中の項目は濃くする
				gameoverAlphas[nCnt] += 0.1f; // 徐々に濃く
				if (gameoverAlphas[nCnt] > 1.0f)
				{
					gameoverAlphas[nCnt] = 1.0f;
				}
			}
			else
			{
				// 非選択の項目は薄く
				gameoverAlphas[nCnt] -= 0.1f; // 徐々に薄く

				if (gameoverAlphas[nCnt] < 0.3f)
				{
					gameoverAlphas[nCnt] = 0.3f;
				}
			}
		}

		// 頂点バッファのロック
		g_pVtxBuffGameoverSelect->Lock(0, 0, (void**)&pVtx, 0);

		// 項目の描画設定
		for (int nCntGameover = 0; nCntGameover < MAX_GAMEOVER; nCntGameover++)
		{
			float scale = gameoverScales[nCntGameover];
			float centerX = 1010.0f;
			float centerY = 300.0f + nCntGameover * 150.0f;

			// 頂点座標を設定
			pVtx[0].pos = D3DXVECTOR3(centerX - 150.0f * scale, centerY - 20.0f * scale, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(centerX + 150.0f * scale, centerY - 20.0f * scale, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(centerX - 150.0f * scale, centerY + 20.0f * scale, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(centerX + 150.0f * scale, centerY + 20.0f * scale, 0.0f);

			// カラー設定
			D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, gameoverAlphas[nCntGameover]);

			// 頂点カラーを設定
			for (int nCntGameover2 = 0; nCntGameover2 < 4; nCntGameover2++)
			{
				pVtx[nCntGameover2].col = color;
			}

			// 頂点ポインタを次の項目に進める
			pVtx += 4;
		}

		// 頂点バッファのアンロック
		g_pVtxBuffGameoverSelect->Unlock();

		// 範囲内クリックの場合のみ処理を実行
		if (g_fade == FADE_NONE && GetMouseButtonTrigger(0))
		{
			if (selectedByMouse != -1)
			{
				// 範囲内の項目がクリックされた場合
				switch (g_gameoverMenu)
				{
				case GAMEOVER_MENU_RETRY:

					// ゲーム画面に移行
					SetFade(MODE_GAME);

					break;

				case GAMEOVER_MENU_TITLE:

					// タイトル画面に移行
					SetFade(MODE_TITLE);

					break;
				}
			}
			// 範囲外をクリックした場合は何もしない
		}
	}
}
//=====================================================
//リザルト画面の描画処理
//=====================================================
void DrawResult(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();//プレイヤーの情報へのポインタ
	Block* pBlock = GetBlock();
	//Flags* pFlag = GetFlag();
	bool bExit = GetExit();
	int nTimeMinutes = GetTimeMinutes();
	int nTimeSeconds = GetTimeSeconds();

	VERTEX_2D* pVtx;

	//====================================
	// 背景の描画
	//====================================

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ゲームクリアの時
	if (bExit == true)
	{
		//====================================
		// ランク描画
		//====================================

		if (nTimeMinutes < 2 && nTimeSeconds >= 0)
		{

			// 頂点バッファをロック
			g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

			// アルファ値を反映
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);

			// 頂点バッファをアンロック
			g_pVtxBuffRank->Unlock();

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRank);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}
		else if (nTimeMinutes >= 2 && nTimeMinutes < 3 && nTimeSeconds >= 0 && nTimeSeconds <= 59)
		{

			// 頂点バッファをロック
			g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

			// アルファ値を反映
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);

			// 頂点バッファをアンロック
			g_pVtxBuffRank->Unlock();

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRank);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}
		else if (nTimeMinutes >= 3 && nTimeSeconds >= 0)
		{

			// 頂点バッファをロック
			g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

			// アルファ値を反映
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);

			// 頂点バッファをアンロック
			g_pVtxBuffRank->Unlock();

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRank);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}

		//====================================
		// 選択項目の描画
		//====================================

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffClearSelect, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int nCntClear = 0; nCntClear < MAX_CLEAR; nCntClear++)
		{

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureClearSelect[nCntClear]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntClear * 4, 2);

		}

	}


	// ゲームオーバーの時
	if (bExit == false)
	{

		//====================================
		// 選択項目の描画
		//====================================

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffGameoverSelect, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int nCntGameover = 0; nCntGameover < MAX_GAMEOVER; nCntGameover++)
		{

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureGameoverSelect[nCntGameover]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGameover * 4, 2);

		}
	}

}
//=============================
// リザルトタイムの初期化処理
//=============================
void InitResultTime(void)
{

	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み(分)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&g_pTextureResultTimeMinute);

	//テクスチャの読み込み(秒)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&g_pTextureResultTimeSecond);

	//テクスチャの読み込み(コロン)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\colon.png",
		&g_pTextureResultColon);

	//初期化
	g_posResultTime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置を初期化する(始まりの位置)
	g_nResultMinutes = 0;
	g_nResultSeconds = 0;

	g_fAlphaTime = 0.0f;			// フェードアルファ値をリセット
	g_nTimeCnt = 0;

	nCnt = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMEDIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultTimeMinute,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMEDIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultTimeSecond,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultColon,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultTimeMinute->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{

		g_aResultTime[nCnt].bUse = true;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(1010.0f + nCnt * 30.0f, 195.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1010.0f + nCnt * 30.0f + 40.0f, 195.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1010.0f + nCnt * 30.0f, 255.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1010.0f + nCnt * 30.0f + 40.0f, 255.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResultTimeMinute->Unlock();

	// コロンの頂点バッファをロック
	g_pVtxBuffResultColon->Lock(0, 0, (void**)&pVtx, 0);

	float colonX = 1085.0f; // コロンのX座標
	float colonY = 190.0f;  // コロンのY座標

	// コロンの頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(colonX, colonY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(colonX + 40.0f, colonY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(colonX, colonY + 70.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(colonX + 40.0f, colonY + 70.0f, 0.0f);

	for (int nCntColon = 0; nCntColon < 4; nCntColon++)
	{
		pVtx[nCntColon].rhw = 1.0f;
		pVtx[nCntColon].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	// コロンのテクスチャ座標設定（1枚の画像の場合は固定）
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffResultColon->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultTimeSecond->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{

		g_aResultTime[nCnt].bUse = true;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(1120.0f + nCnt * 30.0f, 195.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1120.0f + nCnt * 30.0f + 40.0f, 195.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1120.0f + nCnt * 30.0f, 255.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1120.0f + nCnt * 30.0f + 40.0f, 255.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResultTimeSecond->Unlock();

}
//=============================
// リザルトタイムの終了処理
//=============================
void UninitResultTime(void)
{

	//テクスチャの破棄(分)
	if (g_pTextureResultTimeMinute != NULL)
	{
		g_pTextureResultTimeMinute->Release();
		g_pTextureResultTimeMinute = NULL;
	}

	//テクスチャの破棄(秒)
	if (g_pTextureResultTimeSecond != NULL)
	{
		g_pTextureResultTimeSecond->Release();
		g_pTextureResultTimeSecond = NULL;
	}

	//テクスチャの破棄(コロン)
	if (g_pTextureResultColon != NULL)
	{
		g_pTextureResultColon->Release();
		g_pTextureResultColon = NULL;
	}

	//頂点バッファの破棄(分)
	if (g_pVtxBuffResultTimeMinute != NULL)
	{
		g_pVtxBuffResultTimeMinute->Release();
		g_pVtxBuffResultTimeMinute = NULL;
	}

	//頂点バッファの破棄(秒)
	if (g_pVtxBuffResultTimeSecond != NULL)
	{
		g_pVtxBuffResultTimeSecond->Release();
		g_pVtxBuffResultTimeSecond = NULL;
	}

	//頂点バッファの破棄(コロン)
	if (g_pVtxBuffResultColon != NULL)
	{
		g_pVtxBuffResultColon->Release();
		g_pVtxBuffResultColon = NULL;
	}

}
//=============================
// リザルトタイムの更新処理
//=============================
void UpdateResultTime(void)
{
	g_nTimeCnt++;

	if (g_nTimeCnt >= 120)
	{
		if (g_fAlphaTime < 255.0f)
		{
			g_fAlphaTime += 2.0f; // フェード速度調整

			if (g_fAlphaTime > 255.0f)
			{
				g_fAlphaTime = 255.0f;
			}
		}
	}

	int nMinutes = GetTimeMinutes();
	int nSeconds = GetTimeSeconds();

	VERTEX_2D* pVtx;

	g_nResultMinutes = nMinutes;
	g_nResultSeconds = nSeconds;

	int min10 = g_nResultMinutes / 10;	// 分の10の位
	int min1 = g_nResultMinutes % 10;	// 分の1の位
	int sec10 = g_nResultSeconds / 10;	// 秒の10の位
	int sec1 = g_nResultSeconds % 10;	// 秒の1の位

	float texOffset = 0.1f;				// 1桁分のテクスチャ範囲（0.0～1.0を10分割）

	//===============================
	// 分のテクスチャ設定
	//===============================

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultTimeMinute->Lock(0, 0, (void**)&pVtx, 0);

	// 分の10の位
	pVtx[0].tex = D3DXVECTOR2(texOffset * min10, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texOffset * min10 + texOffset, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(texOffset * min10, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(texOffset * min10 + texOffset, 1.0f);

	// 分の1の位
	pVtx[4].tex = D3DXVECTOR2(texOffset * min1, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(texOffset * min1 + texOffset, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(texOffset * min1, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(texOffset * min1 + texOffset, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffResultTimeMinute->Unlock();

	//===============================
	// 秒のテクスチャ設定
	//===============================

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultTimeSecond->Lock(0, 0, (void**)&pVtx, 0);

	// 秒の10の位
	pVtx[0].tex = D3DXVECTOR2(texOffset * sec10, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texOffset * sec10 + texOffset, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(texOffset * sec10, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(texOffset * sec10 + texOffset, 1.0f);

	// 秒の1の位
	pVtx[4].tex = D3DXVECTOR2(texOffset * sec1, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(texOffset * sec1 + texOffset, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(texOffset * sec1, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(texOffset * sec1 + texOffset, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffResultTimeSecond->Unlock();

}
//=============================
// リザルトタイムの描画処理
//=============================
void DrawResultTime(void)
{

	VERTEX_2D* pVtx;

	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//=================
	// 分
	//=================

	// 頂点バッファをロック
	g_pVtxBuffResultTimeMinute->Lock(0, 0, (void**)&pVtx, 0);

	// アルファ値を反映
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// アルファ値を反映
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// 頂点バッファをアンロック
	g_pVtxBuffResultTimeMinute->Unlock();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultTimeMinute, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{
		if (g_aResultTime[nCnt].bUse == true)
		{

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureResultTimeMinute);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}

	//=================
	// コロン
	//=================

	// 頂点バッファをロック
	g_pVtxBuffResultColon->Lock(0, 0, (void**)&pVtx, 0);

	// アルファ値を反映
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// 頂点バッファをアンロック
	g_pVtxBuffResultColon->Unlock();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultColon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultColon);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//=================
	// 秒
	//=================

	// 頂点バッファをロック
	g_pVtxBuffResultTimeSecond->Lock(0, 0, (void**)&pVtx, 0);

	// アルファ値を反映
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// アルファ値を反映
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// 頂点バッファをアンロック
	g_pVtxBuffResultTimeSecond->Unlock();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultTimeSecond, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{
		if (g_aResultTime[nCnt].bUse == true)
		{

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureResultTimeSecond);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}

}