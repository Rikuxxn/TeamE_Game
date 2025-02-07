//=======================================
//
// ���b�V���V�[�����O����[meshceiling.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MESHCEILING_H_//���̃}�N����`������Ă��Ȃ�������
#define _MESHCEILING_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_WIDTH_CEILING (2400.0f)																	// ����
#define MAX_HEIGHT_CEILING (2000.0f)																// �c��

#define MESHCEILING_X (20)																			// X�����̃u���b�N��
#define MESHCEILING_Z (20)																			// Z�����̃u���b�N��

#define MAX_PRIMITIVE_CEILING (((MESHCEILING_X * MESHCEILING_Z) * 2)) + (4 * (MESHCEILING_Z - 1))	// �v���~�e�B�u��
#define MAX_VERTEX_CEILING ((MESHCEILING_X + 1) * (MESHCEILING_Z + 1))								// ���_��
#define MAX_INDEX_CEILING (MAX_PRIMITIVE_CEILING + 2)												// �C���f�b�N�X��

//�v���g�^�C�v�錾
void InitMeshCeiling(void);
void UninitMeshCeiling(void);
void UpdateMeshCeiling(void);
void DrawMeshCeiling(void);

#endif
