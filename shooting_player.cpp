//---------------------------------------------------------
//
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "shooting_player.h"
#include "Input.h"
#include "shooting_bullet.h"
#include "shooting_enemy.h"
#include "shooting_effect.h"
#include "shooting_fade.h"
#include "sound.h"
#include "shooting_particle.h"
#include "game.h"
#include "shooting_background.h"

// マクロ
#define MAX_MAX (400.0f)	//最大でかい
#define MAX_MIN (10.0f)		//最小ちいさい

//グローバル
LPDIRECT3DTEXTURE9 g_pTexturePlayer1 = NULL;	 // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer1 = NULL;// 頂点バッファへのポインタ
ShootingPlayer g_player;						 // プレイヤーの情報

// プレイヤーの初期化処理
void InitShootingPlayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// デバイスへのポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Player.png",//テクスチャのファイル名
		&g_pTexturePlayer1);

	g_player.pos = D3DXVECTOR3(640.0f,540.0f,0.0f);// 位置を初期化する
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);   // 移動量を初期化する
	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);	   // 向きを初期化する、今回はZ軸（3番目）
	g_player.Bullet.x = 10.0f;
	g_player.Bullet.y = 10.0f;
	g_player.bUse = true;
	g_player.bDisp = true;
	g_player.bHit = false;
	g_player.nCntAnimState = 0;
	g_player.nLife = 8;
	g_player.nBulletType = 0;
	g_player.nBulletCnt = BULLET_COOL;
	g_player.nBulletCool = 0;
	g_player.nBulletMax = 0;

	// 対角線の長さを算出する
	g_player.Length = sqrtf(40.0f * 40.0f + 40.0f * 40.0f) / 2.0f;

	// 対角線の角度を算出する
	g_player.Angle = atan2f(WIDTH,HEIGHT);

	// 頂点バッファ2の生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer1,
		NULL);

	VERTEX_2D *pVtx;// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
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
	g_pVtxBuffPlayer1->Unlock();
}
// プレイヤーの終了処理
void UninitShootingPlayer(void)
{
	// テクスチャの破棄
	if (g_pTexturePlayer1 != NULL)
	{
		g_pTexturePlayer1->Release();
		g_pTexturePlayer1 = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffPlayer1 != NULL)
	{
		g_pVtxBuffPlayer1->Release();
		g_pVtxBuffPlayer1 = NULL;
	}
}
// プレイヤーの更新処理
void UpdateShootingPlayer(void)
{
	VERTEX_2D* pVtx;// 頂点情報へのポインタ
	GAME* pGame = GetGame();

	if (g_player.bUse == true && pGame->bSTClear == false)
	{
		//if (GetJoypadPress(JOYKEY_UP) == true)
		//{//上キー
		//	g_player.move.x += 0.0f;
		//	g_player.move.y -= 1.0f;
		//}
		//else if (GetJoypadPress(JOYKEY_DOWN) == true)
		//{//下キー
		//	g_player.move.x += 0.0f;
		//	g_player.move.y += 1.0f;
		//}
		//else if (GetJoypadPress(JOYKEY_LEFT) == true)
		//{
		//	//移動量を更新（増加）
		//	g_player.move.x -= 1.0f;
		//	g_player.move.y += 0.0f;
		//}
		//else if (GetJoypadPress(JOYKEY_RIGHT) == true)
		//{
		//	g_player.move.x += 1.0f;
		//	g_player.move.y += 0.0f;
		//}

		if (GetKeyboardPress(DIK_A) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				// 移動量を更新（増加）
				g_player.move.x += sinf(-D3DX_PI * 0.75f) * 0.75f;
				g_player.move.y += cosf(-D3DX_PI * 0.75f) * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{
				// 移動量を更新（増加）
				g_player.move.x += sinf(-D3DX_PI * 0.25f) * 0.75f;
				g_player.move.y += cosf(-D3DX_PI * 0.25f) * 0.75f;
			}
			else
			{
				// 移動量を更新（増加）
				g_player.move.x -= 1.0f;
				g_player.move.y += 0.0f;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.75f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_player.move.x += sinf(D3DX_PI * 0.25f) * 0.75f;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.75f;
			}
			else
			{
				g_player.move.x += 1.0f;
				g_player.move.y += 0.0f;
			}

		}
		else if (GetKeyboardPress(DIK_W) == true)
		{
			// 上に移動
			g_player.move.x += 0.0f;
			g_player.move.y -= 1.0f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			// 下に移動
			g_player.move.x += 0.0f;
			g_player.move.y += 1.0f;
		}
		//else if (KeyboardTrigger(DIK_R) == true || JoypadTrigger(JOYKEY_RB) == true)
		//{
		//	PlaySound(SOUND_LABEL_RELOAD);
		//	if (g_player.nBulletType == 0)
		//	{
		//		g_player.nBulletType = 1;
		//	}
		//	else if(g_player.nBulletType == 1)
		//	{
		//		g_player.nBulletType = 0;
		//	}
		//}
		if (g_player.bHit == true)
		{
			g_player.nCntAnimState++;// カウンターを加算
		}

		switch (g_player.nBulletType)
		{
		case 0:
			if (/*GetKeyboardPress(DIK_SPACE) == true ||*/ GetMouseButtonPress(0)/*|| GetJoypadPress(JOYKEY_A) == true*/)
			{// SPACE
				g_player.nBulletCnt++;
				if (g_player.nBulletCnt >= BULLET_INTERVAL/* && g_player.nBulletMax < BULLETMAX*/)
				{
					// 弾の設定
					PlaySound(SOUND_LABEL_STSHOT);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * 10.0f, cosf(g_player.rot.z + D3DX_PI) * 10.0f, 0.0f), BULLETTYPE_PLAYER, 20, 1);
					g_player.nBulletCnt = 0;
					g_player.nBulletMax++;
				}
			}
			else if (KeyboardRelease(DIK_SPACE) == true /*|| JoypadRelease(JOYKEY_A) == true*/)
			{
				g_player.nBulletCnt = BULLET_INTERVAL;
				g_player.nBulletMax = 0;
			}
			break;
		//case 1:
		//	if (g_player.nBulletCool <= 0 && (KeyboardTrigger(DIK_SPACE) == true || JoypadTrigger(JOYKEY_A) == true))
		//	{
		//		PlaySound(SOUND_LABEL_SHOT02);
		//		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * 15.0f, cosf(g_player.rot.z + D3DX_PI) * 15.0f, 0.0f), BULLETTYPE_PLAYER,20,2);
		//		g_player.nBulletCool = 15;
		//	}
		//	break;
		//case 2:
		//	if (KeyboardRepeat(DIK_SPACE) == true || GetJoypadPress(JOYKEY_A) == true)
		//	{
		//		SetParticle(D3DXVECTOR3(g_player.pos.x + 50.0f, g_player.pos.y, g_player.pos.z), 2);
		//	}
		//	break;
		}
		// アフターバーナー
		SetParticle(D3DXVECTOR3(g_player.pos.x + 7.0f, g_player.pos.y + 20.0f, g_player.pos.z), 1);
		SetParticle(D3DXVECTOR3(g_player.pos.x - 7.0f, g_player.pos.y + 20.0f, g_player.pos.z), 1);
	}

	if (g_player.nBulletMax < BULLET_MAX)
	{
		g_player.nBulletCool = BULLET_COOL;
	}
	if (g_player.nBulletCool >= 0)
	{
		g_player.nBulletCool--;
	}
	else if (g_player.nBulletCool <= 0)
	{
		g_player.nBulletCool = 0;
		g_player.nBulletMax = 0;
	}

	// 位置を更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	// 移動量を更新（減衰）
	g_player.move.x += (0.0f - g_player.move.x) * 0.1f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.1f;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

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
			if (g_player.nCounterState <= 0)
			{
				g_player.state = PLAYERSTATE_NORMAL;
			}
		}
		break;
	}

	// 位置座標の設定
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.z = 0.0f;

	if (g_player.pos.x >= 640.0f + BACKGROUND_WIDTH - WIDTH)
	{
		g_player.pos.x = 640.0f + BACKGROUND_WIDTH - WIDTH;
	}
	else if (g_player.pos.x <= 640.0f - BACKGROUND_WIDTH + WIDTH)
	{
		g_player.pos.x = 640.0f - BACKGROUND_WIDTH + WIDTH;
	}

	if (g_player.pos.y >= BACKGROUND_HEIGHT - HEIGHT)
	{
		g_player.pos.y = BACKGROUND_HEIGHT - HEIGHT;
	}
	else if (g_player.pos.y <= 0 + HEIGHT)
	{
		g_player.pos.y = 0 + HEIGHT;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPlayer1->Unlock();
}
// プレイヤーの描画処理
void DrawShootingPlayer(void)
{
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();// デバイスへのポインタ

	// デバイスの取得

	if (g_player.bDisp == true)
	{
		// 頂点バッファをデータストリーム
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer1, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		if (g_player.bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePlayer1);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
				0,                                     // 描画する最初の頂点インデックス
				2);                                    // 描画するプリミティブ数
		}
	}
}
ShootingPlayer* GetShootingPlayer(void)
{
	return &g_player;// プレイヤーの情報を返す
}
void HitShootingPlayer(int nDamage)// あたりはんてぇ
{
	VERTEX_2D* pVtx;
	g_player.nLife -= nDamage;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.nLife <= 0)// 死んだ
	{
		//PlaySound(SOUND_LABEL_EXPLOSION);

		//bakuhatu
		SetParticle(g_player.pos, 0);

		g_player.bUse = false;

		g_player.bDisp = false;

		g_player.nCntAnimState = PLAYERSTATE_DEATH;

		g_player.nCounterState = 60;

	}
	else// 死んでない
	{
		g_player.state = PLAYERSTATE_DAMAGE;

		g_player.nCounterState = 5;

		SetParticle(g_player.pos, 3);

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0,0, 255);

		//// サウンドの再生
		//PlaySound(SOUND_LABEL_DAMAGE);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPlayer1->Unlock();
}