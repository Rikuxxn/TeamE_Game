//=======================================
//
// カメラ処理 [camera.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "fade.h"
#include "block.h"
#include "enemy.h"

//グローバル変数
Camera g_camera;//カメラ情報
CAMERAMODE g_cameramode = CAMERAMODE_NORMAL;//現在のカメラモード

bool bFirstPerson;

//=============================
//カメラの初期化処理
//=============================
void InitCamera(void)
{
	MODE pMode = GetMode();

	//視点・注視点・上方向を設定する
	g_camera.posV = D3DXVECTOR3(0.0f, 80.0f, -20.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//固定でいい
	g_camera.rot = D3DXVECTOR3(0.0f, -1.57f, 0.0f);
	g_camera.fDistance = sqrtf(((g_camera.posV.x - g_camera.posR.x) * (g_camera.posV.x - g_camera.posR.x)) + ((g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y)) + ((g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z)));
	bFirstPerson = false;

	//// ビューポート構成の保存
	//g_camera.viewport.X = 0.0f;				//X開始位置
	//g_camera.viewport.Y = 0.0f;				//Y開始位置
	//g_camera.viewport.Width = 1280.0f;		//幅
	//g_camera.viewport.Height = 720.0f;		//高さ
	//g_camera.viewport.MinZ = 0.0f;
	//g_camera.viewport.MaxZ = 1.0f;

}
//=============================
//カメラの終了処理
//=============================
void UninitCamera(void)
{


}
//=============================
//カメラの更新処理
//=============================
void UpdateCamera(void)
{
	MODE pMode = GetMode();
	FADE g_fade = GetFade(); // 現在の状態
	Player* pPlayer = GetPlayer();
	Block* pBlock = GetBlock();
	Flags* pFlag = GetFlag();
	Enemy* pEnemy = GetEnemy();
	bool bEndMotion = GetEndMotion();

	float fAngleA = sqrtf(((g_camera.posR.x - pPlayer->pos.x) * (g_camera.posR.x - pPlayer->pos.x)) + ((g_camera.posR.y - pPlayer->pos.y) * (g_camera.posR.y - pPlayer->pos.y)) + ((g_camera.posR.z - pPlayer->pos.z) * (g_camera.posR.z - pPlayer->pos.z)));

	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	if (pMode == MODE_GAME && pFlag->bExit == false && bEndMotion == false)
	{
		// マウスの状態を取得
		DIMOUSESTATE mouseState;

		// ゲームパッド右スティックカメラ操作
		if (pStick != NULL) 
		{
			// 右スティックの値を取得
			float stickX = pStick->Gamepad.sThumbRX;
			float stickY = pStick->Gamepad.sThumbRY;

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
			stickX /= 32768.0f;
			stickY /= 32768.0f;

			// カメラ回転の更新
			RotateCameraWithGamepad(stickX, stickY);
		}
		if (GetMouseState(&mouseState))
		{
			// 前フレームのカーソル位置を記録する静的変数
			static POINT prevCursorPos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };

			// 現在のカーソル位置を取得
			POINT cursorPos;
			GetCursorPos(&cursorPos);

			// 移動量を計算
			float deltaX = (float)(cursorPos.x - prevCursorPos.x);
			float deltaY = (float)(cursorPos.y - prevCursorPos.y);

			// マウス感度を適用
			const float mouseSensitivity = 0.0009f;
			deltaX *= mouseSensitivity;
			deltaY *= mouseSensitivity;

			// カメラ回転を更新
			g_camera.rot.y += deltaX; // 水平回転
			g_camera.rot.x += deltaY; // 垂直回転

			// 垂直回転の制限
			if (g_camera.rot.x > 1.40f)
			{
				g_camera.rot.x = 1.40f;
			}
			else if (g_camera.rot.x < -1.40f)
			{
				g_camera.rot.x = -1.40f;
			}

			// 水平回転を正規化
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2.0f;
			}
			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2.0f;
			}

			// カーソルを画面中央に戻す
			SetCursorPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

			// 現在のカーソル位置を次回の計算用に保存
			prevCursorPos.x = SCREEN_WIDTH * 0.5f;
			prevCursorPos.y = SCREEN_HEIGHT * 0.5f;
		}

		// カメラの位置をプレイヤーの位置に設定
		g_camera.posV = pPlayer->pos;
		g_camera.posV.y += 75.0f; // 頭部の高さ

		// カメラの回転に基づいて注視点を計算
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * cosf(g_camera.rot.x);
		g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x);
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * cosf(g_camera.rot.x);

	}

	// 滑らかに補間するための補間係数
	const float smoothFactor = 0.005f;

	// 敵に捕まった
	if (pMode == MODE_GAME && pFlag->bExit == false && bEndMotion == true)
	{
		Enemy* pEnemy = GetEnemy();

		// カメラの位置（プレイヤーの視点を少し高く）
		g_camera.posV = pPlayer->pos;
		g_camera.posV.y += 50.0f;  //  ここを調整
		//g_camera.posV.x -= 50.0f;  //  

		// 敵の位置を注視点の目標値にする
		D3DXVECTOR3 targetPosR = pEnemy->pos;
		targetPosR.y += 100.0f;  // ここを調整

		// 敵の方向ベクトルを計算
		D3DXVECTOR3 direction = targetPosR - g_camera.posV;
		D3DXVec3Normalize(&direction, &direction);

		// 目標回転角度を計算
		float targetRotY = atan2f(direction.x, direction.z);
		float targetRotX = -atan2f(direction.y, sqrtf(direction.x * direction.x + direction.z * direction.z));

		// 現在の回転と目標回転を補間
		g_camera.rot.y += (targetRotY - g_camera.rot.y) * smoothFactor;
		g_camera.rot.x += (targetRotX - g_camera.rot.x) * smoothFactor;

		// 注視点を滑らかに補間
		g_camera.posR.x += (targetPosR.x - g_camera.posR.x) * smoothFactor;
		g_camera.posR.y += (targetPosR.y - g_camera.posR.y) * smoothFactor;
		g_camera.posR.z += (targetPosR.z - g_camera.posR.z) * smoothFactor;
	}

	if (pMode == MODE_TITLE)
	{
		// カメラの位置をプレイヤーの位置に設定
		g_camera.posV = pPlayer->pos;
		g_camera.posV.y += 70.0f; // 頭部の高さ

		// カメラの回転に基づいて注視点を計算
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * cosf(g_camera.rot.x);
		g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x);
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * cosf(g_camera.rot.x);
	}

	
	// エディターモードでのカメラ操作
	if (pMode == MODE_EDIT)
	{
		// マウスの状態を取得
		DIMOUSESTATE mouseState;

		if (GetMouseState(&mouseState))
		{
			// 現在のカーソル位置を取得
			POINT cursorPos;
			GetCursorPos(&cursorPos);

			// 移動量を計算
			static POINT prevCursorPos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			float deltaX = (float)(cursorPos.x - prevCursorPos.x);
			float deltaY = (float)(cursorPos.y - prevCursorPos.y);

			// マウス感度
			const float mouseSensitivity = 0.002f;
			deltaX *= mouseSensitivity;
			deltaY *= mouseSensitivity;

			// カメラの回転を更新
			g_camera.rot.y += deltaX; // 水平回転
			g_camera.rot.x += deltaY; // 垂直回転

			// 垂直回転の制限
			if (g_camera.rot.x > 1.40f)
			{
				g_camera.rot.x = 1.40f;
			}
			else if (g_camera.rot.x < -1.40f)
			{
				g_camera.rot.x = -1.40f;
			}

			// 水平回転を正規化
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2.0f;
			}
			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2.0f;
			}

			// カーソルを画面中央に戻す
			SetCursorPos((int)SCREEN_WIDTH / 2, (int)SCREEN_HEIGHT / 2);
		}

		// WASDキーによるカメラの移動
		const float cameraSpeed = 5.0f; // 移動速度
		D3DXVECTOR3 forward, right;

		// カメラの前方向を計算
		forward.x = -sinf(g_camera.rot.y);
		forward.z = -cosf(g_camera.rot.y);
		forward.y = 0.0f;

		D3DXVec3Normalize(&forward, &forward);

		// カメラの右方向を計算
		right.x = forward.z;
		right.z = -forward.x;
		right.y = 0.0f;

		if (GetKeyboardPress(DIK_W))
		{
			g_camera.posV += forward * cameraSpeed;
		}
		if (GetKeyboardPress(DIK_S))
		{
			g_camera.posV -= forward * cameraSpeed;
		}
		if (GetKeyboardPress(DIK_A))
		{
			g_camera.posV -= right * cameraSpeed;
		}
		if (GetKeyboardPress(DIK_D))
		{
			g_camera.posV += right * cameraSpeed;
		}
		if (GetKeyboardPress(DIK_Z))
		{
			g_camera.posV.y += cameraSpeed; // 上昇
		}
		if (GetKeyboardPress(DIK_C))
		{
			g_camera.posV.y -= cameraSpeed; // 下降
		}

		// 注視点の更新
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * cosf(g_camera.rot.x);
		g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x);
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * cosf(g_camera.rot.x);
	}

}
//=============================
//カメラの設定処理
//=============================
void SetCamera(void)
{
	MODE pMode = GetMode();

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	if (pMode == MODE_GAME)
	{
		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
			D3DXToRadian(60.0f),						// 視野角
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, // アスペクト比
			1.0f,										// 近クリップ面
			2500.0f);									// 遠クリップ面
	}
	else
	{
		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
			D3DXToRadian(45.0f),						// 視野角
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, // アスペクト比
			1.0f,										// 近クリップ面
			2500.0f);									// 遠クリップ面
	}

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

}
//=============================
//ゲームパッドのカメラ回転処理
//=============================
void RotateCameraWithGamepad(float stickX, float stickY)
{
	const float rotationSpeed = 0.07f; // 回転速度

	 // 水平方向の回転（Y軸）
	g_camera.rot.y += stickX * rotationSpeed;

	// 垂直方向の回転（X軸）
	g_camera.rot.x -= stickY * rotationSpeed;

	// 垂直方向の回転を制限 (-90度 〜 90度)
	if (g_camera.rot.x > D3DX_PI / 2) 
	{
		g_camera.rot.x = D3DX_PI / 2;
	}
	if (g_camera.rot.x < -D3DX_PI / 2) 
	{
		g_camera.rot.x = -D3DX_PI / 2;
	}

	// 水平方向の回転を正規化 (-π 〜 π)
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}

}
//=================================
//カメラ情報の取得
//=================================
Camera* GetCamera(void)
{
	return &g_camera;
}
//=============================================
//カメラモードの取得
//=============================================
CAMERAMODE* GetCameraMode(void)
{
	return &g_cameramode;
}
bool GetFirstPerson(void)
{
	return bFirstPerson;
}
