//=======================================
//
// �G�̏��� [enemy.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "fade.h"
#include "block.h"
#include "sound.h"
#include "shadow.h"

// ����|�C���g�z��
D3DXVECTOR3 patrolPoints[] =
{
	D3DXVECTOR3(1000.0f, 0.0f, 110.0f),
	D3DXVECTOR3(850.0f, 0.0f, 475.0f),
	D3DXVECTOR3(520.0f, 0.0f, 490.0f),
	D3DXVECTOR3(220.0f, 0.0f, 675.0f),
	D3DXVECTOR3(12.0f, 0.0f, 590.0f),
	D3DXVECTOR3(-190.0f, 0.0f, 635.0f),

	D3DXVECTOR3(-125.0f, 0.0f, 830.0f),
	D3DXVECTOR3(-225.0f, 0.0f, 830.0f),
	D3DXVECTOR3(-325.0f, 0.0f, 830.0f),
	D3DXVECTOR3(-425.0f, 0.0f, 830.0f),
	D3DXVECTOR3(500.0f, 0.0f, 830.0f),
	D3DXVECTOR3(550.0f, 0.0f, 830.0f),
	D3DXVECTOR3(600.0f, 0.0f, 830.0f),
	D3DXVECTOR3(650.0f, 0.0f, 830.0f),
	D3DXVECTOR3(700.0f, 0.0f, 830.0f),

	D3DXVECTOR3(830.0f, 0.0f, 655.0f),
	D3DXVECTOR3(850.0f, 0.0f, 475.0f),

	D3DXVECTOR3(-975.0f, 0.0f, 860.0f),
	D3DXVECTOR3(-1000.0f, 0.0f, 530.0f),
	D3DXVECTOR3(-1015.0f, 0.0f, 260.0f),
	D3DXVECTOR3(-1060.0f, 0.0f, 135.0f),

	D3DXVECTOR3(-1055.0f, 0.0f, -25.0f),
	D3DXVECTOR3(-1025.0f, 0.0f, -225.0f),
	D3DXVECTOR3(-1025.0f, 0.0f, -420.0f),
	D3DXVECTOR3(-1080.0f, 0.0f, -600.0f),
	D3DXVECTOR3(-1075.0f, 0.0f, -805.0f),
	D3DXVECTOR3(-785.0f, 0.0f, -800.0f),
	D3DXVECTOR3(-525.0f, 0.0f, -800.0f),
	D3DXVECTOR3(-335.0f, 0.0f, -800.0f),
	D3DXVECTOR3(45.0f, 0.0f, -730.0f),
	D3DXVECTOR3(378.0f, 0.0f, -705.0f),
	D3DXVECTOR3(495.0f, 0.0f, -670.0f),
	D3DXVECTOR3(475.0f, 0.0f, -420.0f),
	D3DXVECTOR3(570.0f, 0.0f, -235.0f),
	D3DXVECTOR3(830.0f, 0.0f, -140.0f),
	D3DXVECTOR3(840.0f, 0.0f, -265.0f),
	D3DXVECTOR3(935.0f, 0.0f, -365.0f),
	D3DXVECTOR3(985.0f, 0.0f, -495.0f),
	D3DXVECTOR3(1055.0f, 0.0f, -720.0f),
	D3DXVECTOR3(765.0f, 0.0f, -715.0f),
	D3DXVECTOR3(495.0f, 0.0f, -670.0f),
	D3DXVECTOR3(45.0f, 0.0f, -730.0f),
	D3DXVECTOR3(25.0f, 0.0f, -445.0f),
	D3DXVECTOR3(-225.0f, 0.0f, -425.0f),

	D3DXVECTOR3(-710.0f, 0.0f, -420.0f),
	D3DXVECTOR3(-455.0f, 0.0f, -425.0f),
	D3DXVECTOR3(-225.0f, 0.0f, -425.0f),
	D3DXVECTOR3(-225.0f, 0.0f, -35.0f),
	D3DXVECTOR3(-455.0f, 0.0f, -35.0f),
	D3DXVECTOR3(-705.0f, 0.0f, -35.0f),
	D3DXVECTOR3(-1055.0f, 0.0f, -25.0f),
	D3DXVECTOR3(-1015.0f, 0.0f, 260.0f),
	D3DXVECTOR3(-700.0f, 0.0f, 300.0f),
	D3DXVECTOR3(-695.0f, 0.0f, 510.0f),
	D3DXVECTOR3(-415.0f, 0.0f, 510.0f),
	D3DXVECTOR3(-410.0f, 0.0f, 295.0f),
	D3DXVECTOR3(30.0f, 0.0f, 270.0f),
	D3DXVECTOR3(465.0f, 0.0f, 204.0f),
	D3DXVECTOR3(680.0f, 0.0f, 115.0f),
};

