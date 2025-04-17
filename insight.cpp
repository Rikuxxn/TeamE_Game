//=============================================================================
//
// ���E�G�t�F�N�g���� [insight.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "insight.h"
#include "enemy.h"
#include "block.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureInsight = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffInsight = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Insight g_aInsight;

const float ALPHA_INCREMENT = 0.05f; // �A���t�@�l�̑�����
const float MAX_ALPHA = 0.7f;        // �ő�A���t�@�l
const float MIN_ALPHA = 0.0f;        // �ŏ��A���t�@�l
float InsightAlpha = 0.0f;

//=========================================================
// ���E�G�t�F�N�g�̏���������
//=========================================================
void InitInsight(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���(��)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\insight.png",
		&g_pTextureInsight);

	// ������
	g_aInsight.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aInsight.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aInsight.fWidth = 0.0f;
	g_aInsight.fHeight = 0.0f;
	g_aInsight.bUse = false;
	g_aInsight.nCounter = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffInsight,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffInsight->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffInsight->Unlock();

}
//=========================================================
// ���E�G�t�F�N�g�̏I������
//=========================================================
void UninitInsight(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureInsight != NULL)
	{
		g_pTextureInsight->Release();
		g_pTextureInsight = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffInsight != NULL)
	{
		g_pVtxBuffInsight->Release();
		g_pVtxBuffInsight = NULL;
	}
}
//=========================================================
// ���E�G�t�F�N�g�̍X�V����
//=========================================================
void UpdateInsight(void)
{
	Flags* pFlag = GetFlag();

	if (isPlayerInSight() && pFlag->bFuseCmp)  // �v���C���[�����E���ɂ���
	{
		// ���X�ɓ����x���グ��
		InsightAlpha += ALPHA_INCREMENT;
		if (InsightAlpha > MAX_ALPHA) InsightAlpha = MAX_ALPHA;
	}
	else  // �v���C���[�����E�O
	{
		// ���X�ɓ����x��������
		InsightAlpha -= ALPHA_INCREMENT;
		if (InsightAlpha < MIN_ALPHA) InsightAlpha = MIN_ALPHA;
	}

	// ���_�o�b�t�@���X�V
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffInsight->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, InsightAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, InsightAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, InsightAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, InsightAlpha);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffInsight->Unlock();

}
//=========================================================
// ���E�G�t�F�N�g�̕`�揈��
//=========================================================
void DrawInsight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffInsight, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureInsight);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//===================================================
// ���E�G�t�F�N�g�̐ݒ菈��
//===================================================
void SetInsight(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffInsight->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aInsight.bUse == false)
	{
		g_aInsight.pos = pos;
		g_aInsight.col = col;
		g_aInsight.fWidth = fWidth;
		g_aInsight.fHeight = fHeight;
		g_aInsight.bUse = true;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aInsight.pos.x - g_aInsight.fWidth, g_aInsight.pos.y - g_aInsight.fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aInsight.pos.x + g_aInsight.fWidth, g_aInsight.pos.y - g_aInsight.fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aInsight.pos.x - g_aInsight.fWidth, g_aInsight.pos.y + g_aInsight.fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aInsight.pos.x + g_aInsight.fWidth, g_aInsight.pos.y + g_aInsight.fHeight, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffInsight->Unlock();

}
//===================================================
// ���E�G�t�F�N�g���̎擾
//===================================================
Insight* GetInsight(void)
{
	return &g_aInsight;
}