//=======================================
//
// ���C�g����[light.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "light.h"
#include "player.h"
#include "block.h"

#define MAX_LIGHT (3)// ���C�g�̍ő吔

typedef struct 
{
    D3DLIGHT9 light;        // ���C�g���
    D3DXVECTOR3 direction;  // ���C�g�̕����x�N�g��
    D3DXVECTOR3 position;   // ���C�g�̈ʒu
} LightInfo;

//�O���[�o���ϐ�
static LightInfo* g_Lights = NULL; // ���I�ȃ��C�g���X�g
static int g_LightCount = 0;       // ���݂̃��C�g��
static int g_LightCapacity = 0;    // ���C�g���X�g�̗e��

//=============================
//���C�g�̏���������
//=============================
void InitLight(void)
{
    Player* pPlayer = GetPlayer();

    // �����e�ʂŃ��C�g���X�g���m��
    g_LightCapacity = MAX_LIGHT;
    g_Lights = (LightInfo*)malloc(sizeof(LightInfo) * g_LightCapacity);
    if (!g_Lights) 
    {
        // �������m�ێ��s
        g_LightCapacity = 0;
        return;
    }

    g_LightCount = 0; // ���݂̃��C�g�������Z�b�g

}
//=============================
// ���C�g�̒ǉ�����
//=============================
void AddLight(D3DLIGHTTYPE type, D3DXCOLOR diffuse, D3DXVECTOR3 direction, D3DXVECTOR3 position) 
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    if (g_LightCount >= g_LightCapacity)
    {
        g_LightCapacity *= 2; // �e�ʊg��
        LightInfo* newLights = (LightInfo*)realloc(g_Lights, sizeof(LightInfo) * g_LightCapacity);
        if (!newLights) return;
        g_Lights = newLights;
    }

    LightInfo* newLight = &g_Lights[g_LightCount];
    ZeroMemory(&newLight->light, sizeof(D3DLIGHT9));

    newLight->light.Type = type;
    newLight->light.Diffuse = diffuse;

    // �����x�N�g���̏������i�[���x�N�g���h�~�j
    if (D3DXVec3Length(&direction) == 0.0f) 
    {
        direction = D3DXVECTOR3(0, -1, 0); // �f�t�H���g�͉�����
    }
    D3DXVec3Normalize(&newLight->direction, &direction);
    newLight->light.Direction = newLight->direction;

    newLight->position = position;
    newLight->light.Position = position;

    // ���C�g�̎�ނ��Ƃ̐ݒ�
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
// ���C�g�̍폜����
//=============================
void RemoveLight(int index) 
{
    // �͈͊O�`�F�b�N
    if (index < 0 || index >= g_LightCount) 
    {
        return; // �����ȃC���f�b�N�X
    }

    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // �폜���郉�C�g�𖳌���
    pDevice->LightEnable(index, FALSE);

    // ���C�g�����X�g����폜�i�㑱�̃��C�g��O�ɋl�߂�j
    for (int nLight = index; nLight < g_LightCount - 1; nLight++)
    {
        g_Lights[nLight] = g_Lights[nLight + 1];
        // ���C�g�̃C���f�b�N�X���Đݒ�
        pDevice->SetLight(nLight, &g_Lights[nLight].light);
        pDevice->LightEnable(nLight, TRUE);
    }

    // ���C�g��������
    g_LightCount--;
}
//=============================
//���C�g�̏I������
//=============================
void UninitLight(void)
{

    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // �S�Ẵ��C�g�𖳌���
    for (int nLight = 0; nLight < g_LightCount; nLight++)
    {
        pDevice->LightEnable(nLight, FALSE);
    }

    // �����������
    free(g_Lights);
    g_Lights = NULL;
    g_LightCount = 0;
    g_LightCapacity = 0;

}
//=============================
//���C�g�̍X�V����
//=============================
void UpdateLight(int index, D3DXVECTOR3 newPosition, D3DXVECTOR3 newDirection) 
{

    if (index < 0 || index >= g_LightCount)
    {
        return;
    }

    LPDIRECT3DDEVICE9 pDevice = GetDevice();
    LightInfo* light = &g_Lights[index];

    // �ʒu�̍X�V
    light->position = newPosition;
    light->light.Position = newPosition;

    // �����̍X�V�i�[���x�N�g���h�~�j
    if (D3DXVec3Length(&newDirection) == 0.0f) 
    {
        newDirection = D3DXVECTOR3(0, -1, 0);  // �f�t�H���g�͉�����
    }

    D3DXVec3Normalize(&light->direction, &newDirection);
    light->light.Direction = light->direction;

    // �X�|�b�g���C�g�̏ꍇ�A�����W��p�x���Đݒ肷��
    if (light->light.Type == D3DLIGHT_SPOT) 
    {
        light->light.Range = 100.0f;
        light->light.Theta = D3DXToRadian(30.0f);
        light->light.Phi = D3DXToRadian(45.0f);
        light->light.Falloff = 1.0f;
    }

    // ���C�g���Đݒ�
    pDevice->SetLight(index, &light->light);

    // �O�̂��߃��C�g���ēx�L����
    pDevice->LightEnable(index, TRUE);

}
//=============================
// �v���C���[���C�g�̐ݒ菈��
//=============================
void AddLightPlayer(D3DLIGHTTYPE type, D3DXCOLOR diffuse)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    Player* pPlayer = GetPlayer();

    if (!pPlayer)
    {
        return;
    }

    // �v���C���[�̈ʒu�Ǝ����������擾
    D3DXVECTOR3 playerPos = pPlayer->pos;  // �v���C���[�̌��݈ʒu
    D3DXVECTOR3 playerDir = pPlayer->forward; // �v���C���[�̎�������

    // �v���C���[�̖ڂ̍����Ƀ��C�g��ݒ�
    playerPos.y += 75.0f;

    // �ڐ��������[���x�N�g���łȂ����m�F���A���K��
    if (D3DXVec3Length(&playerDir) == 0.0f)
    {
        playerDir = D3DXVECTOR3(0, 0, 1); // �f�t�H���g�̎�������
    }

    D3DXVec3Normalize(&playerDir, &playerDir);

    // �v���C���[�̎��������ɏ����O���Ƀ��C�g��z�u
    D3DXVECTOR3 lightPos = playerPos + (playerDir);

    // ���C�g��ǉ�
    AddLight(type, diffuse, playerDir, lightPos);

}
//=============================
// �X�|�b�g���C�g�̐ݒ菈��
//=============================
void AddSpotlightToBlock(void)
{
    D3DXVECTOR3 boardPosition;
    if (!GetBlockPosition(&boardPosition))
    {
        return; // �`���[�g���A���{�[�h��������Ȃ���Ή������Ȃ�
    }

    // �X�|�b�g���C�g�̌�����ݒ�i�ォ��Ƃ炷�j
    D3DXVECTOR3 lightDirection = D3DXVECTOR3(0, -1, 0);

    // ���C�g�̐F��ݒ�
    D3DXCOLOR lightColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    // �X�|�b�g���C�g�̈ʒu�i�{�[�h�̏�ɔz�u�j
    D3DXVECTOR3 lightPosition = boardPosition + D3DXVECTOR3(0, 200.0f, 0);

    // �X�|�b�g���C�g�̒ǉ�
    AddLight(D3DLIGHT_SPOT, lightColor, lightDirection, lightPosition);
}