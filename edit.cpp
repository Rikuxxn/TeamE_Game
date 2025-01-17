//=======================================
//
// エディット処理[edit.cpp]
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

//グローバル変数
Editinfo g_Editinfo[MAX_BLOCK];
int g_nCntEdit;

//=============================
//エディターの初期化処理
//=============================
void InitEdit(void)
{

    InitBlock();

    InitMeshfield();

    InitLight();

    InitCamera();

    LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

    //デバイスの取得
    pDevice = GetDevice();

    for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
    {
        //初期化
        g_Editinfo[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
        g_Editinfo[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
        g_Editinfo[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//移動量
        g_Editinfo[nCntBlock].bUse = false;
        g_Editinfo[nCntBlock].nType = BLOCKTYPE_NORMAL;

        for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
        {
            //Xファイルの読み込み
            D3DXLoadMeshFromX(BLOCK[nCnt],
                D3DXMESH_SYSTEMMEM,
                pDevice,
                NULL,
                &g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat,
                NULL,
                &g_Editinfo[nCntBlock].blockinfo[nCnt].dwNumMat,
                &g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh);


            int nNumVtx;//頂点数
            DWORD sizeFVF;//頂点フォーマットのサイズ
            BYTE* pVtxBuff;//頂点バッファへのポインタ

            //頂点数の取得
            nNumVtx = g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->GetNumVertices();

            //頂点フォーマットの取得
            sizeFVF = D3DXGetFVFVertexSize(g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->GetFVF());

            //頂点バッファのロック
            g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

            for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
            {
                //頂点座標の代入
                D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

                //頂点座標を比較してモデルの最小値最大値を取得
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

                //頂点フォーマットのサイズ分ポインタを進める
                pVtxBuff += sizeFVF;
            }

            g_Editinfo[nCntBlock].size.x = (g_Editinfo[nCntBlock].vtxMax.x - g_Editinfo[nCntBlock].vtxMin.x);
            g_Editinfo[nCntBlock].size.y = (g_Editinfo[nCntBlock].vtxMax.y - g_Editinfo[nCntBlock].vtxMin.y);
            g_Editinfo[nCntBlock].size.z = (g_Editinfo[nCntBlock].vtxMax.z - g_Editinfo[nCntBlock].vtxMin.z);

            //頂点バッファのアンロック
            g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->UnlockVertexBuffer();

            D3DXMATERIAL* pMat;//マテリアルへのポインタ

            //マテリアルデータへのポインタを取得
            pMat = (D3DXMATERIAL*)g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat->GetBufferPointer();

            for (int nCntMat = 0; nCntMat < (int)g_Editinfo[nCntBlock].blockinfo[nCnt].dwNumMat; nCntMat++)
            {
                if (pMat[nCntMat].pTextureFilename != NULL)
                {//テクスチャファイルが存在する

                    //テクスチャの読み込み
                    D3DXCreateTextureFromFile(pDevice,
                        pMat[nCntMat].pTextureFilename,
                        &g_Editinfo[nCntBlock].blockinfo[nCnt].apTexture[nCntMat]);

                }
            }

        }

    }

    g_Editinfo[0].bUse = true; // 最初のブロックを使用中にする
    g_nCntEdit = 0;               // 最初のインデックスを1に設定

}
//=============================
//エディターの終了処理
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
                //テクスチャの破棄
                if (g_Editinfo[nCntBlock].blockinfo[nCnt].apTexture[nCntMat] != NULL)
                {
                    g_Editinfo[nCntBlock].blockinfo[nCnt].apTexture[nCntMat]->Release();
                    g_Editinfo[nCntBlock].blockinfo[nCnt].apTexture[nCntMat] = NULL;
                }
            }

            //メッシュの破棄
            if (g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh != NULL)
            {
                g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->Release();
                g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh = NULL;
            }

            //マテリアルの破棄
            if (g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat != NULL)
            {
                g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat->Release();
                g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat = NULL;
            }
        }
    }

}
//=============================
//エディターの更新処理
//=============================
void UpdateEdit(void)
{
    UpdateBlock();

    UpdateMeshfield();

    UpdateCamera();

    Block* pBlock = GetBlock();
    FADE g_fade = GetFade(); // 現在の状態

    for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
    {
        for (int nCnt1 = 0; nCnt1 < MAX_BLOCK; nCnt1++)
        {
            // キー操作で位置を変更
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

            //// ブロックタイプの切り替え
            //if (GetKeyboardPress(DIK_1) == true)
            //{
            //    pBlock[nCnt].nType = BLOCKTYPE_NORMAL;
            //}

            //if (GetKeyboardPress(DIK_2) == true)
            //{
            //    pBlock[nCnt].nType = BLOCKTYPE_DOOR;
            //}

            // ブロックを設置
            if (KeyboardTrigger(DIK_RETURN) == true)
            {
                //// 現在選択中のブロックだけを処理する
                //if (g_Editinfo[g_nCntEdit].bUse == false)
                //{
                    g_Editinfo[g_nCntEdit + 1].bUse = true; // 使用中に設定
                    g_Editinfo[g_nCntEdit + 1].pos = g_Editinfo[g_nCntEdit].pos; // 前回の位置を引き継ぐ

                    g_nCntEdit++; // 次のインデックスへ
                    break; // 他のループを終了
                //}
            }

            //ブロックの種類変更
            if (KeyboardTrigger(DIK_O) == true)
            {
                g_Editinfo[g_nCntEdit + 1].nType += 1;
            }
        }
    }

    if (KeyboardTrigger(DIK_F1) == true && g_fade == FADE_NONE)
    {
        //タイトル画面に移行
        SetFade(MODE_TITLE);
    }

    if (KeyboardTrigger(DIK_F7) == true)
    {
        SaveBlockData();
    }
}
//=============================
//エディターの描画処理
//=============================
void DrawEdit(void)
{
    // ブロックとメッシュフィールドの描画
    DrawBlock();
    DrawMeshfield();

    // カメラの設定
    SetCamera();

    LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

    //デバイスの取得
    pDevice = GetDevice();

    //計算用マトリックス
    D3DXMATRIX mtxRot, mtxTrans;

    D3DMATERIAL9 matDef;//現在のマテリアル保存用

    D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

    for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
    {
        for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
        {
            if (g_Editinfo[nCntBlock].bUse == true)
            {
                int nType = g_Editinfo[nCntBlock].nType;

                //ワールドマトリックスの初期化
                D3DXMatrixIdentity(&g_Editinfo[nCntBlock].mtxWorld);

                //向きを反映
                D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Editinfo[nCntBlock].rot.y, g_Editinfo[nCntBlock].rot.x, g_Editinfo[nCntBlock].rot.z);
                D3DXMatrixMultiply(&g_Editinfo[nCntBlock].mtxWorld, &g_Editinfo[nCntBlock].mtxWorld, &mtxRot);

                //位置を反映
                D3DXMatrixTranslation(&mtxTrans, g_Editinfo[nCntBlock].pos.x, g_Editinfo[nCntBlock].pos.y, g_Editinfo[nCntBlock].pos.z);
                D3DXMatrixMultiply(&g_Editinfo[nCntBlock].mtxWorld, &g_Editinfo[nCntBlock].mtxWorld, &mtxTrans);

                //ワールドマトリックスを設定
                pDevice->SetTransform(D3DTS_WORLD, &g_Editinfo[nCntBlock].mtxWorld);

                //現在のマテリアルの取得
                pDevice->GetMaterial(&matDef);

                //マテリアルデータへのポインタを取得
                pMat = (D3DXMATERIAL*)g_Editinfo[nCntBlock].blockinfo[nCnt].pBuffMat->GetBufferPointer();

                for (int nCntMat = 0; nCntMat < (int)g_Editinfo[nCntBlock].blockinfo[nCnt].dwNumMat; nCntMat++)
                {
                    //マテリアルの設定
                    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                    //テクスチャの設定
                    pDevice->SetTexture(0, g_Editinfo[nCntBlock].blockinfo[nCnt].apTexture[nCntMat]);

                    //モデル(パーツ)の描画
                    g_Editinfo[nCntBlock].blockinfo[nCnt].pMesh->DrawSubset(nCntMat);

                }

                //保存していたマテリアルを戻す
                pDevice->SetMaterial(&matDef);

            }
        }
    }

}
//=============================
//ブロックの書き出し処理
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


        //ファイルを閉じる
        fclose(pFile);

    }
    else
    {
        return;
    }
}
//=============================
//ブロックの読み込み処理
//=============================
void LoadBlockData(void)
{
    FILE* pFile = fopen(BLOCKPATH_1, "r");

    D3DXVECTOR3 pos;
    int nType;

    switch (g_nCntEdit)
    {
    case 0:
        //ファイルを開く
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


            //一致したら
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


        //ファイルを閉じる
        fclose(pFile);

        ////ブロックセットカウントアップ
        //g_nBlockSet++;


    }
    else
    {
        return;
    }

    fclose(pFile);
}
