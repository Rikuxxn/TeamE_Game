#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//�e�̎��
typedef enum
{
	BLOCKTYPE_PLAYER=0,	//�v���C���[�̒e
	BLOCKTYPE_ENEMY,	//�G�̒e
	BLOCKTYPE_MAX
}BALLBLOCKTYPE;

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//����
	float fWidth;		//��
	float fHeight;		//����
	int nType;			//�e�N�X�`���̎��
	bool bUse;			//�g�p���Ă��邩�ǂ���
	int nMoveCnt;		//�����J�E���^�[
}BALLBLOCK;

//�v���g
void InitBallBlock(void);
void UninitBallBlock(void);
void UpdateBallBlock(void);
void DrawBallBlock(void);
void SetBallBlock(D3DXVECTOR3 pos,D3DXVECTOR3 move,float fWidth,float fHeight,int type);//�u���b�N�̐ݒu
BALLBLOCK* GetBlock(void);

#endif