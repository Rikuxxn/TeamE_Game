//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "crane_block.h"
#include "crane_player.h"
#include "main.h"

// �}�N��
#define MAX_BLOCK (512)	// �u���b�N�̍ő吔
#define NUM_BLOCK (3)	// �u���b�N�̎��
#define BLOCK_HABA (40.0f)
#define BLOCK_TAKASA (40.0f)

// �O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureBlock[NUM_BLOCK] = {};     // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
CRANEBLOCK g_aBlock[MAX_BLOCK];							// �u���b�N�̏��
bool g_bTyakuti;

void InitCraneBlock(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();
	int nCntBlock;

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//"data\\TEXTURE\\block2.png",		//�e�N�X�`���̃t�@�C����
	//	&g_pTextureBlock[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sand.jpg",		// �e�N�X�`���̃t�@�C����
		&g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block1.png",
		&g_pTextureBlock[2]);

	// �u ���b�N�̏��̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].bUse = false;// �g�p���Ă��Ȃ���Ԃɂ���
		g_aBlock[nCntBlock].nMoveCnt = 0;
	}

	// ���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// 0.0�`1.0�Őݒ�
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;// ���_�f�[�^�̃|�C���^���S���i�߂�

	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}
void UninitCraneBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < NUM_BLOCK; nCntBlock++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}
void UpdateCraneBlock(void)
{
	VERTEX_2D* pVtx = 0;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			g_aBlock[nCntBlock].nMoveCnt++;
			if (g_aBlock[nCntBlock].nType == 0)
			{
				if (g_aBlock[nCntBlock].nMoveCnt >= 60)
				{
					g_aBlock[nCntBlock].move *= -1.0f;
					g_aBlock[nCntBlock].nMoveCnt = 0;
				}
			}
			// �ʒu���X�V
			g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;

			// ���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 5.0f, g_aBlock[nCntBlock].pos.y - 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 5.0f, g_aBlock[nCntBlock].pos.y - 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 5.0f, g_aBlock[nCntBlock].pos.y + 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 5.0f, g_aBlock[nCntBlock].pos.y + 5.0f, 0.0f);

			if (g_aBlock[nCntBlock].nType == 0)
			{
				// ���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);// 0.0�`1.0�Őݒ�
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			}
		}
		pVtx += 4;// ���_�f�[�^�̃|�C���^���S���i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}
void DrawCraneBlock(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^

	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{// �u���b�N���g�p����Ă���	
			int nType = g_aBlock[nCntBlock].nType;

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}
// �u���b�N�̐ݒ菈��
void SetCraneBlock(D3DXVECTOR3 pos,D3DXVECTOR3 move,float fWidth,float fHeight,int nType)
{
	VERTEX_2D* pVtx=0;
	
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{// �u���b�N���g�p����Ă��Ȃ�
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].move = move;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);// 0.0�`1.0�Őݒ�
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			// �e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(fWidth / BLOCK_HABA, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fWidth / BLOCK_HABA, 1.0f);

			break;
		}
		pVtx += 4;// ���_�f�[�^�̃|�C���^���S���i�߂�
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}
CRANEBLOCK* GetBlock(void)
{
	return g_aBlock;
}