//---------------------------------------------------------
// 2Dアクション
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "crane_player.h"
#include "Input.h"
#include "crane_block.h"
#include "crane_particle.h"
#include "crane_item.h"
//#include "sound.h"

//マクロ
#define MAX_MAX (400.0f)//最大でかい
#define MAX_MIN (10.0f)//最小ちいさい

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureCranePlayer = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCranePlayer = NULL;//頂点バッファへのポインタ
CranePlayer g_player;                                 //レイヤーの情報
int g_nCounterAnimPlayer;
int g_nPatternAnimPlayer;
int g_nMutekiCounter;
bool g_bLandingParticle = false;//着地した際のパーティクル表示用関数

//プレイヤーの初期化処理
void InitCranePlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ2の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\crane.png",					 //テクスチャのファイル名
		&g_pTextureCranePlayer);

	g_nMutekiCounter = 0;
	g_player.pos = D3DXVECTOR3(FIELD_LEFT + 75.0f, 70.0f, 0.0f);	//位置を初期化する SCREEN_HEIGHT-TAKASA
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);					//移動量を初期化する
	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);						//向きを初期化する、今回はZ軸（3番目）
	g_player.nCntAnimState = 0;
	g_player.nLife = 5;
	g_player.bUse = true;
	g_player.bMove = true;
	g_player.bLeft = false;
	g_player.bLanding = false;
	g_player.bGetItem = false;
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
		&g_pVtxBuffCranePlayer,
		NULL);

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCranePlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = -HABA;
	pVtx[0].pos.y = g_player.pos.y-TAKASA;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = HABA;;
	pVtx[1].pos.y = g_player.pos.y-TAKASA;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -HABA;
	pVtx[2].pos.y = g_player.pos.y;;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = HABA;
	pVtx[3].pos.y = g_player.pos.y;
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

	////テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	//pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);//(u,v)
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);//(u,v)
	//pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);//(u,v)

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	//頂点バッファをアンロックする
	g_pVtxBuffCranePlayer->Unlock();
}
//プレイヤーの終了処理
void UninitCranePlayer(void)
{
	//テクスチャの破棄
	if (g_pTextureCranePlayer != NULL)
	{
		g_pTextureCranePlayer->Release();
		g_pTextureCranePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffCranePlayer != NULL)
	{
		g_pVtxBuffCranePlayer->Release();
		g_pVtxBuffCranePlayer = NULL;
	}
}
//プレイヤーの更新処理
void UpdateCranePlayer(void)
{
	VERTEX_2D* pVtx;//頂点情報へのポインタ
	int nBulletCnt = 0;

	if (g_player.bUse == true)
	{
		if (g_player.bMove == true && (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true))
		{
			g_nCounterAnimPlayer++;//カウンターを加算
			//移動量を更新（増加）
			if (g_player.move.x <= MAX_SPEED_R)
			{ 
				g_player.move.x += 0.4f;
			}
			else if (g_player.move.x >= MAX_SPEED_R)
			{
				g_player.move.x = MAX_SPEED_R;
			}
		}
		else
		{
			g_nCounterAnimPlayer=0;//カウンターをリセット
		}

		if (g_player.bMove == true && (GetMouseButtonTrigger(0) /*|| JoypadTrigger(JOYKEY_A) == true*/))//ジャンプ
		{
			//PlaySound(SOUND_LABEL_JAMP_SHORT);
			g_player.move.y = DOWN;
			g_player.bMove = false;
			g_player.bLeft = false;
		}
	}//g_player.pos

	if (g_player.bLeft == true && g_player.bMove == false)
	{
		g_player.move.x = MAX_SPEED_L;
	}

	if (g_player.bLanding == true)
	{//上に昇る
		g_player.move.y = UP;
	}

	//前回の位置を保存
	g_player.posOld = g_player.pos;

	if (g_player.pBlock != NULL)//ブロックに乗っている
	{//ブロックが移動した分だけプレイヤーにプラスする
		g_player.pBlock;
	}

	if (CollisionCraneBlock(&g_player.pos,
						&g_player.posOld,
						&g_player.move,
						HABA,
						TAKASA,&g_player.pBlock) == true)
	{

	}

	//位置を更新
	g_player.pos.x += g_player.move.x;//横移動
	g_player.pos.y += g_player.move.y;//落下

	//アイテムのあたりはんてぇ
	g_player.bGetItem = !CollisionCraneItem(&g_player.pos,
									&g_player.posOld,
									&g_player.move,
									ITEM_WIDTH,
									ITEM_HEIGHT);

	//移動量を更新（減衰）
	g_player.move.x += (0.0f - g_player.move.x) * 0.04f;/*0.13f;*/

	if (g_player.pos.y >= FIELD_UNDER)//地面
	{
		g_player.pos.y = FIELD_UNDER;
		g_player.bLanding = true;
	}
	if (g_player.pos.y <= FIELD_TOP + TAKASA)//天井
	{
		g_player.pos.y = FIELD_TOP + TAKASA;
		g_player.bLeft = true;
	}
	if (g_player.pos.x >= FIELD_RIGHT - HABA)//右
	{
		g_player.pos.x = FIELD_RIGHT - HABA;
	}
	if (g_player.pos.x <= FIELD_LEFT + 75.0f + HABA)//左
	{
		g_player.pos.x = FIELD_LEFT + 75.0f + HABA;
		g_player.bMove = true;
		g_player.bLeft = false;
		g_player.bLanding = false;
		g_player.move.x = 0;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
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
	g_pVtxBuffCranePlayer->Unlock();

	////テクスチャ座標の更新0.125
	//if (g_player.bRightMove == true && g_player.bJamp1st == false)
	//{//右向き
	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);//(u,v)
	//	pVtx[1].tex = D3DXVECTOR2(0.5f + 0.25f, 0.0f);//(u,v)
	//	pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);//(u,v)
	//	pVtx[3].tex = D3DXVECTOR2(0.5f + 0.25f, 0.5f);//(u,v)
	//}
	//else if (g_player.bRightMove == false && g_player.bJamp1st == false)
	//{//左向き
	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.5f, 0.5f);//(u,v)
	//	pVtx[1].tex = D3DXVECTOR2(0.5f + 0.25f, 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(0.5f + 0.25f, 1.0f);
	//}

	//if (g_player.bRightMove == true && g_player.bJamp1st == false && KeyboardRepeat(DIK_LSHIFT) == true || g_player.bRightMove == true && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	//{//右向き
	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);//(u,v)
	//	pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
	//	pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f, 0.5f);
	//}
	//else if (g_player.bRightMove == false && g_player.bJamp1st == false && KeyboardRepeat(DIK_LSHIFT) == true || g_player.bRightMove == false && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	//{//左向き
	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);//(u,v)
	//	pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f, 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f, 1.0f);
	//}

	//if (g_player.bStop == true && g_player.bRightMove == true)//ストップ
	//{//右向き
	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	//	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
	//}
	//else if (g_player.bStop == true && g_player.bRightMove == false)
	//{//左向き
	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	//	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
	//}

	//if (g_player.bStop == true && g_player.bRightMove == true && KeyboardRepeat(DIK_LSHIFT) == true || g_player.bRightMove == true && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)//ストップ
	//{//右向き
	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
	//	pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);
	//}
	//else if (g_player.bStop == true && g_player.bRightMove == false && KeyboardRepeat(DIK_LSHIFT) == true || g_player.bRightMove == false && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	//{//左向き
	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);
	//	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
	//}

	//if (g_player.bJamp1st == true)//ジャンプ中
	//{
	//	if (g_player.bRightMove == true && g_player.bJamp1st == true)
	//	{//右向き
	//		//テクスチャ座標の設定
	//		pVtx[0].tex = D3DXVECTOR2(0.75f, 0.0f);
	//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[2].tex = D3DXVECTOR2(0.75f, 0.5f);
	//		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
	//	}
	//	else if (g_player.bRightMove == false && g_player.bJamp1st == true)
	//	{//左向き
	//		//テクスチャ座標の設定
	//		pVtx[0].tex = D3DXVECTOR2(0.75f, 0.5f);
	//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
	//		pVtx[2].tex = D3DXVECTOR2(0.75f, 1.0f);
	//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//	}
	//}
}
//プレイヤーの描画処理
void DrawCranePlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffCranePlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_player.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureCranePlayer);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
			0,                                     //描画する最初の頂点インデックス
			2);                                    //描画するプリミティブ数
	}
}
CranePlayer* GetCranePlayer(void)
{
	return &g_player;//プレイヤーの情報を返す
}
D3DXVECTOR3 GetCranePos(void)
{
	return g_player.move;
}
int GetCraneLife(void)
{
	return g_player.nLife;
}