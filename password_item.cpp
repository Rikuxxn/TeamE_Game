//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================

#include "input.h"
#include "main.h"
#include "password_block.h"
#include "password_item.h"
#include "password_particle.h"
#include "password_score.h"
#include "password_game.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTexturePassItem[NUM_ITEM] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassItem = NULL;		//���_�o�b�t�@�ւ̃|�C���^
PASSWORDITEM g_item[MAX_ITEM];							//�A�C�e���̏��
bool g_bJudgment;
bool g_bReset;

// �|�[�Y���ڂ̊g�嗦���Ǘ�����z��
float passScales[MAX_ITEM] = { ITEM_MIN_SCALE, ITEM_MIN_SCALE, ITEM_MIN_SCALE, ITEM_MIN_SCALE };

//�A�C�e���̏�����
void InitPasswordItem(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_0.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_1.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_2.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_3.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_4.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_5.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[5]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_6.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[6]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_7.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[7]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_8.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[8]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Num_9.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[9]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enter.png",	//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[10]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Delete.png",//�e�N�X�`���̃t�@�C����
		&g_pTexturePassItem[11]);

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
	g_bJudgment = false;

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPassItem,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPassItem->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffPassItem->Unlock();
}
//�A�C�e���̏I������
void UninitPasswordItem(void)
{
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePassItem[nCntItem] != NULL)
		{
			g_pTexturePassItem[nCntItem]->Release();
			g_pTexturePassItem[nCntItem] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPassItem != NULL)
	{
		g_pVtxBuffPassItem->Release();
		g_pVtxBuffPassItem = NULL;
	}
}
//�A�C�e���̍X�V
void UpdatePasswordItem(void)
{
	VERTEX_2D* pVtx = 0;
	g_bJudgment = GetJudge();

	// �}�E�X�J�[�\���̈ʒu���擾
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	// �E�B���h�E�n���h�����擾
	HWND hwnd = GetActiveWindow();

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�
	ScreenToClient(hwnd, &cursorPos);

	// �N���C�A���g�T�C�Y���擾
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	// �E�B���h�E�X�P�[�����v�Z
	float screenWidth = 1280.0f; // �Q�[���̉𑜓x
	float screenHeight = 720.0f;
	float scaleX = screenWidth / (clientRect.right - clientRect.left);
	float scaleY = screenHeight / (clientRect.bottom - clientRect.top);

	// �}�E�X���W���X�P�[��
	float mouseX = cursorPos.x * scaleX;
	float mouseY = cursorPos.y * scaleY;

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == true)
		{//�g�p���Ă���A�C�e����S�ă`�F�b�N����

			float itemLeft = g_item[nCntItem].pos.x - g_item[nCntItem].fWidth / 1.5;
			float itemRight = g_item[nCntItem].pos.x + g_item[nCntItem].fWidth / 1.5;
			float itemTop = g_item[nCntItem].pos.y - g_item[nCntItem].fHeight / 1.5;
			float itemBottom = g_item[nCntItem].pos.y + g_item[nCntItem].fHeight / 1.5;

			if (mouseX >= itemLeft && mouseX <= itemRight &&
				mouseY >= itemTop && mouseY <= itemBottom)
			{
				if (GetMouseButtonTrigger(0) == true)
				{
					switch (g_item[nCntItem].type)
					{// �������{�^���ɉ����ď����̕ω�
					case NUMTYPE_0:		// 0
						AddPassword(0);
						break;
					case NUMTYPE_1:		// 1
						AddPassword(1);
						break;
					case NUMTYPE_2:		// 2
						AddPassword(2);
						break;
					case NUMTYPE_3:		// 3
						AddPassword(3);
						break;
					case NUMTYPE_4:		// 4
						AddPassword(4);
						break;
					case NUMTYPE_5:		// 5
						AddPassword(5);
						break;
					case NUMTYPE_6:		// 6
						AddPassword(6);
						break;
					case NUMTYPE_7:		// 7
						AddPassword(7);
						break;
					case NUMTYPE_8:		// 8
						AddPassword(8);
						break;
					case NUMTYPE_9:		// 9
						AddPassword(9);
						break;
					case NUMTYPE_ENTER:	// �G���^�[
						g_bJudgment = true;
						break;
					case NUMTYPE_DELETE:// �S��������
						SetPassword(0,0,false);
						SetPassword(0, GetAnum4(), true);
						g_bJudgment = false;
						g_bReset = false;
						break;
					}
				}
			}
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y - g_item[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + g_item[nCntItem].fWidth, g_item[nCntItem].pos.y + g_item[nCntItem].fHeight, 0.0f);
	
		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPassItem->Unlock();
}
//�A�C�e���̕`��
void DrawPasswordItem(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPassItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse != false)
		{//�A�C�e�����g�p����Ă���	
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePassItem[g_item[nCntItem].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}
//�A�C�e���̔z�u
void SetPasswordItem(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType, NUMTYPE type)
{
	VERTEX_2D* pVtx = 0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == false)
		{//�A�C�e�����g�p����Ă��Ȃ�
			g_item[nCntItem].pos = pos;
			g_item[nCntItem].fWidth = fWidth;
			g_item[nCntItem].fHeight = fHeight;
			g_item[nCntItem].nType = nType;
			g_item[nCntItem].type = type;
			g_item[nCntItem].bUse = true;
			g_item[nCntItem].bcatch = false;

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
	g_pVtxBuffPassItem->Unlock();
}
//�p�X���[�h�̎擾
PASSWORDITEM* GetItem(void)
{
	return g_item;
}
//��v����
bool GetJudgment(void)
{
	return g_bJudgment;
}
bool GetReset(void)
{
	return g_bReset;
}