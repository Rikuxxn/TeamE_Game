//---------------------------------------------------------
// 
// Author:Yoshida Atyushi
//---------------------------------------------------------

#include "main.h"
#include "shooting_background2.h"

// �O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureBG3 = { NULL };		// �����ʃe�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG3 = NULL;		// �����ʒ��_�o�b�t�@�ւ̃|�C���^

// �w�i�̏���������
void InitBackGround2(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	// �����ʃe�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Shooting_Board �̃R�s�[.png",	// �e�N�X�`���̃t�@�C����
		&g_pTextureBG3);

	// �����ʒ��_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG3,
		NULL);

	VERTEX_2D* pVtx;// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG3->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(640.0f - BACKGROUNDTUTORIAL_WIDTH, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(640.0f + BACKGROUNDTUTORIAL_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(640.0f - BACKGROUNDTUTORIAL_WIDTH, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(640.0f + BACKGROUNDTUTORIAL_WIDTH, 720.0f, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG3->Unlock();
}
// �w�i�̏I������
void UninitBackGround2(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureBG3 != NULL)
	{
		g_pTextureBG3->Release();
		g_pTextureBG3 = NULL;
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG3 != NULL)
	{
		g_pVtxBuffBG3->Release();
		g_pVtxBuffBG3 = NULL;
	}
}
// �w�i�̍X�V����
void UpdateBackGround2(void)
{

}
// �w�i�̕`�揈��
void DrawBackGround2(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^

	// ������
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBG3, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBG3);
	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��

}