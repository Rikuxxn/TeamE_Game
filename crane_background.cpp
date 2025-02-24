//=======================================================
// 
// �N���[���Q�[���̔w�i���� [ crane_background.cpp ]
// Author:Yoshida Atsushi
// 
//=======================================================

// �C���N���[�h�t�@�C��
#include "crane_background.h"

// �}�N����`
#define NUM_BG (2)// �w�i�̐�

// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureCraneBG[NUM_BG] = { NULL };// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureCraneBG3 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneBG = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneBG2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneBG3 = NULL;
float g_aPosCraneTexU[NUM_BG];							// �e�N�X�`�����W�̊J�n�ʒu�iU�l�j

// �w�i�̏���������
void InitCraneBackGround(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^
	int nCntBG;

	// �e�N�X�`��(�Q�[�����)�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Clane_Back.jpg",// �e�N�X�`���̃t�@�C����
		&g_pTextureCraneBG[0]);

	// �e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Clane_Board.jpg",// �e�N�X�`���̃t�@�C����
		&g_pTextureCraneBG3);

	//
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosCraneTexU[nCntBG] = 0.0f;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneBG,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneBG2,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneBG3,
		NULL);

	VERTEX_2D* pVtx;// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCraneBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG;nCntBG++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(CLANEFIELD_LEFT, CLANEFIELD_TOP, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(CLANEFIELD_RIGHT, CLANEFIELD_TOP, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(CLANEFIELD_LEFT, CLANEFIELD_UNDER, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(CLANEFIELD_RIGHT, CLANEFIELD_UNDER, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aPosCraneTexU[nCntBG], 0.0f);// (u,v)
		pVtx[1].tex = D3DXVECTOR2(g_aPosCraneTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosCraneTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosCraneTexU[nCntBG] + 1.0f, 1.0f);

		pVtx += 4;// ���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCraneBG->Unlock();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCraneBG2->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 150);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCraneBG2->Unlock();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCraneBG3->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(CLANEFIELD_LEFT - 30.0f, 0.0f, 0.0f);// ��400.0f
	pVtx[1].pos = D3DXVECTOR3(CLANEFIELD_RIGHT + 30.0f, 0.0f, 0.0f);// ����150.0f
	pVtx[2].pos = D3DXVECTOR3(CLANEFIELD_LEFT - 30.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(CLANEFIELD_RIGHT + 30.0f, 720.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);// (u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCraneBG3->Unlock();
}
// �w�i�̏I������
void UninitCraneBackGround(void)
{
	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureCraneBG[nCntBG] != NULL)
		{
			g_pTextureCraneBG[nCntBG]->Release();
			g_pTextureCraneBG[nCntBG] = NULL;
		}
	}
	if (g_pTextureCraneBG3 != NULL)
	{
		g_pTextureCraneBG3->Release();
		g_pTextureCraneBG3 = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffCraneBG != NULL)
	{
		g_pVtxBuffCraneBG->Release();
		g_pVtxBuffCraneBG = NULL;
	}
	if (g_pVtxBuffCraneBG2 != NULL)
	{
		g_pVtxBuffCraneBG2->Release();
		g_pVtxBuffCraneBG2 = NULL;
	}
	if (g_pVtxBuffCraneBG3 != NULL)
	{
		g_pVtxBuffCraneBG3->Release();
		g_pVtxBuffCraneBG3 = NULL;
	}
}
// �w�i�̍X�V����
void UpdateCraneBackGround(void)
{

}
// �w�i�̕`�揈��
void DrawCraneBackGround(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	// ������
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffCraneBG2, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��

	// �`���[�g���A��
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffCraneBG3, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureCraneBG3);

	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��

	// 3����
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffCraneBG, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCraneBG[0]);

		// �w�i�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
			0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
			2);                                    // �`�悷��v���~�e�B�u��
	}
}