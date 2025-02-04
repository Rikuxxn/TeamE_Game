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
	
	TASKTYPE_SUB1,
	TASKTYPE_SUB2,
	TASKTYPE_SUB1_CMP,
	TASKTYPE_SUB2_CMP,

	TASKTYPE_SUB3,
	TASKTYPE_SUB4,
	TASKTYPE_SUB5,
	TASKTYPE_SUB3_CMP,
	TASKTYPE_SUB4_CMP,
	TASKTYPE_SUB5_CMP,

	TASKTYPE_SUB6,
	TASKTYPE_SUB6_CMP,

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
	"data\\TEXTURE\\mission1.png",			// ���C���~�b�V����1
	"data\\TEXTURE\\mission2.png",			// ���C���~�b�V����2
	"data\\TEXTURE\\mission3.png",			// ���C���~�b�V����3

	"data\\TEXTURE\\Task1.png",				// �T�u�~�b�V����1 (�q���[�Y��������)
	"data\\TEXTURE\\Task2.png",				// �T�u�~�b�V����2 (�q���[�Y��z�d�Ղɕt����)
	"data\\TEXTURE\\TaskC1.png",			// �T�u�~�b�V����1 ���� (�q���[�Y��������)
	"data\\TEXTURE\\TaskC2.png",			// �T�u�~�b�V����2 ���� (�q���[�Y��z�d�Ղɕt����)

	"data\\TEXTURE\\Task3.png",				// �T�u�~�b�V����3 (�N���[���Q�[���𒲂ׂ�)
	"data\\TEXTURE\\Task4.png",				// �T�u�~�b�V����4 (�A�[�P�[�h�Q�[���𒲂ׂ�)
	"data\\TEXTURE\\Task5.png",				// �T�u�~�b�V����5 (�{�[���v�[���𒲂ׂ�)
	"data\\TEXTURE\\TaskC3.png",			// �T�u�~�b�V����3 ���� (�N���[���Q�[���𒲂ׂ�)
	"data\\TEXTURE\\TaskC4.png",			// �T�u�~�b�V����4 ���� (�A�[�P�[�h�Q�[���𒲂ׂ�)
	"data\\TEXTURE\\TaskC5.png",			// �T�u�~�b�V����5 ���� (�{�[���v�[���𒲂ׂ�)

	"data\\TEXTURE\\Task6.png",				// �T�u�~�b�V����6 (�Ïؔԍ�����͂���)
	"data\\TEXTURE\\TaskC6.png",			// �T�u�~�b�V����6 ���� (�Ïؔԍ�����͂���)

};

// �v���g�^�C�v�錾
void InitTask(void);
void UninitTask(void);
void UpdateTask(void);
void DrawTask(void);
void SetTask(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);

#endif