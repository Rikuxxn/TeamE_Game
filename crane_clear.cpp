//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "crane_clear.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureCraneClear = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneClear = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//�N���A�̏���������
void InitCraneClear(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\CLEAR.png",//�e�N�X�`���̃t�@�C����
		&g_apTextureCraneClear);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneClear,
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCraneClear->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(440.0f, 160.0f, 0.0f);//��400.0f
	pVtx[1].pos = D3DXVECTOR3(840.0f, 160.0f, 0.0f);//����150.0f
	pVtx[2].pos = D3DXVECTOR3(440.0f, 310.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(840.0f, 310.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCraneClear->Unlock();
}
//�N���A�̏I������
void UninitCraneClear(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureCraneClear != NULL)
	{
		g_apTextureCraneClear->Release();
		g_apTextureCraneClear = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCraneClear != NULL)
	{
		g_pVtxBuffCraneClear->Release();
		g_pVtxBuffCraneClear = NULL;
	}

}
//�N���A�̍X�V����
void UpdateCraneClear(void)
{

}
//�N���A�̕`�揈��
void DrawCraneClear(void)
{
	//�e�N�X�`��3���̕`��+(�K�v�Ȃ�)��������w�i
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffCraneClear, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureCraneClear);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��
}