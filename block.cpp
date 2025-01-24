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
Block g_aBlock[MAX_BLOCK];		//�u���b�N���
Block g_info[BLOCKTYPE_MAX];	//�u���b�N�̑f�ޏ��

bool g_bExit;					//�o���ɓ�������

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
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].bScoreAdded = false;
		g_aBlock[nCntBlock].bSoundPlayed = false;
		g_aBlock[nCntBlock].bInsight = false;
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

	int nNumVtx;					//���_��
	DWORD sizeFVF;					//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^

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
	
}
//=============================
//�u���b�N�̍X�V����
//=============================
void UpdateBlock(void)
{

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		Player* pPlayer = GetPlayer(); // �v���C���[���̎擾

		if (g_aBlock[nCntBlock].bUse == true)
		{
			// ��]�p�x�̐��K��
			if (g_aBlock[nCntBlock].rot.y > D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.y -= D3DX_PI * 2.0f;
			}
			if (g_aBlock[nCntBlock].rot.y < -D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.y += D3DX_PI * 2.0f;
			}

			if (g_aBlock[nCntBlock].rot.x > D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.x -= D3DX_PI * 2.0f;
			}
			if (g_aBlock[nCntBlock].rot.x < -D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.x += D3DX_PI * 2.0f;
			}

			if (g_aBlock[nCntBlock].rot.z > D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.z -= D3DX_PI * 2.0f;
			}
			if (g_aBlock[nCntBlock].rot.z < -D3DX_PI)
			{
				g_aBlock[nCntBlock].rot.z += D3DX_PI * 2.0f;
			}

			if (BlockInteraction())
			{// �͈͓��ɓ�������
				if (KeyboardTrigger(DIK_E))
				{
					// �~�j�Q�[���p�̔����true
					g_aBlock[nCntBlock].bInsight = true;
				}
			}
			else
			{// �͈͊O
				// �~�j�Q�[���p�̔����false
				g_aBlock[nCntBlock].bInsight = false;
			}


			////�ʒu���X�V
			//g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
			//g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;
			//g_aBlock[nCntBlock].pos.z += g_aBlock[nCntBlock].move.z;
		}
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
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			// ���݂� g_info[nType] ���R�s�[
			g_aBlock[nCntBlock] = g_info[nType];

			// �����I�ɉ�]�������Z�b�g���Đݒ�
			g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].rot = rot;
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

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse)
		{
			// �u���b�N OBB �̏����擾
			D3DXMATRIX blockWorld = g_aBlock[nCntBlock].mtxWorld;
			D3DXVECTOR3 blockSize = g_aBlock[nCntBlock].size;

			// �v���C���[ OBB �̏����擾
			D3DXMATRIX playerWorld;
			D3DXMatrixTranslation(&playerWorld, pPos->x, pPos->y, pPos->z);

			if (g_aBlock[nCntBlock].nType == BLOCKTYPE_UFOCATCHER1)
			{
				// OBB �Փ˔���
				if (CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
				{
					// Z���̏Փ˕␳
					pPos->z = pPosOld->z;
					playerWorld._43 = pPos->z;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// �Փˉ����ł�����AZ�������̈ړ��ʂ����炩�Ɍ���
						pMove->z *= 0.5f;  // Z���ړ����������Ċ�����Č�
						continue;
					}

					// X���̏Փ˕␳
					pPos->x = pPosOld->x;
					playerWorld._41 = pPos->x;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// �Փˉ����ł�����AX�������̈ړ��ʂ����炩�Ɍ���
						pMove->x *= 0.5f;  // X���ړ����������Ċ�����Č�
						continue;
					}

					// Y���̏Փ˕␳
					pPos->y = pPosOld->y;
					playerWorld._42 = pPos->y;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// �Փˉ����ł�����AY�������̈ړ��ʂ����炩�Ɍ���
						pMove->y *= 0.5f;  // Y���ړ����������Ċ�����Č�
						continue;
					}

					// �Ō�ɑS�����~ (�Փˉ����ł��Ȃ������ꍇ)
					pMove->x = 0.0f;
					pMove->y = 0.0f;
					pMove->z = 0.0f;
				}
			}

			if (g_aBlock[nCntBlock].nType == BLOCKTYPE_ARCADE1)
			{
				// OBB �Փ˔���
				if (CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
				{
					// Z���̏Փ˕␳
					pPos->z = pPosOld->z;
					playerWorld._43 = pPos->z;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// �Փˉ����ł�����AZ�������̈ړ��ʂ����炩�Ɍ���
						pMove->z *= 0.5f;  // Z���ړ����������Ċ�����Č�
						continue;
					}

					// X���̏Փ˕␳
					pPos->x = pPosOld->x;
					playerWorld._41 = pPos->x;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// �Փˉ����ł�����AX�������̈ړ��ʂ����炩�Ɍ���
						pMove->x *= 0.5f;  // X���ړ����������Ċ�����Č�
						continue;
					}

					// Y���̏Փ˕␳
					pPos->y = pPosOld->y;
					playerWorld._42 = pPos->y;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// �Փˉ����ł�����AY�������̈ړ��ʂ����炩�Ɍ���
						pMove->y *= 0.5f;  // Y���ړ����������Ċ�����Č�
						continue;
					}

					// �Ō�ɑS�����~ (�Փˉ����ł��Ȃ������ꍇ)
					pMove->x = 0.0f;
					pMove->y = 0.0f;
					pMove->z = 0.0f;
				}
			}
			else
			{
				// OBB �Փ˔���
				if (CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
				{
					// Z���̏Փ˕␳
					pPos->z = pPosOld->z;
					playerWorld._43 = pPos->z;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// �Փˉ����ł�����AZ�������̈ړ��ʂ����炩�Ɍ���
						pMove->z *= 0.5f;  // Z���ړ����������Ċ�����Č�
						continue;
					}

					// X���̏Փ˕␳
					pPos->x = pPosOld->x;
					playerWorld._41 = pPos->x;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// �Փˉ����ł�����AX�������̈ړ��ʂ����炩�Ɍ���
						pMove->x *= 0.5f;  // X���ړ����������Ċ�����Č�
						continue;
					}

					// Y���̏Փ˕␳
					pPos->y = pPosOld->y;
					playerWorld._42 = pPos->y;
					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// �Փˉ����ł�����AY�������̈ړ��ʂ����炩�Ɍ���
						pMove->y *= 0.5f;  // Y���ړ����������Ċ�����Č�
						continue;
					}

					// �Ō�ɑS�����~ (�Փˉ����ł��Ȃ������ꍇ)
					pMove->x = 0.0f;
					pMove->y = 0.0f;
					pMove->z = 0.0f;
				}

			}

		}
	}
}
//==============================================
//�u���b�N�̓����蔻��(OBB���g�p���ĉ�]���l��)
//==============================================
bool CheckOBBCollision(const D3DXMATRIX& world1, const D3DXVECTOR3& size1,
	const D3DXMATRIX& world2, const D3DXVECTOR3& size2)
{
	// ���[���h�}�g���b�N�X�I�I
	// �e OBB �̒��S���W���v�Z
	D3DXVECTOR3 center1(world1._41, world1._42, world1._43);
	D3DXVECTOR3 center2(world2._41, world2._42, world2._43);

	// �e OBB �̎����擾
	D3DXVECTOR3 axes1[3] = 
	{
		{world1._11, world1._12, world1._13}, // X��
		{world1._21, world1._22, world1._23}, // Y��
		{world1._31, world1._32, world1._33}  // Z��
	};

	D3DXVECTOR3 axes2[3] = 
	{
		{world2._11, world2._12, world2._13}, // X��
		{world2._21, world2._22, world2._23}, // Y��
		{world2._31, world2._32, world2._33}  // Z��
	};

	// �������藝 (Separating Axis Theorem) ��p���Ĕ���
	for (int nCnt = 0; nCnt < 3; ++nCnt)
	{
		if (!OverlapOnAxis(center1, axes1, size1, center2, axes2, size2, axes1[nCnt]))
		{
			return false; // ������������������Փ˂��Ă��Ȃ�
		}
		if (!OverlapOnAxis(center1, axes1, size1, center2, axes2, size2, axes2[nCnt]))
		{
			return false; // ������������������Փ˂��Ă��Ȃ�
		}
	}

	// �N���X���̃`�F�b�N
	for (int Cross = 0; Cross < 3; ++Cross)
	{
		for (int Cross2 = 0; Cross2 < 3; ++Cross2)
		{
			D3DXVECTOR3 crossAxis;
			D3DXVec3Cross(&crossAxis, &axes1[Cross], &axes2[Cross2]);
			if (D3DXVec3Length(&crossAxis) > 0.001f) 
			{ // �[���x�N�g���̃`�F�b�N
				if (!OverlapOnAxis(center1, axes1, size1, center2, axes2, size2, crossAxis)) 
				{
					return false; // ������������������Փ˂��Ă��Ȃ�
				}
			}
		}
	}

	return true; // ���������Ȃ����ߏՓ˂��Ă���
}
//=================================
//OBB���e�͈͌v�Z����
//=================================
bool OverlapOnAxis(const D3DXVECTOR3& center1, const D3DXVECTOR3 axes1[3], const D3DXVECTOR3& size1,
	const D3DXVECTOR3& center2, const D3DXVECTOR3 axes2[3], const D3DXVECTOR3& size2, const D3DXVECTOR3& axis)
{
	// �e OBB ���w�肳�ꂽ���ɓ��e�������̔��a���v�Z
	float radius1 = GetProjectionRadius(size1, axes1, axis);
	float radius2 = GetProjectionRadius(size2, axes2, axis);

	// OBB �̒��S�̋������w�肳�ꂽ���ɓ��e
	D3DXVECTOR3 centerDiff = center2 - center1;
	float distance = fabs(D3DXVec3Dot(&centerDiff, &axis));

	// ���e�̏d�Ȃ�𔻒�
	return distance <= (radius1 + radius2);
}
//=================================
//OBB�ɕK�v�Ȕ͈͌v�Z����
//=================================
float GetProjectionRadius(const D3DXVECTOR3& size, const D3DXVECTOR3 axes[3], const D3DXVECTOR3& axis)
{
	// �e�����w�肳�ꂽ���ɓ��e���A���̐�Βl�𑫂����킹��
	return fabs(D3DXVec3Dot(&axes[0], &axis)) * size.x / 2 +
		fabs(D3DXVec3Dot(&axes[1], &axis)) * size.y / 2 +
		fabs(D3DXVec3Dot(&axes[2], &axis)) * size.z / 2;
}
//=================================
//�C�x���g���菈��
//=================================
bool BlockInteraction(void)
{

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		Player* pPlayer = GetPlayer();

		if (g_aBlock[nCntBlock].bUse && g_aBlock[nCntBlock].nType == BLOCKTYPE_ARCADE1)
		{
			// �u���b�N�Ƃ̋������v�Z
			float distance = 
				(g_aBlock[nCntBlock].pos.x - pPlayer->pos.x) * (g_aBlock[nCntBlock].pos.x - pPlayer->pos.x) +
				(g_aBlock[nCntBlock].pos.y - pPlayer->pos.y) * (g_aBlock[nCntBlock].pos.y - pPlayer->pos.y) +
				(g_aBlock[nCntBlock].pos.z - pPlayer->pos.z) * (g_aBlock[nCntBlock].pos.z - pPlayer->pos.z);

			float interactionRange = 60.0f;// ����͈�

			// �͈͓�
			if (distance <= (interactionRange * interactionRange)) 
			{
				return true;
			}

			return false;// �͈͊O
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