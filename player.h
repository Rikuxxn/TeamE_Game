//=======================================
//
//�v���C���[����[player.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _PLAYER_H_//���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "model.h"
#include "motion.h"

//�}�N����`
#define PLAYER_SPEED (0.70f)				// �v���C���[�̕����X�s�[�h
#define PLAYER_DUSHSPEED (1.6f)				// �v���C���[�̃_�b�V���X�s�[�h
#define PLAYER_STAMINA (240)				// �v���C���[�̃X�^�~�i

#define MAX_JUMP (40)						// �W�����v��
#define MAX_GRAVITY (0.8)					// �d��
#define PLAYER_LIFE (0)						// �v���C���[�̗̑�

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,					// �o�����(�_��)
	PLAYERSTATE_NORMAL,						// �ʏ���
	PLAYERSTATE_DAMAGE,						// �_���[�W���
	PLAYERSTATE_DEATH,						// ���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;						// �ʒu
	D3DXVECTOR3 posOld;						// �O�̈ʒu
	D3DXVECTOR3 size;						// �T�C�Y
	D3DXVECTOR3 vtxMin;						// �T�C�Y
	D3DXVECTOR3 vtxMax;						// �T�C�Y
	D3DXVECTOR3 move;						// �ړ���
	D3DXVECTOR3 rot;						// ����
	D3DXVECTOR3 rotDestPlayer;				// ����
	PLAYERSTATE state;						// �v���C���[�̏��
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	int nDush;								// �_�b�V���Q�[�W
	int nDrawDush;							// �_�b�V���Q�[�W�`��p
	bool bUse;								// �g���Ă��邩�ǂ���
	bool bDisp;								// �\�����邩���Ȃ���
	bool bDush;								// �_�b�V�����Ă邩
	bool bEmpty;							// �X�^�~�i�؂ꂩ�ǂ���
	bool bDrawDush;							// �_�b�V���Q�[�W�`��p
	Motion motion;							// ���[�V�������
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);

#endif

