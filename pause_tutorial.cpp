//---------------------------------------------------------
// �|�[�Y���̑���m�F
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "pause_tutorial.h"
#include "pause.h"
#include "input.h"
#include "sound.h"

// �O���[�o��
LPDIRECT3DTEXTURE9 g_pTexturePTutorial = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPTutorial = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

// ������
void InitPTutorial(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause_tutorial.png",		// �e�N�X�`���̃t�@�C����
		&g_pTexturePTutorial);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPTutorial,
		NULL);

	VERTEX_2D* pVtx;// ���_���ւ̃|�C���^

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��1280.0f
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);	// ����720.0f
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPTutorial->Unlock();
}
// �I������
void UninitPTutorial(void)
{
	// �e�N�X�`���̔j��
	if (g_pTexturePTutorial != NULL)
	{
		g_pTexturePTutorial->Release();
		g_pTexturePTutorial = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPTutorial != NULL)
	{
		g_pVtxBuffPTutorial->Release();
		g_pVtxBuffPTutorial = NULL;
	}
}
// �X�V����
void UpdatePTutorial(void)
{
	bool bTutoDraw = GetTutoDraw();
	if (bTutoDraw == true)
	{// �`�撆
		if (GetMouseButtonTrigger(0) || JoyPadTrigger(JOYKEY_A) == true)
		{// ���N���b�N
			SetDraw(false);
			PlaySound(SOUND_LABEL_OK);
		}
	}
}
// �`�揈��
void DrawPTutorial(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^

	// �w�i
	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPTutorial, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePTutorial);
	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��
}