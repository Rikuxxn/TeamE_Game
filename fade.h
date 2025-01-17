//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"


//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE=0,      //�������Ă��Ȃ����
	FADE_IN,          //�t�F�[�h�C�����
	FADE_OUT,         //�t�F�[�h�A�E�g���
	FADE_FOUNDIN,
	FADE_FOUNDOUT,
	FADE_MAX

}FADE;

//�v���g�^�C�v�錾
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(MODE modeNext);
void SetFoundFade(MODE modeNext);
FADE GetFade(void);

#endif
