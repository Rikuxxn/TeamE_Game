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
	g_camera.posV = D3DXVECTOR3(0.0f, 80.0f, -20.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�Œ�ł���
	g_camera.rot = D3DXVECTOR3(0.0f, -1.57f, 0.0f);
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
	FADE g_fade = GetFade(); // ���݂̏��
	Player* pPlayer = GetPlayer();
	Block* pBlock = GetBlock();
	Flags* pFlag = GetFlag();

	float fAngleA = sqrtf(((g_camera.posR.x - pPlayer->pos.x) * (g_camera.posR.x - pPlayer->pos.x)) + ((g_camera.posR.y - pPlayer->pos.y) * (g_camera.posR.y - pPlayer->pos.y)) + ((g_camera.posR.z - pPlayer->pos.z) * (g_camera.posR.z - pPlayer->pos.z)));

	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	if (pMode == MODE_GAME && pFlag->bExit == false)
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

	if (pMode == MODE_TITLE)
	{
		// �J�����̈ʒu���v���C���[�̈ʒu�ɐݒ�
		g_camera.posV = pPlayer->pos;
		g_camera.posV.y += 70.0f; // �����̍���

		// �J�����̉�]�Ɋ�Â��Ē����_���v�Z
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * cosf(g_camera.rot.x);
		g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x);
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * cosf(g_camera.rot.x);
	}

	
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
			static POINT prevCursorPos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			float deltaX = (float)(cursorPos.x - prevCursorPos.x);
			float deltaY = (float)(cursorPos.y - prevCursorPos.y);

			// �}�E�X���x
			const float mouseSensitivity = 0.002f;
			deltaX *= mouseSensitivity;
			deltaY *= mouseSensitivity;

			// �J�����̉�]���X�V
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
			SetCursorPos((int)SCREEN_WIDTH / 2, (int)SCREEN_HEIGHT / 2);
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
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * cosf(g_camera.rot.x);
		g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.x);
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * cosf(g_camera.rot.x);
	}

}
//=============================
//�J�����̐ݒ菈��
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
