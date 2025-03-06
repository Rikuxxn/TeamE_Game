//=======================================
//
// �v���C���[���� [player.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "model.h"
#include "motion.h"

#include <stdio.h>
#include <string.h>
#include "enemy.h"
#include "block.h"
#include "light.h"
#include "sound.h"
#include "game.h"

//�O���[�o���ϐ�
Player g_player;			//�v���C���[�̏��
int g_nIdxShadow;
int g_nCntMotion;
int g_nMotion;				//���[�V�����Z�b�g���Ǘ�
bool g_bFinishMotion;		//���[�V�����Z�b�g���I�������

//=============================
// �v���C���[�̏���������
//=============================
void InitPlayer(void)
{

	MODE pMode = GetMode();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//������
	g_player.pos = D3DXVECTOR3(120.0f, 0.0f, -540.0f);			// �ʒu������������
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �O�̈ʒu������������
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ��ʂ�����������
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����������������
	g_player.rotDestPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����������������
	g_player.fDush = PLAYER_STAMINA;							// �_�b�V�����̑��x
	g_player.nDrawDush = 0;										// �_�b�V���Q�[�W�`��p
	g_player.state = PLAYERSTATE_NORMAL;						// �v���C���[�̏��
	g_player.bDush = false;										// �_�b�V�����Ă��邩
	g_player.bDisp = true;										// �v���C���[�̕`��
	g_player.bEmpty = false;									// �_�b�V���ł��邩
	g_player.bDrawDush = false;									// �_�b�V���Q�[�W�`��p
	g_player.motion.bLoopMotion = true;							// ���[�V���������[�v�����邩
	g_player.motion.nCounterMotion = 0;							// ���[�V�����p�̃J�E���^�[
	g_player.motion.aMotionInfo[MOTIONTYPE_MOVE].startKey = 1;	// ���[�V�����̍ŏ��̃L�[
	//g_player.pos = D3DXVECTOR3(120.0f, 0.0f, 540.0f);			// �f�o�b�O�p
	g_player.bEmptySound = false;
	g_player.bDushSound = false;

	// �v���C���[�̓ǂݍ���
	LoadPlayerTEXT();

	//// �e�̐ݒ�
	//g_nIdxShadow = SetShadow(D3DXVECTOR3(g_player.pos.x, g_player.pos.y, g_player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�I�t�Z�b�g�l��
	for (int nCntOff = 0; nCntOff < g_player.motion.nNumModel; nCntOff++)
	{
		g_player.motion.aModel[nCntOff].Offpos = g_player.motion.aModel[nCntOff].pos;
		g_player.motion.aModel[nCntOff].Offrot = g_player.motion.aModel[nCntOff].rot;
	}

	for (int nCntVtx = 0; nCntVtx < MAX_PARTS; nCntVtx++)
	{

		int nNumVtx;	//���_��
		DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

		//���_���̎擾
		nNumVtx = g_player.motion.aModel[nCntVtx].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̎擾
		sizeFVF = D3DXGetFVFVertexSize(g_player.motion.aModel[nCntVtx].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_player.motion.aModel[nCntVtx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ŏ��l�ő�l���擾
			if (vtx.x < g_player.vtxMin.x)
			{
				g_player.vtxMin.x = vtx.x;
			}
			else if (vtx.y < g_player.vtxMin.y)
			{
				g_player.vtxMin.y = vtx.y;
			}
			else if (vtx.z < g_player.vtxMin.z)
			{
				g_player.vtxMin.z = vtx.z;
			}

			if (vtx.x > g_player.vtxMax.x)
			{
				g_player.vtxMax.x = vtx.x;
			}
			else if (vtx.y > g_player.vtxMax.y)
			{
				g_player.vtxMax.y = vtx.y;
			}
			else if (vtx.z > g_player.vtxMax.z)
			{
				g_player.vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		g_player.size.x = (g_player.vtxMax.x - g_player.vtxMin.x);
		g_player.size.y = (g_player.vtxMax.y - g_player.vtxMin.y);
		g_player.size.z = (g_player.vtxMax.z - g_player.vtxMin.z);

		//���_�o�b�t�@�̃A�����b�N
		g_player.motion.aModel[nCntVtx].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.motion.aModel[nCntVtx].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.motion.aModel[nCntVtx].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���

				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_player.motion.aModel[nCntVtx].apTexture[nCntMat]);

			}
		}
	}
}
//=============================
// �v���C���[�̏I������
//=============================
void UninitPlayer(void)
{
	StopSound(SOUND_LABEL_PLAYERSTEP1);
	StopSound(SOUND_LABEL_PLAYERSTEP2);

	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		for (int nCntMat = 0; nCntMat < (int)g_player.motion.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			//�e�N�X�`���̔j��
			if (g_player.motion.aModel[nCntModel].apTexture[nCntMat] != NULL)
			{
				g_player.motion.aModel[nCntModel].apTexture[nCntMat]->Release();
				g_player.motion.aModel[nCntModel].apTexture[nCntMat] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_player.motion.aModel[nCntModel].pMesh != NULL)
		{
			g_player.motion.aModel[nCntModel].pMesh->Release();
			g_player.motion.aModel[nCntModel].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_player.motion.aModel[nCntModel].pBuffMat != NULL)
		{
			g_player.motion.aModel[nCntModel].pBuffMat->Release();
			g_player.motion.aModel[nCntModel].pBuffMat = NULL;
		}

	}

}
//=============================
// �v���C���[�̍X�V����
//=============================
void UpdatePlayer(void)
{
	MODE pMode = GetMode();

	XINPUT_STATE* pStick = GetJoyStickAngle();
	Block* pBlock = GetBlock();
	Camera* pCamera = GetCamera();
	GAME* pGame = GetGame();
	Flags* pFlag = GetFlag();

	bool bEnd = GetEnd();

	g_player.motion.motionType = MOTIONTYPE_NEUTRAL;

	if (bEnd == true)
	{
		g_player.motion.motionType = MOTIONTYPE_NEUTRAL;
	}

	if (pFlag->bExit == false && g_player.bDisp == true && bEnd == false && pGame->bDraw == false &&
		pGame->bDraw2 == false && pGame->bDraw3 == false && pGame->bDraw4 == false && pGame->bBallHint == false && 
		pGame->bCraneHint == false && pGame->bMap == false)
	{

		// ��l�� �Q�[���p�b�h�̈ړ�����
		if (GetJoyStick() == true)
		{
			// ���X�e�B�b�N�̓��͂��擾
			float stickX = pStick->Gamepad.sThumbLX;
			float stickY = pStick->Gamepad.sThumbLY;

			// �f�b�h�]�[������
			const float DEADZONE = 10922.0f;

			if (fabsf(stickX) < DEADZONE)
			{
				stickX = 0.0f;
			}
			if (fabsf(stickY) < DEADZONE)
			{
				stickY = 0.0f;
			}

			// ���K��
			float magnitude = sqrtf(stickX * stickX + stickY * stickY);
			if (magnitude > 0.0f)
			{
				stickX /= magnitude;
				stickY /= magnitude;
			}

			// �J�����̉�]���擾
			float cameraYaw = pCamera->rot.y;

			// �ړ��x�N�g���v�Z
			float moveX = -(stickX * cosf(cameraYaw) + stickY * sinf(cameraYaw));
			float moveZ = stickX * sinf(-cameraYaw) + stickY * cosf(cameraYaw);

			// �ړ��������]
			moveZ = -moveZ;

			// �v���C���[�̈ړ��X�V
			g_player.move.x += moveX * PLAYER_SPEED;
			g_player.move.z += moveZ * PLAYER_SPEED;

			// �v���C���[�̌������X�V
			g_player.rotDestPlayer.y = atan2f(-moveX, -moveZ);

			g_player.motion.motionType = MOTIONTYPE_MOVE;
		}

		if (GetKeyboardPress(DIK_A) == true /*|| GetJoypadPress(JOYKEY_LEFT) == true*/)
		{//A�L�[�������ꂽ

			if (GetKeyboardPress(DIK_W) == true /*|| GetJoypadPress(JOYKEY_UP) == true*/)
			{//W�L�[�������ꂽ
				if ((GetKeyboardPress(DIK_LSHIFT) == true/* || GetJoypadPress(JOYKEY_RB) == true*/ )&& g_player.fDush >= 0 &&
					g_player.fDush > 0 && g_player.bEmpty == false)
				{// �_�b�V����
					g_player.fDush--;
					g_player.bDush = true;
					g_player.nDrawDush = 0;
					g_player.bDrawDush = true;
					//�_�b�V�����̈ړ��ʂ��X�V(����������)
					g_player.move.x -= sinf(pCamera->rot.y + -D3DX_PI * 0.25f) * PLAYER_DUSHSPEED;
					g_player.move.z -= cosf(pCamera->rot.y + -D3DX_PI * 0.25f) * PLAYER_DUSHSPEED;

					g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.75f;

					g_player.motion.motionType = MOTIONTYPE_MOVE;
				}
				else				
				{
					//�������̈ړ��ʂ��X�V(����������)
					g_player.move.x -= sinf(pCamera->rot.y + -D3DX_PI * 0.25f) * PLAYER_SPEED;
					g_player.move.z -= cosf(pCamera->rot.y + -D3DX_PI * 0.25f) * PLAYER_SPEED;

					g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.75f;

					g_player.motion.motionType = MOTIONTYPE_MOVE;
				}

			}
			else if (GetKeyboardPress(DIK_S) == true /*|| GetJoypadPress(JOYKEY_DOWN) == true*/)
			{//S�L�[�������ꂽ

				//�ړ��ʂ��X�V(����������)
				g_player.move.x -= sinf(pCamera->rot.y + -D3DX_PI * 0.75f) * PLAYER_SPEED;
				g_player.move.z -= cosf(pCamera->rot.y + -D3DX_PI * 0.75f) * PLAYER_SPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.25f;

				g_player.motion.motionType = MOTIONTYPE_MOVE;

			}
			else
			{

				//�ړ��ʂ��X�V(����������)
				g_player.move.z -= sinf(pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.x += cosf(pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.5f;

				g_player.motion.motionType = MOTIONTYPE_MOVE;

			}

		}
		else if (GetKeyboardPress(DIK_D) == true /*|| GetJoypadPress(JOYKEY_RIGHT) == true*/)
		{//D�L�[�������ꂽ

			if (GetKeyboardPress(DIK_W) == true /*|| GetJoypadPress(JOYKEY_UP) == true*/)
			{//W�L�[�������ꂽ
				// �_�b�V����
				if ((GetKeyboardPress(DIK_LSHIFT) == true /*|| GetJoypadPress(JOYKEY_RB) == true*/) && g_player.fDush >= 0 &&
					g_player.fDush > 0 && g_player.bEmpty == false)
				{
					g_player.fDush--;
					g_player.bDush = true;
					g_player.nDrawDush = 0;
					g_player.bDrawDush = true;
					//�_�b�V���̈ړ��ʂ��X�V(����������)
					g_player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_DUSHSPEED;
					g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_DUSHSPEED;

					g_player.rotDestPlayer.y = pCamera->rot.y + (-D3DX_PI * 0.75f);

					g_player.motion.motionType = MOTIONTYPE_MOVE;
				}
				else
				{
					//�������̈ړ��ʂ��X�V(����������)
					g_player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_SPEED;
					g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_SPEED;

					g_player.rotDestPlayer.y = pCamera->rot.y + (-D3DX_PI * 0.75f);

					g_player.motion.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetKeyboardPress(DIK_S) == true /*|| GetJoypadPress(JOYKEY_DOWN) == true*/)
			{//S�L�[�������ꂽ

				//�ړ��ʂ��X�V(����������)
				g_player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.75f) * PLAYER_SPEED;
				g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.75f) * PLAYER_SPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + (-D3DX_PI * 0.25f);

				g_player.motion.motionType = MOTIONTYPE_MOVE;

			}
			else
			{

				//�ړ��ʂ��X�V(����������)
				g_player.move.z += sinf(pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.x -= cosf(pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + -D3DX_PI * 0.5f;

				g_player.motion.motionType = MOTIONTYPE_MOVE;

			}

		}
		else if (GetKeyboardPress(DIK_W) == true /*|| GetJoypadPress(JOYKEY_UP) == true*/)
		{//W�L�[�������ꂽ	
			// �_�b�V����
			if ((GetKeyboardPress(DIK_LSHIFT) == true /*|| GetJoypadPress(JOYKEY_RB) == true*/) && g_player.fDush >= 0 &&
				g_player.fDush > 0 && g_player.bEmpty == false)
			{
				g_player.fDush--;
				g_player.bDush = true;
				g_player.nDrawDush = 0;
				g_player.bDrawDush = true;
				if (g_player.bDushSound == false)
				{
					//PlaySound(SOUND_LABEL_EMPTYBREATH);
					g_player.bDushSound = true;
				}

				//�_�b�V���̈ړ��ʂ��X�V(����������)
				g_player.move.x -= sinf(pCamera->rot.y) * PLAYER_DUSHSPEED;
				g_player.move.z -= cosf(pCamera->rot.y) * PLAYER_DUSHSPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI;

				g_player.motion.motionType = MOTIONTYPE_MOVE;
			}
			else
			{
				//�������̈ړ��ʂ��X�V(����������)
				g_player.move.x -= sinf(pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf(pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI;
				g_player.bDushSound = false;

				g_player.motion.motionType = MOTIONTYPE_MOVE;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true /*|| GetJoypadPress(JOYKEY_DOWN) == true*/)
		{//S�L�[�������ꂽ

			//�ړ��ʂ��X�V(����������)
			g_player.move.x += sinf(pCamera->rot.y) * PLAYER_SPEED;
			g_player.move.z += cosf(pCamera->rot.y) * PLAYER_SPEED;

			g_player.rotDestPlayer.y = pCamera->rot.y;

			g_player.motion.motionType = MOTIONTYPE_MOVE;

		}

		if (g_player.fDush <= 0)
		{//���؂�
			g_player.bEmpty = true;
			g_player.bDush = false;
			g_player.bEmptySound = true;
		}

		if (g_player.bEmpty == true &&
			g_player.bEmptySound == true)
		{//���؂ꎞ�̃T�E���h
			PlaySound(SOUND_LABEL_EMPTYBREATH);
			g_player.bEmptySound = false;
		}

		//�_�b�V�����Ă��Ȃ���
		if ((GetKeyboardPress(DIK_LSHIFT) == false /*|| GetJoypadPress(JOYKEY_RB) == false*/))
		{
			g_player.bDush = false;
		}

		if (g_player.fDush >= PLAYER_STAMINA &&
			(GetKeyboardPress(DIK_LSHIFT) == false /*|| GetJoypadPress(JOYKEY_RB) == false*/))
		{
			g_player.nDrawDush++;
		}

		if (g_player.nDrawDush >= 60)
		{
			g_player.nDrawDush = 0;
			g_player.bDrawDush = false;
		}

		//�d�͉��Z
		g_player.move.y -= MAX_GRAVITY;

		//�����̐��K��
		if (g_player.rotDestPlayer.y - g_player.rot.y > D3DX_PI)
		{
			g_player.rot.y += D3DX_PI * 2.0f;
		}
		else if (g_player.rotDestPlayer.y - g_player.rot.y < -D3DX_PI)
		{
			g_player.rot.y -= D3DX_PI * 2.0f;
		}


		g_player.rot.y += (g_player.rotDestPlayer.y - g_player.rot.y) * 0.2f;


		//�O��̈ʒu���X�V
		g_player.posOld = g_player.pos;


		//�ʒu���X�V
		g_player.pos.x += g_player.move.x;
		CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.size);

		g_player.pos.y += g_player.move.y;
		CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.size);

		g_player.pos.z += g_player.move.z;
		CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.size);

	}

	if (g_player.bDush == false || GetKeyboardPress(DIK_W) == false)
	{//�X�^�~�i��
		if (g_player.fDush <= PLAYER_STAMINA)
		{
			g_player.fDush += STAMINA_RECOVERY;
		}
		else if (g_player.fDush >= PLAYER_STAMINA)
		{
			g_player.fDush += 0;
			g_player.bEmpty = false;
		}
	}

	// �J�����̉�]�p�iYaw, Pitch�j���擾
	float yaw = pCamera->rot.y;   // ������]
	float pitch = pCamera->rot.x; // ������]

	// ���������iforward�j���v�Z
	g_player.forward.x = -sinf(yaw) * cosf(pitch);
	g_player.forward.y = -sinf(pitch);
	g_player.forward.z = -cosf(yaw) * cosf(pitch);

	// ���������𐳋K��
	D3DXVec3Normalize(&g_player.forward, &g_player.forward);
	
	if (g_player.pos.y <= 0)
	{
		g_player.pos.y = 0.0f;
	}

	//�ړ��ʂ��X�V(����������)
	g_player.move.x += (0.0f - g_player.move.x) * 0.3f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.3f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.1f;

	if (g_player.bDush == true)
	{// �����Ă���Ƃ�
		if (g_player.motion.motionType == MOTIONTYPE_MOVE && g_player.motion.nKey == 1 && g_player.motion.nCounterMotion == 9)
		{
			PlaySound(SOUND_LABEL_PLAYERSTEP1);
			//PlaySound3D(SOUND_LABEL_PLAYERSTEP1);
		}
		else if (g_player.motion.motionType == MOTIONTYPE_MOVE && g_player.motion.nKey == 3 && g_player.motion.nCounterMotion == 5)
		{
			PlaySound(SOUND_LABEL_PLAYERSTEP2);
			//PlaySound3D(SOUND_LABEL_PLAYERSTEP2);
		}
	}
	else
	{// �����Ă���Ƃ�
		if (g_player.motion.motionType == MOTIONTYPE_MOVE && g_player.motion.nKey == 1 && g_player.motion.nCounterMotion == 9)
		{
			PlaySound(SOUND_LABEL_PLAYERSTEP1);
			//PlaySound3D(SOUND_LABEL_PLAYERSTEP1);
		}
		else if (g_player.motion.motionType == MOTIONTYPE_MOVE && g_player.motion.nKey == 3 && g_player.motion.nCounterMotion == 12)
		{
			PlaySound(SOUND_LABEL_PLAYERSTEP2);
			//PlaySound3D(SOUND_LABEL_PLAYERSTEP2);
		}
	}


	//// �e��pos�ݒ�
	//SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_player.pos.x, 0.0f, g_player.pos.z));


	//�S���f���̍X�V
	for (int nCntModel = 0; nCntModel < g_player.motion.nNumModel; nCntModel++)
	{

		int nNextKey = (g_player.motion.nKey + 1) % g_player.motion.aMotionInfo[g_player.motion.motionType].nNumKey;

		// ���E�`�F�b�N
		if (g_player.motion.nKey >= g_player.motion.aMotionInfo[g_player.motion.motionType].nNumKey || nNextKey >= g_player.motion.aMotionInfo[g_player.motion.motionType].nNumKey)
		{
			g_player.motion.nKey = 0;
		}

		D3DXVECTOR3 Mpos, Mrot;
		D3DXVECTOR3 MAnswer, MAnswer2;//�v�Z���ʗp

		//�L�[��񂩂�ʒu�E�������Z�o
		Mpos.x = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosX - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosX;
		Mpos.y = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosY - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosY;
		Mpos.z = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fPosZ - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosZ;
																																															 
		Mrot.x = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotX - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotX;
		Mrot.y = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotY - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotY;
		Mrot.z = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[nNextKey].aKey[nCntModel].fRotZ - g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotZ;

		//��ԌW�����v�Z
		float t = (float)g_player.motion.nCounterMotion / g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].nFrame;

		//���߂�l
		MAnswer.x = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosX + Mpos.x * t;
		MAnswer.y = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosY + Mpos.y * t;
		MAnswer.z = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fPosZ + Mpos.z * t;

		MAnswer2.x = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotX + Mrot.x * t;
		MAnswer2.y = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotY + Mrot.y * t;
		MAnswer2.z = g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].aKey[nCntModel].fRotZ + Mrot.z * t;


		//�S�p�[�c�̈ʒu�E������ݒ�
		g_player.motion.aModel[nCntModel].pos = g_player.motion.aModel[nCntModel].Offpos + MAnswer;

		g_player.motion.aModel[nCntModel].rot = g_player.motion.aModel[nCntModel].Offrot + MAnswer2;

	}

	g_player.motion.nCounterMotion++;//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�

	if (g_player.motion.nCounterMotion >= g_player.motion.aMotionInfo[g_player.motion.motionType].aKeyInfo[g_player.motion.nKey].nFrame)
	{
		g_player.motion.nCounterMotion = 0;

		g_player.motion.nKey++;
	}

}
//=============================
// �v���C���[�̕`�揈��
//=============================
void DrawPlayer(void)
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	//�S���f��(�p�[�c)�̕`��
	for (int nCntModel = 0; nCntModel < g_player.motion.nNumModel; nCntModel++)
	{


		//�p�[�c��`�悵�Ȃ�
		continue;


		D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X

		D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X

		//�p�[�c�̃��[���h�}�g���b�N�X��������
		D3DXMatrixIdentity(&g_player.motion.aModel[nCntModel].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.motion.aModel[nCntModel].rot.y, g_player.motion.aModel[nCntModel].rot.x, g_player.motion.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld, &g_player.motion.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.motion.aModel[nCntModel].pos.x, g_player.motion.aModel[nCntModel].pos.y, g_player.motion.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld, &g_player.motion.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_player.motion.aModel[nCntModel].nIdxModelParent != -1)
		{//�e���f��������ꍇ

			mtxParent = g_player.motion.aModel[g_player.motion.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{//�e���f�����Ȃ��ꍇ

			mtxParent = g_player.mtxWorld;
		}

		//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld, &g_player.motion.aModel[nCntModel].mtxWorld, &mtxParent);

		//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.motion.aModel[nCntModel].mtxWorld);

		for (int nCntMat = 0; nCntMat < (int)g_player.motion.aModel[nCntModel].dwNumMat; nCntMat++)
		{

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_player.motion.aModel[nCntModel].pBuffMat->GetBufferPointer();

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_player.motion.aModel[nCntModel].apTexture[nCntMat]);

			//���f��(�p�[�c)�̕`��
			g_player.motion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);

		}

	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
	
}
//============================================
//�v���C���[�̎擾
//============================================
Player* GetPlayer(void)
{
	return &g_player;
}
//============================================
//�v���C���[�̏�Ԏ擾
//============================================
PLAYERSTATE GetPlayerState(void)
{
	return g_player.state;
}
