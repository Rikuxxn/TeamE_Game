//---------------------------------------------------------
// 
// Author:Yoshida Atyushi
//---------------------------------------------------------

#include "main.h"
#include "shooting_player.h"

//�}�N��
#define NUM_BG (3)//�w�i�̐�

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureBG = { NULL };		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBG4 = { NULL };
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG3 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG4 = NULL;
float g_aPosTexU[NUM_BG];//�e�N�X�`�����W�̊J�n�ʒu�iU�l�j

//�w�i�̏���������
void InitBackGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	////�e�N�X�`��1�̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\bg100.png",						//�e�N�X�`���̃t�@�C����
	//	&g_pTextureBG[0]);
	////�e�N�X�`��2�̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\bg101.png",						//�e�N�X�`���̃t�@�C����
	//	&g_pTextureBG[1]);
	////�e�N�X�`��3�̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\bg102.png",						//�e�N�X�`���̃t�@�C����
	//	&g_pTextureBG[2]);
		//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\space_bg.png",						//�e�N�X�`���̃t�@�C����
		&g_pTextureBG);
	//�`���[�g���A���e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Mini_Shooting_Tutorial.png",	//�e�N�X�`���̃t�@�C����
		&g_pTextureBG4);

	//
	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] = 0.0f;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBG = 0; nCntBG < NUM_BG;nCntBG++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(360.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(920.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(360.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(920.0f, 720.0f, 0.0f);
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
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG2,
		NULL);
	VERTEX_2D* pVtx2;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG2->Lock(0, 0, (void**)&pVtx2, 0);
	//���_���W�̐ݒ�
	pVtx2[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx2[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx2[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx2[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	//rhw�̐ݒ�
	pVtx2[0].rhw = 1.0f;
	pVtx2[1].rhw = 1.0f;
	pVtx2[2].rhw = 1.0f;
	pVtx2[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx2[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx2[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx2[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx2[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG2->Unlock();


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG3,
		NULL);
	VERTEX_2D* pVtx3;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG3->Lock(0, 0, (void**)&pVtx3, 0);
	//���_���W�̐ݒ�
	pVtx3[0].pos = D3DXVECTOR3(360.0f, 0.0f, 0.0f);
	pVtx3[1].pos = D3DXVECTOR3(920.0f, 0.0f, 0.0f);
	pVtx3[2].pos = D3DXVECTOR3(360.0f, 720.0f, 0.0f);
	pVtx3[3].pos = D3DXVECTOR3(920.0f, 720.0f, 0.0f);
	//rhw�̐ݒ�
	pVtx3[0].rhw = 1.0f;
	pVtx3[1].rhw = 1.0f;
	pVtx3[2].rhw = 1.0f;
	pVtx3[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx3[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx3[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx3[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx3[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG3->Unlock();


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG4,
		NULL);
	VERTEX_2D* pVtx4;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG4->Lock(0, 0, (void**)&pVtx4, 0);
	//���_���W�̐ݒ�
	pVtx4[0].pos = D3DXVECTOR3(950.0f, 200.0f, 0.0f);
	pVtx4[1].pos = D3DXVECTOR3(1200.0f, 200.0f, 0.0f);
	pVtx4[2].pos = D3DXVECTOR3(950.0f, 600.0f, 0.0f);
	pVtx4[3].pos = D3DXVECTOR3(1200.0f, 600.0f, 0.0f);
	//rhw�̐ݒ�
	pVtx4[0].rhw = 1.0f;
	pVtx4[1].rhw = 1.0f;
	pVtx4[2].rhw = 1.0f;
	pVtx4[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx4[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx4[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx4[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx4[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`�����W�̐ݒ�
	pVtx4[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx4[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx4[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx4[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG4->Unlock();
}
//�w�i�̏I������
void UninitBackGround(void)
{
	//for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	//{
	//	//�e�N�X�`���̔j��
	//	if (g_pTextureBG[nCntBG] != NULL)
	//	{
	//		g_pTextureBG[nCntBG]->Release();
	//		g_pTextureBG[nCntBG] = NULL;
	//	}
	//}
	if (g_pTextureBG != NULL)
	{
		g_pTextureBG->Release();
		g_pTextureBG = NULL;
	}
	if (g_pTextureBG4 != NULL)
	{
		g_pTextureBG4->Release();
		g_pTextureBG4 = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
	if (g_pVtxBuffBG2 != NULL)
	{
		g_pVtxBuffBG2->Release();
		g_pVtxBuffBG2 = NULL;
	}
	if (g_pVtxBuffBG3 != NULL)
	{
		g_pVtxBuffBG3->Release();
		g_pVtxBuffBG3 = NULL;
	}
	if (g_pVtxBuffBG4 != NULL)
	{
		g_pVtxBuffBG4->Release();
		g_pVtxBuffBG4 = NULL;
	}

}
//�w�i�̍X�V����
void UpdateBackGround(void)
{
	VERTEX_2D* pVtx=0;//���_���ւ̃|�C���^
	int nCntBG;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] += 0.007f;

		//�e�N�X�`�����W�̐ݒ�(�c)
		pVtx[0].tex = D3DXVECTOR2(0.0f, g_aPosTexU[nCntBG] + 1.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(1.0f, g_aPosTexU[nCntBG] + 1.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, g_aPosTexU[nCntBG]);
		pVtx[3].tex = D3DXVECTOR2(1.0f, g_aPosTexU[nCntBG]);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}
//�w�i�̕`�揈��
void DrawBackGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//��ⓧ��
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBG2, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��


	//�w�i
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBG3, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��


	//�`���[�g���A��
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBG4, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBG4);
	//�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��


	//�w�i
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBG);
	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��
	//for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	//{
	//	//�e�N�X�`���̐ݒ�
	//	pDevice->SetTexture(0, g_pTextureBG[0]);
	//	pDevice->SetTexture(0, g_pTextureBG[1]);
	//	pDevice->SetTexture(0, g_pTextureBG[2]);
	//	//�w�i�̕`��
	//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
	//		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
	//		2);                                    //�`�悷��v���~�e�B�u��
	//}
}
