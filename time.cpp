//=============================================================================
//
// �^�C������ [time.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "time.h"
#include "player.h"
#include "warning.h"
#include "block.h"
#include "enemy.h"
//#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTimeMinute = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTimeSecond = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureColon = NULL;				//�e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimeMinute = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimeSecond = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffColon = NULL;			//���_�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3 g_posTime;//�^�C���̈ʒu
Time g_aTime[MAX_TIMEDIGIT];

int g_nMinutes;		// ��
int g_nSeconds;		// �b

//=============================
//�^�C���̏���������
//=============================
void InitTime(void)
{

	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���(��)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&g_pTextureTimeMinute);

	//�e�N�X�`���̓ǂݍ���(�b)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&g_pTextureTimeSecond);

	//�e�N�X�`���̓ǂݍ���(�R����)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\colon.png",
		&g_pTextureColon);

	//������
	g_posTime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu������������(�n�܂�̈ʒu)
	g_nMinutes = 0;
	g_nSeconds = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMEDIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimeMinute,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMEDIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimeSecond,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffColon,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimeMinute->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_TIMEDIGIT; nCnt++)
	{

		g_aTime[nCnt].bUse = true;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(600.0f + nCnt * 35.0f, 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(600.0f + nCnt * 35.0f + 40.0f, 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(600.0f + nCnt * 35.0f, 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(600.0f + nCnt * 35.0f + 40.0f, 80.0f, 0.0f);

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
	g_pVtxBuffTimeMinute->Unlock();

	// �R�����̒��_�o�b�t�@�����b�N
	g_pVtxBuffColon->Lock(0, 0, (void**)&pVtx, 0);

	float colonX = 680.0f; // �R������X���W
	float colonY = 20.0f;  // �R������Y���W

	// �R�����̒��_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(colonX, colonY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(colonX + 20.0f, colonY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(colonX, colonY + 60.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(colonX + 20.0f, colonY + 60.0f, 0.0f);

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
	g_pVtxBuffColon->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimeSecond->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_TIMEDIGIT; nCnt++)
	{

		g_aTime[nCnt].bUse = true;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(700.0f + nCnt * 35.0f, 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(700.0f + nCnt * 35.0f + 40.0f, 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(700.0f + nCnt * 35.0f, 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(700.0f + nCnt * 35.0f + 40.0f, 80.0f, 0.0f);

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
	g_pVtxBuffTimeSecond->Unlock();


}
//=============================
//�^�C���̏I������
//=============================
void UninitTime(void)
{

	//�e�N�X�`���̔j��(��)
	if (g_pTextureTimeMinute != NULL)
	{
		g_pTextureTimeMinute->Release();
		g_pTextureTimeMinute = NULL;
	}

	//�e�N�X�`���̔j��(�b)
	if (g_pTextureTimeSecond != NULL)
	{
		g_pTextureTimeSecond->Release();
		g_pTextureTimeSecond = NULL;
	}

	//�e�N�X�`���̔j��(�R����)
	if (g_pTextureColon != NULL)
	{
		g_pTextureColon->Release();
		g_pTextureColon = NULL;
	}

	//���_�o�b�t�@�̔j��(��)
	if (g_pVtxBuffTimeMinute != NULL)
	{
		g_pVtxBuffTimeMinute->Release();
		g_pVtxBuffTimeMinute = NULL;
	}

	//���_�o�b�t�@�̔j��(�b)
	if (g_pVtxBuffTimeSecond != NULL)
	{
		g_pVtxBuffTimeSecond->Release();
		g_pVtxBuffTimeSecond = NULL;
	}

	//���_�o�b�t�@�̔j��(�R����)
	if (g_pVtxBuffColon != NULL)
	{
		g_pVtxBuffColon->Release();
		g_pVtxBuffColon = NULL;
	}

}
//=============================
// �^�C���̍X�V����
//=============================
void UpdateTime(void)
{
	bool bExit = GetExit();
	bool bEnd = GetEnd();

	VERTEX_2D* pVtx;

	static int nCntTimeSecond = 0;

	nCntTimeSecond++;

	if (bExit == false && bEnd == false)
	{
		if (nCntTimeSecond >= 60)			// 1�b���Ƃɏ���
		{
			nCntTimeSecond = 0;

			if (g_nSeconds >= 59)
			{
				g_nMinutes++;				// ���𑝂₷
				g_nSeconds = 0;				// �b�����Z�b�g
			}
			else if (g_nSeconds < 60)
			{
				g_nSeconds++;				// �b�𑝂₷
			}

		}
	}

	int min10 = g_nMinutes / 10;	// ����10�̈�
	int min1 = g_nMinutes % 10;		// ����1�̈�
	int sec10 = g_nSeconds / 10;	// �b��10�̈�
	int sec1 = g_nSeconds % 10;		// �b��1�̈�

	float texOffset = 0.1f;			// 1�����̃e�N�X�`���͈́i10�����j

	//===============================
	// ���̃e�N�X�`���ݒ�
	//===============================

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimeMinute->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTimeMinute->Unlock();

	//===============================
	// �b�̃e�N�X�`���ݒ�
	//===============================

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimeSecond->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTimeSecond->Unlock();

}
//=============================
//�^�C���̕`�揈��
//=============================
void DrawTime(void)
{

	//�K�v�������̕`��

	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//=================
	// ��
	//=================

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimeMinute, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TIMEDIGIT; nCnt++)
	{
		if (g_aTime[nCnt].bUse == true)
		{

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTimeMinute);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}


	//=================
	// �R����
	//=================

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffColon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureColon);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//=================
	// �b
	//=================

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimeSecond, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TIMEDIGIT; nCnt++)
	{
		if (g_aTime[nCnt].bUse == true)
		{

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTimeSecond);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}

}
//=============================
//�^�C��(��)�̎擾
//=============================
int GetTimeMinutes(void)
{
	return g_nMinutes;
}
//=============================
//�^�C��(�b)�̎擾
//=============================
int GetTimeSeconds(void)
{
	return g_nSeconds;
}
