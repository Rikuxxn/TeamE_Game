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

#define NUM_PATROL_POINTS (64)  // ����|�C���g�̍ő吔
#define MAX_CONNECTIONS (3) // ����̐�

#define CELL_SIZE (50) // �O���b�h1�}�X�̑傫��
#define GRID_WIDTH  (MAX_WIDTH / CELL_SIZE)  // 48�}�X
#define GRID_HEIGHT (MAX_HEIGHT / CELL_SIZE) // 40�}�X

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

// �m�[�h�\����
typedef struct Node 
{
    int x, y;
    float g, h; // g: �J�n�n�_����̃R�X�g, h: �q���[���X�e�B�b�N(����S�[���R�X�g)
    struct Node* parent;
} Node;

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

Enemy* GetEnemy(void);

bool isPlayerInSight(void);
bool GetEnd(void);
bool GetEndMotion(void);
bool GetInside(void);

#endif