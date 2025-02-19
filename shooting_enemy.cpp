//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "shooting_enemy.h"
#include "shooting_bullet.h"
#include "shooting_player.h"
#include "shooting_particle.h"
#include "sound.h"

// マクロ
#define NUM_ENEMY (3)// 敵の種類

//gu-baru
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];
int g_nNumEnemy = 0;// 敵の総数

void InitShootingEnemy(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEnemy;

	VERTEX_2D* pVtx;// 頂点情報へのポインタ
	
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy.png",      // テクスチャのファイル名
		&g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy1.png",
		&g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy2.png",
		&g_apTextureEnemy[2]);

	g_nNumEnemy = 0;

	// 敵の情報の初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].BulletCounter = 0;	// 弾カウンター
		g_aEnemy[nCntEnemy].bUse = false;		// 使用していない状態にする
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].MoveCnt = 0;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);// 0.0～1.0で設定
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}
void UninitShootingEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// テクスチャの破棄
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
		break;
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
void UpdateShootingEnemy(void)
{
	VERTEX_2D* pVtx = 0;							// 頂点情報へのポインタ
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);	// 頂点バッファをロックし、頂点情報へのポインタを取得

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].MoveCnt++;
			//g_aEnemy[nCntEnemy].move.x -= g_aEnemy[nCntEnemy].pos.x;
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:

				switch (g_aEnemy[nCntEnemy].nType)
				{
				case 0:
					if (g_aEnemy[nCntEnemy].MoveCnt >= 60)// 動きを反転させる
					{
						g_aEnemy[nCntEnemy].move.x *= -1.0f;
						g_aEnemy[nCntEnemy].MoveCnt = 0;
					}
					break;
				case 1:
					if (g_aEnemy[nCntEnemy].MoveCnt >= 60)// 動きを反転させる
					{
						g_aEnemy[nCntEnemy].move.x *= -1.0f;
						g_aEnemy[nCntEnemy].MoveCnt = 0;
					}

					break;
				case 2:
					if (g_aEnemy[nCntEnemy].MoveCnt >= 150)// 動きを反転させる
					{
						g_aEnemy[nCntEnemy].move.x *= -1.0f;
						g_aEnemy[nCntEnemy].MoveCnt = 0;
					}
					break;
				}
				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState<=0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					// 頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);// 0.0～1.0で設定
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				}
				break;
			}

			// 位置を更新
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);

			// テクスチャ
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		pVtx += 4;
	}					
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}
void DrawShootingEnemy(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			// 使用されてる
			int nType = g_aEnemy[nCntEnemy].nType;

			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[nType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// プリミティブの種類
				nCntEnemy*4,						   // 描画する最初の頂点インデックス
				2);									   // 描画するプリミティブ数
		}
	}
}
void SetEnemy(D3DXVECTOR3 pos,D3DXVECTOR3 move, int nType)
{
	VERTEX_2D* pVtx=0;// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			// 敵の情報の設定
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nLife = 9;
			g_aEnemy[nCntEnemy].BulletCounter = 0;
			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].MoveCnt = 0;
			g_nNumEnemy++;// 敵の総数カウントダウン
			
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);
			
			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);// 0.0～1.0で設定
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			break;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

}
Enemy* GetShootingEnemy(void)
{
	return &g_aEnemy[0];// 敵の情報の先頭アドレスを返す
}
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx=0;// 頂点情報へのポインタ

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		// サウンドの再生
		PlaySound(SOUND_LABEL_STDEAD);
		SetParticle(g_aEnemy[nCntEnemy].pos,0);
		//bakuhatu
		g_aEnemy[nCntEnemy].bUse = false;
		g_nNumEnemy--;// 敵の総数カウントダウン
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;
		
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntEnemy;

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);// 0.0～1.0で設定
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		// 頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();

		// サウンドの再生
		PlaySound(SOUND_LABEL_STHIT);
	}
}
int GetNumEnemy()
{
	return g_nNumEnemy;
}