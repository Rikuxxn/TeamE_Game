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
#include "meshceiling.h"
//#include "sound.h"
#include "guage.h"
#include "shooting_game.h"
#include "crane_game.h"
#include "ui.h"
#include "shadow.h"
#include "map.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;//�Q�[���̏��
int g_nCounterGameState = 0;//��ԊǗ��J�E���^�[

bool g_bPause = false;	//�|�[�Y�����ǂ���
bool g_bDraw = false;	//�~�j�Q�[���̕`��p
bool g_bDraw2 = false;
bool bSTClear;
bool bACClear;
bool bMap;
bool g_bMini;
int nCounter;
int nStgCnt;
int nCraneCnt;

//==============================================
//�Q�[����ʂ̏���������
//==============================================
void InitGame(void)
{

	// �J�[�\������ʒ����ɖ߂�
	SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);


	// �J�[�\�����\���ɂ���
	SetCursorVisibility(false);


	//���b�V���t�B�[���h�̏���������
	InitMeshfield();


	//���b�V���V�[�����O�̏���������
	InitMeshCeiling();


	//���b�V���V�����_�[�̏���������
	InitMeshcylinder();


	//�J�����̏���������
	InitCamera();


	//���C�g�̏���������
	InitLight();


	//�u���b�N�̏���������
	InitBlock();


	//�e�̏�����
	InitShadow();


	//�v���C���[�̏���������
	InitPlayer();
	

	//�G�̏�����
	InitEnemy();


	////�^�C���̏���������
	//InitTime();


	////�r���{�[�h�̏���������
	//InitBillboard();


	//�Q�[�W�̏�����
	InitGuage();


	//UI�̏�����
	InitUI();

	//�~�j�Q�[���̏�����
	InitShootingGame();
	InitCraneGame();

	//// �V��̒����t�߂������G���A���Ƃ炷�X�|�b�g���C�g
	//AddLight(
	//	D3DLIGHT_SPOT,                       // ���C�g�̎��
	//	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),   // �������邢��
	//	D3DXVECTOR3(0.0f, -1.0f, 0.0f),      // �^������
	//	D3DXVECTOR3(0.0f, 5.0f, 0.0f)       // �V�䒆���̈ʒu
	//);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                 // ���C�g�̎��
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),    // �Â߂̔�����
		D3DXVECTOR3(0.0f, -1.0f, 0.0f),       // �^������
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // �V��̈ʒu�i���������j
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ���C�g�̎��
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),    // �Â߂̔�����
		D3DXVECTOR3(-1.0f, 0.0f, 0.0f),       // ������
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // �V��̈ʒu�i���������j
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ���C�g�̎��
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),    // �Â߂̔�����
		D3DXVECTOR3(0.0f, 0.0f, -1.0f),       // ��O����
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // �V��̈ʒu�i���������j
	);


	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ���C�g�̎��
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),    // �Â߂̔�����
		D3DXVECTOR3(1.0f, 0.0f, 0.0f),       // �E����
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // �V��̈ʒu�i���������j
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ���C�g�̎��
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),    // �Â߂̔�����
		D3DXVECTOR3(0.0f, 0.0f, 1.0f),       // ������
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // �V��̈ʒu�i���������j
	);

	// �G
	SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, 160.0f));


	//�|�[�Y�̏���������
	InitPause();

	//�}�b�v�̏���������
	InitMap();

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
	nCraneCnt = 0;
	nStgCnt = 0;

	bSTClear = false;
	bACClear = false;
	g_bMini = false;
	bMap = false;

	//�G�f�B�b�g�ǂݍ���
	LoadBlockData();

	//�G�f�B�b�g�ǂݍ���
	LoadWallData();

}
//============================================
//�Q�[����ʂ̏I������
//============================================
void UninitGame(void)
{

	//StopSound(SOUND_LABEL_GAMEBGM);
	//StopSound();

	// �J�[�\����\������
	SetCursorVisibility(true);


	//���b�V���t�B�[���h�̏I������
	UninitMeshfield();


	//���b�V���V�[�����O�̏I������
	UninitMeshCeiling();


	//���b�V���V�����_�[�̏I������
	UninitMeshcylinder();


	//�J�����̏I������
	UninitCamera();


	//���C�g�̏I������
	UninitLight();


	//�u���b�N�̏I������
	UninitBlock();


	//�e�̏I������
	UninitShadow();


	////�r���{�[�h�̏I������
	//UninitBillboard();


	//�v���C���[�̏I������
	UninitPlayer();


	//�G�̏I������
	UninitEnemy();


	////�^�C���̏I������
	//UninitTime();


	//�|�[�Y�̏I������
	UninitPause();


	//�}�b�v�̏I������
	UninitMap();

	////�G�t�F�N�g�̏I������
	//UninitEffect();


	////�p�[�e�B�N���̏I������
	//UninitParticle();


	//�Q�[�W�̏I������
	UninitGuage();


	//UI�̏I������
	UninitUI();

	//�~�j�Q�[���̏I������
	UninitShootingGame();
	UninitCraneGame();
}
//=========================================
//�Q�[����ʂ̍X�V����
//=========================================
void UpdateGame(void)
{
	//int nTime = GetTime();
	bool bExit = GetExit();
	STGSTATE pStgState = GetShootingGameState();
	CRANEGAMESTATE pCraneState = GetCraneGameState();
	Player* pPlayer = GetPlayer();//�v���C���[�̏��ւ̃|�C���^�Ƀv���C���[�̐擪�A�h���X����������
	bool bArcade = GetArcade();
	bool bCatcher = GetCatcher();
	bool bEnd = GetEnd();


	// �~�j�Q�[�����̓|�[�Y���J���Ȃ��悤�ɂ���
	if (g_bMini == false && bMap == false && (KeyboardTrigger(DIK_P) == true || JoyPadTrigger(JOYKEY_START) == true))
	{
		g_bPause = g_bPause ? false : true;

		// PlaySound(SOUND_LABEL_PAUSE); // �|�[�Y���̍Đ�
	}

	if (g_bPause == true)
	{//�|�[�Y��

		//�|�[�Y�̍X�V����
		UpdatePause();

		// �J�[�\����\������
		SetCursorVisibility(true);

	}
	else
	{//�|�[�Y���ł͂Ȃ�

		// �~�j�Q�[���i�V���[�e�B���O�j�̃g���K�[
		if (KeyboardTrigger(DIK_E) == true && pStgState != STGSTATE_END && bArcade == true && bMap == false)
		{
			g_bDraw = g_bDraw ? false : true;
			g_bMini = g_bMini ? false : true;
		}

		// �~�j�Q�[���i�A�N�V�����j�̃g���K�[
		if (KeyboardTrigger(DIK_E) == true && pCraneState != CRANEGAMESTATE_END && bCatcher == true && bMap == false)
		{
			g_bDraw2 = g_bDraw2 ? false : true;
			g_bMini = g_bMini ? false : true;
		}

		// �}�b�v���J����̂̓~�j�Q�[�����ǂ���������Ă��Ȃ��ꍇ�̂�
		if (g_bMini == false && g_bDraw == false && g_bDraw2 == false &&
			(KeyboardTrigger(DIK_C) == true || JoyPadTrigger(JOYKEY_BACK) == true))
		{
			bMap = bMap ? false : true;
		}


		// �V���[�e�B���O�Q�[���I�����̏���
		if (pStgState == STGSTATE_END)
		{
			if (nStgCnt <= 120)
			{
				nStgCnt++;
			}

			// 120(2�b)�o������
			if (nStgCnt >= 120)
			{
				g_bDraw = false;
				bSTClear = true;
				if (g_bDraw2 == false) // �N���[���Q�[���������Ă��Ȃ��Ȃ�
				{
					g_bMini = false; // �~�j�Q�[���S�̂��I��
				}
			}
		}

		// �N���[���Q�[���I�����̏���
		if (pCraneState == CRANEGAMESTATE_END)
		{
			if (nCraneCnt <= 120)
			{
				nCraneCnt++;
			}

			// 120(2�b)�o������
			if (nCraneCnt >= 120)
			{
				g_bDraw2 = false;
				bACClear = true;
				if (g_bDraw == false) // �V���[�e�B���O�Q�[���������Ă��Ȃ��Ȃ�
				{
					g_bMini = false; // �~�j�Q�[���S�̂��I��
				}
			}
		}

		// �J�[�\�����\������
		SetCursorVisibility(false);


		if (g_bDraw == false && g_bDraw2 == false)
		{
			//�v���C���[�̍X�V����
			UpdatePlayer();
		}
		if (g_bDraw == true)
		{
			//�~�j�Q�[��(�V���[�e�B���O)�̍X�V����
			UpdateShootingGame();
		}
		if (g_bDraw2 == true)
		{
			//�~�j�Q�[��(�A�N�V����)�̍X�V����
			UpdateCraneGame();
		}

		//�G�̍X�V����
		UpdateEnemy();


		//���b�V���t�B�[���h�̍X�V����
		UpdateMeshfield();


		//���b�V���V�[�����O�̍X�V����
		UpdateMeshCeiling();


		//���b�V���V�����_�[�̍X�V����
		UpdateMeshcylinder();

		if (g_bDraw == false && g_bDraw2 == false)
		{
			//�J�����̍X�V����
			UpdateCamera();
		}


		////���C�g�̍X�V����
		//UpdateLight(0, D3DXVECTOR3(0.0f, -1.0f, 0.0f));


		//�u���b�N�̍X�V����
		UpdateBlock();


		//�e�̍X�V����
		UpdateShadow();


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

		//�Q�[�W�̍X�V����
		UpdateGuage();

		//UI�̍X�V����
		UpdateUI();

	}


	if ((pPlayer->bDisp == false || bExit == true /*|| nTime <= 0*/ || bEnd  == true) && g_gameState != GAMESTATE_NONE)
	{

		//���[�h�ݒ�(���U���g��ʂɈڍs)
 		g_gameState = GAMESTATE_END;
		g_bDraw = false;
		g_bDraw2 = false;
		bMap = false;
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
	Player* pPlayer = GetPlayer();	//�v���C���[�擾

	//�v���C���[�̕`�揈��
	DrawPlayer();


	//�G�̕`�揈��
	DrawEnemy();


	//�J�����̐ݒ菈��
	SetCamera();


	//���b�V���t�B�[���h�̕`�揈��
	DrawMeshfield();


	//���b�V���V�[�����O�̕`�揈��
	DrawMeshCeiling();


	////���b�V���V�����_�[�̕`�揈��
	//DrawMeshcylinder();


	//�u���b�N�̕`�揈��
	DrawBlock();


	////�G�t�F�N�g�̕`�揈��
	//DrawEffect();


	////�p�[�e�B�N���̕`�揈��
	//DrawParticle();


	////�r���{�[�h�̕`�揈��
	//DrawBillboard();


	////�^�C���̕`�揈��
	//DrawTime();

	if (g_bMini == false)
	{
		//UI�̕`�揈��
		DrawUI();
	}
	if (pPlayer->bDrawDush == true)
	{
		//�Q�[�W�̕`�揈��
		DrawGuage();
	}

	//�e�̕`�揈��
	DrawShadow();

	if (bMap == true && g_bMini == false)
	{//�}�b�v�̕`��
		DrawMap();
	}
	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�̕`�揈��
		DrawPause();
	}

	if (g_bDraw == true && nStgCnt <= 120)
	{
		//�~�j�Q�[���̕`�揈��
		DrawShootingGame();
	}
	else if (g_bDraw2 == true && nCraneCnt <= 120)
	{
		DrawCraneGame();
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
//============================================
// ST�N���A�̎擾
//============================================
bool GetSTClear(void)
{
	return bSTClear;
}
//============================================
// AC�N���A�̎擾
//============================================
bool GetACClear(void)
{
	return bACClear;
}



