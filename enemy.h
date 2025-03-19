//=======================================
//
// �G�̏��� [enemy.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _ENEMY_H_//���̃}�N����`������Ă��Ȃ�������
#define _ENEMY_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "model.h"
#include "motion.h"
#include "meshfield.h"

#define NUM_PATROL_POINTS (64)              // ����|�C���g�̍ő吔
#define MAX_CONNECTIONS (3)                 // ����̐�

#define GRID_SIZE  (40)
#define GRID_X     (MAX_WIDTH / GRID_SIZE)  // 60
#define GRID_Z     (MAX_HEIGHT / GRID_SIZE) // 50
#define MIN_X (-MAX_WIDTH * 0.5f)
#define MIN_Z (-MAX_HEIGHT * 0.5f)
#define MAX_PATH_LENGTH (GRID_X * GRID_Z)
#define MAX_SEARCH_ITERATIONS (1000)  // �T���񐔂̏��
#define MAX_PATH_DISTANCE (20)  // �ő�T�������i20�O���b�h�ȓ��j

typedef enum 
{
    ENEMYSTATE_PATROLLING,     // ����
    ENEMYSTATE_CHASING,        // �ǐՒ�
    ENEMYSTATE_SEARCHING,      // �{����:�ǐՂ𓦂��ꂽ��
    ENEMYSTATE_MAX
} EnemyState;

typedef struct 
{
    D3DXVECTOR3 pos;                            // �G�̈ʒu
    D3DXVECTOR3 posOld;						    // �O�̈ʒu
    D3DXVECTOR3 rot;						    // �G�̌���
    float sightRange;                           // ���E�͈̔�
    float sightAngle;                           // ���E�̊p�x
    EnemyState state;                           // ���݂̏��
    EnemyMotion enemymotion;                    // �G�̃��[�V�������
    D3DXMATRIX mtxWorld;                        // ���[���h�}�g���b�N�X
    D3DXVECTOR3 size;						    // �T�C�Y
    D3DXVECTOR3 vtxMin;						    // �T�C�Y
    D3DXVECTOR3 vtxMax;						    // �T�C�Y
    D3DXVECTOR3 move;						    // �ړ���
    D3DXVECTOR3 RadiusEnemy, posRadiusEnemy;
    bool bUse;
    bool bCaughtSound;
    int nEndCnt;
}Enemy;

typedef struct 
{
    int x, z;
} Node;

typedef struct
{
    int x, z;
    float f, g, h;
    bool open, closed;
    Node parent;
} PathNode;

//�v���g�^�C�v�錾
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
float Heuristic(Node a, Node b);
Node WorldToGrid(D3DXVECTOR3 pos);
D3DXVECTOR3 GridToWorld(Node node);
bool FindPath(Node start, Node goal);
void SortDirectionsGoal(int goalX, int goalZ, int currentX, int currentZ);

Enemy* GetEnemy(void);

bool isPlayerInSight(void);
bool GetEnd(void);
bool GetEndMotion(void);
bool GetInside(void);

#endif