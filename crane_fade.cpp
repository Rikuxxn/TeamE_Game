//---------------------------------------------------------
// 2D�A�N�V����
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "crane_fade.h"

//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCraneFade = NULL;	//���_�o�b�t�@�ւ̃|�C���^
CRANEFADE g_fade;									//�t�F�[�h�̏��
D3DXCOLOR g_colorCraneFade;							//�|���S��(�t�F�[�h)�̐F

void InitCraneFade(MODE modeNext)
{
	g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
	g_colorCraneFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCraneFade,
		NULL);
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCraneFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = g_colorCraneFade;
	pVtx[1].col = g_colorCraneFade;
	pVtx[2].col = g_colorCraneFade;
	pVtx[3].col = g_colorCraneFade;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCraneFade->Unlock();
}
void UninitCraneFade(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCraneFade != NULL)
	{
		g_pVtxBuffCraneFade->Release();
		g_pVtxBuffCraneFade = NULL;
	}
}
void UpdateCraneFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����
			g_colorCraneFade.a -= 0.04f;//�|���S���𓧖��ɂ��Ă���

			if (g_colorCraneFade.a <= 0.0f)
			{
				g_colorCraneFade.a = 0.0f;
				g_fade = FADE_NONE;//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorCraneFade.a += 0.04f;//�|���S����s�����ɂ��Ă���
			//g_colorCraneFade.r += 0.01f;
			//g_colorCraneFade.b += 0.02f;
			
			g_colorCraneFade.r += 0.04f;
			g_colorCraneFade.g += 0.04f;
			g_colorCraneFade.b += 0.04f;

			if (g_colorCraneFade.a >= 1.0f)
			{
				g_colorCraneFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
			}
		}
		else if (g_fade == FADE_DAMAGE)
		{//�t�F�[�h�A�E�g���
			g_colorCraneFade.a += 0.04f;//�|���S����s�����ɂ��Ă���

			g_colorCraneFade.r += 0.04f;
			g_colorCraneFade.g += 0.04f;
			g_colorCraneFade.b += 0.04f;

			if (g_colorCraneFade.a >= 1.0f)
			{
				g_colorCraneFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
			}
		}

		VERTEX_2D* pVtx;//���_���ւ̃|�C���^
			
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffCraneFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorCraneFade;
		pVtx[1].col = g_colorCraneFade;
		pVtx[2].col = g_colorCraneFade;
		pVtx[3].col = g_colorCraneFade;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffCraneFade->Unlock();

	}
}
void DrawCraneFade(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffCraneFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��
}
void SetCraneFade(CRANEFADE fade)
{
	g_fade = FADE_OUT;//�t�F�[�h�A�E�g��Ԃ�
	g_colorCraneFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//�����|���S��(����)�ɂ��Ă���
}
CRANEFADE GetCraneFade(void)
{
	return g_fade;
}