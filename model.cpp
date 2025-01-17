//=======================================
//
// ���f������[model.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "model.h"
#include "player.h"
#include "input.h"
#include "enemy.h"
//#include "score.h"
//#include "particle.h"
//#include "sound.h"

//�O���[�o���ϐ�
Model g_aModel[MAX_MODEL];//���f�����

//=============================
//���f���̏���������
//=============================
void InitModel(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//������
		g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aModel[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
		g_aModel[nCntModel].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ŏ��l
		g_aModel[nCntModel].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ő�l
		g_aModel[nCntModel].bUse = false;
		g_aModel[nCntModel].bScoreAdded = false;
		g_aModel[nCntModel].bSoundPlayed = false;
		g_aModel[nCntModel].nType = WALLTYPE_NORMAL;
	}

	for (int nCntModel2 = 0; nCntModel2 < MAX_MODEL; nCntModel2++)
	{

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(MODEL[nCntModel2],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aModel[nCntModel2].pBuffMat,
			NULL,
			&g_aModel[nCntModel2].dwNumMat,
			&g_aModel[nCntModel2].pMesh);

	}

	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	for (int nCntModel3 = 0; nCntModel3 < MAX_MODEL; nCntModel3++)
	{

		//���_���̎擾
		nNumVtx = g_aModel[nCntModel3].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̎擾
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[nCntModel3].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aModel[nCntModel3].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ŏ��l�ő�l���擾
			if (vtx.x < g_aModel[nCntModel3].vtxMin.x)
			{
				g_aModel[nCntModel3].vtxMin.x = vtx.x;
			}
			else if (vtx.y < g_aModel[nCntModel3].vtxMin.y)
			{
				g_aModel[nCntModel3].vtxMin.y = vtx.y;
			}
			else if (vtx.z < g_aModel[nCntModel3].vtxMin.z)
			{
				g_aModel[nCntModel3].vtxMin.z = vtx.z;
			}

			if (vtx.x > g_aModel[nCntModel3].vtxMax.x)
			{
				g_aModel[nCntModel3].vtxMax.x = vtx.x;
			}
			else if (vtx.y > g_aModel[nCntModel3].vtxMax.y)
			{
				g_aModel[nCntModel3].vtxMax.y = vtx.y;
			}
			else if (vtx.z > g_aModel[nCntModel3].vtxMax.z)
			{
				g_aModel[nCntModel3].vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		g_aModel[nCntModel3].size.x = (g_aModel[nCntModel3].vtxMax.x - g_aModel[nCntModel3].vtxMin.x);
		g_aModel[nCntModel3].size.y = (g_aModel[nCntModel3].vtxMax.y - g_aModel[nCntModel3].vtxMin.y);
		g_aModel[nCntModel3].size.z = (g_aModel[nCntModel3].vtxMax.z - g_aModel[nCntModel3].vtxMin.z);

		//���_�o�b�t�@�̃A�����b�N
		g_aModel[nCntModel3].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_aModel[nCntModel3].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel3].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���

				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aModel[nCntModel3].apTexture[nCntMat]);

			}
		}
	}
}
//=============================
//���f���̏I������
//=============================
void UninitModel(void)
{
	//StopSound(SOUND_LABEL_MONEY);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].dwNumMat; nCntMat++)
		{
			//�e�N�X�`���̔j��
			if (g_aModel[nCntModel].apTexture[nCntMat] != NULL)
			{
				g_aModel[nCntModel].apTexture[nCntMat]->Release();
				g_aModel[nCntModel].apTexture[nCntMat] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_aModel[nCntModel].pMesh != NULL)
		{
			g_aModel[nCntModel].pMesh->Release();
			g_aModel[nCntModel].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_aModel[nCntModel].pBuffMat != NULL)
		{
			g_aModel[nCntModel].pBuffMat->Release();
			g_aModel[nCntModel].pBuffMat = NULL;
		}
	}
}
//=============================
//���f���̍X�V����
//=============================
void UpdateModel(void)
{

	//for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//{
	//	bool bTaskAllCmp = GetTaskAllCmp();
	//	bool bTaskCmp0 = GetTaskCmp0();
	//	bool bTaskCmp = GetTaskCmp();
	//	bool bTaskCmp2 = GetTaskCmp2();
	//	bool bTaskCmp3 = GetTaskCmp3();
	//	bool bTaskCmp4 = GetTaskCmp4();
	//	bool bTaskCmp5 = GetTaskCmp5();

	//	TASKBAR* pTask = GetTaskbar();

	//	if (bTaskAllCmp == true)
	//	{
	//		if (g_aModel[nCntModel].nType == WALLTYPE_DOOR)
	//		{
	//			if (g_aModel[nCntModel].pos.y >= 80)
	//			{
	//				g_aModel[nCntModel].move.y = 0.0f;
	//			}
	//			else
	//			{
	//				g_aModel[nCntModel].move.y += 0.2f;
	//			}
	//		}
	//	}

	//	if (bTaskCmp == true && bTaskCmp2 == true && bTaskCmp3)
	//	{
	//		if (g_aModel[nCntModel].nType == WALLTYPE_ROOM)
	//		{
	//			if (g_aModel[nCntModel].pos.y >= 80)
	//			{
	//				g_aModel[nCntModel].move.y = 0.0f;
	//			}
	//			else
	//			{
	//				g_aModel[nCntModel].move.y += 0.2f;
	//			}
	//		}
	//	}

	//	if (bTaskCmp4 == true)
	//	{
	//		if (g_aModel[nCntModel].bUse == true && g_aModel[nCntModel].nType == WALLTYPE_BOXTOP1)
	//		{
	//			// ������x�����炷
	//			if (!g_aModel[nCntModel].bSoundPlayed)
	//			{
	//				PlaySound(SOUND_LABEL_MONEY);
	//				g_aModel[nCntModel].bSoundPlayed = true; // ���Đ��ς݃t���O�𗧂Ă�
	//			}

	//			if (g_aModel[nCntModel].rot.z <= -1.49f)
	//			{
	//				g_aModel[nCntModel].rot.z -= 0.0f;

	//				if (!g_aModel[nCntModel].bScoreAdded)
	//				{
	//					AddScore(100000);
	//					g_aModel[nCntModel].bScoreAdded = true;
	//				}
	//			}
	//			else if (g_aModel[nCntModel].rot.z < 1.5f)
	//			{
	//				g_aModel[nCntModel].rot.z -= 0.08f;
	//			}
	//		}
	//	}

	//	if (bTaskCmp5 == true)
	//	{
	//		if (g_aModel[nCntModel].bUse == true && g_aModel[nCntModel].nType == WALLTYPE_BOXTOP2)
	//		{
	//			// ������x�����炷
	//			if (!g_aModel[nCntModel].bSoundPlayed)
	//			{
	//				PlaySound(SOUND_LABEL_MONEY);
	//				g_aModel[nCntModel].bSoundPlayed = true;
	//			}

	//			if (g_aModel[nCntModel].rot.z >= 1.49f)
	//			{
	//				g_aModel[nCntModel].rot.z -= 0.0f;

	//				if (!g_aModel[nCntModel].bScoreAdded)
	//				{
	//					AddScore(100000);
	//					g_aModel[nCntModel].bScoreAdded = true;
	//				}
	//			}
	//			else if (g_aModel[nCntModel].rot.z < 1.5f)
	//			{
	//				g_aModel[nCntModel].rot.z += 0.08f;
	//			}
	//		}
	//	}

	//	//�ʒu���X�V
	//	g_aModel[nCntModel].pos.x += g_aModel[nCntModel].move.x;
	//	g_aModel[nCntModel].pos.y += g_aModel[nCntModel].move.y;
	//	g_aModel[nCntModel].pos.z += g_aModel[nCntModel].move.z;
	//}
}
//=============================
//���f���̕`�揈��
//=============================
void DrawModel(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{

		if (g_aModel[nCntModel].bUse == true)
		{

			//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxRot, mtxTrans;

			D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

			D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);

			//���݂̃}�e���A���̎擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].dwNumMat; nCntMat++)
			{

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_aModel[nCntModel].apTexture[nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_aModel[nCntModel].pMesh->DrawSubset(nCntMat);

			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}
//=============================
//���f���̐ݒ菈��
//=============================
void SetModel(D3DXVECTOR3 pos,int nType)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{

			g_aModel[nCntModel].pos = pos;
			g_aModel[nCntModel].nType = nType;
			g_aModel[nCntModel].bUse = true;

			break;

		}
	}
}
//=============================
//���f���̓����蔻��
//=============================
void CollisionModel(void)
{

	//bool bTask = false;//�G��Ă��邩�ǂ���

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		Player* pPlayer = GetPlayer();
		Enemy* pEnemy = GetEnemy();

		if (g_aModel[nCntModel].nType == WALLTYPE_NORMAL)
		{

			if (pPlayer->posOld.y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y &&
				pPlayer->posOld.y + pPlayer->size.y > g_aModel[nCntModel].pos.y)
			{

				//���E(X����)�̓����蔻��
				if (pPlayer->pos.z - pPlayer->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
					pPlayer->pos.z + pPlayer->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
				{
					//������E�ɓ�������
					if (pPlayer->posOld.x + pPlayer->size.x / 2 < g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2 &&
						pPlayer->pos.x + pPlayer->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
					{
						pPlayer->pos.x = g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2 - pPlayer->size.x / 2 - 0.1f;
					}
					//�E���獶�ɓ�������
					else if (pPlayer->posOld.x - pPlayer->size.x / 2 > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
						pPlayer->pos.x - pPlayer->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2)
					{
						pPlayer->pos.x = (g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2) + pPlayer->size.x / 2 + 0.1f;
					}

				}

				//�O��(Z����)�̓����蔻��
				if (pPlayer->pos.x - pPlayer->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
					pPlayer->pos.x + pPlayer->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
				{

					//��O���瓖������
					if (pPlayer->posOld.z + pPlayer->size.z / 2 < g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2 &&
						pPlayer->pos.z + pPlayer->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
					{
						pPlayer->pos.z = (g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2) - pPlayer->size.z / 2 - 0.1f;
					}
					//�����瓖������
					else if (pPlayer->posOld.z - pPlayer->size.z / 2 > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
						pPlayer->pos.z - pPlayer->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2)
					{
						pPlayer->pos.z = (g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2) + pPlayer->size.z / 2 + 0.1f;
					}

				}

				//�c(Y����)�̓����蔻��
				if (pPlayer->posOld.x - pPlayer->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
					pPlayer->pos.x + pPlayer->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
				{

					if (pPlayer->posOld.z - pPlayer->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
						pPlayer->pos.z + pPlayer->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
					{

						//�ォ�牺�ɓ�������
						if (pPlayer->posOld.y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y &&
							pPlayer->pos.y > g_aModel[nCntModel].pos.y - g_aModel[nCntModel].size.y)
						{
							pPlayer->pos.y = (g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y / 2) + pPlayer->size.y / 2 - 0.9f;
							pPlayer->move.y = 0.0f;
						}
						//�������ɓ�������
						if (pPlayer->posOld.y - pPlayer->size.y / 2 < g_aModel[nCntModel].pos.y / 2 &&
							pPlayer->pos.y - pPlayer->size.y / 2 > g_aModel[nCntModel].pos.y / 2)
						{
							pPlayer->pos.y = (g_aModel[nCntModel].pos.y - pPlayer->size.y);
							pPlayer->move.y = 0.0f;
						}

					}
				}
			}

		}




		//�G�ƃ��f���̓����蔻��
		if (g_aModel[nCntModel].nType == WALLTYPE_NORMAL)
		{

			if (pEnemy->posOld.y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y &&
				pEnemy->posOld.y + pEnemy->size.y > g_aModel[nCntModel].pos.y)
			{

				//���E(X����)�̓����蔻��
				if (pEnemy->pos.z - pEnemy->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
					pEnemy->pos.z + pEnemy->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
				{
					//������E�ɓ�������
					if (pEnemy->posOld.x + pEnemy->size.x / 2 < g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2 &&
						pEnemy->pos.x + pEnemy->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
					{
						pEnemy->pos.x = g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2 - pEnemy->size.x / 2 - 0.1f;
					}
					//�E���獶�ɓ�������
					else if (pEnemy->posOld.x - pEnemy->size.x / 2 > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
						pEnemy->pos.x - pEnemy->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2)
					{
						pEnemy->pos.x = (g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2) + pEnemy->size.x / 2 + 0.1f;
					}

				}

				//�O��(Z����)�̓����蔻��
				if (pEnemy->pos.x - pEnemy->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
					pEnemy->pos.x + pEnemy->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
				{

					//��O���瓖������
					if (pEnemy->posOld.z + pEnemy->size.z / 2 < g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2 &&
						pEnemy->pos.z + pEnemy->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
					{
						pEnemy->pos.z = (g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2) - pEnemy->size.z / 2 - 0.1f;
					}
					//�����瓖������
					else if (pEnemy->posOld.z - pEnemy->size.z / 2 > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
						pEnemy->pos.z - pEnemy->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2)
					{
						pEnemy->pos.z = (g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2) + pEnemy->size.z / 2 + 0.1f;
					}

				}

				//�c(Y����)�̓����蔻��
				if (pEnemy->posOld.x - pEnemy->size.x / 2 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].size.x / 2 &&
					pEnemy->pos.x + pEnemy->size.x / 2 > g_aModel[nCntModel].pos.x - g_aModel[nCntModel].size.x / 2)
				{

					if (pEnemy->posOld.z - pEnemy->size.z / 2 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].size.z / 2 &&
						pEnemy->pos.z + pEnemy->size.z / 2 > g_aModel[nCntModel].pos.z - g_aModel[nCntModel].size.z / 2)
					{

						//�ォ�牺�ɓ�������
						if (pEnemy->posOld.y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y &&
							pEnemy->pos.y > g_aModel[nCntModel].pos.y - g_aModel[nCntModel].size.y)
						{
							pEnemy->pos.y = (g_aModel[nCntModel].pos.y + g_aModel[nCntModel].size.y / 2) + pEnemy->size.y / 2 - 0.9f;
							pEnemy->move.y = 0.0f;
						}
						//�������ɓ�������
						if (pEnemy->posOld.y - pEnemy->size.y / 2 < g_aModel[nCntModel].pos.y / 2 &&
							pEnemy->pos.y - pEnemy->size.y / 2 > g_aModel[nCntModel].pos.y / 2)
						{
							pEnemy->pos.y = (g_aModel[nCntModel].pos.y - pEnemy->size.y);
							pEnemy->move.y = 0.0f;
						}

					}
				}
			}

		}

	}

	//return bTask;

}