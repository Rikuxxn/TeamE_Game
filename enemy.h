//=======================================
//
//�G�̏���[enemy.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _ENEMY_H_//���̃}�N����`������Ă��Ȃ�������
#define _ENEMY_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "model.h"
#include "motion.h"

typedef enum 
{
    ENEMYSTATE_PATROLLING,     // ����
    ENEMYSTATE_CHASING,        // �ǐՒ�
    ENEMYSTATE_SEARCHING,      // �{����:�ǐՂ𓦂��ꂽ��
    ENEMYSTATE_IDLE,           // �ҋ@��:�������~
    ENEMYSTATE_MAX
} EnemyState;

typedef struct 
{
    D3DXVECTOR3 pos;                            // �G�̈ʒu
    D3DXVECTOR3 posOld;						    // �O�̈ʒu
    D3DXVECTOR3 rot;						    
    D3DXVECTOR3 direction;                      // �G�̌���
    float sightRange;                           // ���E�͈̔�
    float sightAngle;                           // ���E�̊p�x
    EnemyState state;                           // ���݂̏��
    Motion motion;
    D3DXMATRIX mtxWorld;
    D3DXVECTOR3 size;						    // �T�C�Y
    D3DXVECTOR3 vtxMin;						    // �T�C�Y
    D3DXVECTOR3 vtxMax;						    // �T�C�Y
    D3DXVECTOR3 move;						    // �ړ���
    D3DXVECTOR3 RadiusEnemy, posRadiusEnemy;
    bool bUse;
    int nIdxExcla;
}Enemy;


//�v���g�^�C�v�錾
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