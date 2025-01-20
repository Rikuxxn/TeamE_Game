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
Block g_info[BLOCKTYPE_MAX];//�u���b�N�̑f�ޏ��

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
		// ������
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].bScoreAdded = false;
		g_aBlock[nCntBlock].bSoundPlayed = false;
		g_aBlock[nCntBlock].nType = BLOCKTYPE_WALL;
	}

	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(BLOCK[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_info[nCnt].blockinfo[nCnt].pBuffMat,
			NULL,
			&g_info[nCnt].blockinfo[nCnt].dwNumMat,
			&g_info[nCnt].blockinfo[nCnt].pMesh);

	}

	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		g_info[nCnt].bUse = true;

		//���_���̎擾
		nNumVtx = g_info[nCnt].blockinfo[nCnt].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̎擾
		sizeFVF = D3DXGetFVFVertexSize(g_info[nCnt].blockinfo[nCnt].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_info[nCnt].blockinfo[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (vtx.x < g_info[nCnt].blockinfo[nCnt].vtxMin.x)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMin.x = vtx.x;
			}
			if (vtx.y < g_info[nCnt].blockinfo[nCnt].vtxMin.y)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMin.y = vtx.y;
			}
			if (vtx.z < g_info[nCnt].blockinfo[nCnt].vtxMin.z)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMin.z = vtx.z;
			}

			if (vtx.x > g_info[nCnt].blockinfo[nCnt].vtxMax.x)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMax.x = vtx.x;
			}
			if (vtx.y > g_info[nCnt].blockinfo[nCnt].vtxMax.y)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMax.y = vtx.y;
			}
			if (vtx.z > g_info[nCnt].blockinfo[nCnt].vtxMax.z)
			{
				g_info[nCnt].blockinfo[nCnt].vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		g_info[nCnt].size.x = (g_info[nCnt].blockinfo[nCnt].vtxMax.x - g_info[nCnt].blockinfo[nCnt].vtxMin.x);
		g_info[nCnt].size.y = (g_info[nCnt].blockinfo[nCnt].vtxMax.y - g_info[nCnt].blockinfo[nCnt].vtxMin.y);
		g_info[nCnt].size.z = (g_info[nCnt].blockinfo[nCnt].vtxMax.z - g_info[nCnt].blockinfo[nCnt].vtxMin.z);

		//���_�o�b�t�@�̃A�����b�N
		g_info[nCnt].blockinfo[nCnt].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_info[nCnt].blockinfo[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_info[nCnt].blockinfo[nCnt].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���

				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat]);

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

	//for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	//{
		for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
		{

			for (int nCntMat = 0; nCntMat < (int)g_info[nCnt].blockinfo[nCnt].dwNumMat; nCntMat++)
			{
				//�e�N�X�`���̔j��
				if (g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat] != NULL)
				{
					g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat]->Release();
					g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat] = NULL;
				}
			}

			//���b�V���̔j��
			if (g_info[nCnt].blockinfo[nCnt].pMesh != NULL)
			{
				g_info[nCnt].blockinfo[nCnt].pMesh->Release();
				g_info[nCnt].blockinfo[nCnt].pMesh = NULL;
			}

			//�}�e���A���̔j��
			if (g_info[nCnt].blockinfo[nCnt].pBuffMat != NULL)
			{
				g_info[nCnt].blockinfo[nCnt].pBuffMat->Release();
				g_info[nCnt].blockinfo[nCnt].pBuffMat = NULL;
			}
		}
	//}
	
}
//=============================
//�u���b�N�̍X�V����
//=============================
void UpdateBlock(void)
{

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

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

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


			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].blockinfo[nType].dwNumMat; nCntMat++) 
			{
				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].blockinfo[nType].pBuffMat->GetBufferPointer();

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
			g_aBlock[nCntBlock] = g_info[nType];

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
void CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, D3DXVECTOR3* pSize)
{

	//bool bTask = false;//�G��Ă��邩�ǂ���

	//for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	//{
	//	Player* pPlayer = GetPlayer();
	//	Enemy* pEnemy = GetEnemy();

	//	if (g_aBlock[nCntBlock].bUse == true)
	//	{

	//		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_WALL)
	//		{

	//			if (pPosOld->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
	//				pPosOld->y + pSize->y > g_aBlock[nCntBlock].pos.y)
	//			{

	//				//���E(X����)�̓����蔻��
	//				if (pPos->z - pSize->z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
	//					pPos->z + pSize->z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
	//				{
	//					//������E�ɓ�������
	//					if (pPosOld->x + pSize->x / 2 < g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 &&
	//						pPos->x + pSize->x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
	//					{
	//						pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 - pSize->x / 2 - 0.1f;
	//					}
	//					//�E���獶�ɓ�������
	//					else if (pPosOld->x - pSize->x / 2 > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
	//						pPos->x - pSize->x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2)
	//					{
	//						pPos->x = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2) + pSize->x / 2 + 0.1f;
	//					}

	//				}

	//				//�O��(Z����)�̓����蔻��
	//				if (pPos->x - pSize->x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
	//					pPos->x + pSize->x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
	//				{

	//					//��O���瓖������
	//					if (pPosOld->z + pSize->z / 2 < g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2 &&
	//						pPos->z + pSize->z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
	//					{
	//						pPos->z = (g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2) - pSize->z / 2 - 0.1f;
	//					}
	//					//�����瓖������
	//					else if (pPosOld->z - pSize->z / 2 > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
	//						pPos->z - pSize->z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2)
	//					{
	//						pPos->z = (g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2) + pSize->z / 2 + 0.1f;
	//					}

	//				}

	//				//�c(Y����)�̓����蔻��
	//				if (pPosOld->x - pSize->x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
	//					pPos->x + pSize->x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
	//				{

	//					if (pPosOld->z - pSize->z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
	//						pPos->z + pSize->z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
	//					{

	//						//�ォ�牺�ɓ�������
	//						if (pPosOld->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
	//							pPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].size.y)
	//						{
	//							pPos->y = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y / 2) + pSize->y / 2 - 0.9f;
	//							pMove->y = 0.0f;
	//						}
	//						//�������ɓ�������
	//						if (pPosOld->y - pSize->y / 2 < g_aBlock[nCntBlock].pos.y / 2 &&
	//							pPos->y - pSize->y / 2 > g_aBlock[nCntBlock].pos.y / 2)
	//						{
	//							pPos->y = (g_aBlock[nCntBlock].pos.y - pSize->y);
	//							pMove->y = 0.0f;
	//						}

	//					}
	//				}
	//			}

	//		}

	//		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_UFOCATCHER1)
	//		{

	//			if (pPosOld->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
	//				pPosOld->y + pSize->y > g_aBlock[nCntBlock].pos.y)
	//			{

	//				//���E(X����)�̓����蔻��
	//				if (pPos->z - pSize->z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
	//					pPos->z + pSize->z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
	//				{
	//					//������E�ɓ�������
	//					if (pPosOld->x + pSize->x / 2 < g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 &&
	//						pPos->x + pSize->x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
	//					{
	//						pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 - pSize->x / 2 - 0.1f;
	//					}
	//					//�E���獶�ɓ�������
	//					else if (pPosOld->x - pSize->x / 2 > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
	//						pPos->x - pSize->x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2)
	//					{
	//						pPos->x = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2) + pSize->x / 2 + 0.1f;
	//					}

	//				}

	//				//�O��(Z����)�̓����蔻��
	//				if (pPos->x - pSize->x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
	//					pPos->x + pSize->x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
	//				{

	//					//��O���瓖������
	//					if (pPosOld->z + pSize->z / 2 < g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2 &&
	//						pPos->z + pSize->z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
	//					{
	//						pPos->z = (g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2) - pSize->z / 2 - 0.1f;
	//					}
	//					//�����瓖������
	//					else if (pPosOld->z - pSize->z / 2 > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
	//						pPos->z - pSize->z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2)
	//					{
	//						pPos->z = (g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2) + pSize->z / 2 + 0.1f;
	//					}

	//				}

	//				//�c(Y����)�̓����蔻��
	//				if (pPosOld->x - pSize->x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
	//					pPos->x + pSize->x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
	//				{

	//					if (pPosOld->z - pSize->z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
	//						pPos->z + pSize->z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
	//					{

	//						//�ォ�牺�ɓ�������
	//						if (pPosOld->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
	//							pPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].size.y)
	//						{
	//							pPos->y = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y / 2) + pSize->y / 2 - 0.9f;
	//							pMove->y = 0.0f;
	//						}
	//						//�������ɓ�������
	//						if (pPosOld->y - pSize->y / 2 < g_aBlock[nCntBlock].pos.y / 2 &&
	//							pPos->y - pSize->y / 2 > g_aBlock[nCntBlock].pos.y / 2)
	//						{
	//							pPos->y = (g_aBlock[nCntBlock].pos.y - pSize->y);
	//							pMove->y = 0.0f;
	//						}

	//					}
	//				}
	//			}

	//		}


	//		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_UFOCATCHER2)
	//		{

	//			if (pPosOld->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
	//				pPosOld->y + pSize->y > g_aBlock[nCntBlock].pos.y)
	//			{

	//				//���E(X����)�̓����蔻��
	//				if (pPos->z - pSize->z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
	//					pPos->z + pSize->z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
	//				{
	//					//������E�ɓ�������
	//					if (pPosOld->x + pSize->x / 2 < g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 &&
	//						pPos->x + pSize->x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
	//					{
	//						pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 - pSize->x / 2 - 0.1f;
	//					}
	//					//�E���獶�ɓ�������
	//					else if (pPosOld->x - pSize->x / 2 > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
	//						pPos->x - pSize->x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2)
	//					{
	//						pPos->x = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2) + pSize->x / 2 + 0.1f;
	//					}

	//				}

	//				//�O��(Z����)�̓����蔻��
	//				if (pPos->x - pSize->x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
	//					pPos->x + pSize->x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
	//				{

	//					//��O���瓖������
	//					if (pPosOld->z + pSize->z / 2 < g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2 &&
	//						pPos->z + pSize->z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
	//					{
	//						pPos->z = (g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2) - pSize->z / 2 - 0.1f;
	//					}
	//					//�����瓖������
	//					else if (pPosOld->z - pSize->z / 2 > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
	//						pPos->z - pSize->z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2)
	//					{
	//						pPos->z = (g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2) + pSize->z / 2 + 0.1f;
	//					}

	//				}

	//				//�c(Y����)�̓����蔻��
	//				if (pPosOld->x - pSize->x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
	//					pPos->x + pSize->x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
	//				{

	//					if (pPosOld->z - pSize->z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
	//						pPos->z + pSize->z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
	//					{

	//						//�ォ�牺�ɓ�������
	//						if (pPosOld->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
	//							pPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].size.y)
	//						{
	//							pPos->y = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y / 2) + pSize->y / 2 - 0.9f;
	//							pMove->y = 0.0f;
	//						}
	//						//�������ɓ�������
	//						if (pPosOld->y - pSize->y / 2 < g_aBlock[nCntBlock].pos.y / 2 &&
	//							pPos->y - pSize->y / 2 > g_aBlock[nCntBlock].pos.y / 2)
	//						{
	//							pPos->y = (g_aBlock[nCntBlock].pos.y - pSize->y);
	//							pMove->y = 0.0f;
	//						}

	//					}
	//				}
	//			}

	//		}

	//	}

	//}
	//return bTask;



	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].nType == BLOCKTYPE_WALL)
		{
			// �e�����Ƃɕ������ē����蔻����s��
			// Y���̔���
			if (pPosOld->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].size.y &&
				pPosOld->y + pSize->y > g_aBlock[nCntBlock].pos.y)
			{
				// X���̔���
				if (pPos->z - pSize->z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
					pPos->z + pSize->z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
				{
					if (pPosOld->x + pSize->x / 2 < g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 &&
						pPos->x + pSize->x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2 - pSize->x / 2 - 0.1f;
					}
					else if (pPosOld->x - pSize->x / 2 > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
						pPos->x - pSize->x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 + pSize->x / 2 + 0.1f;
					}
				}
	
				// Z���̔���
				if (pPos->x - pSize->x / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].size.x / 2 &&
					pPos->x + pSize->x / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].size.x / 2)
				{
					if (pPosOld->z + pSize->z / 2 < g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2 &&
						pPos->z + pSize->z / 2 > g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2)
					{
						pPos->z = g_aBlock[nCntBlock].pos.z - g_aBlock[nCntBlock].size.z / 2 - pSize->z / 2 - 0.1f;
					}
					else if (pPosOld->z - pSize->z / 2 > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 &&
						pPos->z - pSize->z / 2 < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2)
					{
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].size.z / 2 + pSize->z / 2 + 0.1f;
					}
				}
			}
		}
	}


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