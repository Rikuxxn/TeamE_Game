#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

// マクロ定義
#define MAX_ENEMY (128)		// 最大数
#define ENEMY_WIDTH (15.0f)	// 幅
#define ENEMY_HEIGHT (15.0f)// 高さ


// 敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	// 通常
	ENEMYSTATE_DAMAGE,		// ダメージ
	ENEMYSTATE_MAX
}ENEMYSTATE;

//敵の種類
//typedef enum
//{
//	ENEMYTYPE_1=0,
//	ENEMYTYPE_2,
//	ENEMYTYPE_3,
//	ENEMYTYPE_MAX
//}ENEMYTYPE;

// 敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 move;	// 移動量
	int nType;			// 種類
	ENEMYSTATE state;	// 状態
	int nCounterState;	// 状態になっている秒数
	int nLife;			// 命
	bool bUse;			// 使われているか
	int BulletCounter;	// 弾カウンター
	int MoveCnt;		// 移動する秒数
}Enemy;


// プロトタイプ宣言
void InitShootingEnemy(void);
void UninitShootingEnemy(void);
void UpdateShootingEnemy(void);
void DrawShootingEnemy(void);
void SetEnemy(D3DXVECTOR3 pos,D3DXVECTOR3 move, int nType);
Enemy *GetShootingEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
int GetNumEnemy();

#endif // !_ENEMY_H_