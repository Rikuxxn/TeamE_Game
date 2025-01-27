//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "shooting_game.h"
#include "input.h"
#include "shooting_player.h"
#include "shooting_bullet.h"
#include "shooting_enemy.h"
#include "shooting_effect.h"
#include "shooting_particle.h"
#include "shooting_clear.h"
//#include "sound.h"

//�O���[�o��
STGSTATE g_gameState = STGSTATE_NONE;	 //�Q�[���̏��
int g_nCntShootingGameState = 0;						 //��ԊǗ��J�E���^�[

void InitShootingGame(void)
{
	//�e��I�u�W�F�N�g�̏���������

	InitBackGround();		//�w�i�̏���������
	InitShootingPlayer();	//�v���C���[�̏���������
	InitBullet();			//�e�̏���������
	InitEffect();			//�G�t�F�N�g�̏�����
	InitShootingEnemy();	//�G�̏�����
	InitClear();			//�N���A�\���̏�����
	InitParticle();			//�p�[�e�B�N���̏�����

	SetEnemy(D3DXVECTOR3(470.0f, 200.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(750.0f, 200.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(610.0f, 260.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(610.0f, 360.0f, 0.0f),  D3DXVECTOR3(1.0f, 0.0f, 0.0f),1);

	g_gameState = STGSTATE_NORMAL;//�ʏ��Ԃɐݒ�
	g_nCntShootingGameState = 0;

	////�T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_GAMEBGM);
}
void UninitShootingGame(void)
{
	//StopSound();	//�T�E���h�̒�~

	//�e��I�u�W�F�N�g�̏I������
	UninitBackGround();		//�w�i�̏I������
	UninitShootingPlayer();	//�v���C���[�̏I������
	UninitBullet();			//�e�̏I������
	UninitEffect();			//�G�t�F�N�g�̏I������
	UninitShootingEnemy();	//�G�̏I������
	UninitParticle();		//�p�[�e�B�N���̏I������
	UninitClear();			//�N���A�\���̏I������
}
void UpdateShootingGame(void)
{
	int nNum;
	ShootingPlayer* pPlayer = GetShootingPlayer();
	nNum = GetNumEnemy();

	//�e��I�u�W�F�N�g�̍X�V����
	UpdateBackGround();		//�w�i�̍X�V����
	UpdateParticle();		//�p�[�e�B�N���̍X�V����
	UpdateShootingPlayer();	//�v���C���[�̍X�V����
	UpdateShootingEnemy();	//�G�̍X�V����
	UpdateBullet();			//�e�̍X�V����
	UpdateEffect();			//�G�t�F�N�g�̍X�V����

	if (pPlayer->bUse == false || nNum <= 0)
	{
		//���(���[�h)�̐ݒ�
		g_gameState = STGSTATE_END;
	}
	switch (g_gameState)
	{
	case STGSTATE_NORMAL://�ʏ���
		break;
	case STGSTATE_END://�I�����
		if (g_nCntShootingGameState <= 90)
		{
			g_nCntShootingGameState++;
		}

		if (g_nCntShootingGameState >= 90 && nNum <= 0 && pPlayer->bUse == true)
		{
			UpdateClear();
		}
		break;
	}
}
void DrawShootingGame(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��
	DrawBackGround();		//�w�i�̕`�揈��
	DrawBullet();			//�e�̕`�揈��
	DrawShootingPlayer();	//�v���C���[�̕`�揈��
	DrawShootingEnemy();	//�G�̕`�揈��
	DrawEffect();			//�G�t�F�N�g�̕`�揈��
	DrawParticle();			//�p�[�e�B�N���̕`�揈��

	if (g_nCntShootingGameState >= 60)
	{
		DrawClear();		//�N���A�\���̕`�揈��
	}
}
void SetShootingGameState(STGSTATE state)
{
	g_gameState = state;
}
STGSTATE GetShootingGameState(void)
{
	return g_gameState;
}