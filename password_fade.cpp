//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================

#include "password_fade.h"

//グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordFade = NULL;	//頂点バッファへのポインタ
PASSWORDFADE g_fade;									//フェードの状態
D3DXCOLOR g_colorPasswordFade;							//ポリゴン(フェード)の色

void InitPasswordFade(MODE modeNext)
{
	g_fade = FADE_IN;//フェードイン状態に
	g_colorPasswordFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordFade,
		NULL);
	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPasswordFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = g_colorPasswordFade;
	pVtx[1].col = g_colorPasswordFade;
	pVtx[2].col = g_colorPasswordFade;
	pVtx[3].col = g_colorPasswordFade;

	//頂点バッファをアンロックする
	g_pVtxBuffPasswordFade->Unlock();
}
void UninitPasswordFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffPasswordFade != NULL)
	{
		g_pVtxBuffPasswordFade->Release();
		g_pVtxBuffPasswordFade = NULL;
	}
}
void UpdatePasswordFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン状態
			g_colorPasswordFade.a -= 0.04f;//ポリゴンを透明にしていく

			if (g_colorPasswordFade.a <= 0.0f)
			{
				g_colorPasswordFade.a = 0.0f;
				g_fade = FADE_NONE;//何もしていない状態に
			}
		}
		else if (g_fade == FADE_OUT)
		{//フェードアウト状態
			g_colorPasswordFade.a += 0.04f;//ポリゴンを不透明にしていく
			
			g_colorPasswordFade.r += 0.04f;
			g_colorPasswordFade.g += 0.04f;
			g_colorPasswordFade.b += 0.04f;

			if (g_colorPasswordFade.a >= 1.0f)
			{
				g_colorPasswordFade.a = 1.0f;
				g_fade = FADE_IN;//フェードイン状態に
			}
		}
		else if (g_fade == FADE_FAIL)
		{//フェードアウト状態
			g_colorPasswordFade.a += 0.04f;//ポリゴンを不透明にしていく

			g_colorPasswordFade.r += 0.04f;
			//g_colorPasswordFade.g += 0.04f;
			//g_colorPasswordFade.b += 0.04f;

			if (g_colorPasswordFade.a >= 0.5f)
			{
				g_colorPasswordFade.a = 1.0f;
				g_fade = FADE_IN;//フェードイン状態に
			}
		}
		else if (g_fade == FADE_SUCCESS)
		{
			g_colorPasswordFade.a += 0.04f;//ポリゴンを不透明にしていく

			//g_colorPasswordFade.r += 0.04f;
			g_colorPasswordFade.g += 0.04f;
			//g_colorPasswordFade.b += 0.04f;

			if (g_colorPasswordFade.a >= 0.5f)
			{
				g_colorPasswordFade.a = 1.0f;
				g_fade = FADE_IN;//フェードイン状態に
			}
		}

		VERTEX_2D* pVtx;//頂点情報へのポインタ
			
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPasswordFade->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = g_colorPasswordFade;
		pVtx[1].col = g_colorPasswordFade;
		pVtx[2].col = g_colorPasswordFade;
		pVtx[3].col = g_colorPasswordFade;

		//頂点バッファをアンロックする
		g_pVtxBuffPasswordFade->Unlock();
	}
}
void DrawPasswordFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数
}
void SetPasswordFade(PASSWORDFADE fade)
{
	g_fade = fade;											//フェードアウト状態に
	g_colorPasswordFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//黒いポリゴン(透明)にしておく
}
PASSWORDFADE GetPasswordFade(void)
{
	return g_fade;
}