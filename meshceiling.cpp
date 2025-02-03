//=======================================
//
// ���b�V���V�[�����O����[meshceiling.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "meshceiling.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMeshCeiling = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCeiling = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCeiling = NULL;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3 g_posMeshCeiling;//�ʒu
D3DXVECTOR3 g_rotMeshCeiling;//����
D3DXMATRIX g_mtxWorldMeshCeiling;//���[���h�}�g���b�N�X

//==================================
//���b�V���t�B�[���h�̏���������
//==================================
void InitMeshCeiling(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_posMeshCeiling = D3DXVECTOR3(0.0f, 260.0f, 0.0f);
	g_rotMeshCeiling = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX_CEILING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCeiling,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall001.jpg",
		&g_pTextureMeshCeiling);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_INDEX_CEILING,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCeiling,
		NULL);

	VERTEX_3D* pVtx = NULL;//���_���ւ̃|�C���^

	int nCnt = 0;
	float tex = 23.0f / MESHCEILING_X;

	float tex2 = 23.0f / MESHCEILING_Z;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshCeiling->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 <= MESHCEILING_Z; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHCEILING_X; nCnt2++)
		{

			pVtx[nCnt].pos = D3DXVECTOR3(0.0f + ((MAX_WIDTH_CEILING / MESHCEILING_X) * nCnt2) - (MAX_WIDTH_CEILING * 0.5f),
				0.0f,
				MAX_HEIGHT_CEILING - ((MAX_HEIGHT_CEILING / MESHCEILING_Z) * nCnt1) - (MAX_HEIGHT_CEILING * 0.5f));

			//�e���_�̖@���̐ݒ�
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[nCnt].tex = D3DXVECTOR2(tex * nCnt2, tex2 * nCnt1);

			nCnt++;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshCeiling->Unlock();

	WORD* pIdx;//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pIdxBuffMeshCeiling->Lock(0, 0, (void**)&pIdx, 0);

	int nCntIdx3 = MESHCEILING_X + 1;
	int Num = 0;
	int nCntNum = 0;

	for (int nCntIdx = 0; nCntIdx < MESHCEILING_Z; nCntIdx++)
	{
		for (int nCntIdx2 = 0; nCntIdx2 <= MESHCEILING_X; nCntIdx2++, nCntIdx3++, Num++)
		{

			pIdx[nCntNum] = nCntIdx3;

			pIdx[nCntNum + 1] = Num;

			nCntNum += 2;

		}

		//�Ō�̍s���ǂ���
		// NOTE: �Ō�̍s�ɏk�ރ|���S��������
		if (nCntIdx != MESHCEILING_Z - 1)
		{

			pIdx[nCntNum] = Num - 1;

			pIdx[nCntNum + 1] = nCntIdx3;

			nCntNum += 2;

		}

	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshCeiling->Unlock();

}
//==================================
//���b�V���t�B�[���h�̏I������
//==================================
void UninitMeshCeiling(void)
{

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshCeiling != NULL)
	{
		g_pIdxBuffMeshCeiling->Release();
		g_pIdxBuffMeshCeiling = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureMeshCeiling != NULL)
	{
		g_pTextureMeshCeiling->Release();
		g_pTextureMeshCeiling = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshCeiling != NULL)
	{
		g_pVtxBuffMeshCeiling->Release();
		g_pVtxBuffMeshCeiling = NULL;
	}

}
//==================================
//���b�V���t�B�[���h�̍X�V����
//==================================
void UpdateMeshCeiling(void)
{



}
//==================================
//���b�V���t�B�[���h�̕`�揈��
//==================================
void DrawMeshCeiling(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	// �J�����O�ݒ�𖳌���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshCeiling);

	////�����𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCeiling.y, g_rotMeshCeiling.x, g_rotMeshCeiling.z);
	//D3DXMatrixMultiply(&g_mtxWorldMeshCeiling, &g_mtxWorldMeshCeiling, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCeiling.x, g_posMeshCeiling.y, g_posMeshCeiling.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCeiling, &g_mtxWorldMeshCeiling, &mtxTrans);

	//���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCeiling);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCeiling, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshCeiling);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshCeiling);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_VERTEX_CEILING, 0, MAX_PRIMITIVE_CEILING);

	// �J�����O�ݒ��L����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}
