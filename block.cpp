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
#include "ui.h"
#include "camera.h"
#include "game.h"
#include "meshcylinder.h"
#include "light.h"
#include "sound.h"

//�O���[�o���ϐ�
Block g_aBlock[MAX_BLOCK];		// �u���b�N���
Block g_info[BLOCKTYPE_MAX];	// �u���b�N�̑f�ޏ��
Flags g_flag;					// �t���O���

//=============================
// �u���b�N�̏���������
//=============================
void InitBlock(void)
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

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

	// �t���O�����g�\���̂̏�����
	g_flag.bFog = true;
	g_flag.bExit = false;
	g_flag.bArcade = false;
	g_flag.bCatcher = false;
	g_flag.bBall = false;
	g_flag.bKeypad = false;
	g_flag.bFuse = false;
	g_flag.bFusebox = false;
	g_flag.bFuseGet = false;
	g_flag.bFuseCmp = false;
	g_flag.bHintBall = false;
	g_flag.bHintBear = false;
	g_flag.bSet = false;
	g_flag.bSet2 = false;
	g_flag.bSet3 = false;

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

	int nNumVtx;					// ���_��
	DWORD sizeFVF;					// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^

	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		g_info[nCnt].bUse = true;

		g_info[nCnt].blockinfo[nCnt].vtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);		// �ŏ��l��������
		g_info[nCnt].blockinfo[nCnt].vtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);	// �ő�l��������

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


}
//=============================
// �u���b�N�̏I������
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
	

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 < BLOCKTYPE_MAX; nCnt2++)
		{
			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCnt].blockinfo[nCnt2].dwNumMat; nCntMat++)
			{
				//�e�N�X�`���̔j��
				if (g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat] != NULL)
				{
					g_info[nCnt].blockinfo[nCnt].apTexture[nCntMat] = NULL;
				}
			}

			//���b�V���̔j��
			if (g_info[nCnt].blockinfo[nCnt].pMesh != NULL)
			{
				g_info[nCnt].blockinfo[nCnt].pMesh = NULL;
			}

			//�}�e���A���̔j��
			if (g_info[nCnt].blockinfo[nCnt].pBuffMat != NULL)
			{
				g_info[nCnt].blockinfo[nCnt].pBuffMat = NULL;
			}
		}
	}

}
//=============================
// �u���b�N�̍X�V����
//=============================
void UpdateBlock(void)
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		Player* pPlayer = GetPlayer(); // �v���C���[���̎擾
		Camera* pCamera = GetCamera();
		GAME* pGame = GetGame();

		if (g_aBlock[nCntBlock].bUse == true)
		{
			MeshcylinderOnBlock(BLOCKTYPE_FUSE);
			MeshcylinderOnBlock(BLOCKTYPE_BALL);
			MeshcylinderOnBlock(BLOCKTYPE_BEAR);

			// �����䒆����������s
			CheckBlocksInCenter();

			// �q���[�Y����ɓ��ꂽ
			if (g_flag.bFuse == true && KeyboardTrigger(DIK_E) == true && g_aBlock[nCntBlock].bInsight == true)
			{
				if (g_aBlock[nCntBlock].nType == BLOCKTYPE_FUSE)
				{
					PlaySound(SOUND_LABEL_FUSEGET);
					g_aBlock[nCntBlock].bUse = false;
					g_flag.bFuseGet = true;
				}
			}

			// �q���[�Y�{�b�N�X�Ƀq���[�Y���͂߂�
			if (g_flag.bFuseGet == true && KeyboardTrigger(DIK_E) == true && g_aBlock[nCntBlock].bInsight == true)
			{
				if (g_aBlock[nCntBlock].nType == BLOCKTYPE_FUSEBOX)
				{
					PlaySound(SOUND_LABEL_FUSESET);
					g_flag.bFuseCmp = true;
					g_aBlock[nCntBlock].bUse = false;
					SetBlock(D3DXVECTOR3(1140.0f, 80.0f, 250.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), BLOCKTYPE_FUSEBOX_CMP);

					g_flag.bFog = false; // �t���O��ύX
				}
			}

			// �{�[���v�[�����N���A������
			if (pGame->bBallClear == true && g_flag.bSet == false)
			{
				SetBlock(D3DXVECTOR3(805.0f, 0.0f, -165.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_BALL);

				g_flag.bSet = true;
			}

			// �N���[���Q�[�����N���A������
			if (pGame->bACClear == true && g_flag.bSet2 == false)
			{
				SetBlock(D3DXVECTOR3(-520.0f, 0.0f, -785.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_BEAR);

				g_flag.bSet2 = true;
			}

			// �p�X���[�h�������Ă���
			if (pGame->bPassClear == true && g_flag.bSet3 == false)
			{
				SetBlock(D3DXVECTOR3(0.0f, 0.0f, 1010.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_CLEAR);

				g_flag.bSet3 = true;
			}
			if (pGame->bPassClear == true && g_aBlock[nCntBlock].nType == BLOCKTYPE_EXIT)
			{
				if (g_aBlock[nCntBlock].pos.x > -200.0f)
				{
					g_aBlock[nCntBlock].move.x = -1.1f;
				}
				else if (g_aBlock[nCntBlock].pos.x < -200.0f)
				{
					g_aBlock[nCntBlock].move.x = 0.0f;
				}
			}
			if (pGame->bPassClear == true && g_aBlock[nCntBlock].nType == BLOCKTYPE_EXIT2)
			{
				if (g_aBlock[nCntBlock].pos.x < 200.0f)
				{
					g_aBlock[nCntBlock].move.x = 1.1f;
				}
				else if (g_aBlock[nCntBlock].pos.x > 200.0f)
				{
					g_aBlock[nCntBlock].move.x = 0.0f;
				}
			}

			//�ʒu���X�V
			g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
			g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;
			g_aBlock[nCntBlock].pos.z += g_aBlock[nCntBlock].move.z;
		}
	}
}
//=============================
// �u���b�N�̕`�揈��
//=============================
void DrawBlock(void)
{
	GAME* pGame = GetGame();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

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
				pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].blockinfo[nType].pBuffMat->GetBufferPointer();

				// �n�C���C�g�p�̃}�e���A�����쐬
				D3DMATERIAL9 matHighlight = pMat[nCntMat].MatD3D;

				if (g_aBlock[nCntBlock].bInsight == true && g_aBlock[nCntBlock].nType != BLOCKTYPE_UFOCATCHER1 &&
					g_aBlock[nCntBlock].nType != BLOCKTYPE_BALLPOOL && g_aBlock[nCntBlock].nType != BLOCKTYPE_ARCADE1 &&
					g_aBlock[nCntBlock].nType != BLOCKTYPE_KEYPAD && g_aBlock[nCntBlock].nType != BLOCKTYPE_FUSEBOX)
				{
					matHighlight.Emissive.r = 0.2f;
					matHighlight.Emissive.g = 0.2f;
					matHighlight.Emissive.b = 0.2f;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_FUSEBOX &&
					g_flag.bFuseGet == true && g_aBlock[nCntBlock].bInsight == true)
				{
					matHighlight.Emissive.r = 0.2f;
					matHighlight.Emissive.g = 0.2f;
					matHighlight.Emissive.b = 0.2f;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_UFOCATCHER1 && pGame->bACClear == false &&
					g_flag.bFuseCmp == true && g_aBlock[nCntBlock].bInsight == true)
				{
					matHighlight.Emissive.r = 0.2f;
					matHighlight.Emissive.g = 0.2f;
					matHighlight.Emissive.b = 0.2f;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_ARCADE1 &&
					g_flag.bFuseCmp == true && g_aBlock[nCntBlock].bInsight == true)
				{
					matHighlight.Emissive.r = 0.2f;
					matHighlight.Emissive.g = 0.2f;
					matHighlight.Emissive.b = 0.2f;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BALLPOOL && pGame->bBallClear == false &&
					g_flag.bFuseCmp == true && g_aBlock[nCntBlock].bInsight == true)
				{
					matHighlight.Emissive.r = 0.2f;
					matHighlight.Emissive.g = 0.2f;
					matHighlight.Emissive.b = 0.2f;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_KEYPAD && pGame->bSTClear == true &&
					pGame->bACClear == true && pGame->bBallClear == true && g_aBlock[nCntBlock].bInsight == true &&
					pGame->bPassClear == false)
				{
					matHighlight.Emissive.r = 0.2f;
					matHighlight.Emissive.g = 0.2f;
					matHighlight.Emissive.b = 0.2f;
				}

				// �}�e���A�����Z�b�g
				pDevice->SetMaterial(&matHighlight);

				// �e�N�X�`�����Z�b�g
				pDevice->SetTexture(0, g_aBlock[nCntBlock].blockinfo[nType].apTexture[nCntMat]);

				// ���f���̕`��
				g_aBlock[nCntBlock].blockinfo[nType].pMesh->DrawSubset(nCntMat);
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
	
}
//=============================
// �u���b�N�̐ݒ菈��
//=============================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			// ���݂� g_info[nType] ���R�s�[
			g_aBlock[nCntBlock] = g_info[nType];

			// ��]�������Z�b�g���Đݒ�
			g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].rot = rot;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bUse = true;

			AddPointlightToBlock();

			break;
		}
	}
}
//=============================
// �u���b�N�̓����蔻��
//=============================
void CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, D3DXVECTOR3* pSize)
{

	GAME* pGame = GetGame();

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

			if (g_aBlock[nCntBlock].nType == BLOCKTYPE_CLEAR)
			{
				// OBB �Փ˔���
				if (CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
				{
					// Z���̏Փ˕␳
					pPos->z = pPosOld->z;
					playerWorld._43 = pPos->z;

					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// Z�������̈ړ��ʂ����炩�Ɍ���
						pMove->z *= 0.5f;

						// �~�j�Q�[�������ׂăN���A���Ă�����
						if (pGame->bPassClear == true)
						{
							g_flag.bExit = true;
						}

						continue;
					}

					// X���̏Փ˕␳
					pPos->x = pPosOld->x;
					playerWorld._41 = pPos->x;

					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// X�������̈ړ��ʂ����炩�Ɍ���
						pMove->x *= 0.5f;
						continue;
					}

					// Y���̏Փ˕␳
					pPos->y = pPosOld->y;
					playerWorld._42 = pPos->y;

					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// Y�������̈ړ��ʂ����炩�Ɍ���
						pMove->y *= 0.5f;
						continue;
					}

				}
			}
			else
			{
				if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BEAR || g_aBlock[nCntBlock].nType == BLOCKTYPE_BALL ||
					g_aBlock[nCntBlock].nType == BLOCKTYPE_FUSE)
				{
					continue;
				}

				// OBB �Փ˔���
				if (CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
				{
					// Z���̏Փ˕␳
					pPos->z = pPosOld->z;
					playerWorld._43 = pPos->z;

					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// Z�������̈ړ��ʂ����炩�Ɍ���
						pMove->z *= 0.5f;
						continue;
					}

					// X���̏Փ˕␳
					pPos->x = pPosOld->x;
					playerWorld._41 = pPos->x;

					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// X�������̈ړ��ʂ����炩�Ɍ���
						pMove->x *= 0.5f;
						continue;
					}

					// Y���̏Փ˕␳
					pPos->y = pPosOld->y;
					playerWorld._42 = pPos->y;

					if (!CheckOBBCollision(blockWorld, blockSize, playerWorld, *pSize))
					{
						// Y�������̈ړ��ʂ����炩�Ɍ���
						pMove->y *= 0.5f;
						continue;
					}

				}

			}

		}
	}
}
//==================================================
// �u���b�N�̓����蔻��(OBB���g�p���ĉ�]���l��)
//==================================================
bool CheckOBBCollision(const D3DXMATRIX& world1, const D3DXVECTOR3& size1,
	const D3DXMATRIX& world2, const D3DXVECTOR3& size2)
{
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

	// �������藝 (Separating Axis Theorem) ���g���Ĕ���
	for (int nCnt = 0; nCnt < 3; nCnt++)
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
	for (int Cross = 0; Cross < 3; Cross++)
	{
		for (int Cross2 = 0; Cross2 < 3; Cross2++)
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

	return true; // �Փ˂��Ă���
}
//=================================
// OBB���e�͈͌v�Z����
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
// OBB�ɕK�v�Ȕ͈͌v�Z����
//=================================
float GetProjectionRadius(const D3DXVECTOR3& size, const D3DXVECTOR3 axes[3], const D3DXVECTOR3& axis)
{
	// �e�����w�肳�ꂽ���ɓ��e���A���̐�Βl�𑫂����킹��
	return fabs(D3DXVec3Dot(&axes[0], &axis)) * size.x / 2.0f +
		fabs(D3DXVec3Dot(&axes[1], &axis)) * size.y / 2.0f +
		fabs(D3DXVec3Dot(&axes[2], &axis)) * size.z / 2.0f;
}
//=================================
// ������(�t���X�^��)�������菈��
//=================================
void CheckBlocksInCenter(void)
{
	Player* pPlayer = GetPlayer();
	Camera* pCamera = GetCamera();

	const float fov = D3DX_PI / 4.0f;				// ����p
	const float centerFovRatio = 0.4f;				// �����͈͂̕�
	const float maxAngle = fov * centerFovRatio;
	const float heightTolerance = 1.0f;				// �����̋��e�͈�

	float maxDistance = 0.0f;						// �C���^���N�g�\�ȍő勗��

	// �v���C���[�̖ڐ�����ɂ���
	D3DXVECTOR3 eyePos = pCamera->posV;				// �J�����ʒu���

	// �v���C���[�̎��������𐳋K��
	D3DXVECTOR3 forward = pPlayer->forward;
	D3DXVec3Normalize(&forward, &forward);

	// �S�u���b�N��bInsight�����Z�b�g
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].bInsight = false; // ������

		// �u���b�N���Ƃ̃C���^���N�g�t���O��ݒ�
		switch (g_aBlock[nCntBlock].nType)
		{
		case BLOCKTYPE_FUSE:
			g_flag.bFuse = false;
			break;

		case BLOCKTYPE_ARCADE1:
			g_flag.bArcade = false;
			break;

		case BLOCKTYPE_BALLPOOL:
			g_flag.bBall = false;
			break;

		case BLOCKTYPE_KEYPAD:
			g_flag.bKeypad = false;
			break;

		case BLOCKTYPE_UFOCATCHER1:
			g_flag.bCatcher = false;
			break;

		case BLOCKTYPE_FUSEBOX:
			g_flag.bFusebox = false;
			break;

		case BLOCKTYPE_BALL:
			g_flag.bHintBall = false;
			break;

		case BLOCKTYPE_BEAR:
			g_flag.bHintBear = false;
			break;

		}

	}

	// �����͈͂��w�苗�����ɂ���u���b�N���`�F�b�N
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (!g_aBlock[nCntBlock].bUse)
		{
			continue; // �g�p����Ă��Ȃ��u���b�N�̓X�L�b�v
		}

		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_FUSE)
		{
			maxDistance = 100.0f;
		}
		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_FUSEBOX)
		{
			maxDistance = 100.0f;
		}
		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_UFOCATCHER1)
		{
			maxDistance = 120.0f;
		}
		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_ARCADE1)
		{
			maxDistance = 100.0f;
		}
		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BALLPOOL)
		{
			maxDistance = 160.0f;
		}
		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_KEYPAD)
		{
			maxDistance = 80.0f;
		}
		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BALL)
		{
			maxDistance = 100.0f;
		}
		if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BEAR)
		{
			maxDistance = 100.0f;
		}


		// ����̎�ނ̂ݑΏۂƂ���
		if (g_aBlock[nCntBlock].nType != BLOCKTYPE_ARCADE1 && g_aBlock[nCntBlock].nType != BLOCKTYPE_UFOCATCHER1 &&
			g_aBlock[nCntBlock].nType != BLOCKTYPE_BALLPOOL && g_aBlock[nCntBlock].nType != BLOCKTYPE_KEYPAD &&
			g_aBlock[nCntBlock].nType != BLOCKTYPE_FUSE && g_aBlock[nCntBlock].nType != BLOCKTYPE_FUSEBOX &&
			g_aBlock[nCntBlock].nType != BLOCKTYPE_BALL && g_aBlock[nCntBlock].nType != BLOCKTYPE_BEAR)
		{
			continue; // �ΏۊO�̎�ނ̓X�L�b�v
		}

		// �u���b�N�܂ł̃x�N�g�����v�Z(�J�����̈ʒu����ɂ���)
		D3DXVECTOR3 toBlock = g_aBlock[nCntBlock].pos - eyePos;
		float distance = D3DXVec3Length(&toBlock);

		// �����`�F�b�N (��苗���ȏ�Ȃ�X�L�b�v)
		if (distance > maxDistance)
		{
			continue;
		}

		// toBlock�𐳋K�����ĕ����x�N�g���𓾂�
		D3DXVECTOR3 toBlockNormalized;
		D3DXVec3Normalize(&toBlockNormalized, &toBlock);

		// adjustedForward��Y�����𒲐��i����������������j
		D3DXVECTOR3 adjustedForward = forward;
		adjustedForward.y -= 0.2f;
		D3DXVec3Normalize(&adjustedForward, &adjustedForward);

		// �����Ƃ̊p�x���v�Z
		float dotProduct = D3DXVec3Dot(&adjustedForward, &toBlockNormalized);
		float angle = acosf(dotProduct); // �����Ƃ̊p�x�i���W�A���j

		// �����͈͂��w�苗�����ɂ���ꍇ�̂� true
		if (angle < maxAngle)
		{
			g_aBlock[nCntBlock].bInsight = true;

			// �u���b�N���Ƃ̃C���^���N�g�t���O��ݒ�
			switch (g_aBlock[nCntBlock].nType)
			{
			case BLOCKTYPE_FUSE:        
				g_flag.bFuse = true;
				break;

			case BLOCKTYPE_ARCADE1:     
				g_flag.bArcade = true;
				break;

			case BLOCKTYPE_BALLPOOL:    
				g_flag.bBall = true;
				break;

			case BLOCKTYPE_KEYPAD:      
				g_flag.bKeypad = true;
				break;

			case BLOCKTYPE_UFOCATCHER1: 
				g_flag.bCatcher = true;
				break;

			case BLOCKTYPE_FUSEBOX:     
				g_flag.bFusebox = true;
				break;

			case BLOCKTYPE_BALL:
				g_flag.bHintBall = true;
				break;

			case BLOCKTYPE_BEAR:
				g_flag.bHintBear = true;
				break;

			}
		}
	}
}
//================================================
// ���b�V���V�����_�[�̑Ώۃu���b�N��I�����鏈��
//================================================
void MeshcylinderOnBlock(int targetType)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].nType == targetType)
		{
			// �u���b�N�̈ʒu���擾
			D3DXVECTOR3 meshPos = g_aBlock[nCntBlock].pos;

			// ���b�V���V�����_�[�̈ʒu��ݒ�
			SetMeshcylinder(meshPos);

			break; // 1��������I���i�����̏ꍇ�� break ���폜�j
		}
	}
}
//================================================
// �Ώۂ̃u���b�N�̈ʒu�擾����
//================================================
bool GetBlockPosition(D3DXVECTOR3* outPosition)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// �Ώۂ̃u���b�N�̈ʒu���擾����
		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].nType == BLOCKTYPE_TITLEBOARD)
		{
			*outPosition = g_aBlock[nCntBlock].pos;
			return true; // �ʒu���擾�ł���
		}
	}
	return false; // �`���[�g���A���{�[�h��������Ȃ�����
}
//============================================
// �u���b�N�̎擾
//============================================
Block* GetBlock(void)
{
	return &g_aBlock[0];
}
//============================================
// �t���O�̎擾
//============================================
Flags* GetFlag (void)
{
	return &g_flag;
}
