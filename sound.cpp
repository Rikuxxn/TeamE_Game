//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "sound.h"
#include<x3daudio.h>
#include "enemy.h"
#include "player.h"
#include "camera.h"
#include <stdio.h>

//*****************************************************************************
// �T�E���h���̍\���̒�`
//*****************************************************************************
typedef struct
{	
	const char *pFilename;	// �t�@�C����
	int nCntLoop;			// ���[�v�J�E���g
} SOUNDINFO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
IXAudio2 *g_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

// 3D�I�[�f�B�I�p�̕ϐ�
X3DAUDIO_HANDLE g_X3DInstance;       // X3DAudio �C���X�^���X
X3DAUDIO_LISTENER g_Listener = {};   // ���X�i�[�i�v���C���[�̈ʒu�j
X3DAUDIO_EMITTER g_Emitters[SOUND_LABEL_MAX] = {}; // �e�T�E���h�̉���

// �T�E���h�̏��
SOUNDINFO g_aSoundInfo[SOUND_LABEL_MAX] =
{

	{"data/BGM/gameBGM.wav", -1},			// �Q�[��BGM
	{"data/BGM/gameoverBGM.wav", -1},		// �Q�[���I�[�o�[BGM
	{"data/BGM/titleBGM.wav", -1},			// �^�C�g��BGM
	{"data/SE/insight.wav", 0},				// �v���C���[�𔭌�
	{"data/SE/wandering.wav", 0},			// �G�̜p�j
	{"data/SE/footstep_1.wav", 0},			// ����SE
	{"data/SE/footstep_2.wav", 0},			// ����SE2
	{"data/SE/heart.wav", 0},				// �S��
	{"data/SE/heart_quick.wav", 0},			// �S��(��)
	{"data/SE/balltutorial.wav", 0},		// �{�[���v�[���̃`���[�g���A������
	{"data/SE/balltutorial_fade.wav", 0},	// �{�[���v�[���̃t�F�[�h
	{"data/SE/ballcatch.wav", 0},			// �{�[����͂�
	{"data/SE/ballget.wav", 0},				// �{�[������ɓ����
	{"data/SE/ballclear.wav", 0},			// �{�[���v�[���N���A
	{"data/SE/Crane_move.wav", -1},			// �N���[���̈ړ�
	{"data/SE/Crane_Down.wav", 0},			// �N���[����������
	{"data/SE/Crane_UP.wav", 0},			// �N���[�����グ��
	{"data/SE/Crane_get.wav", 0},			// �i�i�Q�b�g
	{"data/SE/stshot.wav", 0},				// �V���[�e�B���O�ˌ�
	{"data/SE/sthit.wav", 0},				// �q�b�g��
	{"data/SE/stdead.wav", 0},				// ���j��
	{"data/SE/stclear.wav", 0},				// �V���[�e�B���O�N���A
	{"data/SE/Passpush.wav", 0},			// �p�X���[�h����
	{"data/SE/Passwrong.wav", 0},			// �p�X���[�h���Ⴄ
	{"data/SE/Passcorrect.wav", 0},			// �p�X���[�h�������Ă���
	{"data/SE/fuseget.wav", 0},				// �q���[�Y���Q�b�g
	{"data/SE/fuseset.wav", 0},				// �q���[�Y���Z�b�g
	{"data/SE/ikigire.wav", 0},				// ���؂�
	{"data/SE/opendoor.wav", 0},			// �h�A���J��
	{"data/SE/enemychase.wav", 0},			// �s�G���ɒǂ��Ă���
	{"data/SE/Check.wav", 0},				// �^�X�N����
	{"data/SE/menu.wav", 0},				// ���j���[�I�[�v��
	{"data/SE/select.wav", 0},				// �I��
	{"data/SE/ok.wav", 0},					// ����
	{"data/SE/resultrank6.wav", 0},			// ���U���g�̃����N�\��
	{"data/SE/gamestart.wav", 0},			// �Q�[���X�^�[�g
	{"data/SE/clear.wav", 0},				// �~�j�Q�[���N���A
	{"data/SE/footstep_enemy.wav", 0},		// �G�̑���SE
	{"data/SE/footstep_enemy2.wav", 0},		// �G�̑���SE2

};
//=============================================================================
// ����������
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice, 4, 48000, 0, NULL, NULL);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if(g_pXAudio2 != NULL)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �X�s�[�J�[�ݒ���擾
	XAUDIO2_VOICE_DETAILS details;
	g_pMasteringVoice->GetVoiceDetails(&details);

	UINT32 speakerConfig = details.InputChannels; // ���݂̃X�s�[�J�[�ݒ�
	X3DAudioInitialize(speakerConfig, X3DAUDIO_SPEED_OF_SOUND, g_X3DInstance);

	// ���X�i�[�i�v���C���[�̏����ʒu�j
	g_Listener.Position = { 0.0f, 0.0f, 0.0f };   // ����
	g_Listener.OrientFront = { 0.0f, 0.0f, 0.0f }; // �O����
	g_Listener.OrientTop = { 0.0f, 1.0f, 0.0f };   // �����
	g_Listener.Velocity = { 0.0f, 0.0f, 0.0f };

	// �T�E���h�f�[�^�̏�����
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;


		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));


		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(g_aSoundInfo[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �\�[�X�{�C�X�̐���
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = g_aSoundInfo[nCntSound].nCntLoop;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitSound(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2 != NULL)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}
//=============================================================================
// �Z�O�����g�Đ�(�Đ����Ȃ��~)
//=============================================================================
HRESULT PlaySound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = g_aSoundInfo[label].nCntLoop;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
// �Z�O�����g3D�Đ�(�Đ����Ȃ��~)
//=============================================================================
HRESULT PlaySound3D(SOUND_LABEL label)
{
	Enemy* pEnemy = GetEnemy();

	if (!g_apSourceVoice[label])
	{
		return E_FAIL;
	}

	// �G�̈ʒu���擾���ĉ����i�G�~�b�^�[�j�ɐݒ�
	UpdateSoundPosition(SOUND_LABEL_ENEMYSTEP1, pEnemy->pos.x, pEnemy->pos.y, pEnemy->pos.z);
	UpdateSoundPosition(SOUND_LABEL_ENEMYSTEP2, pEnemy->pos.x, pEnemy->pos.y, pEnemy->pos.z);

	g_Emitters[label].Velocity = { 0.0f, 0.0f, 0.0f };
	g_Emitters[label].ChannelCount = 1;
	g_Emitters[label].CurveDistanceScaler = 80.0f;  // ����������ݒ�

	// 3D�I�[�f�B�I�v�Z�p�̃o�b�t�@
	X3DAUDIO_DSP_SETTINGS dspSettings = {};
	FLOAT32 matrix[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	dspSettings.SrcChannelCount = 1;
	dspSettings.DstChannelCount = 4;
	dspSettings.pMatrixCoefficients = matrix;

	// �J�X�^���p���j���O�v�Z
	CalculateCustomPanning(label, matrix);

	// �p���j���O�l���N���b�v�i0.0 �` 0.5 �͈̔͂Ɏ��߂�j
	matrix[0] = max(0.0f, min(0.5f, matrix[0]));
	matrix[1] = max(0.0f, min(0.5f, matrix[1]));

	// �p���j���O�l���N���b�v
	for (int i = 0; i < 2; i++)
	{
		if (matrix[i] > 1.0f)
		{
			matrix[i] = 1.0f;
		}
		if (matrix[i] < 0.0f)
		{
			matrix[i] = 0.0f;
		}
	}

	// �v�Z���ʂ�K�p
	g_apSourceVoice[label]->SetOutputMatrix(NULL, 1, 4, matrix);

	// �o�b�t�@�ݒ�
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer = {};
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = 0;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
// �J�X�^���p���j���O
//=============================================================================
void CalculateCustomPanning(SOUND_LABEL label, FLOAT32* matrix)
{
	// �v���C���[�̌����i�O�����x�N�g���j
	D3DXVECTOR3 front = g_Listener.OrientFront;
	D3DXVec3Normalize(&front, &front);

	// ������x�N�g���i�ʏ�� (0, 1, 0)�j
	D3DXVECTOR3 up = g_Listener.OrientTop;
	D3DXVec3Normalize(&up, &up);

	// �E�����x�N�g�� = front �~ up�i�O�ςŋ��߂�j
	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &up, &front);
	D3DXVec3Normalize(&right, &right);

	// �v���C���[ �� �����̃x�N�g��
	D3DXVECTOR3 toEmitter =
	{
		g_Emitters[label].Position.x - g_Listener.Position.x,
		g_Emitters[label].Position.y - g_Listener.Position.y,
		g_Emitters[label].Position.z - g_Listener.Position.z
	};

	// �������v�Z
	float distance = D3DXVec3Length(&toEmitter);

	// �ŏ������ƍő勗���i���������͈̔́j
	float minDistance = 450.0f;
	float maxDistance = 1050.0f;

	// ���������v�Z
	float volumeScale = 1.0f - ((distance - minDistance) / (maxDistance - minDistance));
	volumeScale = max(0.0f, min(1.0f, volumeScale));

	// �����x�N�g���𐳋K��
	D3DXVec3Normalize(&toEmitter, &toEmitter);

	// ���E�p���j���O
	FLOAT32 panFactorLR = D3DXVec3Dot(&right, &toEmitter);
	FLOAT32 panCurveLR = sinf(panFactorLR * D3DX_PI * 0.5f); // -1.0 �` 1.0 �͈̔�

	// �O��p���j���O
	FLOAT32 panFactorFB = D3DXVec3Dot(&front, &toEmitter);
	FLOAT32 panCurveFB = sinf(panFactorFB * D3DX_PI * 0.5f); // -1.0 �` 1.0 �͈̔�

	// �`�����l�����Ƃ̉��ʌv�Z
	FLOAT32 frontLeft = (0.8f - max(0.0f, panCurveLR)) * (1.0f + panCurveFB) * 0.5f * volumeScale;
	FLOAT32 frontRight = (0.8f - max(0.0f, -panCurveLR)) * (1.0f + panCurveFB) * 0.5f * volumeScale;
	FLOAT32 rearLeft = (0.8f - max(0.0f, panCurveLR)) * (1.0f - panCurveFB) * 0.5f * volumeScale;
	FLOAT32 rearRight = (0.8f - max(0.0f, -panCurveLR)) * (1.0f - panCurveFB) * 0.5f * volumeScale;

	// ���ʃ}�g���b�N�X�ɃZ�b�g�i4ch: FL, FR, RL, RR�j
	matrix[0] = frontLeft;
	matrix[1] = frontRight;
	matrix[2] = rearLeft;
	matrix[3] = rearRight;
}
//=============================================================================
// �����̈ʒu�X�V
//=============================================================================
void UpdateSoundPosition(SOUND_LABEL label,float x, float y, float z)
{
	Enemy* pEnemy = GetEnemy();

	if (label < 0 || label >= SOUND_LABEL_MAX)
	{
		return;
	}

	// �G�̌��݈ʒu��K�p
	g_Emitters[label].Position = { x, y, z };

	// 3D�I�[�f�B�I�v�Z
	X3DAUDIO_DSP_SETTINGS dspSettings = {};
	FLOAT32 matrix[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	dspSettings.SrcChannelCount = 1;
	dspSettings.DstChannelCount = 4;
	dspSettings.pMatrixCoefficients = matrix;

	X3DAudioCalculate(
		g_X3DInstance,
		&g_Listener,
		&g_Emitters[label],
		X3DAUDIO_CALCULATE_MATRIX,
		&dspSettings
	);

	// �p���j���O�l���N���b�v
	for (int i = 0; i < 2; i++)
	{
		if (matrix[i] > 1.0f)
		{
			matrix[i] = 1.0f;
		}
		if (matrix[i] < 0.0f)
		{
			matrix[i] = 0.0f;
		}
	}

	// ���̃p���j���O���X�V
	g_apSourceVoice[label]->SetOutputMatrix(NULL, 1, 4, matrix);

}
//=============================================================================
// ���X�i�[(�v���C���[)�̍X�V
//=============================================================================
void UpdateListener(float x, float y, float z)
{
	Camera* pCamera = GetCamera();

	// �J�����̌����x�N�g�����v�Z
	D3DXVECTOR3 forward;
	forward.x = -sinf(pCamera->rot.y) * cosf(pCamera->rot.x);
	forward.y = -sinf(pCamera->rot.x);
	forward.z = -cosf(pCamera->rot.y) * cosf(pCamera->rot.x);

	// ���K������ g_Listener.OrientFront �ɑ��
	D3DXVec3Normalize(&forward, &forward);

	g_Listener.OrientFront = forward;

	D3DXVECTOR3 orienttop;
	orienttop.x = 0.0f;
	orienttop.y = 1.0f;
	orienttop.z = 0.0f;

	D3DXVec3Normalize(&orienttop, &orienttop);

	g_Listener.OrientTop = orienttop;

	g_Listener.Position = { x, y, z };				// ���X�i�[(�v���C���[)�̈ʒu
}
//=============================================================================
// �Z�O�����g��~(���x���w��)
//=============================================================================
void StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}
//=============================================================================
// �Z�O�����g��~(�S��)
//=============================================================================
void StopSound(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}
//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}