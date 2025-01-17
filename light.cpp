//=======================================
//
// ライト処理[light.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "light.h"

#define MAX_LIGHT (3)

//グローバル変数
D3DLIGHT9 g_light[MAX_LIGHT];//ライト情報
D3DXVECTOR3 g_vecDir[MAX_LIGHT];//ライトの方向ベクトル

//=============================
//ライトの初期化処理
//=============================
void InitLight(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	ZeroMemory(&g_light, sizeof(g_light));//複数の時

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_vecDir[nCntLight];

		//ライトの種類を設定
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//ライト拡散光を設定
		g_light[nCntLight].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}

	//ライトの方向を設定
	g_vecDir[0] = D3DXVECTOR3(-0.3f, -0.8f, 0.4f);
	g_vecDir[1] = D3DXVECTOR3(0.3f, -1.0f, 0.4f);
	g_vecDir[2] = D3DXVECTOR3(-0.4f, 0.8f, -0.9f);

	for (int nCntLight2 = 0; nCntLight2 < MAX_LIGHT; nCntLight2++)
	{

		//正規化する(大きさ1のベクトルにする)
		D3DXVec3Normalize(&g_vecDir[nCntLight2], &g_vecDir[nCntLight2]);

		g_light[nCntLight2].Direction = g_vecDir[nCntLight2];

		//ライトを設定する
		pDevice->SetLight(nCntLight2, &g_light[nCntLight2]);//0番目のライトを設定

		//ライトを有効にする
		pDevice->LightEnable(nCntLight2, true);//0番目のライトを有効

	}

}
//=============================
//ライトの終了処理
//=============================
void UninitLight(void)
{




}
//=============================
//ライトの更新処理
//=============================
void UpdateLight(void)
{




}
