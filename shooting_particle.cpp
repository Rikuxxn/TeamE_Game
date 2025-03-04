#include "shooting_particle.h"
#include "shooting_effect.h"
#include "shooting_bullet.h"
#include "shooting_enemy.h"

//�O���[�o��
Particle g_aParticle[MAX_PARTICLE];//�p�[�e�B�N���̏��

//syokika
void InitParticle(void)
{
	int nCntParticle;
	VERTEX_2D* pVtx = 0;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�̏��̏�����
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = false;													//�g�p���Ă��Ȃ���Ԃɂ���
		g_aParticle[nCntParticle].nType = 0;
	}
}
//syuuryou
void UninitParticle(void)
{

}
//kousin
void UpdateParticle(void)
{
	int nCntParticle;
	int nCntAppear;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	float fRadius;
	int nLife;
	float angle;
	float length;

	VERTEX_2D* pVtx = 0;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			//�p�[�e�B�N���̐���
			for (nCntAppear = 0; nCntAppear < 20; nCntAppear++)
			{
				if (g_aParticle[nCntParticle].nType == 0)//����
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 628 - 314) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 3.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.4f, 0.2f, 0.0f, 0.3f);

					//���a�̐ݒ�
					fRadius = 15.0f;

					//�����̐ݒ�
					nLife = 30;

					//�G�t�F�N�g�̐ݒ�
					SetEffect(pos, move, col, fRadius, nLife,0);
				}
				else if (g_aParticle[nCntParticle].nType == 1)//�A�t�^�[�o�[�i�[
				{

					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					//angle = (float)(rand() % 55 - 185) / 100.0f;
					angle = (float)(rand() % 55 - 180) / 50.0f;
					length = (float)(rand() % 10) / 1.0f - 10.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//move.x = sinf(length) * angle;
					//move.y = cosf(length) * angle;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.4f, 0.2f, 0.0f, 0.3f);

					//���a�̐ݒ�
					fRadius = 7.0f;

					//�����̐ݒ�
					nLife = 15;

					//�G�t�F�N�g�̐ݒ�
					SetEffect(pos, move, col, fRadius, nLife,0);
				}
				else if(g_aParticle[nCntParticle].nType == 3)//�q�b�g
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 3.0f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.4f, 0.2f, 0.0f, 1.0f);

					//���a�̐ݒ�
					fRadius = 15.0f;

					//�����̐ݒ�
					nLife = 50;

					//�G�t�F�N�g�̐ݒ�
					SetEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 4)//��1
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 130 - 350) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.1f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.3f);

					//���a�̐ݒ�
					fRadius = 15.0f;

					//�����̐ݒ�
					nLife = 50;

					//�G�t�F�N�g�̐ݒ�
					SetEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 5)//��2
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 50 - 1) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.3f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.3f);

					//���a�̐ݒ�
					fRadius = 15.0f;

					//�����̐ݒ�
					nLife = 50;

					//�G�t�F�N�g�̐ݒ�
					SetEffect(pos, move, col, fRadius, nLife, 0);
				}


				//�ʒu�̐ݒ�
				//pos=D3DXVECTOR3();

				//�ړ��ʂ̐ݒ�
				// sinf((float)(rand() % 628 - 314) / 100.0f);
				// cosf((float)(rand() % 100) / 25.0f + 10.0f);
				//move.x=sinf(�p�x)*�ړ���	�p�x=-3.14�`3.14
				//move.y=cosf(�p�x)*�ړ���	
				//�p�x�̋��ߕ�  (float)(rand() % 629 - 314) / 100.0f;
				//�ړ��ʂ̋��ߕ�(float)(rand() % ***) / *** + ***;

				//�F�̐ݒ�
				//col=;

				//���a�̐ݒ�
				//fRadius=;

				//�����̐ݒ�
				//nLife=;

				//�G�t�F�N�g�̐ݒ�
				//SetEffect();
			}

			for (nCntAppear = 0; nCntAppear < 4; nCntAppear++)
			{
				if (g_aParticle[nCntParticle].nType == 2)//�Ή����˓I�Ȃ��
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					//angle = (float)(rand() % 40 - 175) / 100.0f;
					angle = (float)(rand() % 40 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 2.0f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//move.x = sinf(length) * angle;
					//move.y = cosf(length) * angle;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.5f, 0.1f, 0.0f, 1.0f);

					//���a�̐ݒ�
					fRadius = 20.0f;

					//�����̐ݒ�
					nLife = 90;

					//�G�t�F�N�g�̐ݒ�
					SetEffect(pos, move, col, fRadius, nLife,1);
				}
			}

			g_aParticle[nCntParticle].nLife--;

			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}
}
void DrawParticle(void)
{

}
Particle* GetParticle(void)
{
	return &g_aParticle[0];
}
void SetParticle(D3DXVECTOR3 pos,int nType)
{
	int nCntParticle;
	VERTEX_2D* pVtx = 0;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].nType = nType;
			g_aParticle[nCntParticle].bUse = true;

			if (g_aParticle[nCntParticle].nType == 0)
			{
				g_aParticle[nCntParticle].nLife = 30;
			}
			else if (g_aParticle[nCntParticle].nType == 1)
			{
				g_aParticle[nCntParticle].nLife = 1;
			}
			break;
		}
	}
}