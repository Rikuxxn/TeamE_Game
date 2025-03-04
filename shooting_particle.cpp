#include "shooting_particle.h"
#include "shooting_effect.h"
#include "shooting_bullet.h"
#include "shooting_enemy.h"

//グローバル
Particle g_aParticle[MAX_PARTICLE];//パーティクルの情報

//syokika
void InitParticle(void)
{
	int nCntParticle;
	VERTEX_2D* pVtx = 0;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//弾の情報の初期化
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = false;													//使用していない状態にする
		g_aParticle[nCntParticle].nType = 0;
	}
}
//syuuryou
void UninitParticle(void)
{

}
//kousin
void UpdateParticle(void)
{
	int nCntParticle;
	int nCntAppear;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	float fRadius;
	int nLife;
	float angle;
	float length;

	VERTEX_2D* pVtx = 0;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			//パーティクルの生成
			for (nCntAppear = 0; nCntAppear < 20; nCntAppear++)
			{
				if (g_aParticle[nCntParticle].nType == 0)//爆発
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 628 - 314) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 3.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.4f, 0.2f, 0.0f, 0.3f);

					//半径の設定
					fRadius = 15.0f;

					//寿命の設定
					nLife = 30;

					//エフェクトの設定
					SetEffect(pos, move, col, fRadius, nLife,0);
				}
				else if (g_aParticle[nCntParticle].nType == 1)//アフターバーナー
				{

					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					//angle = (float)(rand() % 55 - 185) / 100.0f;
					angle = (float)(rand() % 55 - 180) / 50.0f;
					length = (float)(rand() % 10) / 1.0f - 10.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//move.x = sinf(length) * angle;
					//move.y = cosf(length) * angle;

					//色の設定
					col = D3DXCOLOR(0.4f, 0.2f, 0.0f, 0.3f);

					//半径の設定
					fRadius = 7.0f;

					//寿命の設定
					nLife = 15;

					//エフェクトの設定
					SetEffect(pos, move, col, fRadius, nLife,0);
				}
				else if(g_aParticle[nCntParticle].nType == 3)//ヒット
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 3.0f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.4f, 0.2f, 0.0f, 1.0f);

					//半径の設定
					fRadius = 15.0f;

					//寿命の設定
					nLife = 50;

					//エフェクトの設定
					SetEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 4)//煙1
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 130 - 350) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.1f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.3f);

					//半径の設定
					fRadius = 15.0f;

					//寿命の設定
					nLife = 50;

					//エフェクトの設定
					SetEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 5)//煙2
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 50 - 1) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.3f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.3f);

					//半径の設定
					fRadius = 15.0f;

					//寿命の設定
					nLife = 50;

					//エフェクトの設定
					SetEffect(pos, move, col, fRadius, nLife, 0);
				}


				//位置の設定
				//pos=D3DXVECTOR3();

				//移動量の設定
				// sinf((float)(rand() % 628 - 314) / 100.0f);
				// cosf((float)(rand() % 100) / 25.0f + 10.0f);
				//move.x=sinf(角度)*移動量	角度=-3.14～3.14
				//move.y=cosf(角度)*移動量	
				//角度の求め方  (float)(rand() % 629 - 314) / 100.0f;
				//移動量の求め方(float)(rand() % ***) / *** + ***;

				//色の設定
				//col=;

				//半径の設定
				//fRadius=;

				//寿命の設定
				//nLife=;

				//エフェクトの設定
				//SetEffect();
			}

			for (nCntAppear = 0; nCntAppear < 4; nCntAppear++)
			{
				if (g_aParticle[nCntParticle].nType == 2)//火炎放射的なやつ
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					//angle = (float)(rand() % 40 - 175) / 100.0f;
					angle = (float)(rand() % 40 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 2.0f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//move.x = sinf(length) * angle;
					//move.y = cosf(length) * angle;

					//色の設定
					col = D3DXCOLOR(0.5f, 0.1f, 0.0f, 1.0f);

					//半径の設定
					fRadius = 20.0f;

					//寿命の設定
					nLife = 90;

					//エフェクトの設定
					SetEffect(pos, move, col, fRadius, nLife,1);
				}
			}

			g_aParticle[nCntParticle].nLife--;

			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}
}
void DrawParticle(void)
{

}
Particle* GetParticle(void)
{
	return &g_aParticle[0];
}
void SetParticle(D3DXVECTOR3 pos,int nType)
{
	int nCntParticle;
	VERTEX_2D* pVtx = 0;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].nType = nType;
			g_aParticle[nCntParticle].bUse = true;

			if (g_aParticle[nCntParticle].nType == 0)
			{
				g_aParticle[nCntParticle].nLife = 30;
			}
			else if (g_aParticle[nCntParticle].nType == 1)
			{
				g_aParticle[nCntParticle].nLife = 1;
			}
			break;
		}
	}
}