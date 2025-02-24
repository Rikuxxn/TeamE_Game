#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

// �}�N����`
#define MAX_ENEMY (128)		// �ő吔
#define ENEMY_WIDTH (15.0f)	// ��
#define ENEMY_HEIGHT (15.0f)// ����


// �G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	// �ʏ�
	ENEMYSTATE_DAMAGE,		// �_���[�W
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�G�̎��
//typedef enum
//{
//	ENEMYTYPE_1=0,
//	ENEMYTYPE_2,
//	ENEMYTYPE_3,
//	ENEMYTYPE_MAX
//}ENEMYTYPE;

// �G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	int nType;			// ���
	ENEMYSTATE state;	// ���
	int nCounterState;	// ��ԂɂȂ��Ă���b��
	int nLife;			// ��
	bool bUse;			// �g���Ă��邩
	int BulletCounter;	// �e�J�E���^�[
	int MoveCnt;		// �ړ�����b��
}Enemy;


// �v���g�^�C�v�錾
void InitShootingEnemy(void);
void UninitShootingEnemy(void);
void UpdateShootingEnemy(void);
void DrawShootingEnemy(void);
void SetEnemy(D3DXVECTOR3 pos,D3DXVECTOR3 move, int nType);
Enemy *GetShootingEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
int GetNumEnemy();

#endif // !_ENEMY_H_