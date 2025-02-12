	#include "shooting_fade.h"


//グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShootingFade = NULL;	//頂点バッファへのポインタ
SHOOTINGFADE g_fade;									//フェードの状態
D3DXCOLOR g_colorShootingFade;							//ポリゴン(フェード)の色

void InitShootingFade(MODE modeNext)
{
	g_fade = FADE_IN;//フェードイン状態に
	g_colorShootingFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShootingFade,
		NULL);
	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShootingFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = g_colorShootingFade;
	pVtx[1].col = g_colorShootingFade;
	pVtx[2].col = g_colorShootingFade;
	pVtx[3].col = g_colorShootingFade;

	//頂点バッファをアンロックする
	g_pVtxBuffShootingFade->Unlock();
}
void UninitShootingFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffShootingFade != NULL)
	{
		g_pVtxBuffShootingFade->Release();
		g_pVtxBuffShootingFade = NULL;
	}
}
void UpdateShootingFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン状態
			g_colorShootingFade.a -= 0.03f;//ポリゴンを透明にしていく

			if (g_colorShootingFade.a <= 0.0f)
			{
				g_colorShootingFade.a = 0.0f;
				g_fade = FADE_NONE;//何もしていない状態に
			}
		}
		else if (g_fade == FADE_OUT)
		{//フェードアウト状態
			g_colorShootingFade.a += 0.03f;//ポリゴンを不透明にしていく

			if (g_colorShootingFade.a >= 1.0f)
			{
				g_colorShootingFade.a = 1.0f;
				g_fade = FADE_IN;//フェードイン状態に
			}
		}

		VERTEX_2D* pVtx;//頂点情報へのポインタ
			
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffShootingFade->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = g_colorShootingFade;
		pVtx[1].col = g_colorShootingFade;
		pVtx[2].col = g_colorShootingFade;
		pVtx[3].col = g_colorShootingFade;

		//頂点バッファをアンロックする
		g_pVtxBuffShootingFade->Unlock();
	}
}
void DrawShootingFade(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffShootingFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,									   //描画する最初の頂点インデックス
		2);                                    //描画するプリミティブ数
}
void SetShootingFade(MODE modeNext)
{
	g_fade = FADE_OUT;//フェードアウト状態に
	g_colorShootingFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//黒いポリゴン(透明)にしておく
}
SHOOTINGFADE GetShootingFade(void)
{
	return g_fade;
}