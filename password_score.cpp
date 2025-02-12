//========================
//|�p�X���[�h			 |
//|Author:Yoshida Atsushi|
//========================
#include "password_background.h"
#include "password_game.h"
#include "password_item.h"
#include "password_score.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTexturePassword = { NULL };			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassword = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassword2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassword3 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassword4 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassword5 = NULL;
int g_nPassword, g_nPassword2, g_nPassword3, g_nPassword4;	//�p�X���[�h�̒l
bool g_bPush1, g_bPush2, g_bPush3, g_bPush4;				//�����ꂽ��
int g_nCnt;
bool g_bJudge;
Password g_aPassword[MAX_NUM_SCORE] = {};

//=========================
//|| �p�X���[�h�̏�����  ||
//=========================
void InitPassword(void)
{
	int nCntPassword;
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",//�e�N�X�`���̃t�@�C����
		&g_pTexturePassword);

	g_nPassword, g_nPassword2, g_nPassword3, g_nPassword4 = 0;
	g_bPush1 = false;
	g_bPush2 = false;
	g_bPush3 = false;
	g_bPush4 = false;
	g_nCnt = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPassword,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPassword2,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPassword3,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPassword4,
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPassword5,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;
	VERTEX_2D* pVtx2;
	VERTEX_2D* pVtx3;
	VERTEX_2D* pVtx4;
	VERTEX_2D* pVtx5;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 20.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 20.0f + 40.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 20.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 20.0f + 40.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword2->Lock(0, 0, (void**)&pVtx2, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		//���_���W�̐ݒ�
		pVtx2[0].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 34.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx2[1].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 34.0f + 40.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx2[2].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 34.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		pVtx2[3].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 34.0f + 40.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx2[0].rhw = 1.0f;
		pVtx2[1].rhw = 1.0f;
		pVtx2[2].rhw = 1.0f;
		pVtx2[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx2[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx2[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx2[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx2[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx2[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx2[1].tex = D3DXVECTOR2(0.1f, 0.0f);//(u,v)
		pVtx2[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
		pVtx2[3].tex = D3DXVECTOR2(0.1f, 1.0f);//(u,v)
		pVtx2 += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword2->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword3->Lock(0, 0, (void**)&pVtx3, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		//���_���W�̐ݒ�
		pVtx3[0].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 48.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx3[1].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 48.0f + 40.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx3[2].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 48.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		pVtx3[3].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 48.0f + 40.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx3[0].rhw = 1.0f;
		pVtx3[1].rhw = 1.0f;
		pVtx3[2].rhw = 1.0f;
		pVtx3[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx3[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx3[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx3[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx3[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx3[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx3[1].tex = D3DXVECTOR2(0.1f, 0.0f);//(u,v)
		pVtx3[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
		pVtx3[3].tex = D3DXVECTOR2(0.1f, 1.0f);//(u,v)
		pVtx3 += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword3->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword4->Lock(0, 0, (void**)&pVtx4, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		//���_���W�̐ݒ�
		pVtx4[0].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 62.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx4[1].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 62.0f + 40.0f, PASSWORDFIELD_TOP + 10.0f, 0.0f);
		pVtx4[2].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 62.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		pVtx4[3].pos = D3DXVECTOR3(PASSWORDPOS + nCntPassword * 62.0f + 40.0f, PASSWORDFIELD_TOP + 55.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx4[0].rhw = 1.0f;
		pVtx4[1].rhw = 1.0f;
		pVtx4[2].rhw = 1.0f;
		pVtx4[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx4[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx4[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx4[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx4[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx4[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx4[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx4[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx4[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx4 += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword4->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword5->Lock(0, 0, (void**)&pVtx5, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		//���_���W�̐ݒ�
		pVtx5[0].pos = D3DXVECTOR3(970.0f + nCntPassword * 62.0f, PASSWORDFIELD_TOP + 110.0f, 0.0f);
		pVtx5[1].pos = D3DXVECTOR3(970.0f + nCntPassword * 62.0f + 40.0f, PASSWORDFIELD_TOP + 110.0f, 0.0f);
		pVtx5[2].pos = D3DXVECTOR3(970.0f + nCntPassword * 62.0f, PASSWORDFIELD_TOP + 155.0f, 0.0f);
		pVtx5[3].pos = D3DXVECTOR3(970.0f + nCntPassword * 62.0f + 40.0f, PASSWORDFIELD_TOP + 155.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx5[0].rhw = 1.0f;
		pVtx5[1].rhw = 1.0f;
		pVtx5[2].rhw = 1.0f;
		pVtx5[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx5[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx5[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx5[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx5[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx5[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx5[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx5[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx5[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx5 += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword5->Unlock();

	SetPassword(0,0,false);
}
//=========================
//|| �p�X���[�h�̏I������||
//=========================
void UninitPassword(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePassword != NULL)
	{
		g_pTexturePassword->Release();
		g_pTexturePassword = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPassword != NULL)
	{
		g_pVtxBuffPassword->Release();
		g_pVtxBuffPassword = NULL;
	}
	if (g_pVtxBuffPassword2 != NULL)
	{
		g_pVtxBuffPassword2->Release();
		g_pVtxBuffPassword2 = NULL;
	}
	if (g_pVtxBuffPassword3 != NULL)
	{
		g_pVtxBuffPassword3->Release();
		g_pVtxBuffPassword3 = NULL;
	}
	if (g_pVtxBuffPassword4 != NULL)
	{
		g_pVtxBuffPassword4->Release();
		g_pVtxBuffPassword4 = NULL;
	}
	if (g_pVtxBuffPassword5 != NULL)
	{
		g_pVtxBuffPassword5->Release();
		g_pVtxBuffPassword5 = NULL;
	}
}
//=========================
//|| �p�X���[�h�̍X�V����||
//=========================
void UpdatePassword(void)
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int nData;
	int nData1 = 0;

	nData = PasswordCounter(g_nPassword);
	for (nData1 = 0; nData1 < MAX_NUM_SCORE; nData1++)
	{
		if (nData1 >= MAX_NUM_SCORE - nData)
		{
			g_aPassword[nData1].buse = true;
		}
		else
		{
			g_aPassword[nData1].buse = false;
		}
	}
}
//=========================
//|| �p�X���[�h�̕`�揈��||
//=========================
void DrawPassword(void)
{
	PASSWORDITEM* pItem = GetItem();
	VERTEX_2D* pVtx = 0;						//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	int nCntPassword;

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPassword, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (g_aPassword[nCntPassword].buse == true)
		{
			if (g_bPush1 == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexturePassword);
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
					nCntPassword * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
					2);										//�`�悷��v���~�e�B�u��
			}
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword->Unlock();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPassword2, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword2->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (g_aPassword[nCntPassword].buse == true)
		{
			if (g_bPush2 == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexturePassword);
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
					nCntPassword * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
					2);										//�`�悷��v���~�e�B�u��
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword2->Unlock();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPassword3, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword3->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (g_aPassword[nCntPassword].buse == true)
		{
			if (g_bPush3 == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexturePassword);
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
					nCntPassword * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
					2);										//�`�悷��v���~�e�B�u��
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword3->Unlock();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPassword4, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword4->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (g_aPassword[nCntPassword].buse == true)
		{
			if (g_bPush4 == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexturePassword);
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
					nCntPassword * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
					2);										//�`�悷��v���~�e�B�u��
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword4->Unlock();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffPassword5, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword5->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (g_aPassword[nCntPassword].buse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePassword);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntPassword * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);										//�`�悷��v���~�e�B�u��
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword5->Unlock();
}
//=========================
//|| �p�X���[�h�̐ݒ菈��||
//=========================
void SetPassword(int nPass, int nA, bool bAnswer)
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int aPosTexU[MAX_NUM_SCORE] = {};//�e���̐������i�[
	int aPosTexU2[MAX_NUM_SCORE] = {};
	int aPosTexU3[MAX_NUM_SCORE] = {};
	int aPosTexU4[MAX_NUM_SCORE] = {};
	int nCntPassword;
	int n = 1000;
	int n1 = 100;
	int nAnum = 0;
	g_bJudge = false;
	aPosTexU[0] = 0;
	aPosTexU2[0] = 0;
	aPosTexU3[0] = 0;
	aPosTexU4[0] = 0;
	bool bA = bAnswer;
	if (bA == true)
	{
		nAnum = nA;
		
	}
	else if (bA == false)
	{
		g_nPassword = nPass;
		g_nPassword2 = nPass;
		g_nPassword3 = nPass;
		g_nPassword4 = nPass;
	}
	g_nCnt = 0;
	g_bPush1 = GetReset();
	g_bPush2 = GetReset();
	g_bPush3 = GetReset();
	g_bPush4 = GetReset();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (nCntPassword == 0)
		{
			aPosTexU[0] = g_nPassword / n;
		}
		else
		{
			aPosTexU[nCntPassword] = g_nPassword % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword->Unlock();

	n = 1000;
	n1 = 100;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword2->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (nCntPassword == 0)
		{
			aPosTexU2[0] = g_nPassword2 / n;
		}
		else
		{
			aPosTexU2[nCntPassword] = g_nPassword2 % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU2[nCntPassword]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU2[nCntPassword]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU2[nCntPassword]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU2[nCntPassword]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword2->Unlock();

	n = 1000;
	n1 = 100;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword3->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (nCntPassword == 0)
		{
			aPosTexU3[0] = g_nPassword3 / n;
		}
		else
		{
			aPosTexU3[nCntPassword] = g_nPassword3 % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU3[nCntPassword]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU3[nCntPassword]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU3[nCntPassword]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU3[nCntPassword]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword3->Unlock();

	n = 1000;
	n1 = 100;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword4->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (nCntPassword == 0)
		{
			aPosTexU4[0] = g_nPassword4 / n;
		}
		else
		{
			aPosTexU4[nCntPassword] = g_nPassword4 % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU4[nCntPassword]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU4[nCntPassword]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU4[nCntPassword]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU4[nCntPassword]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword4->Unlock();

	n = 1000;
	n1 = 100;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPassword5->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
	{
		if (nCntPassword == 0)
		{
			aPosTexU4[0] = nAnum / n;
		}
		else
		{
			aPosTexU4[nCntPassword] = nAnum % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU4[nCntPassword]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU4[nCntPassword]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU4[nCntPassword]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU4[nCntPassword]), 1.0f);//(u,v)
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPassword5->Unlock();
}
//=========================
//|| �p�X���[�h�̉��Z����||
//=========================
void AddPassword(int nValue)
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int nCntPassword;
	int aPosTexU[MAX_NUM_SCORE] = {};//�e���̐������i�[
	int n = 1000;
	int n1 = 100;
	aPosTexU[0] = {};
	g_nCnt++;
	switch (g_nCnt)
	{
	case 1:
		g_nPassword = nValue;
		g_bPush1 = true;
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);
		for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
		{
			if (nCntPassword == 0)
			{
				aPosTexU[0] = g_nPassword / n;
			}
			else
			{
				aPosTexU[nCntPassword] = g_nPassword % n / n1;
				n = n / 10;
				n1 = n1 / 10;
			}
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPassword->Unlock();
		break;
	case 2:
		g_nPassword2 = nValue;
		g_bPush2 = true;
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPassword2->Lock(0, 0, (void**)&pVtx, 0);
		for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
		{
			if (nCntPassword == 0)
			{
				aPosTexU[0] = g_nPassword2 / n;
			}
			else
			{
				aPosTexU[nCntPassword] = g_nPassword2 % n / n1;
				n = n / 10;
				n1 = n1 / 10;
			}
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPassword2->Unlock();
		break;
	case 3:
		g_nPassword3 = nValue;
		g_bPush3 = true;
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPassword3->Lock(0, 0, (void**)&pVtx, 0);
		for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
		{
			if (nCntPassword == 0)
			{
				aPosTexU[0] = g_nPassword3 / n;
			}
			else
			{
				aPosTexU[nCntPassword] = g_nPassword3 % n / n1;
				n = n / 10;
				n1 = n1 / 10;
			}
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPassword3->Unlock();
		break;
	case 4:
		g_nPassword4 = nValue;
		g_bPush4 = true;
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPassword4->Lock(0, 0, (void**)&pVtx, 0);
		for (nCntPassword = 0; nCntPassword < MAX_NUM_SCORE; nCntPassword++)
		{
			if (nCntPassword == 0)
			{
				aPosTexU[0] = g_nPassword4 / n;
			}
			else
			{
				aPosTexU[nCntPassword] = g_nPassword4 % n / n1;
				n = n / 10;
				n1 = n1 / 10;
			}
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 0.0f);//(u,v)
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntPassword]), 1.0f);//(u,v)
			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPassword4->Unlock();
		break;
	default:
		/*���𗬂�*/
		break;
	}

}
//=====================
//�X�R�A��0���J�E���g
//=====================
int PasswordCounter(int nPass)
{
	int nNum = nPass;//�X�R�A�̂O�̕������J�E���g
	int nKeepNum = 0;//�X�R�A�̌���

	while (nNum != 0)//����؂�Ȃ��Ȃ�܂ŌJ��Ԃ�(�O�܂�)
	{
		nNum /= 10;//nNum��10�Ŋ����Ă���
		nKeepNum++;//���������Z
	}
	if (nPass == 0)
	{
		//1���ڂ�0�������Ă���Ƃ�
		nKeepNum = 1;
	}
	return nKeepNum;//�X�R�A�̌�����Ԃ�
}
//=========================
//||  �p�X���[�h�̎擾   ||
//=========================
int GetPassword(void)
{
	return g_nPassword;
}
int GetPassword2(void)
{
	return g_nPassword2;
}
int GetPassword3(void)
{
	return g_nPassword3;
}
int GetPassword4(void)
{
	return g_nPassword4;
}
bool GetPush1(void)
{
	return g_bPush1;
}
bool GetPush2(void)
{
	return g_bPush2;
}
bool GetPush3(void)
{
	return g_bPush3;
}
bool GetPush4(void)
{
	return g_bPush4;
}
int GetCntCounter(void)
{
	return g_nCnt;
}
bool GetJudge(void)
{
	return g_bJudge;
}