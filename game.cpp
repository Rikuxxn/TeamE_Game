//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "input.h"
//#include "ranking.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "pause.h"
//#include "particle.h"
//#include "effect.h"
#include "camera.h"
#include "warning.h"
#include "light.h"
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
#include "password_game.h"
#include "crane_game.h"
#include "ball_game.h"
#include "ui.h"
#include "shadow.h"
#include "map.h"
#include "task.h"
#include "time.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;		// �Q�[���̏��
int g_nCounterGameState = 0;				// ��ԊǗ��J�E���^�[

GAME g_Game;								// �Q�[���̏��

bool g_bPause = false;	//�|�[�Y�����ǂ���

//==============================================
//�Q�[����ʂ̏���������
//==============================================
void InitGame(void)
{

	//// �J�[�\������ʒ����ɖ߂�
	//SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);


	//// �J�[�\�����\���ɂ���
	//SetCursorVisibility(false);


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


	//SetBlock(D3DXVECTOR3(200.0f, 0.0f, -120.0f), D3DXVECTOR3(0.0f, D3DX_PI *0.75f, 0.0f), BLOCKTYPE_TEST);


	//�e�̏�����
	InitShadow();


	//�v���C���[�̏���������
	InitPlayer();
	

	//�G�̏�����
	InitEnemy();


	//�^�C���̏���������
	InitTime();


	////�r���{�[�h�̏���������
	//InitBillboard();


	//�Q�[�W�̏�����
	InitGuage();


	//UI�̏�����
	InitUI();

	//�^�X�NUI�̏���������
	InitTask();

	SetTask(D3DXVECTOR3(2350.0f, 200.0f, 0.0f), 160.0f, 25.0f, TASKTYPE_ONE);
	SetTask(D3DXVECTOR3(2350.0f, 200.0f, 0.0f), 160.0f, 25.0f, TASKTYPE_TWO);
	SetTask(D3DXVECTOR3(2350.0f, 200.0f, 0.0f), 160.0f, 25.0f, TASKTYPE_THREE);

	SetTask(D3DXVECTOR3(2350.0f, 230.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB1);
	SetTask(D3DXVECTOR3(2350.0f, 260.0f, 0.0f), 130.0f, 20.0f, TASKTYPE_SUB2);

	SetTask(D3DXVECTOR3(2350.0f, 230.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB3);
	SetTask(D3DXVECTOR3(2350.0f, 260.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB4);
	SetTask(D3DXVECTOR3(2350.0f, 290.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB5);

	SetTask(D3DXVECTOR3(2350.0f, 230.0f, 0.0f), 110.0f, 20.0f, TASKTYPE_SUB6);

	//�~�j�Q�[���̏�����
	InitShootingGame();
	InitCraneGame();
	InitBallGame();
	InitPasswordGame();

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
	g_Game.nCounter = 0;
	g_Game.nCraneCnt = 0;
	g_Game.nStgCnt = 0;
	g_Game.nBallCnt = 0;
	g_Game.nPassCnt = 0;
	g_Game.bSTClear = false;
	g_Game.bACClear = false;
	g_Game.bBallClear = false;
	g_Game.bPassClear = false;
	g_Game.bMini = false;
	g_Game.bMap = false;

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
	LPDIRECT3DDEVICE9 pDevice; // ���O�ɍ쐬�E����������Ă���f�o�C�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���̖�����
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

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


	//�^�C���̏I������
	UninitTime();


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


	// �^�X�NUI�̏I������
	UninitTask();


	//�~�j�Q�[���̏I������
	UninitShootingGame();
	UninitCraneGame();
	UninitBallGame();
	UninitPasswordGame();
}
//=========================================
//�Q�[����ʂ̍X�V����
//=========================================
void UpdateGame(void)
{
	bool bFog = GetFog();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���̐ݒ�
	SetupVertexFog(pDevice, D3DCOLOR_XRGB(0, 0, 0), D3DFOG_LINEAR, TRUE, 0.0f);

	// ���̖�����
	pDevice->SetRenderState(D3DRS_FOGENABLE, bFog);

	//int nTime = GetTime();
	bool bExit = GetExit();
	STGSTATE pStgState = GetShootingGameState();
	CRANEGAMESTATE pCraneState = GetCraneGameState();
	BALLGAMESTATE pBallState = GetBallGameState();
	PASSWORDGAMESTATE pPassState = GetPasswordGameState();
	Player* pPlayer = GetPlayer();//�v���C���[�̏��ւ̃|�C���^�Ƀv���C���[�̐擪�A�h���X����������
	bool bArcade = GetArcade();
	bool bCatcher = GetCatcher();
	bool bBall = GetBall();
	bool bFuseCmp = GetFuseCmp();
	bool bKeypad = GetKeypad();

	bool bEnd = GetEnd();

	// �~�j�Q�[�����̓|�[�Y���J���Ȃ��悤�ɂ���
	if (g_Game.bMini == false && g_Game.bMap == false && (KeyboardTrigger(DIK_P) == true || JoyPadTrigger(JOYKEY_START) == true))
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
		if (KeyboardTrigger(DIK_E) == true && 
			pStgState != STGSTATE_END && 
			bArcade == true && 
			g_Game.bMap == false &&
			bFuseCmp == true)
		{
			g_Game.bDraw = g_Game.bDraw ? false : true;
			g_Game.bMini = g_Game.bMini ? false : true;
		}

		// �~�j�Q�[���i�A�N�V�����j�̃g���K�[
		if (KeyboardTrigger(DIK_E) == true &&
			pCraneState != CRANEGAMESTATE_END &&
			bCatcher == true && 
			g_Game.bMap == false &&
			bFuseCmp == true)
		{
			g_Game.bDraw2 = g_Game.bDraw2 ? false : true;
			g_Game.bMini = g_Game.bMini ? false : true;
		}

		// �{�[���v�[���̃g���K�[
		if (KeyboardTrigger(DIK_E) == true && 
			pBallState != BALLGAMESTATE_END && 
			bBall == true && 
			g_Game.bMap == false &&
			bFuseCmp == true)
		{
			g_Game.bDraw3 = g_Game.bDraw3 ? false : true;
			g_Game.bMini = g_Game.bMini ? false : true;
		}

		// �L�[�p�b�h�̃g���K�[
		if (KeyboardTrigger(DIK_E) == true/* && 
			pPassState != PASSWORDGAMESTATE_END &&
			bKeypad == true && 
			g_Game.bMap == false &&
			bFuseCmp == true &&
			g_Game.bSTClear == true && g_Game.bACClear == true && g_Game.bBallClear == true*/)
		{
			g_Game.bDraw4 = g_Game.bDraw4 ? false : true;
			g_Game.bMini = g_Game.bMini ? false : true;
		}


		// �}�b�v���J����̂̓~�j�Q�[�����ǂ���������Ă��Ȃ��ꍇ�̂�
		if (g_Game.bMini == false && g_Game.bDraw == false && g_Game.bDraw2 == false && 
			g_Game.bDraw3 == false && g_Game.bDraw4 == false &&
			(KeyboardTrigger(DIK_C) == true || JoyPadTrigger(JOYKEY_BACK) == true))
		{
			g_Game.bMap = g_Game.bMap ? false : true;
		}


		// �V���[�e�B���O�Q�[���I�����̏���
		if (pStgState == STGSTATE_END)
		{
			if (g_Game.nStgCnt <= 120)
			{
				g_Game.nStgCnt++;
			}

			// 120(2�b)�o������
			if (g_Game.nStgCnt >= 120)
			{
				g_Game.bDraw = false;
				g_Game.bSTClear = true;
				if (g_Game.bDraw2 == false &&
					g_Game.bDraw3 == false &&
					g_Game.bDraw4 == false) // ���̃Q�[�����N���A�ς݂Ȃ�
				{
					g_Game.bMini = false; // �~�j�Q�[���S�̂��I��
				}
			}
		}

		// �N���[���Q�[���I�����̏���
		if (pCraneState == CRANEGAMESTATE_END)
		{
			if (g_Game.nCraneCnt <= 120)
			{
				g_Game.nCraneCnt++;
			}

			// 120(2�b)�o������
			if (g_Game.nCraneCnt >= 120)
			{
				g_Game.bDraw2 = false;
				g_Game.bACClear = true;
				if (g_Game.bDraw == false &&
					g_Game.bDraw3 == false &&
					g_Game.bDraw4 == false) // �V���[�e�B���O�Q�[���������Ă��Ȃ��Ȃ�
				{
					g_Game.bMini = false; // �~�j�Q�[���S�̂��I��
				}
			}
		}

		// �{�[���v�[���I�����̏���
		if (pBallState == BALLGAMESTATE_END)
		{
			if (g_Game.nBallCnt <= 120)
			{
				g_Game.nBallCnt++;
			}

			// 120(2�b)�o������
			if (g_Game.nBallCnt >= 120)
			{
				g_Game.bDraw3 = false;
				g_Game.bBallClear = true;
				if (g_Game.bDraw == false &&
					g_Game.bDraw2 == false &&
					g_Game.bDraw4 == false) // �V���[�e�B���O�Q�[���������Ă��Ȃ��Ȃ�
				{
					g_Game.bMini = false; // �~�j�Q�[���S�̂��I��
				}
			}
		}

		// �L�[�p�b�h�I�����̏���
		if (pPassState == PASSWORDGAMESTATE_END)
		{
			if (g_Game.nPassCnt <= 120)
			{
				g_Game.nPassCnt++;
			}

			// 120(2�b)�o������
			if (g_Game.nPassCnt >= 60)
			{
				g_Game.bDraw4 = false;
				g_Game.bPassClear = true;
				if (g_Game.bDraw == false &&
					g_Game.bDraw2 == false &&
					g_Game.bDraw3 == false) // �V���[�e�B���O�Q�[���������Ă��Ȃ��Ȃ�
				{
					g_Game.bMini = false; // �~�j�Q�[���S�̂��I��
				}
			}
		}


		// �J�[�\�����\������
		SetCursorVisibility(false);


		if (g_Game.bDraw == false && g_Game.bDraw2 == false && g_Game.bDraw3 == false)
		{
			//�v���C���[�̍X�V����
			UpdatePlayer();

		}
		if (g_Game.bDraw == true)
		{
			//�~�j�Q�[��(�V���[�e�B���O)�̍X�V����
			UpdateShootingGame();
		}
		if (g_Game.bDraw2 == true)
		{
			//�~�j�Q�[��(�A�N�V����)�̍X�V����
			UpdateCraneGame();
		}
		if (g_Game.bDraw3 == true)
		{
			//�{�[���v�[���̍X�V����
			UpdateBallGame();

			// �J�[�\����\������
			SetCursorVisibility(true);
		}
		if (g_Game.bDraw4 == true)
		{
			//�L�[�p�b�h�̍X�V����
			UpdatePasswordGame();

			// �J�[�\����\������
			SetCursorVisibility(true);
		}


		//�G�̍X�V����
		UpdateEnemy();


		//���b�V���t�B�[���h�̍X�V����
		UpdateMeshfield();


		//���b�V���V�[�����O�̍X�V����
		UpdateMeshCeiling();


		//���b�V���V�����_�[�̍X�V����
		UpdateMeshcylinder();

		if (g_Game.bDraw == false && g_Game.bDraw2 == false && g_Game.bDraw3 == false && g_Game.bDraw4 == false)
		{
			//�J�����̍X�V����
			UpdateCamera();
		}


		//���C�g�̍X�V����
		UpdateLight(0, D3DXVECTOR3(0.0f, 5.0f, -400.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f));


		//�u���b�N�̍X�V����
		UpdateBlock();


		//�e�̍X�V����
		UpdateShadow();


		////�r���{�[�h�̍X�V����
		//UpdateBillboard();


		////�G�t�F�N�g�̍X�V����
		//UpdateEffect();


		//�^�C���̍X�V����
		UpdateTime();


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

		// �^�X�NUI�̍X�V����
		UpdateTask();

		// �}�b�v�̍X�V����
		UpdateMap();
	}


	if ((pPlayer->bDisp == false || bExit == true || bEnd  == true) && g_gameState != GAMESTATE_NONE)
	{
		//���[�h�ݒ�(���U���g��ʂɈڍs)
 		g_gameState = GAMESTATE_END;
		g_Game.bDraw = false;
		g_Game.bDraw2 = false;
		g_Game.bDraw3 = false;
		g_Game.bDraw4 = false;
		g_Game.bMap = false;
	}

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
	LPDIRECT3DDEVICE9 pDevice; // ���O�ɍ쐬�E����������Ă���f�o�C�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

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


	//�u���b�N�̕`�揈��
	DrawBlock();


	//���b�V���V�����_�[�̕`�揈��
	DrawMeshcylinder();


	// ���̖�����
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);


	////�G�t�F�N�g�̕`�揈��
	//DrawEffect();


	////�p�[�e�B�N���̕`�揈��
	//DrawParticle();


	////�r���{�[�h�̕`�揈��
	//DrawBillboard();


	if (pPlayer->bDrawDush == true)
	{
		//�Q�[�W�̕`�揈��
		DrawGuage();
	}

	if (g_Game.bMini == false)
	{
		// �^�X�NUI�̕`�揈��
		DrawTask();

		//UI�̕`�揈��
		DrawUI();
	}

#ifdef _DEBUG

	//�^�C���̕`�揈��
	DrawTime();

#endif

	//�e�̕`�揈��
	DrawShadow();

	if (g_Game.bMap == true && g_Game.bMini == false)
	{//�}�b�v�̕`��
		DrawMap();
	}
	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�̕`�揈��
		DrawPause();
	}

	if (g_Game.bDraw == true && g_Game.nStgCnt <= 120)
	{
		//�~�j�Q�[���̕`�揈��
		DrawShootingGame();
	}
	else if (g_Game.bDraw2 == true && g_Game.nCraneCnt <= 120)
	{
		DrawCraneGame();
	}
	else if (g_Game.bDraw3 == true && g_Game.nBallCnt <= 120)
	{
		DrawBallGame();
	}
	else if (g_Game.bDraw4 == true && g_Game.nPassCnt <= 120)
	{
		DrawPasswordGame();
	}

	// ���̗L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}
//=============================================
// �Q�[���̏�Ԃ̐ݒ�
//=============================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//============================================
// �Q�[����Ԃ̎擾
//============================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
//============================================
// �Q�[���̎擾
//============================================
GAME* GetGame(void)
{
	return &g_Game;
}
//============================================
// �|�[�Y�̗L�������ݒ�
//============================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}