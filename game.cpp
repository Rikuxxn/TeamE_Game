//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "input.h"
//#include "score.h"
//#include "ranking.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "pause.h"
#include "time.h"
//#include "particle.h"
//#include "effect.h"
#include "camera.h"
#include "warning.h"
//#include "wall.h"
//#include "billboard.h"
#include "light.h"
//#include "meshwall.h"
//#include "shadow.h"
#include "meshfield.h"
//#include "rankingscore.h"
#include "model.h"
#include "enemy.h"
#include "meshcylinder.h"
#include "block.h"
#include "edit.h"
//#include "sound.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;//�Q�[���̏��
int g_nCounterGameState = 0;//��ԊǗ��J�E���^�[

bool g_bPause = false;//�|�[�Y�����ǂ���
int nCounter;

//==============================================
//�Q�[����ʂ̏���������
//==============================================
void InitGame(void)
{

	//���b�V���t�B�[���h�̏���������
	InitMeshfield();


	//���b�V���V�����_�[�̏���������
	InitMeshcylinder();


	//�J�����̏���������
	InitCamera();


	//���C�g�̏���������
	InitLight();


	////���f���̏���������
	//InitModel();


	//�u���b�N�̏���������
	InitBlock();


	////�e�̏�����
	//InitShadow();


	//�v���C���[�̏���������
	InitPlayer();


	//�G�̏�����
	InitEnemy();


	////�^�C���̏���������
	//InitTime();


	////�r���{�[�h�̏���������
	//InitBillboard();


	//�u���b�N
	SetBlock(D3DXVECTOR3(-220.0f, 0.0f, 325.0f), BLOCKTYPE_NORMAL);		//	��
	//SetBlock(D3DXVECTOR3(-220.0f, 0.0f, 85.0f), BLOCKTYPE_NORMAL);		//	�h�A


	//SetModel(D3DXVECTOR3(-220.0f, 0.0f, 285.0f), WALLTYPE_NORMAL);		//	��


	//// �ǂ�pos���^�񒆂̎��̂��
	////����
	//SetWall(D3DXVECTOR3(-350.0f, 50.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////�E��
	//SetWall(D3DXVECTOR3(350.0f, 50.0f, 350.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////��O��
	//SetWall(D3DXVECTOR3(350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////����
	//SetWall(D3DXVECTOR3(-350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);


	////�ǂ�pos���[�̎��̂��
	////����
	//SetWall(D3DXVECTOR3(-350.0f, 50.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////�E��
	//SetWall(D3DXVECTOR3(350.0f, 50.0f, 350.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////��O��
	//SetWall(D3DXVECTOR3(350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);

	////����
	//SetWall(D3DXVECTOR3(-350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 50.0f);



	//// �G
	//SetEnemy(D3DXVECTOR3(280.0f, 0.0f, 260.0f));


	//�|�[�Y�̏���������
	InitPause();


	////�G�t�F�N�g�̏���������
	//InitEffect();


	////�p�[�e�B�N���̏���������
	//InitParticle();


	////�T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_GAMEBGM);


	////�T�E���h�̒�~
	//StopSound(SOUND_LABEL_RANK);


	g_gameState = GAMESTATE_NORMAL;//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
	g_bPause = false;//�|�[�Y����
	nCounter = 0;

	////�G�f�B�b�g�ǂݍ���
	//LoadBlockData();

}
//============================================
//�Q�[����ʂ̏I������
//============================================
void UninitGame(void)
{

	//StopSound(SOUND_LABEL_GAMEBGM);
	//StopSound();

	//���b�V���t�B�[���h�̏I������
	UninitMeshfield();


	//���b�V���V�����_�[�̏I������
	UninitMeshcylinder();


	//�J�����̏I������
	UninitCamera();


	//���C�g�̏I������
	UninitLight();


	////���f���̏I������
	//UninitModel();


	//�u���b�N�̏I������
	UninitBlock();


	////�e�̏I������
	//UninitShadow();


	////�r���{�[�h�̏I������
	//UninitBillboard();


	//�v���C���[�̏I������
	UninitPlayer();


	//�G�̏I������
	UninitEnemy();


	////�^�C���̏I������
	//UninitTime();


	////�G�t�F�N�g�̏I������
	//UninitEffect();


	////�p�[�e�B�N���̏I������
	//UninitParticle();

}
//=========================================
//�Q�[����ʂ̍X�V����
//=========================================
void UpdateGame(void)
{
	//int nTime = GetTime();
	bool bExit = GetExit();

	Player* pPlayer = GetPlayer();//�v���C���[�̏��ւ̃|�C���^�Ƀv���C���[�̐擪�A�h���X����������

	if (KeyboardTrigger(DIK_P) == true|| JoyPadTrigger(JOYKEY_START)==true)
	{//ESCAPE(�|�[�Y)�L�[�������ꂽ
		g_bPause = g_bPause ? false : true;

		//PlaySound(SOUND_LABEL_PAUSE);

	}

	if (g_bPause == true)
	{//�|�[�Y��

		//�|�[�Y�̍X�V����
		UpdatePause();

	}
	else
	{

		//�v���C���[�̍X�V����
		UpdatePlayer();


		//�G�̍X�V����
		UpdateEnemy();


		//���b�V���t�B�[���h�̍X�V����
		UpdateMeshfield();


		//���b�V���V�����_�[�̍X�V����
		UpdateMeshcylinder();


		//�J�����̍X�V����
		UpdateCamera();


		//���C�g�̍X�V����
		UpdateLight();


		////���f���̍X�V����
		//UpdateModel();


		//�u���b�N�̍X�V����
		UpdateBlock();


		////�e�̍X�V����
		//UpdateShadow();


		////�r���{�[�h�̍X�V����
		//UpdateBillboard();


		////�G�t�F�N�g�̍X�V����
		//UpdateEffect();


		////�^�C���̍X�V����
		//UpdateTime();


		////�p�[�e�B�N���̍X�V����
		//UpdateParticle();

		//if (KeyboardTrigger(DIK_F5) == true)
		//{
		//	onWireFrame();
		//}
		//else if (KeyboardTrigger(DIK_F6) == true)
		//{
		//	offWireFrame();
		//}
	}

	bool bEnd = GetEnd();

	if ((pPlayer->bDisp == false || bExit == true /*|| nTime <= 0*/ || bEnd  == true) && g_gameState != GAMESTATE_NONE)
	{

		//���[�h�ݒ�(���U���g��ʂɈڍs)
 		g_gameState = GAMESTATE_END;

	}

	int nResultScore;
	//nResultScore = GetScore();
	//nTime = GetTime();

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://�ʏ���
		break;

	case GAMESTATE_END://�I�����
		g_nCounterGameState++;

		if (g_nCounterGameState >= 60)
		{
			
			g_nCounterGameState = 0;

			g_gameState = GAMESTATE_NONE;

			//���[�h�ݒ�(���U���g��ʂɈڍs)
			SetFade(MODE_RESULT);

			if (bExit == true)
			{

				////�^�C���ɉ����ăX�R�A���Z
				//AddScore((nTime* GetScore()) * 0.2f);


				////���U���g�X�R�A�̐ݒ�
				//SetResultScore(GetScore());


				////�����L���O�̃��Z�b�g
				//ResetRanking();


				////�����L���O�̐ݒ�
				//SetRanking(GetScore());

			}

		}
		break;
	}

}
//===========================================
//�Q�[����ʂ̕`�揈��
//===========================================
void DrawGame(void)
{

	//�v���C���[�̕`�揈��
	DrawPlayer();


	//�G�̕`�揈��
	DrawEnemy();


	//�J�����̐ݒ菈��
	SetCamera();


	//���b�V���t�B�[���h�̕`�揈��
	DrawMeshfield();


	//���b�V���V�����_�[�̕`�揈��
	DrawMeshcylinder();


	////���f���̕`�揈��
	DrawModel();


	//�u���b�N�̕`�揈��
	DrawBlock();


	////�e�̕`�揈��
	//DrawShadow();


	////�G�t�F�N�g�̕`�揈��
	//DrawEffect();


	////�p�[�e�B�N���̕`�揈��
	//DrawParticle();


	////�r���{�[�h�̕`�揈��
	//DrawBillboard();


	////�^�C���̕`�揈��
	//DrawTime();

	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�̕`�揈��
		DrawPause();
	}

}
//=============================================
//�Q�[���̏�Ԃ̐ݒ�
//=============================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//============================================
//�Q�[����Ԃ̎擾
//============================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
//============================================
//�|�[�Y�̗L�������ݒ�
//============================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}



