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

#define MAX_PARTS (15)						// �p�[�c��
#define MAX_KEY (20)						// �L�[�̍ő吔
#define MAX_MOTION (3)						// ���[�V�����̍ő吔

#define MOTIONPATH_1 ("data/motion.txt")
#define MOTIONPATH_2 ("data/enemymotion.txt")

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	//�ҋ@
	MOTIONTYPE_MOVE,		//�ړ�
	MOTIONTYPE_ACTION,		//�A�N�V����
	MOTIONTYPE_JUMP,		//�W�����v
	MOTIONTYPE_NEUTRAL2,	//�ҋ@2(�G�p)
	MOTIONTYPE_MAX
}MOTIONTYPE;

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

//�L�[���\����
typedef struct
{
	int nFrame;						//�Đ��t���[��
	KEY aKey[MAX_PARTS];			//�e�p�[�c�̃L�[�v�f

}KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;						//���[�v���邩�ǂ���
	int nNumKey;					//�L�[�̑���
	KEY_INFO aKeyInfo[MAX_KEY];		//�L�[���
	int startKey, startFrame;
}MOTION_INFO;

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

//�v���g�^�C�v�錾
void LoadPlayerTEXT(void);
void LoadEnemyTEXT(void);

#endif
