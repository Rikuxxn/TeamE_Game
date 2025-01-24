#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//弾の種類
typedef enum
{
	BULLETTYPE_PLAYER=0,//プレイヤーの弾
	BULLETTYPE_ENEMY,//敵の弾
	BULLETTYPE_MAX
}BULLETTYPE;

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	D3DXVECTOR3 rot;//角度
	int nLife;//寿命
	BULLETTYPE type;//種類
	bool bUse;//使用しているかどうか
	float fAngle;//
	float fLength;//
	int nBulletType;//弾の種類
}Bullet;


//プロト
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
BULLETTYPE *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move ,BULLETTYPE type,int nLife,int nBulletType);//, D3DXVECTOR3 rot, float fLength);//発射位置と移動量
#endif