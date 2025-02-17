//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "ball_block.h"
#include "main.h"
#include "ball_particle.h"

// マクロ
#define MAX_BLOCK (512)	// ブロックの最大数
#define NUM_BLOCK (3)	// ブロックの種類
#define BLOCK_HABA (40.0f)
#define BLOCK_TAKASA (40.0f)

// グローバル
LPDIRECT3DTEXTURE9 g_pTextureBallBlock = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallBlock = NULL;	// 頂点バッファへのポインタ
BALLBLOCK g_aBlock[MAX_BLOCK];						// ブロックの情報

void InitBallBlock(void)
{
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();	// デバイスの取得
	int nCntBlock;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\box.png",		// テクスチャのファイル名
		&g_pTextureBallBlock);

	// ブロックの情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].bUse = false;// 使用していない状態にする
		g_aBlock[nCntBlock].nMoveCnt = 0;
	}

	// 頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallBlock,
		NULL);

	VERTEX_2D* pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBallBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// 0.0～1.0で設定
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;// 頂点データのポインタを４つ分進める

	}
	// 頂点バッファをアンロック
	g_pVtxBuffBallBlock->Unlock();
}
void UninitBallBlock(void)
{
	// テクスチャの破棄
	if (g_pTextureBallBlock != NULL)
	{
		g_pTextureBallBlock->Release();
		g_pTextureBallBlock = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffBallBlock != NULL)
	{
		g_pVtxBuffBallBlock->Release();
		g_pVtxBuffBallBlock = NULL;
	}
}
void UpdateBallBlock(void)
{
	VERTEX_2D* pVtx = 0;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			g_aBlock[nCntBlock].nMoveCnt++;
			if (g_aBlock[nCntBlock].nType == 0)
			{
				if (g_aBlock[nCntBlock].nMoveCnt >= 60)
				{
					g_aBlock[nCntBlock].move *= -1.0f;
					g_aBlock[nCntBlock].nMoveCnt = 0;
				}
			}
			// 位置を更新
			g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;

			// 頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 5.0f, g_aBlock[nCntBlock].pos.y - 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 5.0f, g_aBlock[nCntBlock].pos.y - 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 5.0f, g_aBlock[nCntBlock].pos.y + 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 5.0f, g_aBlock[nCntBlock].pos.y + 5.0f, 0.0f);

			if (g_aBlock[nCntBlock].nType == 0)
			{
				// 頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);// 0.0～1.0で設定
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			}
		}
		pVtx += 4;// 頂点データのポインタを４つ分進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffBallBlock->Unlock();
}
void DrawBallBlock(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();// デバイスへのポインタ

	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallBlock, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{// ブロックが使用されている	
			int nType = g_aBlock[nCntBlock].nType;

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBallBlock);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}
//ブロックの設定処理
void SetBallBlock(D3DXVECTOR3 pos,D3DXVECTOR3 move,float fWidth,float fHeight,int nType)
{
	VERTEX_2D* pVtx=0;
	
	// ロック
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{// ブロックが使用されていない
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].move = move;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bUse = true;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			// 頂点カラーの設定
			//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//0.0～1.0で設定
			//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//0.0～1.0で設定
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ
			//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//pVtx[1].tex = D3DXVECTOR2(fWidth / BLOCK_HABA, 0.0f);
			//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(fWidth / BLOCK_HABA, 1.0f);
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;// 頂点データのポインタを４つ分進める
	}
	// アンロック
	// 頂点バッファをアンロック
	g_pVtxBuffBallBlock->Unlock();
}
BALLBLOCK* GetBlock(void)
{
	return g_aBlock;
}