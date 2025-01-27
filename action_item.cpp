//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "action_item.h"
#include "action_player.h"
#include "main.h"
#include "action_particle.h"

//マクロ
#define MAX_ITEM (512)	//アイテムの最大数
#define NUM_ITEM (3)	//アイテムの種類
#define BLOCK_HABA (40.0f)
#define BLOCK_TAKASA (20.0f)

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureItem = {};		  //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;//頂点バッファへのポインタ
ACTIONITEM g_item;								  //アイテムの情報

void InitActionItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\item2.png",      //テクスチャのファイル名
			&g_pTextureItem);

	g_item.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_item.fWidth = 0.0f;
	g_item.fHeight = 0.0f;
	g_item.bUse = false;//使用していない状態にする
	g_item.bDisp = false;
	g_item.bGet = false;
	

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem, NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_item.fWidth, g_item.fHeight,0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_item.fWidth, g_item.fHeight,0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_item.fWidth, g_item.fHeight,0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_item.fWidth, g_item.fHeight,0.0f);

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

	//頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}
void UninitActionItem(void)
{
	//テクスチャの破棄
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}
void UpdateActionItem(void)
{

}
void DrawActionItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	if (g_item.bDisp == true)
	{
		//頂点バッファをデータストリーム
		pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		if (g_item.bUse != false)
		{//アイテムが使用されている	

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}
//アイテムの設定処理
void SetActionItem(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	VERTEX_2D* pVtx=0;
	
	//ロック
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	if (g_item.bUse == false)
	{//アイテムが使用されていない
		g_item.pos = pos;
		g_item.fWidth = fWidth;
		g_item.fHeight = fHeight;
		g_item.nType = nType;
		g_item.bUse = true;
		g_item.bDisp = true;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_item.pos.x - g_item.fWidth, g_item.pos.y - g_item.fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_item.pos.x + g_item.fWidth, g_item.pos.y - g_item.fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_item.pos.x - g_item.fWidth, g_item.pos.y + g_item.fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_item.pos.x + g_item.fWidth, g_item.pos.y + g_item.fHeight, 0.0f);

		//テクスチャ
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	}

	//アンロック
	//頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}
//アイテムのあたりはんてぇ
bool CollisionActionItem(D3DXVECTOR3* pPos,		//現在の位置
						 D3DXVECTOR3* pPosOld,	//前回の位置
						 D3DXVECTOR3* pMove,	//移動量
						 float fWidth,			//幅
						 float fHeight)			//高さ
{
	bool bUse = false;//着地しているかどうか
	ActionPlayer* pPlayer = GetActionPlayer();

	if (g_item.bUse == true && g_item.bGet==false)
	{//使用しているアイテムを全てチェックする
		if ((g_item.pos.x - g_item.fWidth >= pPlayer->pos.x - HABA / 2 ||
			g_item.pos.x + g_item.fWidth >= pPlayer->pos.x + HABA / 2) &&
			g_item.pos.y - g_item.fHeight >= pPlayer->pos.y - TAKASA / 2)
		{
			g_item.bDisp = false;
			g_item.bGet = true;
		}
	}
	return bUse;
}
bool GetActionItem(void)
{
	return g_item.bGet;
}