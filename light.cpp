//=======================================
//
// ライト処理[light.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "light.h"

#define MAX_LIGHT (3)// ライトの最大数

typedef struct 
{
    D3DLIGHT9 light;        // ライト情報
    D3DXVECTOR3 direction;  // ライトの方向ベクトル
    D3DXVECTOR3 position;   // ライトの位置
} LightInfo;

//グローバル変数
static LightInfo* g_Lights = NULL; // 動的なライトリスト
static int g_LightCount = 0;       // 現在のライト数
static int g_LightCapacity = 0;    // ライトリストの容量

//=============================
//ライトの初期化処理
//=============================
void InitLight(void)
{

    // 初期容量でライトリストを確保
    g_LightCapacity = MAX_LIGHT;
    g_Lights = (LightInfo*)malloc(sizeof(LightInfo) * g_LightCapacity);
    if (!g_Lights) 
    {
        // メモリ確保失敗
        g_LightCapacity = 0;
        return;
    }

    g_LightCount = 0; // 現在のライト数をリセット
}
//=============================
// ライトの追加処理
//=============================
void AddLight(D3DLIGHTTYPE type, D3DXCOLOR diffuse, D3DXVECTOR3 direction, D3DXVECTOR3 position) 
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // 容量が不足している場合、容量を拡張
    if (g_LightCount >= g_LightCapacity)
    {
        g_LightCapacity *= 2; // 容量を2倍に拡張
        LightInfo* newLights = (LightInfo*)realloc(g_Lights, sizeof(LightInfo) * g_LightCapacity);
        if (!newLights)
        {
            // realloc失敗時は容量を元に戻す
            g_LightCapacity /= 2;
            return;
        }
        g_Lights = newLights;
    }

    // 新しいライト情報を設定
    LightInfo* newLight = &g_Lights[g_LightCount];
    ZeroMemory(&newLight->light, sizeof(D3DLIGHT9));

    // ライトの種類と色を設定
    newLight->light.Type = type;
    newLight->light.Diffuse = diffuse;

    // ライトの位置と方向を設定
    D3DXVECTOR3 normalizedDirection;
    D3DXVec3Normalize(&normalizedDirection, &direction); // 正規化された方向ベクトルを取得
    newLight->direction = normalizedDirection;
    newLight->light.Direction = normalizedDirection;


    newLight->position = position; // ライトの位置を保存
    newLight->light.Position = position; // ライト情報に設定

    // 点光源の設定
    if (type == D3DLIGHT_POINT) 
    {
        newLight->light.Attenuation0 = 0.0f;  // 減衰なし
        newLight->light.Attenuation1 = 0.1f;  // 線形減衰
        newLight->light.Attenuation2 = 0.01f; // 二次減衰
        newLight->light.Range = 100.0f;      // 照射範囲
    }

    // スポットライトの設定
    if (type == D3DLIGHT_SPOT)
    {
        newLight->light.Range = 100.0f;                   // 照らす範囲
        newLight->light.Theta = D3DXToRadian(30.0f); // 内側のスポット角度
        newLight->light.Phi = D3DXToRadian(45.0f);  // 外側のスポット角度
        newLight->light.Falloff = 0.2f;                   // 光の減衰
    }

    // Direct3Dデバイスにライトを設定
    pDevice->SetLight(g_LightCount, &newLight->light);

    // ライトを有効化
    pDevice->LightEnable(g_LightCount, TRUE);

    // ライト数を増加
    g_LightCount++;
}
//=============================
// ライトの削除処理
//=============================
void RemoveLight(int index) 
{
    // 範囲外チェック
    if (index < 0 || index >= g_LightCount) 
    {
        return; // 無効なインデックス
    }

    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // 削除するライトを無効化
    pDevice->LightEnable(index, FALSE);

    // ライトをリストから削除（後続のライトを前に詰める）
    for (int nLight = index; nLight < g_LightCount - 1; nLight++)
    {
        g_Lights[nLight] = g_Lights[nLight + 1];
        // ライトのインデックスを再設定
        pDevice->SetLight(nLight, &g_Lights[nLight].light);
        pDevice->LightEnable(nLight, TRUE);
    }

    // ライト数を減少
    g_LightCount--;
}
//=============================
//ライトの終了処理
//=============================
void UninitLight(void)
{

    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // 全てのライトを無効化
    for (int nLight = 0; nLight < g_LightCount; nLight++)
    {
        pDevice->LightEnable(nLight, FALSE);
    }

    // メモリを解放
    free(g_Lights);
    g_Lights = NULL;
    g_LightCount = 0;
    g_LightCapacity = 0;

}
//=============================
//ライトの更新処理
//=============================
void UpdateLight(int index, D3DXVECTOR3 newPosition, D3DXVECTOR3 newDirection) 
{

    // 範囲外チェック
    if (index < 0 || index >= g_LightCount)
    {
        return; // 無効なインデックス
    }

    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // 位置の更新
    g_Lights[index].position = newPosition;
    g_Lights[index].light.Position = newPosition;

    // 方向ベクトルの更新
    D3DXVECTOR3 normalizedDirection;
    D3DXVec3Normalize(&normalizedDirection, &newDirection); // 正規化
    g_Lights[index].direction = normalizedDirection;
    g_Lights[index].light.Direction = normalizedDirection;

    // Direct3Dデバイスに再設定
    pDevice->SetLight(index, &g_Lights[index].light);
}
