//=======================================
//
// �J��������[camera.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _CAMERA_H_//���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_CAMERA (2)			// �J�����̌�

//�J�������[�h�̎��
typedef enum
{
	CAMERAMODE_NORMAL = 0,		// �m�[�}���J����
	CAMERAMODE_AUTO,			// �J�����Ǐ]
	CAMERAMODE_AUTOTURN,		// ���_������]
	CAMERAMODE_FIRSTPERSON,		// ��l�̃��[�h
	CAMERAMODE_MAX
}CAMERAMODE;

//�J�����\����
typedef struct
{
	D3DXVECTOR3 posV;			// ���_
	D3DXVECTOR3 posVDest;		// �ړI�̎��_
	D3DXVECTOR3 posR;			// �����_
	D3DXVECTOR3 posRDest;		// �ړI�̒����_
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DXVECTOR3 rot;			// ����
	float fDistance;			// ���_���璍���_�̋���
	D3DVIEWPORT9 viewport;		// �r���[�|�[�g
}Camera;

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
void RotateCameraWithGamepad(float stickX, float stickY);
Camera* GetCamera(void);
CAMERAMODE* GetCameraMode(void);
bool GetFirstPerson(void);

#endif

