//=======================================
//
// ライト処理 [light.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "light.h"
#include "player.h"
#include "block.h"
#include "camera.h"

#define MAX_LIGHT (10)                  // ライトの最大数

typedef struct 
{
    D3DLIGHT9 light;                    // ライト情報
    D3DXVECTOR3 direction;              // ライトの方向ベクトル
    D3DXVECTOR3 position;               // ライトの位置
} LightInfo;

//グローバル変数
static LightInfo* g_Lights = NULL;      // 動的なライトリスト
static int g_LightCount = 0;            // 現在のライト数
static int g_LightCapacity = 0;         // ライトリストの容量

static bool g_bLightOn = true;          // ライトのON/OFF状態
static float g_LightTimer = 0.0f;       // タイマー
static float g_NextBlinkTime = 0.0f;    // 次に点滅する時間
static int g_BlinkingLightIndex = -1;   // 点滅するライトのインデックス

//=============================
// ライトの初期化処理
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
int AddLight(D3DLIGHTTYPE type, D3DXCOLOR diffuse, D3DXVECTOR3 direction, D3DXVECTOR3 position) 
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    if (g_LightCount >= g_LightCapacity)
    {
        g_LightCapacity *= 2; // 容量拡張
        LightInfo* newLights = (LightInfo*)realloc(g_Lights, sizeof(LightInfo) * g_LightCapacity);
        if (!newLights) return - 1;
        g_Lights = newLights;
    }

    int newIndex = g_LightCount;

    LightInfo* newLight = &g_Lights[newIndex];
    ZeroMemory(&newLight->light, sizeof(D3DLIGHT9));

    newLight->light.Type = type;
    newLight->light.Diffuse = diffuse;                  // 光の強さ

    // 方向ベクトルの初期化（ゼロベクトル防止）
    if (D3DXVec3Length(&direction) == 0.0f) 
    {
        direction = D3DXVECTOR3(0, -1, 0);              // デフォルトは下向き
    }

    D3DXVec3Normalize(&newLight->direction, &direction);
    newLight->light.Direction = newLight->direction;

    newLight->position = position;
    newLight->light.Position = position;

    // ライトの種類ごとの設定
    if (type == D3DLIGHT_POINT)
    {
        newLight->light.Attenuation0 = 0.0f;
        newLight->light.Attenuation1 = 0.02f;
        newLight->light.Attenuation2 = 0.0f;
        newLight->light.Range = 105.0f;

        // ポイントライトは方向を持たないから Direction は設定しない
    }
    else if (type == D3DLIGHT_SPOT)
    {
        newLight->light.Range = 100.0f;
        newLight->light.Theta = D3DXToRadian(30.0f);
        newLight->light.Phi = D3DXToRadian(45.0f);
        newLight->light.Falloff = 1.0f;
    }

    pDevice->SetLight(newIndex, &newLight->light);
    pDevice->LightEnable(newIndex, TRUE);

    g_LightCount++;

    return newIndex; // 追加したライトのインデックスを返す
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
// ライトの終了処理
//=============================
void UninitLight(void)
{

    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // すべてのライトを無効化
    for (int i = 0; i < g_LightCount; i++)
    {
        pDevice->LightEnable(i, FALSE);
    }

    // メモリ解放
    free(g_Lights);
    g_Lights = NULL;
    g_LightCount = 0;
    g_LightCapacity = 0;
}
//=============================
// ライトの更新処理
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
// ライト点滅の更新処理
//=============================
void UpdateLightBlinking(float deltaTime)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    if (g_BlinkingLightIndex == -1)
    {
        return; // 点滅させるライトがない場合は何もしない
    }

    g_LightTimer += deltaTime;

    // 次の点滅時間を超えたらON/OFFを切り替える
    if (g_LightTimer > g_NextBlinkTime)
    {
        g_bLightOn = !g_bLightOn; // フラグを反転

        pDevice->SetLight(g_BlinkingLightIndex, &g_Lights[g_BlinkingLightIndex].light);
        pDevice->LightEnable(g_BlinkingLightIndex, g_bLightOn);

        g_LightTimer = 0.0f; // タイマーをリセット

        // ONの時間（点滅時）は短くする
        if (g_bLightOn)
        {
            g_NextBlinkTime = (rand() % 950 + 100) / 1000.0f; // 0.05〜0.2秒
        }
        // OFFの時間（消灯時）は長めにする
        else
        {
            g_NextBlinkTime = (rand() % 900 + 300) / 1000.0f; // 0.3〜1.0秒
        }
    }
}
//=============================
// プレイヤーライトの設定処理
//=============================
void AddLightPlayer(D3DLIGHTTYPE type, D3DXCOLOR diffuse)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();
    Player* pPlayer = GetPlayer();
    Camera* pCamera = GetCamera();


    if (!pPlayer)
    {
        return;
    }

    // プレイヤーの視点位置（目の高さ）を設定
    D3DXVECTOR3 playerPos = pCamera->posV;
    playerPos.y += 75.0f; // 身長に合わせて調整

    // 視線方向を取得
    D3DXVECTOR3 playerDir = pPlayer->forward;

    // 視線方向がゼロベクトルの場合の対策
    if (D3DXVec3Length(&playerDir) == 0.0f)
    {
        playerDir = D3DXVECTOR3(0, 0, 1); // デフォルトで前方を向く
    }

    D3DXVec3Normalize(&playerDir, &playerDir);

    // ライトの位置をプレイヤーの視点にセット
    D3DXVECTOR3 lightPos = playerPos; // 目の位置

    // 一人称視点なので、ライトを視線方向に向ける
    int lightIndex = AddLight(type, diffuse, playerDir, lightPos);

    // スポットライトの場合はさらに角度を設定
    if (lightIndex != -1 && type == D3DLIGHT_SPOT)
    {
        g_Lights[lightIndex].light.Range = 450.0f;  // スポットライトの到達距離
        g_Lights[lightIndex].light.Theta = D3DXToRadian(20.0f); // コア部分の光の広がり
        g_Lights[lightIndex].light.Phi = D3DXToRadian(40.0f); // 外側の光の広がり
        g_Lights[lightIndex].light.Falloff = 1.0f; // フォールオフ（光の減衰率）

        // ライトを更新
        pDevice->SetLight(lightIndex, &g_Lights[lightIndex].light);
    }
}
//=============================
// ポイントライトの設定処理
//=============================
void AddPointlightToBlock(BLOCKTYPE nType)
{
    D3DXVECTOR3 blockPosition;

    if (!GetBlockPosition(&blockPosition))
    {
        return; // タイトルボード または 非常口 が見つからなければ何もしない
    }

    D3DXVECTOR3 lightDirection;
    D3DXVECTOR3 lightOffset;
    D3DXCOLOR lightColor;

    // ブロックの種類に応じてライトの設定を変更
    switch (nType)
    {
    case BLOCKTYPE_TITLEBOARD:
        lightDirection = D3DXVECTOR3(0, -1, 0);  // 真下に向ける
        lightOffset = D3DXVECTOR3(-80.0f, 80.0f, 0.0f);
        lightColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        break;

    case BLOCKTYPE_EXIT_SIGN:
        lightDirection = D3DXVECTOR3(0, 0, 1);
        lightOffset = D3DXVECTOR3(0.0f, 30.0f, -50.0f);
        lightColor = D3DXCOLOR(0.0f, 0.8f, 0.0f, 0.5f);
        break;

    default:
        break;
    }

    // ライトの位置をブロックの位置にオフセットを加えて決定
    D3DXVECTOR3 lightPosition = blockPosition + lightOffset;

    // AddLight の戻り値を g_BlinkingLightIndex に設定
    int newLightIndex = AddLight(D3DLIGHT_POINT, lightColor, D3DXVECTOR3(0, -1, 0), lightPosition);

    if (newLightIndex != -1)
    {
        g_BlinkingLightIndex = newLightIndex;

        g_NextBlinkTime = (rand() % 2000) / 1000.0f; // 0.0〜2.0秒の間でランダム
    }
    else
    {
        g_BlinkingLightIndex = -1; // 追加に失敗した場合、無効なインデックスにする
    }
}