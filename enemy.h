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

#define NUM_PATROL_POINTS (62)  // ����|�C���g�̍ő吔
#define MAX_CONNECTIONS (3) // ����̐�
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

// A*�̃m�[�h�\����
typedef struct Node 
{
    int x, y;           // �O���b�h���W
    float g, h, f;      // �R�X�g�l
    struct Node* parent;// �o�H�����p�̐e�m�[�h
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
Enemy* GetEnemy(void);

bool isPlayerInSight(void);
bool GetEnd(void);
bool GetEndMotion(void);
bool GetInside(void);

#endif