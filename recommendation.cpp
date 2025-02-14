//=======================================
//
// ������ʏ���[recommendation.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "recommendation.h"
#include "fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRecommend = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRecommend = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

int g_fadeCount;	// �t�F�[�h�J�E���g

//================================================
// ������ʂ̏���������
//================================================
void InitRecommendation(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\recommendation.png",
		&g_pTextureRecommend);

	g_fadeCount = 0;//������

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRecommend,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRecommend->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffRecommend->Unlock();

}
//=====================================================
// ������ʂ̏I������
//=====================================================
void UninitRecommendation(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRecommend != NULL)
	{
		g_pTextureRecommend->Release();
		g_pTextureRecommend = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRecommend != NULL)
	{
		g_pVtxBuffRecommend->Release();
		g_pVtxBuffRecommend = NULL;
	}
}
//=====================================================
// ������ʂ̍X�V����
//=====================================================
void UpdateRecommendation(void)
{
	GetFade();//�t�F�[�h�̎擾

	FADE g_fade = GetFade();//���݂̏��

	g_fadeCount++;		// �J�E���g���Z

	if (g_fadeCount >= 180)
	{
		//���Ԍo��
		SetFade(MODE_TITLE);
	}
}
//=====================================================
// ������ʂ̕`�揈��
//=====================================================
void DrawRecommendation(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRecommend, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRecommend);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

