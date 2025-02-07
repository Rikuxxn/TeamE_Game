//=======================================
//
// ���b�V���V�����_�[����[meshcylinder.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "meshcylinder.h"
#include "block.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMeshcylinder = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshcylinder = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshcylinder = NULL;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Cylinder g_Cylinder;

//==================================
//���b�V���V�����_�[�̏���������
//==================================
void InitMeshcylinder(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Cylinder.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Cylinder.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Cylinder.bUse = false;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHCYLINDER_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshcylinder,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\cylinder.png",
		&g_pTextureMeshcylinder);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHCYLINDER_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshcylinder,
		NULL);

	VERTEX_3D* pVtx = NULL;//���_���ւ̃|�C���^

	int nCnt = 0;
	float tex = 1.0f / MESHCYLINDER_X;
	float tex2 = 1.0f / MESHCYLINDER_Z;
	int radius = 15;//���a
	D3DXVECTOR3 nor;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshcylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < MESHCYLINDER_V + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < MESHCYLINDER_H + 1; nCntH++)
		{
			float Angle = (D3DX_PI * 2.0f) / MESHCYLINDER_H * nCntH;

			pVtx[nCnt].pos = D3DXVECTOR3(sinf(Angle) * radius, MESHCYLINDER_HEIGHT * nCntV, cosf(Angle) * radius);

			nor.x = pVtx[nCnt].pos.x - 0.0f;
			nor.y = pVtx[nCnt].pos.y - 0.0f;
			nor.z = pVtx[nCnt].pos.z - 0.0f;

			//�@���̐��K��
			D3DXVec3Normalize(&pVtx[nCnt].nor, &nor);

			////�e���_�̖@���̐ݒ�
			//pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[nCnt].tex = D3DXVECTOR2(/*tex * */nCntV, /*tex2 * */nCntH);

			nCnt++;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshcylinder->Unlock();

	WORD* pIdx;//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pIdxBuffMeshcylinder->Lock(0, 0, (void**)&pIdx, 0);

	int nCntIdx3 = MESHCYLINDER_X + 1;
	int Num = 0;
	int nCntNum = 0;

	//�C���f�b�N�X�̐ݒ�
	for (int nCntIdx = 0; nCntIdx < MESHCYLINDER_Z; nCntIdx++)
	{
		for (int nCntIdx2 = 0; nCntIdx2 <= MESHCYLINDER_X; nCntIdx2++, nCntIdx3++, Num++)
		{

			pIdx[nCntNum] = nCntIdx3;

			pIdx[nCntNum + 1] = Num;

			nCntNum += 2;

		}

		//�Ō�̍s���ǂ���
		// NOTE: �Ō�̍s�ɏk�ރ|���S��������
		if (nCntIdx != MESHCYLINDER_Z - 1)
		{

			pIdx[nCntNum] = Num - 1;

			pIdx[nCntNum + 1] = nCntIdx3;

			nCntNum += 2;

		}
	}


	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshcylinder->Unlock();

}
//==================================
//���b�V���V�����_�[�̏I������
//==================================
void UninitMeshcylinder(void)
{

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshcylinder != NULL)
	{
		g_pIdxBuffMeshcylinder->Release();
		g_pIdxBuffMeshcylinder = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureMeshcylinder != NULL)
	{
		g_pTextureMeshcylinder->Release();
		g_pTextureMeshcylinder = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshcylinder != NULL)
	{
		g_pVtxBuffMeshcylinder->Release();
		g_pVtxBuffMeshcylinder = NULL;
	}

}
//==================================
//���b�V���V�����_�[�̍X�V����
//==================================
void UpdateMeshcylinder(void)
{
	Block* pBlock = GetBlock();

	bool cylinderExists = false; // ���b�V���V�����_�[���u����Ă��邩����

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (pBlock[nCnt].bUse == true && (pBlock[nCnt].nType == BLOCKTYPE_FUSE))
		{
			// �u���b�N���g���Ă��� �� ���b�V���V�����_�[��ݒu
			SetMeshcylinder(pBlock[nCnt].pos);
			cylinderExists = true;
			break; // �ŏ��Ɍ������u���b�N�̈ʒu�ɐݒu
		}
	}

	// �֘A����u���b�N���Ȃ��Ȃ����烁�b�V���V�����_�[������
	if (!cylinderExists)
	{
		g_Cylinder.bUse = false;
	}

	// Y����]
	if (g_Cylinder.bUse == true)
	{
		g_Cylinder.rot.y += D3DX_PI * 0.005f; // ��]�X�s�[�h
		if (g_Cylinder.rot.y > D3DX_PI * 2.0f)
		{
			g_Cylinder.rot.y -= D3DX_PI * 2.0f; // �p�x�� 360�� �𒴂����烊�Z�b�g
		}
	}
}
//==================================
//���b�V���V�����_�[�̕`�揈��
//==================================
void DrawMeshcylinder(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	if (g_Cylinder.bUse == true)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Cylinder.mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Cylinder.rot.y, g_Cylinder.rot.x, g_Cylinder.rot.z);
		D3DXMatrixMultiply(&g_Cylinder.mtxWorld, &g_Cylinder.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Cylinder.pos.x, g_Cylinder.pos.y, g_Cylinder.pos.z);
		D3DXMatrixMultiply(&g_Cylinder.mtxWorld, &g_Cylinder.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Cylinder.mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMeshcylinder, 0, sizeof(VERTEX_3D));

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshcylinder);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshcylinder);

		//�|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHCYLINDER_VERTEX, 0, MESHCYLINDER_PRIMITIVE);
	}
}
//==================================
//���b�V���V�����_�[�̐ݒ菈��
//==================================
void SetMeshcylinder(D3DXVECTOR3 pos)
{
	if (g_Cylinder.bUse == false)
	{
		g_Cylinder.pos = pos;
		g_Cylinder.bUse = true;
	}
}