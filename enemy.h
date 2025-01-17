//=======================================
//
//敵の処理[enemy.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _ENEMY_H_//このマクロ定義がされていなかったら
#define _ENEMY_H_//2重インクルード防止のマクロ定義

#include "main.h"
#include "model.h"
#include "motion.h"

typedef enum 
{
    ENEMYSTATE_PATROLLING,     // 巡回中
    ENEMYSTATE_CHASING,        // 追跡中
    ENEMYSTATE_SEARCHING,      // 捜索中:追跡を逃された後
    ENEMYSTATE_IDLE,           // 待機中:動きを停止
    ENEMYSTATE_MAX
} EnemyState;

typedef struct 
{
    D3DXVECTOR3 pos;                            // 敵の位置
    D3DXVECTOR3 posOld;						    // 前の位置
    D3DXVECTOR3 rot;						    
    D3DXVECTOR3 direction;                      // 敵の向き
    float sightRange;                           // 視界の範囲
    float sightAngle;                           // 視界の角度
    EnemyState state;                           // 現在の状態
    Motion motion;
    D3DXMATRIX mtxWorld;
    D3DXVECTOR3 size;						    // サイズ
    D3DXVECTOR3 vtxMin;						    // サイズ
    D3DXVECTOR3 vtxMax;						    // サイズ
    D3DXVECTOR3 move;						    // 移動量
    D3DXVECTOR3 RadiusEnemy, posRadiusEnemy;
    bool bUse;
    int nIdxExcla;
}Enemy;


//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos);
int GetNearestPatrolPoint(D3DXVECTOR3 currentPos);
Enemy* GetEnemy(void);

bool isPlayerInSight(void);
bool GetEnd(void);
bool GetInside(void);

#endif