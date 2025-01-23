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
#include "meshcylinder.h"

//グローバル変数
Editinfo g_Editinfo[MAX_BLOCK];
BlockTex blockTex[BLOCKTYPE_MAX];

int g_nCntEdit;

//=============================
//エディターの初期化処理
//=============================
void InitEdit(void)
{

    // カーソルを非表示にする
    SetCursorVisibility(false);


    // ブロックの初期化処理
    InitBlock();

    // メッシュフィールドの初期化処理
    InitMeshfield();

    // メッシュシリンダーの初期化処理
    InitMeshcylinder();

    // ライトの初期化処理
    InitLight();

    // カメラの初期化処理
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
        g_Editinfo[nCntBlock].nType = BLOCKTYPE_WALL;
    }

    for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
    {
        //Xファイルの読み込み
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

        D3DXMATERIAL* pMat;//マテリアルへのポインタ

        //マテリアルデータへのポインタを取得
        pMat = (D3DXMATERIAL*)blockTex[nCnt].pBuffMat->GetBufferPointer();

        for (int nCntMat = 0; nCntMat < (int)blockTex[nCnt].dwNumMat; nCntMat++)
        {
            if (pMat[nCntMat].pTextureFilename != NULL)
            {//テクスチャファイルが存在する

                //テクスチャの読み込み
                D3DXCreateTextureFromFile(pDevice,
                    pMat[nCntMat].pTextureFilename,
                    &blockTex[nCnt].apTexture[nCntMat]);

            }
        }
    }

    g_Editinfo[0].bUse = true; // 最初のブロックを使用中にする
    g_Editinfo[0].blockTex[0] = blockTex[0];
    g_nCntEdit = 0;

}
//=============================
//エディターの終了処理
//=============================
void UninitEdit(void)
{
    // ブロックの終了処理
    UninitBlock();

    //メッシュフィールドの終了処理
    UninitMeshfield();

    //メッシュシリンダーの終了処理
    UninitMeshcylinder();

    for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
    {
        for (int nCntMat = 0; nCntMat < (int)blockTex[nCnt].dwNumMat; nCntMat++)
        {
            //テクスチャの破棄
            if (blockTex[nCnt].apTexture[nCntMat] != NULL)
            {
                blockTex[nCnt].apTexture[nCntMat]->Release();
                blockTex[nCnt].apTexture[nCntMat] = NULL;
            }
        }

        //メッシュの破棄
        if (blockTex[nCnt].pMesh != NULL)
        {
            blockTex[nCnt].pMesh->Release();
            blockTex[nCnt].pMesh = NULL;
        }

        //マテリアルの破棄
        if (blockTex[nCnt].pBuffMat != NULL)
        {
            blockTex[nCnt].pBuffMat->Release();
            blockTex[nCnt].pBuffMat = NULL;
        }
    }

}
//=============================
//エディターの更新処理
//=============================
void UpdateEdit(void)
{
    // ブロックの更新処理
    UpdateBlock();

    // メッシュフィールドの更新処理
    UpdateMeshfield();

    // メッシュシリンダーの更新処理
    UpdateMeshcylinder();

    // カメラの更新処理
    UpdateCamera();

    Block* pBlock = GetBlock();     // ブロック情報
    FADE g_fade = GetFade();        // 現在の状態
    Camera* pCamera = GetCamera();


    // ブロックの位置を変更
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


    //ブロックを回転する
    if (KeyboardTrigger(DIK_Y) == true)
    {
        g_Editinfo[g_nCntEdit].rot.y += D3DX_PI / 2;
    }
    else if (KeyboardTrigger(DIK_H) == true)
    {
        g_Editinfo[g_nCntEdit].rot.y -= D3DX_PI / 2;
    }

    // ブロックを設置
    if (KeyboardTrigger(DIK_RETURN) == true)
    {
        g_Editinfo[g_nCntEdit + 1].pos = g_Editinfo[g_nCntEdit].pos;
        //g_Editinfo[g_nCntEdit + 1].rot = g_Editinfo[g_nCntEdit].rot;
        g_Editinfo[g_nCntEdit + 1].bUse = true; // 使用中に設定
        g_Editinfo[g_nCntEdit + 1].blockTex[0] = blockTex[0];
        
        g_nCntEdit++; // 次のインデックスへ
        g_Editinfo[g_nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 回転をリセット
    }
    else if (GetMouseButtonTrigger(0))
    {
        g_Editinfo[g_nCntEdit + 1].pos = g_Editinfo[g_nCntEdit].pos;
        //g_Editinfo[g_nCntEdit + 1].rot = g_Editinfo[g_nCntEdit].rot;
        g_Editinfo[g_nCntEdit + 1].bUse = true; // 使用中に設定
        g_Editinfo[g_nCntEdit + 1].blockTex[0] = blockTex[0];

        g_nCntEdit++; // 次のインデックスへ
        g_Editinfo[g_nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 回転をリセット
    }

    int MouseWheel = GetMouseWheel();

    //ブロックの種類変更
    if (MouseWheel > 0 && g_Editinfo[g_nCntEdit].nType < BLOCKTYPE_MAX - 1)//上にスクロール
    {
        g_Editinfo[g_nCntEdit].nType++;

        g_Editinfo[g_nCntEdit].blockTex[g_Editinfo[g_nCntEdit].nType] = blockTex[g_Editinfo[g_nCntEdit].nType];
    }
    else if (MouseWheel < 0 && g_Editinfo[g_nCntEdit].nType > 0)//下にスクロール
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


    // 正規化処理
    if (g_Editinfo[g_nCntEdit].rot.y > D3DX_PI) 
    {
        g_Editinfo[g_nCntEdit].rot.y -= D3DX_PI * 2.0f;
    }
    if (g_Editinfo[g_nCntEdit].rot.y < -D3DX_PI) 
    {
        g_Editinfo[g_nCntEdit].rot.y += D3DX_PI * 2.0f;
    }

    // 必要に応じて他の軸も正規化
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


    //ブロックの削除
    if (KeyboardTrigger(DIK_DELETE) == true && !g_nCntEdit == 0)
    {
        g_Editinfo[g_nCntEdit].bUse = false;
        g_nCntEdit--;
    }


    if (KeyboardTrigger(DIK_F1) == true && g_fade == FADE_NONE)
    {
        //タイトル画面に移行
        SetFade(MODE_TITLE);
    }

    // ブロック設置の情報を保存
    if (KeyboardTrigger(DIK_F7) == true)
    {
        SaveBlockData();
    }
    // 壁設置の情報を保存
    else if (KeyboardTrigger(DIK_F2) == true)
    {
        SaveWallData();
    }
    // タイトル用の配置情報を保存
    else if (KeyboardTrigger(DIK_F3) == true)
    {
        SaveTitleData();
    }



    // ブロック設置の情報を読み込む
    if (KeyboardTrigger(DIK_F6) == true)
    {
        LoadBlockData();
    }
    // 壁設置の情報を読み込む
    else if (KeyboardTrigger(DIK_F3) == true)
    {
        LoadWallData();
    }

}
//=============================
//エディターの描画処理
//=============================
void DrawEdit(void)
{
    // ブロックの描画
    DrawBlock();

    //メッシュフィールドの描画
    DrawMeshfield();

    //メッシュシリンダーの描画
    DrawMeshcylinder();

    // カメラの設定
    SetCamera();

    LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

    //デバイスの取得
    pDevice = GetDevice();

    //計算用マトリックス
    D3DXMATRIX mtxRot, mtxTrans;

    D3DMATERIAL9 matDef;//現在のマテリアル保存用

    D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

    for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
    {
        if (g_Editinfo[nCntBlock].bUse == true)
        {
            int nType = g_Editinfo[nCntBlock].nType;

            // ワールドマトリックスの初期化
            D3DXMatrixIdentity(&g_Editinfo[nCntBlock].mtxWorld);

            // 向きを反映
            D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Editinfo[nCntBlock].rot.y, g_Editinfo[nCntBlock].rot.x, g_Editinfo[nCntBlock].rot.z);
            D3DXMatrixMultiply(&g_Editinfo[nCntBlock].mtxWorld, &g_Editinfo[nCntBlock].mtxWorld, &mtxRot);

            // 位置を反映
            D3DXMatrixTranslation(&mtxTrans, g_Editinfo[nCntBlock].pos.x, g_Editinfo[nCntBlock].pos.y, g_Editinfo[nCntBlock].pos.z);
            D3DXMatrixMultiply(&g_Editinfo[nCntBlock].mtxWorld, &g_Editinfo[nCntBlock].mtxWorld, &mtxTrans);

            // ワールドマトリックスを設定
            pDevice->SetTransform(D3DTS_WORLD, &g_Editinfo[nCntBlock].mtxWorld);

            // 現在のマテリアルの取得
            pDevice->GetMaterial(&matDef);

            for (int nCntMat = 0; nCntMat < (int)g_Editinfo[nCntBlock].blockTex[nType].dwNumMat; nCntMat++) 
            {
                // マテリアルデータへのポインタを取得
                pMat = (D3DXMATERIAL*)g_Editinfo[nCntBlock].blockTex[nType].pBuffMat->GetBufferPointer();

                D3DXMATERIAL color;

                color = pMat[nCntMat];

                // 選択中のブロックを半透明にする
                if (nCntBlock == g_nCntEdit)
                {

                    color.MatD3D.Diffuse.r = 1.0f;
                    color.MatD3D.Diffuse.g = 1.0f;
                    color.MatD3D.Diffuse.b = 1.0f;
                    color.MatD3D.Diffuse.a = 0.6f;

                    // マテリアルの設定
                    pDevice->SetMaterial(&color.MatD3D);

                }
                else
                {
                    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
                }

                // テクスチャの設定
                pDevice->SetTexture(0, g_Editinfo[nCntBlock].blockTex[nType].apTexture[nCntMat]);

                // モデル(パーツ)の描画
                g_Editinfo[nCntBlock].blockTex[nType].pMesh->DrawSubset(nCntMat);
            }

            // 保存していたマテリアルを戻す
            pDevice->SetMaterial(&matDef);
        }
    }

}
//======================================
//ブロック(オブジェクト)の書き出し処理
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

        //ファイルを閉じる
        fclose(pFile);

    }
    else
    {
        return;
    }
}
//=============================
//壁の書き出し処理
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

        //ファイルを閉じる
        fclose(pFile);

    }
    else
    {
        return;
    }
}
//=============================
//タイトル用の書き出し処理
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

    for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
    {
        g_Editinfo[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 初期位置
        g_Editinfo[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 初期回転
        g_Editinfo[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 移動量初期化
        g_Editinfo[nCntBlock].bUse = false;                             // 未使用状態に設定
        g_Editinfo[nCntBlock].nType = BLOCKTYPE_WALL;                   // デフォルトのブロックタイプ
    }

    g_nCntEdit = 0; // 編集中のブロック数をリセット


    // ファイルを開く
    FILE* pFile = fopen(BLOCKPATH_1, "r");

    D3DXVECTOR3 pos;
    D3DXVECTOR3 rot;
    int nType = 0;

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

        //ファイルを閉じる
        fclose(pFile);

    }
    else
    {
        return;
    }

    // 現在選択中のブロックを設定 (編集用ブロック)
    g_Editinfo[g_nCntEdit].bUse = true; // 新しいブロックを使用状態にする
    g_Editinfo[g_nCntEdit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 初期位置に配置
    g_Editinfo[g_nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 初期位置に配置
    g_Editinfo[g_nCntEdit].nType = BLOCKTYPE_WALL; // デフォルトのブロックタイプ
    g_Editinfo[g_nCntEdit].blockTex[0] = blockTex[BLOCKTYPE_WALL];

    // ファイルを閉じる
    fclose(pFile);
}
//=============================
//壁の読み込み処理
//=============================
void LoadWallData(void)
{

    for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
    {
        g_Editinfo[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 初期位置
        g_Editinfo[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 初期回転
        g_Editinfo[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 移動量初期化
        g_Editinfo[nCntBlock].bUse = false;                             // 未使用状態に設定
        g_Editinfo[nCntBlock].nType = BLOCKTYPE_WALL;                   // デフォルトのブロックタイプ
    }

    g_nCntEdit = 0; // 編集中のブロック数をリセット


    // ファイルを開く
    FILE* pFile = fopen(WALLPATH_1, "r");

    D3DXVECTOR3 pos;
    D3DXVECTOR3 rot;
    int nType = 0;

    switch (g_nCntEdit)
    {
    case 0:
        //ファイルを開く
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

        //ファイルを閉じる
        fclose(pFile);

    }
    else
    {
        return;
    }

    // 現在選択中のブロックを設定 (編集用ブロック)
    g_Editinfo[g_nCntEdit].bUse = true; // 新しいブロックを使用状態にする
    g_Editinfo[g_nCntEdit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 初期位置に配置
    g_Editinfo[g_nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 初期位置に配置
    g_Editinfo[g_nCntEdit].nType = BLOCKTYPE_WALL; // デフォルトのブロックタイプ
    g_Editinfo[g_nCntEdit].blockTex[0] = blockTex[BLOCKTYPE_WALL];

    // ファイルを閉じる
    fclose(pFile);
}
//=============================
//タイトル用の読み込み処理
//=============================
void LoadTitleData(void)
{

    for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
    {
        g_Editinfo[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 初期位置
        g_Editinfo[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 初期回転
        g_Editinfo[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 移動量初期化
        g_Editinfo[nCntBlock].bUse = false;                             // 未使用状態に設定
        g_Editinfo[nCntBlock].nType = BLOCKTYPE_WALL;                   // デフォルトのブロックタイプ
    }

    g_nCntEdit = 0; // 編集中のブロック数をリセット


    // ファイルを開く
    FILE* pFile = fopen(TITLEPATH_1, "r");

    D3DXVECTOR3 pos;
    D3DXVECTOR3 rot;
    int nType = 0;

    switch (g_nCntEdit)
    {
    case 0:
        //ファイルを開く
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

        //ファイルを閉じる
        fclose(pFile);

    }
    else
    {
        return;
    }

    // 現在選択中のブロックを設定 (編集用ブロック)
    g_Editinfo[g_nCntEdit].bUse = true; // 新しいブロックを使用状態にする
    g_Editinfo[g_nCntEdit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 初期位置に配置
    g_Editinfo[g_nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 初期位置に配置
    g_Editinfo[g_nCntEdit].nType = BLOCKTYPE_WALL; // デフォルトのブロックタイプ
    g_Editinfo[g_nCntEdit].blockTex[0] = blockTex[BLOCKTYPE_WALL];

    // ファイルを閉じる
    fclose(pFile);
}

