#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//�e�̎��
typedef enum
{
	ITEMTYPE_PLAYER=0,//�v���C���[�̒e
	ITEMTYPE_ENEMY,//�G�̒e
	ITEMTYPE_MAX
}ACTIONITEMTYPE;

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	float fWidth;	//��
	float fHeight;	//����
	int nType;		//�e�N�X�`���̎��
	bool bUse;		//�g�p���Ă��邩�ǂ���
	bool bGet;		//�擾�������ǂ���
	bool bDisp;		//�\�����邩
}ACTIONITEM;

//�v���g
void InitActionItem(void);
void UninitActionItem(void);
void UpdateActionItem(void);
void DrawActionItem(void);
void SetActionItem(D3DXVECTOR3 pos,float fWidth,float fHeight,int type);//�u���b�N�̐ݒu
bool CollisionActionItem(D3DXVECTOR3 *pPos,D3DXVECTOR3 *pPosOld,D3DXVECTOR3 *pMove,float fWidth,float fHeight);;
bool GetActionItem(void);

#endif