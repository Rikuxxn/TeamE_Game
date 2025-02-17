//=======================================
//
// ���C������[main.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MAIN_H_//���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_//2�d�C���N���[�h�h�~�̃}�N����`


#include<windows.h>
#include "d3dx9.h"															//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)										//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"															//���͏����ɕK�v
#include "Xinput.h"															//�W���C�p�b�h�����ɕK�v
#include "xaudio2.h"														//�T�E���h�����ɕK�v


//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")												//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")											//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")											//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")											//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")											//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")											//�W���C�p�b�h�����ɕK�v


//�}�N����`
#define CLASS_NAME "WindowClass"											//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "ARCADE NIGHTMARE"											//�E�B���h�E�̖��O(�L���v�V�����ɕ\��)
#define SCREEN_WIDTH (1280.0f)													//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720.0f)													//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���W�E�@���E�J���[�E�e�N�X�`��
//#define FVF_VERTEX_3D_MULTI (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2)	// �}���`�e�N�X�`��


#define FIELD_LEFT (280.0f)//��720.0f
#define FIELD_RIGHT (1000.0f)
#define FIELD_TOP (50.0f)//����400.0f
#define FIELD_UNDER (450.0f)

#define BALLFIELD_LEFT (230.0f)//��820.0f
#define BALLFIELD_RIGHT (1050.0f)
#define BALLFIELD_TOP (50.0f)//����400.0f
#define BALLFIELD_UNDER (650.0f)


//��ʂ̎��
typedef enum
{
	MODE_RECOMMEND = 0,		//�������
	MODE_TITLE,				//�^�C�g�����
	MODE_TUTORIAL,			//�`���[�g���A�����
	MODE_TUTORIAL2,			//�`���[�g���A�����2
	MODE_GAME,				//�Q�[�����
	MODE_RESULT,			//���U���g���
	MODE_FOUND,				//�G�Ɍ����������̉��
	MODE_EDIT,
	MODE_MAX
}MODE;


//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//���W�ϊ��p�W��
	D3DCOLOR col;			//���W�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
}VERTEX_2D;


//���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	D3DXVECTOR3 nor;		//�@���x�N�g��
	D3DCOLOR col;			//���W�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
}VERTEX_3D;

////���_���[3D_MULTI]�̍\���̂��`
//typedef struct
//{
//	D3DXVECTOR3 pos;		//���_���W
//	D3DXVECTOR3 nor;		//�@���x�N�g��
//	D3DCOLOR col;			//���W�J���[
//	D3DXVECTOR2 tex;		//�e�N�X�`�����W0
//	D3DXVECTOR2 texM;		//�e�N�X�`�����W1
//}VERTEX_3D_MULTI;

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

LPDIRECT3DDEVICE9 GetDevice(void);

void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
void onWireFrame(void);
void offWireFrame(void);
void ToggleFullscreen(HWND hWnd);// �E�B���h�E���t���X�N���[��
MODE GetMode(void);
bool GetFullScreen(void);
void SetupVertexFog(LPDIRECT3DDEVICE9 pDevice, DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density);
void DrawAPass(int Answer, int Answer2, int Answer3, int Answer4);

#endif
