//=============================================================================
//
// �^�X�N���� [task.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _TASK_H_
#define _TASK_H_

#include "main.h"

// �}�N����`
#define MAX_TASK (256)      //�^�X�NUI�̍ő吔

//�^�X�NUI�̎��
typedef enum
{
	TASKTYPE_ONE = 0,
	TASKTYPE_TWO,
	TASKTYPE_THREE,

	TASKTYPE_MAX
}TASKTYPE;


//�^�X�N�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�^�X�N�̈ʒu
	D3DXVECTOR3 move;	//�^�X�N�̈ړ���
	float fWidth;		//�^�X�N�̕�
	float fHeight;		//�^�X�N�̍���
	int nType;			//�^�X�N�̎��
	bool bUse;
}TASK;


static const char* TASK_TEXTURE[TASKTYPE_MAX] =		// �^�X�N�̃e�N�X�`���̐ݒ�
{
	"data\\TEXTURE\\mission1.png",			//1
	"data\\TEXTURE\\mission2.png",			//1
	"data\\TEXTURE\\mission3.png",			//1

};

// �v���g�^�C�v�錾
void InitTask(void);
void UninitTask(void);
void UpdateTask(void);
void DrawTask(void);
void SetTask(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);


#endif