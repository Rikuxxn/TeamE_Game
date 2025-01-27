//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "action_player.h"
#include "Input.h"
#include "action_block.h"
#include "action_particle.h"
#include "action_item.h"
//#include "sound.h"

//�}�N��
#define MAX_MAX (400.0f)//�ő�ł���
#define MAX_MIN (10.0f)//�ŏ���������

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureActionPlayer = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffActionPlayer = NULL;//���_�o�b�t�@�ւ̃|�C���^
ActionPlayer g_player;                                 //���C���[�̏��
int g_nCounterAnimPlayer;
int g_nPatternAnimPlayer;
int g_nMutekiCounter;
bool g_bLandingParticle = false;//���n�����ۂ̃p�[�e�B�N���\���p�֐�

//�v���C���[�̏���������
void InitActionPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;                   //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��2�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player2.png",      //�e�N�X�`���̃t�@�C����
		&g_pTextureActionPlayer);

	g_nMutekiCounter = 0;
	g_player.pos = D3DXVECTOR3(640.0f,670.0f,0.0f);//�ʒu������������ SCREEN_HEIGHT-TAKASA
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);   //�ړ��ʂ�����������
	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);	   //����������������A�����Z���i3�Ԗځj
	g_player.nCntAnimState = 0;
	g_player.nLife = 5;
	g_player.nGuardCnt = 0;
	g_player.bUse = true;
	g_player.bDisp = true;
	g_player.bHit = false;
	g_player.bJamp1st = true;
	g_player.bRightMove = true;
	g_player.bStop = true;
	g_player.bLanding = false;
	g_player.bGetItem = false;
	g_player.bBlockUse = false;
	g_player.pBlock = NULL;

	//�Ίp���̒������Z�o����
	g_player.Length = sqrtf(50.0f * 50.0f + 100.0f * 100.0f) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	g_player.Angle = atan2f(HABA ,TAKASA);

	//���_�o�b�t�@2�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffActionPlayer,
		NULL);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffActionPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�

	pVtx[0].pos.x = -HABA;//g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.y = g_player.pos.y-TAKASA;//g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = HABA;//g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.y = g_player.pos.y-TAKASA;//g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -HABA;//g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.y = g_player.pos.y;// +cosf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = HABA;//g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.y = g_player.pos.y;// +cosf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);//(u,v)

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffActionPlayer->Unlock();
}
//�v���C���[�̏I������
void UninitActionPlayer(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureActionPlayer != NULL)
	{
		g_pTextureActionPlayer->Release();
		g_pTextureActionPlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffActionPlayer != NULL)
	{
		g_pVtxBuffActionPlayer->Release();
		g_pVtxBuffActionPlayer = NULL;
	}
}
//�v���C���[�̍X�V����
void UpdateActionPlayer(void)
{
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^
	int nBulletCnt = 0;

	if (g_player.bUse == true)
	{
		if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
		{
			g_nCounterAnimPlayer++;//�J�E���^�[�����Z
			g_player.bRightMove = false;
			g_player.bStop = false;

			if (g_player.bJamp1st == false)
			{//�ʏ�
				//�ړ��ʂ��X�V�i�����j
				if (g_player.move.x >= MAX_SPEED_L)
				{
					g_player.move.x -= 0.4f;
				}
				else if (g_player.move.x <= MAX_SPEED_L)
				{
 					g_player.move.x = MAX_SPEED_L;
					SetActionParticle(D3DXVECTOR3(g_player.pos.x + HABA / 2, g_player.pos.y, 0.0f), 9);
				}
			}
			if (g_player.bJamp1st == true)
			{//�W�����v��
				//�ړ��ʂ��X�V�i�����j
				g_player.move.x -= 0.3f;
			}

		}
		else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true)
		{
			g_nCounterAnimPlayer++;//�J�E���^�[�����Z
			g_player.bRightMove = true;
			g_player.bStop = false;

			if (g_player.bJamp1st == false)
			{//�ʏ�
				//�ړ��ʂ��X�V�i�����j
				if (g_player.move.x <= MAX_SPEED_R)
				{
					g_player.move.x += 0.4f;
				}
				else if (g_player.move.x >= MAX_SPEED_R)
				{
					g_player.move.x = MAX_SPEED_R;
					SetActionParticle(D3DXVECTOR3(g_player.pos.x - HABA / 2, g_player.pos.y, 0.0f), 8);
				}
			}
			
			if (g_player.bJamp1st == true)
			{//�W�����v��
				//�ړ��ʂ��X�V�i�����j
				g_player.move.x += 0.3f;
			}
		}
		else if(KeyboardRelease(DIK_A) == true || KeyboardRelease(DIK_D) == true /*|| JoypadRelease(JOYKEY_LEFT) == true || JoypadRelease(JOYKEY_RIGHT) == true*/)
		{
			g_player.bStop = true;
		}
		else
		{
			g_nCounterAnimPlayer=0;//�J�E���^�[�����Z�b�g
		}

		if (g_player.bHit == true)
		{
			g_player.nCntAnimState++;//�J�E���^�[�����Z
		}

		if (KeyboardTrigger(DIK_SPACE) == true /*|| JoypadTrigger(JOYKEY_A) == true*/)//�W�����v
		{
 			if (g_player.bJamp1st == false)
			{
				//PlaySound(SOUND_LABEL_JAMP_SHORT);
				SetActionParticle(D3DXVECTOR3(g_player.pos.x, g_player.pos.y, 0.0f), 1);
				g_player.move.y = F_JAMP1ST;
				g_player.bJamp1st = true;
				g_player.bLanding = false;
				g_bLandingParticle = true;
			}
		}
	}//g_player.pos

	if (g_player.bLanding == true && g_bLandingParticle == true)
	{//���n
		SetActionParticle(g_player.pos, 14);
		SetActionParticle(g_player.pos, 15);
		g_player.bLanding = false;
		g_bLandingParticle = false;
	}

	//�d�͂��X�V
	g_player.move.y += 1.0f;//�d�͉��Z

	//�O��̈ʒu��ۑ�
	g_player.posOld = g_player.pos;

	if (g_player.pBlock != NULL)//�u���b�N�ɏ���Ă���
	{//�u���b�N���ړ������������v���C���[�Ƀv���X����
		g_player.pBlock;
	}

	if (CollisionActionBlock(&g_player.pos,
						&g_player.posOld,
						&g_player.move,
						HABA,
						TAKASA,&g_player.pBlock) == true)
	{

	}

	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;//���ړ�
	g_player.pos.y += g_player.move.y;//����

	//�u���b�N�̂�����͂�Ă�
	g_player.bJamp1st = !CollisionActionBlock(&g_player.pos,
										&g_player.posOld,
										&g_player.move,
										HABA,
										TAKASA,&g_player.pBlock);

	g_player.bBlockUse = !CollisionActionBlock2(&g_player.pos,
										&g_player.posOld,
										&g_player.move,
										HABA,
										TAKASA);
	
	//�A�C�e���̂�����͂�Ă�
	g_player.bGetItem = !CollisionActionItem(&g_player.pos,
									&g_player.posOld,
									&g_player.move,
									HABA,
									TAKASA);

	//�ړ��ʂ��X�V�i�����j
	g_player.move.x += (0.0f - g_player.move.x) * 0.04f;/*0.13f;*/

	if (g_player.pos.x >= 880.0f - HABA)//��
	{
		g_player.pos.x = 880.0f - HABA;
	}
	else if (g_player.pos.x <= 400.0f + HABA)
	{
		g_player.pos.x = 400.0f + HABA;
	}

	if (g_player.pos.y >= SCREEN_HEIGHT)//�n��
	{
		g_player.pos.y = SCREEN_HEIGHT;
		g_player.bJamp1st = false;
	}
	else if (g_player.pos.y <= 0 + TAKASA)//�V��
	{
		g_player.pos.y = 0 + TAKASA;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffActionPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		break;
	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			////���[�h��ݒ�i���U���g�j
			//SetMode(MODE_RESULT_LOSE);
			return;
		}
		else
		{
		}
		break;
	case PLAYERSTATE_MUTEKI:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
		}
		break;
	}

	//�ʒu���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x-HABA;
	pVtx[0].pos.y = g_player.pos.y-TAKASA;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x+HABA;
	pVtx[1].pos.y = g_player.pos.y-TAKASA;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x-HABA;
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x+HABA;
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffActionPlayer->Unlock();

	//�e�N�X�`�����W�̍X�V0.125
	if (g_player.bRightMove == true && g_player.bJamp1st == false)
	{//�E����
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.5f + 0.25f, 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.5f + 0.25f, 0.5f);//(u,v)
	}
	else if (g_player.bRightMove == false && g_player.bJamp1st == false)
	{//������
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.5f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.5f + 0.25f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f + 0.25f, 1.0f);
	}

	if (g_player.bRightMove == true && g_player.bJamp1st == false && GetKeyboardPress(DIK_LSHIFT) == true || g_player.bRightMove == true && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	{//�E����
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f, 0.5f);
	}
	else if (g_player.bRightMove == false && g_player.bJamp1st == false && GetKeyboardPress(DIK_LSHIFT) == true || g_player.bRightMove == false && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	{//������
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f, 1.0f);
	}

	if (g_player.bStop == true && g_player.bRightMove == true)//�X�g�b�v
	{//�E����
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
	}
	else if (g_player.bStop == true && g_player.bRightMove == false)
	{//������
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
	}

	if (g_player.bStop == true && g_player.bRightMove == true && GetKeyboardPress(DIK_LSHIFT) == true || g_player.bRightMove == true && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)//�X�g�b�v
	{//�E����
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);
	}
	else if (g_player.bStop == true && g_player.bRightMove == false && GetKeyboardPress(DIK_LSHIFT) == true || g_player.bRightMove == false && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	{//������
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
	}

	if (g_player.bJamp1st == true)//�W�����v��
	{
		if (g_player.bRightMove == true && g_player.bJamp1st == true)
		{//�E����
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.75f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.75f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
		}
		else if (g_player.bRightMove == false && g_player.bJamp1st == true)
		{//������
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.75f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.75f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}
}
//�v���C���[�̕`�揈��
void DrawActionPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[��
		pDevice->SetStreamSource(0, g_pVtxBuffActionPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		if (g_player.bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureActionPlayer);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				0,                                     //�`�悷��ŏ��̒��_�C���f�b�N�X
				2);                                    //�`�悷��v���~�e�B�u��
		}
	}
}
ActionPlayer* GetActionPlayer(void)
{
	return &g_player;//�v���C���[�̏���Ԃ�
}
D3DXVECTOR3 GetActionPos(void)
{
	return g_player.move;
}
int GetActionLife(void)
{
	return g_player.nLife;
}