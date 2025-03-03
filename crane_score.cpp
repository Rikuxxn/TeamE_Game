//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_background.h"
#include "password_game.h"
#include "crane_score.h"

// �O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureCranePass = { NULL };			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCranePass = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
CranePass g_aCranePass[MAX_NUM_SCORE] = {};					// �N���[��
int g_nCranePass;											// �p�X���[�h�̒l

//=========================
//|| �p�X���[�h�̏�����  ||
//=========================
void InitCranePass(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ballnumber.png",// �e�N�X�`���̃t�@�C����
		&g_pTextureCranePass);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCranePass,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCranePass->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntCranePass = 0; nCntCranePass < MAX_NUM_SCORE; nCntCranePass++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(PASSPOSX + nCntCranePass * 20.0f, PASSWORDFIELD_TOP, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PASSPOSX + nCntCranePass * 20.0f + 45.0f, PASSWORDFIELD_TOP, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PASSPOSX + nCntCranePass * 20.0f, PASSWORDFIELD_TOP + 70.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PASSPOSX + nCntCranePass * 20.0f + 45.0f, PASSWORDFIELD_TOP + 70.0f, 0.0f);
		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCranePass->Unlock();

	SetCranePass(0);
}
//=========================
//|| �p�X���[�h�̏I������||
//=========================
void UninitCranePass(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureCranePass != NULL)
	{
		g_pTextureCranePass->Release();
		g_pTextureCranePass = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffCranePass != NULL)
	{
		g_pVtxBuffCranePass->Release();
		g_pVtxBuffCranePass = NULL;
	}
}
//=========================
//|| �p�X���[�h�̍X�V����||
//=========================
void UpdateCranePass(void)
{
	VERTEX_2D* pVtx = 0;// ���_���ւ̃|�C���^
	int nData;
	int nData1 = 0;

	nData = CranePassCounter(g_nCranePass);
	for (nData1 = 0; nData1 < MAX_NUM_SCORE; nData1++)
	{
		if (nData1 >= MAX_NUM_SCORE - nData)
		{
			g_aCranePass[nData1].buse = true;
		}
		else
		{
			g_aCranePass[nData1].buse = false;
		}
	}
}
//=========================
//|| �p�X���[�h�̕`�揈��||
//=========================
void DrawCranePass(void)
{

	VERTEX_2D* pVtx = 0;						// ���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffCranePass, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCranePass->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCranePass = 0; nCntCranePass < MAX_NUM_SCORE; nCntCranePass++)
	{
		if (g_aCranePass[nCntCranePass].buse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCranePass);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCntCranePass * 4,						// �`�悷��ŏ��̒��_�C���f�b�N�X
				2);										// �`�悷��v���~�e�B�u��
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCranePass->Unlock();
}
//=========================
//|| �p�X���[�h�̐ݒ菈��||
//=========================
void SetCranePass(int nCraneAPass) 
{
	VERTEX_2D* pVtx = 0;				// ���_���ւ̃|�C���^
	int aPosTexU[MAX_NUM_SCORE] = {};	// �e���̐������i�[
	int n = 1000;
	int n1 = 100;
	aPosTexU[0] = 0;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCranePass->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCranePass = 0; nCntCranePass < MAX_NUM_SCORE; nCntCranePass++)
	{
		if (nCntCranePass == 0)
		{
			aPosTexU[0] = nCraneAPass / n;
		}
		else
		{
			aPosTexU[nCntCranePass] = nCraneAPass % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntCranePass]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntCranePass]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntCranePass]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntCranePass]), 1.0f);
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCranePass->Unlock();
}
//=====================
//�X�R�A��0���J�E���g
//=====================
int CranePassCounter(int nPass)
{
	int nNum = nPass;	// �X�R�A�̂O�̕������J�E���g
	int nKeepNum = 0;	// �X�R�A�̌���

	while (nNum != 0)	// ����؂�Ȃ��Ȃ�܂ŌJ��Ԃ�(�O�܂�)
	{
		nNum /= 10;		// nNum��10�Ŋ����Ă���
		nKeepNum++;		// ���������Z
	}
	if (nPass == 0)
	{
		nKeepNum = 1;	// 1���ڂ�0�������Ă���Ƃ�
	}
	return nKeepNum;	// �X�R�A�̌�����Ԃ�
}