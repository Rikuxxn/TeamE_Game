//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "meshfield.h"
#include "meshceiling.h"
#include "camera.h"
#include "light.h"
#include "block.h"
#include "edit.h"
#include "player.h"
#include "main.h"
#include "ui.h"
#include "sound.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TITLE] = {};		//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureTitleBG = NULL;				//テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleBG = NULL;			//頂点バッファへのポインタ

TITLE_MENU g_titleMenu;										//ポーズメニュー
bool g_bSelect;												//選ばれているか

// タイトル項目の拡大率を管理する配列
float titleScales[MAX_TITLE] = { TITLE_MIN_SCALE, TITLE_MIN_SCALE };

// 項目ごとの透明度を保持する配列
float titleAlphas[MAX_TITLE] = { 0.3f, 0.3f };				// 初期は全て半透明（範囲外状態）

HWND hWnd;

//========================
// タイトルの初期化
//========================
void InitTitle(void)
{
	Player* pPlayer = GetPlayer();

	// カーソルを表示する
	SetCursorVisibility(true);

	// メッシュフィールドの初期化処理
	InitMeshfield();

	// メッシュシーリングの初期化処理
	InitMeshCeiling();

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	// ブロックの初期化処理
	InitBlock();

	// プレイヤーの初期化処理
	InitPlayer();

	// エディット読み込み
	LoadParticular(PATH_TITLE);


	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ライトの種類
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),    // 暗めの白い光
		D3DXVECTOR3(0.0f, -1.0f, 0.0f),       // 真下方向
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // 天井の位置（無視される）
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ライトの種類
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),    // 暗めの白い光
		D3DXVECTOR3(-1.0f, 0.0f, 0.0f),       // 左方向
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // 天井の位置（無視される）
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ライトの種類
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),    // 暗めの白い光
		D3DXVECTOR3(0.0f, 0.0f, -1.0f),       // 手前方向
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // 天井の位置（無視される）
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ライトの種類
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),    // 暗めの白い光
		D3DXVECTOR3(1.0f, 0.0f, 0.0f),       // 右方向
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // 天井の位置（無視される）
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ライトの種類
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),    // 暗めの白い光
		D3DXVECTOR3(0.0f, 0.0f, 1.0f),       // 奥方向
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // 天井の位置（無視される）
	);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int title = 0; title < MAX_TITLE; title++)
	{
		D3DXCreateTextureFromFile(pDevice,
			TITLE_TEXTURE[title],
			&g_apTextureTitle[title]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	int nCntTitle;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(500.0f, (150.0f + nCntTitle * 150), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f, (150.0f + nCntTitle * 150), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, (250.0f + nCntTitle * 150), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, (250.0f + nCntTitle * 150), 0.0f);

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
	g_pVtxBuffTitle->Unlock();

	g_titleMenu = TITLE_MENU_START;
	g_bSelect = false;
	PlaySound(SOUND_LABEL_TITLEBGM);
}
//========================
// タイトルの終了
//========================
void UninitTitle(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); // 事前に作成・初期化されているデバイス

	// 霧の無効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//メッシュフィールドの終了処理
	UninitMeshfield();

	//メッシュシーリングの終了処理
	UninitMeshCeiling();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//ブロックの終了処理
	UninitBlock();

	//プレイヤーの終了処理
	UninitPlayer();

	//サウンドの停止
	StopSound(SOUND_LABEL_TITLEBGM);

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		//テクスチャの破棄
		if (g_apTextureTitle[nCnt] != NULL)
		{
			g_apTextureTitle[nCnt]->Release();
			g_apTextureTitle[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}
//========================
// タイトルの更新
//========================
void UpdateTitle(void)
{

	//メッシュフィールドの更新処理
	UpdateMeshfield();

	//メッシュシーリングの更新処理
	UpdateMeshCeiling();

	//カメラの更新処理
	UpdateCamera();

	////ライトの更新処理
	//UpdateLight(0, D3DXVECTOR3(0.0f, -1.0f, 0.0f));

	// ライトの点滅更新処理
	UpdateLightBlinking(0.016f);

	////ブロックの更新処理
	//UpdateBlock();

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

	// ゲームパッドでマウスカーソルを動かす
	UpdateCursorWithGamepad();

	// マウスカーソルが当たっている項目を探す
	int selectedByMouse = -1; // -1は未選択

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		float scale = titleScales[nCnt];
		float centerX = 1060.0f; // 中心X座標
		float centerY = 450.0f + nCnt * 120.0f; // 中心Y座標

		// 領域の計算
		float left = centerX - 150.0f * scale;
		float right = centerX + 150.0f * scale;
		float top = centerY - 30.0f * scale;
		float bottom = centerY + 30.0f * scale;

		// 範囲内判定
		if (mouseX >= left && mouseX <= right &&
			mouseY >= top && mouseY <= bottom)
		{
			selectedByMouse = nCnt; // 項目のインデックスを記録
			g_titleMenu = (TITLE_MENU)(nCnt); // 選択状態を更新
		}
	}

	// 項目の透明度を更新
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (selectedByMouse == -1)
		{
			// 範囲外ならすべて半透明
			titleAlphas[nCnt] -= 0.1f; // 徐々に薄く
			if (titleAlphas[nCnt] < 0.3f) titleAlphas[nCnt] = 0.3f;
			else
			{
				g_bSelect = false;
			}
		}
		else if (nCnt == g_titleMenu)
		{
			// 選択中の項目は濃く
			titleAlphas[nCnt] += 0.1f; // 徐々に濃く
			if (titleAlphas[nCnt] > 1.0f)
			{
				titleAlphas[nCnt] = 1.0f;
			}
			if (g_bSelect == false)
			{
				PlaySound(SOUND_LABEL_SELECT);
				g_bSelect = true;
			}
		}
		else
		{
			// 非選択の項目は薄く
			titleAlphas[nCnt] -= 0.1f; // 徐々に薄く

			if (titleAlphas[nCnt] < 0.3f)
			{
				titleAlphas[nCnt] = 0.3f;
			}
		}
	}

	// 頂点バッファのロック
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 項目の描画設定
	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		float scale = titleScales[nCntTitle];
		float centerX = 1060.0f;
		float centerY = 450.0f + nCntTitle * 120.0f;

		// 頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(centerX - 150.0f * scale, centerY - 30.0f * scale, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(centerX + 150.0f * scale, centerY - 30.0f * scale, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(centerX - 150.0f * scale, centerY + 30.0f * scale, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(centerX + 150.0f * scale, centerY + 30.0f * scale, 0.0f);

		// カラー設定
		D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, titleAlphas[nCntTitle]);

		// 頂点カラーを設定
		for (int nCntTitle2 = 0; nCntTitle2 < 4; nCntTitle2++)
		{
			pVtx[nCntTitle2].col = color;
		}

		// 頂点ポインタを次の項目に進める
		pVtx += 4;
	}

	// 頂点バッファのアンロック
	g_pVtxBuffTitle->Unlock();

	// 範囲内クリックの場合のみ処理を実行
	if (g_fade == FADE_NONE && (GetMouseButtonTrigger(0) || JoyPadTrigger(JOYKEY_A) == true))
	{
		if (selectedByMouse != -1)
		{
			// 範囲内の項目がクリックされた場合
			switch (g_titleMenu)
			{
			case TITLE_MENU_START:

				// ゲーム画面に移行
				SetFade(MODE_TUTORIAL);
				PlaySound(SOUND_LABEL_GAMESTART);
				break;

			case TITLE_MENU_QUIT:

				//ライトの終了処理
				UninitLight();

				//ウィンドウを破棄する
				PostQuitMessage(0);

				break;
			}
		}
		// 範囲外をクリックした場合は何もしない
	}


#ifdef _DEBUG
	if (KeyboardTrigger(DIK_F1) == true && g_fade == FADE_NONE)
	{
		//エディット画面に移行
		SetFade(MODE_EDIT);
	}
#endif
}
//========================
// タイトルの描画
//========================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice; // 事前に作成・初期化されているデバイス

	//デバイスの取得
	pDevice = GetDevice();

	SetupVertexFog(pDevice, D3DCOLOR_XRGB(0, 0, 0), D3DFOG_LINEAR, TRUE, 0.0f);

	//プレイヤーの描画処理
	DrawPlayer();

	//カメラの設定処理
	SetCamera();

	//メッシュフィールドの描画処理
	DrawMeshfield();

	//メッシュシーリングの描画処理
	DrawMeshCeiling();

	//ブロックの描画処理
	DrawBlock();

	int nCntTitle;

	// 霧の無効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTitle[nCntTitle]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}

	// 霧の有効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}
