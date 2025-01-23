//=======================================
//
// カメラ処理[camera.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"

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
	g_camera.posV = D3DXVECTOR3(0.0f, 280.0f, -20.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//固定でいい
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

	Player* pPlayer = GetPlayer();

	float fAngleA = sqrtf(((g_camera.posR.x - pPlayer->pos.x) * (g_camera.posR.x - pPlayer->pos.x)) + ((g_camera.posR.y - pPlayer->pos.y) * (g_camera.posR.y - pPlayer->pos.y)) + ((g_camera.posR.z - pPlayer->pos.z) * (g_camera.posR.z - pPlayer->pos.z)));

	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	if (pMode == MODE_GAME)
	{
		//if (pStick != NULL) 
		//{
		//	// 右スティックの値を取得
		//	float stickX = pStick->Gamepad.sThumbRX;
		//	float stickY = pStick->Gamepad.sThumbRY;

		//	// デッドゾーン処理
		//	const float DEADZONE = 10922.0f;
		//	if (fabsf(stickX) < DEADZONE)
		//	{
		//		stickX = 0.0f;
		//	}
		//	if (fabsf(stickY) < DEADZONE)
		//	{
		//		stickY = 0.0f;
		//	}

		//	// 正規化
		//	stickX /= 32768.0f;
		//	stickY /= 32768.0f;

		//	// カメラ回転の更新
		//	RotateCameraWithGamepad(stickX, stickY);
		//}

		// マウスの状態を取得
		DIMOUSESTATE mouseState;

		if (GetMouseState(&mouseState))
		{
			// 前フレームのカーソル位置を記録する静的変数
			static POINT prevCursorPos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

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
			if (g_camera.rot.x > 0.72f)
			{
				g_camera.rot.x = 0.72f;
			}
			else if (g_camera.rot.x < -0.72f)
			{
				g_camera.rot.x = -0.72f;
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
			SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

			// 現在のカーソル位置を次回の計算用に保存
			prevCursorPos.x = SCREEN_WIDTH / 2;
			prevCursorPos.y = SCREEN_HEIGHT / 2;
		}

		// カメラの位置をプレイヤーの位置に設定
		g_camera.posV = pPlayer->pos;
		g_camera.posV.y += 70.0f; // 頭部の高さ

		// カメラの回転に基づいて注視点を計算
		float lookDistance = 10.0f; // 注視点までの距離
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * lookDistance * cosf(g_camera.rot.x);
		g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x) * lookDistance;
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * lookDistance * cosf(g_camera.rot.x);

	}


	//if (g_cameramode == CAMERAMODE_NORMAL)
	//{
		if (pMode != MODE_EDIT)
		{
			g_camera.posRDest.x = pPlayer->pos.x - sinf(fAngleA) * PLAYER_SPEED;
			g_camera.posRDest.z = pPlayer->pos.z - cosf(fAngleA) * PLAYER_SPEED;

			g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y + D3DX_PI) * g_camera.fDistance;
			g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y + D3DX_PI) * g_camera.fDistance;

			g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.05f;
			g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.05f;

			g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.05f;
			g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.05f;
		}




		////注視点の旋回(X軸)
		//else if (GetKeyboardPress(DIK_T))
		//{

		//	g_camera.rot.x -= 0.02f;

		//	//角度の正規化
		//	if (g_camera.rot.x > D3DX_PI)
		//	{
		//		g_camera.rot.x -= D3DX_PI * 2.0f;
		//	}

		//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		//	g_camera.posR.y = g_camera.posV.y + cosf(g_camera.rot.x) * g_camera.fDistance;
		//	g_camera.posR.z = g_camera.posV.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

		//}
		//else if (GetKeyboardPress(DIK_G))
		//{

		//	g_camera.rot.x += 0.02f;

		//	//角度の正規化
		//	if (g_camera.rot.x < -D3DX_PI)
		//	{
		//		g_camera.rot.x += D3DX_PI * 2.0f;
		//	}

		//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		//	g_camera.posR.y = g_camera.posV.y + cosf(g_camera.rot.x) * g_camera.fDistance;
		//	g_camera.posR.z = g_camera.posV.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

		//}

		////視点の旋回(X軸)
		//else if (GetKeyboardPress(DIK_UP))
		//{

		//	//角度の正規化
		//	if (g_camera.rot.x < -D3DX_PI)
		//	{
		//		g_camera.rot.x += D3DX_PI * 2.0f;
		//	}
		//	else if (g_camera.rot.x > D3DX_PI)
		//	{
		//		g_camera.rot.x -= D3DX_PI * 2.0f;
		//	}

		//	if (g_camera.rot.x <= 3.0f)
		//	{

		//		g_camera.rot.x += 0.01f;

		//		g_camera.posV.x = g_camera.posR.z - sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		//		g_camera.posV.y = g_camera.posR.y - cosf(g_camera.rot.x) * g_camera.fDistance;
		//		g_camera.posV.z = g_camera.posR.x - sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

		//	}

		//}
		//else if (GetKeyboardPress(DIK_DOWN))
		//{

		//	//角度の正規化
		//	if (g_camera.rot.x < -D3DX_PI)
		//	{
		//		g_camera.rot.x += D3DX_PI * 2.0f;
		//	}
		//	else if (g_camera.rot.x > D3DX_PI)
		//	{
		//		g_camera.rot.x -= D3DX_PI * 2.0f;
		//	}

		//	if (g_camera.rot.x > D3DX_PI * 0.5f)
		//	{

		//		g_camera.rot.x -= 0.01f;

		//		g_camera.posV.x = g_camera.posR.z - sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		//		g_camera.posV.y = g_camera.posR.y - cosf(g_camera.rot.x) * g_camera.fDistance;
		//		g_camera.posV.z = g_camera.posR.x - sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

		//	}

		//}
	//}
	// 
	
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
			static POINT prevCursorPos = { SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.5 };
			float deltaX = (float)(cursorPos.x - prevCursorPos.x);
			float deltaY = (float)(cursorPos.y - prevCursorPos.y);

			// マウス感度
			const float mouseSensitivity = 0.002f;
			deltaX *= mouseSensitivity;
			deltaY *= mouseSensitivity;

			// カメラの回転を更新
			g_camera.rot.y += deltaX; // 水平回転
			g_camera.rot.x += deltaY; // 垂直回転

			// 垂直回転の制限 (-π/2 ～ π/2)
			if (g_camera.rot.x > D3DX_PI / 2)
			{
				g_camera.rot.x = D3DX_PI / 2;
			}
			else if (g_camera.rot.x < -D3DX_PI / 2)
			{
				g_camera.rot.x = -D3DX_PI / 2;
			}

			// カーソルを画面中央に戻す
			SetCursorPos(SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.5);
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
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y);
		g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x);
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y);
	}

	//if (KeyboardTrigger(DIK_F2) == true)
	//{
	//	if (g_cameramode == CAMERAMODE_NORMAL)
	//	{
	//		g_cameramode = CAMERAMODE_AUTO;
	//	}
	//	else if (g_cameramode == CAMERAMODE_AUTO)
	//	{
	//		g_cameramode = CAMERAMODE_NORMAL;
	//	}
	//}

	//if (KeyboardTrigger(DIK_F3) == true)
	//{
	//	if (g_cameramode == CAMERAMODE_NORMAL || g_cameramode == CAMERAMODE_AUTO)
	//	{
	//		g_cameramode = CAMERAMODE_AUTOTURN;
	//	}
	//	else if (g_cameramode == CAMERAMODE_AUTOTURN)
	//	{
	//		g_cameramode = CAMERAMODE_NORMAL;
	//	}
	//}


	//switch (g_cameramode)
	//{
	//case CAMERAMODE_NORMAL:
	//	break;

	//case CAMERAMODE_AUTO:

	//	//g_camera.posRDest.x = pPlayer->pos.x - sinf(fAngleA) * PLAYER_SPEED;
	//	//g_camera.posRDest.z = pPlayer->pos.z - cosf(fAngleA) * PLAYER_SPEED;

	//	//g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y + D3DX_PI) * g_camera.fDistance;
	//	//g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y + D3DX_PI) * g_camera.fDistance;

	//	//g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.05f;
	//	//g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.05f;

	//	//g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.05f;
	//	//g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.05f;

	//	break;

	//case CAMERAMODE_AUTOTURN:

	//	g_camera.rot.y -= 0.006f;

	//	//角度の正規化
	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y -= D3DX_PI * 2.0f;
	//	}
	//	else if (g_camera.rot.y < -D3DX_PI)
	//	{
	//		g_camera.rot.y += D3DX_PI * 2.0f;
	//	}

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;

	//	break;

	//default:

	//	break;
	//}


}
//=============================
//カメラの設定処理
//=============================
void SetCamera(void)
{

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

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),                  // 視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, // アスペクト比
		1.0f,                                // 近クリップ面
		1100.0f);                            // 遠クリップ面

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

	// 垂直方向の回転を制限 (-90度 ～ 90度)
	if (g_camera.rot.x > D3DX_PI / 2) 
	{
		g_camera.rot.x = D3DX_PI / 2;
	}
	if (g_camera.rot.x < -D3DX_PI / 2) 
	{
		g_camera.rot.x = -D3DX_PI / 2;
	}

	// 水平方向の回転を正規化 (-π ～ π)
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
