//=======================================
//
// 敵の処理 [enemy.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _ENEMY_H_//このマクロ定義がされていなかったら
#define _ENEMY_H_//2重インクルード防止のマクロ定義

#include "main.h"
#include "model.h"
#include "motion.h"
#include "meshfield.h"

#define NUM_PATROL_POINTS (64)  // 巡回ポイントの最大数
#define MAX_CONNECTIONS (3) // 分岐の数

#define CELL_SIZE (50) // グリッド1マスの大きさ
#define GRID_WIDTH  (MAX_WIDTH / CELL_SIZE)  // 48マス
#define GRID_HEIGHT (MAX_HEIGHT / CELL_SIZE) // 40マス

typedef enum 
{
    ENEMYSTATE_PATROLLING,     // 巡回中
    ENEMYSTATE_CHASING,        // 追跡中
    ENEMYSTATE_SEARCHING,      // 捜索中:追跡を逃された後
    ENEMYSTATE_MAX
} EnemyState;

typedef struct 
{
    D3DXVECTOR3 pos;                            // 敵の位置
    D3DXVECTOR3 posOld;						    // 前の位置
    D3DXVECTOR3 rot;						    // 敵の向き
    float sightRange;                           // 視界の範囲
    float sightAngle;                           // 視界の角度
    EnemyState state;                           // 現在の状態
    EnemyMotion enemymotion;                    // 敵のモーション情報
    D3DXMATRIX mtxWorld;                        // ワールドマトリックス
    D3DXVECTOR3 size;						    // サイズ
    D3DXVECTOR3 vtxMin;						    // サイズ
    D3DXVECTOR3 vtxMax;						    // サイズ
    D3DXVECTOR3 move;						    // 移動量
    D3DXVECTOR3 RadiusEnemy, posRadiusEnemy;
    bool bUse;
    bool bCaughtSound;
    int nEndCnt;
}Enemy;

// ノード構造体
typedef struct Node 
{
    int x, y;
    float g, h; // g: 開始地点からのコスト, h: ヒューリスティック(推定ゴールコスト)
    struct Node* parent;
} Node;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos);
int GetNearestPatrolPoint(D3DXVECTOR3 currentPos);
void Patrol(void);
void Chase(void);
void Search(void);
float NormalizeAngle(float angle);

void LoadMapInfo(const char* filename);

Enemy* GetEnemy(void);

bool isPlayerInSight(void);
bool GetEnd(void);
bool GetEndMotion(void);
bool GetInside(void);

#endif