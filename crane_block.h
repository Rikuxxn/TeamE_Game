#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

// �e�̎��
typedef enum
{
	BLOCKTYPE_PLAYER=0,	// �v���C���[�̒e
	BLOCKTYPE_ENEMY,	// �G�̒e
	BLOCKTYPE_MAX
}CRANEBLOCKTYPE;

// �e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// ����
	float fWidth;		// ��
	float fHeight;		// ����
	int nType;			// �e�N�X�`���̎��
	bool bUse;			// �g�p���Ă��邩�ǂ���
	int nMoveCnt;		// �����J�E���^�[
}CRANEBLOCK;

// �v���g
void InitCraneBlock(void);
void UninitCraneBlock(void);
void UpdateCraneBlock(void);
void DrawCraneBlock(void);
void SetCraneBlock(D3DXVECTOR3 pos,D3DXVECTOR3 move,float fWidth,float fHeight,int type);// �u���b�N�̐ݒu
CRANEBLOCK* GetBlock(void);

#endif