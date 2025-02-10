//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_background.h"
#include "password_game.h"
#include "shooting_score.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureSTPass = { NULL };			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSTPass = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nSTPass;											//�p�X���[�h�̒l
STPass g_aSTPass[MAX_NUM_SCORE] = {};

//=========================
//|| �p�X���[�h�̏�����  ||
//=========================
void InitSTPass(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ballnumber.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureSTPass);

	//g_nSTPass = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSTPass,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSTPass->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntSTPass = 0; nCntSTPass < MAX_NUM_SCORE; nCntSTPass++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(PASSPOSX + nCntSTPass * 20.0f, PASSPOSY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PASSPOSX + nCntSTPass * 20.0f + 100.0f, PASSPOSY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PASSPOSX + nCntSTPass * 20.0f, PASSPOSY + 110.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PASSPOSX + nCntSTPass * 20.0f + 100.0f, PASSPOSY + 110.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSTPass->Unlock();

	SetSTPass(0);
}
//=========================
//|| �p�X���[�h�̏I������||
//=========================
void UninitSTPass(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSTPass != NULL)
	{
		g_pTextureSTPass->Release();
		g_pTextureSTPass = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSTPass != NULL)
	{
		g_pVtxBuffSTPass->Release();
		g_pVtxBuffSTPass = NULL;
	}
}
//=========================
//|| �p�X���[�h�̍X�V����||
//=========================
void UpdateSTPass(void)
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int nData;
	int nData1 = 0;

	nData = STPassCounter(g_nSTPass);
	for (nData1 = 0; nData1 < MAX_NUM_SCORE; nData1++)
	{
		if (nData1 >= MAX_NUM_SCORE - nData)
		{
			g_aSTPass[nData1].buse = true;
		}
		else
		{
			g_aSTPass[nData1].buse = false;
		}
	}
}
//=========================
//|| �p�X���[�h�̕`�揈��||
//=========================
void DrawSTPass(void)
{

	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int nCntSTPass;
	LPDIRECT3DDEVICE9 pDevice;
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffSTPass, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSTPass->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSTPass = 0; nCntSTPass < MAX_NUM_SCORE; nCntSTPass++)
	{
		if (g_aSTPass[nCntSTPass].buse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSTPass);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntSTPass * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);										//�`�悷��v���~�e�B�u��
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSTPass->Unlock();
}
//=========================
//|| �p�X���[�h�̐ݒ菈��||
//=========================
void SetSTPass(int nSTAPass) 
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int aPosTexU[MAX_NUM_SCORE] = {};//�e���̐������i�[
	int n = 1000;
	int n1 = 100;
	aPosTexU[0] = 0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSTPass->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntSTPass = 0; nCntSTPass < MAX_NUM_SCORE; nCntSTPass++)
	{
		if (nCntSTPass == 0)
		{
			aPosTexU[0] = nSTAPass / n;
		}
		else
		{
			aPosTexU[nCntSTPass] = nSTAPass % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntSTPass]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntSTPass]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntSTPass]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntSTPass]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSTPass->Unlock();
}
//=====================
//�X�R�A��0���J�E���g
//=====================
int STPassCounter(int nPass)
{
	int nNum = nPass;//�X�R�A�̂O�̕������J�E���g
	int nKeepNum = 0;//�X�R�A�̌���

	while (nNum != 0)//����؂�Ȃ��Ȃ�܂ŌJ��Ԃ�(�O�܂�)
	{
		nNum /= 10;//nNum��10�Ŋ����Ă���
		nKeepNum++;//���������Z
	}
	if (nPass == 0)
	{
		//1���ڂ�0�������Ă���Ƃ�
		nKeepNum = 1;
	}
	return nKeepNum;//�X�R�A�̌�����Ԃ�
}