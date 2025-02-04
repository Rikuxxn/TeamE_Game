//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "crane_item.h"
#include "crane_player.h"
#include "crane_particle.h"
#include "crane_block.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureItem[NUM_ITEM] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;		//���_�o�b�t�@�ւ̃|�C���^
CRANEITEM g_item[MAX_ITEM];							//�A�C�e���̏��
int g_nItem;

void InitCraneItem(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\item.png",		//�e�N�X�`���̃t�@�C����
		&g_pTextureItem[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\item2.png",		//�e�N�X�`���̃t�@�C����
		&g_pTextureItem[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\item3.png",		//�e�N�X�`���̃t�@�C����
		&g_pTextureItem[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\item4.png",		//�e�N�X�`���̃t�@�C����
		&g_pTextureItem[3]);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_item[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_item[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_item[nCntItem].fWidth = 0.0f;
		g_item[nCntItem].fHeight = 0.0f;
		g_item[nCntItem].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
		g_item[nCntItem].bGet = false;
		g_item[nCntItem].bcatch = false;
	}
	g_nItem = 0;

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_item[nCntItem].fWidth, g_item[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_item[nCntItem].fWidth, g_item[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_item[nCntItem].fWidth, g_item[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_item[nCntItem].fWidth, g_item[nCntItem].fHeight, 0.0f);

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
	g_pVtxBuffItem->Unlock();
}
void UninitCraneItem(void)
{
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem]->Release();
			g_pTextureItem[nCntItem] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}
void UpdateCraneItem(void)
{
	VERTEX_2D* pVtx = 0;
	CranePlayer* pPlayer = GetCranePlayer();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (pPlayer->bMove == false &&
			g_item[nCntItem].bcatch == true &&
			g_item[nCntItem].pos.x >= pPlayer->pos.x - ITEM_WIDTH
			&& g_item[nCntItem].pos.x <= pPlayer->pos.x + ITEM_WIDTH)
		{
			g_item[nCntItem].pos = pPlayer->pos;
		}
		if (pPlayer->bLeft == false &&
			pPlayer->bFall == true &&
			g_item[nCntItem].bcatch == false)
		{
			g_item[nCntItem].move.y = 4.5f;
		}

		g_item[nCntItem].pos += g_item[nCntItem].move;

		if (g_item[nCntItem].pos.y >= FIELD_UNDER - g_item[nCntItem].fHeight)//�n��
		{
			g_item[nCntItem].pos.y = FIELD_UNDER - g_item[nCntItem].fHeight;
			//g_item[nCntItem].bcatch = false;
		}
		if (g_item[nCntItem].pos.y >= ITEM_CLEARPOSY &&
			g_item[nCntItem].pos.x - g_item[nCntItem].fWidth >= ITEM_CLEARPOSX - ITEM_CLEARZONE &&
			g_item[nCntItem].pos.x + g_item[nCntItem].fWidth <= ITEM_CLEARPOSX + ITEM_CLEARZONE &&
			g_item[nCntItem].bcatch == true &&
			g_item[nCntItem].bUse == true &&
			pPlayer->bFall == true)
		{//�A�C�e���Q�b�g
			g_item[nCntItem].bUse = false;
			pPlayer->bFall = false;
			g_nItem--;
		}
	}

	//���b�N
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);
	
		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//�A�����b�N
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}
//
void DrawCraneItem(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse != false)
		{//�A�C�e�����g�p����Ă���	

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_item[nCntItem].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}
//�A�C�e���̐ݒ菈��
void SetCraneItem(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	VERTEX_2D* pVtx=0;
	
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == false)
		{//�A�C�e�����g�p����Ă��Ȃ�
			g_item[nCntItem].pos = pos;
			g_item[nCntItem].fWidth = fWidth;
			g_item[nCntItem].fHeight = fHeight;
			g_item[nCntItem].nType = nType;
			g_item[nCntItem].bUse = true;
			g_item[nCntItem].bcatch = false;
			g_nItem++;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);

			//�e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}
//�A�C�e���̌�
int GetNumItem(void)
{
	return g_nItem;
}
CRANEITEM GetItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		return g_item[nCntItem];
	}
}
//�A�C�e���̂�����͂�Ă�
bool CollisionCraneItem(D3DXVECTOR3* pPos,		//���݂̈ʒu
						 D3DXVECTOR3* pPosOld,	//�O��̈ʒu
						 D3DXVECTOR3* pMove,	//�ړ���
						 float fWidth,			//��
						 float fHeight)			//����
{
	bool bUse = false;//���n���Ă��邩�ǂ���
	CranePlayer* pPlayer = GetCranePlayer();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{

		if (g_item[nCntItem].bUse == true && g_item[nCntItem].bGet == false)
		{//�g�p���Ă���A�C�e����S�ă`�F�b�N����
			if (g_item[nCntItem].pos.x >= pPlayer->pos.x - ITEM_WIDTH
				&& g_item[nCntItem].pos.x <= pPlayer->pos.x + ITEM_WIDTH
				&& g_item[nCntItem].pos.y >= pPlayer->pos.y - ITEM_HEIGHT
				&& g_item[nCntItem].pos.y <= pPlayer->pos.y + ITEM_HEIGHT
				&& pPlayer->pos.x >= FIELD_LEFT + 75.0f + HABA)
			{
				g_item[nCntItem].bcatch = true;
			}
		}
	}
	return bUse;
}