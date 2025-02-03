//=======================================
//
//���[�V�����ǂݍ��ݏ���[motion.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MOTION_H_//���̃}�N����`������Ă��Ȃ�������
#define _MOTION_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_WORD (1024)//�ő啶����

#define MAX_ENEMY_PARTS (16)						// �G�̃p�[�c��
#define MAX_PARTS (15)								// �v���C���[�p�[�c��

#define MAX_KEY (30)								// �L�[�̍ő吔

#define MOTIONPATH_1 ("data/motion.txt")
#define MOTIONPATH_2 ("data/enemymotion.txt")

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	// �v���C���[:�ҋ@
	MOTIONTYPE_MOVE,		// �v���C���[:�ړ�
	MOTIONTYPE_ACTION,		// �v���C���[:�A�N�V����

	MOTIONTYPE_MAX
}MOTIONTYPE;

//���[�V�����̎��
typedef enum
{
	ENEMYMOTIONTYPE_NEUTRAL = 0,	// �v���C���[:�ҋ@ / �G:�ʏ�ړ�
	ENEMYMOTIONTYPE_MOVE,		// �v���C���[:�ړ� / �G:�ǐ�
	ENEMYMOTIONTYPE_ACTION,		// �v���C���[:�A�N�V���� / �G:�U��
	ENEMYMOTIONTYPE_SEARCH,		// �G:���G

	ENEMYMOTIONTYPE_MAX
}ENEMYMOTIONTYPE;

//�L�[�\����
typedef struct
{
	float fPosX;					//�ʒu(X)
	float fPosY;					//�ʒu(Y)
	float fPosZ;					//�ʒu(Z)

	float fRotX;					//����(X)
	float fRotY;					//����(Y)
	float fRotZ;					//����(Z)
}KEY;

//�G�̃L�[�\����
typedef struct
{
	float fPosX;					//�ʒu(X)
	float fPosY;					//�ʒu(Y)
	float fPosZ;					//�ʒu(Z)

	float fRotX;					//����(X)
	float fRotY;					//����(Y)
	float fRotZ;					//����(Z)
}ENEMYKEY;

//�L�[���\����
typedef struct
{
	int nFrame;						//�Đ��t���[��
	KEY aKey[MAX_PARTS];			//�e�p�[�c�̃L�[�v�f

}KEY_INFO;

//�L�[���\����
typedef struct
{
	int nFrame;							//�Đ��t���[��
	KEY aKey[MAX_ENEMY_PARTS];			//�e�p�[�c�̃L�[�v�f

}ENEMYKEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;						//���[�v���邩�ǂ���
	int nNumKey;					//�L�[�̑���
	KEY_INFO aKeyInfo[MAX_KEY];		//�L�[���
	int startKey, startFrame;
}MOTION_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;						//���[�v���邩�ǂ���
	int nNumKey;					//�L�[�̑���
	ENEMYKEY_INFO aEnemyKeyInfo[MAX_KEY];		//�L�[���
	int startKey, startFrame;
}ENEMYMOTION_INFO;

typedef struct
{
	Model aModel[MAX_PARTS];				//���f��(�p�[�c)
	int nNumModel;							//���f��(�p�[�c)�̑���
	MOTION_INFO aMotionInfo[MOTIONTYPE_MAX];//���[�V�������
	MOTIONTYPE motionType;					//���[�V�����̎��
	int nNumMotion;							//���[�V��������
	bool bLoopMotion;						//���[�v���邩�ǂ���
	int nNumKey;							//�L�[�̑���
	int nKey;								//���݂̃L�[No.
	int nCounterMotion;						//���[�V�����̃J�E���^�[
	MOTIONTYPE pMotion;
}Motion;

typedef struct
{
	Model aModel[MAX_ENEMY_PARTS];				//���f��(�p�[�c)
	int nNumModel;							//���f��(�p�[�c)�̑���
	ENEMYMOTION_INFO aEnemyMotionInfo[ENEMYMOTIONTYPE_MAX];//���[�V�������
	ENEMYMOTIONTYPE EnemymotionType;					//���[�V�����̎��
	int nNumMotion;							//���[�V��������
	bool bLoopMotion;						//���[�v���邩�ǂ���
	int nNumKey;							//�L�[�̑���
	int nKey;								//���݂̃L�[No.
	int nCounterMotion;						//���[�V�����̃J�E���^�[
	ENEMYMOTIONTYPE pMotionEnemy;
}EnemyMotion;

//�v���g�^�C�v�錾
void LoadPlayerTEXT(void);
void LoadEnemyTEXT(void);

#endif
