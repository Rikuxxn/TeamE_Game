//=======================================
//
// ���C�g����[light.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "light.h"

#define MAX_LIGHT (3)

//�O���[�o���ϐ�
D3DLIGHT9 g_light[MAX_LIGHT];//���C�g���
D3DXVECTOR3 g_vecDir[MAX_LIGHT];//���C�g�̕����x�N�g��

//=============================
//���C�g�̏���������
//=============================
void InitLight(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	ZeroMemory(&g_light, sizeof(g_light));//�����̎�

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_vecDir[nCntLight];

		//���C�g�̎�ނ�ݒ�
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�g�U����ݒ�
		g_light[nCntLight].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}

	//���C�g�̕�����ݒ�
	g_vecDir[0] = D3DXVECTOR3(-0.3f, -0.8f, 0.4f);
	g_vecDir[1] = D3DXVECTOR3(0.3f, -1.0f, 0.4f);
	g_vecDir[2] = D3DXVECTOR3(-0.4f, 0.8f, -0.9f);

	for (int nCntLight2 = 0; nCntLight2 < MAX_LIGHT; nCntLight2++)
	{

		//���K������(�傫��1�̃x�N�g���ɂ���)
		D3DXVec3Normalize(&g_vecDir[nCntLight2], &g_vecDir[nCntLight2]);

		g_light[nCntLight2].Direction = g_vecDir[nCntLight2];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight2, &g_light[nCntLight2]);//0�Ԗڂ̃��C�g��ݒ�

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight2, true);//0�Ԗڂ̃��C�g��L��

	}

}
//=============================
//���C�g�̏I������
//=============================
void UninitLight(void)
{




}
//=============================
//���C�g�̍X�V����
//=============================
void UpdateLight(void)
{




}
