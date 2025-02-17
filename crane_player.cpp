//---------------------------------------------------------
// �N���[���Q�[��
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "crane_player.h"
#include "Input.h"
#include "crane_block.h"
#include "crane_particle.h"
#include "crane_item.h"
#include "sound.h"

// �}�N��
#define MAX_MAX (400.0f)	// �ő�ł���
#define MAX_MIN (10.0f)		// �ŏ���������

// �O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureCranePlayer = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCranePlayer = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
CranePlayer g_player;									// ���C���[�̏��
//int g_nCounterAnimPlayer;
//int g_nPatternAnimPlayer;

// �v���C���[�̏���������
void InitCranePlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`��2�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\crane.png",					 // �e�N�X�`���̃t�@�C����
		&g_pTextureCranePlayer);

	g_player.pos = D3DXVECTOR3(CLANEFIELD_LEFT + 75.0f, 70.0f, 0.0f);	// �ʒu������������ SCREEN_HEIGHT-HEIGHT
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);						// �ړ��ʂ�����������
	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);							// ����������������A�����Z���i3�Ԗځj
	g_player.nCntAnimState = 0;
	g_player.bUse = true;
	g_player.bMove = true;
	g_player.bLeft = false;
	g_player.bDown = false;
	g_player.bUpSound = false;
	g_player.bLanding = false;
	g_player.bGetItem = false;
	g_player.pBlock = NULL;

	// �Ίp���̒������Z�o����
	g_player.Length = sqrtf(50.0f * 50.0f + 100.0f * 100.0f) / 2.0f;

	// �Ίp���̊p�x���Z�o����
	g_player.Angle = atan2f(WIDTH ,HEIGHT);

	// ���_�o�b�t�@2�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCranePlayer,
		NULL);

	VERTEX_2D *pVtx;// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCranePlayer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�

	pVtx[0].pos.x = -WIDTH;
	pVtx[0].pos.y = g_player.pos.y - HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = WIDTH;
	pVtx[1].pos.y = g_player.pos.y - HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -WIDTH;
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = WIDTH;
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	////�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	//pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);//(u,v)
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);//(u,v)
	//pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);//(u,v)

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCranePlayer->Unlock();
}
// �v���C���[�̏I������
void UninitCranePlayer(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureCranePlayer != NULL)
	{
		g_pTextureCranePlayer->Release();
		g_pTextureCranePlayer = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffCranePlayer != NULL)
	{
		g_pVtxBuffCranePlayer->Release();
		g_pVtxBuffCranePlayer = NULL;
	}
}
// �v���C���[�̍X�V����
void UpdateCranePlayer(void)
{
	VERTEX_2D* pVtx;// ���_���ւ̃|�C���^
	CRANEITEM pItem = GetItem();
	int nBulletCnt = 0;

	if (g_player.bUse == true)
	{
		if (g_player.bMove == true &&
			(GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true))
		{
			//g_nCounterAnimPlayer++;//�J�E���^�[�����Z
			// �ړ��ʂ��X�V�i�����j
			if (g_player.move.x <= MAX_SPEED_R)
			{ 
				g_player.move.x += 0.8f;
			}
			else if (g_player.move.x >= MAX_SPEED_R)
			{
				g_player.move.x = MAX_SPEED_R;
			}
		}

		if (g_player.bMove == true &&
			g_player.pos.x > CLANEFIELD_LEFT + 75.0f + WIDTH &&
			(GetMouseButtonTrigger(0) /*|| JoypadTrigger(JOYKEY_A) == true*/))
		{// �N���[��������
			g_player.move.y = DOWN;
			g_player.bMove = false;
			g_player.bDown = true;
			g_player.bLeft = false;
			PlaySound(SOUND_LABEL_CRANEDOWN);
		}
	}

	if (g_player.bLanding == true &&
		g_player.bMove == false &&
		g_player.bUpSound == false)
	{// ��ɏ���
		g_player.move.y = UP;
		g_player.bUpSound = true;
		StopSound(SOUND_LABEL_CRANEDOWN);
		PlaySound(SOUND_LABEL_CRANEUP);
	}

	if (g_player.bLeft == true &&
		g_player.bMove == false)
	{
		StopSound(SOUND_LABEL_CRANEUP);
		g_player.move.y = 0.0f;
		g_player.move.x = MAX_SPEED_L;
	}

	// �O��̈ʒu��ۑ�
	g_player.posOld = g_player.pos;

	// �ʒu���X�V
	g_player.pos.x += g_player.move.x;// ���ړ�
	g_player.pos.y += g_player.move.y;// ����

	// �A�C�e���̂�����͂�Ă�
	g_player.bGetItem = !CollisionCraneItem(&g_player.pos,
		&g_player.posOld,
		&g_player.move,
		ITEM_WIDTH,
		ITEM_HEIGHT);

	// �ړ��ʂ��X�V�i�����j
	g_player.move.x += (0.0f - g_player.move.x) * 0.2f;

	if (g_player.pos.y >= CLANEFIELD_UNDER)// �n��
	{
		g_player.pos.y = CLANEFIELD_UNDER;
		g_player.bLanding = true;
	}
	if (g_player.pos.y <= CLANEFIELD_TOP + HEIGHT)// �V��
	{
		g_player.pos.y = CLANEFIELD_TOP + HEIGHT;
		g_player.bLeft = true;
	}
	if (g_player.pos.x >= CLANEFIELD_RIGHT - WIDTH)// �E
	{
		g_player.pos.x = CLANEFIELD_RIGHT - WIDTH;
	}
	if (g_player.pos.x <= CLANEFIELD_LEFT + 75.0f + WIDTH)// ��
	{
		g_player.pos.x = CLANEFIELD_LEFT + 75.0f + WIDTH;
		g_player.bMove = true;
		g_player.bLeft = false;
		g_player.bFall = true;
		g_player.bUpSound = false;
		g_player.bLanding = false;
		g_player.move.x = 0;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCranePlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			// ���_�J���[�̐ݒ�
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

	// �ʒu���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x - WIDTH;
	pVtx[0].pos.y = g_player.pos.y - HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + WIDTH;
	pVtx[1].pos.y = g_player.pos.y - HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x - WIDTH;
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + WIDTH;
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCranePlayer->Unlock();

	////�e�N�X�`�����W�̍X�V0.125
	//if (g_player.bRightMove == true && g_player.bJamp1st == false)
	//{//�E����
	//	//�e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);//(u,v)
	//	pVtx[1].tex = D3DXVECTOR2(0.5f + 0.25f, 0.0f);//(u,v)
	//	pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);//(u,v)
	//	pVtx[3].tex = D3DXVECTOR2(0.5f + 0.25f, 0.5f);//(u,v)
	//}
	//else if (g_player.bRightMove == false && g_player.bJamp1st == false)
	//{//������
	//	//�e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.5f, 0.5f);//(u,v)
	//	pVtx[1].tex = D3DXVECTOR2(0.5f + 0.25f, 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(0.5f + 0.25f, 1.0f);
	//}

	//if (g_player.bRightMove == true && g_player.bJamp1st == false && KeyboardRepeat(DIK_LSHIFT) == true || g_player.bRightMove == true && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	//{//�E����
	//	//�e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);//(u,v)
	//	pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
	//	pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f, 0.5f);
	//}
	//else if (g_player.bRightMove == false && g_player.bJamp1st == false && KeyboardRepeat(DIK_LSHIFT) == true || g_player.bRightMove == false && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	//{//������
	//	//�e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);//(u,v)
	//	pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f, 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f, 1.0f);
	//}

	//if (g_player.bStop == true && g_player.bRightMove == true)//�X�g�b�v
	//{//�E����
	//	//�e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	//	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
	//}
	//else if (g_player.bStop == true && g_player.bRightMove == false)
	//{//������
	//	//�e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	//	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
	//}

	//if (g_player.bStop == true && g_player.bRightMove == true && KeyboardRepeat(DIK_LSHIFT) == true || g_player.bRightMove == true && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)//�X�g�b�v
	//{//�E����
	//	//�e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
	//	pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);
	//}
	//else if (g_player.bStop == true && g_player.bRightMove == false && KeyboardRepeat(DIK_LSHIFT) == true || g_player.bRightMove == false && g_player.bJamp1st == false && GetJoypadPress(JOYKEY_LB) == true)
	//{//������
	//	//�e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);
	//	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
	//}

	//if (g_player.bJamp1st == true)//�W�����v��
	//{
	//	if (g_player.bRightMove == true && g_player.bJamp1st == true)
	//	{//�E����
	//		//�e�N�X�`�����W�̐ݒ�
	//		pVtx[0].tex = D3DXVECTOR2(0.75f, 0.0f);
	//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[2].tex = D3DXVECTOR2(0.75f, 0.5f);
	//		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
	//	}
	//	else if (g_player.bRightMove == false && g_player.bJamp1st == true)
	//	{//������
	//		//�e�N�X�`�����W�̐ݒ�
	//		pVtx[0].tex = D3DXVECTOR2(0.75f, 0.5f);
	//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
	//		pVtx[2].tex = D3DXVECTOR2(0.75f, 1.0f);
	//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//	}
	//}
}
// �v���C���[�̕`�揈��
void DrawCranePlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffCranePlayer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_player.bUse == true)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCranePlayer);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
			0,                                     // �`�悷��ŏ��̒��_�C���f�b�N�X
			2);                                    // �`�悷��v���~�e�B�u��
	}
}
CranePlayer* GetCranePlayer(void)
{
	return &g_player;// �v���C���[�̏���Ԃ�
}
D3DXVECTOR3 GetCranePos(void)
{
	return g_player.move;
}