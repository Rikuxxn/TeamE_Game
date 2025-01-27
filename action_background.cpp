//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "action_background.h"

//�}�N��
#define NUM_BG (2)//�w�i�̐�

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureActionBG[NUM_BG] = { NULL };//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureActionBG3 = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffActionBG = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffActionBG2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffActionBG3 = NULL;
float g_aActionPosTexU[NUM_BG];//�e�N�X�`�����W�̊J�n�ʒu�iU�l�j

//�w�i�̏���������
void InitActionBackGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBG;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\images.jpg",//�e�N�X�`���̃t�@�C����
		&g_pTextureActionBG[0]);

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Mini_Action_Tutorial.png",//�e�N�X�`���̃t�@�C���� bg1.png
		&g_pTextureActionBG3);

	//
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aActionPosTexU[nCntBG] = 0.0f;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffActionBG,
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffActionBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG;nCntBG++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(400.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(880.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(400.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(880.0f, 720.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(g_aActionPosTexU[nCntBG], 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(g_aActionPosTexU[nCntBG] + 1.0f, 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(g_aActionPosTexU[nCntBG], 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(g_aActionPosTexU[nCntBG] + 1.0f, 1.0f);//(u,v)

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffActionBG->Unlock();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffActionBG2,
		NULL);

	VERTEX_2D* pVtx2;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffActionBG2->Lock(0, 0, (void**)&pVtx2, 0);

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
	g_pVtxBuffActionBG2->Unlock();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffActionBG3,
		NULL);

	VERTEX_2D* pVtx3;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffActionBG3->Lock(0, 0, (void**)&pVtx3, 0);

	//���_���W�̐ݒ�
	pVtx3[0].pos = D3DXVECTOR3(900.0f, 200.0f, 0.0f);
	pVtx3[1].pos = D3DXVECTOR3(1150.0f, 200.0f, 0.0f);
	pVtx3[2].pos = D3DXVECTOR3(900.0f, 600.0f, 0.0f);
	pVtx3[3].pos = D3DXVECTOR3(1150.0f, 600.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx3[0].rhw = 1.0f;
	pVtx3[1].rhw = 1.0f;
	pVtx3[2].rhw = 1.0f;
	pVtx3[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx3[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx3[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx3[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx3[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx3[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx3[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx3[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx3[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffActionBG3->Unlock();
}
//�w�i�̏I������
void UninitActionBackGround(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureActionBG[nCntBG] != NULL)
		{
			g_pTextureActionBG[nCntBG]->Release();
			g_pTextureActionBG[nCntBG] = NULL;
		}
	}
	//�e�N�X�`���̔j��
	if (g_pTextureActionBG3 != NULL)
	{
		g_pTextureActionBG3->Release();
		g_pTextureActionBG3 = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffActionBG != NULL)
	{
		g_pVtxBuffActionBG->Release();
		g_pVtxBuffActionBG = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffActionBG2 != NULL)
	{
		g_pVtxBuffActionBG2->Release();
		g_pVtxBuffActionBG2 = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffActionBG3 != NULL)
	{
		g_pVtxBuffActionBG3->Release();
		g_pVtxBuffActionBG3 = NULL;
	}
}
//�w�i�̍X�V����
void UpdateActionBackGround(void)
{

}
//�w�i�̕`�揈��
void DrawActionBackGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBG;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//����
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffActionBG2, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��

	//�`���[�g���A��
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffActionBG3, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureActionBG3);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��

	//3����
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffActionBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureActionBG[0]);

		//�w�i�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
			0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
			2);                                    //�`�悷��v���~�e�B�u��
	}
}