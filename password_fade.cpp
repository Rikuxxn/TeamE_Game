//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================

#include "password_fade.h"

//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPasswordFade = NULL;	//���_�o�b�t�@�ւ̃|�C���^
PASSWORDFADE g_fade;									//�t�F�[�h�̏��
D3DXCOLOR g_colorPasswordFade;							//�|���S��(�t�F�[�h)�̐F

void InitPasswordFade(MODE modeNext)
{
	g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
	g_colorPasswordFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPasswordFade,
		NULL);
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPasswordFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = g_colorPasswordFade;
	pVtx[1].col = g_colorPasswordFade;
	pVtx[2].col = g_colorPasswordFade;
	pVtx[3].col = g_colorPasswordFade;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPasswordFade->Unlock();
}
void UninitPasswordFade(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPasswordFade != NULL)
	{
		g_pVtxBuffPasswordFade->Release();
		g_pVtxBuffPasswordFade = NULL;
	}
}
void UpdatePasswordFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����
			g_colorPasswordFade.a -= 0.04f;//�|���S���𓧖��ɂ��Ă���

			if (g_colorPasswordFade.a <= 0.0f)
			{
				g_colorPasswordFade.a = 0.0f;
				g_fade = FADE_NONE;//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorPasswordFade.a += 0.04f;//�|���S����s�����ɂ��Ă���
			
			g_colorPasswordFade.r += 0.04f;
			g_colorPasswordFade.g += 0.04f;
			g_colorPasswordFade.b += 0.04f;

			if (g_colorPasswordFade.a >= 1.0f)
			{
				g_colorPasswordFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
			}
		}
		else if (g_fade == FADE_FAIL)
		{//�t�F�[�h�A�E�g���
			g_colorPasswordFade.a += 0.04f;//�|���S����s�����ɂ��Ă���

			g_colorPasswordFade.r += 0.04f;
			//g_colorPasswordFade.g += 0.04f;
			//g_colorPasswordFade.b += 0.04f;

			if (g_colorPasswordFade.a >= 0.5f)
			{
				g_colorPasswordFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
			}
		}
		else if (g_fade == FADE_SUCCESS)
		{
			g_colorPasswordFade.a += 0.04f;//�|���S����s�����ɂ��Ă���

			//g_colorPasswordFade.r += 0.04f;
			g_colorPasswordFade.g += 0.04f;
			//g_colorPasswordFade.b += 0.04f;

			if (g_colorPasswordFade.a >= 0.5f)
			{
				g_colorPasswordFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
			}
		}

		VERTEX_2D* pVtx;//���_���ւ̃|�C���^
			
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPasswordFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorPasswordFade;
		pVtx[1].col = g_colorPasswordFade;
		pVtx[2].col = g_colorPasswordFade;
		pVtx[3].col = g_colorPasswordFade;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPasswordFade->Unlock();
	}
}
void DrawPasswordFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPasswordFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��
}
void SetPasswordFade(PASSWORDFADE fade)
{
	g_fade = fade;											//�t�F�[�h�A�E�g��Ԃ�
	g_colorPasswordFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//�����|���S��(����)�ɂ��Ă���
}
PASSWORDFADE GetPasswordFade(void)
{
	return g_fade;
}