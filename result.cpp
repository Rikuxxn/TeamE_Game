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
//#include "score.h"
#include "time.h"
#include "time.h"
#include "enemy.h"
#include "block.h"

typedef struct
{
	bool bUse;
	float fAlpha;     // �����x
	float fPosY;      // Y���W
	int nTimer;       // �A�j���[�V�����p�^�C�}�[
}ResultScore;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResultCrear = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResultGameover = NULL;			//�e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultCrear = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultGameover = NULL;	//���_�o�b�t�@�ւ̃|�C���^

float g_fAlphaGameover = 0.0f;								// �Q�[���I�[�o�[�p�̃A���t�@�l
int g_nRankCnt = 0;

//================================================
//���U���g��ʂ̏���������
//================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	g_fAlphaGameover = 0.0f;	// �t�F�[�h�A���t�@�l�����Z�b�g

	Player* pPlayer = GetPlayer();//�v���C���[�̏��ւ̃|�C���^

	bool bEnd = GetEnd();
	bool bExit = GetExit();
	//nScore = GetScore();
	//nTime = GetTime();

	if (bExit == true)
	{//�E�o������

		////���U���g(�Q�[���N���A)��ʂɑJ��
		//PlaySound(SOUND_LABEL_SCORE);

		//�e�N�X�`���̓ǂݍ���(�w�i)
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\exit.png",
			&g_pTextureResult);

	}
	else if (bEnd == true /*|| nTime == 0*/)
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
		&g_pVtxBuffResultCrear,
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
	g_pVtxBuffResultCrear->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(380.0f, 640.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(500.0f, 640.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(380.0f, 710.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(500.0f, 710.0f, 0.0f);

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
	g_pVtxBuffResultCrear->Unlock();


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
	if (g_pTextureResultCrear != NULL)
	{
		g_pTextureResultCrear->Release();
		g_pTextureResultCrear = NULL;
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
	if (g_pVtxBuffResultCrear != NULL)
	{
		g_pVtxBuffResultCrear->Release();
		g_pVtxBuffResultCrear = NULL;
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
		else if ((pPlayer->bDisp == false || bExit == false /*|| nTime <= 0*/) &&
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


	//====================================
    //�����̑��z�̕`��
    //====================================


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