//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "action_player.h"
#include "Input.h"
#include "action_block.h"
#include "action_particle.h"
#include "action_item.h"
//#include "sound.h"

//マクロ
#define MAX_MAX (400.0f)//最大でかい
#define MAX_MIN (10.0f)//最小ちいさい

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureActionPlayer = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffActionPlayer = NULL;//頂点バッファへのポインタ
ActionPlayer g_player;                                 //レイヤーの情報
int g_nCounterAnimPlayer;
int g_nPatternAnimPlayer;
int g_nMutekiCounter;
bool g_bLandingParticle = false;//着地した際のパーティクル表示用関数

//プレイヤーの初期化処理
void InitActionPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;                   //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ2の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player2.png",      //テクスチャのファイル名
		&g_pTextureActionPlayer);

	g_nMutekiCounter = 0;
	g_player.pos = D3DXVECTOR3(640.0f,670.0f,0.0f);//位置を初期化する SCREEN_HEIGHT-TAKASA
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);   //移動量を初期化する
	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);	   //向きを初期化する、今回はZ軸（3番目）
	g_player.nCntAnimState = 0;
	g_player.nLife = 5;
	g_player.nGuardCnt = 0;
	g_player.bUse = true;
	g_player.bDisp = true;
	g_player.bHit = false;
	g_player.bJamp1st = true;
	g_player.bRightMove = true;
	g_player.bStop = true;
	g_player.bLanding = false;
	g_player.bGetItem = false;
	g_player.bBlockUse = false;
	g_player.pBlock = NULL;

	//対角線の長さを算出する
	g_player.Length = sqrtf(50.0f * 50.0f + 100.0f * 100.0f) / 2.0f;

	//対角線の角度を算出する
	g_player.Angle = atan2f(HABA ,TAKASA);

	//頂点バッファ2の生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffActionPlayer,
		NULL);

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffActionPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = -HABA;//g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.y = g_player.pos.y-TAKASA;//g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = HABA;//g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.y = g_player.pos.y-TAKASA;//g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -HABA;//g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.y = g_player.pos.y;// +cosf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = HABA;//g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.y = g_player.pos.y;// +cosf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);//(u,v)

	//頂点バッファをアンロックする
	g_pVtxBuffActionPlayer->Unlock();
}
//プレイヤーの終了処理
void UninitActionPlayer(void)
{

	//テクスチャの破棄
	if (g_pTextureActionPlayer != NULL)
	{
		g_pTextureActionPlayer->Release();
		g_pTextureActionPlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffActionPlayer != NULL)
	{
		g_pVtxBuffActionPlayer->Release();
		g_pVtxBuffActionPlayer = NULL;
	}
}
//プレイヤーの更新処理
void UpdateActionPlayer(void)
{
	VERTEX_2D* pVtx;//頂点情報へのポインタ
	int nBulletCnt = 0;

	if (g_player.bUse == true)
	{
		if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
		{
			g_nCounterAnimPlayer++;//カウンターを加算
			g_player.bRightMove = false;
			g_player.bStop = false;

			if (g_player.bJamp1st == false)
			{//通常
				//移動量を更新（増加）
				if (g_player.move.x >= MAX_SPEED_L)
				{
					g_player.move.x -= 0.4f;
				}
				else if (g_player.move.x <= MAX_SPEED_L)
				{
 					g_player.move.x = MAX_SPEED_L;
					SetActionParticle(D3DXVECTOR3(g_player.pos.x + HABA / 2, g_player.pos.y, 0.0f), 9);
				}
			}
			if (g_player.bJamp1st == true)
			{//ジャンプ中
				//移動量を更新（増加）
				g_player.move.x -= 0.3f;
			}

		}
		else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true)
		{
			g_nCounterAnimPlayer++;//カウンターを加算
			g_player.bRightMove = true;
			g_player.bStop = false;

			if (g_player.bJamp1st == false)
			{//通常
				//移動量を更新（増加）
				if (g_player.move.x <= MAX_SPEED_R)
				{
					g_player.move.x += 0.4f;
				}
				else if (g_player.move.x >= MAX_SPEED_R)
				{
					g_player.move.x = MAX_SPEED_R;
					SetActionParticle(D3DXVECTOR3(g_player.pos.x - HABA / 2, g_player.pos.y, 0.0f), 8);
				}
			}
			
			if (g_player.bJamp1st == true)
			{//ジャンプ中
				//移動量を更新（増加）
				g_player.move.x += 0.3f;
			}
		}
		else if(KeyboardRelease(DIK_A) == true || KeyboardRelease(DIK_D) == true /*|| JoypadRelease(JOYKEY_LEFT) == true || JoypadRelease(JOYKEY_RIGHT) == true*/)
		{
			g_player.bStop = true;
		}
		else
		{
			g_nCounterAnimPlayer=0;//カウンターをリセット
		}

		if (g_player.bHit == true)
		{
			g_player.nCntAnimState++;//カウンターを加算
		}

		if (KeyboardTrigger(DIK_SPACE) == true /*|| JoypadTrigger(JOYKEY_A) == true*/)//ジャンプ
		{
 			if (g_player.bJamp1st == false)
			{
				//PlaySound(SOUND_LABEL_JAMP_SHORT);
				SetActionParticle(D3DXVECTOR3(g_player.pos.x, g_player.pos.y, 0.0f), 1);
				g_player.move.y = F_JAMP1ST;
				g_player.bJamp1st = true;
				g_player.bLanding = false;
				g_bLandingParticle = true;
			}
		}
	}//g_player.pos

	if (g_player.bLanding == true && g_bLandingParticle == true)
	{//着地
		SetActionParticle(g_player.pos, 14);
		SetActionParticle(g_player.pos, 15);
		g_player.bLanding = false;
		g_bLandingParticle = false;
	}

	//重力を更新
	g_player.move.y += 1.0f;//重力加算

	//前回の位置を保存
	g_player.posOld = g_player.pos;

	if (g_player.pBlock != NULL)//ブロックに乗っている
	{//ブロックが移動した分だけプレイヤーにプラスする
		g_player.pBlock;
	}

	if (CollisionActionBlock(&g_player.pos,
						&g_player.posOld,
						&g_player.move,
						HABA,
						TAKASA,&g_player.pBlock) == true)
	{

	}

	//位置を更新
	g_player.pos.x += g_player.move.x;//横移動
	g_player.pos.y += g_player.move.y;//落下

	//ブロックのあたりはんてぇ
	g_player.bJamp1st = !CollisionActionBlock(&g_player.pos,
										&g_player.posOld,
										&g_player.move,
										HABA,
										TAKASA,&g_player.pBlock);

	g_player.bBlockUse = !CollisionActionBlock2(&g_player.pos,
										&g_player.posOld,
										&g_player.move,
										HABA,
										TAKASA);
	
	//アイテムのあたりはんてぇ
	g_player.bGetItem = !CollisionActionItem(&g_player.pos,
									&g_player.posOld,
									&g_player.move,
									HABA,
									TAKASA);

	//移動量を更新（減衰）
	g_player.move.x += (0.0f - g_player.move.x) * 0.04f;/*0.13f;*/

	if (g_player.pos.x >= 880.0f - HABA)//横
	{
		g_player.pos.x = 880.0f - HABA;
	}
	else if (g_player.pos.x <= 400.0f + HABA)
	{
		g_player.pos.x = 400.0f + HABA;
	}

	if (g_player.pos.y >= SCREEN_HEIGHT)//地面
	{
		g_player.pos.y = SCREEN_HEIGHT;
		g_player.bJamp1st = false;
	}
	else if (g_player.pos.y <= 0 + TAKASA)//天井
	{
		g_player.pos.y = 0 + TAKASA;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffActionPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			//頂点カラーの設定
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
			////モードを設定（リザルト）
			//SetMode(MODE_RESULT_LOSE);
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

	//位置座標の設定
	pVtx[0].pos.x = g_player.pos.x-HABA;
	pVtx[0].pos.y = g_player.pos.y-TAKASA;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x+HABA;
	pVtx[1].pos.y = g_player.pos.y-TAKASA;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x-HABA;
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x+HABA;
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする
	g_pVtxBuffActionPlayer->Unlock();

	//テクスチャ座標の更新0.125
	if (g_player.bRightMove == true && g_player.bJamp1st == false)
	{//右向き
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.5f + 0.25f, 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.5f + 0.25f, 0.5f);//(u,v)
	}
	else if (g_player.bRightMove == false && g_player.bJamp1st == false)
	{//左向き
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.5f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.5f + 0.25f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f + 0.25f, 1.0f);
	}

	if (g_player.bRightMove == true && g_player.bJamp1st == false && GetKeyboardPress(DIK_LSHIFT) == true || g_player.bRightMove == true && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	{//右向き
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f, 0.5f);
	}
	else if (g_player.bRightMove == false && g_player.bJamp1st == false && GetKeyboardPress(DIK_LSHIFT) == true || g_player.bRightMove == false && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	{//左向き
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f, 1.0f);
	}

	if (g_player.bStop == true && g_player.bRightMove == true)//ストップ
	{//右向き
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
	}
	else if (g_player.bStop == true && g_player.bRightMove == false)
	{//左向き
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
	}

	if (g_player.bStop == true && g_player.bRightMove == true && GetKeyboardPress(DIK_LSHIFT) == true || g_player.bRightMove == true && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)//ストップ
	{//右向き
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);
	}
	else if (g_player.bStop == true && g_player.bRightMove == false && GetKeyboardPress(DIK_LSHIFT) == true || g_player.bRightMove == false && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	{//左向き
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
	}

	if (g_player.bJamp1st == true)//ジャンプ中
	{
		if (g_player.bRightMove == true && g_player.bJamp1st == true)
		{//右向き
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.75f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.75f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
		}
		else if (g_player.bRightMove == false && g_player.bJamp1st == true)
		{//左向き
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.75f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.75f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}
}
//プレイヤーの描画処理
void DrawActionPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//頂点バッファをデータストリーム
		pDevice->SetStreamSource(0, g_pVtxBuffActionPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		if (g_player.bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureActionPlayer);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				0,                                     //描画する最初の頂点インデックス
				2);                                    //描画するプリミティブ数
		}
	}
}
ActionPlayer* GetActionPlayer(void)
{
	return &g_player;//プレイヤーの情報を返す
}
D3DXVECTOR3 GetActionPos(void)
{
	return g_player.move;
}
int GetActionLife(void)
{
	return g_player.nLife;
}