// �O���[�o���ϐ�
Enemy g_aEnemy;						// �G���
bool g_bEnd;						// �߂܂�������
bool Inside;						// ���E�ɓ�������
bool isPlayerInSightPrev;
bool isReversePatrol;				// ����̕����ifalse: �����, true: �t���j

int currentPatrolPoint;				// ���݂̏���|�C���g
int g_nIdxShadowEnemy;

//=============================
// �G�̏���������
//=============================
void InitEnemy(void)
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

    //������
    g_aEnemy.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu������������
    g_aEnemy.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O�̈ʒu������������
	g_aEnemy.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    g_aEnemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ�����������
    g_aEnemy.enemymotion.bLoopMotion = true;
    g_aEnemy.enemymotion.nCounterMotion = 0;
	g_aEnemy.RadiusEnemy = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	g_aEnemy.posRadiusEnemy = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	g_aEnemy.state = ENEMYSTATE_PATROLLING;
	g_aEnemy.bUse = false;
	g_aEnemy.sightRange = 310.0f;							//���E����
	g_aEnemy.sightAngle = D3DXToRadian(90.0f);				//���E�͈�
	g_bEnd = false;
	Inside = false;
	isPlayerInSightPrev = false;
	isReversePatrol = false;
	currentPatrolPoint = 0;

	LoadEnemyTEXT();

	//g_nIdxShadowEnemy = SetShadow(D3DXVECTOR3(g_aEnemy.pos.x, g_aEnemy.pos.y, g_aEnemy.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�I�t�Z�b�g�l��
	for (int nCntOff = 0; nCntOff < g_aEnemy.enemymotion.nNumModel; nCntOff++)
	{
		g_aEnemy.enemymotion.aModel[nCntOff].Offpos = g_aEnemy.enemymotion.aModel[nCntOff].pos;
		g_aEnemy.enemymotion.aModel[nCntOff].Offrot = g_aEnemy.enemymotion.aModel[nCntOff].rot;
	}

	for (int nCntVtx = 0; nCntVtx < MAX_PARTS; nCntVtx++)
	{

		int nNumVtx;//���_��
		DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

		//���_���̎擾
		nNumVtx = g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̎擾
		sizeFVF = D3DXGetFVFVertexSize(g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ŏ��l�ő�l���擾
			if (vtx.x < g_aEnemy.vtxMin.x)
			{
				g_aEnemy.vtxMin.x = vtx.x;
			}
			else if (vtx.y < g_aEnemy.vtxMin.y)
			{
				g_aEnemy.vtxMin.y = vtx.y;
			}
			else if (vtx.z < g_aEnemy.vtxMin.z)
			{
				g_aEnemy.vtxMin.z = vtx.z;
			}

			if (vtx.x > g_aEnemy.vtxMax.x)
			{
				g_aEnemy.vtxMax.x = vtx.x;
			}
			else if (vtx.y > g_aEnemy.vtxMax.y)
			{
				g_aEnemy.vtxMax.y = vtx.y;
			}
			else if (vtx.z > g_aEnemy.vtxMax.z)
			{
				g_aEnemy.vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		g_aEnemy.size.x = (g_aEnemy.vtxMax.x - g_aEnemy.vtxMin.x);
		g_aEnemy.size.y = (g_aEnemy.vtxMax.y - g_aEnemy.vtxMin.y);
		g_aEnemy.size.z = (g_aEnemy.vtxMax.z - g_aEnemy.vtxMin.z);

		//���_�o�b�t�@�̃A�����b�N
		g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_aEnemy.enemymotion.aModel[nCntVtx].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aEnemy.enemymotion.aModel[nCntVtx].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���

				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aEnemy.enemymotion.aModel[nCntVtx].apTexture[nCntMat]);

			}
		}

	}

}
//=============================
// �G�̏I������
//=============================
void UninitEnemy(void)
{

	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		for (int nCntMat = 0; nCntMat < (int)g_aEnemy.enemymotion.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			//�e�N�X�`���̔j��
			if (g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat] != NULL)
			{
				g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat]->Release();
				g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_aEnemy.enemymotion.aModel[nCntModel].pMesh != NULL)
		{
			g_aEnemy.enemymotion.aModel[nCntModel].pMesh->Release();
			g_aEnemy.enemymotion.aModel[nCntModel].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat != NULL)
		{
			g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat->Release();
			g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}
