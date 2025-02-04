//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================

#include "main.h"
#include "password_block.h"
#include "password_particle.h"

//マクロ
#define MAX_BLOCK (256)		//ブロックの最大数
#define NUM_BLOCK (3)		//種類
#define BLOCK_HABA (40.0f)	//幅
#define BLOCK_TAKASA (40.0f)//高さ

//グローバル
LPDIRECT3DTEXTURE9 g_pTexturePassBlock[NUM_BLOCK] = {};     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassBlock = NULL;			//頂点バッファへのポインタ
PASSWORDBLOCK g_aPassBlock[MAX_BLOCK];						//ブロックの情報

void InitPassBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPassBlock;

	//デバイスの取得
	pDevice = GetDevice();

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//"data\\TEXTURE\\block2.png",		//テクスチャのファイル名
	//	&g_pTexturePassBlock[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sand.jpg",		//テクスチャのファイル名
		&g_pTexturePassBlock[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block1.png",	//テクスチャのファイル名
		&g_pTexturePassBlock[2]);

	//ブロックの情報の初期化
	for (nCntPassBlock = 0; nCntPassBlock < MAX_BLOCK; nCntPassBlock++)
	{
		g_aPassBlock[nCntPassBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPassBlock[nCntPassBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPassBlock[nCntPassBlock].fWidth = 0.0f;
		g_aPassBlock[nCntPassBlock].fHeight = 0.0f;
		g_aPassBlock[nCntPassBlock].bUse = false;//使用していない状態にする
		g_aPassBlock[nCntPassBlock].nMoveCnt = 0;
	}

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
														D3DUSAGE_WRITEONLY,
														FVF_VERTEX_2D,
														D3DPOOL_MANAGED,
														&g_pVtxBuffPassBlock,
														NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPassBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPassBlock = 0; nCntPassBlock < MAX_BLOCK; nCntPassBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].fHeight,0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].fHeight,0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].fHeight,0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].fHeight,0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//0.0～1.0で設定
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffPassBlock->Unlock();
}
void UninitPassBlock(void)
{
	for (int nCntPassBlock = 0; nCntPassBlock < NUM_BLOCK; nCntPassBlock++)
	{
		//テクスチャの破棄
		if (g_pTexturePassBlock[nCntPassBlock] != NULL)
		{
			g_pTexturePassBlock[nCntPassBlock]->Release();
			g_pTexturePassBlock[nCntPassBlock] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPassBlock != NULL)
	{
		g_pVtxBuffPassBlock->Release();
		g_pVtxBuffPassBlock = NULL;
	}
}
void UpdatePassBlock(void)
{
	VERTEX_2D* pVtx = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPassBlock = 0; nCntPassBlock < MAX_BLOCK; nCntPassBlock++)
	{
		if (g_aPassBlock[nCntPassBlock].bUse == true)
		{
			g_aPassBlock[nCntPassBlock].nMoveCnt++;
			if (g_aPassBlock[nCntPassBlock].nType == 0)
			{
				if (g_aPassBlock[nCntPassBlock].nMoveCnt >= 60)
				{
					g_aPassBlock[nCntPassBlock].move *= -1.0f;
					g_aPassBlock[nCntPassBlock].nMoveCnt = 0;
				}
			}
			//位置を更新
			g_aPassBlock[nCntPassBlock].pos.x += g_aPassBlock[nCntPassBlock].move.x;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x - 5.0f, g_aPassBlock[nCntPassBlock].pos.y - 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x + 5.0f, g_aPassBlock[nCntPassBlock].pos.y - 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x - 5.0f, g_aPassBlock[nCntPassBlock].pos.y + 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x + 5.0f, g_aPassBlock[nCntPassBlock].pos.y + 5.0f, 0.0f);

			if (g_aPassBlock[nCntPassBlock].nType == 0)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);//0.0～1.0で設定
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			}
		}
		pVtx += 4;//頂点データのポインタを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassBlock->Unlock();
}
void DrawPassBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntPassBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPassBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPassBlock = 0; nCntPassBlock < MAX_BLOCK; nCntPassBlock++)
	{
		if (g_aPassBlock[nCntPassBlock].bUse == true)
		{//ブロックが使用されている	
			int nType = g_aPassBlock[nCntPassBlock].nType;

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePassBlock[nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPassBlock * 4, 2);
		}
	}
}
//ブロックの設定処理
void SetPassBlock(D3DXVECTOR3 pos,D3DXVECTOR3 move,float fWidth,float fHeight,int nType)
{
	int nCntPassBlock;
	VERTEX_2D* pVtx=0;
	
	//ロック
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPassBlock = 0; nCntPassBlock < MAX_BLOCK; nCntPassBlock++)
	{
		if (g_aPassBlock[nCntPassBlock].bUse == false)
		{//ブロックが使用されていない
			g_aPassBlock[nCntPassBlock].pos = pos;
			g_aPassBlock[nCntPassBlock].move = move;
			g_aPassBlock[nCntPassBlock].fWidth = fWidth;
			g_aPassBlock[nCntPassBlock].fHeight = fHeight;
			g_aPassBlock[nCntPassBlock].nType = nType;
			g_aPassBlock[nCntPassBlock].bUse = true;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x - g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].pos.y - g_aPassBlock[nCntPassBlock].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x + g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].pos.y - g_aPassBlock[nCntPassBlock].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x - g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].pos.y + g_aPassBlock[nCntPassBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x + g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].pos.y + g_aPassBlock[nCntPassBlock].fHeight, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//0.0～1.0で設定
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			//テクスチャ
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(fWidth / BLOCK_HABA, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fWidth / BLOCK_HABA, 1.0f);

			break;
		}
		pVtx += 4;//頂点データのポインタを４つ分進める
	}
	//アンロック
	//頂点バッファをアンロック
	g_pVtxBuffPassBlock->Unlock();
}
PASSWORDBLOCK* GetPassBlock(void)
{
	return g_aPassBlock;
}