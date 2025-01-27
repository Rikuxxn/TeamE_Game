//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "action_game.h"
#include "input.h"
#include "action_player.h"
#include "action_fade.h"
#include "action_effect.h"
#include "action_particle.h"
#include "action_block.h"
#include "action_item.h"
#include "action_background.h"
#include "time.h"
//#include "sound.h"
#include "action_clear.h"

//�O���[�o��
ACTSTATE g_gameState = ACTSTATE_NONE;		//�Q�[���̏��
int g_nCntActionGameState = 0;						//��ԊǗ��J�E���^�[

void InitActionGame(void)
{
	//�e��I�u�W�F�N�g�̏���������
	InitActionBackGround();	//�w�i�̏���������
	InitActionParticle();	//�p�[�e�B�N���̏�����
	InitActionPlayer();		//�v���C���[�̏���������
	InitActionBlock();		//�u���b�N�̏���������
	InitActionEffect();		//�G�t�F�N�g�̏�����
	InitActionItem();		//�A�C�e���̏�����
	InitActionClear();		//�N���A��ʂ̏�����

	SetActionBlock(D3DXVECTOR3(640.0f, 700.0f, 0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), 240.0f, 20.0f, 1);	//�n��
	SetActionBlock(D3DXVECTOR3(640.0f, 300.0f, 0.0f), D3DXVECTOR3(), 20.0f, 20.0f, 0);					//�u���b�N
	SetActionBlock(D3DXVECTOR3(520.0f, 320.0f, 0.0f),D3DXVECTOR3(), 20.0f, 20.0f, 0);
	SetActionBlock(D3DXVECTOR3(740.0f, 200.0f, 0.0f), D3DXVECTOR3(), 20.0f, 20.0f, 0);
	SetActionBlock(D3DXVECTOR3(430.0f, 440.0f, 0.0f),D3DXVECTOR3(), 30.0f, 20.0f, 0);
	SetActionBlock(D3DXVECTOR3(600.0f, 550.0f, 0.0f), D3DXVECTOR3(), 60.0f, 20.0f, 0);
	SetActionItem(D3DXVECTOR3(740.0f, 50.0f, 0.0f), 10.0f, 10.0f, 0);									//�A�C�e��

	g_gameState = ACTSTATE_NORMAL;//�ʏ��Ԃɐݒ�
	g_nCntActionGameState = 0;

	////�T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_GAMEBGM);
}
void UninitActionGame(void)
{
	////�T�E���h�̒�~
	//StopSound(SOUND_LABEL_GAMEBGM);

	//�e��I�u�W�F�N�g�̏I������
	UninitActionBackGround();	//�w�i�̏I������
	UninitActionParticle();		//�p�[�e�B�N���̏I������
	UninitActionPlayer();		//�v���C���[�̏I������
	UninitActionBlock();		//�u���b�N�̏I������
	UninitActionEffect();		//�G�t�F�N�g�̏I������
	UninitActionItem();			//�A�C�e���̏I������
	UninitActionClear();		//�N���A��ʂ̏I������
}
void UpdateActionGame(void)
{
	ActionPlayer* pPlayer = GetActionPlayer();
	bool bItem;
	bItem = GetActionItem();

	//�e��I�u�W�F�N�g�̍X�V����
	UpdateActionBackGround();	//�w�i�̍X�V����
	UpdateActionParticle();		//�p�[�e�B�N���̍X�V����
	UpdateActionPlayer();		//�v���C���[�̍X�V����
	UpdateActionEffect();		//�G�t�F�N�g�̍X�V����
	UpdateActionItem();			//�A�C�e���̍X�V����

	if (pPlayer->bUse == false || bItem == true)//�I������
	{
		//���(���[�h)�̐ݒ�
		g_gameState = ACTSTATE_END;
	}

	switch (g_gameState)
	{
	case ACTSTATE_NORMAL:	//�ʏ���
		break;
	case ACTSTATE_END:		//�I�����
		if (g_nCntActionGameState <= 45)
		{
			g_nCntActionGameState++;
		}

		if (g_nCntActionGameState >= 45 && bItem == true && pPlayer->bUse == true)
		{
			UpdateActionClear();
		}
		break;
	}
}
void DrawActionGame(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��
	DrawActionBackGround();	//�w�i�̕`�揈��
	DrawActionParticle();		//�p�[�e�B�N���̕`�揈��
	DrawActionPlayer();		//�v���C���[�̕`�揈��
	DrawActionBlock();		//�u���b�N�̕`�揈��
	DrawActionEffect();		//�G�t�F�N�g�̕`�揈��
	DrawActionItem();			//�A�C�e���̕`�揈��

	if (g_nCntActionGameState >= 45)
	{
		DrawActionClear();
	}
}
void SetGameState(ACTSTATE state)
{
	g_gameState = state;
}
ACTSTATE GetActionGameState(void)
{
	return g_gameState;
}