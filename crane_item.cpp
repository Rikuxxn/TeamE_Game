//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "crane_item.h"
#include "crane_player.h"
#include "crane_particle.h"
#include "crane_block.h"

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureItem[NUM_ITEM] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;		//頂点バッファへのポインタ
CRANEITEM g_item[MAX_ITEM];							//アイテムの情報
int g_nItem;

void InitCraneItem(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\item.png",		//テクスチャのファイル名
		&g_pTextureItem[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\item2.png",		//テクスチャのファイル名
		&g_pTextureItem[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\item3.png",		//テクスチャのファイル名
		&g_pTextureItem[2]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\item4.png",		//テクスチャのファイル名
		&g_pTextureItem[3]);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_item[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_item[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_item[nCntItem].fWidth = 0.0f;
		g_item[nCntItem].fHeight = 0.0f;
		g_item[nCntItem].bUse = false;//使用していない状態にする
		g_item[nCntItem].bGet = false;
		g_item[nCntItem].bcatch = false;
	}
	g_nItem = 0;

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_item[nCntItem].fWidth, g_item[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_item[nCntItem].fWidth, g_item[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_item[nCntItem].fWidth, g_item[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_item[nCntItem].fWidth, g_item[nCntItem].fHeight, 0.0f);

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
	g_pVtxBuffItem->Unlock();
}
void UninitCraneItem(void)
{
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		//テクスチャの破棄
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem]->Release();
			g_pTextureItem[nCntItem] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}
void UpdateCraneItem(void)
{
	VERTEX_2D* pVtx = 0;
	CranePlayer* pPlayer = GetCranePlayer();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (pPlayer->bMove == false &&
			g_item[nCntItem].bcatch == true &&
			g_item[nCntItem].pos.x >= pPlayer->pos.x - ITEM_WIDTH
			&& g_item[nCntItem].pos.x <= pPlayer->pos.x + ITEM_WIDTH)
		{
			g_item[nCntItem].pos = pPlayer->pos;
		}
		if (pPlayer->bLeft == false &&
			pPlayer->bFall == true &&
			g_item[nCntItem].bcatch == false)
		{
			g_item[nCntItem].move.y = 4.5f;
		}

		g_item[nCntItem].pos += g_item[nCntItem].move;

		if (g_item[nCntItem].pos.y >= FIELD_UNDER - g_item[nCntItem].fHeight)//地面
		{
			g_item[nCntItem].pos.y = FIELD_UNDER - g_item[nCntItem].fHeight;
			//g_item[nCntItem].bcatch = false;
		}
		if (g_item[nCntItem].pos.y >= ITEM_CLEARPOSY &&
			g_item[nCntItem].pos.x - g_item[nCntItem].fWidth >= ITEM_CLEARPOSX - ITEM_CLEARZONE &&
			g_item[nCntItem].pos.x + g_item[nCntItem].fWidth <= ITEM_CLEARPOSX + ITEM_CLEARZONE &&
			g_item[nCntItem].bcatch == true &&
			g_item[nCntItem].bUse == true &&
			pPlayer->bFall == true)
		{//アイテムゲット
			g_item[nCntItem].bUse = false;
			pPlayer->bFall = false;
			g_nItem--;
		}
	}

	//ロック
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);
	
		pVtx += 4;//頂点データのポインタを４つ分進める
	}
	//アンロック
	//頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}
//
void DrawCraneItem(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse != false)
		{//アイテムが使用されている	

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem[g_item[nCntItem].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}
//アイテムの設定処理
void SetCraneItem(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	VERTEX_2D* pVtx=0;
	
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == false)
		{//アイテムが使用されていない
			g_item[nCntItem].pos = pos;
			g_item[nCntItem].fWidth = fWidth;
			g_item[nCntItem].fHeight = fHeight;
			g_item[nCntItem].nType = nType;
			g_item[nCntItem].bUse = true;
			g_item[nCntItem].bcatch = false;
			g_nItem++;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);

			//テクスチャ
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;//頂点データのポインタを４つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}
//アイテムの個数
int GetNumItem(void)
{
	return g_nItem;
}
CRANEITEM GetItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		return g_item[nCntItem];
	}
}
//アイテムのあたりはんてぇ
bool CollisionCraneItem(D3DXVECTOR3* pPos,		//現在の位置
						 D3DXVECTOR3* pPosOld,	//前回の位置
						 D3DXVECTOR3* pMove,	//移動量
						 float fWidth,			//幅
						 float fHeight)			//高さ
{
	bool bUse = false;//着地しているかどうか
	CranePlayer* pPlayer = GetCranePlayer();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{

		if (g_item[nCntItem].bUse == true && g_item[nCntItem].bGet == false)
		{//使用しているアイテムを全てチェックする
			if (g_item[nCntItem].pos.x >= pPlayer->pos.x - ITEM_WIDTH
				&& g_item[nCntItem].pos.x <= pPlayer->pos.x + ITEM_WIDTH
				&& g_item[nCntItem].pos.y >= pPlayer->pos.y - ITEM_HEIGHT
				&& g_item[nCntItem].pos.y <= pPlayer->pos.y + ITEM_HEIGHT
				&& pPlayer->pos.x >= FIELD_LEFT + 75.0f + HABA)
			{
				g_item[nCntItem].bcatch = true;
			}
		}
	}
	return bUse;
}