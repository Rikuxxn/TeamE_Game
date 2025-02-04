//=======================================
//
// メイン処理[main.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

#include "main.h"
#include "fade.h"
#include "input.h"
#include "result.h"
#include "game.h"
#include "title.h"
#include "model.h"
#include "camera.h"
#include "block.h"
#include "edit.h"
#include "player.h"
#include "enemy.h"
#include "light.h"
#include "tutorial.h"
#include "password_game.h"

//プロトタイプ宣言
void DrawFPS(void);
void DrawOption(void);
void DrawEditInfo(void);
void DrawTitleInfo(void);

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;				//DirectX3Dオブジェクトへのポインタ
LPD3DXFONT g_pFont = NULL;				//フォントへのポインタ

LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_mode = MODE_TITLE;				//現在のモード
int g_nCountFPS = 0;					//FPSカウンター

RECT g_windowRect;						//ウィンドウを切り替えるための変数
bool g_isFullscreen = false;			//ウィンドウを切り替えるためのフラグ

//=======================================
//メイン関数
//=======================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);//メモリリーク検知

	DWORD dwCurrentTime;	//現在時刻
	DWORD dwExecLastTime;	//最後に処理した時刻


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),             //WNDCLASSEXのメモリサイズ
		CS_CLASSDC,                     //ウィンドウのスタイル
		WindowProc,                     //ウィンドウプロシージャ
		0,                              //0にする(通常は使用しない)
		0,                              //0にする
		hInstance,                      //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION), //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),     //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),     //クライアント領域の背景色
		NULL,                           //メニューバー
		CLASS_NAME,                     //ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)  //ファイルのアイコン
	};


	HWND hWnd;   //ウィンドウハンドル
	MSG msg;     //メッセージを格納する変数

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);


	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);


	//ウィンドウを生成
	hWnd = CreateWindowEx(0,		//拡張ウィンドウスタイル
		CLASS_NAME,					//ウィンドウクラスの名前
		WINDOW_NAME,				//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル
		CW_USEDEFAULT,				//ウィンドウの左上x座標
		CW_USEDEFAULT,				//左上y座標

		(rect.right - rect.left),	//幅
		(rect.bottom - rect.top),	//高さ

		NULL,						//親ウィンドウのハンドル
		NULL,						//メニューハンドルまたは子ウィンドウID
		hInstance,					//インスタンスハンドル
		NULL);						//ウィンドウ作成データ


	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}


	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;				//初期化する
	dwExecLastTime = timeGetTime();	//現在時刻を取得（保存）


	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	DWORD dwFrameCount;				//フレームカウント
	DWORD dwFPSLastTime;			//最後にFPSを計測した時刻


	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();


	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);		//仮想メッセージを文字メッセージへ変換
				DispatchMessage(&msg);		//ウィンドウ
			}

		}
		else
		{//DirectXの処理


			dwCurrentTime = timeGetTime();//現在時刻を取得


			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;//FPSを計測した時刻を保存

				dwFrameCount = 0;//フレームカウントをクリア

			}


			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過

				dwExecLastTime = dwCurrentTime;//処理開始の時刻[現在時刻]を保存


				dwCurrentTime = timeGetTime();//現在時刻を取得


				dwFrameCount++;//フレームカウントを加算


				//更新処理
				Update();


				//描画処理
				Draw();

			}

		}
	}

	//終了処理
	Uninit();


	//分解能を戻す
	timeEndPeriod(1);


	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}
