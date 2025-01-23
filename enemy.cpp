//=======================================
//
//�G�̏���[enemy.cpp]
//Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "fade.h"
#include "block.h"
//#include "sound.h"
//#include "shadow.h"
//#include "billboard.h"

// ����|�C���g�z��
D3DXVECTOR3 patrolPoints[] =
{//�����̃|�C���g

	D3DXVECTOR3(280.0f, 0.0f, 270.0f),		// �E��̃|�C���g
	D3DXVECTOR3(-260.0f, 0.0f, 270.0f),		// ����̃|�C���g
	D3DXVECTOR3(-260.0f, 0.0f, -300.0f),	// �����̃|�C���g
	D3DXVECTOR3(270.0f, 0.0f, -300.0f)		// �E���̃|�C���g

};

//�O���[�o���ϐ�
Enemy g_aEnemy;						//�G���
bool g_bEnd;						//�߂܂�������
bool Inside;						//���E�ɓ�������
bool isPlayerInSightPrev = false;
bool isReversePatrol = false;		// ����̕����ifalse: �����, true: �t���j

int currentPatrolPoint = 0;			// ���݂̏���|�C���g
int g_nIdxShadowEnemy;

//=============================
//�G�̏���������
//=============================
void InitEnemy(void)
{

    LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

    //�f�o�C�X�̎擾
    pDevice = GetDevice();


    //������
    g_aEnemy.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu������������
    g_aEnemy.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O�̈ʒu������������
	g_aEnemy.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    g_aEnemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ�����������
    g_aEnemy.motion.bLoopMotion = true;
    g_aEnemy.motion.nCounterMotion = 0;
	g_aEnemy.RadiusEnemy = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	g_aEnemy.posRadiusEnemy = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	g_aEnemy.state = ENEMYSTATE_PATROLLING;
	g_aEnemy.bUse = false;
	g_aEnemy.sightRange = 165.0f;							//���E����
	g_aEnemy.sightAngle = D3DXToRadian(110.0f);				//���E�͈�
	g_bEnd = false;
	Inside = false;
	currentPatrolPoint = 0;

	LoadEnemyTEXT();

	//g_nIdxShadowEnemy = SetShadow(D3DXVECTOR3(g_aEnemy.pos.x, g_aEnemy.pos.y, g_aEnemy.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�I�t�Z�b�g�l��
	for (int nCntOff = 0; nCntOff < g_aEnemy.motion.nNumModel; nCntOff++)
	{
		g_aEnemy.motion.aModel[nCntOff].Offpos = g_aEnemy.motion.aModel[nCntOff].pos;
		g_aEnemy.motion.aModel[nCntOff].Offrot = g_aEnemy.motion.aModel[nCntOff].rot;
	}

	for (int nCntVtx = 0; nCntVtx < MAX_PARTS; nCntVtx++)
	{

		int nNumVtx;//���_��
		DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

		//���_���̎擾
		nNumVtx = g_aEnemy.motion.aModel[nCntVtx].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̎擾
		sizeFVF = D3DXGetFVFVertexSize(g_aEnemy.motion.aModel[nCntVtx].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aEnemy.motion.aModel[nCntVtx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

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
		g_aEnemy.motion.aModel[nCntVtx].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_aEnemy.motion.aModel[nCntVtx].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aEnemy.motion.aModel[nCntVtx].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���

				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aEnemy.motion.aModel[nCntVtx].apTexture[nCntMat]);

			}
		}

	}

}
//=============================
//�G�̏I������
//=============================
void UninitEnemy(void)
{
	//StopSound(SOUND_LABEL_DENKI);
	//StopSound(SOUND_LABEL_STEP1);
	//StopSound(SOUND_LABEL_STEP2);

	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		for (int nCntMat = 0; nCntMat < (int)g_aEnemy.motion.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			//�e�N�X�`���̔j��
			if (g_aEnemy.motion.aModel[nCntModel].apTexture[nCntMat] != NULL)
			{
				g_aEnemy.motion.aModel[nCntModel].apTexture[nCntMat]->Release();
				g_aEnemy.motion.aModel[nCntModel].apTexture[nCntMat] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_aEnemy.motion.aModel[nCntModel].pMesh != NULL)
		{
			g_aEnemy.motion.aModel[nCntModel].pMesh->Release();
			g_aEnemy.motion.aModel[nCntModel].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_aEnemy.motion.aModel[nCntModel].pBuffMat != NULL)
		{
			g_aEnemy.motion.aModel[nCntModel].pBuffMat->Release();
			g_aEnemy.motion.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}
//=============================
//�G�̍X�V����
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
			//PlaySound(SOUND_LABEL_WARNING); // SE���Đ�
			SetFoundFade(MODE_FOUND);
		}

		// �t���O���X�V���Ď��̃t���[���ɔ�����
		isPlayerInSightPrev = isPlayerInSightNow;

		Player* pPlayer = GetPlayer();


		//�ړ��ʂ��X�V(����������)
		g_aEnemy.move.x += (0.0f - g_aEnemy.move.x) * 0.3f;
		g_aEnemy.move.z += (0.0f - g_aEnemy.move.z) * 0.3f;
		g_aEnemy.move.y += (0.0f - g_aEnemy.move.y) * 0.1f;

		//�O��̈ʒu���X�V
		g_aEnemy.posOld = g_aEnemy.pos;

		//�ʒu���X�V
		g_aEnemy.pos.x += g_aEnemy.move.x;
		g_aEnemy.pos.z += g_aEnemy.move.z;
		g_aEnemy.pos.y += g_aEnemy.move.y;


		//CollisionModel();

		CollisionBlock(&g_aEnemy.pos,&g_aEnemy.posOld,&g_aEnemy.move,&g_aEnemy.size);


		D3DXVECTOR3 PlayerRadius(12.0f, 12.0f, 12.0f);

		float fDistance =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadius =
			(g_aEnemy.RadiusEnemy.x + PlayerRadius.x) * (g_aEnemy.RadiusEnemy.x + PlayerRadius.x) +
			(g_aEnemy.RadiusEnemy.y + PlayerRadius.y) * (g_aEnemy.RadiusEnemy.y + PlayerRadius.y) +
			(g_aEnemy.RadiusEnemy.z + PlayerRadius.z) * (g_aEnemy.RadiusEnemy.z + PlayerRadius.z);


		if (fDistance <= fRadius)
		{
			pPlayer->pos = pPlayer->posOld;
			g_aEnemy.pos = g_aEnemy.posOld;
			g_aEnemy.motion.motionType = MOTIONTYPE_NEUTRAL2;
			g_bEnd = true;
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


		//�͈͓��ɓ�����
		if (fDistancePlayer <= fRadiusPlayer)
		{
			g_aEnemy.state = ENEMYSTATE_CHASING;
		}

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
		if (g_aEnemy.motion.motionType == MOTIONTYPE_NEUTRAL && g_aEnemy.motion.nKey == 1 && g_aEnemy.motion.nCounterMotion == 9)
		{
			//PlaySound(SOUND_LABEL_STEP1);
		}
		else if (g_aEnemy.motion.motionType == MOTIONTYPE_NEUTRAL && g_aEnemy.motion.nKey == 3 && g_aEnemy.motion.nCounterMotion == 5)
		{
			//PlaySound(SOUND_LABEL_STEP2);
		}

		if (g_aEnemy.motion.motionType == MOTIONTYPE_MOVE && g_aEnemy.motion.nKey == 1 && g_aEnemy.motion.nCounterMotion == 8)
		{
			//PlaySound(SOUND_LABEL_STEP1);
		}
		else if (g_aEnemy.motion.motionType == MOTIONTYPE_MOVE && g_aEnemy.motion.nKey == 3 && g_aEnemy.motion.nCounterMotion == 5)
		{
			//PlaySound(SOUND_LABEL_STEP2);
		}

		//�S���f���̍X�V
		for (int nCntModel = 0; nCntModel < g_aEnemy.motion.nNumModel; nCntModel++)
		{

			int nNextKey = (g_aEnemy.motion.nKey + 1) % g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].nNumKey;

			// ���E�`�F�b�N
			if (g_aEnemy.motion.nKey >= g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].nNumKey ||
				nNextKey >= g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].nNumKey)
			{
				g_aEnemy.motion.nKey = 0;
			}

			D3DXVECTOR3 Mpos, Mrot;
			D3DXVECTOR3 MAnswer, MAnswer2;//�v�Z���ʗp

			//�L�[��񂩂�ʒu�E�������Z�o
			Mpos.x = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosX - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosX;
			Mpos.y = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosY - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosY;
			Mpos.z = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosZ - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosZ;

			Mrot.x = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotX - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotX;
			Mrot.y = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotY - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotY;
			Mrot.z = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotZ - g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotZ;

			//��ԌW�����v�Z
			float t = (float)g_aEnemy.motion.nCounterMotion / g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].nFrame;

			//���߂�l
			MAnswer.x = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosX + Mpos.x * t;
			MAnswer.y = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosY + Mpos.y * t;
			MAnswer.z = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fPosZ + Mpos.z * t;

			MAnswer2.x = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotX + Mrot.x * t;
			MAnswer2.y = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotY + Mrot.y * t;
			MAnswer2.z = g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].aKey[nCntModel].fRotZ + Mrot.z * t;


			//�S�p�[�c�̈ʒu�E������ݒ�
			g_aEnemy.motion.aModel[nCntModel].pos = g_aEnemy.motion.aModel[nCntModel].Offpos + MAnswer;

			g_aEnemy.motion.aModel[nCntModel].rot = g_aEnemy.motion.aModel[nCntModel].Offrot + MAnswer2;

		}

		g_aEnemy.motion.nCounterMotion++;//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�

		if (g_aEnemy.motion.nCounterMotion >= g_aEnemy.motion.aMotionInfo[g_aEnemy.motion.motionType].aKeyInfo[g_aEnemy.motion.nKey].nFrame)
		{
			g_aEnemy.motion.nCounterMotion = 0;

			g_aEnemy.motion.nKey++;
		}

		float moveSpeed = 0.0f;
		static int lostSightTimer = 0;			// ���E�O�^�C�}�[
		float distanceToTarget = 0.0f;
		float angleToTarget = 0.0f;
		float fAngle = 0.0f;

		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		static int patrolTimer = 0;				// �{���^�C�}�[

		switch (g_aEnemy.state)
		{
		case ENEMYSTATE_PATROLLING:

			g_aEnemy.motion.motionType = MOTIONTYPE_NEUTRAL;

			// ���݂̏���|�C���g�Ɍ�����
			target = patrolPoints[currentPatrolPoint];

			distanceToTarget = sqrt
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
				angleToTarget = atan2f(target.x - g_aEnemy.pos.x, target.z - g_aEnemy.pos.z);
				g_aEnemy.move.x += sinf(angleToTarget) * moveSpeed;
				g_aEnemy.move.z += cosf(angleToTarget) * moveSpeed;

				g_aEnemy.rot.y = angleToTarget + D3DX_PI;
			}
			else
			{
				// ���m���ŋt���ɐ؂�ւ���
				if (rand() % 100 < 30) // 30%�̊m���ŕ�����؂�ւ���
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

			g_aEnemy.move.x += sinf(fAngle) * 1.15f;
			g_aEnemy.move.z += cosf(fAngle) * 1.15f;

			g_aEnemy.rot.y = fAngle + D3DX_PI;

			g_aEnemy.motion.motionType = MOTIONTYPE_MOVE;


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

			g_aEnemy.motion.motionType = MOTIONTYPE_ACTION;

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

		case ENEMYSTATE_IDLE:

			break;
		}
	}
}
//=============================
//�G�̕`�揈��
//=============================
void DrawEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

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
		for (int nCntModel = 0; nCntModel < g_aEnemy.motion.nNumModel; nCntModel++)
		{

			D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X

			D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X

			//�p�[�c�̃��[���h�}�g���b�N�X��������
			D3DXMatrixIdentity(&g_aEnemy.motion.aModel[nCntModel].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy.motion.aModel[nCntModel].rot.y, g_aEnemy.motion.aModel[nCntModel].rot.x, g_aEnemy.motion.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aEnemy.motion.aModel[nCntModel].mtxWorld, &g_aEnemy.motion.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, g_aEnemy.motion.aModel[nCntModel].pos.x, g_aEnemy.motion.aModel[nCntModel].pos.y, g_aEnemy.motion.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aEnemy.motion.aModel[nCntModel].mtxWorld, &g_aEnemy.motion.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//�p�[�c�̐e�̃}�g���b�N�X��ݒ�
			if (g_aEnemy.motion.aModel[nCntModel].nIdxModelParent != -1)
			{//�e���f��������ꍇ

				mtxParent = g_aEnemy.motion.aModel[g_aEnemy.motion.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//�e���f�����Ȃ��ꍇ

				mtxParent = g_aEnemy.mtxWorld;
			}

			//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
			D3DXMatrixMultiply(&g_aEnemy.motion.aModel[nCntModel].mtxWorld, &g_aEnemy.motion.aModel[nCntModel].mtxWorld, &mtxParent);

			//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy.motion.aModel[nCntModel].mtxWorld);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aEnemy.motion.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aEnemy.motion.aModel[nCntModel].dwNumMat; nCntMat++)
			{

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_aEnemy.motion.aModel[nCntModel].apTexture[nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_aEnemy.motion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);

			}

		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}
//=============================
//�G�̐ݒ菈��
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
//�G�̎擾
//============================================
Enemy* GetEnemy(void)
{
	return &g_aEnemy;
}
//=============================
//���E������
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

	// ���ς��王���������
	if (dotProduct > cosf(g_aEnemy.sightAngle * 0.5f)) // ����p�̔����Ŕ���
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
//��ԋ߂�����|�C���g�̎Z�o����
//======================================================
int GetNearestPatrolPoint(D3DXVECTOR3 currentPos) 
{
	float minDistance = FLT_MAX; // ���ɑ傫�Ȓl�ŏ�����
	int nearestPoint = 0;

	for (int i = 0; i < sizeof(patrolPoints) / sizeof(patrolPoints[0]); i++) 
	{
		float distance = sqrt(
			(patrolPoints[i].x - currentPos.x) * (patrolPoints[i].x - currentPos.x) +
			(patrolPoints[i].y - currentPos.y) * (patrolPoints[i].y - currentPos.y) +
			(patrolPoints[i].z - currentPos.z) * (patrolPoints[i].z - currentPos.z)
		);

		if (distance < minDistance) 
		{
			minDistance = distance;
			nearestPoint = i;
		}
	}

	return nearestPoint; // �ł��߂�����|�C���g�̃C���f�b�N�X��Ԃ�
}
//======================================================
//�߂܂�������
//======================================================
bool GetEnd(void)
{
	return g_bEnd;
}
//======================================================
//���E�ɓ�����������
//======================================================
bool GetInside(void)
{
	return Inside;
}