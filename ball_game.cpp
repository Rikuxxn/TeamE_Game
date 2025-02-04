//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "ball_game.h"
#include "input.h"
#include "ball_fade.h"
#include "ball_effect.h"
#include "ball_particle.h"
#include "ball_block.h"
#include "ball_item.h"
#include "ball_background.h"
#include "time.h"
//#include "sound.h"
#include "ball_clear.h"

//�O���[�o��
BALLGAMESTATE g_gameState = BALLGAMESTATE_NONE;	  //�Q�[���̏��
int g_nCounterBallGameState = 0;				  //��ԊǗ��J�E���^�[

void InitBallGame(void)
{
	//�e��I�u�W�F�N�g�̏���������
	InitBallBackGround();	//�w�i�̏���������
	InitBallParticle();		//�p�[�e�B�N���̏�����
	InitBallBlock();		//�u���b�N�̏���������
	InitBallEffect();		//�G�t�F�N�g�̏�����
	InitBallItem();			//�A�C�e���̏�����
	InitBallClear();		//�N���A��ʂ̏�����

	SetBallBlock(D3DXVECTOR3(BALLFIELD_LEFT + 100.0f, BALLFIELD_UNDER - 30.0f, 0.0f), D3DXVECTOR3(), 50.0f, 30.0f, 0);	//�u���b�N
	
	SetBallItem(D3DXVECTOR3(740.0f, BALLFIELD_UNDER - 160.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 0);					//�A�C�e��
	SetBallItem(D3DXVECTOR3(540.0f, BALLFIELD_UNDER - 69.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 1);
	SetBallItem(D3DXVECTOR3(640.0f, BALLFIELD_UNDER - 161.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2);
	SetBallItem(D3DXVECTOR3(840.0f, BALLFIELD_UNDER - 475.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3);

	SetBallItem(D3DXVECTOR3(340.0f, BALLFIELD_UNDER - 304.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3);
	SetBallItem(D3DXVECTOR3(564.0f, BALLFIELD_UNDER - 121.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 1);
	SetBallItem(D3DXVECTOR3(792.0f, BALLFIELD_UNDER - 207.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 0);
	SetBallItem(D3DXVECTOR3(284.0f, BALLFIELD_UNDER - 94.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2);

	//SetBallItem(D3DXVECTOR3(313.0f, BALLFIELD_UNDER - 571.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 1);
	//SetBallItem(D3DXVECTOR3(207.0f, BALLFIELD_UNDER - 432.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3);
	//SetBallItem(D3DXVECTOR3(580.0f, BALLFIELD_UNDER - 389.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2);
	//SetBallItem(D3DXVECTOR3(703.0f, BALLFIELD_UNDER - 249.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 0);

	SetBallItem(D3DXVECTOR3(452.0f, BALLFIELD_UNDER - 571.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 1);
	SetBallItem(D3DXVECTOR3(513.0f, BALLFIELD_UNDER - 432.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 3);
	SetBallItem(D3DXVECTOR3(637.0f, BALLFIELD_UNDER - 389.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 2);
	SetBallItem(D3DXVECTOR3(870.0f, BALLFIELD_UNDER - 209.0f, 0.0f), ITEM_WIDTH, ITEM_HEIGHT, 0);

	g_gameState = BALLGAMESTATE_NORMAL;//�ʏ��Ԃɐݒ�
	g_nCounterBallGameState = 0;

	////�T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_GAMEBGM);
}
void UninitBallGame(void)
{
	////�T�E���h�̒�~
	//StopSound(SOUND_LABEL_GAMEBGM);

	//�e��I�u�W�F�N�g�̏I������
	UninitBallBackGround();	//�w�i�̏I������
	UninitBallParticle();		//�p�[�e�B�N���̏I������
	UninitBallBlock();			//�u���b�N�̏I������
	UninitBallEffect();		//�G�t�F�N�g�̏I������
	UninitBallItem();			//�A�C�e���̏I������
	UninitBallClear();			//�N���A��ʂ̏I������
}
void UpdateBallGame(void)
{
	int nNum = GetNumBallItem();

	//�e��I�u�W�F�N�g�̍X�V����
	UpdateBallBackGround();	//�w�i�̍X�V����
	UpdateBallParticle();	//�p�[�e�B�N���̍X�V����
	UpdateBallEffect();		//�G�t�F�N�g�̍X�V����
	UpdateBallItem();		//�A�C�e���̍X�V����

	if (nNum==0)//�I������
	{
		//���(���[�h)�̐ݒ�
		g_gameState = BALLGAMESTATE_END;
	}

	switch (g_gameState)
	{
	case BALLGAMESTATE_NORMAL://�ʏ���
		break;
	case BALLGAMESTATE_END://�I�����
		if (g_nCounterBallGameState <= 45)
		{
			g_nCounterBallGameState++;
		}

		if (g_nCounterBallGameState >= 45 && nNum == 0)
		{
			UpdateBallClear();
		}
		break;
	}
}
void DrawBallGame(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��
	DrawBallBackGround();	//�w�i�̕`�揈��
	DrawBallParticle();		//�p�[�e�B�N���̕`�揈��
	DrawBallItem();			//�A�C�e���̕`�揈��
	DrawBallBlock();		//�u���b�N�̕`�揈��
	DrawBallEffect();		//�G�t�F�N�g�̕`�揈��

	if (g_nCounterBallGameState >= 45)
	{
		DrawBallClear();
	}
}
void SetBallGameState(BALLGAMESTATE state)
{
	g_gameState = state;
}
BALLGAMESTATE GetBallGameState(void)
{
	return g_gameState;
}