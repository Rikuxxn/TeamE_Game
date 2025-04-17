//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "meshfield.h"
#include "meshceiling.h"
#include "camera.h"
#include "light.h"
#include "block.h"
#include "edit.h"
#include "player.h"
#include "main.h"
#include "ui.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TITLE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureTitleBG = NULL;				//�e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleBG = NULL;			//���_�o�b�t�@�ւ̃|�C���^

TITLE_MENU g_titleMenu;										//�|�[�Y���j���[
bool g_bSelect;												//�I�΂�Ă��邩

// �^�C�g�����ڂ̊g�嗦���Ǘ�����z��
float titleScales[MAX_TITLE] = { TITLE_MIN_SCALE, TITLE_MIN_SCALE };

// ���ڂ��Ƃ̓����x��ێ�����z��
float titleAlphas[MAX_TITLE] = { 0.3f, 0.3f };				// �����͑S�Ĕ������i�͈͊O��ԁj

HWND hWnd;

//========================
// �^�C�g���̏�����
//========================
void InitTitle(void)
{
	Player* pPlayer = GetPlayer();

	// �J�[�\����\������
	SetCursorVisibility(true);

	// ���b�V���t�B�[���h�̏���������
	InitMeshfield();

	// ���b�V���V�[�����O�̏���������
	InitMeshCeiling();

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �u���b�N�̏���������
	InitBlock();

	// �v���C���[�̏���������
	InitPlayer();

	// �G�f�B�b�g�ǂݍ���
	LoadParticular(PATH_TITLE);


	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ���C�g�̎��
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),    // �Â߂̔�����
		D3DXVECTOR3(0.0f, -1.0f, 0.0f),       // �^������
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // �V��̈ʒu�i���������j
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ���C�g�̎��
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),    // �Â߂̔�����
		D3DXVECTOR3(-1.0f, 0.0f, 0.0f),       // ������
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // �V��̈ʒu�i���������j
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ���C�g�̎��
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),    // �Â߂̔�����
		D3DXVECTOR3(0.0f, 0.0f, -1.0f),       // ��O����
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // �V��̈ʒu�i���������j
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ���C�g�̎��
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),    // �Â߂̔�����
		D3DXVECTOR3(1.0f, 0.0f, 0.0f),       // �E����
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // �V��̈ʒu�i���������j
	);

	AddLight(
		D3DLIGHT_DIRECTIONAL,                  // ���C�g�̎��
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),    // �Â߂̔�����
		D3DXVECTOR3(0.0f, 0.0f, 1.0f),       // ������
		D3DXVECTOR3(0.0f, 260.0f, 0.0f)       // �V��̈ʒu�i���������j
	);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int title = 0; title < MAX_TITLE; title++)
	{
		D3DXCreateTextureFromFile(pDevice,
			TITLE_TEXTURE[title],
			&g_apTextureTitle[title]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	int nCntTitle;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(500.0f, (150.0f + nCntTitle * 150), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f, (150.0f + nCntTitle * 150), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, (250.0f + nCntTitle * 150), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, (250.0f + nCntTitle * 150), 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	g_titleMenu = TITLE_MENU_START;
	g_bSelect = false;
	PlaySound(SOUND_LABEL_TITLEBGM);
}
//========================
// �^�C�g���̏I��
//========================
void UninitTitle(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); // ���O�ɍ쐬�E����������Ă���f�o�C�X

	// ���̖�����
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//���b�V���t�B�[���h�̏I������
	UninitMeshfield();

	//���b�V���V�[�����O�̏I������
	UninitMeshCeiling();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//�u���b�N�̏I������
	UninitBlock();

	//�v���C���[�̏I������
	UninitPlayer();

	//�T�E���h�̒�~
	StopSound(SOUND_LABEL_TITLEBGM);

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureTitle[nCnt] != NULL)
		{
			g_apTextureTitle[nCnt]->Release();
			g_apTextureTitle[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}
//========================
// �^�C�g���̍X�V
//========================
void UpdateTitle(void)
{

	//���b�V���t�B�[���h�̍X�V����
	UpdateMeshfield();

	//���b�V���V�[�����O�̍X�V����
	UpdateMeshCeiling();

	//�J�����̍X�V����
	UpdateCamera();

	////���C�g�̍X�V����
	//UpdateLight(0, D3DXVECTOR3(0.0f, -1.0f, 0.0f));

	// ���C�g�̓_�ōX�V����
	UpdateLightBlinking(0.016f);

	////�u���b�N�̍X�V����
	//UpdateBlock();

	FADE g_fade = GetFade(); // ���݂̏��

	VERTEX_2D* pVtx;

	// �}�E�X�J�[�\���̈ʒu���擾
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	// �E�B���h�E�n���h�����擾
	HWND hwnd = GetActiveWindow();

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�
	ScreenToClient(hwnd, &cursorPos);

	// �N���C�A���g�T�C�Y���擾
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	// �E�B���h�E�X�P�[�����v�Z
	float screenWidth = 1280.0f; // �Q�[���̉𑜓x
	float screenHeight = 720.0f;
	float scaleX = screenWidth / (clientRect.right - clientRect.left);
	float scaleY = screenHeight / (clientRect.bottom - clientRect.top);

	// �}�E�X���W���X�P�[��
	float mouseX = cursorPos.x * scaleX;
	float mouseY = cursorPos.y * scaleY;

	// �Q�[���p�b�h�Ń}�E�X�J�[�\���𓮂���
	UpdateCursorWithGamepad();

	// �}�E�X�J�[�\�����������Ă��鍀�ڂ�T��
	int selectedByMouse = -1; // -1�͖��I��

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		float scale = titleScales[nCnt];
		float centerX = 1060.0f; // ���SX���W
		float centerY = 450.0f + nCnt * 120.0f; // ���SY���W

		// �̈�̌v�Z
		float left = centerX - 150.0f * scale;
		float right = centerX + 150.0f * scale;
		float top = centerY - 30.0f * scale;
		float bottom = centerY + 30.0f * scale;

		// �͈͓�����
		if (mouseX >= left && mouseX <= right &&
			mouseY >= top && mouseY <= bottom)
		{
			selectedByMouse = nCnt; // ���ڂ̃C���f�b�N�X���L�^
			g_titleMenu = (TITLE_MENU)(nCnt); // �I����Ԃ��X�V
		}
	}

	// ���ڂ̓����x���X�V
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (selectedByMouse == -1)
		{
			// �͈͊O�Ȃ炷�ׂĔ�����
			titleAlphas[nCnt] -= 0.1f; // ���X�ɔ���
			if (titleAlphas[nCnt] < 0.3f) titleAlphas[nCnt] = 0.3f;
			else
			{
				g_bSelect = false;
			}
		}
		else if (nCnt == g_titleMenu)
		{
			// �I�𒆂̍��ڂ͔Z��
			titleAlphas[nCnt] += 0.1f; // ���X�ɔZ��
			if (titleAlphas[nCnt] > 1.0f)
			{
				titleAlphas[nCnt] = 1.0f;
			}
			if (g_bSelect == false)
			{
				PlaySound(SOUND_LABEL_SELECT);
				g_bSelect = true;
			}
		}
		else
		{
			// ��I���̍��ڂ͔���
			titleAlphas[nCnt] -= 0.1f; // ���X�ɔ���

			if (titleAlphas[nCnt] < 0.3f)
			{
				titleAlphas[nCnt] = 0.3f;
			}
		}
	}

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// ���ڂ̕`��ݒ�
	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		float scale = titleScales[nCntTitle];
		float centerX = 1060.0f;
		float centerY = 450.0f + nCntTitle * 120.0f;

		// ���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(centerX - 150.0f * scale, centerY - 30.0f * scale, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(centerX + 150.0f * scale, centerY - 30.0f * scale, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(centerX - 150.0f * scale, centerY + 30.0f * scale, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(centerX + 150.0f * scale, centerY + 30.0f * scale, 0.0f);

		// �J���[�ݒ�
		D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, titleAlphas[nCntTitle]);

		// ���_�J���[��ݒ�
		for (int nCntTitle2 = 0; nCntTitle2 < 4; nCntTitle2++)
		{
			pVtx[nCntTitle2].col = color;
		}

		// ���_�|�C���^�����̍��ڂɐi�߂�
		pVtx += 4;
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitle->Unlock();

	// �͈͓��N���b�N�̏ꍇ�̂ݏ��������s
	if (g_fade == FADE_NONE && (GetMouseButtonTrigger(0) || JoyPadTrigger(JOYKEY_A) == true))
	{
		if (selectedByMouse != -1)
		{
			// �͈͓��̍��ڂ��N���b�N���ꂽ�ꍇ
			switch (g_titleMenu)
			{
			case TITLE_MENU_START:

				// �Q�[����ʂɈڍs
				SetFade(MODE_TUTORIAL);
				PlaySound(SOUND_LABEL_GAMESTART);
				break;

			case TITLE_MENU_QUIT:

				//���C�g�̏I������
				UninitLight();

				//�E�B���h�E��j������
				PostQuitMessage(0);

				break;
			}
		}
		// �͈͊O���N���b�N�����ꍇ�͉������Ȃ�
	}


#ifdef _DEBUG
	if (KeyboardTrigger(DIK_F1) == true && g_fade == FADE_NONE)
	{
		//�G�f�B�b�g��ʂɈڍs
		SetFade(MODE_EDIT);
	}
#endif
}
//========================
// �^�C�g���̕`��
//========================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice; // ���O�ɍ쐬�E����������Ă���f�o�C�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	SetupVertexFog(pDevice, D3DCOLOR_XRGB(0, 0, 0), D3DFOG_LINEAR, TRUE, 0.0f);

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�J�����̐ݒ菈��
	SetCamera();

	//���b�V���t�B�[���h�̕`�揈��
	DrawMeshfield();

	//���b�V���V�[�����O�̕`�揈��
	DrawMeshCeiling();

	//�u���b�N�̕`�揈��
	DrawBlock();

	int nCntTitle;

	// ���̖�����
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureTitle[nCntTitle]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}

	// ���̗L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}
