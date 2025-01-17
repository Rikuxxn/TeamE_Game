//=======================================
//
// �u���b�N�z�u����[block.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "block.h"
#include "player.h"
#include "input.h"
#include "enemy.h"
#include "edit.h"
#include <stdio.h>

//�O���[�o���ϐ�
Block g_aBlock[MAX_BLOCK];//�u���b�N���
bool g_bExit;//�o���ɓ�������

//=============================
//�u���b�N�̏���������
//=============================
void InitBlock(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//������
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].bScoreAdded = false;
		g_aBlock[nCntBlock].bSoundPlayed = false;
		g_aBlock[nCntBlock].nType = BLOCKTYPE_NORMAL;

		for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(BLOCK[nCnt],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aBlock[nCntBlock].blockinfo[nCnt].pBuffMat,
				NULL,
				&g_aBlock[nCntBlock].blockinfo[nCnt].dwNumMat,
				&g_aBlock[nCntBlock].blockinfo[nCnt].pMesh);


			int nNumVtx;//���_��
			DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

			//���_���̎擾

			nNumVtx = g_aBlock[nCntBlock].blockinfo[nCnt].pMesh->GetNumVertices();

			//���_�t�H�[�}�b�g�̎擾
			sizeFVF = D3DXGetFVFVertexSize(g_aBlock[nCntBlock].blockinfo[nCnt].pMesh->GetFVF());

			//���_�o�b�t�@�̃��b�N
			g_aBlock[nCntBlock].blockinfo[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				if (vtx.x < g_aBlock[nCntBlock].vtxMin.x)
				{
					g_aBlock[nCntBlock].vtxMin.x = vtx.x;
				}
				if (vtx.y < g_aBlock[nCntBlock].vtxMin.y)
				{
					g_aBlock[nCntBlock].vtxMin.y = vtx.y;
				}
				if (vtx.z < g_aBlock[nCntBlock].vtxMin.z)
				{
					g_aBlock[nCntBlock].vtxMin.z = vtx.z;
				}

				if (vtx.x > g_aBlock[nCntBlock].vtxMax.x)
				{
					g_aBlock[nCntBlock].vtxMax.x = vtx.x;
				}
				if (vtx.y > g_aBlock[nCntBlock].vtxMax.y)
				{
					g_aBlock[nCntBlock].vtxMax.y = vtx.y;
				}
				if (vtx.z > g_aBlock[nCntBlock].vtxMax.z)
				{
					g_aBlock[nCntBlock].vtxMax.z = vtx.z;
				}

				//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}

			g_aBlock[nCntBlock].size.x = (g_aBlock[nCntBlock].vtxMax.x - g_aBlock[nCntBlock].vtxMin.x);
			g_aBlock[nCntBlock].size.y = (g_aBlock[nCntBlock].vtxMax.y - g_aBlock[nCntBlock].vtxMin.y);
			g_aBlock[nCntBlock].size.z = (g_aBlock[nCntBlock].vtxMax.z - g_aBlock[nCntBlock].vtxMin.z);

			//���_�o�b�t�@�̃A�����b�N
			g_aBlock[nCntBlock].blockinfo[nCnt].pMesh->UnlockVertexBuffer();

			D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].blockinfo[nCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].blockinfo[nCnt].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//�e�N�X�`���t�@�C�������݂���

					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_aBlock[nCntBlock].blockinfo[nCnt].apTexture[nCntMat]);

				}
			}
		}
	}

	g_bExit = false;

}
//=============================
//�u���b�N�̏I������
//=============================
void UninitBlock(void)
{
	//StopSound(SOUND_LABEL_MONEY);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
		{

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].blockinfo[nCnt].dwNumMat; nCntMat++)
			{
				//�e�N�X�`���̔j��
				if (g_aBlock[nCntBlock].blockinfo[nCnt].apTexture[nCntMat] != NULL)
				{
					g_aBlock[nCntBlock].blockinfo[nCnt].apTexture[nCntMat]->Release();
					g_aBlock[nCntBlock].blockinfo[nCnt].apTexture[nCntMat] = NULL;
				}
			}

			//���b�V���̔j��
			if (g_aBlock[nCntBlock].blockinfo[nCnt].pMesh != NULL)
			{
				g_aBlock[nCntBlock].blockinfo[nCnt].pMesh->Release();
				g_aBlock[nCntBlock].blockinfo[nCnt].pMesh = NULL;
			}

			//�}�e���A���̔j��
			if (g_aBlock[nCntBlock].blockinfo[nCnt].pBuffMat != NULL)
			{
				g_aBlock[nCntBlock].blockinfo[nCnt].pBuffMat->Release();
				g_aBlock[nCntBlock].blockinfo[nCnt].pBuffMat = NULL;
			}
		}
	}
	
}
//=============================
//�u���b�N�̍X�V����
//=============================
void UpdateBlock(void)
{
	//UpdateEdit();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{

		////�ʒu���X�V
		//g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
		//g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;
		//g_aBlock[nCntBlock].pos.z += g_aBlock[nCntBlock].move.z;
	}

}
//=============================
//�u���b�N�̕`�揈��
//=============================
void DrawBlock(void)
{
	//DrawEdit();

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	//{
		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse == true) 
			{
				int nType = g_aBlock[nCntBlock].nType;

				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aBlock[nCntBlock].mtxWorld);

				// �����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBlock[nCntBlock].rot.y, g_aBlock[nCntBlock].rot.x, g_aBlock[nCntBlock].rot.z);
				D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
				D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxTrans);

				// ���[���h�}�g���b�N�X��ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aBlock[nCntBlock].mtxWorld);

				// ���݂̃}�e���A���̎擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].blockinfo[nType].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].blockinfo[nType].dwNumMat; nCntMat++) {
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_aBlock[nCntBlock].blockinfo[nType].apTexture[nCntMat]);

					// ���f��(�p�[�c)�̕`��
					g_aBlock[nCntBlock].blockinfo[nType].pMesh->DrawSubset(nCntMat);
				}

				// �ۑ����Ă����}�e���A����߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	//}
	
}
//=============================
//�u���b�N�̐ݒ菈��
//=============================
void SetBlock(D3DXVECTOR3 pos, int nType)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{

			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bUse = true;

			break;

		}
	}
}
//=============================
//�u���b�N�̓����蔻��
//=============================
void CollisionBlock(void)
{

	//bool bTask = false;//�G��Ă��邩�ǂ���

	//for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	//{
		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			Player* pPlayer = GetPlayer();
			Enemy* pEnemy = GetEnemy();

			if (g_aBlock[nCntBlock].bUse == true)
			{

				if (g_aBlock[nCntBlock].nType == BLOCKTYPE_NORMAL)
				{

					if (pPlayer->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
						pPlayer->posOld.y + pPlayer->size.y > g_aBlock[nCntBlock].pos.y)
					{

						//���E(X����)�̓����蔻��
						if (pPlayer->pos.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
							pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
						{
							//������E�ɓ�������
							if (pPlayer->posOld.x + pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 &&
								pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
							{
								pPlayer->pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 - pPlayer->size.x / 2 - 0.1f;
							}
							//�E���獶�ɓ�������
							else if (pPlayer->posOld.x - pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
								pPlayer->pos.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2)
							{
								pPlayer->pos.x = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2) + pPlayer->size.x / 2 + 0.1f;
							}

						}

						//�O��(Z����)�̓����蔻��
						if (pPlayer->pos.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							//��O���瓖������
							if (pPlayer->posOld.z + pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{
								pPlayer->pos.z = (g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2) - pPlayer->size.z / 2 - 0.1f;
							}
							//�����瓖������
							else if (pPlayer->posOld.z - pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2)
							{
								pPlayer->pos.z = (g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2) + pPlayer->size.z / 2 + 0.1f;
							}

						}

						//�c(Y����)�̓����蔻��
						if (pPlayer->posOld.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							if (pPlayer->posOld.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{

								//�ォ�牺�ɓ�������
								if (pPlayer->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
									pPlayer->pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].size.y)
								{
									pPlayer->pos.y = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y / 2) + pPlayer->size.y / 2 - 0.9f;
									pPlayer->move.y = 0.0f;
								}
								//�������ɓ�������
								if (pPlayer->posOld.y - pPlayer->size.y / 2 < g_aBlock[nCntBlock].pos.y / 2 &&
									pPlayer->pos.y - pPlayer->size.y / 2 > g_aBlock[nCntBlock].pos.y / 2)
								{
									pPlayer->pos.y = (g_aBlock[nCntBlock].pos.y - pPlayer->size.y);
									pPlayer->move.y = 0.0f;
								}

							}
						}
					}

				}

				if (g_aBlock[nCntBlock].nType == BLOCKTYPE_DOOR)
				{

					if (pPlayer->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
						pPlayer->posOld.y + pPlayer->size.y > g_aBlock[nCntBlock].pos.y)
					{

						//���E(X����)�̓����蔻��
						if (pPlayer->pos.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
							pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
						{
							//������E�ɓ�������
							if (pPlayer->posOld.x + pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 &&
								pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
							{
								pPlayer->pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 - pPlayer->size.x / 2 - 0.1f;
							}
							//�E���獶�ɓ�������
							else if (pPlayer->posOld.x - pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
								pPlayer->pos.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2)
							{
								pPlayer->pos.x = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2) + pPlayer->size.x / 2 + 0.1f;
							}

						}

						//�O��(Z����)�̓����蔻��
						if (pPlayer->pos.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							//��O���瓖������
							if (pPlayer->posOld.z + pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{
								pPlayer->pos.z = (g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2) - pPlayer->size.z / 2 - 0.1f;
							}
							//�����瓖������
							else if (pPlayer->posOld.z - pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2)
							{
								pPlayer->pos.z = (g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2) + pPlayer->size.z / 2 + 0.1f;
							}

						}

						//�c(Y����)�̓����蔻��
						if (pPlayer->posOld.x - pPlayer->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pPlayer->pos.x + pPlayer->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							if (pPlayer->posOld.z - pPlayer->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pPlayer->pos.z + pPlayer->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{

								//�ォ�牺�ɓ�������
								if (pPlayer->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
									pPlayer->pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].size.y)
								{
									pPlayer->pos.y = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y / 2) + pPlayer->size.y / 2 - 0.9f;
									pPlayer->move.y = 0.0f;
								}
								//�������ɓ�������
								if (pPlayer->posOld.y - pPlayer->size.y / 2 < g_aBlock[nCntBlock].pos.y / 2 &&
									pPlayer->pos.y - pPlayer->size.y / 2 > g_aBlock[nCntBlock].pos.y / 2)
								{
									pPlayer->pos.y = (g_aBlock[nCntBlock].pos.y - pPlayer->size.y);
									pPlayer->move.y = 0.0f;
								}

							}
						}
					}

				}



				//�G�ƃ��f���̓����蔻��
				if (g_aBlock[nCntBlock].nType == BLOCKTYPE_NORMAL)
				{

					if (pEnemy->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
						pEnemy->posOld.y + pEnemy->size.y > g_aBlock[nCntBlock].pos.y)
					{

						//���E(X����)�̓����蔻��
						if (pEnemy->pos.z - pEnemy->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
							pEnemy->pos.z + pEnemy->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
						{
							//������E�ɓ�������
							if (pEnemy->posOld.x + pEnemy->size.x / 2 < g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 &&
								pEnemy->pos.x + pEnemy->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
							{
								pEnemy->pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 - pEnemy->size.x / 2 - 0.1f;
							}
							//�E���獶�ɓ�������
							else if (pEnemy->posOld.x - pEnemy->size.x / 2 > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
								pEnemy->pos.x - pEnemy->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2)
							{
								pEnemy->pos.x = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2) + pEnemy->size.x / 2 + 0.1f;
							}

						}

						//�O��(Z����)�̓����蔻��
						if (pEnemy->pos.x - pEnemy->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pEnemy->pos.x + pEnemy->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							//��O���瓖������
							if (pEnemy->posOld.z + pEnemy->size.z / 2 < g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2 &&
								pEnemy->pos.z + pEnemy->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{
								pEnemy->pos.z = (g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2) - pEnemy->size.z / 2 - 0.1f;
							}
							//�����瓖������
							else if (pEnemy->posOld.z - pEnemy->size.z / 2 > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pEnemy->pos.z - pEnemy->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2)
							{
								pEnemy->pos.z = (g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2) + pEnemy->size.z / 2 + 0.1f;
							}

						}

						//�c(Y����)�̓����蔻��
						if (pEnemy->posOld.x - pEnemy->size.x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
							pEnemy->pos.x + pEnemy->size.x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
						{

							if (pEnemy->posOld.z - pEnemy->size.z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
								pEnemy->pos.z + pEnemy->size.z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
							{

								//�ォ�牺�ɓ�������
								if (pEnemy->posOld.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
									pEnemy->pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].size.y)
								{
									pEnemy->pos.y = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y / 2) + pEnemy->size.y / 2 - 0.9f;
									pEnemy->move.y = 0.0f;
								}
								//�������ɓ�������
								if (pEnemy->posOld.y - pEnemy->size.y / 2 < g_aBlock[nCntBlock].pos.y / 2 &&
									pEnemy->pos.y - pEnemy->size.y / 2 > g_aBlock[nCntBlock].pos.y / 2)
								{
									pEnemy->pos.y = (g_aBlock[nCntBlock].pos.y - pEnemy->size.y);
									pEnemy->move.y = 0.0f;
								}

							}
						}
					}

				}
			}
		}
	//}
	//return bTask;

}
//============================================
//�u���b�N�̎擾
//============================================
Block* GetBlock(void)
{
	return &g_aBlock[0];
}
//======================================================
//�o������
//======================================================
bool GetExit(void)
{
	return g_bExit;
}