//=============================
// �G�̍X�V����
//=============================
void UpdateEnemy(void)
{
	if (g_aEnemy.bUse == true)
	{
		bool isPlayerInSightNow = isPlayerInSight(); // ���݂̎��E����

		// ���E�O���王�E���ɕω������u��
		if (isPlayerInSightNow && !isPlayerInSightPrev)
		{
			// �v���C���[�����E�ɓ������u��
			PlaySound(SOUND_LABEL_INSIGHT); // SE���Đ�
		}
		
		// �t���O���X�V���Ď��̃t���[���ɔ�����
		isPlayerInSightPrev = isPlayerInSightNow;

		Player* pPlayer = GetPlayer();

		//�ړ��ʂ��X�V(����������)
		g_aEnemy.move.x += (0.0f - g_aEnemy.move.x) * 0.25f;
		g_aEnemy.move.z += (0.0f - g_aEnemy.move.z) * 0.25f;
		g_aEnemy.move.y += (0.0f - g_aEnemy.move.y) * 0.1f;

		//�O��̈ʒu���X�V
		g_aEnemy.posOld = g_aEnemy.pos;

		//�ʒu���X�V
		g_aEnemy.pos.x += g_aEnemy.move.x;
		g_aEnemy.pos.z += g_aEnemy.move.z;
		g_aEnemy.pos.y += g_aEnemy.move.y;


		//CollisionModel();

		CollisionBlock(&g_aEnemy.pos,&g_aEnemy.posOld,&g_aEnemy.move,&g_aEnemy.size);


		D3DXVECTOR3 PlayerRadius(20.0f, 20.0f, 20.0f);				// �߂܂鋗��
		D3DXVECTOR3 PlayerInsightRadius(50.0f, 50.0f, 50.0f);		// �o���鋗��
		D3DXVECTOR3 SoundRadius1(500.0f, 500.0f, 500.0f);			// �S���̖鋗��

		float fDistance =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadius =
			(g_aEnemy.RadiusEnemy.x + PlayerRadius.x) * (g_aEnemy.RadiusEnemy.x + PlayerRadius.x) +
			(g_aEnemy.RadiusEnemy.y + PlayerRadius.y) * (g_aEnemy.RadiusEnemy.y + PlayerRadius.y) +
			(g_aEnemy.RadiusEnemy.z + PlayerRadius.z) * (g_aEnemy.RadiusEnemy.z + PlayerRadius.z);

		float fDistance2 =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadius2 =
			(g_aEnemy.RadiusEnemy.x + PlayerInsightRadius.x) * (g_aEnemy.RadiusEnemy.x + PlayerInsightRadius.x) +
			(g_aEnemy.RadiusEnemy.y + PlayerInsightRadius.y) * (g_aEnemy.RadiusEnemy.y + PlayerInsightRadius.y) +
			(g_aEnemy.RadiusEnemy.z + PlayerInsightRadius.z) * (g_aEnemy.RadiusEnemy.z + PlayerInsightRadius.z);

		float fDistanceSound1 =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadiusSound1 =
			(g_aEnemy.RadiusEnemy.x + SoundRadius1.x) * (g_aEnemy.RadiusEnemy.x + SoundRadius1.x) +
			(g_aEnemy.RadiusEnemy.y + SoundRadius1.y) * (g_aEnemy.RadiusEnemy.y + SoundRadius1.y) +
			(g_aEnemy.RadiusEnemy.z + SoundRadius1.z) * (g_aEnemy.RadiusEnemy.z + SoundRadius1.z);

		// �߂܂���
		if (fDistance <= fRadius)
		{
			pPlayer->pos = pPlayer->posOld;
			g_aEnemy.pos = g_aEnemy.posOld;
			g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_ACTION;
			g_bEnd = true;
		}

		// �ǐՃ��[�h�ɂ���
		if (fDistance2 <= fRadius2)
		{
			g_aEnemy.state = ENEMYSTATE_CHASING;
		}

		// �S��1
		if (fDistanceSound1 <= fRadiusSound1)
		{

		}

		D3DXVECTOR3 posPlayerRadius(1.0f, 1.0f, 1.0f);

		float fDistancePlayer =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadiusPlayer =
			(g_aEnemy.posRadiusEnemy.x + posPlayerRadius.x) * (g_aEnemy.posRadiusEnemy.x + posPlayerRadius.x) +
			(g_aEnemy.posRadiusEnemy.y + posPlayerRadius.y) * (g_aEnemy.posRadiusEnemy.y + posPlayerRadius.y) +
			(g_aEnemy.posRadiusEnemy.z + posPlayerRadius.z) * (g_aEnemy.posRadiusEnemy.z + posPlayerRadius.z);


		if (isPlayerInSight())
		{
			Inside = true;
		}
		else
		{
			Inside = false;
		}


		if (g_aEnemy.pos.y <= 0)
		{
			g_aEnemy.pos.y = 0.0f;
		}


		//SetPositionShadow(g_nIdxShadowEnemy, D3DXVECTOR3(g_aEnemy.pos.x, 0.0f, g_aEnemy.pos.z));


		//�G�̑���
		if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_NEUTRAL && g_aEnemy.enemymotion.nKey == 1 && 
			g_aEnemy.enemymotion.nCounterMotion == 9)
		{
			//PlaySound(SOUND_LABEL_STEP1);
		}
		else if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_NEUTRAL && g_aEnemy.enemymotion.nKey == 3 &&
			g_aEnemy.enemymotion.nCounterMotion == 5)
		{
			//PlaySound(SOUND_LABEL_STEP2);
		}

		if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_MOVE && g_aEnemy.enemymotion.nKey == 1 &&
			g_aEnemy.enemymotion.nCounterMotion == 8)
		{
			//PlaySound(SOUND_LABEL_STEP1);
		}
		else if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_MOVE && g_aEnemy.enemymotion.nKey == 3 && 
			g_aEnemy.enemymotion.nCounterMotion == 5)
		{
			//PlaySound(SOUND_LABEL_STEP2);
		}

		//�S���f���̍X�V
		for (int nCntModel = 0; nCntModel < g_aEnemy.enemymotion.nNumModel; nCntModel++)
		{

			int nNextKey = (g_aEnemy.enemymotion.nKey + 1) % g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].nNumKey;

			// ���E�`�F�b�N
			if (g_aEnemy.enemymotion.nKey >= g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].nNumKey ||
				nNextKey >= g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].nNumKey)
			{
				g_aEnemy.enemymotion.nKey = 0;
			}

			D3DXVECTOR3 Mpos, Mrot;
			D3DXVECTOR3 MAnswer, MAnswer2;//�v�Z���ʗp

			//�L�[��񂩂�ʒu�E�������Z�o
			Mpos.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fPosX - 
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosX;
			Mpos.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fPosY -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosY;
			Mpos.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fPosZ -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosZ;

			Mrot.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fRotX -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotX;
			Mrot.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fRotY -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotY;
			Mrot.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fRotZ -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotZ;

			//��ԌW�����v�Z
			float t = (float)g_aEnemy.enemymotion.nCounterMotion / g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].nFrame;

			//���߂�l
			MAnswer.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosX + Mpos.x * t;
			MAnswer.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosY + Mpos.y * t;
			MAnswer.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosZ + Mpos.z * t;

			MAnswer2.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotX + Mrot.x * t;
			MAnswer2.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotY + Mrot.y * t;
			MAnswer2.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotZ + Mrot.z * t;


			//�S�p�[�c�̈ʒu�E������ݒ�
			g_aEnemy.enemymotion.aModel[nCntModel].pos = g_aEnemy.enemymotion.aModel[nCntModel].Offpos + MAnswer;

			g_aEnemy.enemymotion.aModel[nCntModel].rot = g_aEnemy.enemymotion.aModel[nCntModel].Offrot + MAnswer2;

		}

		g_aEnemy.enemymotion.nCounterMotion++;//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�

		if (g_aEnemy.enemymotion.nCounterMotion >= g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].nFrame)
		{
			g_aEnemy.enemymotion.nCounterMotion = 0;

			g_aEnemy.enemymotion.nKey++;
		}

		float moveSpeed           = 0.0f;
		float distanceToTarget	  = 0.0f;
		float angleToTarget       = 0.0f;
		float fAngle              = 0.0f;
		static int lostSightTimer = 0;				// ���E�O�^�C�}�[
		static int patrolTimer    = 0;				// �{���^�C�}�[

		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);

		switch (g_aEnemy.state)
		{
		case ENEMYSTATE_PATROLLING:

			g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_NEUTRAL;

			// ���݂̏���|�C���g�Ɍ�����
			target = patrolPoints[currentPatrolPoint];

			distanceToTarget = sqrtf
			(
				(target.x - g_aEnemy.pos.x) * (target.x - g_aEnemy.pos.x) +
				(target.y - g_aEnemy.pos.y) * (target.y - g_aEnemy.pos.y) +
				(target.z - g_aEnemy.pos.z) * (target.z - g_aEnemy.pos.z)
			);

			if (currentPatrolPoint < 0 || currentPatrolPoint >= sizeof(patrolPoints) / sizeof(patrolPoints[0]))
			{
				currentPatrolPoint = 0; // �͈͊O�A�N�Z�X��h��
			}

			// �߂Â�
			moveSpeed = 0.4f; // ���񑬓x

			if (distanceToTarget > 5.0f)
			{ // ���B����
				angleToTarget	 = atan2f(target.x - g_aEnemy.pos.x, target.z - g_aEnemy.pos.z);
				g_aEnemy.move.x += sinf(angleToTarget) * moveSpeed;
				g_aEnemy.move.z += cosf(angleToTarget) * moveSpeed;

				g_aEnemy.rot.y = angleToTarget + D3DX_PI;
			}
			else
			{
				// ���m���ŋt���ɐ؂�ւ���
				if (rand() % 100 < 25) // 25%�̊m���ŕ�����؂�ւ���
				{
					isReversePatrol = !isReversePatrol;
				}

				// ����|�C���g�̍X�V
				if (isReversePatrol)
				{
					currentPatrolPoint = (currentPatrolPoint - 1 + (sizeof(patrolPoints) / sizeof(patrolPoints[0]))) % (sizeof(patrolPoints) / sizeof(patrolPoints[0]));
				}
				else
				{
					currentPatrolPoint = (currentPatrolPoint + 1) % (sizeof(patrolPoints) / sizeof(patrolPoints[0]));
				}
			}

			// �v���C���[�����E���Ō��o������ǐՂɐ؂�ւ���
			if (isPlayerInSight())
			{
				g_aEnemy.state = ENEMYSTATE_CHASING;
			}

			break;

		case ENEMYSTATE_CHASING:

			fAngle = atan2f(pPlayer->pos.x - g_aEnemy.pos.x, pPlayer->pos.z - g_aEnemy.pos.z);

			g_aEnemy.move.x += sinf(fAngle) * 1.151f;
			g_aEnemy.move.z += cosf(fAngle) * 1.151f;

			g_aEnemy.rot.y = fAngle + D3DX_PI;

			g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_MOVE;


			// �v���C���[�����E�O�ɏo����{����Ԃɐ؂�ւ���
			if (!isPlayerInSight())
			{
				g_aEnemy.state = ENEMYSTATE_SEARCHING; // �{����Ԃ�
			}

			if (!isPlayerInSight())
			{
				lostSightTimer++;

				if (lostSightTimer > 180)
				{ // 180�t���[���o��
					currentPatrolPoint = GetNearestPatrolPoint(g_aEnemy.pos);

					g_aEnemy.state = ENEMYSTATE_PATROLLING;

					lostSightTimer = 0; // �^�C�}�[�����Z�b�g
				}
			}
			else
			{
				lostSightTimer = 0; // ���E���ɖ߂�����^�C�}�[�����Z�b�g
			}

			break;

		case ENEMYSTATE_SEARCHING:

			g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_SEARCH;

			if (isPlayerInSight())
			{
				g_aEnemy.state = ENEMYSTATE_CHASING;
			}

			// ��莞�Ԍo�ߌ㏄��ɖ߂�
			patrolTimer++;

			if (patrolTimer > 180)
			{
				currentPatrolPoint = GetNearestPatrolPoint(g_aEnemy.pos);

				g_aEnemy.state = ENEMYSTATE_PATROLLING;
				patrolTimer = 0;
			}

			break;
		}
	}
}
//=============================
// �G�̕`�揈��
//=============================
void DrawEnemy(void)
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (g_aEnemy.bUse == true)
	{
		//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans, mtxSize;

		D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

		D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aEnemy.mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy.rot.y, g_aEnemy.rot.x, g_aEnemy.rot.z);
		D3DXMatrixMultiply(&g_aEnemy.mtxWorld, &g_aEnemy.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aEnemy.pos.x, g_aEnemy.pos.y, g_aEnemy.pos.z);
		D3DXMatrixMultiply(&g_aEnemy.mtxWorld, &g_aEnemy.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy.mtxWorld);

		//���݂̃}�e���A���̎擾
		pDevice->GetMaterial(&matDef);

		//�S���f��(�p�[�c)�̕`��
		for (int nCntModel = 0; nCntModel < g_aEnemy.enemymotion.nNumModel; nCntModel++)
		{

			D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X

			D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X

			//�p�[�c�̃��[���h�}�g���b�N�X��������
			D3DXMatrixIdentity(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy.enemymotion.aModel[nCntModel].rot.y, g_aEnemy.enemymotion.aModel[nCntModel].rot.x, g_aEnemy.enemymotion.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, g_aEnemy.enemymotion.aModel[nCntModel].pos.x, g_aEnemy.enemymotion.aModel[nCntModel].pos.y, g_aEnemy.enemymotion.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//�p�[�c�̐e�̃}�g���b�N�X��ݒ�
			if (g_aEnemy.enemymotion.aModel[nCntModel].nIdxModelParent != -1)
			{//�e���f��������ꍇ

				mtxParent = g_aEnemy.enemymotion.aModel[g_aEnemy.enemymotion.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//�e���f�����Ȃ��ꍇ

				mtxParent = g_aEnemy.mtxWorld;
			}

			//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
			D3DXMatrixMultiply(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &mtxParent);

			//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aEnemy.enemymotion.aModel[nCntModel].dwNumMat; nCntMat++)
			{

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_aEnemy.enemymotion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);

			}

		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}
//=============================
// �G�̐ݒ菈��
//=============================
void SetEnemy(D3DXVECTOR3 pos)
{
	if (g_aEnemy.bUse == false)
	{
		g_aEnemy.pos = pos;
		g_aEnemy.bUse = true;
	}
}
//============================================
// �G�̎擾
//============================================
Enemy* GetEnemy(void)
{
	return &g_aEnemy;
}
//=============================
// ���E������
//=============================
bool isPlayerInSight(void) 
{
	Player* pPlayer = GetPlayer();

	// �G�̐��ʃx�N�g�����v�Z
	D3DXVECTOR3 enemyFront;

	enemyFront.x = -sinf(g_aEnemy.rot.y);
	enemyFront.y = 0.0f;
	enemyFront.z = -cosf(g_aEnemy.rot.y);

	// �v���C���[�Ƃ̕����x�N�g��
	D3DXVECTOR3 toPlayer;

	toPlayer.x = pPlayer->pos.x - g_aEnemy.pos.x;
	toPlayer.y = 0.0f;
	toPlayer.z = pPlayer->pos.z - g_aEnemy.pos.z;

	// �v���C���[�����x�N�g���𐳋K��
	D3DXVec3Normalize(&toPlayer, &toPlayer);

	// �G�̐��ʃx�N�g�������K��
	D3DXVec3Normalize(&enemyFront, &enemyFront);

	// �x�N�g���̓��ς��v�Z
	float dotProduct = D3DXVec3Dot(&enemyFront, &toPlayer);

	// ���ς��王���������(0.5f�͂������l)
	if (dotProduct > cosf(g_aEnemy.sightAngle * 0.5f)) // ����p�̔����Ŕ��� 1 �� ���S�ɓ��������i���ʁj0 �� ���p�i�^���j- 1 �� �^�t�i�w��j
	{
		// �v���C���[�Ƃ̋������v�Z
		float distanceSquared =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		if (distanceSquared <= g_aEnemy.sightRange * g_aEnemy.sightRange)
		{
			return true; // �v���C���[�͎��E��
		}
	}

	return false; // ���E�O
}
//======================================================
// ��ԋ߂�����|�C���g�̎Z�o����
//======================================================
int GetNearestPatrolPoint(D3DXVECTOR3 currentPos) 
{
	float minDistance = FLT_MAX; // ���ɑ傫�Ȓl�ŏ�����
	int nearestPoint = 0;

	for (int nCnt = 0; nCnt < sizeof(patrolPoints) / sizeof(patrolPoints[0]); nCnt++)
	{
		float distance = sqrtf
		(
			(patrolPoints[nCnt].x - currentPos.x) * (patrolPoints[nCnt].x - currentPos.x) +
			(patrolPoints[nCnt].y - currentPos.y) * (patrolPoints[nCnt].y - currentPos.y) +
			(patrolPoints[nCnt].z - currentPos.z) * (patrolPoints[nCnt].z - currentPos.z)
		);

		if (distance < minDistance) 
		{
			minDistance = distance;
			nearestPoint = nCnt;
		}
	}

	return nearestPoint; // �ł��߂�����|�C���g�̃C���f�b�N�X��Ԃ�
}
//======================================================
// �߂܂�������
//======================================================
bool GetEnd(void)
{
	return g_bEnd;
}
//======================================================
// ���E�ɓ�����������
//======================================================
bool GetInside(void)
{
	return Inside;
}