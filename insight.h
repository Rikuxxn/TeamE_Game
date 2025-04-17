//=============================================================================
//
// ���E�G�t�F�N�g���� [insight.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _INSIGHT_H_//���̃}�N����`������Ă��Ȃ�������
#define _INSIGHT_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"


// �\����
typedef struct
{
	D3DXVECTOR3 pos;							// �ʒu
	D3DXCOLOR col;								// �F
	float fWidth;								// ��
	float fHeight;								// ����
	int nCounter;								// �J�E���^�[
	bool bUse;									// �g�p���Ă��邩�ǂ���
}Insight;

//�v���g�^�C�v�錾
void InitInsight(void);
void UninitInsight(void);
void UpdateInsight(void);
void DrawInsight(void);
void SetInsight(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);
Insight* GetInsight(void);

#endif