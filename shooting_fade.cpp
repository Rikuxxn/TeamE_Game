	#include "shooting_fade.h"


//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShootingFade = NULL;	//���_�o�b�t�@�ւ̃|�C���^
SHOOTINGFADE g_fade;									//�t�F�[�h�̏��
D3DXCOLOR g_colorShootingFade;							//�|���S��(�t�F�[�h)�̐F

void InitShootingFade(MODE modeNext)
{
	g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
	g_colorShootingFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShootingFade,
		NULL);
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShootingFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = g_colorShootingFade;
	pVtx[1].col = g_colorShootingFade;
	pVtx[2].col = g_colorShootingFade;
	pVtx[3].col = g_colorShootingFade;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShootingFade->Unlock();
}
void UninitShootingFade(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShootingFade != NULL)
	{
		g_pVtxBuffShootingFade->Release();
		g_pVtxBuffShootingFade = NULL;
	}
}
void UpdateShootingFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����
			g_colorShootingFade.a -= 0.03f;//�|���S���𓧖��ɂ��Ă���

			if (g_colorShootingFade.a <= 0.0f)
			{
				g_colorShootingFade.a = 0.0f;
				g_fade = FADE_NONE;//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorShootingFade.a += 0.03f;//�|���S����s�����ɂ��Ă���

			if (g_colorShootingFade.a >= 1.0f)
			{
				g_colorShootingFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
			}
		}

		VERTEX_2D* pVtx;//���_���ւ̃|�C���^
			
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffShootingFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorShootingFade;
		pVtx[1].col = g_colorShootingFade;
		pVtx[2].col = g_colorShootingFade;
		pVtx[3].col = g_colorShootingFade;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffShootingFade->Unlock();
	}
}
void DrawShootingFade(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffShootingFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,									   //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    //�`�悷��v���~�e�B�u��
}
void SetShootingFade(MODE modeNext)
{
	g_fade = FADE_OUT;//�t�F�[�h�A�E�g��Ԃ�
	g_colorShootingFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//�����|���S��(����)�ɂ��Ă���
}
SHOOTINGFADE GetShootingFade(void)
{
	return g_fade;
}