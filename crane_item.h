#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//�}�N��
#define MAX_ITEM (4)								//�A�C�e���̍ő吔
#define NUM_ITEM (4)								//�A�C�e���̎��
#define ITEM_WIDTH (20.0f)							//�A�C�e���̕�
#define ITEM_HEIGHT (15.0f)							//�A�C�e���̍���
#define ITEM_CLEARZONE (50.0f)						//�A�C�e���͈̔�
#define ITEM_CLEARPOSX (CLANEFIELD_LEFT + 120.0f)	//�A�C�e���̏ꏊ(X)
#define ITEM_CLEARPOSY (CLANEFIELD_UNDER - 40.0f)	//�A�C�e���̏ꏊ(Y)

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	float fWidth;		//��
	float fHeight;		//����
	int nType;			//�e�N�X�`���̎��
	bool bUse;			//�g�p���Ă��邩�ǂ���
	bool bGet;			//�擾�������ǂ���
	bool bcatch;		//�L���b�`������
	//bool bDisp;			//�\�����邩
}CRANEITEM;

//�v���g
void InitCraneItem(void);
void UninitCraneItem(void);
void UpdateCraneItem(void);
void DrawCraneItem(void);
void SetCraneItem(D3DXVECTOR3 pos,float fWidth,float fHeight,int type);//�u���b�N�̐ݒu
int GetNumItem(void);
CRANEITEM GetItem(void);
bool CollisionCraneItem(D3DXVECTOR3 *pPos,D3DXVECTOR3 *pPosOld,D3DXVECTOR3 *pMove,float fWidth,float fHeight);;

#endif