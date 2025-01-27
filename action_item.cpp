//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "action_item.h"
#include "action_player.h"
#include "main.h"
#include "action_particle.h"

//�}�N��
#define MAX_ITEM (512)	//�A�C�e���̍ő吔
#define NUM_ITEM (3)	//�A�C�e���̎��
#define BLOCK_HABA (40.0f)
#define BLOCK_TAKASA (20.0f)

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureItem = {};		  //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;//���_�o�b�t�@�ւ̃|�C���^
ACTIONITEM g_item;								  //�A�C�e���̏��

void InitActionItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\item2.png",      //�e�N�X�`���̃t�@�C����
			&g_pTextureItem);

	g_item.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_item.fWidth = 0.0f;
	g_item.fHeight = 0.0f;
	g_item.bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	g_item.bDisp = false;
	g_item.bGet = false;
	

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem, NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_item.fWidth, g_item.fHeight,0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_item.fWidth, g_item.fHeight,0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_item.fWidth, g_item.fHeight,0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_item.fWidth, g_item.fHeight,0.0f);

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

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}
void UninitActionItem(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}
void UpdateActionItem(void)
{

}
void DrawActionItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_item.bDisp == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[��
		pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		if (g_item.bUse != false)
		{//�A�C�e�����g�p����Ă���	

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}
//�A�C�e���̐ݒ菈��
void SetActionItem(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	VERTEX_2D* pVtx=0;
	
	//���b�N
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	if (g_item.bUse == false)
	{//�A�C�e�����g�p����Ă��Ȃ�
		g_item.pos = pos;
		g_item.fWidth = fWidth;
		g_item.fHeight = fHeight;
		g_item.nType = nType;
		g_item.bUse = true;
		g_item.bDisp = true;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_item.pos.x - g_item.fWidth, g_item.pos.y - g_item.fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_item.pos.x + g_item.fWidth, g_item.pos.y - g_item.fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_item.pos.x - g_item.fWidth, g_item.pos.y + g_item.fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_item.pos.x + g_item.fWidth, g_item.pos.y + g_item.fHeight, 0.0f);

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	}

	//�A�����b�N
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}
//�A�C�e���̂�����͂�Ă�
bool CollisionActionItem(D3DXVECTOR3* pPos,		//���݂̈ʒu
						 D3DXVECTOR3* pPosOld,	//�O��̈ʒu
						 D3DXVECTOR3* pMove,	//�ړ���
						 float fWidth,			//��
						 float fHeight)			//����
{
	bool bUse = false;//���n���Ă��邩�ǂ���
	ActionPlayer* pPlayer = GetActionPlayer();

	if (g_item.bUse == true && g_item.bGet==false)
	{//�g�p���Ă���A�C�e����S�ă`�F�b�N����
		if ((g_item.pos.x - g_item.fWidth >= pPlayer->pos.x - HABA / 2 ||
			g_item.pos.x + g_item.fWidth >= pPlayer->pos.x + HABA / 2) &&
			g_item.pos.y - g_item.fHeight >= pPlayer->pos.y - TAKASA / 2)
		{
			g_item.bDisp = false;
			g_item.bGet = true;
		}
	}
	return bUse;
}
bool GetActionItem(void)
{
	return g_item.bGet;
}