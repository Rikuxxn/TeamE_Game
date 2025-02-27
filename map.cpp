//=========================================================
// 
// �~�j�}�b�v�\������ [map.cpp]
// Author : TANEKAWA RIKU
// 
//=========================================================
#include "map.h"
#include "player.h"
#include "input.h"
#include "meshfield.h"
#include "camera.h"

// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMap = { NULL };						// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayerIcon = NULL;						// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureNone = NULL;							// �e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMap = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerIcon = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNone = NULL;						// ���_�o�b�t�@�ւ̃|�C���^

Icon g_Icon;														// �A�C�R���̏��
Map g_Map;															// �}�b�v�̏��

//===============================
// �~�j�}�b�v�̏���������
//===============================
void InitMap(void)
{
	Player* pPlayer = GetPlayer();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\minimap.png",			// �e�N�X�`���̃t�@�C����
		&g_pTextureMap);

	// �e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\playerpos.png",			// �e�N�X�`���̃t�@�C����
		&g_pTexturePlayerIcon);

	// �e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\.png",					// �e�N�X�`���̃t�@�C����
		&g_pTextureNone);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMap,
		NULL);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerIcon,
		NULL);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNone,
		NULL);

	g_Map.pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f); // �����ʒu

	// �t�B�[���h�̕��ƍ���
	g_Map.fWidth = MAX_WIDTH / 3.0f;
	g_Map.fHeight = MAX_HEIGHT / 3.0f;

	// �A�C�R���̃T�C�Y�ݒ�
	g_Icon.fWidth = 15.0f;
	g_Icon.fHeight = 15.0f;

	// �~�j�}�b�v�̍�����W���v�Z
	float miniMapLeft	= g_Map.pos.x - g_Map.fWidth / 2.0f;
	float miniMapTop	= g_Map.pos.y - g_Map.fHeight / 2.0f;

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(miniMapLeft, miniMapTop, 0.0f);									// ����
	pVtx[1].pos = D3DXVECTOR3(miniMapLeft + g_Map.fWidth, miniMapTop, 0.0f);					// �E��
	pVtx[2].pos = D3DXVECTOR3(miniMapLeft, miniMapTop + g_Map.fHeight, 0.0f);					// ����
	pVtx[3].pos = D3DXVECTOR3(miniMapLeft + g_Map.fWidth, miniMapTop + g_Map.fHeight, 0.0f);	// �E��

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMap->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayerIcon->Lock(0, 0, (void**)&pVtx, 0);

	float size = g_Icon.fWidth;// �v���C���[�A�C�R���̑傫��

	// �v���C���[�A�C�R���̒��_��ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Icon.pos.x - size, g_Icon.pos.y - size, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Icon.pos.x + size, g_Icon.pos.y - size, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Icon.pos.x - size, g_Icon.pos.y + size, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Icon.pos.x + size, g_Icon.pos.y + size, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayerIcon->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffNone->Lock(0, 0, (void**)&pVtx, 0);

	// ���Â��w�i�̒��_��ݒ�
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
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffNone->Unlock();

}
//===============================
// �~�j�}�b�v�̏I������
//===============================
void UninitMap(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureMap != NULL)
	{
		g_pTextureMap->Release();
		g_pTextureMap = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pTexturePlayerIcon != NULL)
	{
		g_pTexturePlayerIcon->Release();
		g_pTexturePlayerIcon = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pTextureNone != NULL)
	{
		g_pTextureNone->Release();
		g_pTextureNone = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMap != NULL)
	{
		g_pVtxBuffMap->Release();
		g_pVtxBuffMap = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayerIcon != NULL)
	{
		g_pVtxBuffPlayerIcon->Release();
		g_pVtxBuffPlayerIcon = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffNone != NULL)
	{
		g_pVtxBuffNone->Release();
		g_pVtxBuffNone = NULL;
	}

}
//===============================
// �~�j�}�b�v�̍X�V����
//===============================
void UpdateMap(void)
{

	Player* pPlayer = GetPlayer();
	Camera* pCamera = GetCamera();

	// �~�j�}�b�v�̍���̍��W
	float miniMapLeft	= g_Map.pos.x - g_Map.fWidth / 2.0f;
	float miniMapTop	= g_Map.pos.y - g_Map.fHeight / 2.0f;

	// �X�P�[���i���[���h���W �� �~�j�}�b�v���W�ϊ��p�j
	float scaleX = g_Map.fWidth / MAX_WIDTH;   // 600 / 2400 = 0.25
	float scaleY = g_Map.fHeight / MAX_HEIGHT; // 500 / 2000 = 0.25

	// �v���C���[�̍��W���~�j�}�b�v���W�ɕϊ�
	g_Icon.pos.x = miniMapLeft + (pPlayer->pos.x + (MAX_WIDTH / 2.0f)) * scaleX;
	g_Icon.pos.y = miniMapTop - (pPlayer->pos.z - (MAX_HEIGHT / 2.0f)) * scaleY;
	g_Icon.pos.z = 0.0f;

	// �v���C���[�̉�]���A�C�R���ɔ��f
	g_Icon.rot.y = pCamera->rot.y; // �J������Y����]

	// ���_�o�b�t�@���X�V
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffPlayerIcon->Lock(0, 0, (void**)&pVtx, 0);

	// ��]�s��
	D3DXMATRIX matRot;
	D3DXMatrixRotationZ(&matRot, g_Icon.rot.y); // Z����]�i2D��]�j

	// �A�C�R���̒��_����]
	D3DXVECTOR3 v[4] =
	{
		{  g_Icon.fWidth,  g_Icon.fHeight, 0.0f },
		{ -g_Icon.fWidth,  g_Icon.fHeight, 0.0f },
		{  g_Icon.fWidth, -g_Icon.fHeight, 0.0f },
		{ -g_Icon.fWidth, -g_Icon.fHeight, 0.0f }
	};

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		D3DXVec3TransformCoord(&v[nCnt], &v[nCnt], &matRot);
		pVtx[nCnt].pos = D3DXVECTOR3(g_Icon.pos.x + v[nCnt].x, g_Icon.pos.y + v[nCnt].y, 0.0f);
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPlayerIcon->Unlock();
}
//===============================
// �~�j�}�b�v�̕`�揈��
//===============================
void DrawMap(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//====================
	// ���Â��w�i�̕`��
	//====================

	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffNone, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��


	//===============
	// �}�b�v�̕`��
	//===============

	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffMap, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMap);

	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��


	//==========================
	// �v���C���[�A�C�R���̕`��
	//==========================

	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerIcon, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayerIcon);

	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��

}