//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "action_particle.h"
#include "action_effect.h"

//�O���[�o��
ActionParticle g_aParticle[MAX_PARTICLE];//�p�[�e�B�N���̏��

//syokika
void InitActionParticle(void)
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
void UninitActionParticle(void)
{

}
//kousin
void UpdateActionParticle(void)
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
					nLife = 50;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife,0);
				}
				else if (g_aParticle[nCntParticle].nType == 1)//�W�����v
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 90 - 50) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 1.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.8f);

					//���a�̐ݒ�
					fRadius = 20.0f;

					//�����̐ݒ�
					nLife = 40;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife,0);
				}
				else if(g_aParticle[nCntParticle].nType == 3)//�o���A�ɓ�������(�E����)
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.1f, 0.1f, 0.4f, 1.0f);

					//���a�̐ݒ�
					fRadius = 15.0f;

					//�����̐ݒ�
					nLife = 50;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 4)//�o���A�ɓ�������(������)
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.1f, 0.1f, 0.4f, 1.0f);

					//���a�̐ݒ�
					fRadius = 15.0f;

					//�����̐ݒ�
					nLife = 50;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 5)//���n
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 90 - 50) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * -length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f);

					//���a�̐ݒ�
					fRadius = 10.0f;

					//�����̐ݒ�
					nLife = 30;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 6)//�󒆃_�b�V��(������)
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 1.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.8f);

					//���a�̐ݒ�
					fRadius = 20.0f;

					//�����̐ݒ�
					nLife = 40;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 7)//�󒆃_�b�V��(�E����)
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;
	
					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 1.0f;
	
					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;
	
					//�F�̐ݒ�
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.8f);

					//���a�̐ݒ�
					fRadius = 20.0f;
	
					//�����̐ݒ�
					nLife = 40;
	
					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 8)//�n�㑖��(�E��)
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 40 - 180) / 60.0f;//50.0f;
					length = (float)(rand() % 10) / 1.0f + 1.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.8f);

					//���a�̐ݒ�
					fRadius = 7.0f;

					//�����̐ݒ�
					nLife = 15;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 9)//�n�㑖��(����)
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 40 - 180) / 60.0f;
					length = (float)(rand() % 10) / 1.0f + 1.0f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.8f);

					//���a�̐ݒ�
					fRadius = 7.0f;

					//�����̐ݒ�
					nLife = 15;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 10)//�^�b�N��(�E����)
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(1.0f, 0.0f, 0.4f, 1.0f);

					//���a�̐ݒ�
					fRadius = 20.0f;

					//�����̐ݒ�
					nLife = 50;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 11)//�^�b�N��(������)
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(1.0f, 0.0f, 0.4f, 1.0f);

					//���a�̐ݒ�
					fRadius = 20.0f;

					//�����̐ݒ�
					nLife = 50;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 12)//�`���[�W����
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 628 - 314) / 100.0f;
					length = (float)(rand() % 10) / 1.0f - 1.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.4f, 0.4f, 0.0f, 0.4f);

					//���a�̐ݒ�
					fRadius = 8.0f;

					//�����̐ݒ�
					nLife = 6;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 13)//�e�̔���
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;
					
					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 628 - 314) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 3.0f;
					
					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;
					
					//�F�̐ݒ�
					col = D3DXCOLOR(0.4f, 0.2f, 0.0f, 0.8f);
					
					//���a�̐ݒ�
					fRadius = 15.0f;
					
					//�����̐ݒ�
					nLife = 20;
					
					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 16)//�_�b�V���E
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.2f);

					//���a�̐ݒ�
					fRadius = 10.0f;

					//�����̐ݒ�
					nLife = 15;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 17)//�_�b�V���E
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 55 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 0.2f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.8f, 0.2f, 0.0f, 0.2f);

					//���a�̐ݒ�
					fRadius = 10.0f;

					//�����̐ݒ�
					nLife = 15;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
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
				//SetActionEffect();
			}

			for (nCntAppear = 0; nCntAppear < 10; nCntAppear++)
			{
				if (g_aParticle[nCntParticle].nType == 14)//���n(������)
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 50 - 180) / 80.0f;
					length = (float)(rand() % 10) / 1.0f + 0.0f;

					move.x = sinf(angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.3f);

					//���a�̐ݒ�
					fRadius = 20.0f;

					//�����̐ݒ�
					nLife = 30;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}
				else if (g_aParticle[nCntParticle].nType == 15)//���n(�E����)
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 50 - 180) / 80.0f;
					length = (float)(rand() % 10) / 1.0f + 0.0f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.3f);

					//���a�̐ݒ�
					fRadius = 20.0f;

					//�����̐ݒ�
					nLife = 30;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife, 0);
				}

			}

			for (nCntAppear = 0; nCntAppear < 4; nCntAppear++)
			{
				if (g_aParticle[nCntParticle].nType == 2)//�Ή����˓I�Ȃ��
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					angle = (float)(rand() % 40 - 180) / 100.0f;
					length = (float)(rand() % 10) / 1.0f + 2.0f;

					move.x = sinf(-angle) * length;
					move.y = cosf(angle) * length;

					//�F�̐ݒ�
					col = D3DXCOLOR(0.5f, 0.1f, 0.0f, 1.0f);

					//���a�̐ݒ�
					fRadius = 20.0f;

					//�����̐ݒ�
					nLife = 90;

					//�G�t�F�N�g�̐ݒ�
					SetActionEffect(pos, move, col, fRadius, nLife,1);
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
void DrawActionParticle(void)
{

}
ActionParticle* GetActionParticle(void)
{
	return &g_aParticle[0];
}
void SetActionParticle(D3DXVECTOR3 pos,int nType)
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