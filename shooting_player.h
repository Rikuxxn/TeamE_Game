//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#ifndef _SHOOTINGPLAYER_H_//���̃}�N����`������ĂȂ�������
#define _SHOOTINGPLAYER_H_//�Q�d�C���N���[�h�h�~�̃}�N����`

#define HABA (25.0f)		//��
#define TAKASA (50.0f)		//����
#define BULLETINTERVAL (10)	//���ˊԊu
#define BULLETCOOL (20)		//�N�[���^�C��
#define BULLETMAX (3)		//1�x�̎ˌ���

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//�o����ԁi�_�Łj
	PLAYERSTATE_NORMAL,		//�ʏ�
	PLAYERSTATE_DAMAGE,		//�_���[�W
	PLAYERSTATE_DEATH,		//���b
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�v���C���[�̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	PLAYERSTATE state;	//���
	int nCounterState;	//��ԊǗ��J�E���^�[
	bool bDisp;			//�\��
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 Bullet; //�e�̑���
	float Length;		//�Ίp���̒���
	float Angle;		//�Ίp���̊p�x
	bool bUse;			//�g���Ă��邩
	bool bHit;			//������͂�Ă�
	int nCntAnimState;	//��Ԃ��J�E���g
	int nLife;			//��
	int nBulletType;	//�e�̐؂�ւ�
	int nBulletCnt;		//�e�J�E���g
	int nBulletCool;	//�N�[���^�C��
	int nBulletMax;		//1�x�̔��ː�
}ShootingPlayer;

//�v���g
void InitBackGround(void);
void UninitBackGround(void);
void UpdateBackGround(void);
void DrawBackGround(void);
void InitShootingPlayer(void);
void UninitShootingPlayer(void);
void UpdateShootingPlayer(void);
void DrawShootingPlayer(void);
ShootingPlayer* GetShootingPlayer(void);
void HitShootingPlayer(int nDamage);				 //������͂�Ă�

#endif