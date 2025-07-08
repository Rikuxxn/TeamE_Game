//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_GAMEBGM = 0,	// �Q�[��BGM
	SOUND_LABEL_GAMEOVERBGM,	// �Q�[���I�[�o�[BGM
	SOUND_LABEL_TITLEBGM,		// �^�C�g��BGM
	SOUND_LABEL_INSIGHT,		// �v���C���[�𔭌�
	SOUND_LABEL_ENEMYWANDERING,	// �G���p�j���Ă���Ƃ��̉�
	SOUND_LABEL_ENEMYATTACK,	// �G�̍U��
	SOUND_LABEL_ENEMYCAUGHT,	// �G�ɕ߂܂���
	SOUND_LABEL_ENEMYSTEP1,		// �G�̑���SE
	SOUND_LABEL_ENEMYSTEP2,		// �G�̑���SE2
	SOUND_LABEL_PLAYERSTEP1,	// ����SE
	SOUND_LABEL_PLAYERSTEP2,	// ����SE2
	SOUND_LABEL_HEART,			// �S��
	SOUND_LABEL_HEARTQUICK,		// �S��(��)
	SOUND_LABEL_BALLTUTO,		// �{�[���v�[���̃`���[�g���A������
	SOUND_LABEL_BALLFADE,		// �{�[���v�[���̃t�F�[�h
	SOUND_LABEL_BALLCATCH,		// �{�[����͂�
	SOUND_LABEL_BALLGET,		// �{�[������ɓ����
	SOUND_LABEL_BALLCLEAR,		// �{�[���v�[���N���A
	SOUND_LABEL_CRANEMOVE,		// �N���[���̈ړ�
	SOUND_LABEL_CRANEDOWN,		// �N���[����������
	SOUND_LABEL_CRANEUP,		// �N���[�����グ��
	SOUND_LABEL_CRANEGET,		// �i�i�Q�b�g
	SOUND_LABEL_DROPHINT,		// �q���g��������
	SOUND_LABEL_HINTWATCH,		// �q���g�̊m�F
	SOUND_LABEL_STSHOT,			// �V���[�e�B���O�ˌ�
	SOUND_LABEL_STHIT,			// �q�b�g��
	SOUND_LABEL_STDEAD,			// ���j��
	SOUND_LABEL_STCLEAR,		// �V���[�e�B���O�N���A
	SOUND_LABEL_PASSPUSH,		// �p�X���[�h����
	SOUND_LABEL_PASSWRONG,		// �p�X���[�h���Ⴄ
	SOUND_LABEL_PASSCORRECT,	// �p�X���[�h�������Ă���
	SOUND_LABEL_FUSEGET,		// �q���[�Y���Q�b�g
	SOUND_LABEL_FUSESET,		// �q���[�Y���Z�b�g
	SOUND_LABEL_EMPTYBREATH,	// ���؂�
	SOUND_LABEL_OPENDOOR,		// �h�A���J��
	SOUND_LABEL_TASKOK,			// �^�X�N����
	SOUND_LABEL_MENUOPEN,		// ���j���[�I�[�v��
	SOUND_LABEL_SELECT,			// �I��
	SOUND_LABEL_OK,				// ����
	SOUND_LABEL_RANK,			// ���U���g�̃����N�\��
	SOUND_LABEL_GAMESTART,		// �Q�[���X�^�[�g
	SOUND_LABEL_MINICLEAR,		// �~�j�Q�[���N���A

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
HRESULT PlaySound3D(SOUND_LABEL label);
void UpdateSoundPosition(SOUND_LABEL label, float x, float y, float z);
void CalculateCustomPanning(SOUND_LABEL label, FLOAT32* matrix);
void UpdateListener(float x, float y, float z);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif