//=======================================
//
//���b�V���V�����_�[����[meshcylinder.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MESHCYLINDER_H_//���̃}�N����`������Ă��Ȃ�������
#define _MESHCYLINDER_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_CYLINDER (5)					// �V�����_�[�̍ő吔

#define MESHCYLINDER_WIDTH (150.0f)			// ����
#define MESHCYLINDER_HEIGHT (120.0f)		// �c��

#define MESHCYLINDER_X (8)					// X�����̃u���b�N��
#define MESHCYLINDER_Z (1)					// Z�����̃u���b�N��

#define MESHCYLINDER_V (1)					// ���������̕�����
#define MESHCYLINDER_H (8)					// ���������̕�����

#define MESHCYLINDER_PRIMITIVE (((MESHCYLINDER_X * MESHCYLINDER_Z) * 2)) + (4 * (MESHCYLINDER_Z - 1))//�v���~�e�B�u��
#define MESHCYLINDER_VERTEX ((MESHCYLINDER_X + 1) * (MESHCYLINDER_Z + 1))//���_��
#define MESHCYLINDER_INDEX (MESHCYLINDER_PRIMITIVE + 2)//�C���f�b�N�X��

// ���b�V���V�����_�[�\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Cylinder;

//�v���g�^�C�v�錾
void InitMeshcylinder(void);
void UninitMeshcylinder(void);
void UpdateMeshcylinder(void);
void DrawMeshcylinder(void);
void SetMeshcylinder(D3DXVECTOR3 pos);

#endif
