//=============================================================================
//
// �^�C�g������ [title.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _TITLE_H_//���̃}�N����`������Ă��Ȃ�������
#define _TITLE_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�^�C�g���̎�ނ̍\����
typedef enum
{
	TITLE_FIRST=0,	//��ڂ̃^�C�g��
	TITLE_SECOND,	//��ڂ̃^�C�g��
	TITLE_TWO,		//�i���o�[

	TITLE_MAX
}TITLE;

//�^�C�g���̏��
typedef enum
{
	TITLE_NONE=0,	//�ʏ���
	TITLE_FLASH,	//�_�ŏ��
	STATE_MAX
}TITLESTATE;

//�v���g�^�C�v�錾
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

void SetTitle(int nType,D3DXVECTOR3 pos);//�^�C�g���̐ݒ�
void TitleFlash(int nType);//�^�C�g���̓_��

#endif

