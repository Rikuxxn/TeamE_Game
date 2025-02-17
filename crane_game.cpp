//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "crane_game.h"
#include "input.h"
#include "crane_player.h"
#include "crane_fade.h"
#include "crane_effect.h"
#include "crane_particle.h"
#include "crane_block.h"
#include "crane_item.h"
#include "crane_background.h"
#include "time.h"
#include "game.h"
#include "sound.h"
#include "crane_clear.h"
#include "crane_score.h"
#include "password_game.h"

//�O���[�o��
CRANEGAMESTATE g_gameState = CRANEGAMESTATE_NONE;	//�Q�[���̏��
int g_nCounterCraneGameState = 0;					//��ԊǗ��J�E���^�[

void InitCraneGame(void)
{
	//�e��I�u�W�F�N�g�̏���������
	InitCraneBackGround();	//�w�i�̏���������
	InitCraneParticle();	//�p�[�e�B�N���̏�����
	InitCranePlayer();		//�v���C���[�̏���������
	InitCraneBlock();		//�u���b�N�̏���������
	InitCraneEffect();		//�G�t�F�N�g�̏�����
	InitCraneItem();		//�A�C�e���̏�����
	InitCraneClear();		//�N���A��ʂ̏�����

	SetCraneBlock(D3DXVECTOR3(FIELD_LEFT + 100.0f, FIELD_UNDER - 30.0f, 0.0f), D3DXVECTOR3(), 40.0f, 30.0f, 0);	//�u���b�N
	SetCraneItem(D3DXVECTOR3(600.0f, FIELD_UNDER - 15.0f, 0.0f), ITEM_WIDTH + 20.0f, ITEM_HEIGHT + 20.0f, 1);
	SetCraneItem(D3DXVECTOR3(800.0f, FIELD_UNDER - 15.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2);
	//SetCraneItem(D3DXVECTOR3(740.0f, FIELD_UNDER - 15.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3);					//�A�C�e��

	g_gameState = CRANEGAMESTATE_NORMAL;//�ʏ��Ԃɐݒ�
	g_nCounterCraneGameState = 0;

	////�T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_CRANEGAMEBGM);
}
void UninitCraneGame(void)
{
	////�T�E���h�̒�~
	//StopSound(SOUND_LABEL_CRANEGAMEBGM);

	//�e��I�u�W�F�N�g�̏I������
	UninitCraneBackGround();	//�w�i�̏I������
	UninitCraneParticle();		//�p�[�e�B�N���̏I������
	UninitCranePlayer();		//�v���C���[�̏I������
	UninitCraneBlock();			//�u���b�N�̏I������
	UninitCraneEffect();		//�G�t�F�N�g�̏I������
	UninitCraneItem();			//�A�C�e���̏I������
	UninitCraneClear();			//�N���A��ʂ̏I������
}
void UpdateCraneGame(void)
{
	CranePlayer* pPlayer = GetCranePlayer();
	int nNum = GetNumItem();

	//�e��I�u�W�F�N�g�̍X�V����
	UpdateCraneBackGround();	//�w�i�̍X�V����
	UpdateCraneParticle();		//�p�[�e�B�N���̍X�V����
	UpdateCranePlayer();		//�v���C���[�̍X�V����
	UpdateCraneEffect();		//�G�t�F�N�g�̍X�V����
	UpdateCraneItem();			//�A�C�e���̍X�V����

	if (pPlayer->bUse == false || nNum <= 0)//�I������
	{
		//���(���[�h)�̐ݒ�
		g_gameState = CRANEGAMESTATE_END;
	}

	switch (g_gameState)
	{
	case CRANEGAMESTATE_NORMAL://�ʏ���
		break;
	case CRANEGAMESTATE_END://�I�����
		if (g_nCounterCraneGameState <= 45)
		{
			g_nCounterCraneGameState++;
		}

		if (g_nCounterCraneGameState == 45 && nNum == 0 && pPlayer->bUse == true)
		{
			PlaySound(SOUND_LABEL_MINICLEAR);
			//UpdateCraneClear();
		}
		break;
	}
}
void DrawCraneGame(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��
	DrawCraneBackGround();	//�w�i�̕`�揈��
	DrawCraneParticle();	//�p�[�e�B�N���̕`�揈��
	DrawCranePlayer();		//�v���C���[�̕`�揈��
	DrawCraneItem();		//�A�C�e���̕`�揈��
	DrawCraneBlock();		//�u���b�N�̕`�揈��
	DrawCraneEffect();		//�G�t�F�N�g�̕`�揈��

	//if (g_nCounterCraneGameState >= 45)
	//{
	//	DrawCraneClear();
	//}
}
void SetCraneGameState(CRANEGAMESTATE state)
{
	g_gameState = state;
}
CRANEGAMESTATE GetCraneGameState(void)
{
	return g_gameState;
}