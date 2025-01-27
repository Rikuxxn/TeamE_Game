//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "action_block.h"
#include "action_player.h"
#include "main.h"
#include "action_particle.h"

//�}�N��
#define MAX_BLOCK (512)	//�u���b�N�̍ő吔
#define NUM_BLOCK (3)	//�u���b�N�̎��
#define BLOCK_HABA (40.0f)
#define BLOCK_TAKASA (40.0f)

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureBlock[NUM_BLOCK] = {};     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;//���_�o�b�t�@�ւ̃|�C���^
ACTIONBLOCK g_aBlock[MAX_BLOCK];					//�u���b�N�̏��
bool g_bTyakuti;

void InitActionBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\block2.png",		//�e�N�X�`���̃t�@�C����
		&g_pTextureBlock[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sand.jpg",		//�e�N�X�`���̃t�@�C����
		&g_pTextureBlock[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block1.png",	//�e�N�X�`���̃t�@�C����
		&g_pTextureBlock[2]);

	//�u���b�N�̏��̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
		g_aBlock[nCntBlock].nMoveCnt = 0;
	}

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBlock, NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight,0.0f);

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
	g_pVtxBuffBlock->Unlock();
}
void UninitActionBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < NUM_BLOCK; nCntBlock++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}

		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffBlock != NULL)
		{
			g_pVtxBuffBlock->Release();
			g_pVtxBuffBlock = NULL;
		}

	}
}
void UpdateActionBlock(void)
{
	VERTEX_2D* pVtx = 0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
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
			//�ʒu���X�V
			g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 5.0f, g_aBlock[nCntBlock].pos.y - 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 5.0f, g_aBlock[nCntBlock].pos.y - 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 5.0f, g_aBlock[nCntBlock].pos.y + 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 5.0f, g_aBlock[nCntBlock].pos.y + 5.0f, 0.0f);
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}
void DrawActionBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă���	
			int nType = g_aBlock[nCntBlock].nType;

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBlock*4 , 2);
		}
	}
}
//�u���b�N�̐ݒ菈��
void SetActionBlock(D3DXVECTOR3 pos,D3DXVECTOR3 move,float fWidth,float fHeight,int nType)
{
	int nCntBlock;
	VERTEX_2D* pVtx=0;
	
	//���b�N
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ�
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].move = move;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

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
	g_pVtxBuffBlock->Unlock();
}
//�u���b�N�̂�����͂�Ă�
bool CollisionActionBlock(D3DXVECTOR3* pPos,		 //���݂̈ʒu
						D3DXVECTOR3* pPosOld,//�O��̈ʒu
						D3DXVECTOR3* pMove,	 //�ړ���
						float fWidth,		 //��
						float fHeight,		 //����
						ACTIONBLOCK**pBlock)
{
	bool bLanding = false;//���n���Ă��邩�ǂ���
	ActionPlayer* pPlayer=GetActionPlayer();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�g�p���Ă���u���b�N��S�ă`�F�b�N����
			if (pPos->x + HABA / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth &&
				pPos->x - HABA / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)//�v���C���[��x�͈̔͂��u���b�N�ɏd�Ȃ��Ă���
			{
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight &&
					pPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)//�u���b�N�ɏォ��߂荞��
				{
					pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;//�u���b�N�̍���
					pMove->y = 0.0f;
					bLanding = true;
					pPlayer->bLanding = true;
					if (pBlock != NULL)
					{//�u���b�N�̃A�h���X�������ꏊ������
						*pBlock = &g_aBlock[nCntBlock];//�u���b�N�̃A�h���X����
					}
				}
				else if (pPosOld->y - TAKASA >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPos->y - TAKASA < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)//������
				{
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight  + TAKASA;
					pMove->y = 0.0f;
				}
			}
			if (pPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight &&
				pPosOld->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)//�v���C���[�̑O���y�͈̔͂��u���b�N�ɏd�Ȃ��Ă���
			{
				if (pPosOld->x + HABA <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth &&
					pPos->x + HABA >= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth)//������
				{
					pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - HABA;
					pMove->x = 0.0f;
				}
				else if (pPosOld->x - HABA >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth &&
					pPos->x - HABA <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)//�E����
				{
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + HABA;
					pMove->x = 0.0f;
				}
			}
		}
	}
	return bLanding;
}
bool CollisionActionBlock2(D3DXVECTOR3* pPos,		 //���݂̈ʒu
						D3DXVECTOR3* pPosOld,//�O��̈ʒu
						D3DXVECTOR3* pMove,	 //�ړ���
						float fWidth,		 //��
						float fHeight)		 //����
{
	bool bUse = true;//���n���Ă��邩�ǂ���
	ActionPlayer* pPlayer = GetActionPlayer();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�g�p���Ă���u���b�N��S�ă`�F�b�N����
			if (pPos->y >= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight/2 && pPosOld->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)//�v���C���[�̑O���y�͈̔͂��u���b�N�ɏd�Ȃ��Ă���
			{
				if (pPosOld->x + HABA <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth 
					&& pPos->x + HABA > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth)
				{//������
					pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - HABA;
				}
				else if (pPosOld->x - HABA >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth 
					&& pPos->x - HABA < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
				{//�E����
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + HABA;
				}
			}
		}
	}
	return bUse;
}