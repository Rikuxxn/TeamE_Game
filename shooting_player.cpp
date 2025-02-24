//---------------------------------------------------------
//
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "shooting_player.h"
#include "Input.h"
#include "shooting_bullet.h"
#include "shooting_enemy.h"
#include "shooting_effect.h"
#include "shooting_fade.h"
#include "sound.h"
#include "shooting_particle.h"
#include "game.h"
#include "shooting_background.h"

// �}�N��
#define MAX_MAX (400.0f)	//�ő�ł���
#define MAX_MIN (10.0f)		//�ŏ���������

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTexturePlayer1 = NULL;	 // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer1 = NULL;// ���_�o�b�t�@�ւ̃|�C���^
ShootingPlayer g_player;						 // �v���C���[�̏��

// �v���C���[�̏���������
void InitShootingPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Player.png",//�e�N�X�`���̃t�@�C����
		&g_pTexturePlayer1);

	g_player.pos = D3DXVECTOR3(640.0f,540.0f,0.0f);// �ʒu������������
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);   // �ړ��ʂ�����������
	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);	   // ����������������A�����Z���i3�Ԗځj
	g_player.Bullet.x = 10.0f;
	g_player.Bullet.y = 10.0f;
	g_player.bUse = true;
	g_player.bDisp = true;
	g_player.bHit = false;
	g_player.nCntAnimState = 0;
	g_player.nLife = 8;
	g_player.nBulletType = 0;
	g_player.nBulletCnt = BULLET_COOL;
	g_player.nBulletCool = 0;
	g_player.nBulletMax = 0;

	// �Ίp���̒������Z�o����
	g_player.Length = sqrtf(40.0f * 40.0f + 40.0f * 40.0f) / 2.0f;

	// �Ίp���̊p�x���Z�o����
	g_player.Angle = atan2f(WIDTH,HEIGHT);

	// ���_�o�b�t�@2�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer1,
		NULL);

	VERTEX_2D *pVtx;// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
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

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer1->Unlock();
}
// �v���C���[�̏I������
void UninitShootingPlayer(void)
{
	// �e�N�X�`���̔j��
	if (g_pTexturePlayer1 != NULL)
	{
		g_pTexturePlayer1->Release();
		g_pTexturePlayer1 = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer1 != NULL)
	{
		g_pVtxBuffPlayer1->Release();
		g_pVtxBuffPlayer1 = NULL;
	}
}
// �v���C���[�̍X�V����
void UpdateShootingPlayer(void)
{
	VERTEX_2D* pVtx;// ���_���ւ̃|�C���^
	GAME* pGame = GetGame();

	if (g_player.bUse == true && pGame->bSTClear == false)
	{
		//if (GetJoypadPress(JOYKEY_UP) == true)
		//{//��L�[
		//	g_player.move.x += 0.0f;
		//	g_player.move.y -= 1.0f;
		//}
		//else if (GetJoypadPress(JOYKEY_DOWN) == true)
		//{//���L�[
		//	g_player.move.x += 0.0f;
		//	g_player.move.y += 1.0f;
		//}
		//else if (GetJoypadPress(JOYKEY_LEFT) == true)
		//{
		//	//�ړ��ʂ��X�V�i�����j
		//	g_player.move.x -= 1.0f;
		//	g_player.move.y += 0.0f;
		//}
		//else if (GetJoypadPress(JOYKEY_RIGHT) == true)
		//{
		//	g_player.move.x += 1.0f;
		//	g_player.move.y += 0.0f;
		//}

		if (GetKeyboardPress(DIK_A) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				// �ړ��ʂ��X�V�i�����j
				g_player.move.x += sinf(-D3DX_PI * 0.75f) * 0.75f;
				g_player.move.y += cosf(-D3DX_PI * 0.75f) * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{
				// �ړ��ʂ��X�V�i�����j
				g_player.move.x += sinf(-D3DX_PI * 0.25f) * 0.75f;
				g_player.move.y += cosf(-D3DX_PI * 0.25f) * 0.75f;
			}
			else
			{
				// �ړ��ʂ��X�V�i�����j
				g_player.move.x -= 1.0f;
				g_player.move.y += 0.0f;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.75f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_player.move.x += sinf(D3DX_PI * 0.25f) * 0.75f;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.75f;
			}
			else
			{
				g_player.move.x += 1.0f;
				g_player.move.y += 0.0f;
			}

		}
		else if (GetKeyboardPress(DIK_W) == true)
		{
			// ��Ɉړ�
			g_player.move.x += 0.0f;
			g_player.move.y -= 1.0f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			// ���Ɉړ�
			g_player.move.x += 0.0f;
			g_player.move.y += 1.0f;
		}
		//else if (KeyboardTrigger(DIK_R) == true || JoypadTrigger(JOYKEY_RB) == true)
		//{
		//	PlaySound(SOUND_LABEL_RELOAD);
		//	if (g_player.nBulletType == 0)
		//	{
		//		g_player.nBulletType = 1;
		//	}
		//	else if(g_player.nBulletType == 1)
		//	{
		//		g_player.nBulletType = 0;
		//	}
		//}
		if (g_player.bHit == true)
		{
			g_player.nCntAnimState++;// �J�E���^�[�����Z
		}

		switch (g_player.nBulletType)
		{
		case 0:
			if (/*GetKeyboardPress(DIK_SPACE) == true ||*/ GetMouseButtonPress(0)/*|| GetJoypadPress(JOYKEY_A) == true*/)
			{// SPACE
				g_player.nBulletCnt++;
				if (g_player.nBulletCnt >= BULLET_INTERVAL/* && g_player.nBulletMax < BULLETMAX*/)
				{
					// �e�̐ݒ�
					PlaySound(SOUND_LABEL_STSHOT);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * 10.0f, cosf(g_player.rot.z + D3DX_PI) * 10.0f, 0.0f), BULLETTYPE_PLAYER, 20, 1);
					g_player.nBulletCnt = 0;
					g_player.nBulletMax++;
				}
			}
			else if (KeyboardRelease(DIK_SPACE) == true /*|| JoypadRelease(JOYKEY_A) == true*/)
			{
				g_player.nBulletCnt = BULLET_INTERVAL;
				g_player.nBulletMax = 0;
			}
			break;
		//case 1:
		//	if (g_player.nBulletCool <= 0 && (KeyboardTrigger(DIK_SPACE) == true || JoypadTrigger(JOYKEY_A) == true))
		//	{
		//		PlaySound(SOUND_LABEL_SHOT02);
		//		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * 15.0f, cosf(g_player.rot.z + D3DX_PI) * 15.0f, 0.0f), BULLETTYPE_PLAYER,20,2);
		//		g_player.nBulletCool = 15;
		//	}
		//	break;
		//case 2:
		//	if (KeyboardRepeat(DIK_SPACE) == true || GetJoypadPress(JOYKEY_A) == true)
		//	{
		//		SetParticle(D3DXVECTOR3(g_player.pos.x + 50.0f, g_player.pos.y, g_player.pos.z), 2);
		//	}
		//	break;
		}
		// �A�t�^�[�o�[�i�[
		SetParticle(D3DXVECTOR3(g_player.pos.x + 7.0f, g_player.pos.y + 20.0f, g_player.pos.z), 1);
		SetParticle(D3DXVECTOR3(g_player.pos.x - 7.0f, g_player.pos.y + 20.0f, g_player.pos.z), 1);
	}

	if (g_player.nBulletMax < BULLET_MAX)
	{
		g_player.nBulletCool = BULLET_COOL;
	}
	if (g_player.nBulletCool >= 0)
	{
		g_player.nBulletCool--;
	}
	else if (g_player.nBulletCool <= 0)
	{
		g_player.nBulletCool = 0;
		g_player.nBulletMax = 0;
	}

	// �ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	// �ړ��ʂ��X�V�i�����j
	g_player.move.x += (0.0f - g_player.move.x) * 0.1f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.1f;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

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
			if (g_player.nCounterState <= 0)
			{
				g_player.state = PLAYERSTATE_NORMAL;
			}
		}
		break;
	}

	// �ʒu���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.z = 0.0f;

	if (g_player.pos.x >= 640.0f + BACKGROUND_WIDTH - WIDTH)
	{
		g_player.pos.x = 640.0f + BACKGROUND_WIDTH - WIDTH;
	}
	else if (g_player.pos.x <= 640.0f - BACKGROUND_WIDTH + WIDTH)
	{
		g_player.pos.x = 640.0f - BACKGROUND_WIDTH + WIDTH;
	}

	if (g_player.pos.y >= BACKGROUND_HEIGHT - HEIGHT)
	{
		g_player.pos.y = BACKGROUND_HEIGHT - HEIGHT;
	}
	else if (g_player.pos.y <= 0 + HEIGHT)
	{
		g_player.pos.y = 0 + HEIGHT;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer1->Unlock();
}
// �v���C���[�̕`�揈��
void DrawShootingPlayer(void)
{
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾

	if (g_player.bDisp == true)
	{
		// ���_�o�b�t�@���f�[�^�X�g���[��
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer1, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		if (g_player.bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePlayer1);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
				0,                                     // �`�悷��ŏ��̒��_�C���f�b�N�X
				2);                                    // �`�悷��v���~�e�B�u��
		}
	}
}
ShootingPlayer* GetShootingPlayer(void)
{
	return &g_player;// �v���C���[�̏���Ԃ�
}
void HitShootingPlayer(int nDamage)// ������͂�Ă�
{
	VERTEX_2D* pVtx;
	g_player.nLife -= nDamage;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.nLife <= 0)// ����
	{
		//PlaySound(SOUND_LABEL_EXPLOSION);

		//bakuhatu
		SetParticle(g_player.pos, 0);

		g_player.bUse = false;

		g_player.bDisp = false;

		g_player.nCntAnimState = PLAYERSTATE_DEATH;

		g_player.nCounterState = 60;

	}
	else// ����łȂ�
	{
		g_player.state = PLAYERSTATE_DAMAGE;

		g_player.nCounterState = 5;

		SetParticle(g_player.pos, 3);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0,0, 255);

		//// �T�E���h�̍Đ�
		//PlaySound(SOUND_LABEL_DAMAGE);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer1->Unlock();
}