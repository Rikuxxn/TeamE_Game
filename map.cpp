//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "map.h"
#include "player.h"
#include "input.h"
#include "meshfield.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureMap = { NULL };//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayerIcon = NULL;//�e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMap = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerIcon = NULL;//���_�o�b�t�@�ւ̃|�C���^

float g_aPosCraneTexU;//�e�N�X�`�����W�̊J�n�ʒu�iU�l�j

//�w�i�̏���������
void InitMap(void)
{
	Player* pPlayer = GetPlayer();

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\map.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureMap);

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\playerpos.png",//�e�N�X�`���̃t�@�C����
		&g_pTexturePlayerIcon);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMap,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerIcon,
		NULL);

	float PlayerPosX = pPlayer->pos.x;  // �v���C���[�̈ʒu���擾
	float PlayerPosY = pPlayer->pos.y;	// �v���C���[�̈ʒu���擾


	// �t�B�[���h�̕��ƍ���
	float fieldWidth = MAX_WIDTH;
	float fieldHeight = MAX_HEIGHT;

	// �~�j�}�b�v�̕��ƍ���
	float miniMapWidth = MINIMAP_RIGHT - MINIMAP_LEFT;
	float miniMapHeight = MINIMAP_UNDER - MINIMAP_TOP;

	// �X�P�[���i�k�ځj�̌v�Z
	float scaleX = miniMapWidth / fieldWidth;
	float scaleY = miniMapHeight / fieldHeight;

	// �v���C���[�̍��W���~�j�}�b�v�̍��W�ɕϊ�
	float miniMapPlayerX = MINIMAP_LEFT + (pPlayer->pos.x / fieldWidth) * miniMapWidth;
	float miniMapPlayerY = MINIMAP_TOP + (pPlayer->pos.y / fieldHeight) * miniMapHeight;

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(MINIMAP_LEFT - 50.0f, MINIMAP_TOP, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(MINIMAP_RIGHT + 50.f, MINIMAP_TOP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(MINIMAP_LEFT - 50.0f, MINIMAP_UNDER + 200.f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MINIMAP_RIGHT + 50.f, MINIMAP_UNDER + 200.f, 0.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMap->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayerIcon->Lock(0, 0, (void**)&pVtx, 0);

	float size = 5.0f; // �~�j�}�b�v��ł̃v���C���[�A�C�R���̑傫��

	// �~�j�}�b�v��̍��W�Ńv���C���[�A�C�R���̒��_��ݒ�
	pVtx[0].pos = D3DXVECTOR3(miniMapPlayerX - size, miniMapPlayerY - size, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(miniMapPlayerX + size, miniMapPlayerY - size, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(miniMapPlayerX - size, miniMapPlayerY + size, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(miniMapPlayerX + size, miniMapPlayerY + size, 0.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayerIcon->Unlock();

}
//�w�i�̏I������
void UninitMap(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMap != NULL)
	{
		g_pTextureMap->Release();
		g_pTextureMap = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTexturePlayerIcon != NULL)
	{
		g_pTexturePlayerIcon->Release();
		g_pTexturePlayerIcon = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMap != NULL)
	{
		g_pVtxBuffMap->Release();
		g_pVtxBuffMap = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayerIcon != NULL)
	{
		g_pVtxBuffPlayerIcon->Release();
		g_pVtxBuffPlayerIcon = NULL;
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


	//===============
	// �}�b�v�̕`��
	//===============

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffMap, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMap);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��


	//==========================
	// �v���C���[�A�C�R���̕`��
	//==========================

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerIcon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayerIcon);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��

}