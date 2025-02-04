//=======================================
//
// ライト処理[light.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "light.h"
#include "player.h"
#include "block.h"

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
    Player* pPlayer = GetPlayer();

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
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    if (g_LightCount >= g_LightCapacity)
    {
        g_LightCapacity *= 2; // 容量拡張
        LightInfo* newLights = (LightInfo*)realloc(g_Lights, sizeof(LightInfo) * g_LightCapacity);
        if (!newLights) return;
        g_Lights = newLights;
    }

    LightInfo* newLight = &g_Lights[g_LightCount];
    ZeroMemory(&newLight->light, sizeof(D3DLIGHT9));

    newLight->light.Type = type;
    newLight->light.Diffuse = diffuse;

    // 方向ベクトルの初期化（ゼロベクトル防止）
    if (D3DXVec3Length(&direction) == 0.0f) 
    {
        direction = D3DXVECTOR3(0, -1, 0); // デフォルトは下向き
    }
    D3DXVec3Normalize(&newLight->direction, &direction);
    newLight->light.Direction = newLight->direction;

    newLight->position = position;
    newLight->light.Position = position;

    // ライトの種類ごとの設定
    if (type == D3DLIGHT_POINT)
    {
        newLight->light.Attenuation0 = 0.0f;
        newLight->light.Attenuation1 = 0.1f;
        newLight->light.Attenuation2 = 0.01f;
        newLight->light.Range = 100.0f;
    }
    else if (type == D3DLIGHT_SPOT)
    {
        newLight->light.Range = 500.0f;
        newLight->light.Theta = D3DXToRadian(30.0f);
        newLight->light.Phi = D3DXToRadian(45.0f);
        newLight->light.Falloff = 1.0f;
    }

    pDevice->SetLight(g_LightCount, &newLight->light);
    pDevice->LightEnable(g_LightCount, TRUE);

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

    if (index < 0 || index >= g_LightCount)
    {
        return;
    }

    LPDIRECT3DDEVICE9 pDevice = GetDevice();
    LightInfo* light = &g_Lights[index];

    // 位置の更新
    light->position = newPosition;
    light->light.Position = newPosition;

    // 方向の更新（ゼロベクトル防止）
    if (D3DXVec3Length(&newDirection) == 0.0f) 
    {
        newDirection = D3DXVECTOR3(0, -1, 0);  // デフォルトは下向き
    }

    D3DXVec3Normalize(&light->direction, &newDirection);
    light->light.Direction = light->direction;

    // スポットライトの場合、レンジや角度を再設定する
    if (light->light.Type == D3DLIGHT_SPOT) 
    {
        light->light.Range = 100.0f;
        light->light.Theta = D3DXToRadian(30.0f);
        light->light.Phi = D3DXToRadian(45.0f);
        light->light.Falloff = 1.0f;
    }

    // ライトを再設定
    pDevice->SetLight(index, &light->light);

    // 念のためライトを再度有効化
    pDevice->LightEnable(index, TRUE);

}
//=============================
// プレイヤーライトの設定処理
//=============================
void AddLightPlayer(D3DLIGHTTYPE type, D3DXCOLOR diffuse)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    Player* pPlayer = GetPlayer();

    if (!pPlayer)
    {
        return;
    }

    // プレイヤーの位置と視線方向を取得
    D3DXVECTOR3 playerPos = pPlayer->pos;  // プレイヤーの現在位置
    D3DXVECTOR3 playerDir = pPlayer->forward; // プレイヤーの視線方向

    // プレイヤーの目の高さにライトを設定
    playerPos.y += 75.0f;

    // 目線方向がゼロベクトルでないか確認し、正規化
    if (D3DXVec3Length(&playerDir) == 0.0f)
    {
        playerDir = D3DXVECTOR3(0, 0, 1); // デフォルトの視線方向
    }

    D3DXVec3Normalize(&playerDir, &playerDir);

    // プレイヤーの視線方向に少し前方にライトを配置
    D3DXVECTOR3 lightPos = playerPos + (playerDir);

    // ライトを追加
    AddLight(type, diffuse, playerDir, lightPos);

}
//=============================
// スポットライトの設定処理
//=============================
void AddSpotlightToBlock(void)
{
    D3DXVECTOR3 boardPosition;
    if (!GetBlockPosition(&boardPosition))
    {
        return; // チュートリアルボードが見つからなければ何もしない
    }

    // スポットライトの向きを設定（上から照らす）
    D3DXVECTOR3 lightDirection = D3DXVECTOR3(0, -1, 0);

    // ライトの色を設定
    D3DXCOLOR lightColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    // スポットライトの位置（ボードの上に配置）
    D3DXVECTOR3 lightPosition = boardPosition + D3DXVECTOR3(0, 200.0f, 0);

    // スポットライトの追加
    AddLight(D3DLIGHT_SPOT, lightColor, lightDirection, lightPosition);
}