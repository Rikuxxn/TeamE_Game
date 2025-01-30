//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "ball_fade.h"

//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallFade = NULL;//���_�o�b�t�@�ւ̃|�C���^
BALLFADE g_fade;//�t�F�[�h�̏��
D3DXCOLOR g_colorBallFade;//�|���S��(�t�F�[�h)�̐F

void InitBallFade(MODE modeNext)
{
	g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
	g_colorBallFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallFade,
		NULL);
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_colorBallFade;
	pVtx[1].col = g_colorBallFade;
	pVtx[2].col = g_colorBallFade;
	pVtx[3].col = g_colorBallFade;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBallFade->Unlock();
}
void UninitBallFade(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBallFade != NULL)
	{
		g_pVtxBuffBallFade->Release();
		g_pVtxBuffBallFade = NULL;
	}
}
void UpdateBallFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����
			g_colorBallFade.a -= 0.04f;//�|���S���𓧖��ɂ��Ă���

			if (g_colorBallFade.a <= 0.0f)
			{
				g_colorBallFade.a = 0.0f;
				g_fade = FADE_NONE;//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorBallFade.a += 0.04f;//�|���S����s�����ɂ��Ă���
			//g_colorBallFade.r += 0.01f;
			//g_colorBallFade.b += 0.02f;
			
			g_colorBallFade.r += 0.04f;
			g_colorBallFade.g += 0.04f;
			g_colorBallFade.b += 0.04f;

			if (g_colorBallFade.a >= 1.0f)
			{
				g_colorBallFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
			}
		}
		else if (g_fade == FADE_DAMAGE)
		{//�t�F�[�h�A�E�g���
			g_colorBallFade.a += 0.04f;//�|���S����s�����ɂ��Ă���

			g_colorBallFade.r += 0.04f;
			g_colorBallFade.g += 0.04f;
			g_colorBallFade.b += 0.04f;

			if (g_colorBallFade.a >= 1.0f)
			{
				g_colorBallFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
			}
		}

		VERTEX_2D* pVtx;//���_���ւ̃|�C���^
			
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBallFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorBallFade;
		pVtx[1].col = g_colorBallFade;
		pVtx[2].col = g_colorBallFade;
		pVtx[3].col = g_colorBallFade;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBallFade->Unlock();

	}
}
void DrawBallFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBallFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��
}
void SetBallFade(BALLFADE fade)
{
	g_fade = FADE_OUT;//�t�F�[�h�A�E�g��Ԃ�
	g_colorBallFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//�����|���S��(����)�ɂ��Ă���
}
BALLFADE GetBallFade(void)
{
	return g_fade;
}