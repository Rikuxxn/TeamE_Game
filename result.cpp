//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "sound.h"
#include "time.h"
#include "enemy.h"
#include "block.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;						// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;						// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureClearSelect[MAX_GAMEOVER] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureGameoverSelect[MAX_GAMEOVER] = {};	// �e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClearSelect = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameoverSelect = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

CLEAR_MENU g_clearMenu;											// �N���A���j���[
GAMEOVER_MENU g_gameoverMenu;									// �Q�[���I�[�o�[���j���[

// ���ڂ̊g�嗦���Ǘ�����z��
float gameoverScales[MAX_GAMEOVER] = { GAMEOVER_MIN_SCALE, GAMEOVER_MIN_SCALE };
float clearScales[MAX_CLEAR] = { CLEAR_MIN_SCALE };

// ���ڂ��Ƃ̓����x��ێ�����z��
float clearAlphas[MAX_CLEAR] = { 0.3f };						// �����͑S�Ĕ������i�͈͊O��ԁj
float gameoverAlphas[MAX_GAMEOVER] = { 0.3f, 0.3f };			// �����͑S�Ĕ������i�͈͊O��ԁj

float g_fAlphaTime = 0.0f;										// �^�C���p�̃A���t�@�l
float g_fAlphaRank = 0.0f;										// �����N�p�̃A���t�@�l

int g_nRankCnt = 0;
int g_nTimeCnt = 0;

LPDIRECT3DTEXTURE9 g_pTextureResultTimeMinute = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResultTimeSecond = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResultColon = NULL;				// �e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultTimeMinute = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultTimeSecond = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultColon = NULL;			// ���_�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3 g_posResultTime;									// �^�C���̈ʒu
Time g_aResultTime[MAX_RESULT_TIMEDIGIT];

int g_nResultMinutes;											// ��
int g_nResultSeconds;											// �b

