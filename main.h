//=======================================
//
// メイン処理[main.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MAIN_H_//このマクロ定義がされていなかったら
#define _MAIN_H_//2重インクルード防止のマクロ定義


#include<windows.h>
#include "d3dx9.h"															//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)										//ビルド時の警告対処用マクロ
#include "dinput.h"															//入力処理に必要
#include "Xinput.h"															//ジョイパッド処理に必要
#include "xaudio2.h"														//サウンド処理に必要


//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")												//描画処理に必要
#pragma comment(lib,"d3dx9.lib")											//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")											//DirectXコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")											//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")											//入力処理に必要
#pragma comment(lib,"xinput.lib")											//ジョイパッド処理に必要


//マクロ定義
#define CLASS_NAME "WindowClass"											//ウィンドウクラスの名前
#define WINDOW_NAME "ARCADE NIGHTMARE"											//ウィンドウの名前(キャプションに表示)
#define SCREEN_WIDTH (1280.0f)													//ウィンドウの幅
#define SCREEN_HEIGHT (720.0f)													//ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//座標・法線・カラー・テクスチャ
//#define FVF_VERTEX_3D_MULTI (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2)	// マルチテクスチャ


#define FIELD_LEFT (280.0f)//幅720.0f
#define FIELD_RIGHT (1000.0f)
#define FIELD_TOP (50.0f)//高さ400.0f
#define FIELD_UNDER (450.0f)

#define BALLFIELD_LEFT (230.0f)//幅820.0f
#define BALLFIELD_RIGHT (1050.0f)
#define BALLFIELD_TOP (50.0f)//高さ400.0f
#define BALLFIELD_UNDER (650.0f)


//画面の種類
typedef enum
{
	MODE_RECOMMEND = 0,		//推奨画面
	MODE_TITLE,				//タイトル画面
	MODE_TUTORIAL,			//チュートリアル画面
	MODE_TUTORIAL2,			//チュートリアル画面2
	MODE_GAME,				//ゲーム画面
	MODE_RESULT,			//リザルト画面
	MODE_FOUND,				//敵に見つかった時の画面
	MODE_EDIT,
	MODE_MAX
}MODE;


//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	float rhw;				//座標変換用係数
	D3DCOLOR col;			//座標カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
}VERTEX_2D;


//頂点情報[3D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	D3DXVECTOR3 nor;		//法線ベクトル
	D3DCOLOR col;			//座標カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
}VERTEX_3D;

////頂点情報[3D_MULTI]の構造体を定義
//typedef struct
//{
//	D3DXVECTOR3 pos;		//頂点座標
//	D3DXVECTOR3 nor;		//法線ベクトル
//	D3DCOLOR col;			//座標カラー
//	D3DXVECTOR2 tex;		//テクスチャ座標0
//	D3DXVECTOR2 texM;		//テクスチャ座標1
//}VERTEX_3D_MULTI;

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

LPDIRECT3DDEVICE9 GetDevice(void);

void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
void onWireFrame(void);
void offWireFrame(void);
void ToggleFullscreen(HWND hWnd);// ウィンドウをフルスクリーン
MODE GetMode(void);
bool GetFullScreen(void);
void SetupVertexFog(LPDIRECT3DDEVICE9 pDevice, DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density);
void DrawAPass(int Answer, int Answer2, int Answer3, int Answer4);

#endif
