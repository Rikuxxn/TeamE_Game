//=============================================================================
//
// �C�[�W���O���� [easing.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _EASING_H_//���̃}�N����`������Ă��Ȃ�������
#define _EASING_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

// �C�[�W���O�̎��
typedef enum
{
	EASE_INEXPO = 0,
	EASE_OUTEXPO,
	EASE_INOUTEXPO,
	EASE_MAX
}EasingType;

float ease(float t, float start, float end, float duration, EasingType type);


#endif