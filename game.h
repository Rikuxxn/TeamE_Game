//=============================================================================
//
// �Q�[������ [game.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _GAME_H_//���̃}�N����`������Ă��Ȃ�������
#define _GAME_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�Q�[���̏��
typedef enum
{

	GAMESTATE_NONE = 0,		//�������Ă��Ȃ����
	GAMESTATE_NORMAL,		//�ʏ���
	GAMESTATE_END,			//�I�����
	GAMESTATE_MAX

}GAMESTATE;

//�Q�[���\����
typedef struct
{
	bool bDraw;				//�@�V���[�e�B���O�~�j�Q�[���̕`��p
	bool bDraw2;			//�@�N���[��
	bool bDraw3;			//�@�{�[���v�[��
	bool bDraw4;			//�@�p�X���[�h
	bool bSTClear;			//�@�V���[�e�B���O
	bool bACClear;			//�@�N���[��
	bool bBallClear;		//�@�{�[���v�[��
	bool bPassClear;		//�@�p�X���[�h
	bool bMap;				//�@�}�b�v
	bool bMini;				//�@�~�j�Q�[���S��
	int nCounter;			//�@�J�E���^�[
	int nStgCnt;			//�@�V���[�e�B���O�J�E���^�[
	int nCraneCnt;			//�@�N���[���J�E���^�[
	int nBallCnt;			//�@�{�[���v�[���J�E���^�[
	int nPassCnt;			//�@�p�X���[�h�J�E���^�[

}GAME;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void SetGameState(GAMESTATE state);
void SetEnablePause(bool bPause);
GAMESTATE GetGameState(void);
GAME* GetGame(void);

bool GetSTClear(void);
bool GetACClear(void);
bool GetBallClear(void);
bool GetPassClear(void);


#endif
