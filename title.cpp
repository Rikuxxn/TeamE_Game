//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
//#include "sound.h"


//�}�N����`
#define NUM_TITLE (3)//�^�C�g����


//�^�C�g���̎�ނ̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	int nType;
	float fHeight;//����
	float fWidth;//��
	TITLESTATE state;//���
	bool bEnterTitle;
	bool bUse;//�g�p���
}Title;


//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//���_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleback = NULL;//�^�C�g���w�i

LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLE] = {};//�e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitleback = NULL;//�^�C�g���w�i�e�N�X�`���̃|�C���^

Title g_aTitle[NUM_TITLE];//�^�C�g���\���̂̏��
TITLE g_Title;//�^�C�g���񋓌^�̏��

int g_nCntTitleAnim;//�^�C�g�����
int g_nCntTitleAnim2;//�^�C�g�����

int g_nPatternAnim;//��ԃp�^�[��
int g_aTimeCount;//�^�C���J�E���g


//==================
//�^�C�g���̏�����
//==================
void InitTitle(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^


	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	VERTEX_2D* pVtx;//���_���̃|�C���^


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\titleBG.png",
		&g_pTextureTitleback);


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gametitle.png",
		&g_pTextureTitle[0]);


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enter.png",
		&g_pTextureTitle[1]);


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\second.png",
		&g_pTextureTitle[2]);


	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		g_aTitle[nCntTitle].move = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aTitle[nCntTitle].nType = 0;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].bEnterTitle = true;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].state = TITLE_NONE;//�������Ă��Ȃ����
	}


	g_nCntTitleAnim = 0;//�^�C�g�����
	g_nCntTitleAnim2 = 0;//�^�C�g�����
	g_nPatternAnim = 0;//��ԃp�^�[��
	g_aTimeCount = 0;//������

    //==================
    //�^�C�g���w�i
    //==================

	//���_�o�b�t�@�̐��� �w�i
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleback,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleback->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//1�ڂ̒��_���
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);//2�ڂ̒��_���
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);//3�ڂ̒��_���
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);//4�ڂ̒��_���

	//rhw�̐ݒ�(1.0f�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,0.6f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,0.6f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,0.6f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,0.6f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	g_pVtxBuffTitleback->Unlock();

	//==================
	//�^�C�g���`��
	//==================

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLE,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//1�ڂ̒��_���
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//2�ڂ̒��_���
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//3�ڂ̒��_���
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//4�ڂ̒��_���

		//rhw�̐ݒ�(1.0f�ŌŒ�)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}


	SetTitle(TITLE_FIRST, D3DXVECTOR3(620.0f, 230.0f, 0.0f));//�^�C�g��1
	SetTitle(TITLE_SECOND, D3DXVECTOR3(640.0f, 600.0f, 0.0f));//�^�C�g��2
	//SetTitle(TITLE_TWO, D3DXVECTOR3(980.0f, 350.0f, 0.0f));//2

	//�A�����b�N
	g_pVtxBuffTitle->Unlock();

	//PlaySound(SOUND_LABEL_BGM);

}
//==================
//�^�C�g���̏I��
//==================
void UninitTitle(void)
{

	////�T�E���h�̒�~
	//StopSound(SOUND_LABEL_BGM);
	//StopSound(SOUND_LABEL_ENTER);


	//==================
	//�^�C�g���̔w�i
	//==================

	//�e�N�X�`���̔j��
	if (g_pTextureTitleback != NULL)
	{
		g_pTextureTitleback->Release();
		g_pTextureTitleback = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitleback != NULL)
	{
		g_pVtxBuffTitleback->Release();
		g_pVtxBuffTitleback = NULL;
	}

	//==================
	//�^�C�g��
	//==================

	//�e�N�X�`���̔j��
	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{

		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}
//==================
//�^�C�g���̍X�V
//==================
void UpdateTitle(void)
{

	FADE g_fade = GetFade(); // ���݂̏��

	VERTEX_2D* pVtx = 0;     // ���_���̃|�C���^

	static float alpha = 0.0f;			// �A���t�@�l
	static bool bIncreasing = true;		// �A���t�@�l�����������ǂ���

	// �A���t�@�l�𑝌������郍�W�b�N
	if (bIncreasing)
	{
		alpha += 0.02f; // ����
		if (alpha >= 1.0f)
		{
			alpha = 1.0f;
			bIncreasing = false; // �����ɐ؂�ւ���
		}
	}
	else
	{
		alpha -= 0.02f; // ����
		if (alpha <= 0.0f)
		{
			alpha = 0.0f;
			bIncreasing = true; // �����ɐ؂�ւ���
		}
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{

		if (g_aTitle[nCntTitle].nType == TITLE_SECOND)
		{
			// ���_�J���[�̃A���t�@�l��ݒ�
			D3DXCOLOR color(1.0f, 1.0f, 1.0f, alpha);

			pVtx[0].col = color;
			pVtx[1].col = color;
			pVtx[2].col = color;
			pVtx[3].col = color;
		}

		if (g_aTitle[nCntTitle].bEnterTitle == true && g_fade == FADE_NONE && (KeyboardTrigger(DIK_RETURN) == true || JoyPadTrigger(JOYKEY_A) == true))
		{
			alpha = 0.0f;

			//PlaySound(SOUND_LABEL_ENTER);

			//Enter�L�[�������ꂽ
			for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
			{
				if (g_aTitle[nCntTitle].bUse == true && g_aTitle[nCntTitle].nType == TITLE_SECOND)
				{
					g_aTitle[nCntTitle].state = TITLE_FLASH;
				}
			}

			g_aTitle[nCntTitle].bEnterTitle = false;

			//���[�h�ݒ�(�Q�[����ʂɈړ�)
			SetFade(MODE_GAME);

		}

		TitleFlash(TITLE_SECOND);//�v���X�G���^�[�̓_��

		// ���̒��_�Ɉړ�
		pVtx += 4;
	}

	if (KeyboardTrigger(DIK_F1) == true && g_fade == FADE_NONE)
	{
		//�G�f�B�b�g��ʂɈڍs
		SetFade(MODE_EDIT);
	}

	// �A�����b�N
	g_pVtxBuffTitle->Unlock();
}
//==================
//�^�C�g���̕`��
//==================
void DrawTitle(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//==================
	//�^�C�g���w�i�̕`��
	//==================

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleback, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleback);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    //==================
    //�^�C�g���̕`��
    //==================

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[g_aTitle[nCntTitle].nType]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}

}
//======================
//�^�C�g���̐ݒ菈��
//======================
void SetTitle(int nType, D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == false)
		{
			g_aTitle[nCntTitle].nType = nType;
			g_aTitle[nCntTitle].pos = pos;
			g_aTitle[nCntTitle].bUse = true;

			//�ꍇ����
			switch (nType)
			{
			case TITLE_FIRST:

				g_aTitle[nCntTitle].fHeight = 450.0f;//����
				g_aTitle[nCntTitle].fWidth = 850.0f;//����
				break;

			case TITLE_SECOND:

				g_aTitle[nCntTitle].fHeight = 70.0f;//����
				g_aTitle[nCntTitle].fWidth = 670.0f; //����
				break;

			case TITLE_TWO:

				g_aTitle[nCntTitle].fHeight = 160.0f;//����
				g_aTitle[nCntTitle].fWidth = 130.0f; //����
				break;

			}

			//���_���W1�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//1�ڂ̒��_���
			pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//2�ڂ̒��_���
			pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//3�ڂ̒��_���
			pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//4�ڂ̒��_���

			break;
		}

		pVtx += 4;
	}

	//�A�����b�N
	g_pVtxBuffTitle->Unlock();
}
//==============================
//�^�C�g���̓_��
//==============================
void TitleFlash(int nType)
{
	VERTEX_2D* pVtx = 0;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == true && g_aTitle[nCntTitle].state == TITLE_FLASH)
		{
			g_nCntTitleAnim++;//�J�E���^�[�����Z

			if (g_nCntTitleAnim == 2)//5�̎�
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);

			}

			else if (g_nCntTitleAnim == 7)//10�̎�
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				g_nCntTitleAnim = 0;//�����l�ɖ߂�
			}
		}
		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffTitle->Unlock();

}



