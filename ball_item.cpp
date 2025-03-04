//---------------------------------------------------------
// ボールプール
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "ball_item.h"
#include "ball_particle.h"
#include "input.h"
#include "crane_item.h"
#include "sound.h"
#include "ball_background.h"

// グローバル
LPDIRECT3DTEXTURE9 g_pTextureBallItem[NUM_ITEM] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallItem = NULL;		// 頂点バッファへのポインタ
BALLITEM g_ballitem[MAX_ITEM];							// アイテムの情報
int g_nBallItem;

// アイテム項目の拡大率を管理する配列
float ItemScales[MAX_ITEM] = { ITEM_MIN_SCALE, ITEM_MIN_SCALE, ITEM_MIN_SCALE, ITEM_MIN_SCALE };
bool bHoldingItem = false;  // アイテムを持っているか

void InitBallItem(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ball_red.png",		// テクスチャのファイル名
		&g_pTextureBallItem[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ball_blue.png",		// テクスチャのファイル名
		&g_pTextureBallItem[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ball_yellow.png",	// テクスチャのファイル名
		&g_pTextureBallItem[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ball_green.png",	// テクスチャのファイル名
		&g_pTextureBallItem[3]);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_ballitem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ballitem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ballitem[nCntItem].fWidth = 0.0f;
		g_ballitem[nCntItem].fHeight = 0.0f;
		g_ballitem[nCntItem].nType = 0;
		g_ballitem[nCntItem].bUse = false;// 使用していない状態にする
		g_ballitem[nCntItem].bGet = false;
		g_ballitem[nCntItem].bcatch = false;
		g_ballitem[nCntItem].dragOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	g_nBallItem = 0;
	bHoldingItem = false;

	// 頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallItem,
		NULL);

	VERTEX_2D* pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBallItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].fHeight, 0.0f);

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
	g_pVtxBuffBallItem->Unlock();
}
void UninitBallItem(void)
{
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		// テクスチャの破棄
		if (g_pTextureBallItem[nCntItem] != NULL)
		{
			g_pTextureBallItem[nCntItem]->Release();
			g_pTextureBallItem[nCntItem] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffBallItem != NULL)
	{
		g_pVtxBuffBallItem->Release();
		g_pVtxBuffBallItem = NULL;
	}
}
void UpdateBallItem(void)
{
	VERTEX_2D* pVtx = 0;

	// マウスカーソルの位置を取得
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	// ウィンドウハンドルを取得
	HWND hwnd = GetActiveWindow();

	// スクリーン座標をクライアント座標に変換
	ScreenToClient(hwnd, &cursorPos);

	// クライアントサイズを取得
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	// ウィンドウスケールを計算
	float screenWidth = 1280.0f; // ゲームの解像度
	float screenHeight = 720.0f;
	float scaleX = screenWidth / (clientRect.right - clientRect.left);
	float scaleY = screenHeight / (clientRect.bottom - clientRect.top);

	// マウス座標をスケール
	float mouseX = cursorPos.x * scaleX;
	float mouseY = cursorPos.y * scaleY;

	// ゲームパッドでマウスカーソルを動かす
	UpdateCursorWithGamepad();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_ballitem[nCntItem].bUse)
		{
			float scaleFactor = 1.5f;  // 1.5倍の範囲にする
			float itemLeft = g_ballitem[nCntItem].pos.x - (g_ballitem[nCntItem].fWidth * scaleFactor) / 2.0f;
			float itemRight = g_ballitem[nCntItem].pos.x + (g_ballitem[nCntItem].fWidth * scaleFactor) / 2.0f;
			float itemTop = g_ballitem[nCntItem].pos.y - (g_ballitem[nCntItem].fHeight * scaleFactor) / 2.0f;
			float itemBottom = g_ballitem[nCntItem].pos.y + (g_ballitem[nCntItem].fHeight * scaleFactor) / 2.0f;

			if (mouseX >= itemLeft && mouseX <= itemRight &&
				mouseY >= itemTop && mouseY <= itemBottom)
			{
				if (!bHoldingItem && (GetMouseButtonPress(0) || GetJoypadPress(JOYKEY_B) == true))
				{
					if (g_ballitem[nCntItem].bGet == false)
					{
						PlaySound(SOUND_LABEL_BALLCATCH);
						g_ballitem[nCntItem].bGet = true;
					}
					g_ballitem[nCntItem].bcatch = true;
					bHoldingItem = true;  // アイテムを持っていることを記録

					// マウスのどこを掴んだかを記録
					g_ballitem[nCntItem].dragOffset.x = g_ballitem[nCntItem].pos.x - mouseX;
					g_ballitem[nCntItem].dragOffset.y = g_ballitem[nCntItem].pos.y - mouseY;

				}				
				if (GetMouseButtonRelease(0) || JoyPadRelease(JOYKEY_B) == true)
				{
					g_ballitem[nCntItem].bcatch = false;
					g_ballitem[nCntItem].bGet = false;
					bHoldingItem = false;  // 持っている状態を解除

					// 画面端の制限
					if (g_ballitem[nCntItem].pos.x < BALLFIELD_LEFT + g_ballitem[nCntItem].fWidth / 2)
					{
						g_ballitem[nCntItem].pos.x = BALLFIELD_LEFT + g_ballitem[nCntItem].fWidth / 2;
					}
					if (g_ballitem[nCntItem].pos.x > BALLFIELD_RIGHT - g_ballitem[nCntItem].fWidth / 2)
					{
						g_ballitem[nCntItem].pos.x = BALLFIELD_RIGHT - g_ballitem[nCntItem].fWidth / 2;
					}
					if (g_ballitem[nCntItem].pos.y < BALLFIELD_TOP + g_ballitem[nCntItem].fHeight / 2)
					{
						g_ballitem[nCntItem].pos.y = BALLFIELD_TOP + g_ballitem[nCntItem].fHeight / 2;
					}
					if (g_ballitem[nCntItem].pos.y > BALLFIELD_UNDER - g_ballitem[nCntItem].fHeight / 2)
					{
						g_ballitem[nCntItem].pos.y = BALLFIELD_UNDER - g_ballitem[nCntItem].fHeight / 2;
					}
				}
			}


			if (g_ballitem[nCntItem].bcatch)
			{
				// マウスの位置にオフセットを足して移動
				g_ballitem[nCntItem].pos.x = mouseX + g_ballitem[nCntItem].dragOffset.x;
				g_ballitem[nCntItem].pos.y = mouseY + g_ballitem[nCntItem].dragOffset.y;
			}

		
		}

		g_ballitem[nCntItem].pos += g_ballitem[nCntItem].move;

		if (g_ballitem[nCntItem].pos.y >= BALLFIELD_UNDER - g_ballitem[nCntItem].fHeight)
		{// 地面
			g_ballitem[nCntItem].pos.y = BALLFIELD_UNDER - g_ballitem[nCntItem].fHeight;
		}

		if (g_ballitem[nCntItem].pos.y <= BALLFIELD_TOP + g_ballitem[nCntItem].fHeight)
		{// 天井
			g_ballitem[nCntItem].pos.y = BALLFIELD_TOP + g_ballitem[nCntItem].fHeight;
		}

		if (g_ballitem[nCntItem].pos.x <= BALLFIELD_LEFT + g_ballitem[nCntItem].fWidth)
		{// 左端
			g_ballitem[nCntItem].pos.x = BALLFIELD_LEFT + g_ballitem[nCntItem].fWidth;
		}

		if (g_ballitem[nCntItem].pos.x >= BALLFIELD_RIGHT - g_ballitem[nCntItem].fWidth)
		{// 右端
			g_ballitem[nCntItem].pos.x = BALLFIELD_RIGHT - g_ballitem[nCntItem].fWidth;
		}

		if (g_ballitem[nCntItem].pos.y >= ITEM_CLEARPOSY - ITEM_CLEARZONEY
			&& g_ballitem[nCntItem].pos.x - g_ballitem[nCntItem].fWidth >= ITEM_CLEARPOSX - ITEM_CLEARZONEX
			&& g_ballitem[nCntItem].pos.x + g_ballitem[nCntItem].fWidth <= ITEM_CLEARPOSX + ITEM_CLEARZONEX
			&& g_ballitem[nCntItem].bUse == true)
		{// ボールを片づけた
			PlaySound(SOUND_LABEL_BALLGET);
			g_ballitem[nCntItem].bcatch = false;
			g_ballitem[nCntItem].bUse = false;
			bHoldingItem = false;
			g_nBallItem--;
		}

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x - g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y - g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x + g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y - g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x - g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y + g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x + g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y + g_ballitem[nCntItem].fHeight, 0.0f);

		pVtx += 4;// 頂点データのポインタを４つ分進める

	}

	if (!GetMouseButtonPress(0) && !GetJoypadPress(JOYKEY_B))
	{
		for (int i = 0; i < MAX_ITEM; i++)
		{
			g_ballitem[i].bcatch = false;
		}
		bHoldingItem = false;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffBallItem->Unlock();

}
void DrawBallItem(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();// デバイスへのポインタ

	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBallItem, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_ballitem[nCntItem].bUse != false)
		{// アイテムが使用されている	

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBallItem[g_ballitem[nCntItem].nType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}
// アイテムの設定処理
void SetBallItem(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	VERTEX_2D* pVtx=0;
	
	// ロック
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_ballitem[nCntItem].bUse == false)
		{// アイテムが使用されていない
			g_ballitem[nCntItem].pos = pos;
			g_ballitem[nCntItem].fWidth = fWidth;
			g_ballitem[nCntItem].fHeight = fHeight;
			g_ballitem[nCntItem].nType = nType;
			g_ballitem[nCntItem].bUse = true;
			g_ballitem[nCntItem].bcatch = false;
			g_nBallItem++;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x - g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y - g_ballitem[nCntItem].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x + g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y - g_ballitem[nCntItem].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x - g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y + g_ballitem[nCntItem].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x + g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y + g_ballitem[nCntItem].fHeight, 0.0f);

			// テクスチャ
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
	g_pVtxBuffBallItem->Unlock();
}
// アイテムの個数
int GetNumBallItem(void)
{
	return g_nBallItem;
}