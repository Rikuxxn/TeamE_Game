//=======================================
//
// �J��������[camera.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"

//�O���[�o���ϐ�
Camera g_camera;//�J�������
CAMERAMODE g_cameramode = CAMERAMODE_NORMAL;//���݂̃J�������[�h

bool bFirstPerson;

//=============================
//�J�����̏���������
//=============================
void InitCamera(void)
{
	MODE pMode = GetMode();

	//���_�E�����_�E�������ݒ肷��
	g_camera.posV = D3DXVECTOR3(0.0f, 280.0f, -20.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�Œ�ł���
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf(((g_camera.posV.x - g_camera.posR.x) * (g_camera.posV.x - g_camera.posR.x)) + ((g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y)) + ((g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z)));
	bFirstPerson = false;

	//// �r���[�|�[�g�\���̕ۑ�
	//g_camera.viewport.X = 0.0f;				//X�J�n�ʒu
	//g_camera.viewport.Y = 0.0f;				//Y�J�n�ʒu
	//g_camera.viewport.Width = 1280.0f;		//��
	//g_camera.viewport.Height = 720.0f;		//����
	//g_camera.viewport.MinZ = 0.0f;
	//g_camera.viewport.MaxZ = 1.0f;

}
//=============================
//�J�����̏I������
//=============================
void UninitCamera(void)
{


}
//=============================
//�J�����̍X�V����
//=============================
void UpdateCamera(void)
{
	MODE pMode = GetMode();

	Player* pPlayer = GetPlayer();

	float fAngleA = sqrtf(((g_camera.posR.x - pPlayer->pos.x) * (g_camera.posR.x - pPlayer->pos.x)) + ((g_camera.posR.y - pPlayer->pos.y) * (g_camera.posR.y - pPlayer->pos.y)) + ((g_camera.posR.z - pPlayer->pos.z) * (g_camera.posR.z - pPlayer->pos.z)));

	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	if (pMode == MODE_GAME)
	{
		//if (pStick != NULL) 
		//{
		//	// �E�X�e�B�b�N�̒l���擾
		//	float stickX = pStick->Gamepad.sThumbRX;
		//	float stickY = pStick->Gamepad.sThumbRY;

		//	// �f�b�h�]�[������
		//	const float DEADZONE = 10922.0f;
		//	if (fabsf(stickX) < DEADZONE)
		//	{
		//		stickX = 0.0f;
		//	}
		//	if (fabsf(stickY) < DEADZONE)
		//	{
		//		stickY = 0.0f;
		//	}

		//	// ���K��
		//	stickX /= 32768.0f;
		//	stickY /= 32768.0f;

		//	// �J������]�̍X�V
		//	RotateCameraWithGamepad(stickX, stickY);
		//}

		// �}�E�X�̏�Ԃ��擾
		DIMOUSESTATE mouseState;

		if (GetMouseState(&mouseState))
		{
			// �O�t���[���̃J�[�\���ʒu���L�^����ÓI�ϐ�
			static POINT prevCursorPos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

			// ���݂̃J�[�\���ʒu���擾
			POINT cursorPos;
			GetCursorPos(&cursorPos);

			// �ړ��ʂ��v�Z
			float deltaX = (float)(cursorPos.x - prevCursorPos.x);
			float deltaY = (float)(cursorPos.y - prevCursorPos.y);

			// �}�E�X���x��K�p
			const float mouseSensitivity = 0.0009f;
			deltaX *= mouseSensitivity;
			deltaY *= mouseSensitivity;

			// �J������]���X�V
			g_camera.rot.y += deltaX; // ������]
			g_camera.rot.x += deltaY; // ������]

			// ������]�̐���
			if (g_camera.rot.x > 0.72f)
			{
				g_camera.rot.x = 0.72f;
			}
			else if (g_camera.rot.x < -0.72f)
			{
				g_camera.rot.x = -0.72f;
			}

			// ������]�𐳋K��
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2.0f;
			}
			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2.0f;
			}

			// �J�[�\������ʒ����ɖ߂�
			SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

			// ���݂̃J�[�\���ʒu������̌v�Z�p�ɕۑ�
			prevCursorPos.x = SCREEN_WIDTH / 2;
			prevCursorPos.y = SCREEN_HEIGHT / 2;
		}

		// �J�����̈ʒu���v���C���[�̈ʒu�ɐݒ�
		g_camera.posV = pPlayer->pos;
		g_camera.posV.y += 70.0f; // �����̍���

		// �J�����̉�]�Ɋ�Â��Ē����_���v�Z
		float lookDistance = 10.0f; // �����_�܂ł̋���
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * lookDistance * cosf(g_camera.rot.x);
		g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x) * lookDistance;
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * lookDistance * cosf(g_camera.rot.x);

	}


	//if (g_cameramode == CAMERAMODE_NORMAL)
	//{
		if (pMode != MODE_EDIT)
		{
			g_camera.posRDest.x = pPlayer->pos.x - sinf(fAngleA) * PLAYER_SPEED;
			g_camera.posRDest.z = pPlayer->pos.z - cosf(fAngleA) * PLAYER_SPEED;

			g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y + D3DX_PI) * g_camera.fDistance;
			g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y + D3DX_PI) * g_camera.fDistance;

			g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.05f;
			g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.05f;

			g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.05f;
			g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.05f;
		}




		////�����_�̐���(X��)
		//else if (GetKeyboardPress(DIK_T))
		//{

		//	g_camera.rot.x -= 0.02f;

		//	//�p�x�̐��K��
		//	if (g_camera.rot.x > D3DX_PI)
		//	{
		//		g_camera.rot.x -= D3DX_PI * 2.0f;
		//	}

		//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		//	g_camera.posR.y = g_camera.posV.y + cosf(g_camera.rot.x) * g_camera.fDistance;
		//	g_camera.posR.z = g_camera.posV.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

		//}
		//else if (GetKeyboardPress(DIK_G))
		//{

		//	g_camera.rot.x += 0.02f;

		//	//�p�x�̐��K��
		//	if (g_camera.rot.x < -D3DX_PI)
		//	{
		//		g_camera.rot.x += D3DX_PI * 2.0f;
		//	}

		//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		//	g_camera.posR.y = g_camera.posV.y + cosf(g_camera.rot.x) * g_camera.fDistance;
		//	g_camera.posR.z = g_camera.posV.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

		//}

		////���_�̐���(X��)
		//else if (GetKeyboardPress(DIK_UP))
		//{

		//	//�p�x�̐��K��
		//	if (g_camera.rot.x < -D3DX_PI)
		//	{
		//		g_camera.rot.x += D3DX_PI * 2.0f;
		//	}
		//	else if (g_camera.rot.x > D3DX_PI)
		//	{
		//		g_camera.rot.x -= D3DX_PI * 2.0f;
		//	}

		//	if (g_camera.rot.x <= 3.0f)
		//	{

		//		g_camera.rot.x += 0.01f;

		//		g_camera.posV.x = g_camera.posR.z - sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		//		g_camera.posV.y = g_camera.posR.y - cosf(g_camera.rot.x) * g_camera.fDistance;
		//		g_camera.posV.z = g_camera.posR.x - sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

		//	}

		//}
		//else if (GetKeyboardPress(DIK_DOWN))
		//{

		//	//�p�x�̐��K��
		//	if (g_camera.rot.x < -D3DX_PI)
		//	{
		//		g_camera.rot.x += D3DX_PI * 2.0f;
		//	}
		//	else if (g_camera.rot.x > D3DX_PI)
		//	{
		//		g_camera.rot.x -= D3DX_PI * 2.0f;
		//	}

		//	if (g_camera.rot.x > D3DX_PI * 0.5f)
		//	{

		//		g_camera.rot.x -= 0.01f;

		//		g_camera.posV.x = g_camera.posR.z - sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
		//		g_camera.posV.y = g_camera.posR.y - cosf(g_camera.rot.x) * g_camera.fDistance;
		//		g_camera.posV.z = g_camera.posR.x - sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

		//	}

		//}
	//}
	// 
	
	// �G�f�B�^�[���[�h�ł̃J��������
	if (pMode == MODE_EDIT)
	{
		// �}�E�X�̏�Ԃ��擾
		DIMOUSESTATE mouseState;

		if (GetMouseState(&mouseState))
		{
			// ���݂̃J�[�\���ʒu���擾
			POINT cursorPos;
			GetCursorPos(&cursorPos);

			// �ړ��ʂ��v�Z
			static POINT prevCursorPos = { SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.5 };
			float deltaX = (float)(cursorPos.x - prevCursorPos.x);
			float deltaY = (float)(cursorPos.y - prevCursorPos.y);

			// �}�E�X���x
			const float mouseSensitivity = 0.002f;
			deltaX *= mouseSensitivity;
			deltaY *= mouseSensitivity;

			// �J�����̉�]���X�V
			g_camera.rot.y += deltaX; // ������]
			g_camera.rot.x += deltaY; // ������]

			// ������]�̐��� (-��/2 �` ��/2)
			if (g_camera.rot.x > D3DX_PI / 2)
			{
				g_camera.rot.x = D3DX_PI / 2;
			}
			else if (g_camera.rot.x < -D3DX_PI / 2)
			{
				g_camera.rot.x = -D3DX_PI / 2;
			}

			// �J�[�\������ʒ����ɖ߂�
			SetCursorPos(SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.5);
		}

		// WASD�L�[�ɂ��J�����̈ړ�
		const float cameraSpeed = 5.0f; // �ړ����x
		D3DXVECTOR3 forward, right;

		// �J�����̑O�������v�Z
		forward.x = -sinf(g_camera.rot.y);
		forward.z = -cosf(g_camera.rot.y);
		forward.y = 0.0f;

		D3DXVec3Normalize(&forward, &forward);

		// �J�����̉E�������v�Z
		right.x = forward.z;
		right.z = -forward.x;
		right.y = 0.0f;

		if (GetKeyboardPress(DIK_W))
		{
			g_camera.posV += forward * cameraSpeed;
		}
		if (GetKeyboardPress(DIK_S))
		{
			g_camera.posV -= forward * cameraSpeed;
		}
		if (GetKeyboardPress(DIK_A))
		{
			g_camera.posV -= right * cameraSpeed;
		}
		if (GetKeyboardPress(DIK_D))
		{
			g_camera.posV += right * cameraSpeed;
		}
		if (GetKeyboardPress(DIK_Z))
		{
			g_camera.posV.y += cameraSpeed; // �㏸
		}
		if (GetKeyboardPress(DIK_C))
		{
			g_camera.posV.y -= cameraSpeed; // ���~
		}

		// �����_�̍X�V
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y);
		g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x);
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y);
	}

	//if (KeyboardTrigger(DIK_F2) == true)
	//{
	//	if (g_cameramode == CAMERAMODE_NORMAL)
	//	{
	//		g_cameramode = CAMERAMODE_AUTO;
	//	}
	//	else if (g_cameramode == CAMERAMODE_AUTO)
	//	{
	//		g_cameramode = CAMERAMODE_NORMAL;
	//	}
	//}

	//if (KeyboardTrigger(DIK_F3) == true)
	//{
	//	if (g_cameramode == CAMERAMODE_NORMAL || g_cameramode == CAMERAMODE_AUTO)
	//	{
	//		g_cameramode = CAMERAMODE_AUTOTURN;
	//	}
	//	else if (g_cameramode == CAMERAMODE_AUTOTURN)
	//	{
	//		g_cameramode = CAMERAMODE_NORMAL;
	//	}
	//}


	//switch (g_cameramode)
	//{
	//case CAMERAMODE_NORMAL:
	//	break;

	//case CAMERAMODE_AUTO:

	//	//g_camera.posRDest.x = pPlayer->pos.x - sinf(fAngleA) * PLAYER_SPEED;
	//	//g_camera.posRDest.z = pPlayer->pos.z - cosf(fAngleA) * PLAYER_SPEED;

	//	//g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y + D3DX_PI) * g_camera.fDistance;
	//	//g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y + D3DX_PI) * g_camera.fDistance;

	//	//g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.05f;
	//	//g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.05f;

	//	//g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.05f;
	//	//g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.05f;

	//	break;

	//case CAMERAMODE_AUTOTURN:

	//	g_camera.rot.y -= 0.006f;

	//	//�p�x�̐��K��
	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y -= D3DX_PI * 2.0f;
	//	}
	//	else if (g_camera.rot.y < -D3DX_PI)
	//	{
	//		g_camera.rot.y += D3DX_PI * 2.0f;
	//	}

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;

	//	break;

	//default:

	//	break;
	//}


}
//=============================
//�J�����̐ݒ菈��
//=============================
void SetCamera(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),                  // ����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, // �A�X�y�N�g��
		1.0f,                                // �߃N���b�v��
		1100.0f);                            // ���N���b�v��

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

}
//=============================
//�Q�[���p�b�h�̃J������]����
//=============================
void RotateCameraWithGamepad(float stickX, float stickY)
{
	const float rotationSpeed = 0.07f; // ��]���x

	 // ���������̉�]�iY���j
	g_camera.rot.y += stickX * rotationSpeed;

	// ���������̉�]�iX���j
	g_camera.rot.x -= stickY * rotationSpeed;

	// ���������̉�]�𐧌� (-90�x �` 90�x)
	if (g_camera.rot.x > D3DX_PI / 2) 
	{
		g_camera.rot.x = D3DX_PI / 2;
	}
	if (g_camera.rot.x < -D3DX_PI / 2) 
	{
		g_camera.rot.x = -D3DX_PI / 2;
	}

	// ���������̉�]�𐳋K�� (-�� �` ��)
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}

}
//=================================
//�J�������̎擾
//=================================
Camera* GetCamera(void)
{
	return &g_camera;
}
//=============================================
//�J�������[�h�̎擾
//=============================================
CAMERAMODE* GetCameraMode(void)
{
	return &g_cameramode;
}
bool GetFirstPerson(void)
{
	return bFirstPerson;
}
