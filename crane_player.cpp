//---------------------------------------------------------
// クレーンゲーム
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "crane_player.h"
#include "Input.h"
#include "crane_block.h"
#include "crane_item.h"
#include "sound.h"
#include "crane_background.h"
#include "crane_game.h"

// マクロ
#define MAX_MAX (400.0f)	// 最大でかい
#define MAX_MIN (10.0f)		// 最小ちいさい

// グローバル
LPDIRECT3DTEXTURE9 g_pTextureCranePlayer = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCranePlayer = NULL;	// 頂点バッファへのポインタ
CranePlayer g_player;									// レイヤーの情報
//int g_nCounterAnimPlayer;
//int g_nPatternAnimPlayer;

// プレイヤーの初期化処理
void InitCranePlayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ

	// テクスチャ2の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\crane_long2.png",					 // テクスチャのファイル名
		&g_pTextureCranePlayer);

	g_player.pos = D3DXVECTOR3(CLANEFIELD_LEFT + 75.0f, -70.0f, 0.0f);	// 位置を初期化する SCREEN_HEIGHT-HEIGHT
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);						// 移動量を初期化する
	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);							// 向きを初期化する、今回はZ軸（3番目）
	g_player.pBlock = NULL;
	g_player.nCntAnimState = 0;
	g_player.bUse = true;
	g_player.bMove = true;
	g_player.bLeft = false;
	g_player.bDown = false;
	g_player.bUpSound = false;
	g_player.bLanding = false;
	g_player.bGetItem = false;
	g_player.bMoveSound = false;

	// 対角線の長さを算出する
	g_player.Length = sqrtf(50.0f * 50.0f + 100.0f * 100.0f) / 2.0f;

	// 対角線の角度を算出する
	g_player.Angle = atan2f(WIDTH ,HEIGHT);

	// 頂点バッファ2の生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCranePlayer,
		NULL);

	VERTEX_2D *pVtx;// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCranePlayer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定

	pVtx[0].pos.x = -WIDTH;
	pVtx[0].pos.y = g_player.pos.y - HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = WIDTH;
	pVtx[1].pos.y = g_player.pos.y - HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -WIDTH;
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = WIDTH;
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffCranePlayer->Unlock();
}
// プレイヤーの終了処理
void UninitCranePlayer(void)
{
	// テクスチャの破棄
	if (g_pTextureCranePlayer != NULL)
	{
		g_pTextureCranePlayer->Release();
		g_pTextureCranePlayer = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffCranePlayer != NULL)
	{
		g_pVtxBuffCranePlayer->Release();
		g_pVtxBuffCranePlayer = NULL;
	}
}
// プレイヤーの更新処理
void UpdateCranePlayer(void)
{
	VERTEX_2D* pVtx;// 頂点情報へのポインタ
	CRANEITEM pItem = GetItem();
	CRANEGAMESTATE pCrane = GetCraneGameState();
	int nBulletCnt = 0;

	if (g_player.bUse == true && pCrane != CRANEGAMESTATE_END)
	{
		if (g_player.bMove == true &&
			(GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true))
		{// Dキーが押されている
			// 移動量を更新（増加）
			if (g_player.move.x <= MAX_SPEED_R)
			{ 
				g_player.move.x += 0.8f;
			}
			else if (g_player.move.x >= MAX_SPEED_R)
			{
				g_player.move.x = MAX_SPEED_R;
			}

			// 移動音の再生
			if (g_player.bMoveSound == false)
			{
				PlaySound(SOUND_LABEL_CRANEMOVE);
				g_player.bMoveSound = true;
			}
		}
		else if (KeyboardRelease(DIK_D) == true || JoyPadRelease(JOYKEY_RIGHT) == true)
		{// Dキーが押されていない
			StopSound(SOUND_LABEL_CRANEMOVE);
			g_player.bMoveSound = false;
		}

		if (g_player.bMove == true &&
			g_player.pos.x > CLANEFIELD_LEFT + 75.0f + WIDTH &&
			(GetMouseButtonTrigger(0) || JoyPadTrigger(JOYKEY_X) == true))
		{// クレーンを下す
			g_player.move.y = DOWN;
			g_player.bMove = false;
			g_player.bDown = true;
			g_player.bLeft = false;
			PlaySound(SOUND_LABEL_CRANEDOWN);
		}
	}

	if (g_player.bLanding == true &&
		g_player.bMove == false &&
		g_player.bUpSound == false)
	{// 上に昇る
		g_player.move.y = UP;
		g_player.bUpSound = true;
		StopSound(SOUND_LABEL_CRANEDOWN);
		PlaySound(SOUND_LABEL_CRANEUP);
	}

	if (g_player.bLeft == true &&
		g_player.bMove == false)
	{// 左に戻る
		StopSound(SOUND_LABEL_CRANEUP);
		if (g_player.bMoveSound == false)
		{// 移動音の再生
			PlaySound(SOUND_LABEL_CRANEMOVE);
			g_player.bMoveSound = true;
		}
		g_player.move.y = 0.0f;
		g_player.move.x = MAX_SPEED_L;
	}

	// 前回の位置を保存
	g_player.posOld = g_player.pos;

	// 位置を更新
	g_player.pos.x += g_player.move.x;// 横移動
	g_player.pos.y += g_player.move.y;// 落下

	// アイテムのあたりはんてぇ
	g_player.bGetItem = !CollisionCraneItem(&g_player.pos,
		&g_player.posOld,
		&g_player.move,
		ITEM_WIDTH,
		ITEM_HEIGHT);

	// 移動量を更新（減衰）
	g_player.move.x += (0.0f - g_player.move.x) * 0.2f;

	if (g_player.pos.y >= CLANEFIELD_UNDER)// 地面
	{
		g_player.pos.y = CLANEFIELD_UNDER;
		g_player.bLanding = true;
	}
	if (g_player.pos.y <= CLANEFIELD_TOP + HEIGHT - 300.0f)// 天井
	{
		g_player.pos.y = CLANEFIELD_TOP + HEIGHT - 300.0f;
		g_player.bLeft = true;
	}
	if (g_player.pos.x >= CLANEFIELD_RIGHT - WIDTH)// 右
	{
		StopSound(SOUND_LABEL_CRANEMOVE);
		g_player.pos.x = CLANEFIELD_RIGHT - WIDTH;
	}
	if (g_player.pos.x <= CLANEFIELD_LEFT + 75.0f + WIDTH)// 左
	{
		StopSound(SOUND_LABEL_CRANEMOVE);
		g_player.pos.x = CLANEFIELD_LEFT + 75.0f + WIDTH;
		g_player.bMove = true;
		g_player.bLeft = false;
		g_player.bFall = true;
		g_player.bUpSound = false;
		g_player.bLanding = false;
		g_player.bMoveSound = false;
		g_player.move.x = 0;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCranePlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		break;
	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			return;
		}
		else
		{
		}
		break;
	case PLAYERSTATE_MUTEKI:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
		}
		break;
	}

	// 位置座標の設定
	pVtx[0].pos.x = g_player.pos.x - WIDTH;
	pVtx[0].pos.y = g_player.pos.y - HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + WIDTH;
	pVtx[1].pos.y = g_player.pos.y - HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x - WIDTH;
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + WIDTH;
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	// 頂点バッファをアンロックする
	g_pVtxBuffCranePlayer->Unlock();
}
// プレイヤーの描画処理
void DrawCranePlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;// デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffCranePlayer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_player.bUse == true)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureCranePlayer);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
			0,                                     // 描画する最初の頂点インデックス
			2);                                    // 描画するプリミティブ数
	}
}
CranePlayer* GetCranePlayer(void)
{
	return &g_player;// プレイヤーの情報を返す
}
D3DXVECTOR3 GetCranePos(void)
{
	return g_player.move;
}