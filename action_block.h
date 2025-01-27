#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//�e�̎��
typedef enum
{
	BLOCKTYPE_PLAYER=0,//�v���C���[�̒e
	BLOCKTYPE_ENEMY,//�G�̒e
	BLOCKTYPE_MAX
}ACTIONBLOCKTYPE;

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
}ACTIONBLOCK;

//�v���g
void InitActionBlock(void);
void UninitActionBlock(void);
void UpdateActionBlock(void);
void DrawActionBlock(void);
void SetActionBlock(D3DXVECTOR3 pos,D3DXVECTOR3 move,float fWidth,float fHeight,int type);//�u���b�N�̐ݒu
bool CollisionActionBlock(D3DXVECTOR3 *pPos,D3DXVECTOR3 *pPosOld,D3DXVECTOR3 *pMove,float fWidth,float fHeight, ACTIONBLOCK**pBlock);
bool CollisionActionBlock2(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);

#endif