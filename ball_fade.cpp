//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "ball_fade.h"

//グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallFade = NULL;//頂点バッファへのポインタ
BALLFADE g_fade;//フェードの状態
D3DXCOLOR g_colorBallFade;//ポリゴン(フェード)の色

void InitBallFade(MODE modeNext)
{
	g_fade = FADE_IN;//フェードイン状態に
	g_colorBallFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallFade,
		NULL);
	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = g_colorBallFade;
	pVtx[1].col = g_colorBallFade;
	pVtx[2].col = g_colorBallFade;
	pVtx[3].col = g_colorBallFade;

	//頂点バッファをアンロックする
	g_pVtxBuffBallFade->Unlock();
}
void UninitBallFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffBallFade != NULL)
	{
		g_pVtxBuffBallFade->Release();
		g_pVtxBuffBallFade = NULL;
	}
}
void UpdateBallFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン状態
			g_colorBallFade.a -= 0.04f;//ポリゴンを透明にしていく

			if (g_colorBallFade.a <= 0.0f)
			{
				g_colorBallFade.a = 0.0f;
				g_fade = FADE_NONE;//何もしていない状態に
			}
		}
		else if (g_fade == FADE_OUT)
		{//フェードアウト状態
			g_colorBallFade.a += 0.04f;//ポリゴンを不透明にしていく
			//g_colorBallFade.r += 0.01f;
			//g_colorBallFade.b += 0.02f;
			
			g_colorBallFade.r += 0.04f;
			g_colorBallFade.g += 0.04f;
			g_colorBallFade.b += 0.04f;

			if (g_colorBallFade.a >= 1.0f)
			{
				g_colorBallFade.a = 1.0f;
				g_fade = FADE_IN;//フェードイン状態に
			}
		}
		else if (g_fade == FADE_DAMAGE)
		{//フェードアウト状態
			g_colorBallFade.a += 0.04f;//ポリゴンを不透明にしていく

			g_colorBallFade.r += 0.04f;
			g_colorBallFade.g += 0.04f;
			g_colorBallFade.b += 0.04f;

			if (g_colorBallFade.a >= 1.0f)
			{
				g_colorBallFade.a = 1.0f;
				g_fade = FADE_IN;//フェードイン状態に
			}
		}

		VERTEX_2D* pVtx;//頂点情報へのポインタ
			
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffBallFade->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = g_colorBallFade;
		pVtx[1].col = g_colorBallFade;
		pVtx[2].col = g_colorBallFade;
		pVtx[3].col = g_colorBallFade;

		//頂点バッファをアンロックする
		g_pVtxBuffBallFade->Unlock();

	}
}
void DrawBallFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数
}
void SetBallFade(BALLFADE fade)
{
	g_fade = FADE_OUT;//フェードアウト状態に
	g_colorBallFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//黒いポリゴン(透明)にしておく
}
BALLFADE GetBallFade(void)
{
	return g_fade;
}