//================================================
//���U���g��ʂ̏���������
//================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_fAlphaRank = 0.0f;			// �t�F�[�h�A���t�@�l�����Z�b�g
	g_nRankCnt = 0;

	Player* pPlayer = GetPlayer();	//�v���C���[�̏��ւ̃|�C���^
	Block* pBlock = GetBlock();
	//Flags* pFlag = GetFlag();
	bool bEnd = GetEnd();
	bool bExit = GetExit();
	int nTimeMinutes = GetTimeMinutes();
	int nTimeSeconds = GetTimeSeconds();

	if (bExit == true)
	{//�E�o������

		////���U���g(�Q�[���N���A)��ʂɑJ��
		//PlaySound(SOUND_LABEL_SCORE);

		//�e�N�X�`���̓ǂݍ���(�w�i)
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\resultBG.png",
			&g_pTextureResult);

		// 2���؂�����
		if (nTimeMinutes < 2 && nTimeSeconds >= 0)
		{// �����NA

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\rankA.png",
				&g_pTextureRank);

		}
		// 2���ȏ�3������
		else if (nTimeMinutes >= 2 && nTimeMinutes < 3 && nTimeSeconds >= 0 && nTimeSeconds <= 59)
		{// �����NB

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\rankB.png",
				&g_pTextureRank);

		}
		// 3���ȏ�
		else if (nTimeMinutes >= 3 && nTimeSeconds >= 0)
		{// �����NC

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\rankC.png",
				&g_pTextureRank);

		}

		for (int clear = 0; clear < MAX_CLEAR; clear++)
		{
			D3DXCreateTextureFromFile(pDevice,
				CLEAR_TEXTURE[clear],
				&g_pTextureClearSelect[clear]);
		}

	}
	else if (bEnd == true)
	{//�߂܂�����܂��̓^�C����0�ɂȂ�����

		////���U���g(�Q�[���I�[�o�[)��ʂɑJ��
		//PlaySound(SOUND_LABEL_GAMEOVER);

		//�e�N�X�`���̓ǂݍ���(�w�i)
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\gameoverBG.png",
			&g_pTextureResult);


		for (int gameover = 0; gameover < MAX_GAMEOVER; gameover++)
		{
			D3DXCreateTextureFromFile(pDevice,
				GAMEOVER_TEXTURE[gameover],
				&g_pTextureGameoverSelect[gameover]);
		}

	}
	

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CLEAR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffClearSelect,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GAMEOVER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameoverSelect,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(200,200,200,255);
	pVtx[1].col = D3DCOLOR_RGBA(200,200,200,255);
	pVtx[2].col = D3DCOLOR_RGBA(200,200,200,255);
	pVtx[3].col = D3DCOLOR_RGBA(200,200,200,255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	float rankX = 1110.0f; // �����N��X���W
	float rankY = 370.0f;  // �����N��Y���W

	// �����N�̒��_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(rankX, rankY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(rankX + 50.0f, rankY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(rankX, rankY + 70.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(rankX + 50.0f, rankY + 70.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffClearSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntClear = 0; nCntClear < MAX_CLEAR; nCntClear++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(500.0f, (110.0f + nCntClear * 150), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f, (110.0f + nCntClear * 150), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, (210.0f + nCntClear * 150), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, (210.0f + nCntClear * 150), 0.0f);

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
	g_pVtxBuffClearSelect->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGameoverSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGameover = 0; nCntGameover < MAX_GAMEOVER; nCntGameover++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(500.0f, (110.0f + nCntGameover * 150), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f, (110.0f + nCntGameover * 150), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, (210.0f + nCntGameover * 150), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, (210.0f + nCntGameover * 150), 0.0f);

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
	g_pVtxBuffGameoverSelect->Unlock();

	g_clearMenu = CLEAR_MENU_TITLE;
	g_gameoverMenu = GAMEOVER_MENU_RETRY;

}
//=====================================================
//���U���g��ʂ̏I������
//=====================================================
void UninitResult(void)
{

	////�T�E���h�̒�~
	//StopSound(SOUND_LABEL_CLEAR);
	//StopSound(SOUND_LABEL_GAMEOVER);
	//StopSound(SOUND_LABEL_RANK);

	//�e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_CLEAR; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureClearSelect[nCnt] != NULL)
		{
			g_pTextureClearSelect[nCnt]->Release();
			g_pTextureClearSelect[nCnt] = NULL;
		}
	}

	for (int nCnt2 = 0; nCnt2 < MAX_GAMEOVER; nCnt2++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureGameoverSelect[nCnt2] != NULL)
		{
			g_pTextureGameoverSelect[nCnt2]->Release();
			g_pTextureGameoverSelect[nCnt2] = NULL;
		}
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffClearSelect != NULL)
	{
		g_pVtxBuffClearSelect->Release();
		g_pVtxBuffClearSelect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGameoverSelect != NULL)
	{
		g_pVtxBuffGameoverSelect->Release();
		g_pVtxBuffGameoverSelect = NULL;
	}

}
//=====================================================
//���U���g��ʂ̍X�V����
//=====================================================
void UpdateResult(void)
{
	FADE g_fade = GetFade(); // ���݂̏��
	Block* pBlock = GetBlock();
	//Flags* pFlag = GetFlag();
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

	bool bExit = GetExit();
	//nTime = GetTime();

	Player* pPlayer = GetPlayer();

	g_nRankCnt++;

	// �����N�\���t�F�[�h
	if (g_nRankCnt >= 300)
	{
		if (g_fAlphaRank < 255.0f)
		{
			g_fAlphaRank += 2.0f; // �t�F�[�h���x����

			if (g_fAlphaRank > 255.0f)
			{
				g_fAlphaRank = 255.0f;
			}
		}
	}
	if (g_nRankCnt <= 300 && bExit == true)
	{
		//PlaySound(SOUND_LABEL_RANK);
	}
	
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

	if (bExit == true)
	{
		for (int nCnt = 0; nCnt < MAX_CLEAR; nCnt++)
		{
			float scale = clearScales[nCnt];
			float centerX = 980.0f; // ���SX���W
			float centerY = 600.0f + nCnt * 150.0f; // ���SY���W

			// �̈�̌v�Z
			float left = centerX - 78.0f * scale;
			float right = centerX + 78.0f * scale;
			float top = centerY - 10.0f * scale;
			float bottom = centerY + 10.0f * scale;

			// �͈͓�����
			if (mouseX >= left && mouseX <= right &&
				mouseY >= top && mouseY <= bottom)
			{
				selectedByMouse = nCnt; // ���ڂ̃C���f�b�N�X���L�^
				g_clearMenu = static_cast<CLEAR_MENU>(nCnt); // �I����Ԃ��X�V
			}
		}

		// ���ڂ̓����x���X�V
		for (int nCnt = 0; nCnt < MAX_CLEAR; nCnt++)
		{
			if (selectedByMouse == -1)
			{
				// �͈͊O�Ȃ炷�ׂĔ�����
				clearAlphas[nCnt] -= 0.2f; // ���X�ɔ���
				if (clearAlphas[nCnt] < 0.3f)
				{
					clearAlphas[nCnt] = 0.3f;
				}
			}
			else if (nCnt == g_clearMenu)
			{
				// �I�𒆂̍��ڂ͔Z������
				clearAlphas[nCnt] += 0.2f; // ���X�ɔZ��
				if (clearAlphas[nCnt] > 1.0f)
				{
					clearAlphas[nCnt] = 1.0f;
				}
			}
			else
			{
				// ��I���̍��ڂ͔���
				clearAlphas[nCnt] -= 0.1f; // ���X�ɔ���

				if (clearAlphas[nCnt] < 0.3f)
				{
					clearAlphas[nCnt] = 0.3f;
				}
			}
		}

		// ���_�o�b�t�@�̃��b�N
		g_pVtxBuffClearSelect->Lock(0, 0, (void**)&pVtx, 0);

		// ���ڂ̕`��ݒ�
		for (int nCntClear = 0; nCntClear < MAX_CLEAR; nCntClear++)
		{
			float scale = clearScales[nCntClear];
			float centerX = 980.0f;
			float centerY = 600.0f + nCntClear * 150.0f;

			// ���_���W��ݒ�
			pVtx[0].pos = D3DXVECTOR3(centerX - 78.0f * scale, centerY - 10.0f * scale, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(centerX + 78.0f * scale, centerY - 10.0f * scale, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(centerX - 78.0f * scale, centerY + 10.0f * scale, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(centerX + 78.0f * scale, centerY + 10.0f * scale, 0.0f);

			// �J���[�ݒ�
			D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, clearAlphas[nCntClear]);

			// ���_�J���[��ݒ�
			for (int nCntClear2 = 0; nCntClear2 < 4; nCntClear2++)
			{
				pVtx[nCntClear2].col = color;
			}

			// ���_�|�C���^�����̍��ڂɐi�߂�
			pVtx += 4;
		}

		// ���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffClearSelect->Unlock();

		// �͈͓��N���b�N�̏ꍇ�̂ݏ��������s
		if (g_fade == FADE_NONE && GetMouseButtonTrigger(0))
		{
			if (selectedByMouse != -1)
			{
				// �͈͓��̍��ڂ��N���b�N���ꂽ�ꍇ
				switch (g_clearMenu)
				{
				case CLEAR_MENU_TITLE:

					// �^�C�g����ʂɈڍs
					SetFade(MODE_TITLE);

					break;
				}
			}
			// �͈͊O���N���b�N�����ꍇ�͉������Ȃ�
		}

	}
	else if (bExit == false)
	{
		for (int nCnt = 0; nCnt < MAX_GAMEOVER; nCnt++)
		{
			float scale = gameoverScales[nCnt];
			float centerX = 1010.0f; // ���SX���W
			float centerY = 300.0f + nCnt * 150.0f; // ���SY���W

			// �̈�̌v�Z
			float left = centerX - 150.0f * scale;
			float right = centerX + 150.0f * scale;
			float top = centerY - 20.0f * scale;
			float bottom = centerY + 20.0f * scale;

			// �͈͓�����
			if (mouseX >= left && mouseX <= right &&
				mouseY >= top && mouseY <= bottom)
			{
				selectedByMouse = nCnt; // ���ڂ̃C���f�b�N�X���L�^
				g_gameoverMenu = static_cast<GAMEOVER_MENU>(nCnt); // �I����Ԃ��X�V
			}
		}

		// ���ڂ̓����x���X�V
		for (int nCnt = 0; nCnt < MAX_GAMEOVER; nCnt++)
		{
			if (selectedByMouse == -1)
			{
				// �͈͊O�Ȃ炷�ׂĔ�����
				gameoverAlphas[nCnt] -= 0.1f; // ���X�ɔ���
				if (gameoverAlphas[nCnt] < 0.3f) gameoverAlphas[nCnt] = 0.3f;
			}
			else if (nCnt == g_gameoverMenu)
			{
				// �I�𒆂̍��ڂ͔Z������
				gameoverAlphas[nCnt] += 0.1f; // ���X�ɔZ��
				if (gameoverAlphas[nCnt] > 1.0f)
				{
					gameoverAlphas[nCnt] = 1.0f;
				}
			}
			else
			{
				// ��I���̍��ڂ͔���
				gameoverAlphas[nCnt] -= 0.1f; // ���X�ɔ���

				if (gameoverAlphas[nCnt] < 0.3f)
				{
					gameoverAlphas[nCnt] = 0.3f;
				}
			}
		}

		// ���_�o�b�t�@�̃��b�N
		g_pVtxBuffGameoverSelect->Lock(0, 0, (void**)&pVtx, 0);

		// ���ڂ̕`��ݒ�
		for (int nCntGameover = 0; nCntGameover < MAX_GAMEOVER; nCntGameover++)
		{
			float scale = gameoverScales[nCntGameover];
			float centerX = 1010.0f;
			float centerY = 300.0f + nCntGameover * 150.0f;

			// ���_���W��ݒ�
			pVtx[0].pos = D3DXVECTOR3(centerX - 150.0f * scale, centerY - 20.0f * scale, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(centerX + 150.0f * scale, centerY - 20.0f * scale, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(centerX - 150.0f * scale, centerY + 20.0f * scale, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(centerX + 150.0f * scale, centerY + 20.0f * scale, 0.0f);

			// �J���[�ݒ�
			D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, gameoverAlphas[nCntGameover]);

			// ���_�J���[��ݒ�
			for (int nCntGameover2 = 0; nCntGameover2 < 4; nCntGameover2++)
			{
				pVtx[nCntGameover2].col = color;
			}

			// ���_�|�C���^�����̍��ڂɐi�߂�
			pVtx += 4;
		}

		// ���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffGameoverSelect->Unlock();

		// �͈͓��N���b�N�̏ꍇ�̂ݏ��������s
		if (g_fade == FADE_NONE && GetMouseButtonTrigger(0))
		{
			if (selectedByMouse != -1)
			{
				// �͈͓��̍��ڂ��N���b�N���ꂽ�ꍇ
				switch (g_gameoverMenu)
				{
				case GAMEOVER_MENU_RETRY:

					// �Q�[����ʂɈڍs
					SetFade(MODE_GAME);

					break;

				case GAMEOVER_MENU_TITLE:

					// �^�C�g����ʂɈڍs
					SetFade(MODE_TITLE);

					break;
				}
			}
			// �͈͊O���N���b�N�����ꍇ�͉������Ȃ�
		}
	}
}
//=====================================================
//���U���g��ʂ̕`�揈��
//=====================================================
void DrawResult(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();//�v���C���[�̏��ւ̃|�C���^
	Block* pBlock = GetBlock();
	//Flags* pFlag = GetFlag();
	bool bExit = GetExit();
	int nTimeMinutes = GetTimeMinutes();
	int nTimeSeconds = GetTimeSeconds();

	VERTEX_2D* pVtx;

	//====================================
	// �w�i�̕`��
	//====================================

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �Q�[���N���A�̎�
	if (bExit == true)
	{
		//====================================
		// �����N�`��
		//====================================

		if (nTimeMinutes < 2 && nTimeSeconds >= 0)
		{

			// ���_�o�b�t�@�����b�N
			g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

			// �A���t�@�l�𔽉f
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);

			// ���_�o�b�t�@���A�����b�N
			g_pVtxBuffRank->Unlock();

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRank);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}
		else if (nTimeMinutes >= 2 && nTimeMinutes < 3 && nTimeSeconds >= 0 && nTimeSeconds <= 59)
		{

			// ���_�o�b�t�@�����b�N
			g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

			// �A���t�@�l�𔽉f
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);

			// ���_�o�b�t�@���A�����b�N
			g_pVtxBuffRank->Unlock();

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRank);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}
		else if (nTimeMinutes >= 3 && nTimeSeconds >= 0)
		{

			// ���_�o�b�t�@�����b�N
			g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

			// �A���t�@�l�𔽉f
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaRank);

			// ���_�o�b�t�@���A�����b�N
			g_pVtxBuffRank->Unlock();

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRank);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}

		//====================================
		// �I�����ڂ̕`��
		//====================================

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffClearSelect, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int nCntClear = 0; nCntClear < MAX_CLEAR; nCntClear++)
		{

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureClearSelect[nCntClear]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntClear * 4, 2);

		}

	}


	// �Q�[���I�[�o�[�̎�
	if (bExit == false)
	{

		//====================================
		// �I�����ڂ̕`��
		//====================================

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffGameoverSelect, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int nCntGameover = 0; nCntGameover < MAX_GAMEOVER; nCntGameover++)
		{

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureGameoverSelect[nCntGameover]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGameover * 4, 2);

		}
	}

}
//=============================
// ���U���g�^�C���̏���������
//=============================
void InitResultTime(void)
{

	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���(��)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&g_pTextureResultTimeMinute);

	//�e�N�X�`���̓ǂݍ���(�b)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&g_pTextureResultTimeSecond);

	//�e�N�X�`���̓ǂݍ���(�R����)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\colon.png",
		&g_pTextureResultColon);

	//������
	g_posResultTime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu������������(�n�܂�̈ʒu)
	g_nResultMinutes = 0;
	g_nResultSeconds = 0;

	g_fAlphaTime = 0.0f;			// �t�F�[�h�A���t�@�l�����Z�b�g
	g_nTimeCnt = 0;

	nCnt = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMEDIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultTimeMinute,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMEDIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultTimeSecond,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultColon,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultTimeMinute->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{

		g_aResultTime[nCnt].bUse = true;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(1010.0f + nCnt * 30.0f, 195.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1010.0f + nCnt * 30.0f + 40.0f, 195.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1010.0f + nCnt * 30.0f, 255.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1010.0f + nCnt * 30.0f + 40.0f, 255.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultTimeMinute->Unlock();

	// �R�����̒��_�o�b�t�@�����b�N
	g_pVtxBuffResultColon->Lock(0, 0, (void**)&pVtx, 0);

	float colonX = 1085.0f; // �R������X���W
	float colonY = 190.0f;  // �R������Y���W

	// �R�����̒��_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(colonX, colonY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(colonX + 40.0f, colonY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(colonX, colonY + 70.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(colonX + 40.0f, colonY + 70.0f, 0.0f);

	for (int nCntColon = 0; nCntColon < 4; nCntColon++)
	{
		pVtx[nCntColon].rhw = 1.0f;
		pVtx[nCntColon].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	// �R�����̃e�N�X�`�����W�ݒ�i1���̉摜�̏ꍇ�͌Œ�j
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffResultColon->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultTimeSecond->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{

		g_aResultTime[nCnt].bUse = true;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(1120.0f + nCnt * 30.0f, 195.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1120.0f + nCnt * 30.0f + 40.0f, 195.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1120.0f + nCnt * 30.0f, 255.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1120.0f + nCnt * 30.0f + 40.0f, 255.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultTimeSecond->Unlock();

}
//=============================
// ���U���g�^�C���̏I������
//=============================
void UninitResultTime(void)
{

	//�e�N�X�`���̔j��(��)
	if (g_pTextureResultTimeMinute != NULL)
	{
		g_pTextureResultTimeMinute->Release();
		g_pTextureResultTimeMinute = NULL;
	}

	//�e�N�X�`���̔j��(�b)
	if (g_pTextureResultTimeSecond != NULL)
	{
		g_pTextureResultTimeSecond->Release();
		g_pTextureResultTimeSecond = NULL;
	}

	//�e�N�X�`���̔j��(�R����)
	if (g_pTextureResultColon != NULL)
	{
		g_pTextureResultColon->Release();
		g_pTextureResultColon = NULL;
	}

	//���_�o�b�t�@�̔j��(��)
	if (g_pVtxBuffResultTimeMinute != NULL)
	{
		g_pVtxBuffResultTimeMinute->Release();
		g_pVtxBuffResultTimeMinute = NULL;
	}

	//���_�o�b�t�@�̔j��(�b)
	if (g_pVtxBuffResultTimeSecond != NULL)
	{
		g_pVtxBuffResultTimeSecond->Release();
		g_pVtxBuffResultTimeSecond = NULL;
	}

	//���_�o�b�t�@�̔j��(�R����)
	if (g_pVtxBuffResultColon != NULL)
	{
		g_pVtxBuffResultColon->Release();
		g_pVtxBuffResultColon = NULL;
	}

}
//=============================
// ���U���g�^�C���̍X�V����
//=============================
void UpdateResultTime(void)
{
	g_nTimeCnt++;

	if (g_nTimeCnt >= 120)
	{
		if (g_fAlphaTime < 255.0f)
		{
			g_fAlphaTime += 2.0f; // �t�F�[�h���x����

			if (g_fAlphaTime > 255.0f)
			{
				g_fAlphaTime = 255.0f;
			}
		}
	}

	int nMinutes = GetTimeMinutes();
	int nSeconds = GetTimeSeconds();

	VERTEX_2D* pVtx;

	g_nResultMinutes = nMinutes;
	g_nResultSeconds = nSeconds;

	int min10 = g_nResultMinutes / 10;	// ����10�̈�
	int min1 = g_nResultMinutes % 10;	// ����1�̈�
	int sec10 = g_nResultSeconds / 10;	// �b��10�̈�
	int sec1 = g_nResultSeconds % 10;	// �b��1�̈�

	float texOffset = 0.1f;				// 1�����̃e�N�X�`���͈́i0.0�`1.0��10�����j

	//===============================
	// ���̃e�N�X�`���ݒ�
	//===============================

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultTimeMinute->Lock(0, 0, (void**)&pVtx, 0);

	// ����10�̈�
	pVtx[0].tex = D3DXVECTOR2(texOffset * min10, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texOffset * min10 + texOffset, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(texOffset * min10, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(texOffset * min10 + texOffset, 1.0f);

	// ����1�̈�
	pVtx[4].tex = D3DXVECTOR2(texOffset * min1, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(texOffset * min1 + texOffset, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(texOffset * min1, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(texOffset * min1 + texOffset, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultTimeMinute->Unlock();

	//===============================
	// �b�̃e�N�X�`���ݒ�
	//===============================

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultTimeSecond->Lock(0, 0, (void**)&pVtx, 0);

	// �b��10�̈�
	pVtx[0].tex = D3DXVECTOR2(texOffset * sec10, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texOffset * sec10 + texOffset, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(texOffset * sec10, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(texOffset * sec10 + texOffset, 1.0f);

	// �b��1�̈�
	pVtx[4].tex = D3DXVECTOR2(texOffset * sec1, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(texOffset * sec1 + texOffset, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(texOffset * sec1, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(texOffset * sec1 + texOffset, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultTimeSecond->Unlock();

}
//=============================
// ���U���g�^�C���̕`�揈��
//=============================
void DrawResultTime(void)
{

	VERTEX_2D* pVtx;

	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//=================
	// ��
	//=================

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffResultTimeMinute->Lock(0, 0, (void**)&pVtx, 0);

	// �A���t�@�l�𔽉f
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// �A���t�@�l�𔽉f
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffResultTimeMinute->Unlock();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultTimeMinute, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{
		if (g_aResultTime[nCnt].bUse == true)
		{

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureResultTimeMinute);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}

	//=================
	// �R����
	//=================

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffResultColon->Lock(0, 0, (void**)&pVtx, 0);

	// �A���t�@�l�𔽉f
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffResultColon->Unlock();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultColon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResultColon);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//=================
	// �b
	//=================

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffResultTimeSecond->Lock(0, 0, (void**)&pVtx, 0);

	// �A���t�@�l�𔽉f
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// �A���t�@�l�𔽉f
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaTime);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffResultTimeSecond->Unlock();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultTimeSecond, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_RESULT_TIMEDIGIT; nCnt++)
	{
		if (g_aResultTime[nCnt].bUse == true)
		{

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureResultTimeSecond);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}

}