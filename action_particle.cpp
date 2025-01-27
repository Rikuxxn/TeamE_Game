//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "action_particle.h"
#include "action_effect.h"

//グローバル
ActionParticle g_aParticle[MAX_PARTICLE];//パーティクルの情報

//syokika
void InitActionParticle(void)
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
void UninitActionParticle(void)
{

}
//kousin
void UpdateActionParticle(void)
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
					nLife = 50;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife,0);
				}
				else if (g_aParticle[nCntParticle].nType == 1)//ジャンプ
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 90 - 50) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 1.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.8f);

					//半径の設定
					fRadius = 20.0f;

					//寿命の設定
					nLife = 40;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife,0);
				}
				else if(g_aParticle[nCntParticle].nType == 3)//バリアに当たった(右から)
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.1f, 0.1f, 0.4f, 1.0f);

					//半径の設定
					fRadius = 15.0f;

					//寿命の設定
					nLife = 50;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 4)//バリアに当たった(左から)
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.1f, 0.1f, 0.4f, 1.0f);

					//半径の設定
					fRadius = 15.0f;

					//寿命の設定
					nLife = 50;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 5)//着地
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 90 - 50) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * -length;

					//色の設定
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f);

					//半径の設定
					fRadius = 10.0f;

					//寿命の設定
					nLife = 30;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 6)//空中ダッシュ(左から)
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 1.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.8f);

					//半径の設定
					fRadius = 20.0f;

					//寿命の設定
					nLife = 40;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 7)//空中ダッシュ(右から)
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;
	
					//移動量の設定
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 1.0f;
	
					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;
	
					//色の設定
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.8f);

					//半径の設定
					fRadius = 20.0f;
	
					//寿命の設定
					nLife = 40;
	
					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 8)//地上走り(右に)
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 40 - 180) / 60.0f;//50.0f;
					length = (float)(rand() % 10) / 1.0f + 1.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.8f);

					//半径の設定
					fRadius = 7.0f;

					//寿命の設定
					nLife = 15;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 9)//地上走り(左に)
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 40 - 180) / 60.0f;
					length = (float)(rand() % 10) / 1.0f + 1.0f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.8f);

					//半径の設定
					fRadius = 7.0f;

					//寿命の設定
					nLife = 15;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 10)//タックル(右向き)
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(1.0f, 0.0f, 0.4f, 1.0f);

					//半径の設定
					fRadius = 20.0f;

					//寿命の設定
					nLife = 50;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 11)//タックル(左向き)
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(1.0f, 0.0f, 0.4f, 1.0f);

					//半径の設定
					fRadius = 20.0f;

					//寿命の設定
					nLife = 50;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 12)//チャージ完了
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 628 - 314) / 100.0f;
					length = (float)(rand() % 10) / 1.0f - 1.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.4f, 0.4f, 0.0f, 0.4f);

					//半径の設定
					fRadius = 8.0f;

					//寿命の設定
					nLife = 6;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 13)//弾の爆発
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;
					
					//移動量の設定
					angle = (float)(rand() % 628 - 314) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 3.0f;
					
					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;
					
					//色の設定
					col = D3DXCOLOR(0.4f, 0.2f, 0.0f, 0.8f);
					
					//半径の設定
					fRadius = 15.0f;
					
					//寿命の設定
					nLife = 20;
					
					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 16)//ダッシュ右
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.2f);

					//半径の設定
					fRadius = 10.0f;

					//寿命の設定
					nLife = 15;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 17)//ダッシュ右
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.2f);

					//半径の設定
					fRadius = 10.0f;

					//寿命の設定
					nLife = 15;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
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
				//SetActionEffect();
			}

			for (nCntAppear = 0; nCntAppear < 10; nCntAppear++)
			{
				if (g_aParticle[nCntParticle].nType == 14)//着地(左から)
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 50 - 180) / 80.0f;
					length = (float)(rand() % 10) / 1.0f + 0.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.3f);

					//半径の設定
					fRadius = 20.0f;

					//寿命の設定
					nLife = 30;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 15)//着地(右から)
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 50 - 180) / 80.0f;
					length = (float)(rand() % 10) / 1.0f + 0.0f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.3f);

					//半径の設定
					fRadius = 20.0f;

					//寿命の設定
					nLife = 30;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}

			}

			for (nCntAppear = 0; nCntAppear < 4; nCntAppear++)
			{
				if (g_aParticle[nCntParticle].nType == 2)//火炎放射的なやつ
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

					//移動量の設定
					angle = (float)(rand() % 40 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 2.0f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//色の設定
					col = D3DXCOLOR(0.5f, 0.1f, 0.0f, 1.0f);

					//半径の設定
					fRadius = 20.0f;

					//寿命の設定
					nLife = 90;

					//エフェクトの設定
					SetActionEffect(pos, move, col, fRadius, nLife,1);
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
void DrawActionParticle(void)
{

}
ActionParticle* GetActionParticle(void)
{
	return &g_aParticle[0];
}
void SetActionParticle(D3DXVECTOR3 pos,int nType)
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