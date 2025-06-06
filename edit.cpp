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
#include "meshceiling.h"

//グローバル変数
Editinfo g_Editinfo[MAX_BLOCK];
BlockTex blockTex[BLOCKTYPE_MAX];

int g_nCntEdit;

int g_CurrentSavePathSet = 0;   // 保存用ファイルパスの選択
int g_CurrentLoadPathSet = 0;   // 読み込み用ファイルパスの選択
int g_selectedIndex = -1;

//=============================
// エディターの初期化処理
//=============================
void InitEdit(void)
{

    // カーソルを非表示にする
    SetCursorVisibility(true);


    // ブロックの初期化処理
    InitBlock();

    // メッシュフィールドの初期化処理
    InitMeshfield();

    // メッシュシーリングの初期化処理
    InitMeshCeiling();

    // メッシュシリンダーの初期化処理
    InitMeshcylinder();

    // ライトの初期化処理
    InitLight();

    // カメラの初期化処理
    InitCamera();
    
    // ライトの設定
    AddLight(
        D3DLIGHT_DIRECTIONAL,              // ライトの種類
        D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), // 暗めの白い光
        D3DXVECTOR3(0.0f, -1.0f, 0.0f),    // 真下方向
        D3DXVECTOR3(0.0f, 260.0f, 0.0f)    // 天井の位置（無視される）
    );

    AddLight(
        D3DLIGHT_DIRECTIONAL,               // ライトの種類
        D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),  // 暗めの白い光
        D3DXVECTOR3(-1.0f, 0.0f, 0.0f),     // 左方向
        D3DXVECTOR3(0.0f, 260.0f, 0.0f)     // 天井の位置（無視される）
    );

    AddLight(
        D3DLIGHT_DIRECTIONAL,               // ライトの種類
        D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),  // 暗めの白い光
        D3DXVECTOR3(0.0f, 0.0f, -1.0f),     // 手前方向
        D3DXVECTOR3(0.0f, 260.0f, 0.0f)     // 天井の位置（無視される）
    );


    AddLight(
        D3DLIGHT_DIRECTIONAL,                // ライトの種類
        D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),   // 暗めの白い光
        D3DXVECTOR3(1.0f, 0.0f, 0.0f),       // 右方向
        D3DXVECTOR3(0.0f, 260.0f, 0.0f)      // 天井の位置（無視される）
    );

    AddLight(
        D3DLIGHT_DIRECTIONAL,                // ライトの種類
        D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),   // 暗めの白い光
        D3DXVECTOR3(0.0f, 0.0f, 1.0f),       // 奥方向
        D3DXVECTOR3(0.0f, 260.0f, 0.0f)      // 天井の位置（無視される）
    );

    LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

    //デバイスの取得
    pDevice = GetDevice();

    for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
    {
        //初期化
        g_Editinfo[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //位置
        g_Editinfo[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //向き
        g_Editinfo[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量
        g_Editinfo[nCntBlock].bUse = false;
        g_Editinfo[nCntBlock].nType = BLOCKTYPE_WALL;
        g_Editinfo[nCntBlock].nPathType = PATH_BLOCK;
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
// エディターの終了処理
//=============================
void UninitEdit(void)
{
    // ブロックの終了処理
    UninitBlock();

    //メッシュフィールドの終了処理
    UninitMeshfield();

    //メッシュシーリングの終了処理
    UninitMeshCeiling();

    //メッシュシリンダーの終了処理
    UninitMeshcylinder();

    // ライトの終了処理
    UninitLight();

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


    for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
    {
        for (int nCnt2 = 0; nCnt2 < BLOCKTYPE_MAX; nCnt2++)
        {
            for (int nCntMat = 0; nCntMat < (int)g_Editinfo[nCnt].blockTex[nCnt2].dwNumMat; nCntMat++)
            {
                //テクスチャの破棄
                if (blockTex[nCnt].apTexture[nCntMat] != NULL)
                {
                    blockTex[nCnt].apTexture[nCntMat] = NULL;
                }
            }

            //メッシュの破棄
            if (blockTex[nCnt].pMesh != NULL)
            {
                blockTex[nCnt].pMesh = NULL;
            }

            //マテリアルの破棄
            if (blockTex[nCnt].pBuffMat != NULL)
            {
                blockTex[nCnt].pBuffMat = NULL;
            }
        }
    }
}
//=============================
// エディターの更新処理
//=============================
void UpdateEdit(void)
{
    FADE g_fade = GetFade();// 現在の状態

    // ブロックの更新処理
    UpdateBlock();

    // メッシュフィールドの更新処理
    UpdateMeshfield();

    //メッシュシーリングの更新処理
    UpdateMeshCeiling();

    // メッシュシリンダーの更新処理
    UpdateMeshcylinder();

    // カメラの更新処理
    UpdateCamera();

    // エディターブロック移動処理
    MoveEditBlock();

    // エディターブロック回転処理
    TurnEditBlock();

    // エディターブロックの正規化処理
    NormalizeEditBlock();

    // エディター操作処理
    OperationEdit();

    if (KeyboardTrigger(DIK_F1) == true && g_fade == FADE_NONE)
    {
        // タイトル画面に移行
        SetFade(MODE_TITLE);
    }

}
//=============================
// エディターの描画処理
//=============================
void DrawEdit(void)
{
    // ブロックの描画
    DrawBlock();

    //メッシュフィールドの描画
    DrawMeshfield();

    //メッシュシーリングの描画処理
    DrawMeshCeiling();

    //メッシュシリンダーの描画
    DrawMeshcylinder();

    // カメラの設定
    SetCamera();

    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

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
// ブロック(オブジェクト)の書き出し処理
//======================================
void SaveBlockData(void)
{
    D3DXVECTOR3 pos;
    int nType = 0;
    FILE* pFile = NULL;

    // ファイルを開く
    pFile = fopen(PATH[g_CurrentSavePathSet], "w");

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
// ブロックの読み込み処理
//=============================
void LoadBlockData(void)
{
    FILE* pFile = NULL;

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
    pFile = fopen(PATH[g_CurrentLoadPathSet], "r");

    D3DXVECTOR3 pos;
    D3DXVECTOR3 rot;
    int nType = 0;

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
                        // ブロックを設置
                        SetBlock(pos, rot,nType);

                        g_Editinfo[g_nCntEdit].pos = pos;
                        g_Editinfo[g_nCntEdit].rot = rot;
                        g_Editinfo[g_nCntEdit].nType = nType;
                        g_Editinfo[g_nCntEdit].bUse = true;
                        g_nCntEdit++; // 読み込んだブロック数を増やす

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
//======================================
// 特定のファイルの読み込み処理
//======================================
void LoadParticular(int nPathType)
{
    FILE* pFile = NULL;

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
    pFile = fopen(PATH[nPathType], "r");

    D3DXVECTOR3 pos;
    D3DXVECTOR3 rot;
    int nType = 0;

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
                        // ブロックを設置
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
//=============================
// マウスブロック選択
//=============================
void SelectBlockByMouse(void)
{
    // マウスのスクリーン座標を取得
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(GetActiveWindow(), &pt);

    // デバイス取得
    LPDIRECT3DDEVICE9 pDevice = GetDevice();
    D3DVIEWPORT9 viewport;
    pDevice->GetViewport(&viewport);

    // クリック位置のスクリーン座標を正規化 (-1.0 ~ 1.0)
    D3DXVECTOR3 rayOrigin, rayDir;
    D3DXMATRIX matProj;
    pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
    float px = ((2.0f * pt.x) / viewport.Width - 1.0f) / matProj._11;
    float py = ((-2.0f * pt.y) / viewport.Height + 1.0f) / matProj._22;

    // カメラのビュー・逆行列取得
    D3DXMATRIX matView, matInvView;
    pDevice->GetTransform(D3DTS_VIEW, &matView);
    D3DXMatrixInverse(&matInvView, NULL, &matView);

    // レイの方向・原点計算
    rayDir.x = px * matInvView._11 + py * matInvView._21 + matInvView._31;
    rayDir.y = px * matInvView._12 + py * matInvView._22 + matInvView._32;
    rayDir.z = px * matInvView._13 + py * matInvView._23 + matInvView._33;
    D3DXVec3Normalize(&rayDir, &rayDir);

    rayOrigin.x = matInvView._41;
    rayOrigin.y = matInvView._42;
    rayOrigin.z = matInvView._43;

    // ブロックとの交差判定
    float closestDist = FLT_MAX; // 一番近いブロックを選択するため

    for (int i = 0; i < MAX_BLOCK; i++)
    {
        if (!g_Editinfo[i].bUse)
        {
            continue; // 使ってないブロックは無視
        }

        BOOL hit;
        DWORD faceIndex; // ヒットした面のインデックス
        FLOAT u, v, dist; // ヒット位置のUV座標と距離

        // レイとメッシュの交差判定
        D3DXIntersect(g_Editinfo[i].blockTex[g_Editinfo[i].nType].pMesh,
            &rayOrigin, &rayDir, &hit, &faceIndex, &u, &v, &dist, NULL, NULL);

        if (hit && dist < closestDist)
        {
            closestDist = dist;
            g_selectedIndex = i;
        }
    }

    if (g_selectedIndex != -1)
    {
        g_nCntEdit = g_selectedIndex; // 選択中のブロックを更新
    }
}
//==================================================
// ブロックの移動処理
//==================================================
void MoveEditBlock(void)
{
    Camera* pCamera = GetCamera();

    // ブロックの位置を変更
    if (KeyboardTrigger(DIK_W))    // 前進
    {
        if (fabsf(cosf(pCamera->rot.y)) > fabsf(sinf(pCamera->rot.y)))
        {
            // Z方向に移動
            g_Editinfo[g_nCntEdit].pos.z -= (cosf(pCamera->rot.y) > 0 ? MAX_SPEED : -MAX_SPEED);
        }
        else
        {
            // X方向に移動
            g_Editinfo[g_nCntEdit].pos.x -= (sinf(pCamera->rot.y) > 0 ? MAX_SPEED : -MAX_SPEED);
        }
    }

    if (KeyboardTrigger(DIK_S))   // 後退
    {
        if (fabsf(cosf(pCamera->rot.y)) > fabsf(sinf(pCamera->rot.y)))
        {
            // Z方向に移動
            g_Editinfo[g_nCntEdit].pos.z += (cosf(pCamera->rot.y) > 0 ? MAX_SPEED : -MAX_SPEED);
        }
        else
        {
            // X方向に移動
            g_Editinfo[g_nCntEdit].pos.x += (sinf(pCamera->rot.y) > 0 ? MAX_SPEED : -MAX_SPEED);
        }
    }

    if (KeyboardTrigger(DIK_A))   // 左移動
    {
        if (fabsf(cosf(pCamera->rot.y)) > fabsf(sinf(pCamera->rot.y)))
        {
            // X方向に移動
            g_Editinfo[g_nCntEdit].pos.x += (cosf(pCamera->rot.y) > 0 ? MAX_SPEED : -MAX_SPEED);
        }
        else
        {
            // Z方向に移動
            g_Editinfo[g_nCntEdit].pos.z -= (sinf(pCamera->rot.y) > 0 ? MAX_SPEED : -MAX_SPEED);
        }
    }

    if (KeyboardTrigger(DIK_D))  // 右移動
    {
        if (fabsf(cosf(pCamera->rot.y)) > fabsf(sinf(pCamera->rot.y)))
        {
            // X方向に移動
            g_Editinfo[g_nCntEdit].pos.x -= (cosf(pCamera->rot.y) > 0 ? MAX_SPEED : -MAX_SPEED);
        }
        else
        {
            // Z方向に移動
            g_Editinfo[g_nCntEdit].pos.z += (sinf(pCamera->rot.y) > 0 ? MAX_SPEED : -MAX_SPEED);
        }
    }
    else if (KeyboardTrigger(DIK_Z) == true)// 上移動
    {
        g_Editinfo[g_nCntEdit].pos.y += 10.0f;
    }
    else if (KeyboardTrigger(DIK_C) == true)// 下移動
    {
        g_Editinfo[g_nCntEdit].pos.y -= 10.0f;
    }
}
//==================================================
// ブロックの回転処理
//==================================================
void TurnEditBlock(void)
{
    // ブロックをX軸回転する
    if (KeyboardTrigger(DIK_T) == true)
    {
        g_Editinfo[g_nCntEdit].rot.x += D3DXToRadian(45);
    }
    else if (KeyboardTrigger(DIK_G) == true)
    {
        g_Editinfo[g_nCntEdit].rot.x -= D3DXToRadian(45);
    }

    // ブロックをY軸回転する
    if (KeyboardTrigger(DIK_Y) == true)
    {
        g_Editinfo[g_nCntEdit].rot.y += D3DXToRadian(45);
    }
    else if (KeyboardTrigger(DIK_H) == true)
    {
        g_Editinfo[g_nCntEdit].rot.y -= D3DXToRadian(45);
    }

    // ブロックをZ軸回転する
    if (KeyboardTrigger(DIK_U) == true)
    {
        g_Editinfo[g_nCntEdit].rot.z += D3DXToRadian(45);
    }
    else if (KeyboardTrigger(DIK_J) == true)
    {
        g_Editinfo[g_nCntEdit].rot.z -= D3DXToRadian(45);
    }
}
//==================================================
// エディター操作処理
//==================================================
void OperationEdit(void)
{
    int MouseWheel = GetMouseWheel();

    // ブロックを設置
    if (KeyboardTrigger(DIK_F) == true)
    {
        g_Editinfo[g_nCntEdit + 1].pos = g_Editinfo[g_nCntEdit].pos;
        g_Editinfo[g_nCntEdit + 1].bUse = true; // 使用中に設定
        g_Editinfo[g_nCntEdit + 1].blockTex[0] = blockTex[0];

        g_nCntEdit++; // 次のインデックスへ
        g_Editinfo[g_nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 回転をリセット
    }

    if (KeyboardTrigger(DIK_Q) == true && g_Editinfo[g_nCntEdit].nType > 0)
    {
        g_Editinfo[g_nCntEdit].nType--;

        g_Editinfo[g_nCntEdit].blockTex[g_Editinfo[g_nCntEdit].nType] = blockTex[g_Editinfo[g_nCntEdit].nType];
    }
    else if (KeyboardTrigger(DIK_E) == true && g_Editinfo[g_nCntEdit].nType < BLOCKTYPE_MAX - 1)
    {
        g_Editinfo[g_nCntEdit].nType++;

        g_Editinfo[g_nCntEdit].blockTex[g_Editinfo[g_nCntEdit].nType] = blockTex[g_Editinfo[g_nCntEdit].nType];
    }

    // ブロックの削除
    if (KeyboardTrigger(DIK_DELETE) == true && g_nCntEdit > 0)
    {
        if (g_Editinfo[g_nCntEdit].bUse) // 使用中のブロックだけ削除
        {
            g_Editinfo[g_nCntEdit].bUse = false;
            g_nCntEdit--;
        }
    }

    //if (GetMouseButtonTrigger(0)) // 左クリック
    //{
    //    SelectBlockByMouse();
    //}

    // ブロック設置の情報を読み込む
    if (KeyboardTrigger(DIK_F6) == true)
    {
        LoadBlockData();
    }
    // ブロック設置の情報を保存
    else if (KeyboardTrigger(DIK_F7) == true)
    {
        SaveBlockData();
    }

    // 保存するファイルパスの変更
    if (KeyboardTrigger(DIK_2) && g_CurrentSavePathSet < PATH_MAX - 1)
    {// 2キーで次のファイルパスへ
        g_CurrentSavePathSet++;
    }
    else if (KeyboardTrigger(DIK_1) && g_CurrentSavePathSet > 0)
    {// 1キーで前のファイルパスへ
        g_CurrentSavePathSet--;
    }

    // 読み込むファイルパスの変更
    if (KeyboardTrigger(DIK_4) && g_CurrentLoadPathSet < PATH_MAX - 1)
    {// 4キーで次のファイルパスへ
        g_CurrentLoadPathSet++;
    }
    else if (KeyboardTrigger(DIK_3) && g_CurrentLoadPathSet > 0)
    {// 3キーで前のファイルパスへ
        g_CurrentLoadPathSet--;
    }
}
//==================================================
// エディットブロックの正規化
//==================================================
void NormalizeEditBlock(void)
{
    // X軸の正規化
    if (g_Editinfo[g_nCntEdit].rot.x > D3DX_PI)
    {
        g_Editinfo[g_nCntEdit].rot.x -= D3DX_PI * 2.0f;
    }
    if (g_Editinfo[g_nCntEdit].rot.x < -D3DX_PI)
    {
        g_Editinfo[g_nCntEdit].rot.x += D3DX_PI * 2.0f;
    }

    // Y軸の正規化
    if (g_Editinfo[g_nCntEdit].rot.y > D3DX_PI)
    {
        g_Editinfo[g_nCntEdit].rot.y -= D3DX_PI * 2.0f;
    }
    if (g_Editinfo[g_nCntEdit].rot.y < -D3DX_PI)
    {
        g_Editinfo[g_nCntEdit].rot.y += D3DX_PI * 2.0f;
    }

    // Z軸の正規化
    if (g_Editinfo[g_nCntEdit].rot.z > D3DX_PI)
    {
        g_Editinfo[g_nCntEdit].rot.z -= D3DX_PI * 2.0f;
    }
    if (g_Editinfo[g_nCntEdit].rot.z < -D3DX_PI)
    {
        g_Editinfo[g_nCntEdit].rot.z += D3DX_PI * 2.0f;
    }
}
//==================================================
// 現在のセーブブロックファイルのパスを取得する
//==================================================
const char* GetCurrentSaveFilePath(void)
{
    return PATH[g_CurrentSavePathSet];  // ブロックデータのファイルパスを返す
}
//==================================================
// 現在のロードブロックファイルのパスを取得する
//==================================================
const char* GetCurrentLoadFilePath(void)
{
    return PATH[g_CurrentLoadPathSet];  // ブロックデータのファイルパスを返す
}