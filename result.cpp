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
//#include "sound.h"
#include "time.h"
#include "enemy.h"
#include "block.h"


//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResultGameover = NULL;			//�e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultGameover = NULL;	//���_�o�b�t�@�ւ̃|�C���^

float g_fAlphaGameover = 0.0f;								// �Q�[���I�[�o�[�p�̃A���t�@�l
float g_fAlphaTime = 0.0f;									// �^�C���p�̃A���t�@�l
float g_fAlphaRank = 0.0f;									// �����N�p�̃A���t�@�l

int g_nRankCnt = 0;
int g_nTimeCnt = 0;


LPDIRECT3DTEXTURE9 g_pTextureResultTimeMinute = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResultTimeSecond = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResultColon = NULL;			//�e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultTimeMinute = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultTimeSecond = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultColon = NULL;		//���_�o�b�t�@�ւ̃|�C���^


D3DXVECTOR3 g_posResultTime;//�^�C���̈ʒu
Time g_aResultTime[MAX_RESULT_TIMEDIGIT];

int g_nResultMinutes;		// ��
int g_nResultSeconds;		// �b

//================================================
//���U���g��ʂ̏���������
//================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

<<<<<<< HEAD
	g_fAlphaGameover = 0.0f;		// �t�F�[�h�A���t�@�l�����Z�b�g
	g_fAlphaRank = 0.0f;			// �t�F�[�h�A���t�@�l�����Z�b�g
=======

	g_fAlphaGameover = 0.0f;		// �t�F�[�h�A���t�@�l�����Z�b�g
	g_fAlphaGameover = 0.0f;	// �t�F�[�h�A���t�@�l�����Z�b�g
	g_fAlphaTime = 0.0f;		// �t�F�[�h�A���t�@�l�����Z�b�g
	g_fAlphaRank = 0.0f;		// �t�F�[�h�A���t�@�l�����Z�b�g
>>>>>>> 3a86f006f54aff85320f4cf4156d77e82acf56c4
	g_nRankCnt = 0;

	Player* pPlayer = GetPlayer();	//�v���C���[�̏��ւ̃|�C���^

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

	}
	else if (bEnd == true)
	{//�߂܂�����܂��̓^�C����0�ɂȂ�����

		////���U���g(�Q�[���I�[�o�[)��ʂɑJ��
		//PlaySound(SOUND_LABEL_GAMEOVER);

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\wall001.jpg",
			&g_pTextureResult);


		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\gameover.png",
			&g_pTextureResultGameover);

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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultGameover,
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

	pVtx[0].pos = D3DXVECTOR3(500.0f, 640.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(630.0f, 640.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(500.0f, 710.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(630.0f, 710.0f, 0.0f);

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
	g_pVtxBuffResultGameover->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(320.0f, 300.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(960.0f, 300.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(320.0f, 470.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(960.0f, 470.0f, 0.0f);

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
	g_pVtxBuffResultGameover->Unlock();

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

	//�e�N�X�`���̔j��
	if (g_pTextureResultGameover != NULL)
	{
		g_pTextureResultGameover->Release();
		g_pTextureResultGameover = NULL;
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
	if (g_pVtxBuffResultGameover != NULL)
	{
		g_pVtxBuffResultGameover->Release();
		g_pVtxBuffResultGameover = NULL;
	}

}
//=====================================================
//���U���g��ʂ̍X�V����
//=====================================================
void UpdateResult(void)
{
	FADE g_fade = GetFade(); // ���݂̏��

	bool bExit = GetExit();
	//nTime = GetTime();

	Player* pPlayer = GetPlayer();

	g_nRankCnt++;

	// �����N�\���t�F�[�h
	if (g_nRankCnt >= 210)
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
	if (g_nRankCnt <= 210 && bExit == true)
	{
		//PlaySound(SOUND_LABEL_RANK);
	}

	// �Q�[���I�[�o�[�e�L�X�g�̃t�F�[�h
	if (g_nRankCnt >= 30)
	{
		if (g_fAlphaGameover < 255.0f)
		{
			g_fAlphaGameover += 5.0f; // �t�F�[�h���x����

			if (g_fAlphaGameover > 255.0f)
			{
				g_fAlphaGameover = 255.0f;
			}
		}
	}
	

	if (g_nRankCnt >= 180)
	{
		if (pPlayer->bDisp == true && bExit == true &&
			(g_fade == FADE_NONE && GetMouseButtonTrigger(0) /*|| JoyPadTrigger(JOYKEY_A) == true)*/))
		{//����L�[(ENTER�L�[)�������ꂽ

			//���[�h�ݒ�(�^�C�g����ʂɈڍs)
			SetFade(MODE_TITLE);

		}
		else if ((pPlayer->bDisp == false || bExit == false) &&
			(g_fade == FADE_NONE && GetMouseButtonTrigger(0) /*|| JoyPadTrigger(JOYKEY_A) == true)*/))
		{

			//���[�h�ݒ�(�^�C�g����ʂɈڍs)
			SetFade(MODE_TITLE);

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


	if (bExit == true)
	{
		//====================================
		//�����N�`��
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

	}

	if (bExit == false)
	{
		// ���_�o�b�t�@�����b�N
		g_pVtxBuffResultGameover->Lock(0, 0, (void**)&pVtx, 0);

		// �A���t�@�l�𔽉f
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaGameover);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaGameover);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaGameover);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlphaGameover);

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffResultGameover->Unlock();

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffResultGameover, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResultGameover);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
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
		pVtx[0].pos = D3DXVECTOR3(800.0f + nCnt * 70.0f, 190.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f + nCnt * 70.0f + 80.0f, 190.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(800.0f + nCnt * 70.0f, 280.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f + nCnt * 70.0f + 80.0f, 280.0f, 0.0f);

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

<<<<<<< HEAD
	float colonX = 970.0f;	// �R������X���W
	float colonY = 190.0f;	// �R������Y���W
=======
	//float colonX = 920.0f;	// �R������X���W
	//float colonY = 150.0f;	// �R������Y���W
	float colonX = 960.0f; // �R������X���W
	float colonY = 190.0f;  // �R������Y���W
>>>>>>> 3a86f006f54aff85320f4cf4156d77e82acf56c4

	// �R�����̒��_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(colonX, colonY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(colonX + 40.0f, colonY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(colonX, colonY + 90.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(colonX + 40.0f, colonY + 90.0f, 0.0f);

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
		pVtx[0].pos = D3DXVECTOR3(1020.0f + nCnt * 70.0f, 190.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1020.0f + nCnt * 70.0f + 80.0f, 190.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1020.0f + nCnt * 70.0f, 280.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1020.0f + nCnt * 70.0f + 80.0f, 280.0f, 0.0f);

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