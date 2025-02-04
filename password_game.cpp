//========================
//|      �p�X���[�h		 |
//|Author:Yoshida Atsushi|
//========================

// �C���N���[�h�t�@�C���錾
#include <time.h>
#include "input.h"
#include "password_background.h"
#include "password_block.h"
#include "password_clear.h"
#include "password_effect.h"
#include "password_fade.h"
#include "password_game.h"
#include "password_item.h"
#include "password_particle.h"
#include "password_score.h"
//#include "sound.h"

// �O���[�o���ϐ��錾
PASSWORDGAMESTATE g_gameState = PASSWORDGAMESTATE_NONE;	//�Q�[���̏��
int g_nCounterPasswordGameState = 0;					//��ԊǗ��J�E���^�[
int g_nA1, g_nA2, g_nA3, g_nA4;							//�p�X���[�h�̓���

//=========================
//|      �����������@     |
//=========================
void InitPasswordGame(void)
{
	//�e��I�u�W�F�N�g�̏���������
	InitPasswordBackGround();	//�w�i�̏���������
	InitPasswordParticle();		//�p�[�e�B�N���̏�����
	InitPassBlock();		//�u���b�N�̏���������
	InitPasswordEffect();		//�G�t�F�N�g�̏�����
	InitPasswordItem();			//�A�C�e���̏�����
	InitPasswordClear();		//�N���A��ʂ̏�����
	InitPassword();				//�p�X���[�h�̏�����

	SetPassword(0);
	//�A�C�e��
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_LEFT, ITEM_POSY_TOP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 1, NUMTYPE_1);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_CENTER, ITEM_POSY_TOP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2, NUMTYPE_2);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_RIGHT, ITEM_POSY_TOP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3, NUMTYPE_3);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_LEFT, ITEM_POSY_MIDDLE_UP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 4, NUMTYPE_4);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_CENTER, ITEM_POSY_MIDDLE_UP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 5, NUMTYPE_5);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_RIGHT, ITEM_POSY_MIDDLE_UP, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 6, NUMTYPE_6);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_LEFT, ITEM_POSY_MIDDLE_DOWN, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 7, NUMTYPE_7);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_CENTER, ITEM_POSY_MIDDLE_DOWN, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 8, NUMTYPE_8);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_RIGHT, ITEM_POSY_MIDDLE_DOWN, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 9, NUMTYPE_9);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_LEFT, ITEM_POSY_UNDER, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 11, NUMTYPE_DELETE);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_CENTER, ITEM_POSY_UNDER, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 0, NUMTYPE_0);
	SetPasswordItem(D3DXVECTOR3(ITEM_POSX_RIGHT, ITEM_POSY_UNDER, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 10, NUMTYPE_ENTER);

	srand((unsigned int)time(NULL));		//�����_��
	g_gameState = PASSWORDGAMESTATE_NORMAL;	//�ʏ��Ԃɐݒ�
	g_nCounterPasswordGameState = 0;
	g_nA1 = rand() % 9 + 0;
	g_nA2 = rand() % 9 + 0;
	g_nA3 = rand() % 9 + 0;
	g_nA4 = rand() % 9 + 0;

	////�T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_GAMEBGM);
}
//=======================
//|      �I������	    |
//=======================
void UninitPasswordGame(void)
{
	////�T�E���h�̒�~
	//StopSound(SOUND_LABEL_GAMEBGM);

	//�e��I�u�W�F�N�g�̏I������
	UninitPasswordBackGround();	//�w�i�̏I������
	UninitPasswordParticle();	//�p�[�e�B�N���̏I������
	UninitPassBlock();		//�u���b�N�̏I������
	UninitPasswordEffect();		//�G�t�F�N�g�̏I������
	UninitPasswordItem();		//�A�C�e���̏I������
	UninitPasswordClear();		//�N���A��ʂ̏I������
	UninitPassword();
}
//=======================
//| 	 �X�V����	    |
//=======================
void UpdatePasswordGame(void)
{
	int nPass = GetPassword();
	int nPass2 = GetPassword2();
	int nPass3 = GetPassword3();
	int nPass4 = GetPassword4();
	bool bJudge = GetJudgment();

	//�e��I�u�W�F�N�g�̍X�V����
	UpdatePasswordBackGround();	//�w�i�̍X�V����
	UpdatePasswordParticle();	//�p�[�e�B�N���̍X�V����
	UpdatePasswordEffect();		//�G�t�F�N�g�̍X�V����
	UpdatePasswordItem();		//�A�C�e���̍X�V����
	UpdatePassword();

	if (nPass == g_nA1 &&
		nPass2 == g_nA2 &&
		nPass3 == g_nA3 &&
		nPass4 == g_nA4 &&
		bJudge == true)//�Ïؔԍ��̈�v
	{//�I������
		//���(���[�h)�̐ݒ�
		g_gameState = PASSWORDGAMESTATE_END;
	}
	else if ((nPass == g_nA1 || nPass != g_nA1) &&
		(nPass2 == g_nA2 || nPass2 != g_nA2) &&
		(nPass3 == g_nA3 || nPass3 != g_nA3) &&
		(nPass4 == g_nA4 || nPass4 != g_nA4) &&
		bJudge == true)//�Ïؔԍ��̕s��v
	{
		SetPassword(0);
	}

	switch (g_gameState)
	{
	case PASSWORDGAMESTATE_NORMAL:	//�ʏ���
		break;
	case PASSWORDGAMESTATE_END:		//�I�����
		if (g_nCounterPasswordGameState <= 45)
		{
			g_nCounterPasswordGameState++;
		}

		if (g_nCounterPasswordGameState >= 45)
		{
			UpdatePasswordClear();
		}
		break;
	}
}
//=======================
//|  �Q�[���̕`�揈��   |
//=======================
void DrawPasswordGame(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��
	DrawPasswordBackGround();	//�w�i�̕`�揈��
	DrawPasswordParticle();		//�p�[�e�B�N���̕`�揈��
	DrawPasswordItem();			//�A�C�e���̕`�揈��
	DrawPassBlock();		//�u���b�N�̕`�揈��
	DrawPasswordEffect();		//�G�t�F�N�g�̕`�揈��
	DrawPassword();

	if (g_nCounterPasswordGameState >= 45)
	{
		DrawPasswordClear();
	}
}
void SetPasswordGameState(PASSWORDGAMESTATE state)
{
	g_gameState = state;
}
PASSWORDGAMESTATE GetPasswordGameState(void)
{
	return g_gameState;
}
int GetAnum(void)
{
	return g_nA1;
}
int GetAnum2(void)
{
	return g_nA2;
}
int GetAnum3(void)
{
	return g_nA3;
}
int GetAnum4(void)
{
	return g_nA4;
}