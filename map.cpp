//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "map.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureCraneMap = { NULL };//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneMap = NULL;//���_�o�b�t�@�ւ̃|�C���^
float g_aPosCraneTexU;//�e�N�X�`�����W�̊J�n�ʒu�iU�l�j

//�w�i�̏���������
void InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\map.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureCraneMap);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneMap,
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCraneMap->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(FIELD_LEFT - 50.0f, FIELD_TOP, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(FIELD_RIGHT + 50.f, FIELD_TOP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FIELD_LEFT - 50.0f, FIELD_UNDER + 200.f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(FIELD_RIGHT + 50.f, FIELD_UNDER + 200.f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)
}
//�w�i�̏I������
void UninitMap(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureCraneMap != NULL)
	{
		g_pTextureCraneMap->Release();
		g_pTextureCraneMap = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCraneMap != NULL)
	{
		g_pVtxBuffCraneMap->Release();
		g_pVtxBuffCraneMap = NULL;
	}
}
//�w�i�̍X�V����
void UpdateMap(void)
{

}
//�w�i�̕`�揈��
void DrawMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffCraneMap, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureCraneMap);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��
}