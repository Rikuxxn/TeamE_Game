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
#include "meshcylinder.h"

//�O���[�o���ϐ�
Editinfo g_Editinfo[MAX_BLOCK];
BlockTex blockTex[BLOCKTYPE_MAX];

int g_nCntEdit;

//=============================
//�G�f�B�^�[�̏���������
//=============================
void InitEdit(void)
{

    // �J�[�\�����\���ɂ���
    SetCursorVisibility(false);


    // �u���b�N�̏���������
    InitBlock();

    // ���b�V���t�B�[���h�̏���������
    InitMeshfield();

    // ���b�V���V�����_�[�̏���������
    InitMeshcylinder();

    // ���C�g�̏���������
    InitLight();

    // �J�����̏���������
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
        g_Editinfo[nCntBlock].nType = BLOCKTYPE_WALL;
    }

    for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
    {
        //X�t�@�C���̓ǂݍ���
        D3DXLoadMeshFromX(BLOCK[nCnt],
            D3DXMESH_SYSTEMMEM,
            pDevice,
            NULL,
            &blockTex[nCnt].pBuffMat,
            NULL,
            &blockTex[nCnt].dwNumMat,
            &blockTex[nCnt].pMesh);
    }


    for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
    {

        D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

        //�}�e���A���f�[�^�ւ̃|�C���^���擾
        pMat = (D3DXMATERIAL*)blockTex[nCnt].pBuffMat->GetBufferPointer();

        for (int nCntMat = 0; nCntMat < (int)blockTex[nCnt].dwNumMat; nCntMat++)
        {
            if (pMat[nCntMat].pTextureFilename != NULL)
            {//�e�N�X�`���t�@�C�������݂���

                //�e�N�X�`���̓ǂݍ���
                D3DXCreateTextureFromFile(pDevice,
                    pMat[nCntMat].pTextureFilename,
                    &blockTex[nCnt].apTexture[nCntMat]);

            }
        }
    }

    g_Editinfo[0].bUse = true; // �ŏ��̃u���b�N���g�p���ɂ���
    g_Editinfo[0].blockTex[0] = blockTex[0];
    g_nCntEdit = 0;

}
//=============================
//�G�f�B�^�[�̏I������
//=============================
void UninitEdit(void)
{
    // �u���b�N�̏I������
    UninitBlock();

    //���b�V���t�B�[���h�̏I������
    UninitMeshfield();

    //���b�V���V�����_�[�̏I������
    UninitMeshcylinder();

    for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
    {
        for (int nCntMat = 0; nCntMat < (int)blockTex[nCnt].dwNumMat; nCntMat++)
        {
            //�e�N�X�`���̔j��
            if (blockTex[nCnt].apTexture[nCntMat] != NULL)
            {
                blockTex[nCnt].apTexture[nCntMat]->Release();
                blockTex[nCnt].apTexture[nCntMat] = NULL;
            }
        }

        //���b�V���̔j��
        if (blockTex[nCnt].pMesh != NULL)
        {
            blockTex[nCnt].pMesh->Release();
            blockTex[nCnt].pMesh = NULL;
        }

        //�}�e���A���̔j��
        if (blockTex[nCnt].pBuffMat != NULL)
        {
            blockTex[nCnt].pBuffMat->Release();
            blockTex[nCnt].pBuffMat = NULL;
        }
    }

}
//=============================
//�G�f�B�^�[�̍X�V����
//=============================
void UpdateEdit(void)
{
    // �u���b�N�̍X�V����
    UpdateBlock();

    // ���b�V���t�B�[���h�̍X�V����
    UpdateMeshfield();

    // ���b�V���V�����_�[�̍X�V����
    UpdateMeshcylinder();

    // �J�����̍X�V����
    UpdateCamera();

    Block* pBlock = GetBlock();     // �u���b�N���
    FADE g_fade = GetFade();        // ���݂̏��
    Camera* pCamera = GetCamera();


    // �u���b�N�̈ʒu��ύX
    if (KeyboardTrigger(DIK_UP) == true)
    {
        g_Editinfo[g_nCntEdit].pos.z += 10.0f;
    }
    else if (KeyboardTrigger(DIK_DOWN) == true)
    {
        g_Editinfo[g_nCntEdit].pos.z -= 10.0f;
    }
    else if (KeyboardTrigger(DIK_LEFT) == true)
    {
        g_Editinfo[g_nCntEdit].pos.x -= 10.0f;
    }
    else if (KeyboardTrigger(DIK_RIGHT) == true)
    {
        g_Editinfo[g_nCntEdit].pos.x += 10.0f;
    }
    else if (KeyboardTrigger(DIK_U) == true)
    {
        g_Editinfo[g_nCntEdit].pos.y += 10.0f;
    }
    else if (KeyboardTrigger(DIK_J) == true)
    {
        g_Editinfo[g_nCntEdit].pos.y -= 10.0f;
    }


    //�u���b�N����]����
    if (KeyboardTrigger(DIK_Y) == true)
    {
        g_Editinfo[g_nCntEdit].rot.y += D3DX_PI / 2;
    }
    else if (KeyboardTrigger(DIK_H) == true)
    {
        g_Editinfo[g_nCntEdit].rot.y -= D3DX_PI / 2;
    }

    // �u���b�N��ݒu
    if (KeyboardTrigger(DIK_RETURN) == true)
    {
        g_Editinfo[g_nCntEdit + 1].pos = g_Editinfo[g_nCntEdit].pos;
        //g_Editinfo[g_nCntEdit + 1].rot = g_Editinfo[g_nCntEdit].rot;
        g_Editinfo[g_nCntEdit + 1].bUse = true; // �g�p���ɐݒ�
        g_Editinfo[g_nCntEdit + 1].blockTex[0] = blockTex[0];
        
        g_nCntEdit++; // ���̃C���f�b�N�X��
        g_Editinfo[g_nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // ��]�����Z�b�g
    }
    else if (GetMouseButtonTrigger(0))
    {
        g_Editinfo[g_nCntEdit + 1].pos = g_Editinfo[g_nCntEdit].pos;
        //g_Editinfo[g_nCntEdit + 1].rot = g_Editinfo[g_nCntEdit].rot;
        g_Editinfo[g_nCntEdit + 1].bUse = true; // �g�p���ɐݒ�
        g_Editinfo[g_nCntEdit + 1].blockTex[0] = blockTex[0];

        g_nCntEdit++; // ���̃C���f�b�N�X��
        g_Editinfo[g_nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // ��]�����Z�b�g
    }

    int MouseWheel = GetMouseWheel();

    //�u���b�N�̎�ޕύX
    if (MouseWheel > 0 && g_Editinfo[g_nCntEdit].nType < BLOCKTYPE_MAX - 1)//��ɃX�N���[��
    {
        g_Editinfo[g_nCntEdit].nType++;

        g_Editinfo[g_nCntEdit].blockTex[g_Editinfo[g_nCntEdit].nType] = blockTex[g_Editinfo[g_nCntEdit].nType];
    }
    else if (MouseWheel < 0 && g_Editinfo[g_nCntEdit].nType > 0)//���ɃX�N���[��
    {
        g_Editinfo[g_nCntEdit].nType--;

        g_Editinfo[g_nCntEdit].blockTex[g_Editinfo[g_nCntEdit].nType] = blockTex[g_Editinfo[g_nCntEdit].nType];
    }
    if (KeyboardTrigger(DIK_O) == true && g_Editinfo[g_nCntEdit].nType < BLOCKTYPE_MAX - 1)
    {
        g_Editinfo[g_nCntEdit].nType++;

        g_Editinfo[g_nCntEdit].blockTex[g_Editinfo[g_nCntEdit].nType] = blockTex[g_Editinfo[g_nCntEdit].nType];
    }
    else if (KeyboardTrigger(DIK_L) == true && g_Editinfo[g_nCntEdit].nType > 0)
    {
        g_Editinfo[g_nCntEdit].nType--;

        g_Editinfo[g_nCntEdit].blockTex[g_Editinfo[g_nCntEdit].nType] = blockTex[g_Editinfo[g_nCntEdit].nType];
    }


    // ���K������
    if (g_Editinfo[g_nCntEdit].rot.y > D3DX_PI) 
    {
        g_Editinfo[g_nCntEdit].rot.y -= D3DX_PI * 2.0f;
    }
    if (g_Editinfo[g_nCntEdit].rot.y < -D3DX_PI) 
    {
        g_Editinfo[g_nCntEdit].rot.y += D3DX_PI * 2.0f;
    }

    // �K�v�ɉ����đ��̎������K��
    if (g_Editinfo[g_nCntEdit].rot.x > D3DX_PI) 
    {
        g_Editinfo[g_nCntEdit].rot.x -= D3DX_PI * 2.0f;
    }
    if (g_Editinfo[g_nCntEdit].rot.x < -D3DX_PI) 
    {
        g_Editinfo[g_nCntEdit].rot.x += D3DX_PI * 2.0f;
    }

    if (g_Editinfo[g_nCntEdit].rot.z > D3DX_PI) 
    {
        g_Editinfo[g_nCntEdit].rot.z -= D3DX_PI * 2.0f;
    }
    if (g_Editinfo[g_nCntEdit].rot.z < -D3DX_PI) 
    {
        g_Editinfo[g_nCntEdit].rot.z += D3DX_PI * 2.0f;
    }


    //�u���b�N�̍폜
    if (KeyboardTrigger(DIK_DELETE) == true && !g_nCntEdit == 0)
    {
        g_Editinfo[g_nCntEdit].bUse = false;
        g_nCntEdit--;
    }


    if (KeyboardTrigger(DIK_F1) == true && g_fade == FADE_NONE)
    {
        //�^�C�g����ʂɈڍs
        SetFade(MODE_TITLE);
    }

    // �u���b�N�ݒu�̏���ۑ�
    if (KeyboardTrigger(DIK_F7) == true)
    {
        SaveBlockData();
    }
    // �ǐݒu�̏���ۑ�
    else if (KeyboardTrigger(DIK_F2) == true)
    {
        SaveWallData();
    }
    // �^�C�g���p�̔z�u����ۑ�
    else if (KeyboardTrigger(DIK_F3) == true)
    {
        SaveTitleData();
    }



    // �u���b�N�ݒu�̏���ǂݍ���
    if (KeyboardTrigger(DIK_F6) == true)
    {
        LoadBlockData();
    }
    // �ǐݒu�̏���ǂݍ���
    else if (KeyboardTrigger(DIK_F3) == true)
    {
        LoadWallData();
    }

}
//=============================
//�G�f�B�^�[�̕`�揈��
//=============================
void DrawEdit(void)
{
    // �u���b�N�̕`��
    DrawBlock();

    //���b�V���t�B�[���h�̕`��
    DrawMeshfield();

    //���b�V���V�����_�[�̕`��
    DrawMeshcylinder();

    // �J�����̐ݒ�
    SetCamera();

    LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

    //�f�o�C�X�̎擾
    pDevice = GetDevice();

    //�v�Z�p�}�g���b�N�X
    D3DXMATRIX mtxRot, mtxTrans;

    D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

    D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

    for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
    {
        if (g_Editinfo[nCntBlock].bUse == true)
        {
            int nType = g_Editinfo[nCntBlock].nType;

            // ���[���h�}�g���b�N�X�̏�����
            D3DXMatrixIdentity(&g_Editinfo[nCntBlock].mtxWorld);

            // �����𔽉f
            D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Editinfo[nCntBlock].rot.y, g_Editinfo[nCntBlock].rot.x, g_Editinfo[nCntBlock].rot.z);
            D3DXMatrixMultiply(&g_Editinfo[nCntBlock].mtxWorld, &g_Editinfo[nCntBlock].mtxWorld, &mtxRot);

            // �ʒu�𔽉f
            D3DXMatrixTranslation(&mtxTrans, g_Editinfo[nCntBlock].pos.x, g_Editinfo[nCntBlock].pos.y, g_Editinfo[nCntBlock].pos.z);
            D3DXMatrixMultiply(&g_Editinfo[nCntBlock].mtxWorld, &g_Editinfo[nCntBlock].mtxWorld, &mtxTrans);

            // ���[���h�}�g���b�N�X��ݒ�
            pDevice->SetTransform(D3DTS_WORLD, &g_Editinfo[nCntBlock].mtxWorld);

            // ���݂̃}�e���A���̎擾
            pDevice->GetMaterial(&matDef);

            for (int nCntMat = 0; nCntMat < (int)g_Editinfo[nCntBlock].blockTex[nType].dwNumMat; nCntMat++) 
            {
                // �}�e���A���f�[�^�ւ̃|�C���^���擾
                pMat = (D3DXMATERIAL*)g_Editinfo[nCntBlock].blockTex[nType].pBuffMat->GetBufferPointer();

                D3DXMATERIAL color;

                color = pMat[nCntMat];

                // �I�𒆂̃u���b�N�𔼓����ɂ���
                if (nCntBlock == g_nCntEdit)
                {

                    color.MatD3D.Diffuse.r = 1.0f;
                    color.MatD3D.Diffuse.g = 1.0f;
                    color.MatD3D.Diffuse.b = 1.0f;
                    color.MatD3D.Diffuse.a = 0.6f;

                    // �}�e���A���̐ݒ�
                    pDevice->SetMaterial(&color.MatD3D);

                }
                else
                {
                    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
                }

                // �e�N�X�`���̐ݒ�
                pDevice->SetTexture(0, g_Editinfo[nCntBlock].blockTex[nType].apTexture[nCntMat]);

                // ���f��(�p�[�c)�̕`��
                g_Editinfo[nCntBlock].blockTex[nType].pMesh->DrawSubset(nCntMat);
            }

            // �ۑ����Ă����}�e���A����߂�
            pDevice->SetMaterial(&matDef);
        }
    }

}
//======================================
//�u���b�N(�I�u�W�F�N�g)�̏����o������
//======================================
void SaveBlockData(void)
{
    D3DXVECTOR3 pos;
    int nType = 0;

    FILE* pFile = fopen(BLOCKPATH_1, "w");

    if (pFile != NULL)
    {

        fwrite(&g_nCntEdit, sizeof(int), 0, pFile);

        for (int nCnt1 = 0; nCnt1 < g_nCntEdit; nCnt1++)
        {

            if (g_Editinfo[nCnt1].bUse == true)
            {

                fprintf(pFile, "SETBLOCK\n");
                fprintf(pFile, "POS %.1f %.1f %.1f\n", g_Editinfo[nCnt1].pos.x, g_Editinfo[nCnt1].pos.y, g_Editinfo[nCnt1].pos.z);
                fprintf(pFile, "ROT %.2f %.2f %.2f\n", g_Editinfo[nCnt1].rot.x, g_Editinfo[nCnt1].rot.y, g_Editinfo[nCnt1].rot.z);
                fprintf(pFile, "BLOCKTYPE %d\n", g_Editinfo[nCnt1].nType);
                fprintf(pFile, "END_BLOCKSET\n");
                fprintf(pFile, "================\n");

            }

        }

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
//�ǂ̏����o������
//=============================
void SaveWallData(void)
{
    D3DXVECTOR3 pos;
    int nType = 0;

    FILE* pFile = fopen(WALLPATH_1, "w");

    if (pFile != NULL)
    {

        fwrite(&g_nCntEdit, sizeof(int), 0, pFile);

        for (int nCnt1 = 0; nCnt1 < g_nCntEdit; nCnt1++)
        {

            if (g_Editinfo[nCnt1].bUse == true)
            {

                fprintf(pFile, "SETBLOCK\n");
                fprintf(pFile, "POS %.1f %.1f %.1f\n", g_Editinfo[nCnt1].pos.x, g_Editinfo[nCnt1].pos.y, g_Editinfo[nCnt1].pos.z);
                fprintf(pFile, "ROT %.2f %.2f %.2f\n", g_Editinfo[nCnt1].rot.x, g_Editinfo[nCnt1].rot.y, g_Editinfo[nCnt1].rot.z);
                fprintf(pFile, "BLOCKTYPE %d\n", g_Editinfo[nCnt1].nType);
                fprintf(pFile, "END_BLOCKSET\n");
                fprintf(pFile, "================\n");

            }

        }

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
//�^�C�g���p�̏����o������
//=============================
void SaveTitleData(void)
{
    D3DXVECTOR3 pos;
    int nType = 0;

    FILE* pFile = fopen(TITLEPATH_1, "w");

    if (pFile != NULL)
    {

        fwrite(&g_nCntEdit, sizeof(int), 0, pFile);

        for (int nCnt1 = 0; nCnt1 < g_nCntEdit; nCnt1++)
        {

            if (g_Editinfo[nCnt1].bUse == true)
            {

                fprintf(pFile, "SETBLOCK\n");
                fprintf(pFile, "POS %.1f %.1f %.1f\n", g_Editinfo[nCnt1].pos.x, g_Editinfo[nCnt1].pos.y, g_Editinfo[nCnt1].pos.z);
                fprintf(pFile, "ROT %.2f %.2f %.2f\n", g_Editinfo[nCnt1].rot.x, g_Editinfo[nCnt1].rot.y, g_Editinfo[nCnt1].rot.z);
                fprintf(pFile, "BLOCKTYPE %d\n", g_Editinfo[nCnt1].nType);
                fprintf(pFile, "END_BLOCKSET\n");
                fprintf(pFile, "================\n");

            }

        }

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

    for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
    {
        g_Editinfo[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // �����ʒu
        g_Editinfo[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // ������]
        g_Editinfo[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // �ړ��ʏ�����
        g_Editinfo[nCntBlock].bUse = false;                             // ���g�p��Ԃɐݒ�
        g_Editinfo[nCntBlock].nType = BLOCKTYPE_WALL;                   // �f�t�H���g�̃u���b�N�^�C�v
    }

    g_nCntEdit = 0; // �ҏW���̃u���b�N�������Z�b�g


    // �t�@�C�����J��
    FILE* pFile = fopen(BLOCKPATH_1, "r");

    D3DXVECTOR3 pos;
    D3DXVECTOR3 rot;
    int nType = 0;

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
                    else if (strcmp(aStr, "ROT") == 0)
                    {
                        fscanf(pFile, "%f", &rot.x);
                        fscanf(pFile, "%f", &rot.y);
                        fscanf(pFile, "%f", &rot.z);
                    }
                    else if (strcmp(aStr, "BLOCKTYPE") == 0)
                    {
                        fscanf(pFile, "%d", &nType);
                    }
                    else if (strcmp(aStr, "END_BLOCKSET") == 0)
                    {

                        SetBlock(pos, rot,nType);
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

    }
    else
    {
        return;
    }

    // ���ݑI�𒆂̃u���b�N��ݒ� (�ҏW�p�u���b�N)
    g_Editinfo[g_nCntEdit].bUse = true; // �V�����u���b�N���g�p��Ԃɂ���
    g_Editinfo[g_nCntEdit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �����ʒu�ɔz�u
    g_Editinfo[g_nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �����ʒu�ɔz�u
    g_Editinfo[g_nCntEdit].nType = BLOCKTYPE_WALL; // �f�t�H���g�̃u���b�N�^�C�v
    g_Editinfo[g_nCntEdit].blockTex[0] = blockTex[BLOCKTYPE_WALL];

    // �t�@�C�������
    fclose(pFile);
}
//=============================
//�ǂ̓ǂݍ��ݏ���
//=============================
void LoadWallData(void)
{

    for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
    {
        g_Editinfo[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // �����ʒu
        g_Editinfo[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // ������]
        g_Editinfo[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // �ړ��ʏ�����
        g_Editinfo[nCntBlock].bUse = false;                             // ���g�p��Ԃɐݒ�
        g_Editinfo[nCntBlock].nType = BLOCKTYPE_WALL;                   // �f�t�H���g�̃u���b�N�^�C�v
    }

    g_nCntEdit = 0; // �ҏW���̃u���b�N�������Z�b�g


    // �t�@�C�����J��
    FILE* pFile = fopen(WALLPATH_1, "r");

    D3DXVECTOR3 pos;
    D3DXVECTOR3 rot;
    int nType = 0;

    switch (g_nCntEdit)
    {
    case 0:
        //�t�@�C�����J��
        pFile = fopen(WALLPATH_1, "r");

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
                    else if (strcmp(aStr, "ROT") == 0)
                    {
                        fscanf(pFile, "%f", &rot.x);
                        fscanf(pFile, "%f", &rot.y);
                        fscanf(pFile, "%f", &rot.z);
                    }
                    else if (strcmp(aStr, "BLOCKTYPE") == 0)
                    {
                        fscanf(pFile, "%d", &nType);
                    }
                    else if (strcmp(aStr, "END_BLOCKSET") == 0)
                    {

                        SetBlock(pos, rot,nType);
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

    }
    else
    {
        return;
    }

    // ���ݑI�𒆂̃u���b�N��ݒ� (�ҏW�p�u���b�N)
    g_Editinfo[g_nCntEdit].bUse = true; // �V�����u���b�N���g�p��Ԃɂ���
    g_Editinfo[g_nCntEdit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �����ʒu�ɔz�u
    g_Editinfo[g_nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �����ʒu�ɔz�u
    g_Editinfo[g_nCntEdit].nType = BLOCKTYPE_WALL; // �f�t�H���g�̃u���b�N�^�C�v
    g_Editinfo[g_nCntEdit].blockTex[0] = blockTex[BLOCKTYPE_WALL];

    // �t�@�C�������
    fclose(pFile);
}
//=============================
//�^�C�g���p�̓ǂݍ��ݏ���
//=============================
void LoadTitleData(void)
{

    for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
    {
        g_Editinfo[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // �����ʒu
        g_Editinfo[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // ������]
        g_Editinfo[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // �ړ��ʏ�����
        g_Editinfo[nCntBlock].bUse = false;                             // ���g�p��Ԃɐݒ�
        g_Editinfo[nCntBlock].nType = BLOCKTYPE_WALL;                   // �f�t�H���g�̃u���b�N�^�C�v
    }

    g_nCntEdit = 0; // �ҏW���̃u���b�N�������Z�b�g


    // �t�@�C�����J��
    FILE* pFile = fopen(TITLEPATH_1, "r");

    D3DXVECTOR3 pos;
    D3DXVECTOR3 rot;
    int nType = 0;

    switch (g_nCntEdit)
    {
    case 0:
        //�t�@�C�����J��
        pFile = fopen(TITLEPATH_1, "r");

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
                    else if (strcmp(aStr, "ROT") == 0)
                    {
                        fscanf(pFile, "%f", &rot.x);
                        fscanf(pFile, "%f", &rot.y);
                        fscanf(pFile, "%f", &rot.z);
                    }
                    else if (strcmp(aStr, "BLOCKTYPE") == 0)
                    {
                        fscanf(pFile, "%d", &nType);
                    }
                    else if (strcmp(aStr, "END_BLOCKSET") == 0)
                    {

                        SetBlock(pos, rot, nType);
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

    }
    else
    {
        return;
    }

    // ���ݑI�𒆂̃u���b�N��ݒ� (�ҏW�p�u���b�N)
    g_Editinfo[g_nCntEdit].bUse = true; // �V�����u���b�N���g�p��Ԃɂ���
    g_Editinfo[g_nCntEdit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �����ʒu�ɔz�u
    g_Editinfo[g_nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �����ʒu�ɔz�u
    g_Editinfo[g_nCntEdit].nType = BLOCKTYPE_WALL; // �f�t�H���g�̃u���b�N�^�C�v
    g_Editinfo[g_nCntEdit].blockTex[0] = blockTex[BLOCKTYPE_WALL];

    // �t�@�C�������
    fclose(pFile);
}

