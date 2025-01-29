//=======================================
//
// ���C�g����[light.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "light.h"

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
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // �e�ʂ��s�����Ă���ꍇ�A�e�ʂ��g��
    if (g_LightCount >= g_LightCapacity)
    {
        g_LightCapacity *= 2; // �e�ʂ�2�{�Ɋg��
        LightInfo* newLights = (LightInfo*)realloc(g_Lights, sizeof(LightInfo) * g_LightCapacity);
        if (!newLights)
        {
            // realloc���s���͗e�ʂ����ɖ߂�
            g_LightCapacity /= 2;
            return;
        }
        g_Lights = newLights;
    }

    // �V�������C�g����ݒ�
    LightInfo* newLight = &g_Lights[g_LightCount];
    ZeroMemory(&newLight->light, sizeof(D3DLIGHT9));

    // ���C�g�̎�ނƐF��ݒ�
    newLight->light.Type = type;
    newLight->light.Diffuse = diffuse;

    // ���C�g�̈ʒu�ƕ�����ݒ�
    D3DXVECTOR3 normalizedDirection;
    D3DXVec3Normalize(&normalizedDirection, &direction); // ���K�����ꂽ�����x�N�g�����擾
    newLight->direction = normalizedDirection;
    newLight->light.Direction = normalizedDirection;


    newLight->position = position; // ���C�g�̈ʒu��ۑ�
    newLight->light.Position = position; // ���C�g���ɐݒ�

    // �_�����̐ݒ�
    if (type == D3DLIGHT_POINT) 
    {
        newLight->light.Attenuation0 = 0.0f;  // �����Ȃ�
        newLight->light.Attenuation1 = 0.1f;  // ���`����
        newLight->light.Attenuation2 = 0.01f; // �񎟌���
        newLight->light.Range = 100.0f;      // �Ǝ˔͈�
    }

    // �X�|�b�g���C�g�̐ݒ�
    if (type == D3DLIGHT_SPOT)
    {
        newLight->light.Range = 100.0f;                   // �Ƃ炷�͈�
        newLight->light.Theta = D3DXToRadian(30.0f); // �����̃X�|�b�g�p�x
        newLight->light.Phi = D3DXToRadian(45.0f);  // �O���̃X�|�b�g�p�x
        newLight->light.Falloff = 0.2f;                   // ���̌���
    }

    // Direct3D�f�o�C�X�Ƀ��C�g��ݒ�
    pDevice->SetLight(g_LightCount, &newLight->light);

    // ���C�g��L����
    pDevice->LightEnable(g_LightCount, TRUE);

    // ���C�g���𑝉�
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

    // �͈͊O�`�F�b�N
    if (index < 0 || index >= g_LightCount)
    {
        return; // �����ȃC���f�b�N�X
    }

    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // �ʒu�̍X�V
    g_Lights[index].position = newPosition;
    g_Lights[index].light.Position = newPosition;

    // �����x�N�g���̍X�V
    D3DXVECTOR3 normalizedDirection;
    D3DXVec3Normalize(&normalizedDirection, &newDirection); // ���K��
    g_Lights[index].direction = normalizedDirection;
    g_Lights[index].light.Direction = normalizedDirection;

    // Direct3D�f�o�C�X�ɍĐݒ�
    pDevice->SetLight(index, &g_Lights[index].light);
}
