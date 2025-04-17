//=======================================
//
// �J�������� [camera.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "fade.h"
#include "block.h"
#include "enemy.h"

//�O���[�o���ϐ�
Camera g_camera;//�J�������
CAMERAMODE g_cameramode = CAMERAMODE_NORMAL;//���݂̃J�������[�h

// ���炩�ɕ�Ԃ��邽�߂̕�ԌW��
const float smoothFactor = 0.005f;

//=============================
// �J�����̏���������
//=============================
void InitCamera(void)
{
	MODE pMode = GetMode();

	//���_�E�����_�E�������ݒ肷��
	g_camera.posV = D3DXVECTOR3(0.0f, 80.0f, -540.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�Œ�ł���
	g_camera.rot = D3DXVECTOR3(0.0f, -1.57f, 0.0f);
	g_camera.fDistance = sqrtf(((g_camera.posV.x - g_camera.posR.x) * (g_camera.posV.x - g_camera.posR.x)) + ((g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y)) + ((g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z)));

	//// �r���[�|�[�g�\���̕ۑ�
	//g_camera.viewport.X = 0.0f;				//X�J�n�ʒu
	//g_camera.viewport.Y = 0.0f;				//Y�J�n�ʒu
	//g_camera.viewport.Width = 1280.0f;		//��
	//g_camera.viewport.Height = 720.0f;		//����
	//g_camera.viewport.MinZ = 0.0f;
	//g_camera.viewport.MaxZ = 1.0f;

}
//=============================
// �J�����̏I������
//=============================
void UninitCamera(void)
{


}
//=============================
// �J�����̍X�V����
//=============================
void UpdateCamera(void)
{
	MODE pMode = GetMode();
	Player* pPlayer = GetPlayer();

	// ���[�h���Ƃ̃J��������
	switch (pMode)
	{
	case MODE_GAME:
		GameCamera();
		break;
	case MODE_TITLE:
		TitleCamera();
		break;
	case MODE_EDIT:
		EditCamera();
		break;
	}
}
//=============================
// �J�����̐ݒ菈��
//=============================
void SetCamera(void)
{
	MODE pMode = GetMode();

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

	if (pMode == MODE_GAME)
	{
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
			D3DXToRadian(60.0f),						// ����p
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, // �A�X�y�N�g��
			1.0f,										// �߃N���b�v��
			2500.0f);									// ���N���b�v��
	}
	else
	{
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
			D3DXToRadian(45.0f),						// ����p
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, // �A�X�y�N�g��
			1.0f,										// �߃N���b�v��
			2500.0f);									// ���N���b�v��
	}

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

}
//=============================
// �Q�[���p�b�h�̃J������]����
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
//==================================
// ���[�h�Q�[�����̃J��������
//==================================
void GameCamera(void)
{
	MODE pMode = GetMode();
	Player* pPlayer = GetPlayer();
	Flags* pFlag = GetFlag();
	bool bEndMotion = GetEndMotion();
	XINPUT_STATE* pStick = GetJoyStickAngle();

	if (pFlag->bExit == false && bEndMotion == false)
	{
		// �}�E�X�̏�Ԃ��擾
		DIMOUSESTATE mouseState;

		// �Q�[���p�b�h�E�X�e�B�b�N�J��������
		if (pStick != NULL)
		{
			// �E�X�e�B�b�N�̒l���擾
			float stickX = pStick->Gamepad.sThumbRX;
			float stickY = pStick->Gamepad.sThumbRY;

			// �f�b�h�]�[������
			const float DEADZONE = 10922.0f;
			if (fabsf(stickX) < DEADZONE)
			{
				stickX = 0.0f;
			}
			if (fabsf(stickY) < DEADZONE)
			{
				stickY = 0.0f;
			}

			// ���K��
			stickX /= 32768.0f;
			stickY /= 32768.0f;

			// �J������]�̍X�V
			RotateCameraWithGamepad(stickX, stickY);
		}
		if (GetMouseState(&mouseState))
		{
			// �O�t���[���̃J�[�\���ʒu���L�^����ÓI�ϐ�
			static POINT prevCursorPos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };

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
			if (g_camera.rot.x > 1.40f)
			{
				g_camera.rot.x = 1.40f;
			}
			else if (g_camera.rot.x < -1.40f)
			{
				g_camera.rot.x = -1.40f;
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
			SetCursorPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

			// ���݂̃J�[�\���ʒu������̌v�Z�p�ɕۑ�
			prevCursorPos.x = SCREEN_WIDTH * 0.5f;
			prevCursorPos.y = SCREEN_HEIGHT * 0.5f;
		}

		// �J�����̈ʒu���v���C���[�̈ʒu�ɐݒ�
		g_camera.posV = pPlayer->pos;
		g_camera.posV.y += 75.0f; // �����̍���

		// �J�����̉�]�Ɋ�Â��Ē����_���v�Z
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * cosf(g_camera.rot.x);
		g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x);
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * cosf(g_camera.rot.x);

	}

	// �G�ɕ߂܂���
	if (pFlag->bExit == false && bEndMotion == true)
	{
		Enemy* pEnemy = GetEnemy();

		// �J�����̈ʒu�i�v���C���[�̎��_�����������j
		g_camera.posV = pPlayer->pos;
		g_camera.posV.y += 50.0f;  //  �����𒲐�

		// �G�̈ʒu�𒍎��_�̖ڕW�l�ɂ���
		D3DXVECTOR3 targetPosR = pEnemy->pos;
		targetPosR.y += 100.0f;  // �����𒲐�

		// �G�̕����x�N�g�����v�Z
		D3DXVECTOR3 direction = targetPosR - g_camera.posV;
		D3DXVec3Normalize(&direction, &direction);

		// �ڕW��]�p�x���v�Z
		float targetRotY = atan2f(direction.x, direction.z);
		float targetRotX = -atan2f(direction.y, sqrtf(direction.x * direction.x + direction.z * direction.z));

		// ���݂̉�]�ƖڕW��]����
		g_camera.rot.y += (targetRotY - g_camera.rot.y) * smoothFactor;
		g_camera.rot.x += (targetRotX - g_camera.rot.x) * smoothFactor;

		// �����_�����炩�ɕ��
		g_camera.posR.x += (targetPosR.x - g_camera.posR.x) * smoothFactor;
		g_camera.posR.y += (targetPosR.y - g_camera.posR.y) * smoothFactor;
		g_camera.posR.z += (targetPosR.z - g_camera.posR.z) * smoothFactor;
	}
}
//==================================
// ���[�h�^�C�g�����̃J��������
//==================================
void TitleCamera(void)
{
	Player* pPlayer = GetPlayer();

	// �J�����̈ʒu���v���C���[�̈ʒu�ɐݒ�
	g_camera.posV = pPlayer->pos;
	g_camera.posV.y += 70.0f; // �����̍���

	// �J�����̉�]�Ɋ�Â��Ē����_���v�Z
	g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * cosf(g_camera.rot.x);
	g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x);
	g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * cosf(g_camera.rot.x);
}
//==================================
// ���[�h�G�f�B�b�g���̃J��������
//==================================
void EditCamera(void)
{
	// �}�E�X�̏�Ԃ��擾
	DIMOUSESTATE mouseState;

	if (GetMouseState(&mouseState))
	{
		// ���݂̃J�[�\���ʒu���擾
		POINT cursorPos;
		GetCursorPos(&cursorPos);

		// �O�t���[������̃}�E�X�ړ��ʂ��擾
		static POINT prevCursorPos = { cursorPos.x, cursorPos.y };
		float deltaX = (float)(cursorPos.x - prevCursorPos.x);
		float deltaY = (float)(cursorPos.y - prevCursorPos.y);

		// ���݂̃J�[�\���ʒu��ۑ��i���̃t���[���ł̔�r�p�j
		prevCursorPos = cursorPos;

		// �}�E�X���x
		const float mouseSensitivity = 0.004f;
		deltaX *= mouseSensitivity;
		deltaY *= mouseSensitivity;

		if (GetKeyboardPress(DIK_LALT) && GetMouseButtonPress(0)) // ���N���b�N�����Ȃ���}�E�X�ړ� �� ���_��]
		{
			g_camera.rot.y += deltaX; // ������]
			g_camera.rot.x += deltaY; // ������]

			//�p�x�̐��K��
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2.0f;
			}

			// ������]�̐���
			if (g_camera.rot.x > 1.57f)
			{
				g_camera.rot.x = 1.57f;
			}
			if (g_camera.rot.x < -1.57f)
			{
				g_camera.rot.x = -1.57f;
			}

			// ���_�̍X�V�i�J�����̕�����K�p�j
			g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posV.y = g_camera.posR.y + sinf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;

		}
		else if (GetMouseButtonPress(1)) // �E�N���b�N�����Ȃ���}�E�X�ړ� �� �����_��]
		{
			g_camera.rot.y += deltaX; // ������]
			g_camera.rot.x += deltaY; // ������]

			//�p�x�̐��K��
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2.0f;
			}

			// ������]�̐���
			if (g_camera.rot.x > 1.57f)
			{
				g_camera.rot.x = 1.57f;
			}
			if (g_camera.rot.x < -1.57f)
			{
				g_camera.rot.x = -1.57f;
			}

			// �����_�̍X�V
			g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;

		}
	}

	// �����_�̍X�V
	g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;
	g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x) * g_camera.fDistance;
	g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;
}
//=================================
// �J�������̎擾
//=================================
Camera* GetCamera(void)
{
	return &g_camera;
}
//=============================================
// �J�������[�h�̎擾
//=============================================
CAMERAMODE* GetCameraMode(void)
{
	return &g_cameramode;
}