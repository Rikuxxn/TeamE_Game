//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "action_fade.h"

//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffActionFade = NULL;//���_�o�b�t�@�ւ̃|�C���^
ACTIONFADE g_fade;//�t�F�[�h�̏��
D3DXCOLOR g_colorActionFade;//�|���S��(�t�F�[�h)�̐F

void InitActionFade(MODE modeNext)
{
	g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
	g_colorActionFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffActionFade,
		NULL);
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffActionFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = g_colorActionFade;
	pVtx[1].col = g_colorActionFade;
	pVtx[2].col = g_colorActionFade;
	pVtx[3].col = g_colorActionFade;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffActionFade->Unlock();
}
void UninitActionFade(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffActionFade != NULL)
	{
		g_pVtxBuffActionFade->Release();
		g_pVtxBuffActionFade = NULL;
	}
}
void UpdateActionFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����
			g_colorActionFade.a -= 0.04f;//�|���S���𓧖��ɂ��Ă���

			if (g_colorActionFade.a <= 0.0f)
			{
				g_colorActionFade.a = 0.0f;
				g_fade = FADE_NONE;//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorActionFade.a += 0.04f;//�|���S����s�����ɂ��Ă���
			//g_colorActionFade.r += 0.01f;
			//g_colorActionFade.b += 0.02f;
			
			g_colorActionFade.r += 0.04f;
			g_colorActionFade.g += 0.04f;
			g_colorActionFade.b += 0.04f;

			if (g_colorActionFade.a >= 1.0f)
			{
				g_colorActionFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
			}
		}
		else if (g_fade == FADE_DAMAGE)
		{//�t�F�[�h�A�E�g���
			g_colorActionFade.a += 0.04f;//�|���S����s�����ɂ��Ă���

			g_colorActionFade.r += 0.04f;
			g_colorActionFade.g += 0.04f;
			g_colorActionFade.b += 0.04f;

			if (g_colorActionFade.a >= 1.0f)
			{
				g_colorActionFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
			}
		}

		VERTEX_2D* pVtx;//���_���ւ̃|�C���^
			
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffActionFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorActionFade;
		pVtx[1].col = g_colorActionFade;
		pVtx[2].col = g_colorActionFade;
		pVtx[3].col = g_colorActionFade;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffActionFade->Unlock();

	}
}
void DrawActionFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffActionFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��
}
void SetActionFade(ACTIONFADE fade)
{
	g_fade = FADE_OUT;//�t�F�[�h�A�E�g��Ԃ�
	g_colorActionFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//�����|���S��(����)�ɂ��Ă���
}
ACTIONFADE GetActionFade(void)
{
	return g_fade;
}