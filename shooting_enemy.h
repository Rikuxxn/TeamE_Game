#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//maku
#define MAX_ENEMY (128)//tekimax
#define ENEMY_WIDTH (15.0f)//tekimax
#define ENEMY_HEIGHT (15.0f)//tekimax


//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,//通常
	ENEMYSTATE_DAMAGE,//ダメージ
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

//kouzou
typedef struct
{
	D3DXVECTOR3 pos;//iti
	D3DXVECTOR3 move;//ugoki
	int nType;//syurui
	ENEMYSTATE state;//joutai
	int nCounterState;//joutaicounter
	int nLife;//tairyoku
	bool bUse;//siyou
	int BulletCounter;//弾カウンター
	int MoveCnt;//ugokikaunnto
}Enemy;


//puroto
void InitShootingEnemy(void);
void UninitShootingEnemy(void);
void UpdateShootingEnemy(void);
void DrawShootingEnemy(void);
void SetEnemy(D3DXVECTOR3 pos,D3DXVECTOR3 move, int nType);
Enemy *GetShootingEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
int GetNumEnemy();

#endif // !_ENEMY_H_