//=======================================
//
// ���C������[main.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

#include "main.h"
#include "fade.h"
#include "input.h"
#include "result.h"
#include "game.h"
#include "title.h"
#include "model.h"
#include "camera.h"
#include "block.h"
#include "edit.h"
#include "player.h"
#include "enemy.h"

//�v���g�^�C�v�錾
void DrawFPS(void);
void DrawOption(void);
void DrawEditInfo(void);
void DrawTitleInfo(void);

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;//DirectX3D�I�u�W�F�N�g�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;//�t�H���g�ւ̃|�C���^

LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_mode = MODE_TITLE;//���݂̃��[�h
int g_nCountFPS = 0;//FPS�J�E���^�[

RECT g_windowRect;                        //�E�B���h�E��؂�ւ��邽�߂̕ϐ�
bool g_isFullscreen = false;            //�E�B���h�E��؂�ւ��邽�߂̃t���O

//=======================================
//���C���֐�
//=======================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);//���������[�N���m

	DWORD dwCurrentTime;//���ݎ���
	DWORD dwExecLastTime;//�Ō�ɏ�����������


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),             //WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,                     //�E�B���h�E�̃X�^�C��
		WindowProc,                     //�E�B���h�E�v���V�[�W��
		0,                              //0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,                              //0�ɂ���
		hInstance,                      //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),     //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),     //�N���C�A���g�̈�̔w�i�F
		NULL,                           //���j���[�o�[
		CLASS_NAME,                     //�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)  //�t�@�C���̃A�C�R��
	};


	HWND hWnd;   //�E�B���h�E�n���h��
	MSG msg;     //���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);


	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);


	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,		//�g���E�B���h�E�X�^�C��
		CLASS_NAME,					//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,				//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,				//�E�B���h�E�̍���x���W
		CW_USEDEFAULT,				//����y���W

		(rect.right - rect.left),	//��
		(rect.bottom - rect.top),	//����

		NULL,						//�e�E�B���h�E�̃n���h��
		NULL,						//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,					//�C���X�^���X�n���h��
		NULL);						//�E�B���h�E�쐬�f�[�^


	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}


	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;				//����������
	dwExecLastTime = timeGetTime();	//���ݎ������擾�i�ۑ��j


	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	DWORD dwFrameCount;				//�t���[���J�E���g
	DWORD dwFPSLastTime;			//�Ō��FPS���v����������


	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();


	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);		//���z���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);		//�E�B���h�E
			}

		}
		else
		{//DirectX�̏���


			dwCurrentTime = timeGetTime();//���ݎ������擾


			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;//FPS���v������������ۑ�

				dwFrameCount = 0;//�t���[���J�E���g���N���A

			}


			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��

				dwExecLastTime = dwCurrentTime;//�����J�n�̎���[���ݎ���]��ۑ�


				dwCurrentTime = timeGetTime();//���ݎ������擾


				dwFrameCount++;//�t���[���J�E���g�����Z


				//�X�V����
				Update();


				//�`�揈��
				Draw();

			}

		}
	}

	//�I������
	Uninit();


	//����\��߂�
	timeEndPeriod(1);


	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}
