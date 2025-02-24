//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "password_background.h"

//�}�N��
#define MAX_ITEM (12)										// �A�C�e���̍ő吔
#define NUM_ITEM (12)										// ���
#define ITEM_WIDTH (25.0f)									// ��
#define ITEM_HEIGHT (25.0f)									// ����
#define ITEM_MIN_SCALE (1.0f)								// �g�嗦
#define ITEM_POSX_LEFT (PASSWORDFIELD_LEFT + 38.0f)			// ����120.0f
#define ITEM_POSX_CENTER (ITEM_POSX_LEFT + 60.0f)			// ����
#define ITEM_POSX_RIGHT (ITEM_POSX_CENTER + 60.0f)			// �E��
#define ITEM_POSY_TOP (PASSWORDFIELD_UNDER - 230.0f)		// ��
#define ITEM_POSY_MIDDLE_UP (PASSWORDFIELD_UNDER - 170.0f)	// �^�񒆂���
#define ITEM_POSY_MIDDLE_DOWN (PASSWORDFIELD_UNDER - 110.0f)// �^�񒆂�艺
#define ITEM_POSY_UNDER (PASSWORDFIELD_UNDER - 50.0f)		// ��

typedef enum
{
	NUMTYPE_0 = 0,
	NUMTYPE_1,
	NUMTYPE_2,
	NUMTYPE_3,
	NUMTYPE_4,
	NUMTYPE_5,
	NUMTYPE_6,
	NUMTYPE_7,
	NUMTYPE_8,
	NUMTYPE_9,
	NUMTYPE_ENTER,
	NUMTYPE_DELETE,
	NUMTYPE_MAX
}NUMTYPE;

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	NUMTYPE type;		// �L�[�̎��
	float fWidth;		// ��
	float fHeight;		// ����
	int nType;			// �e�N�X�`���̎��
	bool bUse;			// �g�p���Ă��邩�ǂ���
	bool bGet;			// �擾�������ǂ���
	bool bcatch;		// �L���b�`������
}PASSWORDITEM;

//�v���g
void InitPasswordItem(void);
void UninitPasswordItem(void);
void UpdatePasswordItem(void);
void DrawPasswordItem(void);
void SetPasswordItem(D3DXVECTOR3 pos,float fWidth,float fHeight,int nType, NUMTYPE type);//�u���b�N�̐ݒu
PASSWORDITEM* GetItem(void);
bool GetJudgment(void);
bool GetReset(void);

#endif