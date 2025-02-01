//=============================================================================
//
// �^�X�N���� [task.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "task.h"
#include "block.h"
#include "game.h"



// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTask[TASKTYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTask = NULL;			//���_�o�b�t�@�ւ̃|�C���^
TASK g_aTask[MAX_TASK];


//============================================
//�^�X�NUI�\���̏���������
//============================================
void InitTask(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	int nCntTask;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < TASKTYPE_MAX; nCnt++)
	{

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			TASK_TEXTURE[nCnt],
			&g_pTextureTask[nCnt]);

	}

	//�^�X�N����UI�̏��̏�����
	for (nCntTask = 0; nCntTask < MAX_TASK; nCntTask++)
	{
		g_aTask[nCntTask].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTask[nCntTask].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTask[nCntTask].fWidth = 0.0f;
		g_aTask[nCntTask].fHeight = 0.0f;
		g_aTask[nCntTask].nType = TASKTYPE_ONE;
		g_aTask[nCntTask].bUse = false;

	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TASK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTask,
		NULL);


	VERTEX_2D* pVtx;


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTask->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntTask = 0; nCntTask < MAX_TASK; nCntTask++)
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
		pVtx[1].tex = D3DXVECTOR2(4.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(4.0f, 1.0f);


		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�

	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTask->Unlock();

}
//============================================
//�^�X�NUI�\���̏I������
//============================================
void UninitTask(void)
{

	for (int nCntTask = 0; nCntTask < TASKTYPE_MAX; nCntTask++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTask[nCntTask] != NULL)
		{
			g_pTextureTask[nCntTask]->Release();
			g_pTextureTask[nCntTask] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTask != NULL)
	{
		g_pVtxBuffTask->Release();
		g_pVtxBuffTask = NULL;
	}
}
//============================================
//�^�X�NUI�\���̍X�V����
//============================================
void UpdateTask(void)
{

	bool bFuseCmp = GetFuseCmp();
	bool bSTClear = GetSTClear();
	bool bACClear = GetACClear();
	bool bBallClear = GetBallClear();


	VERTEX_2D* pVtx;

	int nCntTask;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTask->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTask = 0; nCntTask < MAX_TASK; nCntTask++)
	{
		if (bFuseCmp == false && g_aTask[nCntTask].nType == TASKTYPE_ONE)
		{
			if (g_aTask[nCntTask].pos.x <= 1130.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}
		else if (bFuseCmp == true && bSTClear == false && bACClear == false && bBallClear == false &&
			g_aTask[nCntTask].nType == TASKTYPE_TWO)
		{
			if (g_aTask[nCntTask].pos.x <= 1120.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}
		else if (bSTClear == true && bACClear == true && bBallClear == true && g_aTask[nCntTask].nType == TASKTYPE_THREE)
		{
			if (g_aTask[nCntTask].pos.x <= 1120.0f)
			{
				g_aTask[nCntTask].pos.x -= 0.0f;
			}
			else if (g_aTask[nCntTask].pos.x <= 2350.0f)
			{
				g_aTask[nCntTask].pos.x -= 15.0f;
			}
		}

		// �q���[�Y��t������
		if (bFuseCmp == true)
		{
			if (g_aTask[nCntTask].nType == TASKTYPE_ONE)
			{
				g_aTask[nCntTask].pos.x += 15.0f;

				if (g_aTask[nCntTask].pos.x >= 2350.0f)
				{
					g_aTask[nCntTask].pos.x += 0.0f;
					g_aTask[nCntTask].bUse = false;
				}
			}
		}

		// �~�j�Q�[�������ׂăN���A������
		if (bSTClear == true && bACClear == true && bBallClear == true)
		{
			if (g_aTask[nCntTask].nType == TASKTYPE_TWO)
			{
				g_aTask[nCntTask].pos.x += 15.0f;

				if (g_aTask[nCntTask].pos.x >= 2350.0f)
				{
					g_aTask[nCntTask].pos.x += 0.0f;
					g_aTask[nCntTask].bUse = false;
				}

			}
		}

		//�ʒu���X�V
		g_aTask[nCntTask].pos.x += g_aTask[nCntTask].move.x;
		g_aTask[nCntTask].pos.y += g_aTask[nCntTask].move.y;


		//���_���W�̍X�V
		pVtx[1].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x + g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y - g_aTask[nCntTask].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x - g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y + g_aTask[nCntTask].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x + g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y + g_aTask[nCntTask].fHeight, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x - g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y - g_aTask[nCntTask].fHeight, 0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTask->Unlock();

}
//============================================
//�^�X�NUI�\���̕`�揈��
//============================================
void DrawTask(void)
{

	int nCntTask;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTask, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTask = 0; nCntTask < MAX_TASK; nCntTask++)
	{
		if (g_aTask[nCntTask].bUse == true)
		{//�u���b�N���g�p����Ă���


			int nType = g_aTask[nCntTask].nType;

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTask[nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTask * 4, 2);

		}
	}
}
//============================================
//�^�X�NUI�\���̐ݒ菈��
//============================================
void SetTask(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{

	int nCntTask;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTask->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTask = 0; nCntTask < MAX_TASK; nCntTask++)
	{

		if (g_aTask[nCntTask].bUse == false)
		{//UI���g�p����Ă��Ȃ�

			g_aTask[nCntTask].pos = pos;
			g_aTask[nCntTask].nType = nType;
			g_aTask[nCntTask].fWidth = fWidth;
			g_aTask[nCntTask].fHeight = fHeight;
			g_aTask[nCntTask].bUse = true;


			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//���_���W�̍X�V
			pVtx[1].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x + g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y - g_aTask[nCntTask].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x - g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y + g_aTask[nCntTask].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x + g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y + g_aTask[nCntTask].fHeight, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_aTask[nCntTask].pos.x - g_aTask[nCntTask].fWidth, g_aTask[nCntTask].pos.y - g_aTask[nCntTask].fHeight, 0.0f);

			break;
		}
		pVtx += 4;

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTask->Unlock();
}
