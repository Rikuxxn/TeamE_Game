#ifndef _ITEM_H_
#define _ITEM_H_

#include "ball_game.h"

// �}�N��
#define MAX_ITEM (16)							// �A�C�e���̍ő吔
#define NUM_ITEM (4)							// �A�C�e���̎��
#define ITEM_WIDTH (25.0f)						// �A�C�e���̕�
#define ITEM_HEIGHT (25.0f)						// �A�C�e���̍���
#define ITEM_CLEARZONEX (75.0f)					// �ЂÂ���͈̔�(X)
#define ITEM_CLEARZONEY (50.0f)					// �ЂÂ���͈̔�(Y)
#define ITEM_CLEARPOSX (BALLPOS + 100.0f)		// �A�C�e���̏ꏊ(X)
#define ITEM_CLEARPOSY (BALLFIELD_UNDER - 30.0f)// �A�C�e���̏ꏊ(Y)
#define ITEM_MIN_SCALE (1.0f)					// �A�C�e���̊g�嗦


// �A�C�e���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	float fWidth;			// ��
	float fHeight;			// ����
	int nType;				// �e�N�X�`���̎��
	bool bUse;				// �g�p���Ă��邩�ǂ���
	bool bGet;				// �擾�������ǂ���
	bool bcatch;			// �L���b�`������
	D3DXVECTOR3 dragOffset;	// �}�E�X���������ʒu�̃I�t�Z�b�g
}BALLITEM;

//�v���g
void InitBallItem(void);
void UninitBallItem(void);
void UpdateBallItem(void);
void DrawBallItem(void);
void SetBallItem(D3DXVECTOR3 pos,float fWidth,float fHeight,int type);// �A�C�e���̐ݒu
int GetNumBallItem(void);

#endif