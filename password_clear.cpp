//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_clear.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTexturePasswordClear = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordClear = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//�N���A�̏���������
void InitPasswordClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBG;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Complete.png",//�e�N�X�`���̃t�@�C����
		&g_apTexturePasswordClear);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordClear,
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPasswordClear->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < 3; nCntBG++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(440.0f, 260.0f, 0.0f);//��400.0f
		pVtx[1].pos = D3DXVECTOR3(840.0f, 260.0f, 0.0f);//����150.0f
		pVtx[2].pos = D3DXVECTOR3(440.0f, 410.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(840.0f, 410.0f, 0.0f);

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

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPasswordClear->Unlock();
}
//�N���A�̏I������
void UninitPasswordClear(void)
{
	//�e�N�X�`���̔j��
	if (g_apTexturePasswordClear != NULL)
	{
		g_apTexturePasswordClear->Release();
		g_apTexturePasswordClear = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPasswordClear != NULL)
	{
		g_pVtxBuffPasswordClear->Release();
		g_pVtxBuffPasswordClear = NULL;
	}
}
//�N���A�̍X�V����
void UpdatePasswordClear(void)
{

}
//�N���A�̕`�揈��
void DrawPasswordClear(void)
{
	//�e�N�X�`��3���̕`��+(�K�v�Ȃ�)��������w�i
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordClear, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTexturePasswordClear);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��
}