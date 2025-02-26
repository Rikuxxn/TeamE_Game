//=============================================================================
//
// ポーズ処理 [pause.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "pause.h"
#include "main.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTexturePause[MAX_PAUSE] = {};		//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_apTexturePauseBG = NULL;				//テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseBG = NULL;			//頂点バッファへのポインタ

PAUSE_MENU g_pauseMenu;										//ポーズメニュー
bool g_bPauseSelect;										//選ばれているか
bool g_bTutoDraw;											//チュートリアル描画用
bool g_bDraw;												// 

// ポーズ項目の拡大率を管理する配列
float pauseScales[MAX_PAUSE] = { PAUSE_MIN_SCALE, PAUSE_MIN_SCALE, PAUSE_MIN_SCALE, PAUSE_MIN_SCALE };

// 項目ごとの透明度を保持する配列
float pauseAlphas[MAX_PAUSE] = { 0.3f, 0.3f, 0.3f, 0.3f};		// 初期は全て半透明（範囲外状態）

//===============================================================
// ポーズの初期化処理
//===============================================================
void InitPause(void)
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntPause;
	g_bTutoDraw = false;
	g_bDraw = false;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\.png",
		&g_apTexturePauseBG);

	for (int i = 0; i < MAX_PAUSE; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			PAUSE_TEXTURE[i],
			&g_apTexturePause[i]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG,
		NULL);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);


	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//1つ目の頂点情報
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);		//2つ目の頂点情報
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);		//3つ目の頂点情報
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);	//4つ目の頂点情報

	//rhwの設定(1.0fで固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseBG->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(500.0f, (150.0f + nCntPause * 150), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f, (150.0f + nCntPause * 150), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, (250.0f + nCntPause * 150), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, (250.0f + nCntPause * 150), 0.0f);

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
	g_pVtxBuffPause->Unlock();

	g_pauseMenu = PAUSE_MENU_CONTINUE;

}
//===============================================================
// ポーズの終了処理
//===============================================================
void UninitPause(void)
{

	StopSound(SOUND_LABEL_SELECT);
	StopSound(SOUND_LABEL_OK);

	//テクスチャの破棄
	if (g_apTexturePauseBG != NULL)
	{
		g_apTexturePauseBG->Release();
		g_apTexturePauseBG = NULL;
	}

	int nCnt;

	for (nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		//テクスチャの破棄
		if (g_apTexturePause[nCnt] != NULL)
		{
			g_apTexturePause[nCnt]->Release();
			g_apTexturePause[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();
		g_pVtxBuffPauseBG = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

}
//===============================================================
// ポーズの更新処理
//===============================================================
void UpdatePause(void)
{
	FADE g_fade = GetFade(); // 現在の状態

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

	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++) 
	{
		float scale = pauseScales[nCnt];
		float centerX = 660.0f;					// 中心X座標
		float centerY = 180.0f + nCnt * 150.0f; // 中心Y座標

		// 領域の計算
		float left = centerX - 140.0f * scale;
		float right = centerX + 140.0f * scale;
		float top = centerY - 40.0f * scale;
		float bottom = centerY + 40.0f * scale;

		// 範囲内判定
		if (mouseX >= left && mouseX <= right &&
			mouseY >= top && mouseY <= bottom) 
		{
			selectedByMouse = nCnt;							// 項目のインデックスを記録
			g_pauseMenu = (PAUSE_MENU)(nCnt);	// 選択状態を更新
		}
	}

	if (g_bTutoDraw == false)
	{
		// 項目の透明度を更新
		for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++) 
		{
			if (selectedByMouse == -1) 
			{
				// 範囲外ならすべて半透明
				pauseAlphas[nCnt] -= 0.1f; // 徐々に薄く
				if (pauseAlphas[nCnt] < 0.3f) pauseAlphas[nCnt] = 0.3f;
				else
				{
					g_bPauseSelect = false;
				}
			}
			else if (nCnt == g_pauseMenu) 
			{
				// 選択中の項目は濃く
				pauseAlphas[nCnt] += 0.1f; // 徐々に濃く
				if (pauseAlphas[nCnt] > 1.0f)
				{
					pauseAlphas[nCnt] = 1.0f;
				}
				if (g_bPauseSelect == false)
				{
					PlaySound(SOUND_LABEL_SELECT);
					g_bPauseSelect = true;
				}
			}
			else 
			{
				// 非選択の項目は薄く
				pauseAlphas[nCnt] -= 0.1f; // 徐々に薄く

				if (pauseAlphas[nCnt] < 0.3f)
				{
					pauseAlphas[nCnt] = 0.3f;
				}
			}
		}

		// 頂点バッファのロック
		g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

		// 項目の描画設定
		for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++) 
		{
			float scale = pauseScales[nCntPause];
			float centerX = 660.0f;
			float centerY = 180.0f + nCntPause * 150.0f;

			// 頂点座標を設定
			pVtx[0].pos = D3DXVECTOR3(centerX - 140.0f * scale, centerY - 40.0f * scale, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(centerX + 140.0f * scale, centerY - 40.0f * scale, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(centerX - 140.0f * scale, centerY + 40.0f * scale, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(centerX + 140.0f * scale, centerY + 40.0f * scale, 0.0f);

			// カラー設定
			D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, pauseAlphas[nCntPause]);

			// 頂点カラーを設定
			for (int nCntPause2 = 0; nCntPause2 < 4; nCntPause2++) 
			{
				pVtx[nCntPause2].col = color;
			}

			// 頂点ポインタを次の項目に進める
			pVtx += 4;
		}

		// 頂点バッファのアンロック
		g_pVtxBuffPause->Unlock();

		// 範囲内クリックの場合のみ処理を実行
		if (g_fade == FADE_NONE && GetMouseButtonTrigger(0)) 
		{
			if (selectedByMouse != -1) 
			{
				// 範囲内の項目がクリックされた場合
				switch (g_pauseMenu) 
				{
				case PAUSE_MENU_CONTINUE:		// 続ける
					SetEnablePause(false);
					PlaySound(SOUND_LABEL_OK);
					break;
				case PAUSE_MENU_RETRY:			// リトライ
					SetFade(MODE_GAME);
					PlaySound(SOUND_LABEL_OK);
					break;
				case PAUSE_MENU_TUTORIAL:		// 操作確認
					SetDraw(true);
					PlaySound(SOUND_LABEL_OK);
					break;
				case PAUSE_MENU_QUIT:			// やめる
					SetFade(MODE_TITLE);
					PlaySound(SOUND_LABEL_OK);
					break;
				}
			}
			// 範囲外をクリックした場合は何もしない
		}

	}
}
//===============================================================
// ポーズの描画処理
//===============================================================
void DrawPause(void)
{
	int nCntPause;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//===============
	// 背景
	//===============

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//===============
	// ポーズ項目
	//===============

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePause[nCntPause]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause*4, 2);

	}
}

void SetDraw(bool bDraw)
{
	g_bTutoDraw = bDraw;
}

bool GetTutoDraw(void)
{
	return g_bTutoDraw;
}