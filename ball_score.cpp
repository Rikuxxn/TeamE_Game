//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_background.h"
#include "password_game.h"
#include "ball_score.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureBallPass = { NULL };			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallPass = NULL;			//���_�o�b�t�@�ւ̃|�C���^
int g_nBallPass;											//�p�X���[�h�̒l
BallPass g_aBallPass[MAX_NUM_SCORE] = {};

//=========================
//|| �p�X���[�h�̏�����  ||
//=========================
void InitBallPass(void)
{
	int nCntBallPass;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ballnum.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureBallPass);

	//g_nBallPass = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallPass,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallPass->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBallPass = 0; nCntBallPass < MAX_NUM_SCORE; nCntBallPass++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(PASSPOSX + nCntBallPass * 20.0f, 160.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PASSPOSX + nCntBallPass * 20.0f + 200.0f, 160.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PASSPOSX + nCntBallPass * 20.0f, 560.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PASSPOSX + nCntBallPass * 20.0f + 200.0f, 560.0f, 0.0f);
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBallPass->Unlock();

	SetBallPass(0);
}
//=========================
//|| �p�X���[�h�̏I������||
//=========================
void UninitBallPass(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBallPass != NULL)
	{
		g_pTextureBallPass->Release();
		g_pTextureBallPass = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBallPass != NULL)
	{
		g_pVtxBuffBallPass->Release();
		g_pVtxBuffBallPass = NULL;
	}
}
//=========================
//|| �p�X���[�h�̍X�V����||
//=========================
void UpdateBallPass(void)
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int nData;
	int nData1 = 0;

	nData = BallPassCounter(g_nBallPass);
	for (nData1 = 0; nData1 < MAX_NUM_SCORE; nData1++)
	{
		if (nData1 >= MAX_NUM_SCORE - nData)
		{
			g_aBallPass[nData1].buse = true;
		}
		else
		{
			g_aBallPass[nData1].buse = false;
		}
	}
}
//=========================
//|| �p�X���[�h�̕`�揈��||
//=========================
void DrawBallPass(void)
{

	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int nCntBallPass;
	LPDIRECT3DDEVICE9 pDevice;
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBallPass, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallPass->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBallPass = 0; nCntBallPass < MAX_NUM_SCORE; nCntBallPass++)
	{
		if (g_aBallPass[nCntBallPass].buse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBallPass);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntBallPass * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);										//�`�悷��v���~�e�B�u��
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBallPass->Unlock();
}
//=========================
//|| �p�X���[�h�̐ݒ菈��||
//=========================
void SetBallPass(int nBallAPass) 
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int aPosTexU[MAX_NUM_SCORE] = {};//�e���̐������i�[
	int n = 1000;
	int n1 = 100;
	aPosTexU[0] = 0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallPass->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBallPass = 0; nCntBallPass < MAX_NUM_SCORE; nCntBallPass++)
	{
		if (nCntBallPass == 0)
		{
			aPosTexU[0] = nBallAPass / n;
		}
		else
		{
			aPosTexU[nCntBallPass] = nBallAPass % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntBallPass]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntBallPass]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntBallPass]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntBallPass]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBallPass->Unlock();
}
//=====================
//|�X�R�A��0���J�E���g|
//=====================
int BallPassCounter(int nPass)
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