//=============================================
//ウィンドウプロシージャ
//=============================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	//HDC hDC;

	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	switch (uMsg)
	{
	case WM_DESTROY:  //ウィンドウ破棄のメッセージ
		//WM_QUITメッセージを送る
		PostQuitMessage(0);

		break;
	case WM_KEYDOWN://キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE://[ESC]キーが押された
			// ライトの初期化
			UninitLight();

			//ウィンドウを破棄する
			DestroyWindow(hWnd);

			break;
		case VK_F11:
			ToggleFullscreen(hWnd);//F11でフルスクリーン
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//既定の処理を繰り返す
}
//=============================================
//初期化処理
//=============================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ



	//DirectX3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}


	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//ゲーム画面サイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//ゲーム画面サイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;							//バックバッファの形式
	d3dpp.BackBufferCount = 1;										//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE;							//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル



	//DirectX3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//DirectX3Dデバイスの生成
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//DirectX3Dデバイスの生成
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}

		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);


	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);



	//デバッグ表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);



	// キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ジョイパッドの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	// マウスの初期化処理
	if (FAILED(InitMouse(hInstance, hWnd)))
	{
		return E_FAIL;
	}


	////サウンドの初期化処理
	//InitSound(hWnd);


	//モードの設定
	SetMode(g_mode);


	//フェードの設定
	InitFade(g_mode);


	return S_OK;

}
//=============================================
//終了処理
//=============================================
void Uninit(void)
{

	////サウンドの初期化処理
	//UninitSound();


	//ジョイパッドの終了処理
	UninitJoypad();


	//キーボードの終了処理
	UninitKeyboard();


	//マウスの終了処理
	UninitMouse();


	//フェードの終了処理
	UninitFade();


	//デバッグ表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();

		g_pFont = NULL;
	}

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();

		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();

		g_pD3D = NULL;
	}

}
//=============================================
//更新処理
//=============================================
void Update(void)
{
	bool bExit = GetExit();


	//ジョイパッドの更新処理
	UpdateJoypad();


	//キーボードの更新処理
	UpdateKeyboard();


	//マウスの更新処理
	UpdateMouse();


	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UpdateTitle();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		UpdateTutorial();
		break;

	case MODE_GAME://ゲーム画面
		UpdateGame();
		break;

	case MODE_RESULT://リザルト画面
		UpdateResult();

		if (bExit == true)
		{
			UpdateResultTime();
		}

		break;

	//case MODE_RANKING://ランキング画面
	//	UpdateRanking();
	//	break;

	case MODE_EDIT://エディット画面
		UpdateEdit();
		break;
	}

	//フェードの更新処理
	UpdateFade();

}
//=============================================
//描画処理
//=============================================
void Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; // 事前に作成・初期化されているデバイス

	//デバイスの取得
	pDevice = GetDevice();

	bool bExit = GetExit();

	Camera* pCamera = GetCamera();

	//LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	////デバイスの取得
	//pDevice = GetDevice();

	////ビューポートの設定
	//pDevice->SetViewport(&pCamera->viewport);

	//画面クリア
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		switch (g_mode)
		{
		case MODE_TITLE://タイトル画面
			DrawTitle();

#ifdef _DEBUG
			//タイトル情報の表示
			DrawTitleInfo();
#endif
			break;

		case MODE_TUTORIAL://チュートリアル画面
			DrawTutorial();
			break;

		case MODE_GAME://ゲーム画面
			DrawGame();

#ifdef _DEBUG
			//操作方法の表示
			DrawOption();
#endif

			break;

		case MODE_RESULT://リザルト画面
			DrawResult();

			if (bExit == true)
			{
				//リザルトタイムの描画処理
				DrawResultTime();
			}

			break;

		//case MODE_RANKING://ランキング画面
		//	DrawRanking();
		//	break;
#ifdef _DEBUG
		case MODE_EDIT://エディット画面
			DrawEdit();

			//エディター情報の表示
			DrawEditInfo();

			break;
#endif

		}

		//フェードの描画処理
		DrawFade();


#ifdef _DEBUG

		//FPSの表示
		DrawFPS();

		//パスワードの答え
		DrawAPass(GetAnum());
		DrawAPass2(GetAnum2());
		DrawAPass3(GetAnum3());
		DrawAPass4(GetAnum4());
#endif
		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================
