//=======================================
//
// カメラ処理[camera.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _CAMERA_H_//このマクロ定義がされていなかったら
#define _CAMERA_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_CAMERA (2)			// カメラの個数

//カメラモードの種類
typedef enum
{
	CAMERAMODE_NORMAL = 0,		// ノーマルカメラ
	CAMERAMODE_AUTO,			// カメラ追従
	CAMERAMODE_AUTOTURN,		// 視点自動回転
	CAMERAMODE_FIRSTPERSON,		// 一人称モード
	CAMERAMODE_MAX
}CAMERAMODE;

//カメラ構造体
typedef struct
{
	D3DXVECTOR3 posV;			// 視点
	D3DXVECTOR3 posVDest;		// 目的の視点
	D3DXVECTOR3 posR;			// 注視点
	D3DXVECTOR3 posRDest;		// 目的の注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX mtxView;			// ビューマトリックス
	D3DXVECTOR3 rot;			// 向き
	float fDistance;			// 視点から注視点の距離
	D3DVIEWPORT9 viewport;		// ビューポート
}Camera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
void RotateCameraWithGamepad(float stickX, float stickY);
Camera* GetCamera(void);
CAMERAMODE* GetCameraMode(void);
bool GetFirstPerson(void);

#endif

