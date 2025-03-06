//=======================================
//
// プレイヤー処理 [player.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "model.h"
#include "motion.h"

#include <stdio.h>
#include <string.h>
#include "enemy.h"
#include "block.h"
#include "light.h"
#include "sound.h"
#include "game.h"

//グローバル変数
Player g_player;			//プレイヤーの情報
int g_nIdxShadow;
int g_nCntMotion;
int g_nMotion;				//モーションセットを管理
bool g_bFinishMotion;		//モーションセットが終わったか

//=============================
// プレイヤーの初期化処理
//=============================
void InitPlayer(void)
{

	MODE pMode = GetMode();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期化
	g_player.pos = D3DXVECTOR3(120.0f, 0.0f, -540.0f);			// 位置を初期化する
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 前の位置を初期化する
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 移動量を初期化する
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向きを初期化する
	g_player.rotDestPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向きを初期化する
	g_player.fDush = PLAYER_STAMINA;							// ダッシュ時の速度
	g_player.nDrawDush = 0;										// ダッシュゲージ描画用
	g_player.state = PLAYERSTATE_NORMAL;						// プレイヤーの状態
	g_player.bDush = false;										// ダッシュしているか
	g_player.bDisp = true;										// プレイヤーの描画
	g_player.bEmpty = false;									// ダッシュできるか
	g_player.bDrawDush = false;									// ダッシュゲージ描画用
	g_player.motion.bLoopMotion = true;							// モーションをループさせるか
	g_player.motion.nCounterMotion = 0;							// モーション用のカウンター
	g_player.motion.aMotionInfo[MOTIONTYPE_MOVE].startKey = 1;	// モーションの最初のキー
	//g_player.pos = D3DXVECTOR3(120.0f, 0.0f, 540.0f);			// デバッグ用
	g_player.bEmptySound = false;
	g_player.bDushSound = false;

	// プレイヤーの読み込み
	LoadPlayerTEXT();

	//// 影の設定
	//g_nIdxShadow = SetShadow(D3DXVECTOR3(g_player.pos.x, g_player.pos.y, g_player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//オフセット考慮
	for (int nCntOff = 0; nCntOff < g_player.motion.nNumModel; nCntOff++)
	{
		g_player.motion.aModel[nCntOff].Offpos = g_player.motion.aModel[nCntOff].pos;
		g_player.motion.aModel[nCntOff].Offrot = g_player.motion.aModel[nCntOff].rot;
	}

	for (int nCntVtx = 0; nCntVtx < MAX_PARTS; nCntVtx++)
	{

		int nNumVtx;	//頂点数
		DWORD sizeFVF;	//頂点フォーマットのサイズ
		BYTE* pVtxBuff;	//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = g_player.motion.aModel[nCntVtx].pMesh->GetNumVertices();

		//頂点フォーマットの取得
		sizeFVF = D3DXGetFVFVertexSize(g_player.motion.aModel[nCntVtx].pMesh->GetFVF());

		//頂点バッファのロック
		g_player.motion.aModel[nCntVtx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値最大値を取得
			if (vtx.x < g_player.vtxMin.x)
			{
				g_player.vtxMin.x = vtx.x;
			}
			else if (vtx.y < g_player.vtxMin.y)
			{
				g_player.vtxMin.y = vtx.y;
			}
			else if (vtx.z < g_player.vtxMin.z)
			{
				g_player.vtxMin.z = vtx.z;
			}

			if (vtx.x > g_player.vtxMax.x)
			{
				g_player.vtxMax.x = vtx.x;
			}
			else if (vtx.y > g_player.vtxMax.y)
			{
				g_player.vtxMax.y = vtx.y;
			}
			else if (vtx.z > g_player.vtxMax.z)
			{
				g_player.vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		g_player.size.x = (g_player.vtxMax.x - g_player.vtxMin.x);
		g_player.size.y = (g_player.vtxMax.y - g_player.vtxMin.y);
		g_player.size.z = (g_player.vtxMax.z - g_player.vtxMin.z);

		//頂点バッファのアンロック
		g_player.motion.aModel[nCntVtx].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.motion.aModel[nCntVtx].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.motion.aModel[nCntVtx].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャファイルが存在する

				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_player.motion.aModel[nCntVtx].apTexture[nCntMat]);

			}
		}
	}
}
//=============================
// プレイヤーの終了処理
//=============================
void UninitPlayer(void)
{
	StopSound(SOUND_LABEL_PLAYERSTEP1);
	StopSound(SOUND_LABEL_PLAYERSTEP2);

	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		for (int nCntMat = 0; nCntMat < (int)g_player.motion.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			//テクスチャの破棄
			if (g_player.motion.aModel[nCntModel].apTexture[nCntMat] != NULL)
			{
				g_player.motion.aModel[nCntModel].apTexture[nCntMat]->Release();
				g_player.motion.aModel[nCntModel].apTexture[nCntMat] = NULL;
			}
		}

		//メッシュの破棄
		if (g_player.motion.aModel[nCntModel].pMesh != NULL)
		{
			g_player.motion.aModel[nCntModel].pMesh->Release();
			g_player.motion.aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_player.motion.aModel[nCntModel].pBuffMat != NULL)
		{
			g_player.motion.aModel[nCntModel].pBuffMat->Release();
			g_player.motion.aModel[nCntModel].pBuffMat = NULL;
		}

	}

}
//=============================
// プレイヤーの更新処理
//=============================
void UpdatePlayer(void)
{
	MODE pMode = GetMode();

	XINPUT_STATE* pStick = GetJoyStickAngle();
	Block* pBlock = GetBlock();
	Camera* pCamera = GetCamera();
	GAME* pGame = GetGame();
	Flags* pFlag = GetFlag();

	bool bEnd = GetEnd();

	g_player.motion.motionType = MOTIONTYPE_NEUTRAL;

	if (bEnd == true)
	{
		g_player.motion.motionType = MOTIONTYPE_NEUTRAL;
	}

	if (pFlag->bExit == false && g_player.bDisp == true && bEnd == false && pGame->bDraw == false &&
		pGame->bDraw2 == false && pGame->bDraw3 == false && pGame->bDraw4 == false && pGame->bBallHint == false && 
		pGame->bCraneHint == false && pGame->bMap == false)
	{

		// 一人称 ゲームパッドの移動処理
		if (GetJoyStick() == true)
		{
			// 左スティックの入力を取得
			float stickX = pStick->Gamepad.sThumbLX;
			float stickY = pStick->Gamepad.sThumbLY;

			// デッドゾーン処理
			const float DEADZONE = 10922.0f;

			if (fabsf(stickX) < DEADZONE)
			{
				stickX = 0.0f;
			}
			if (fabsf(stickY) < DEADZONE)
			{
				stickY = 0.0f;
			}

			// 正規化
			float magnitude = sqrtf(stickX * stickX + stickY * stickY);
			if (magnitude > 0.0f)
			{
				stickX /= magnitude;
				stickY /= magnitude;
			}

			// カメラの回転を取得
			float cameraYaw = pCamera->rot.y;

			// 移動ベクトル計算
			float moveX = -(stickX * cosf(cameraYaw) + stickY * sinf(cameraYaw));
			float moveZ = stickX * sinf(-cameraYaw) + stickY * cosf(cameraYaw);

			// 移動方向反転
			moveZ = -moveZ;

			// プレイヤーの移動更新
			g_player.move.x += moveX * PLAYER_SPEED;
			g_player.move.z += moveZ * PLAYER_SPEED;

			// プレイヤーの向きを更新
			g_player.rotDestPlayer.y = atan2f(-moveX, -moveZ);

			g_player.motion.motionType = MOTIONTYPE_MOVE;
		}

		if (GetKeyboardPress(DIK_A) == true /*|| GetJoypadPress(JOYKEY_LEFT) == true*/)
		{//Aキーが押された

			if (GetKeyboardPress(DIK_W) == true /*|| GetJoypadPress(JOYKEY_UP) == true*/)
			{//Wキーが押された
				if ((GetKeyboardPress(DIK_LSHIFT) == true/* || GetJoypadPress(JOYKEY_RB) == true*/ )&& g_player.fDush >= 0 &&
					g_player.fDush > 0 && g_player.bEmpty == false)
				{// ダッシュ時
					g_player.fDush--;
					g_player.bDush = true;
					g_player.nDrawDush = 0;
					g_player.bDrawDush = true;
					//ダッシュ時の移動量を更新(増加させる)
					g_player.move.x -= sinf(pCamera->rot.y + -D3DX_PI * 0.25f) * PLAYER_DUSHSPEED;
					g_player.move.z -= cosf(pCamera->rot.y + -D3DX_PI * 0.25f) * PLAYER_DUSHSPEED;

					g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.75f;

					g_player.motion.motionType = MOTIONTYPE_MOVE;
				}
				else				
				{
					//歩く時の移動量を更新(増加させる)
					g_player.move.x -= sinf(pCamera->rot.y + -D3DX_PI * 0.25f) * PLAYER_SPEED;
					g_player.move.z -= cosf(pCamera->rot.y + -D3DX_PI * 0.25f) * PLAYER_SPEED;

					g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.75f;

					g_player.motion.motionType = MOTIONTYPE_MOVE;
				}

			}
			else if (GetKeyboardPress(DIK_S) == true /*|| GetJoypadPress(JOYKEY_DOWN) == true*/)
			{//Sキーが押された

				//移動量を更新(増加させる)
				g_player.move.x -= sinf(pCamera->rot.y + -D3DX_PI * 0.75f) * PLAYER_SPEED;
				g_player.move.z -= cosf(pCamera->rot.y + -D3DX_PI * 0.75f) * PLAYER_SPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.25f;

				g_player.motion.motionType = MOTIONTYPE_MOVE;

			}
			else
			{

				//移動量を更新(増加させる)
				g_player.move.z -= sinf(pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.x += cosf(pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.5f;

				g_player.motion.motionType = MOTIONTYPE_MOVE;

			}

		}
		else if (GetKeyboardPress(DIK_D) == true /*|| GetJoypadPress(JOYKEY_RIGHT) == true*/)
		{//Dキーが押された

			if (GetKeyboardPress(DIK_W) == true /*|| GetJoypadPress(JOYKEY_UP) == true*/)
			{//Wキーが押された
				// ダッシュ時
				if ((GetKeyboardPress(DIK_LSHIFT) == true /*|| GetJoypadPress(JOYKEY_RB) == true*/) && g_player.fDush >= 0 &&
					g_player.fDush > 0 && g_player.bEmpty == false)
				{
					g_player.fDush--;
					g_player.bDush = true;
					g_player.nDrawDush = 0;
					g_player.bDrawDush = true;
					//ダッシュの移動量を更新(増加させる)
					g_player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_DUSHSPEED;
					g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_DUSHSPEED;

					g_player.rotDestPlayer.y = pCamera->rot.y + (-D3DX_PI * 0.75f);

					g_player.motion.motionType = MOTIONTYPE_MOVE;
				}
				else
				{
					//歩く時の移動量を更新(増加させる)
					g_player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_SPEED;
					g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_SPEED;

					g_player.rotDestPlayer.y = pCamera->rot.y + (-D3DX_PI * 0.75f);

					g_player.motion.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetKeyboardPress(DIK_S) == true /*|| GetJoypadPress(JOYKEY_DOWN) == true*/)
			{//Sキーが押された

				//移動量を更新(増加させる)
				g_player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.75f) * PLAYER_SPEED;
				g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.75f) * PLAYER_SPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + (-D3DX_PI * 0.25f);

				g_player.motion.motionType = MOTIONTYPE_MOVE;

			}
			else
			{

				//移動量を更新(増加させる)
				g_player.move.z += sinf(pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.x -= cosf(pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + -D3DX_PI * 0.5f;

				g_player.motion.motionType = MOTIONTYPE_MOVE;

			}

		}
		else if (GetKeyboardPress(DIK_W) == true /*|| GetJoypadPress(JOYKEY_UP) == true*/)
		{//Wキーが押された	
			// ダッシュ時
			if ((GetKeyboardPress(DIK_LSHIFT) == true /*|| GetJoypadPress(JOYKEY_RB) == true*/) && g_player.fDush >= 0 &&
				g_player.fDush > 0 && g_player.bEmpty == false)
			{
				g_player.fDush--;
				g_player.bDush = true;
				g_player.nDrawDush = 0;
				g_player.bDrawDush = true;
				if (g_player.bDushSound == false)
				{
					//PlaySound(SOUND_LABEL_EMPTYBREATH);
					g_player.bDushSound = true;
				}

				//ダッシュの移動量を更新(増加させる)
				g_player.move.x -= sinf(pCamera->rot.y) * PLAYER_DUSHSPEED;
				g_player.move.z -= cosf(pCamera->rot.y) * PLAYER_DUSHSPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI;

				g_player.motion.motionType = MOTIONTYPE_MOVE;
			}
			else
			{
				//歩く時の移動量を更新(増加させる)
				g_player.move.x -= sinf(pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf(pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI;
				g_player.bDushSound = false;

				g_player.motion.motionType = MOTIONTYPE_MOVE;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true /*|| GetJoypadPress(JOYKEY_DOWN) == true*/)
		{//Sキーが押された

			//移動量を更新(増加させる)
			g_player.move.x += sinf(pCamera->rot.y) * PLAYER_SPEED;
			g_player.move.z += cosf(pCamera->rot.y) * PLAYER_SPEED;

			g_player.rotDestPlayer.y = pCamera->rot.y;

			g_player.motion.motionType = MOTIONTYPE_MOVE;

		}

		if (g_player.fDush <= 0)
		{//息切れ
			g_player.bEmpty = true;
			g_player.bDush = false;
			g_player.bEmptySound = true;
		}

		if (g_player.bEmpty == true &&
			g_player.bEmptySound == true)
		{//息切れ時のサウンド
			PlaySound(SOUND_LABEL_EMPTYBREATH);
			g_player.bEmptySound = false;
		}

		//ダッシュしていない時
		if ((GetKeyboardPress(DIK_LSHIFT) == false /*|| GetJoypadPress(JOYKEY_RB) == false*/))
		{
			g_player.bDush = false;
		}

		if (g_player.fDush >= PLAYER_STAMINA &&
			(GetKeyboardPress(DIK_LSHIFT) == false /*|| GetJoypadPress(JOYKEY_RB) == false*/))
		{
			g_player.nDrawDush++;
		}

		if (g_player.nDrawDush >= 60)
		{
			g_player.nDrawDush = 0;
			g_player.bDrawDush = false;
		}

		//重力加算
		g_player.move.y -= MAX_GRAVITY;

		//向きの正規化
		if (g_player.rotDestPlayer.y - g_player.rot.y > D3DX_PI)
		{
			g_player.rot.y += D3DX_PI * 2.0f;
		}
		else if (g_player.rotDestPlayer.y - g_player.rot.y < -D3DX_PI)
		{
			g_player.rot.y -= D3DX_PI * 2.0f;
		}


		g_player.rot.y += (g_player.rotDestPlayer.y - g_player.rot.y) * 0.2f;


		//前回の位置を更新
		g_player.posOld = g_player.pos;


		//位置を更新
		g_player.pos.x += g_player.move.x;
		CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.size);

		g_player.pos.y += g_player.move.y;
		CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.size);

		g_player.pos.z += g_player.move.z;
		CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.size);

	}

	if (g_player.bDush == false || GetKeyboardPress(DIK_W) == false)
	{//スタミナ回復
		if (g_player.fDush <= PLAYER_STAMINA)
		{
			g_player.fDush += STAMINA_RECOVERY;
		}
		else if (g_player.fDush >= PLAYER_STAMINA)
		{
			g_player.fDush += 0;
			g_player.bEmpty = false;
		}
	}

	// カメラの回転角（Yaw, Pitch）を取得
	float yaw = pCamera->rot.y;   // 水平回転
	float pitch = pCamera->rot.x; // 垂直回転

	// 視線方向（forward）を計算
	g_player.forward.x = -sinf(yaw) * cosf(pitch);
	g_player.forward.y = -sinf(pitch);
	g_player.forward.z = -cosf(yaw) * cosf(pitch);

	// 視線方向を正規化
	D3DXVec3Normalize(&g_player.forward, &g_player.forward);
	
	if (g_player.pos.y <= 0)
	{
		g_player.pos.y = 0.0f;
	}

	//移動量を更新(減衰させる)
	g_player.move.x += (0.0f - g_player.move.x) * 0.3f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.3f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.1f;

	if (g_player.bDush == true)
	{// 走っているとき
		if (g_player.motion.motionType == MOTIONTYPE_MOVE && g_player.motion.nKey == 1 && g_player.motion.nCounterMotion == 9)
		{
			PlaySound(SOUND_LABEL_PLAYERSTEP1);
			//PlaySound3D(SOUND_LABEL_PLAYERSTEP1);
		}
		else if (g_player.motion.motionType == MOTIONTYPE_MOVE && g_player.motion.nKey == 3 && g_player.motion.nCounterMotion == 5)
		{
			PlaySound(SOUND_LABEL_PLAYERSTEP2);
			//PlaySound3D(SOUND_LABEL_PLAYERSTEP2);
		}
	}
	else
	{// 歩いているとき
		if (g_player.motion.motionType == MOTIONTYPE_MOVE && g_player.motion.nKey == 1 && g_player.motion.nCounterMotion == 9)
		{
			PlaySound(SOUND_LABEL_PLAYERSTEP1);
			//PlaySound3D(SOUND_LABEL_PLAYERSTEP1);
		}
		else if (g_player.motion.motionType == MOTIONTYPE_MOVE && g_player.motion.nKey == 3 && g_player.motion.nCounterMotion == 12)
		{
			PlaySound(SOUND_LABEL_PLAYERSTEP2);
			//PlaySound3D(SOUND_LABEL_PLAYERSTEP2);
		}
	}


	//// 影のpos設定
	//SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_player.pos.x, 0.0f, g_player.pos.z));


	//全モデルの更新
	for (int nCntModel = 0; nCntModel < g_player.motion.nNumModel; nCntModel++)
	{

		int nNextKey = (g_player.motion.nKey + 1) % g_player.motion.aMotionInfo[g_player.motion.motionType].nNumKey;

		// 境界チェック
		if (g_player.motion.nKey >= g_player.motion.aMotionInfo[g_player.motion.motionType].nNumKey || nNextKey >= g_player.motion.aMotionInfo[g_player.motion.motionType].nNumKey)
		{
			g_player.motion.nKey = 0;
		}

		D3DXVECTOR3 Mpos, Mrot;
		D3DXVECTOR3 MAnswer, MAnswer2;//計算結果用

		//キー情報から位置・向きを算出
		Mpos.x = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosX - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosX;
		Mpos.y = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosY - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosY;
		Mpos.z = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosZ - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosZ;
																																															 
		Mrot.x = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotX - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotX;
		Mrot.y = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotY - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotY;
		Mrot.z = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotZ - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotZ;

		//補間係数を計算
		float t = (float)g_player.motion.nCounterMotion / g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].nFrame;

		//求める値
		MAnswer.x = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosX + Mpos.x * t;
		MAnswer.y = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosY + Mpos.y * t;
		MAnswer.z = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosZ + Mpos.z * t;

		MAnswer2.x = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotX + Mrot.x * t;
		MAnswer2.y = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotY + Mrot.y * t;
		MAnswer2.z = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotZ + Mrot.z * t;


		//全パーツの位置・向きを設定
		g_player.motion.aModel[nCntModel].pos = g_player.motion.aModel[nCntModel].Offpos + MAnswer;

		g_player.motion.aModel[nCntModel].rot = g_player.motion.aModel[nCntModel].Offrot + MAnswer2;

	}

	g_player.motion.nCounterMotion++;//再生フレーム数に達したら現在のキーを1つ進める

	if (g_player.motion.nCounterMotion >= g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].nFrame)
	{
		g_player.motion.nCounterMotion = 0;

		g_player.motion.nKey++;
	}

}
//=============================
// プレイヤーの描画処理
//=============================
void DrawPlayer(void)
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	//全モデル(パーツ)の描画
	for (int nCntModel = 0; nCntModel < g_player.motion.nNumModel; nCntModel++)
	{


		//パーツを描画しない
		continue;


		D3DXMATRIX mtxRotModel, mtxTransModel;//計算用マトリックス

		D3DXMATRIX mtxParent;//親のマトリックス

		//パーツのワールドマトリックスも初期化
		D3DXMatrixIdentity(&g_player.motion.aModel[nCntModel].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.motion.aModel[nCntModel].rot.y, g_player.motion.aModel[nCntModel].rot.x, g_player.motion.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld, &g_player.motion.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_player.motion.aModel[nCntModel].pos.x, g_player.motion.aModel[nCntModel].pos.y, g_player.motion.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld, &g_player.motion.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//パーツの親のマトリックスを設定
		if (g_player.motion.aModel[nCntModel].nIdxModelParent != -1)
		{//親モデルがある場合

			mtxParent = g_player.motion.aModel[g_player.motion.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{//親モデルがない場合

			mtxParent = g_player.mtxWorld;
		}

		//算出したパーツのワールドマトリックスと親のマトリックスをかけ合わせる
		D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld, &g_player.motion.aModel[nCntModel].mtxWorld, &mtxParent);

		//パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.motion.aModel[nCntModel].mtxWorld);

		for (int nCntMat = 0; nCntMat < (int)g_player.motion.aModel[nCntModel].dwNumMat; nCntMat++)
		{

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_player.motion.aModel[nCntModel].pBuffMat->GetBufferPointer();

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_player.motion.aModel[nCntModel].apTexture[nCntMat]);

			//モデル(パーツ)の描画
			g_player.motion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);

		}

	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
	
}
//============================================
//プレイヤーの取得
//============================================
Player* GetPlayer(void)
{
	return &g_player;
}
//============================================
//プレイヤーの状態取得
//============================================
PLAYERSTATE GetPlayerState(void)
{
	return g_player.state;
}
