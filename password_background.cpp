//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_background.h"

//�}�N��
#define NUM_BG (2)//�w�i�̐�

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTexturePasswordBG = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG3 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG4 = NULL;
float g_aPassPosTexU[NUM_BG];							//�e�N�X�`�����W�̊J�n�ʒu�iU�l�j

//�w�i�̏���������
void InitPasswordBackGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBG;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UIKai6.png",//�e�N�X�`���̃t�@�C����
		&g_pTexturePasswordBG);

	//
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPassPosTexU[nCntBG] = 0.0f;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG,
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPasswordBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG;nCntBG++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT, PASSWORDFIELD_TOP, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT, PASSWORDFIELD_TOP, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT, PASSWORDFIELD_UNDER, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT, PASSWORDFIELD_UNDER, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[1].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[2].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[3].col = D3DCOLOR_RGBA(100, 100, 100, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aPassPosTexU[nCntBG], 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(g_aPassPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPassPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPassPosTexU[nCntBG] + 1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPasswordBG->Unlock();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG2,
		NULL);

	VERTEX_2D* pVtx2;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPasswordBG2->Lock(0, 0, (void**)&pVtx2, 0);

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
	pVtx2[0].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx2[1].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx2[2].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx2[3].col = D3DCOLOR_RGBA(100, 100, 100, 100);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPasswordBG2->Unlock();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG3,
		NULL);

	VERTEX_2D* pVtx3;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPasswordBG3->Lock(0, 0, (void**)&pVtx3, 0);

	//���_���W�̐ݒ�
	pVtx3[0].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT + 7.0f, PASSWORDFIELD_TOP + 7.0f, 0.0f);//��200.0f
	pVtx3[1].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT - 7.0f, PASSWORDFIELD_TOP + 7.0f, 0.0f);//����500.0f
	pVtx3[2].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT + 7.0f, PASSWORDFIELD_TOP + 59.0f, 0.0f);
	pVtx3[3].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT - 7.0f, PASSWORDFIELD_TOP + 59.0f, 0.0f);

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
	g_pVtxBuffPasswordBG3->Unlock();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG4,
		NULL);

	VERTEX_2D* pVtx4;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPasswordBG4->Lock(0, 0, (void**)&pVtx4, 0);

	//���_���W�̐ݒ�
	pVtx4[0].pos = D3DXVECTOR3(660.0f, 590.0f, 0.0f);//��150.0f
	pVtx4[1].pos = D3DXVECTOR3(810.0f, 590.0f, 0.0f);//����40.0f
	pVtx4[2].pos = D3DXVECTOR3(660.0f, 690.0f, 0.0f);
	pVtx4[3].pos = D3DXVECTOR3(810.0f, 690.0f, 0.0f);

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
	g_pVtxBuffPasswordBG4->Unlock();
}
//�w�i�̏I������
void UninitPasswordBackGround(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPasswordBG != NULL &&
		g_pVtxBuffPasswordBG2 != NULL &&
		g_pVtxBuffPasswordBG3 != NULL &&
		g_pVtxBuffPasswordBG4 != NULL)
	{
		g_pVtxBuffPasswordBG->Release();
		g_pVtxBuffPasswordBG = NULL;
		g_pVtxBuffPasswordBG2->Release();
		g_pVtxBuffPasswordBG2 = NULL;
		g_pVtxBuffPasswordBG3->Release();
		g_pVtxBuffPasswordBG3 = NULL;
		g_pVtxBuffPasswordBG4->Release();
		g_pVtxBuffPasswordBG4 = NULL;
	}
}
//�w�i�̍X�V����
void UpdatePasswordBackGround(void)
{

}
//�w�i�̕`�揈��
void DrawPasswordBackGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBG;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//����
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG2, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��

	//���͉��
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�w�i�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
			0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
			2);                                    //�`�悷��v���~�e�B�u��
	}

	//�o�͉��
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG3, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��

	//�����
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG4, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePasswordBG);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��
}