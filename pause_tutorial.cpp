//---------------------------------------------------------
// ポーズ中の操作確認
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "pause_tutorial.h"
#include "pause.h"
#include "input.h"
#include "sound.h"

// グローバル
LPDIRECT3DTEXTURE9 g_pTexturePTutorial = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPTutorial = NULL;	// 頂点バッファへのポインタ

// 初期化
void InitPTutorial(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause_tutorial.png",		// テクスチャのファイル名
		&g_pTexturePTutorial);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPTutorial,
		NULL);

	VERTEX_2D* pVtx;// 頂点情報へのポインタ

		// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 幅1280.0f
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);	// 高さ720.0f
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffPTutorial->Unlock();
}
// 終了処理
void UninitPTutorial(void)
{
	// テクスチャの破棄
	if (g_pTexturePTutorial != NULL)
	{
		g_pTexturePTutorial->Release();
		g_pTexturePTutorial = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffPTutorial != NULL)
	{
		g_pVtxBuffPTutorial->Release();
		g_pVtxBuffPTutorial = NULL;
	}
}
// 更新処理
void UpdatePTutorial(void)
{
	bool bTutoDraw = GetTutoDraw();
	if (bTutoDraw == true)
	{// 描画中
		if (GetMouseButtonTrigger(0) || JoyPadTrigger(JOYKEY_A) == true)
		{// 左クリック
			SetDraw(false);
			PlaySound(SOUND_LABEL_OK);
		}
	}
}
// 描画処理
void DrawPTutorial(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// デバイスへのポインタ

	// 背景
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPTutorial, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePTutorial);
	// 背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
		0,									   // 描画する最初の頂点インデックス
		2);                                    // 描画するプリミティブ数
}