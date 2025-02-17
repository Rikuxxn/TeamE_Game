//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_background.h"

// �}�N��
#define NUM_BG (2)// �w�i�̐�

// �O���[�o��
LPDIRECT3DTEXTURE9 g_pTexturePasswordBG4 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePasswordBG5 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG3 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG4 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordBG5 = NULL;

// �w�i�̏���������
void InitPasswordBackGround(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UIKai6.png",// �e�N�X�`���̃t�@�C����
		&g_pTexturePasswordBG4);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Pass_answer2.png",// �e�N�X�`���̃t�@�C����
		&g_pTexturePasswordBG5);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG2,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG3,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG4,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordBG5,
		NULL);

	VERTEX_2D* pVtx;// ���_���ւ̃|�C���^
	
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPasswordBG->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT, PASSWORDFIELD_TOP, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT, PASSWORDFIELD_TOP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT, PASSWORDFIELD_UNDER, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT, PASSWORDFIELD_UNDER, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	
	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPasswordBG->Unlock();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPasswordBG2->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPasswordBG2->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPasswordBG3->Lock(0, 0, (void**)&pVtx, 0);
	
	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT + 7.0f, PASSWORDFIELD_TOP + 7.0f, 0.0f);	//��200.0f
	pVtx[1].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT - 7.0f, PASSWORDFIELD_TOP + 7.0f, 0.0f);	//����500.0f
	pVtx[2].pos = D3DXVECTOR3(PASSWORDFIELD_LEFT + 7.0f, PASSWORDFIELD_TOP + 59.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PASSWORDFIELD_RIGHT - 7.0f, PASSWORDFIELD_TOP + 59.0f, 0.0f);
	
	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	
	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 255);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 255);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 255);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 255);
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPasswordBG3->Unlock();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPasswordBG4->Lock(0, 0, (void**)&pVtx, 0);
	
	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(510.0f, 550.0f, 0.0f);//��150.0f
	pVtx[1].pos = D3DXVECTOR3(810.0f, 550.0f, 0.0f);//����40.0f
	pVtx[2].pos = D3DXVECTOR3(510.0f, 630.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(810.0f, 630.0f, 0.0f);
	
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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPasswordBG4->Unlock();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPasswordBG5->Lock(0, 0, (void**)&pVtx, 0);
	
	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(850.0f, 220.0f, 0.0f);	//��360.0f
	pVtx[1].pos = D3DXVECTOR3(1210.0f, 220.0f, 0.0f);	//����130.0f
	pVtx[2].pos = D3DXVECTOR3(850.0f, 350.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1210.0f, 350.0f, 0.0f);
	
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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPasswordBG5->Unlock();
}
// �w�i�̏I������
void UninitPasswordBackGround(void)
{
	// �e�N�X�`��
	if (g_pTexturePasswordBG4 != NULL)
	{
		g_pTexturePasswordBG4->Release();
		g_pTexturePasswordBG4 = NULL;
	}
	if (g_pTexturePasswordBG5 != NULL)
	{
		g_pTexturePasswordBG5->Release();
		g_pTexturePasswordBG5 = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPasswordBG != NULL)
	{
		g_pVtxBuffPasswordBG->Release();
		g_pVtxBuffPasswordBG = NULL;
	}
	if (g_pVtxBuffPasswordBG2 != NULL)
	{
		g_pVtxBuffPasswordBG2->Release();
		g_pVtxBuffPasswordBG2 = NULL;
	}
	if (g_pVtxBuffPasswordBG3 != NULL)
	{
		g_pVtxBuffPasswordBG3->Release();
		g_pVtxBuffPasswordBG3 = NULL;
	}
	if (g_pVtxBuffPasswordBG4 != NULL)
	{
		g_pVtxBuffPasswordBG4->Release();
		g_pVtxBuffPasswordBG4 = NULL;
	}
	if (g_pVtxBuffPasswordBG5 != NULL)
	{
		g_pVtxBuffPasswordBG5->Release();
		g_pVtxBuffPasswordBG5 = NULL;
	}
}
// �w�i�̍X�V����
void UpdatePasswordBackGround(void)
{

}
// �w�i�̕`�揈��
void DrawPasswordBackGround(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// �f�o�C�X�̎擾


	// ����
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG2, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��


	// ���͉��
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��


	// �o�͉��
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG3, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��


	// �����
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG4, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePasswordBG4);
	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��


	// �q���g
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordBG5, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePasswordBG5);
	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��
}