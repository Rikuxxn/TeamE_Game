//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#ifndef _PLAYER_H_//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_//�Q�d�C���N���[�h�h�~�̃}�N����`

#define HABA (25.0f)//�v���C���[��
#define TAKASA (60.0f)//�v���C���[����
#define F_JAMP1ST (-19.0f)//�W�����v1
#define F_JAMP2ND (-10.0f)//�W�����v2
#define MAX_SPEED_L (-7.0f)//�ő���
#define MAX_SPEED_R (7.0f)//�ő��E

#include "action_block.h"

//�v���C���[�̏��2024/08/26
typedef enum
{
	PLAYERSTATE_APPEAR = 0, //�o����ԁi�_�Łj
	PLAYERSTATE_NORMAL,		//�ʏ�
	PLAYERSTATE_DAMAGE,		//�_���[�W
	PLAYERSTATE_DEATH,		//���b
	PLAYERSTATE_MUTEKI,		//���G���
	PLAYERSTATE_MAX
}ACTIONPLAYERSTATE;

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;                        //���݂̈ʒu
	D3DXVECTOR3 posOld;						//�O��̈ʒu
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 move;						//�ړ���
	ACTIONBLOCK* pBlock;					//�u���b�N�ւ̃|�C���^
	ACTIONPLAYERSTATE state;				//�v���C���[�̏��
	int nCounterState;						//��ԊǗ��J�E���^�[
	int nGuardCnt;							//�K�[�h�J�E���^�[
	int nCntAnimState;						//��Ԃ��J�E���g
	int nLife;								//��
	float Length;							//�Ίp���̒���
	float Angle;							//�Ίp���̊p�x
	bool bUse;								//�g���Ă��邩
	bool bHit;								//������͂�Ă�
	bool bJamp1st;							//�W�����v�̎g�p1�x��
	bool bRightMove;						//����	true=�E����	false=������
	bool bStop;								//�~�܂��Ă��邩
	bool bDisp;								//�\�����邩���Ȃ���
	bool bGetItem;							//�A�C�e���擾�p�̃t���O
	bool bBlockUse;							//�u���b�N�����蔻��p
	bool bLanding;							//�n�ʂɂ��Ă��邩
}ActionPlayer;

//�v���g
void InitActionPlayer(void);
void UninitActionPlayer(void);
void UpdateActionPlayer(void);
void DrawActionPlayer(void);
ActionPlayer* GetActionPlayer(void);
D3DXVECTOR3 GetActionPos(void);
#endif