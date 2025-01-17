//=======================================
//
//���b�V���t�B�[���h����[meshfield.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MESHFIELD_H_//���̃}�N����`������Ă��Ȃ�������
#define _MESHFIELD_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

////���b�V���t�B�[���h�\����
//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 rot;
//}MeshField;

#define MAX_WIDTH (2400.0f)			//����
#define MAX_HEIGHT (2000.0f)		//�c��

#define MESHFIELD_X (20)			//X�����̃u���b�N��
#define MESHFIELD_Z (20)			//Z�����̃u���b�N��

#define MAX_PRIMITIVE (((MESHFIELD_X * MESHFIELD_Z) * 2)) + (4 * (MESHFIELD_Z - 1))//�v���~�e�B�u��
#define MAX_VERTEX ((MESHFIELD_X + 1) * (MESHFIELD_Z + 1))//���_��
#define MAX_INDEX (MAX_PRIMITIVE + 2)//�C���f�b�N�X��

//�v���g�^�C�v�錾
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

#endif
