//=============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "pause.h"
#include "main.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTexturePause[MAX_PAUSE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTexturePauseBG = NULL;				//�e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseBG = NULL;			//���_�o�b�t�@�ւ̃|�C���^

PAUSE_MENU g_pauseMenu;										//�|�[�Y���j���[
bool g_bPauseSelect;										//�I�΂�Ă��邩
bool g_bTutoDraw;											//�`���[�g���A���`��p
bool g_bDraw;												// 

// �|�[�Y���ڂ̊g�嗦���Ǘ�����z��
float pauseScales[MAX_PAUSE] = { PAUSE_MIN_SCALE, PAUSE_MIN_SCALE, PAUSE_MIN_SCALE, PAUSE_MIN_SCALE };

// ���ڂ��Ƃ̓����x��ێ�����z��
float pauseAlphas[MAX_PAUSE] = { 0.3f, 0.3f, 0.3f, 0.3f};		// �����͑S�Ĕ������i�͈͊O��ԁj

//===============================================================
// �|�[�Y�̏���������
//===============================================================
void InitPause(void)
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntPause;
	g_bTutoDraw = false;
	g_bDraw = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\.png",
		&g_apTexturePauseBG);

	for (int i = 0; i < MAX_PAUSE; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			PAUSE_TEXTURE[i],
			&g_apTexturePause[i]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG,
		NULL);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);


	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//1�ڂ̒��_���
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);		//2�ڂ̒��_���
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);		//3�ڂ̒��_���
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);	//4�ڂ̒��_���

	//rhw�̐ݒ�(1.0f�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseBG->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(500.0f, (150.0f + nCntPause * 150), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f, (150.0f + nCntPause * 150), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, (250.0f + nCntPause * 150), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, (250.0f + nCntPause * 150), 0.0f);

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
	g_pVtxBuffPause->Unlock();

	g_pauseMenu = PAUSE_MENU_CONTINUE;

}
//===============================================================
// �|�[�Y�̏I������
//===============================================================
void UninitPause(void)
{

	StopSound(SOUND_LABEL_SELECT);
	StopSound(SOUND_LABEL_OK);

	//�e�N�X�`���̔j��
	if (g_apTexturePauseBG != NULL)
	{
		g_apTexturePauseBG->Release();
		g_apTexturePauseBG = NULL;
	}

	int nCnt;

	for (nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_apTexturePause[nCnt] != NULL)
		{
			g_apTexturePause[nCnt]->Release();
			g_apTexturePause[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();
		g_pVtxBuffPauseBG = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

}
//===============================================================
// �|�[�Y�̍X�V����
//===============================================================
void UpdatePause(void)
{
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

	// �}�E�X�J�[�\�����������Ă��鍀�ڂ�T��
	int selectedByMouse = -1; // -1�͖��I��

	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++) 
	{
		float scale = pauseScales[nCnt];
		float centerX = 660.0f;					// ���SX���W
		float centerY = 180.0f + nCnt * 150.0f; // ���SY���W

		// �̈�̌v�Z
		float left = centerX - 140.0f * scale;
		float right = centerX + 140.0f * scale;
		float top = centerY - 40.0f * scale;
		float bottom = centerY + 40.0f * scale;

		// �͈͓�����
		if (mouseX >= left && mouseX <= right &&
			mouseY >= top && mouseY <= bottom) 
		{
			selectedByMouse = nCnt;							// ���ڂ̃C���f�b�N�X���L�^
			g_pauseMenu = (PAUSE_MENU)(nCnt);	// �I����Ԃ��X�V
		}
	}

	if (g_bTutoDraw == false)
	{
		// ���ڂ̓����x���X�V
		for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++) 
		{
			if (selectedByMouse == -1) 
			{
				// �͈͊O�Ȃ炷�ׂĔ�����
				pauseAlphas[nCnt] -= 0.1f; // ���X�ɔ���
				if (pauseAlphas[nCnt] < 0.3f) pauseAlphas[nCnt] = 0.3f;
				else
				{
					g_bPauseSelect = false;
				}
			}
			else if (nCnt == g_pauseMenu) 
			{
				// �I�𒆂̍��ڂ͔Z��
				pauseAlphas[nCnt] += 0.1f; // ���X�ɔZ��
				if (pauseAlphas[nCnt] > 1.0f)
				{
					pauseAlphas[nCnt] = 1.0f;
				}
				if (g_bPauseSelect == false)
				{
					PlaySound(SOUND_LABEL_SELECT);
					g_bPauseSelect = true;
				}
			}
			else 
			{
				// ��I���̍��ڂ͔���
				pauseAlphas[nCnt] -= 0.1f; // ���X�ɔ���

				if (pauseAlphas[nCnt] < 0.3f)
				{
					pauseAlphas[nCnt] = 0.3f;
				}
			}
		}

		// ���_�o�b�t�@�̃��b�N
		g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

		// ���ڂ̕`��ݒ�
		for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++) 
		{
			float scale = pauseScales[nCntPause];
			float centerX = 660.0f;
			float centerY = 180.0f + nCntPause * 150.0f;

			// ���_���W��ݒ�
			pVtx[0].pos = D3DXVECTOR3(centerX - 140.0f * scale, centerY - 40.0f * scale, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(centerX + 140.0f * scale, centerY - 40.0f * scale, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(centerX - 140.0f * scale, centerY + 40.0f * scale, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(centerX + 140.0f * scale, centerY + 40.0f * scale, 0.0f);

			// �J���[�ݒ�
			D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, pauseAlphas[nCntPause]);

			// ���_�J���[��ݒ�
			for (int nCntPause2 = 0; nCntPause2 < 4; nCntPause2++) 
			{
				pVtx[nCntPause2].col = color;
			}

			// ���_�|�C���^�����̍��ڂɐi�߂�
			pVtx += 4;
		}

		// ���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffPause->Unlock();

		// �͈͓��N���b�N�̏ꍇ�̂ݏ��������s
		if (g_fade == FADE_NONE && GetMouseButtonTrigger(0)) 
		{
			if (selectedByMouse != -1) 
			{
				// �͈͓��̍��ڂ��N���b�N���ꂽ�ꍇ
				switch (g_pauseMenu) 
				{
				case PAUSE_MENU_CONTINUE:		// ������
					SetEnablePause(false);
					PlaySound(SOUND_LABEL_OK);
					break;
				case PAUSE_MENU_RETRY:			// ���g���C
					SetFade(MODE_GAME);
					PlaySound(SOUND_LABEL_OK);
					break;
				case PAUSE_MENU_TUTORIAL:		// ����m�F
					SetDraw(true);
					PlaySound(SOUND_LABEL_OK);
					break;
				case PAUSE_MENU_QUIT:			// ��߂�
					SetFade(MODE_TITLE);
					PlaySound(SOUND_LABEL_OK);
					break;
				}
			}
			// �͈͊O���N���b�N�����ꍇ�͉������Ȃ�
		}

	}
}
//===============================================================
// �|�[�Y�̕`�揈��
//===============================================================
void DrawPause(void)
{
	int nCntPause;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//===============
	// �w�i
	//===============

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//===============
	// �|�[�Y����
	//===============

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePause[nCntPause]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause*4, 2);

	}
}

void SetDraw(bool bDraw)
{
	g_bTutoDraw = bDraw;
}

bool GetTutoDraw(void)
{
	return g_bTutoDraw;
}