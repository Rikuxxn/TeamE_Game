//=======================================
//
// �G�f�B�b�g����[edit.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "block.h"
#include "input.h"
#include "meshfield.h"
#include "light.h"
#include "fade.h"
#include "camera.h"
#include <stdio.h>
#include "edit.h"

//�O���[�o���ϐ�
Editinfo g_Editinfo[MAX_BLOCK];
int g_nCntEdit;

//=============================
//�G�f�B�^�[�̏���������
//=============================
void InitEdit(void)
{

    InitBlock();

    InitMeshfield();

    InitLight();

    InitCamera();

    LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

    //�f�o�C�X�̎擾
    pDevice = GetDevice();

    for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
    {
        //������
        g_Editinfo[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
        g_Editinfo[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
        g_Editinfo[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
        g_Editinfo[nCntBlock].bUse = false;
        g_Editinfo[nCntBlock].nType = BLOCKTYPE_NORMAL;

        for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
        {
            //X�t�@�C���̓ǂݍ���
            D3DXLoadMeshFromX(BLOCK[nCnt],
                D3DXMESH_SYSTEMMEM,
                pDevice,
                NULL,
                &g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat,
                NULL,
                &g_Editinfo[nCntBlock].blockinfo[nCnt].dwNumMat,
                &g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh);


            int nNumVtx;//���_��
            DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
            BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

            //���_���̎擾
            nNumVtx = g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->GetNumVertices();

            //���_�t�H�[�}�b�g�̎擾
            sizeFVF = D3DXGetFVFVertexSize(g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->GetFVF());

            //���_�o�b�t�@�̃��b�N
            g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

            for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
            {
                //���_���W�̑��
                D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

                //���_���W���r���ă��f���̍ŏ��l�ő�l���擾
                if (vtx.x < g_Editinfo[nCntBlock].vtxMin.x)
                {
                    g_Editinfo[nCntBlock].vtxMin.x = vtx.x;
                }
                else if (vtx.y < g_Editinfo[nCntBlock].vtxMin.y)
                {
                    g_Editinfo[nCntBlock].vtxMin.y = vtx.y;
                }
                else if (vtx.z < g_Editinfo[nCntBlock].vtxMin.z)
                {
                    g_Editinfo[nCntBlock].vtxMin.z = vtx.z;
                }

                if (vtx.x > g_Editinfo[nCntBlock].vtxMax.x)
                {
                    g_Editinfo[nCntBlock].vtxMax.x = vtx.x;
                }
                else if (vtx.y > g_Editinfo[nCntBlock].vtxMax.y)
                {
                    g_Editinfo[nCntBlock].vtxMax.y = vtx.y;
                }
                else if (vtx.z > g_Editinfo[nCntBlock].vtxMax.z)
                {
                    g_Editinfo[nCntBlock].vtxMax.z = vtx.z;
                }

                //���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
                pVtxBuff += sizeFVF;
            }

            g_Editinfo[nCntBlock].size.x = (g_Editinfo[nCntBlock].vtxMax.x - g_Editinfo[nCntBlock].vtxMin.x);
            g_Editinfo[nCntBlock].size.y = (g_Editinfo[nCntBlock].vtxMax.y - g_Editinfo[nCntBlock].vtxMin.y);
            g_Editinfo[nCntBlock].size.z = (g_Editinfo[nCntBlock].vtxMax.z - g_Editinfo[nCntBlock].vtxMin.z);

            //���_�o�b�t�@�̃A�����b�N
            g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->UnlockVertexBuffer();

            D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

            //�}�e���A���f�[�^�ւ̃|�C���^���擾
            pMat = (D3DXMATERIAL*)g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat->GetBufferPointer();

            for (int nCntMat = 0; nCntMat < (int)g_Editinfo[nCntBlock].blockinfo[nCnt].dwNumMat; nCntMat++)
            {
                if (pMat[nCntMat].pTextureFilename != NULL)
                {//�e�N�X�`���t�@�C�������݂���

                    //�e�N�X�`���̓ǂݍ���
                    D3DXCreateTextureFromFile(pDevice,
                        pMat[nCntMat].pTextureFilename,
                        &g_Editinfo[nCntBlock].blockinfo[nCnt].apTexture[nCntMat]);

                }
            }

        }

    }

    g_Editinfo[0].bUse = true; // �ŏ��̃u���b�N���g�p���ɂ���
    g_nCntEdit = 0;               // �ŏ��̃C���f�b�N�X��1�ɐݒ�

}
//=============================
//�G�f�B�^�[�̏I������
//=============================
void UninitEdit(void)
{
    UninitBlock();

    UninitMeshfield();

    for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
    {
        for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
        {
            for (int nCntMat = 0; nCntMat < (int)g_Editinfo[nCntBlock].blockinfo[nCnt].dwNumMat; nCntMat++)
            {
                //�e�N�X�`���̔j��
                if (g_Editinfo[nCntBlock].blockinfo[nCnt].apTexture[nCntMat] != NULL)
                {
                    g_Editinfo[nCntBlock].blockinfo[nCnt].apTexture[nCntMat]->Release();
                    g_Editinfo[nCntBlock].blockinfo[nCnt].apTexture[nCntMat] = NULL;
                }
            }

            //���b�V���̔j��
            if (g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh != NULL)
            {
                g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->Release();
                g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh = NULL;
            }

            //�}�e���A���̔j��
            if (g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat != NULL)
            {
                g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat->Release();
                g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat = NULL;
            }
        }
    }

}
//=============================
//�G�f�B�^�[�̍X�V����
//=============================
void UpdateEdit(void)
{
    UpdateBlock();

    UpdateMeshfield();

    UpdateCamera();

    Block* pBlock = GetBlock();
    FADE g_fade = GetFade(); // ���݂̏��

    for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
    {
        for (int nCnt1 = 0; nCnt1 < MAX_BLOCK; nCnt1++)
        {
            // �L�[����ňʒu��ύX
            if (KeyboardTrigger(DIK_UP) == true)
            {
                g_Editinfo[g_nCntEdit].pos.z += 0.5f;
            }
            else if (KeyboardTrigger(DIK_DOWN) == true)
            {
                g_Editinfo[g_nCntEdit].pos.z -= 0.5f;
            }
            else if (KeyboardTrigger(DIK_LEFT) == true)
            {
                g_Editinfo[g_nCntEdit].pos.x -= 0.5f;
            }
            else if (KeyboardTrigger(DIK_RIGHT) == true)
            {
                g_Editinfo[g_nCntEdit].pos.x += 0.5f;
            }

            if (KeyboardTrigger(DIK_U) == true)
            {
                g_Editinfo[g_nCntEdit].pos.y += 0.5f;
            }
            else if (KeyboardTrigger(DIK_J) == true)
            {
                g_Editinfo[g_nCntEdit].pos.y -= 0.5f;
            }

            //// �u���b�N�^�C�v�̐؂�ւ�
            //if (GetKeyboardPress(DIK_1) == true)
            //{
            //    pBlock[nCnt].nType = BLOCKTYPE_NORMAL;
            //}

            //if (GetKeyboardPress(DIK_2) == true)
            //{
            //    pBlock[nCnt].nType = BLOCKTYPE_DOOR;
            //}

            // �u���b�N��ݒu
            if (KeyboardTrigger(DIK_RETURN) == true)
            {
                //// ���ݑI�𒆂̃u���b�N��������������
                //if (g_Editinfo[g_nCntEdit].bUse == false)
                //{
                    g_Editinfo[g_nCntEdit + 1].bUse = true; // �g�p���ɐݒ�
                    g_Editinfo[g_nCntEdit + 1].pos = g_Editinfo[g_nCntEdit].pos; // �O��̈ʒu�������p��

                    g_nCntEdit++; // ���̃C���f�b�N�X��
                    break; // ���̃��[�v���I��
                //}
            }

            //�u���b�N�̎�ޕύX
            if (KeyboardTrigger(DIK_O) == true)
            {
                g_Editinfo[g_nCntEdit + 1].nType += 1;
            }
        }
    }

    if (KeyboardTrigger(DIK_F1) == true && g_fade == FADE_NONE)
    {
        //�^�C�g����ʂɈڍs
        SetFade(MODE_TITLE);
    }

    if (KeyboardTrigger(DIK_F7) == true)
    {
        SaveBlockData();
    }
}
//=============================
//�G�f�B�^�[�̕`�揈��
//=============================
void DrawEdit(void)
{
    // �u���b�N�ƃ��b�V���t�B�[���h�̕`��
    DrawBlock();
    DrawMeshfield();

    // �J�����̐ݒ�
    SetCamera();

    LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

    //�f�o�C�X�̎擾
    pDevice = GetDevice();

    //�v�Z�p�}�g���b�N�X
    D3DXMATRIX mtxRot, mtxTrans;

    D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

    D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

    for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
    {
        for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
        {
            if (g_Editinfo[nCntBlock].bUse == true)
            {
                int nType = g_Editinfo[nCntBlock].nType;

                //���[���h�}�g���b�N�X�̏�����
                D3DXMatrixIdentity(&g_Editinfo[nCntBlock].mtxWorld);

                //�����𔽉f
                D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Editinfo[nCntBlock].rot.y, g_Editinfo[nCntBlock].rot.x, g_Editinfo[nCntBlock].rot.z);
                D3DXMatrixMultiply(&g_Editinfo[nCntBlock].mtxWorld, &g_Editinfo[nCntBlock].mtxWorld, &mtxRot);

                //�ʒu�𔽉f
                D3DXMatrixTranslation(&mtxTrans, g_Editinfo[nCntBlock].pos.x, g_Editinfo[nCntBlock].pos.y, g_Editinfo[nCntBlock].pos.z);
                D3DXMatrixMultiply(&g_Editinfo[nCntBlock].mtxWorld, &g_Editinfo[nCntBlock].mtxWorld, &mtxTrans);

                //���[���h�}�g���b�N�X��ݒ�
                pDevice->SetTransform(D3DTS_WORLD, &g_Editinfo[nCntBlock].mtxWorld);

                //���݂̃}�e���A���̎擾
                pDevice->GetMaterial(&matDef);

                //�}�e���A���f�[�^�ւ̃|�C���^���擾
                pMat = (D3DXMATERIAL*)g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat->GetBufferPointer();

                for (int nCntMat = 0; nCntMat < (int)g_Editinfo[nCntBlock].blockinfo[nCnt].dwNumMat; nCntMat++)
                {
                    //�}�e���A���̐ݒ�
                    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                    //�e�N�X�`���̐ݒ�
                    pDevice->SetTexture(0, g_Editinfo[nCntBlock].blockinfo[nCnt].apTexture[nCntMat]);

                    //���f��(�p�[�c)�̕`��
                    g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->DrawSubset(nCntMat);

                }

                //�ۑ����Ă����}�e���A����߂�
                pDevice->SetMaterial(&matDef);

            }
        }
    }

}
//=============================
//�u���b�N�̏����o������
//=============================
void SaveBlockData(void)
{
    D3DXVECTOR3 pos;
    int nType = 0;

    FILE* pFile = fopen(BLOCKPATH_1, "w");

    if (pFile != NULL)
    {

        fwrite(&g_nCntEdit, sizeof(int), 0, pFile);

        //for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
        //{
            for (int nCnt1 = 0; nCnt1 < g_nCntEdit; nCnt1++)
            {

                if (g_Editinfo[nCnt1].bUse == true)
                {

                    fprintf(pFile, "SETBLOCK\n");
                    fprintf(pFile, "POS %f %f %f\n", g_Editinfo[nCnt1].pos.x, g_Editinfo[nCnt1].pos.y, g_Editinfo[nCnt1].pos.z);
                    fprintf(pFile, "BLOCKTYPE %d\n", g_Editinfo[nCnt1].nType);
                    fprintf(pFile, "END_BLOCKSET\n");

                }

            }
        //}
        fprintf(pFile, "END_SCRIPT\n");


        //�t�@�C�������
        fclose(pFile);

    }
    else
    {
        return;
    }
}
//=============================
//�u���b�N�̓ǂݍ��ݏ���
//=============================
void LoadBlockData(void)
{
    FILE* pFile = fopen(BLOCKPATH_1, "r");

    D3DXVECTOR3 pos;
    int nType;

    switch (g_nCntEdit)
    {
    case 0:
        //�t�@�C�����J��
        pFile = fopen(BLOCKPATH_1, "r");

        break;

    default:
        pFile = NULL;

        break;
    }

    if (pFile != NULL)
    {

        while (1)
        {

            char aStr[MAX_EDITWORD];


            fscanf(pFile, "%s", &aStr[0]);


            //��v������
            if (strcmp(aStr, "SETBLOCK") == 0)
            {

                while (1)
                {

                    fscanf(pFile, "%s", &aStr[0]);



                    if (strcmp(aStr, "POS") == 0)
                    {

                        fscanf(pFile, "%f", &pos.x);
                        fscanf(pFile, "%f", &pos.y);
                        fscanf(pFile, "%f", &pos.z);

                    }
                    else if (strcmp(aStr, "BLOCKTYPE") == 0)
                    {

                        fscanf(pFile, "%d", &nType);

                    }
                    else if (strcmp(aStr, "END_BLOCKSET") == 0)
                    {

                        SetBlock(pos, nType);
                        break;

                    }

                }

            }

            if (strcmp(aStr, "END_SCRIPT") == 0)
            {
                break;
            }

        }


        //�t�@�C�������
        fclose(pFile);

        ////�u���b�N�Z�b�g�J�E���g�A�b�v
        //g_nBlockSet++;


    }
    else
    {
        return;
    }

    fclose(pFile);
}
