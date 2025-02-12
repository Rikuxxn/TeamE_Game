//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================

#include "input.h"
#include "main.h"
#include "password_block.h"
#include "password_item.h"
#include "password_particle.h"
#include "password_score.h"
#include "password_game.h"

//グローバル
LPDIRECT3DTEXTURE9 g_pTexturePassItem[NUM_ITEM] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassItem = NULL;		//頂点バッファへのポインタ
PASSWORDITEM g_item[MAX_ITEM];							//アイテムの情報
bool g_bJudgment;
bool g_bReset;

// ポーズ項目の拡大率を管理する配列
float passScales[MAX_ITEM] = { ITEM_MIN_SCALE, ITEM_MIN_SCALE, ITEM_MIN_SCALE, ITEM_MIN_SCALE };

//アイテムの初期化
void InitPasswordItem(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_0.png",	//テクスチャのファイル名
		&g_pTexturePassItem[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_1.png",	//テクスチャのファイル名
		&g_pTexturePassItem[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_2.png",	//テクスチャのファイル名
		&g_pTexturePassItem[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_3.png",	//テクスチャのファイル名
		&g_pTexturePassItem[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_4.png",	//テクスチャのファイル名
		&g_pTexturePassItem[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_5.png",	//テクスチャのファイル名
		&g_pTexturePassItem[5]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_6.png",	//テクスチャのファイル名
		&g_pTexturePassItem[6]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_7.png",	//テクスチャのファイル名
		&g_pTexturePassItem[7]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_8.png",	//テクスチャのファイル名
		&g_pTexturePassItem[8]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_9.png",	//テクスチャのファイル名
		&g_pTexturePassItem[9]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enter.png",	//テクスチャのファイル名
		&g_pTexturePassItem[10]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Delete.png",//テクスチャのファイル名
		&g_pTexturePassItem[11]);

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
	g_bJudgment = false;

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPassItem,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPassItem->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffPassItem->Unlock();
}
//アイテムの終了処理
void UninitPasswordItem(void)
{
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		//テクスチャの破棄
		if (g_pTexturePassItem[nCntItem] != NULL)
		{
			g_pTexturePassItem[nCntItem]->Release();
			g_pTexturePassItem[nCntItem] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPassItem != NULL)
	{
		g_pVtxBuffPassItem->Release();
		g_pVtxBuffPassItem = NULL;
	}
}
//アイテムの更新
void UpdatePasswordItem(void)
{
	VERTEX_2D* pVtx = 0;
	g_bJudgment = GetJudge();

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

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == true)
		{//使用しているアイテムを全てチェックする

			float itemLeft = g_item[nCntItem].pos.x - g_item[nCntItem].fWidth / 1.5;
			float itemRight = g_item[nCntItem].pos.x + g_item[nCntItem].fWidth / 1.5;
			float itemTop = g_item[nCntItem].pos.y - g_item[nCntItem].fHeight / 1.5;
			float itemBottom = g_item[nCntItem].pos.y + g_item[nCntItem].fHeight / 1.5;

			if (mouseX >= itemLeft && mouseX <= itemRight &&
				mouseY >= itemTop && mouseY <= itemBottom)
			{
				if (GetMouseButtonTrigger(0) == true)
				{
					switch (g_item[nCntItem].type)
					{// 押したボタンに応じて処理の変化
					case NUMTYPE_0:		// 0
						AddPassword(0);
						break;
					case NUMTYPE_1:		// 1
						AddPassword(1);
						break;
					case NUMTYPE_2:		// 2
						AddPassword(2);
						break;
					case NUMTYPE_3:		// 3
						AddPassword(3);
						break;
					case NUMTYPE_4:		// 4
						AddPassword(4);
						break;
					case NUMTYPE_5:		// 5
						AddPassword(5);
						break;
					case NUMTYPE_6:		// 6
						AddPassword(6);
						break;
					case NUMTYPE_7:		// 7
						AddPassword(7);
						break;
					case NUMTYPE_8:		// 8
						AddPassword(8);
						break;
					case NUMTYPE_9:		// 9
						AddPassword(9);
						break;
					case NUMTYPE_ENTER:	// エンター
						g_bJudgment = true;
						break;
					case NUMTYPE_DELETE:// 全消去処理
						SetPassword(0,0,false);
						SetPassword(0, GetAnum4(), true);
						g_bJudgment = false;
						g_bReset = false;
						break;
					}
				}
			}
		}
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);
	
		pVtx += 4;//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffPassItem->Unlock();
}
//アイテムの描画
void DrawPasswordItem(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffPassItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse != false)
		{//アイテムが使用されている	
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePassItem[g_item[nCntItem].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}
//アイテムの配置
void SetPasswordItem(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType, NUMTYPE type)
{
	VERTEX_2D* pVtx = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == false)
		{//アイテムが使用されていない
			g_item[nCntItem].pos = pos;
			g_item[nCntItem].fWidth = fWidth;
			g_item[nCntItem].fHeight = fHeight;
			g_item[nCntItem].nType = nType;
			g_item[nCntItem].type = type;
			g_item[nCntItem].bUse = true;
			g_item[nCntItem].bcatch = false;

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
	g_pVtxBuffPassItem->Unlock();
}
//パスワードの取得
PASSWORDITEM* GetItem(void)
{
	return g_item;
}
//一致判定
bool GetJudgment(void)
{
	return g_bJudgment;
}
bool GetReset(void)
{
	return g_bReset;
}