//FPS表示処理
//=============================================
void DrawFPS(void)
{

	RECT rect = { 5, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	char aStr[256];


	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);


	//テキストの描画
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
//=============================================
//操作方法表示処理
//=============================================
void DrawOption(void)
{
	Camera* pCamera = GetCamera();
	Player* pPlayer = GetPlayer();
	Enemy* pEnemy = GetEnemy();
	Block* pBlock = GetBlock();

	RECT rect = { 5, 20, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect2 = { 5, 40, SCREEN_WIDTH, SCREEN_HEIGHT };

	char aStr[128];
	char aStr2[128];

	//文字列に代入
	sprintf(&aStr[0], "プレイヤーの位置 (%f, %f, %f)\n",pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	sprintf(&aStr2[0], "カメラの向き (%f, %f, %f)\n", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);

	//テキストの描画
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr2[0], -1, &rect2, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
//=============================================
//エディター情報表示処理
//=============================================
void DrawEditInfo(void)
{
	Camera* pCamera = GetCamera();

	RECT rect = { 5, 20, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect2 = { 5, 40, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect3 = { 5, 60, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect4 = { 5, 100, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect5 = { 5, 120, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect6 = { 5, 140, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect7 = { 5, 160, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect8 = { 5, 180, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect9 = { 5, 200, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect10 = { 5, 260, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect11 = { 5, 280, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect12 = { 5, 300, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect13 = { 5, 320, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect14 = { 5, 340, SCREEN_WIDTH, SCREEN_HEIGHT };

	char aStr[128];
	char aStr2[128];
	char aStr3[128];
	char aStr4[128];
	char aStr5[128];
	char aStr6[128];
	char aStr7[128];
	char aStr8[128];
	char aStr9[128];
	char aStr10[128];
	char aStr11[128];
	char aStr12[128];
	char aStr13[128];
	char aStr14[128];

	wsprintf(&aStr[0], "タイトル画面 [F1]\n");
	wsprintf(&aStr2[0], "ブロック配置情報の保存 [F7]\n");
	wsprintf(&aStr3[0], "前回のブロック配置情報の読み込み [F6]\n");
	wsprintf(&aStr4[0], "ブロックの平行移動 : [↑/↓/←/→]\n");
	wsprintf(&aStr5[0], "ブロックの垂直移動 : [U/J]\n");
	wsprintf(&aStr6[0], "ブロックの種類変更 : [マウスホイール][O/L]\n");
	wsprintf(&aStr7[0], "ブロックの回転 : [Y/H]\n");
	wsprintf(&aStr8[0], "ブロックの設置 : [ENTER][左クリック]\n");
	wsprintf(&aStr9[0], "ブロックの破棄 : [DELETE]\n");
	wsprintf(&aStr10[0], "===============================\n");
	wsprintf(&aStr11[0], "  カメラ操作方法\n");
	wsprintf(&aStr12[0], "===============================\n");
	wsprintf(&aStr13[0], "  カメラ平行移動 : [W/A/S/D]\n");
	wsprintf(&aStr14[0], "  カメラ垂直移動 : [Z/C]\n");

	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr2[0], -1, &rect2, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr3[0], -1, &rect3, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr4[0], -1, &rect4, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr5[0], -1, &rect5, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr6[0], -1, &rect6, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr7[0], -1, &rect7, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr8[0], -1, &rect8, DT_LEFT, D3DCOLOR_RGBA(0, 255, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr9[0], -1, &rect9, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr10[0], -1, &rect10, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr11[0], -1, &rect11, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr12[0], -1, &rect12, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr13[0], -1, &rect13, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr14[0], -1, &rect14, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
//=============================================
//タイトル情報表示処理
//=============================================
void DrawTitleInfo(void)
{
	RECT rect = { 5, 20, SCREEN_WIDTH, SCREEN_HEIGHT };

	char aStr[128];

	wsprintf(&aStr[0], "エディターモード [F1]\n");

	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 255, 0, 255));

}
//=============================================
//モードの設定
//=============================================
void SetMode(MODE mode)
{
	LPDIRECT3DDEVICE9 pDevice; // 事前に作成・初期化されているデバイス

	//デバイスの取得
	pDevice = GetDevice();

	//現在の画面の終了処理
	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UninitTitle();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		UninitTutorial();
		break;

	case MODE_GAME://ゲーム画面
		UninitGame();
		break;

	case MODE_RESULT://リザルト画面
		UninitResult();
		UninitResultTime();

		break;

	//case MODE_RANKING://ランキング画面
	//	UninitRanking();
	//	break;

	case MODE_EDIT://エディット画面
		UninitEdit();
		break;
	}



	//新しい画面の初期化処理
	switch (mode)
	{
	case MODE_TITLE://タイトル画面
		InitTitle();

		break;

	case MODE_TUTORIAL://チュートリアル画面
		InitTutorial();
		break;

	case MODE_GAME://ゲーム画面
		InitGame();
		break;

	case MODE_RESULT://リザルト画面
		InitResult();
		InitResultTime();

		break;

	//case MODE_RANKING://ランキング画面
	//	InitRanking();
	//	break;

	case MODE_EDIT://エディット画面
		InitEdit();
		break;
	}

	g_mode = mode;//現在の画面を切り替える

}
//=============================================
//デバイスの取得
//=============================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================================
//モードの取得
//=============================================
MODE GetMode(void)
{
	return g_mode;
}
//============================================================
// ウィンドウフルスクリーン処理
//============================================================
void ToggleFullscreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;

}
//============================================================
// 霧の設定処理
//============================================================
void SetupVertexFog(LPDIRECT3DDEVICE9 pDevice, DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density)
{

	MODE pMode = GetMode();

	float Start = 0.0f;			// 霧の開始距離
	float End = 0.0f;			// 霧の終了距離

	if (pMode == MODE_TITLE)
	{
		// 霧の開始・終了距離を遠めに設定
		Start = 100.0f;	// 霧の開始距離
		End = 1000.0f;	// 霧の終了距離
	}
	else if (pMode == MODE_GAME)
	{
		// 霧の開始・終了距離を遠めに設定
		Start = 100.0f;	// 霧の開始距離
		End = 700.0f;	// 霧の終了距離
	}

    // 霧の有効化
    pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

    // 霧の色を設定
    pDevice->SetRenderState(D3DRS_FOGCOLOR, Color);

    // 霧のモードを設定
    pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);

    if (Mode == D3DFOG_LINEAR)
    {
        pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&Start));
        pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&End));
    }
    else
    {
		pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&Density));
	}

    // 距離に基づくフォグの有効化
    pDevice->SetRenderState(D3DRS_RANGEFOGENABLE, UseRange ? TRUE : FALSE);

}
void onWireFrame()
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}
void offWireFrame()
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
bool GetFullScreen(void)
{
	return g_isFullscreen;
}
void DrawAPass(int Answer)
{
	RECT rect = { 0,60,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "一つ目の番号:%d", Answer);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
void DrawAPass2(int Answer2)
{
	RECT rect = { 0,80,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "二つ目の番号:%d", Answer2);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
void DrawAPass3(int Answer3)
{
	RECT rect = { 0,100,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "三つ目の番号:%d", Answer3);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
void DrawAPass4(int Answer4)
{
	RECT rect = { 0,120,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "四つ目の答え:%d", Answer4);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}