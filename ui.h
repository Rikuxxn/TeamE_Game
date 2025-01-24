//=============================================================================
//
// UI���� [ui.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _UI_H_//���̃}�N����`������Ă��Ȃ�������
#define _UI_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_UI (28)      // UI�̍ő吔

// UI�̎��
typedef enum
{
	UITYPE_GAME=0,
	UITYPE_INTERACT,
	UITYPE_INPUT,
	UITYPE_MAX
}UITYPE;


// UI�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	float fWidth;			// UI�̕�
	float fHeight;			// UI�̍���
	int nType;				// UI�̎��
	bool bUse;				// �g�p���Ă��邩�ǂ���
}UI;

static const char* UI_TEXTURE[UITYPE_MAX] =	// UI�̃e�N�X�`���̐ݒ�
{
	"data/TEXTURE/.x",// �~�j�Q�[��
	"data/TEXTURE/.x",// �E��
	"data/TEXTURE/.x",// ���͂���

};

//�v���g�^�C�v�錾
void InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);
void SetUI(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);


#endif