//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "ball_tutorial.h"
#include "sound.h"

// �O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureBallTutorial = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallTutorial = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallTutorial2 = NULL;
int g_nTutoCnt = 0;										// �`���[�g���A���\���J�E���^�[
float g_fAlpha1, g_fAlpha2;								// �A���t�@�l
bool g_bStart;											// �Q�[���J�n�t���O
bool g_bTutoSound;										// �J�n���̉����p
bool g_bFadeSound;										// �t�F�[�h���̉����p

// �`���[�g���A���̏���������
void InitBallTutorial(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\IamJobHoshii.png",// �e�N�X�`���̃t�@�C����
		&g_apTextureBallTutorial);

	g_nTutoCnt = 0;
	g_fAlpha1 = 255.0f;
	g_fAlpha2 = 230.0f;
	g_bStart = false;
	g_bTutoSound = false;
	g_bFadeSound = false;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallTutorial,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBallTutorial2,
		NULL);

	VERTEX_2D* pVtx;// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallTutorial->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(440.0f, 260.0f, 0.0f);// ��400.0f
	pVtx[1].pos = D3DXVECTOR3(840.0f, 260.0f, 0.0f);// ����150.0f
	pVtx[2].pos = D3DXVECTOR3(440.0f, 410.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(840.0f, 410.0f, 0.0f);
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
	g_pVtxBuffBallTutorial->Unlock();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallTutorial2->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��400.0f
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);	// ����150.0f
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 230);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 230);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 230);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 230);
	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);// (u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBallTutorial2->Unlock();
}
// �`���[�g���A���̏I������
void UninitBallTutorial(void)
{
	// �e�N�X�`���̔j��
	if (g_apTextureBallTutorial != NULL)
	{
		g_apTextureBallTutorial->Release();
		g_apTextureBallTutorial = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffBallTutorial != NULL)
	{
		g_pVtxBuffBallTutorial->Release();
		g_pVtxBuffBallTutorial = NULL;
	}

}
// �`���[�g���A���̍X�V����
void UpdateBallTutorial(void)
{
	if (g_nTutoCnt <= 60)
	{
		g_nTutoCnt++;
		if (g_bTutoSound == false)
		{
			PlaySound(SOUND_LABEL_BALLTUTO);
			g_bTutoSound = true;
		}
	}
	else if (g_nTutoCnt >= 60)
	{
		if (g_fAlpha1 > 0)
		{
			g_fAlpha1 -= (255 / 60);

			if (g_fAlpha1 < 0.0f)
			{
				g_fAlpha1 = 0.0f;
			}

		}
		if (g_fAlpha2 > 0)
		{
			g_fAlpha2 -= (230 / 60);

			if (g_fAlpha2 < 0.0f)
			{
				g_fAlpha2 = 0.0f;
			}

		}
		if (g_bFadeSound == false)
		{
			PlaySound(SOUND_LABEL_BALLFADE);
			g_bFadeSound = true;
		}
	}
	if (g_fAlpha1 <= 0.0f && g_fAlpha2 <= 0.0f)
	{
		g_bStart = true;
	}
}
// �`���[�g���A���̕`�揈��
void DrawBallTutorial(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();// �f�o�C�X�ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBallTutorial2, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallTutorial2->Lock(0, 0, (void**)&pVtx, 0);
	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, (int)g_fAlpha2);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, (int)g_fAlpha2);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, (int)g_fAlpha2);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, (int)g_fAlpha2);
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBallTutorial2->Unlock();


	// ���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBallTutorial, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureBallTutorial);
	// �w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,// �v���~�e�B�u�̎��
		0,									   // �`�悷��ŏ��̒��_�C���f�b�N�X
		2);                                    // �`�悷��v���~�e�B�u��
	
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallTutorial->Lock(0, 0, (void**)&pVtx, 0);
	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlpha1);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlpha1);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlpha1);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, (int)g_fAlpha1);
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBallTutorial->Unlock();
}
// �Q�[���J�n
bool GetStart(void)
{
	return g_bStart;
}