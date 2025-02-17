//---------------------------------------------------------
// �{�[���v�[��
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "crane_hint.h"

// �O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureCraneHint = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureCraneHint2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneHint = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneHint2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneHint3 = NULL;

// �q���g�̏�����
void InitCraneHintBG(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bear.png",		// �e�N�X�`���̃t�@�C����
		&g_pTextureCraneHint);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\�摜2.png",		// �e�N�X�`���̃t�@�C����
		&g_pTextureCraneHint2);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneHint,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneHint2,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneHint3,
		NULL);

	VERTEX_2D* pVtx;// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCraneHint->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(440.0f, 160.0f, 0.0f);// ��400.0f
	pVtx[1].pos = D3DXVECTOR3(840.0f, 160.0f, 0.0f);// ����400.0f
	pVtx[2].pos = D3DXVECTOR3(440.0f, 560.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(840.0f, 560.0f, 0.0f);

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
	g_pVtxBuffCraneHint->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCraneHint2->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//��400.0f
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);	//����400.0f
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
	g_pVtxBuffCraneHint2->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCraneHint3->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(440.0f, 580.0f, 0.0f);//��400.0f
	pVtx[1].pos = D3DXVECTOR3(840.0f, 580.0f, 0.0f);//����400.0f
	pVtx[2].pos = D3DXVECTOR3(440.0f, 630.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(840.0f, 630.0f, 0.0f);

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
	g_pVtxBuffCraneHint3->Unlock();
}
// �q���g�̏I��
void UninitCraneHintBG(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureCraneHint != NULL)
	{
		g_pTextureCraneHint->Release();
		g_pTextureCraneHint = NULL;
	}
	if (g_pTextureCraneHint2 != NULL)
	{
		g_pTextureCraneHint2->Release();
		g_pTextureCraneHint2 = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffCraneHint != NULL)
	{
		g_pVtxBuffCraneHint->Release();
		g_pVtxBuffCraneHint = NULL;
	}
	if (g_pVtxBuffCraneHint2 != NULL)
	{
		g_pVtxBuffCraneHint2->Release();
		g_pVtxBuffCraneHint2 = NULL;
	}
	if (g_pVtxBuffCraneHint3 != NULL)
	{
		g_pVtxBuffCraneHint3->Release();
		g_pVtxBuffCraneHint3 = NULL;
	}
}
// �q���g�̍X�V
void UpdateCraneHintBG(void)
{

}
// �q���g�̕`��
void DrawCraneHintBG(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^

	// �w�i
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffCraneHint2, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��

	// �F
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffCraneHint, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureCraneHint);
	// �F�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��

	// ����������Ă���
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffCraneHint3, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureCraneHint2);
	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��
}