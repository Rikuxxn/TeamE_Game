//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------
#ifndef _CRANEPLAYER_H_//���̃}�N����`������ĂȂ�������
#define _CRANEPLAYER_H_//�Q�d�C���N���[�h�h�~�̃}�N����`

#define WIDTH (50.0f)		// �v���C���[��
#define HEIGHT (100.0f)		// �v���C���[����
#define DOWN (3.0f)			// �~��鑬��
#define UP (-3.0f)			// ��鑬��
#define MAX_SPEED_L (-3.0f)	// �ő���
#define MAX_SPEED_R (3.0f)	// �ő��E

#include "crane_block.h"

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0, // �o����ԁi�_�Łj
	PLAYERSTATE_NORMAL,		// �ʏ�
	PLAYERSTATE_DAMAGE,		// �_���[�W
	PLAYERSTATE_DEATH,		// ���b
	PLAYERSTATE_MUTEKI,		// ���G���
	PLAYERSTATE_MAX
}CRANEPLAYERSTATE;

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;        // ���݂̈ʒu
	D3DXVECTOR3 posOld;		// �O��̈ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 move;		// �ړ���
	CRANEBLOCK* pBlock;		// �u���b�N�ւ̃|�C���^
	CRANEPLAYERSTATE state;	// �v���C���[�̏��
	int nCounterState;		// ��ԊǗ��J�E���^�[
	int nCntAnimState;		// ��Ԃ��J�E���g
	float Length;			// �Ίp���̒���
	float Angle;			// �Ίp���̊p�x
	bool bUse;				// �g���Ă��邩
	bool bMove;				// �����邩
	bool bUpSound;			// ��ɏオ���Ă��邩
	bool bLeft;				// ���ɐi�ނ�
	bool bDown;				// �����Ă��邩
	bool bLanding;			// ���n���Ă��邩
	bool bGetItem;			// �A�C�e���擾
	bool bFall;				// �A�C�e���������Ă��邩
}CranePlayer;

//�v���g
void InitCranePlayer(void);
void UninitCranePlayer(void);
void UpdateCranePlayer(void);
void DrawCranePlayer(void);
CranePlayer* GetCranePlayer(void);
D3DXVECTOR3 GetCranePos(void);
#endif