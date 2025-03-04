//---------------------------------------------------------
// �{�[���v�[��
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "ball_item.h"
#include "ball_particle.h"
#include "input.h"
#include "crane_item.h"
#include "sound.h"
#include "ball_background.h"

// �O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureBallItem[NUM_ITEM] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallItem = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
BALLITEM g_ballitem[MAX_ITEM];							// �A�C�e���̏��
int g_nBallItem;

// �A�C�e�����ڂ̊g�嗦���Ǘ�����z��
float ItemScales[MAX_ITEM] = { ITEM_MIN_SCALE, ITEM_MIN_SCALE, ITEM_MIN_SCALE, ITEM_MIN_SCALE };
bool bHoldingItem = false;  // �A�C�e���������Ă��邩

void InitBallItem(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ball_red.png",		// �e�N�X�`���̃t�@�C����
		&g_pTextureBallItem[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ball_blue.png",		// �e�N�X�`���̃t�@�C����
		&g_pTextureBallItem[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ball_yellow.png",	// �e�N�X�`���̃t�@�C����
		&g_pTextureBallItem[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ball_green.png",	// �e�N�X�`���̃t�@�C����
		&g_pTextureBallItem[3]);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_ballitem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ballitem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ballitem[nCntItem].fWidth = 0.0f;
		g_ballitem[nCntItem].fHeight = 0.0f;
		g_ballitem[nCntItem].nType = 0;
		g_ballitem[nCntItem].bUse = false;// �g�p���Ă��Ȃ���Ԃɂ���
		g_ballitem[nCntItem].bGet = false;
		g_ballitem[nCntItem].bcatch = false;
		g_ballitem[nCntItem].dragOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	g_nBallItem = 0;
	bHoldingItem = false;

	// ���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallItem,
		NULL);

	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBallItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].fHeight, 0.0f);

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
	g_pVtxBuffBallItem->Unlock();
}
void UninitBallItem(void)
{
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureBallItem[nCntItem] != NULL)
		{
			g_pTextureBallItem[nCntItem]->Release();
			g_pTextureBallItem[nCntItem] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffBallItem != NULL)
	{
		g_pVtxBuffBallItem->Release();
		g_pVtxBuffBallItem = NULL;
	}
}
void UpdateBallItem(void)
{
	VERTEX_2D* pVtx = 0;

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

	// �Q�[���p�b�h�Ń}�E�X�J�[�\���𓮂���
	UpdateCursorWithGamepad();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_ballitem[nCntItem].bUse)
		{
			float scaleFactor = 1.5f;  // 1.5�{�͈̔͂ɂ���
			float itemLeft = g_ballitem[nCntItem].pos.x - (g_ballitem[nCntItem].fWidth * scaleFactor) / 2.0f;
			float itemRight = g_ballitem[nCntItem].pos.x + (g_ballitem[nCntItem].fWidth * scaleFactor) / 2.0f;
			float itemTop = g_ballitem[nCntItem].pos.y - (g_ballitem[nCntItem].fHeight * scaleFactor) / 2.0f;
			float itemBottom = g_ballitem[nCntItem].pos.y + (g_ballitem[nCntItem].fHeight * scaleFactor) / 2.0f;

			if (mouseX >= itemLeft && mouseX <= itemRight &&
				mouseY >= itemTop && mouseY <= itemBottom)
			{
				if (!bHoldingItem && (GetMouseButtonPress(0) || GetJoypadPress(JOYKEY_B) == true))
				{
					if (g_ballitem[nCntItem].bGet == false)
					{
						PlaySound(SOUND_LABEL_BALLCATCH);
						g_ballitem[nCntItem].bGet = true;
					}
					g_ballitem[nCntItem].bcatch = true;
					bHoldingItem = true;  // �A�C�e���������Ă��邱�Ƃ��L�^

					// �}�E�X�̂ǂ���͂񂾂����L�^
					g_ballitem[nCntItem].dragOffset.x = g_ballitem[nCntItem].pos.x - mouseX;
					g_ballitem[nCntItem].dragOffset.y = g_ballitem[nCntItem].pos.y - mouseY;

				}				
				if (GetMouseButtonRelease(0) || JoyPadRelease(JOYKEY_B) == true)
				{
					g_ballitem[nCntItem].bcatch = false;
					g_ballitem[nCntItem].bGet = false;
					bHoldingItem = false;  // �����Ă����Ԃ�����

					// ��ʒ[�̐���
					if (g_ballitem[nCntItem].pos.x < BALLFIELD_LEFT + g_ballitem[nCntItem].fWidth / 2)
					{
						g_ballitem[nCntItem].pos.x = BALLFIELD_LEFT + g_ballitem[nCntItem].fWidth / 2;
					}
					if (g_ballitem[nCntItem].pos.x > BALLFIELD_RIGHT - g_ballitem[nCntItem].fWidth / 2)
					{
						g_ballitem[nCntItem].pos.x = BALLFIELD_RIGHT - g_ballitem[nCntItem].fWidth / 2;
					}
					if (g_ballitem[nCntItem].pos.y < BALLFIELD_TOP + g_ballitem[nCntItem].fHeight / 2)
					{
						g_ballitem[nCntItem].pos.y = BALLFIELD_TOP + g_ballitem[nCntItem].fHeight / 2;
					}
					if (g_ballitem[nCntItem].pos.y > BALLFIELD_UNDER - g_ballitem[nCntItem].fHeight / 2)
					{
						g_ballitem[nCntItem].pos.y = BALLFIELD_UNDER - g_ballitem[nCntItem].fHeight / 2;
					}
				}
			}


			if (g_ballitem[nCntItem].bcatch)
			{
				// �}�E�X�̈ʒu�ɃI�t�Z�b�g�𑫂��Ĉړ�
				g_ballitem[nCntItem].pos.x = mouseX + g_ballitem[nCntItem].dragOffset.x;
				g_ballitem[nCntItem].pos.y = mouseY + g_ballitem[nCntItem].dragOffset.y;
			}

		
		}

		g_ballitem[nCntItem].pos += g_ballitem[nCntItem].move;

		if (g_ballitem[nCntItem].pos.y >= BALLFIELD_UNDER - g_ballitem[nCntItem].fHeight)
		{// �n��
			g_ballitem[nCntItem].pos.y = BALLFIELD_UNDER - g_ballitem[nCntItem].fHeight;
		}

		if (g_ballitem[nCntItem].pos.y <= BALLFIELD_TOP + g_ballitem[nCntItem].fHeight)
		{// �V��
			g_ballitem[nCntItem].pos.y = BALLFIELD_TOP + g_ballitem[nCntItem].fHeight;
		}

		if (g_ballitem[nCntItem].pos.x <= BALLFIELD_LEFT + g_ballitem[nCntItem].fWidth)
		{// ���[
			g_ballitem[nCntItem].pos.x = BALLFIELD_LEFT + g_ballitem[nCntItem].fWidth;
		}

		if (g_ballitem[nCntItem].pos.x >= BALLFIELD_RIGHT - g_ballitem[nCntItem].fWidth)
		{// �E�[
			g_ballitem[nCntItem].pos.x = BALLFIELD_RIGHT - g_ballitem[nCntItem].fWidth;
		}

		if (g_ballitem[nCntItem].pos.y >= ITEM_CLEARPOSY - ITEM_CLEARZONEY
			&& g_ballitem[nCntItem].pos.x - g_ballitem[nCntItem].fWidth >= ITEM_CLEARPOSX - ITEM_CLEARZONEX
			&& g_ballitem[nCntItem].pos.x + g_ballitem[nCntItem].fWidth <= ITEM_CLEARPOSX + ITEM_CLEARZONEX
			&& g_ballitem[nCntItem].bUse == true)
		{// �{�[����ЂÂ���
			PlaySound(SOUND_LABEL_BALLGET);
			g_ballitem[nCntItem].bcatch = false;
			g_ballitem[nCntItem].bUse = false;
			bHoldingItem = false;
			g_nBallItem--;
		}

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x - g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y - g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x + g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y - g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x - g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y + g_ballitem[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x + g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y + g_ballitem[nCntItem].fHeight, 0.0f);

		pVtx += 4;// ���_�f�[�^�̃|�C���^���S���i�߂�

	}

	if (!GetMouseButtonPress(0) && !GetJoypadPress(JOYKEY_B))
	{
		for (int i = 0; i < MAX_ITEM; i++)
		{
			g_ballitem[i].bcatch = false;
		}
		bHoldingItem = false;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBallItem->Unlock();

}
void DrawBallItem(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^

	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBallItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_ballitem[nCntItem].bUse != false)
		{// �A�C�e�����g�p����Ă���	

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBallItem[g_ballitem[nCntItem].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}
// �A�C�e���̐ݒ菈��
void SetBallItem(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	VERTEX_2D* pVtx=0;
	
	// ���b�N
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_ballitem[nCntItem].bUse == false)
		{// �A�C�e�����g�p����Ă��Ȃ�
			g_ballitem[nCntItem].pos = pos;
			g_ballitem[nCntItem].fWidth = fWidth;
			g_ballitem[nCntItem].fHeight = fHeight;
			g_ballitem[nCntItem].nType = nType;
			g_ballitem[nCntItem].bUse = true;
			g_ballitem[nCntItem].bcatch = false;
			g_nBallItem++;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x - g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y - g_ballitem[nCntItem].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x + g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y - g_ballitem[nCntItem].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x - g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y + g_ballitem[nCntItem].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ballitem[nCntItem].pos.x + g_ballitem[nCntItem].fWidth, g_ballitem[nCntItem].pos.y + g_ballitem[nCntItem].fHeight, 0.0f);

			// �e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;// ���_�f�[�^�̃|�C���^���S���i�߂�
	}
	// �A�����b�N
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBallItem->Unlock();
}
// �A�C�e���̌�
int GetNumBallItem(void)
{
	return g_nBallItem;
}