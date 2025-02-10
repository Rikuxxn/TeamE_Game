//=============================================================================
//
// UI���� [ui.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "ui.h"
#include "main.h"
#include "player.h"
#include "block.h"
#include "game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureUI[UITYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
UI g_aUI[MAX_UI];

//=========================================================
// UI�̏���������
//=========================================================
void InitUI(void)
{
	int nCntUI;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < UITYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			UI_TEXTURE[nCnt],
			&g_pTextureUI[nCnt]);
	}

	// UI�̏��̏�����
	for (nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{
		g_aUI[nCntUI].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUI[nCntUI].fWidth = 0.0f;
		g_aUI[nCntUI].fHeight = 0.0f;
		g_aUI[nCntUI].nType = UITYPE_GAME;
		g_aUI[nCntUI].bUse = false;

	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUI,
		NULL);


	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI->Unlock();

}
//==================================================
// UI�̏I������
//==================================================
void UninitUI(void)
{
	for (int nCntUI = 0; nCntUI < UITYPE_MAX; nCntUI++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureUI[nCntUI] != NULL)
		{
			g_pTextureUI[nCntUI]->Release();
			g_pTextureUI[nCntUI] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffUI != NULL)
	{
		g_pVtxBuffUI->Release();
		g_pVtxBuffUI = NULL;
	}
}
//============================================================
// UI�̍X�V����
//============================================================
void UpdateUI(void)
{

	VERTEX_2D* pVtx;

	MODE pMode = GetMode();
	Block* pBlock = GetBlock();
	Player* pPlayer = GetPlayer();
	GAME* pGame = GetGame();
	//Flags* pFlag = GetFlag();

	int nCntUI;

	bool bArcade = GetArcade();
	bool bCatcher = GetCatcher();
	bool bBall = GetBall();
	bool bKeypad = GetKeypad();
	bool bFuse = GetFuse();
	bool bFusebox = GetFusebox();

	bool bFuseGet = GetFuseGet();
	bool bFuseCmp = GetFuseCmp();
	bool bHintBall = GetHintBall();
	bool bHintBear = GetHintBear();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{

		// �A�[�P�[�h�Q�[���͈͓̔�
		if (bArcade == true && bFuseCmp == true)
		{
			// UI��\��
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_GAME);
		}
		else// �͈͊O
		{
			// false�ɂ���
			g_aUI[nCntUI].bUse = false;
		}

		// UFO�L���b�`���[�͈͓̔�
		if (bCatcher == true && bFuseCmp == true && pGame->bACClear == false)
		{
			// UI��\��
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_GAME);
		}
		else// �͈͊O
		{
			// false�ɂ���
			g_aUI[nCntUI].bUse = false;
		}

		// �{�[���v�[���͈͓̔�
		if (bBall == true && bFuseCmp == true && pGame->bBallClear == false)
		{
			// UI��\��
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_GAME);
		}
		else// �͈͊O
		{
			// false�ɂ���
			g_aUI[nCntUI].bUse = false;
		}

		// �L�[�p�b�h�͈͓̔�
		if (bKeypad == true && pGame->bSTClear == true && pGame->bACClear == true &&
			pGame->bBallClear == true && pGame->bPassClear == false)
		{
			// UI��\��
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_INPUT);
		}
		else// �͈͊O
		{
			// false�ɂ���
			g_aUI[nCntUI].bUse = false;
		}

		// �q���[�Y�͈͓̔�
		if (bFuse == true)
		{
			// UI��\��
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_INTERACT);
		}
		else// �͈͊O
		{
			// false�ɂ���
			g_aUI[nCntUI].bUse = false;
		}

		// �q���[�Y�{�b�N�X�͈͓̔�
		if (bFusebox == true && bFuseGet == true && bFuseCmp == false)
		{
			// UI��\��
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_USE);
		}
		else// �͈͊O
		{
			// false�ɂ���
			g_aUI[nCntUI].bUse = false;
		}

		// �q���g�{�[���͈͓̔�
		if (bHintBall == true)
		{
			// UI��\��
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_GAME);
		}
		else// �͈͊O
		{
			// false�ɂ���
			g_aUI[nCntUI].bUse = false;
		}

		// �q���g���܂���͈͓̔�
		if (bHintBear == true)
		{
			// UI��\��
			SetUI(D3DXVECTOR3(660.0f, 590.0f, 0.0f), 150.0f, 40.0f, UITYPE_GAME);
		}
		else// �͈͊O
		{
			// false�ɂ���
			g_aUI[nCntUI].bUse = false;
		}

		pVtx[0].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y - g_aUI[nCntUI].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y - g_aUI[nCntUI].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y + g_aUI[nCntUI].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y + g_aUI[nCntUI].fHeight, 0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI->Unlock();

}
//=======================================================
// UI�̕`�揈��
//=======================================================
void DrawUI(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffUI, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{
		if (!g_aUI[nCntUI].bUse)
		{
			continue; // �g�p���Ă��Ȃ� UI ���X�L�b�v
		}

		// �g�p���� UI �̂ݕ`�揈�����s��
		int nType = g_aUI[nCntUI].nType;

		pDevice->SetTexture(0, g_pTextureUI[nType]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUI * 4, 2);
	}
}
//===================================================
// UI�̐ݒ菈��
//===================================================
void SetUI(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{

	int nCntUI;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{
		if (g_aUI[nCntUI].bUse == false)
		{
			g_aUI[nCntUI].pos = pos;
			g_aUI[nCntUI].nType = nType;
			g_aUI[nCntUI].fWidth = fWidth;
			g_aUI[nCntUI].fHeight = fHeight;
			g_aUI[nCntUI].bUse = true;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx[0].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y - g_aUI[nCntUI].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y - g_aUI[nCntUI].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y + g_aUI[nCntUI].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + g_aUI[nCntUI].fWidth, g_aUI[nCntUI].pos.y + g_aUI[nCntUI].fHeight, 0.0f);

			break;
		}

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI->Unlock();

}
//===================================================
// UI���̎擾
//===================================================
UI* GetUI(void)
{
	return &g_aUI[0];
}