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
//#include "sound.h"


//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTexturePause[MAX_PAUSE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTexturePauseBG = NULL;				//�e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseBG = NULL;			//���_�o�b�t�@�ւ̃|�C���^

PAUSE_MENU g_pauseMenu;										//�|�[�Y���j���[

// �|�[�Y���ڂ̊g�嗦���Ǘ�����z��
float pauseScales[MAX_PAUSE] = { PAUSE_MIN_SCALE, PAUSE_MIN_SCALE, PAUSE_MIN_SCALE };

//HWND g_hWnd;

//===============================================================
//�|�[�Y�̏���������
//===============================================================
void InitPause(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	int nCntPause;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

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
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//1�ڂ̒��_���
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);//2�ڂ̒��_���
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);//3�ڂ̒��_���
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);//4�ڂ̒��_���

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
//�|�[�Y�̏I������
//===============================================================
void UninitPause(void)
{

	//StopSound(SOUND_LABEL_PAUSE);
	//StopSound(SOUND_LABEL_PAUSE2);

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
//�|�[�Y�̍X�V����
//===============================================================
void UpdatePause(void)
{
	FADE g_fade = GetFade(); // ���݂̏��

	VERTEX_2D* pVtx;

	// ���݂̃J�[�\���ʒu���擾
	POINT cursorPos;
	GetCursorPos(&cursorPos);


	if (KeyboardTrigger(DIK_UP) || JoyPadTrigger(JOYKEY_UP)) 
	{
		//PlaySound(SOUND_LABEL_PAUSE2);
		g_pauseMenu = static_cast<PAUSE_MENU>((g_pauseMenu - 1 + MAX_PAUSE) % MAX_PAUSE);
	}
	else if (KeyboardTrigger(DIK_DOWN) || JoyPadTrigger(JOYKEY_DOWN)) 
	{
		//PlaySound(SOUND_LABEL_PAUSE2);
		g_pauseMenu = static_cast<PAUSE_MENU>((g_pauseMenu + 1) % MAX_PAUSE);
	}

	// �g�嗦�̍X�V
	for (int p = 0; p < MAX_PAUSE; p++)
	{
		if (p == g_pauseMenu)
		{
			// �I�𒆂̍��ڂ��g��i�X���[�Y�� MAX_SCALE �ɋ߂Â��j
			if (pauseScales[p] < PAUSE_MAX_SCALE)
			{
				pauseScales[p] += PAUSE_SCALE_SPEED;
			}
		}
		else
		{
			// ��I�����ڂ��k���i�X���[�Y�� MIN_SCALE �ɋ߂Â��j
			if (pauseScales[p] > PAUSE_MIN_SCALE)
			{
				pauseScales[p] -= PAUSE_SCALE_SPEED;
			}
		}
	}

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		float scale = pauseScales[nCntPause];
		float centerX = 650.0f;
		float centerY = 200.0f + nCntPause * 150.0f;

		// ���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(centerX - 150.0f * scale, centerY - 50.0f * scale, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(centerX + 150.0f * scale, centerY - 50.0f * scale, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(centerX - 150.0f * scale, centerY + 50.0f * scale, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(centerX + 150.0f * scale, centerY + 50.0f * scale, 0.0f);

		// �J���[�ݒ�i�I�𒆂Ȃ甒�A�s�I���Ȃ甖�����j
		D3DXCOLOR color;

		if (nCntPause == g_pauseMenu)
		{
			color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		}

		for (int nCntPause2 = 0; nCntPause2 < 4; nCntPause2++)
		{
			pVtx[nCntPause2].col = color;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPause->Unlock();


	if (g_fade == FADE_NONE && (KeyboardTrigger(DIK_RETURN) == true || JoyPadTrigger(JOYKEY_A) == true))
	{//����(ENTER)�L�[�������ꂽ
		//���j���[�ɍ��킹�ă��[�h�̐؂�ւ�

		//PlaySound(SOUND_LABEL_PAUSE);

		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);

			break;
		case PAUSE_MENU_RETRY:
			SetFade(MODE_GAME);

			break;
		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);

			break;
		}

	}

}
//===============================================================
//�|�[�Y�̕`�揈��
//===============================================================
void DrawPause(void)
{
	int nCntPause;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, /*g_apTexturePauseBG*/NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

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