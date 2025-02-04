//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================

#include "main.h"
#include "password_block.h"
#include "password_particle.h"

//�}�N��
#define MAX_BLOCK (256)		//�u���b�N�̍ő吔
#define NUM_BLOCK (3)		//���
#define BLOCK_HABA (40.0f)	//��
#define BLOCK_TAKASA (40.0f)//����

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTexturePassBlock[NUM_BLOCK] = {};     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassBlock = NULL;			//���_�o�b�t�@�ւ̃|�C���^
PASSWORDBLOCK g_aPassBlock[MAX_BLOCK];						//�u���b�N�̏��

void InitPassBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPassBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//"data\\TEXTURE\\block2.png",		//�e�N�X�`���̃t�@�C����
	//	&g_pTexturePassBlock[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sand.jpg",		//�e�N�X�`���̃t�@�C����
		&g_pTexturePassBlock[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block1.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassBlock[2]);

	//�u���b�N�̏��̏�����
	for (nCntPassBlock = 0; nCntPassBlock < MAX_BLOCK; nCntPassBlock++)
	{
		g_aPassBlock[nCntPassBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPassBlock[nCntPassBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPassBlock[nCntPassBlock].fWidth = 0.0f;
		g_aPassBlock[nCntPassBlock].fHeight = 0.0f;
		g_aPassBlock[nCntPassBlock].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
		g_aPassBlock[nCntPassBlock].nMoveCnt = 0;
	}

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
														D3DUSAGE_WRITEONLY,
														FVF_VERTEX_2D,
														D3DPOOL_MANAGED,
														&g_pVtxBuffPassBlock,
														NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPassBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPassBlock = 0; nCntPassBlock < MAX_BLOCK; nCntPassBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].fHeight,0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].fHeight,0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].fHeight,0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].fHeight,0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//0.0�`1.0�Őݒ�
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPassBlock->Unlock();
}
void UninitPassBlock(void)
{
	for (int nCntPassBlock = 0; nCntPassBlock < NUM_BLOCK; nCntPassBlock++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePassBlock[nCntPassBlock] != NULL)
		{
			g_pTexturePassBlock[nCntPassBlock]->Release();
			g_pTexturePassBlock[nCntPassBlock] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPassBlock != NULL)
	{
		g_pVtxBuffPassBlock->Release();
		g_pVtxBuffPassBlock = NULL;
	}
}
void UpdatePassBlock(void)
{
	VERTEX_2D* pVtx = 0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPassBlock = 0; nCntPassBlock < MAX_BLOCK; nCntPassBlock++)
	{
		if (g_aPassBlock[nCntPassBlock].bUse == true)
		{
			g_aPassBlock[nCntPassBlock].nMoveCnt++;
			if (g_aPassBlock[nCntPassBlock].nType == 0)
			{
				if (g_aPassBlock[nCntPassBlock].nMoveCnt >= 60)
				{
					g_aPassBlock[nCntPassBlock].move *= -1.0f;
					g_aPassBlock[nCntPassBlock].nMoveCnt = 0;
				}
			}
			//�ʒu���X�V
			g_aPassBlock[nCntPassBlock].pos.x += g_aPassBlock[nCntPassBlock].move.x;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x - 5.0f, g_aPassBlock[nCntPassBlock].pos.y - 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x + 5.0f, g_aPassBlock[nCntPassBlock].pos.y - 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x - 5.0f, g_aPassBlock[nCntPassBlock].pos.y + 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x + 5.0f, g_aPassBlock[nCntPassBlock].pos.y + 5.0f, 0.0f);

			if (g_aPassBlock[nCntPassBlock].nType == 0)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);//0.0�`1.0�Őݒ�
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			}
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassBlock->Unlock();
}
void DrawPassBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntPassBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPassBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPassBlock = 0; nCntPassBlock < MAX_BLOCK; nCntPassBlock++)
	{
		if (g_aPassBlock[nCntPassBlock].bUse == true)
		{//�u���b�N���g�p����Ă���	
			int nType = g_aPassBlock[nCntPassBlock].nType;

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePassBlock[nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPassBlock * 4, 2);
		}
	}
}
//�u���b�N�̐ݒ菈��
void SetPassBlock(D3DXVECTOR3 pos,D3DXVECTOR3 move,float fWidth,float fHeight,int nType)
{
	int nCntPassBlock;
	VERTEX_2D* pVtx=0;
	
	//���b�N
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPassBlock = 0; nCntPassBlock < MAX_BLOCK; nCntPassBlock++)
	{
		if (g_aPassBlock[nCntPassBlock].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ�
			g_aPassBlock[nCntPassBlock].pos = pos;
			g_aPassBlock[nCntPassBlock].move = move;
			g_aPassBlock[nCntPassBlock].fWidth = fWidth;
			g_aPassBlock[nCntPassBlock].fHeight = fHeight;
			g_aPassBlock[nCntPassBlock].nType = nType;
			g_aPassBlock[nCntPassBlock].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x - g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].pos.y - g_aPassBlock[nCntPassBlock].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x + g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].pos.y - g_aPassBlock[nCntPassBlock].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x - g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].pos.y + g_aPassBlock[nCntPassBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPassBlock[nCntPassBlock].pos.x + g_aPassBlock[nCntPassBlock].fWidth, g_aPassBlock[nCntPassBlock].pos.y + g_aPassBlock[nCntPassBlock].fHeight, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//0.0�`1.0�Őݒ�
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			//�e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(fWidth / BLOCK_HABA, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fWidth / BLOCK_HABA, 1.0f);

			break;
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//�A�����b�N
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPassBlock->Unlock();
}
PASSWORDBLOCK* GetPassBlock(void)
{
	return g_aPassBlock;
}