//=============================================
//�E�B���h�E�v���V�[�W��
//=============================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	//HDC hDC;

	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	switch (uMsg)
	{
	case WM_DESTROY:  //�E�B���h�E�j���̃��b�Z�[�W
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);

		break;
	case WM_KEYDOWN://�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE://[ESC]�L�[�������ꂽ
			//�E�B���h�E��j������
			DestroyWindow(hWnd);
			break;
		case VK_F11:
			ToggleFullscreen(hWnd);//F11�Ńt���X�N���[��
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//����̏������J��Ԃ�
}
//=============================================
//����������
//=============================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;//�v���[���e�[�V�����p�����[�^



	//DirectX3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}


	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//�Q�[����ʃT�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//�Q�[����ʃT�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;							//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;							//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��



	//DirectX3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//DirectX3D�f�o�C�X�̐���
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//DirectX3D�f�o�C�X�̐���
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}

		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);


	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);



	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);



	// �L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �W���C�p�b�h�̏���������
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	// �}�E�X�̏���������
	if (FAILED(InitMouse(hInstance, hWnd)))
	{
		return E_FAIL;
	}


	////�T�E���h�̏���������
	//InitSound(hWnd);


	//���[�h�̐ݒ�
	SetMode(g_mode);


	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);


	return S_OK;

}
//=============================================
//�I������
//=============================================
void Uninit(void)
{

	////�T�E���h�̏���������
	//UninitSound();


	//�W���C�p�b�h�̏I������
	UninitJoypad();


	//�L�[�{�[�h�̏I������
	UninitKeyboard();


	//�}�E�X�̏I������
	UninitMouse();


	//�t�F�[�h�̏I������
	UninitFade();


	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();

		g_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();

		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();

		g_pD3D = NULL;
	}

}
//=============================================
//�X�V����
//=============================================
void Update(void)
{

	//�W���C�p�b�h�̍X�V����
	UpdateJoypad();


	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();


	//�}�E�X�̍X�V����
	UpdateMouse();


	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����
		UpdateTitle();
		break;

	//case MODE_TUTORIAL://�`���[�g���A�����
	//	UpdateTutorial();
	//	break;

	//case MODE_TUTORIAL2://�`���[�g���A�����2
	//	UpdateTutorial2();
	//	break;

	case MODE_GAME://�Q�[�����
		UpdateGame();
		break;

	case MODE_RESULT://���U���g���
		UpdateResult();
		break;

	//case MODE_RANKING://�����L���O���
	//	UpdateRanking();
	//	break;

	case MODE_EDIT://�G�f�B�b�g���
		UpdateEdit();
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();

}
//=============================================
//�`�揈��
//=============================================
void Draw(void)
{
	bool bExit = GetExit();

	Camera* pCamera = GetCamera();

	//LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	////�f�o�C�X�̎擾
	//pDevice = GetDevice();

	////�r���[�|�[�g�̐ݒ�
	//pDevice->SetViewport(&pCamera->viewport);

	//��ʃN���A
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		switch (g_mode)
		{
		case MODE_TITLE://�^�C�g�����
			DrawTitle();

#ifdef _DEBUG
			//�^�C�g�����̕\��
			DrawTitleInfo();
#endif
			break;

		//case MODE_TUTORIAL://�`���[�g���A�����
		//	DrawTutorial();
		//	break;

		//case MODE_TUTORIAL2://�`���[�g���A�����2
		//	DrawTutorial2();
		//	break;

		case MODE_GAME://�Q�[�����
			DrawGame();

#ifdef _DEBUG
			//������@�̕\��
			DrawOption();
#endif

			break;

		case MODE_RESULT://���U���g���
			DrawResult();

			break;

		//case MODE_RANKING://�����L���O���
		//	DrawRanking();
		//	break;
#ifdef _DEBUG
		case MODE_EDIT://�G�f�B�b�g���
			DrawEdit();

			//�G�f�B�^�[���̕\��
			DrawEditInfo();

			break;
#endif

		}

		//�t�F�[�h�̕`�揈��
		DrawFade();


#ifdef _DEBUG

		//FPS�̕\��
		DrawFPS();

#endif
		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================
//FPS�\������
//=============================================
void DrawFPS(void)
{

	RECT rect = { 5, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	char aStr[256];


	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);


	//�e�L�X�g�̕`��
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
//=============================================
//������@�\������
//=============================================
void DrawOption(void)
{
	Camera* pCamera = GetCamera();
	CAMERAMODE* pCameraMode = GetCameraMode();
	Player* pPlayer = GetPlayer();
	Enemy* pEnemy = GetEnemy();
	Block* pBlock = GetBlock();

	RECT rect = { 5, 20, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect2 = { 5, 40, SCREEN_WIDTH, SCREEN_HEIGHT };

	char aStr[128];
	char aStr2[128];


	//������ɑ��
	sprintf(&aStr[0], "�v���C���[�̈ʒu (%f, %f, %f)\n",pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	sprintf(&aStr2[0], "�J�����̌��� (%f, %f, %f)\n", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);


	//�e�L�X�g�̕`��
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr2[0], -1, &rect2, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
//=============================================
//�G�f�B�^�[���\������
//=============================================
void DrawEditInfo(void)
{
	Camera* pCamera = GetCamera();

	RECT rect = { 5, 20, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect2 = { 5, 40, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect3 = { 5, 60, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect4 = { 5, 100, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect5 = { 5, 120, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect6 = { 5, 140, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect7 = { 5, 160, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect8 = { 5, 180, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect9 = { 5, 220, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect10 = { 5, 240, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect11 = { 5, 260, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rect12 = { 5, 280, SCREEN_WIDTH, SCREEN_HEIGHT };

	char aStr[128];
	char aStr2[128];
	char aStr3[128];
	char aStr4[128];
	char aStr5[128];
	char aStr6[128];
	char aStr7[128];
	char aStr8[128];
	char aStr9[128];
	char aStr10[128];
	char aStr11[128];
	char aStr12[128];

	wsprintf(&aStr[0], "�^�C�g����� [F1]\n");
	wsprintf(&aStr2[0], "�u���b�N�z�u���̕ۑ� [F7]\n");
	wsprintf(&aStr3[0], "�O��̃u���b�N�z�u���̓ǂݍ��� [F6]\n");
	wsprintf(&aStr4[0], "�u���b�N�̕��s�ړ� : [��/��/��/��]\n");
	wsprintf(&aStr5[0], "�u���b�N�̐����ړ� : [U/J]\n");
	wsprintf(&aStr6[0], "�u���b�N�̎�ޕύX : [�}�E�X�z�C�[��]\n");
	wsprintf(&aStr7[0], "�u���b�N�̐ݒu : [ENTER]\n");
	wsprintf(&aStr8[0], "�u���b�N�̔j�� : [DELETE]\n");
	wsprintf(&aStr9[0], "===============================\n");
	wsprintf(&aStr10[0], "  �J����������@\n");
	wsprintf(&aStr11[0], "===============================\n");
	wsprintf(&aStr12[0], "  �J�����ړ� : [W/A/S/D]\n");

	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 255, 255));
	g_pFont->DrawTextA(NULL, &aStr2[0], -1, &rect2, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr3[0], -1, &rect3, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr4[0], -1, &rect4, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr5[0], -1, &rect5, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr6[0], -1, &rect6, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr7[0], -1, &rect7, DT_LEFT, D3DCOLOR_RGBA(0, 255, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr8[0], -1, &rect8, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr9[0], -1, &rect9, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr10[0], -1, &rect10, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr11[0], -1, &rect11, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
	g_pFont->DrawTextA(NULL, &aStr12[0], -1, &rect12, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));

}
//=============================================
//�^�C�g�����\������
//=============================================
void DrawTitleInfo(void)
{
	RECT rect = { 5, 20, SCREEN_WIDTH, SCREEN_HEIGHT };

	char aStr[128];

	wsprintf(&aStr[0], "�G�f�B�^�[���[�h [F1]\n");

	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 255, 0, 255));

}
//=============================================
//���[�h�̐ݒ�
//=============================================
void SetMode(MODE mode)
{

	//���݂̉�ʂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����
		UninitTitle();
		break;

	//case MODE_TUTORIAL://�`���[�g���A�����
	//	UninitTutorial();
	//	break;

	//case MODE_TUTORIAL2://�`���[�g���A�����2
	//	UninitTutorial2();
	//	break;

	case MODE_GAME://�Q�[�����
		UninitGame();
		break;

	case MODE_RESULT://���U���g���
		UninitResult();

		break;

	//case MODE_RANKING://�����L���O���
	//	UninitRanking();
	//	break;

	case MODE_EDIT://�G�f�B�b�g���
		UninitEdit();
		break;
	}



	//�V������ʂ̏���������
	switch (mode)
	{
	case MODE_TITLE://�^�C�g�����
		InitTitle();
		break;

	//case MODE_TUTORIAL://�`���[�g���A�����
	//	InitTutorial();
	//	break;

	//case MODE_TUTORIAL2://�`���[�g���A�����2
	//	InitTutorial2();
	//	break;

	case MODE_GAME://�Q�[�����
		InitGame();
		break;

	case MODE_RESULT://���U���g���
		InitResult();

		break;

	//case MODE_RANKING://�����L���O���
	//	InitRanking();
	//	break;

	case MODE_EDIT://�G�f�B�b�g���
		InitEdit();
		break;
	}

	g_mode = mode;//���݂̉�ʂ�؂�ւ���

}
//=============================================
//�f�o�C�X�̎擾
//=============================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================================
//���[�h�̎擾
//=============================================
MODE GetMode(void)
{
	return g_mode;
}
//============================================================
// �E�B���h�E�t���X�N���[������
//============================================================
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;

}
void onWireFrame()
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void offWireFrame()
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}