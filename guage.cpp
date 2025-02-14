//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "guage.h"
#include "player.h"
#include "sound.h"

//�}�N��
#define NUM_LIFE (5)	 //���C�t�̎��

//�O���[�o��
//LPDIRECT3DTEXTURE9 g_pTextureGuage = {};				  //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGuage = NULL;		  //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGuage2 = NULL;
float g_fWidthGuage;
float g_fHeightGuage;
bool g_bLow;

void InitGuage(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	g_fWidthGuage = 470.0f;
	g_fHeightGuage = 650.0f;
	g_bLow = false;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGuage,
		NULL);
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGuage->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 255);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGuage->Unlock();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGuage2,
		NULL);
	VERTEX_2D* pVtx2;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGuage2->Lock(0, 0, (void**)&pVtx2, 0);

	//���_���W�̐ݒ�
	pVtx2[0].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);
	pVtx2[1].pos = D3DXVECTOR3(g_fWidthGuage + (PLAYER_STAMINA * 1.5f), g_fHeightGuage, 0.0f);
	pVtx2[2].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage + 13.0f, 0.0f);
	pVtx2[3].pos = D3DXVECTOR3(g_fWidthGuage + (PLAYER_STAMINA * 1.5f), g_fHeightGuage + 13.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx2[0].rhw = 1.0f;
	pVtx2[1].rhw = 1.0f;
	pVtx2[2].rhw = 1.0f;
	pVtx2[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx2[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx2[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx2[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx2[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGuage2->Unlock();
}
void UninitGuage(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGuage != NULL)
	{
		g_pVtxBuffGuage->Release();
		g_pVtxBuffGuage = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGuage2 != NULL)
	{
		g_pVtxBuffGuage2->Release();
		g_pVtxBuffGuage2 = NULL;
	}
}
void UpdateGuage(void)
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	Player *pPlayer = GetPlayer();
	float fLife = pPlayer->fDush;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGuage->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_fWidthGuage + (fLife * 1.5f), g_fHeightGuage, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_fWidthGuage, g_fHeightGuage + 13.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_fWidthGuage + (fLife * 1.5f), g_fHeightGuage + 13.0f, 0.0f);

	if (pPlayer->fDush <= 90)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	else if (pPlayer->fDush >= 90 && pPlayer->bEmpty == false)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGuage->Unlock();
}
void DrawGuage(void)
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffGuage2, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGuage2->Lock(0, 0, (void**)&pVtx, 0);

	////�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pTextureGuage);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);									   //�`�悷��v���~�e�B�u��

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGuage2->Unlock();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffGuage, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGuage->Lock(0, 0, (void**)&pVtx, 0);

	////�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pTextureGuage);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);									   //�`�悷��v���~�e�B�u��
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGuage->Unlock();
}