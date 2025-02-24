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

	{"data/BGM/gameBGM.wav", -1},		// �Q�[��BGM
	{"data/BGM/gameoverBGM.wav", -1},	// �Q�[���I�[�o�[BGM
	{"data/BGM/titleBGM.wav", -1},		// �^�C�g��BGM
	{"data/SE/insight.wav", 0},			// �v���C���[�𔭌�
	{"data/SE/wandering.wav", 0},		// �G�̜p�j
	{"data/SE/footstep_1.wav", 0},		// ����SE
	{"data/SE/footstep_2.wav", 0},		// ����SE2
	{"data/SE/heart.wav", 0},			// �S��
	{"data/SE/heart_quick.wav", 0},		// �S��(��)
	{"data/SE/ballcatch.wav", 0},		// �{�[����͂�
	{"data/SE/ballget.wav", 0},			// �{�[������ɓ����
	{"data/SE/ballclear.wav", 0},		// �{�[���v�[���N���A
	{"data/SE/ClaneDown.wav", 0},		// �N���[����������
	{"data/SE/ClaneUP.wav", 0},			// �N���[�����グ��
	{"data/SE/Claneget.wav", 0},		// �i�i�Q�b�g
	{"data/SE/stshot.wav", 0},			// �V���[�e�B���O�ˌ�
	{"data/SE/sthit.wav", 0},			// �q�b�g��
	{"data/SE/stdead.wav", 0},			// ���j��
	{"data/SE/stclear.wav", 0},			// �V���[�e�B���O�N���A
	{"data/SE/Passpush.wav", 0},		// �p�X���[�h����
	{"data/SE/Passwrong.wav", 0},		// �p�X���[�h���Ⴄ
	{"data/SE/Passcorrect.wav", 0},		// �p�X���[�h�������Ă���
	{"data/SE/fuseget.wav", 0},			// �q���[�Y���Q�b�g
	{"data/SE/fuseset.wav", 0},			// �q���[�Y���Z�b�g
	{"data/SE/ikigire.wav", 0},			// ���؂�
	{"data/SE/opendoor.wav", 0},		// �h�A���J��
	{"data/SE/enemychase.wav", 0},		// �s�G���ɒǂ��Ă���
	{"data/SE/Check.wav", 0},			// �^�X�N����
	{"data/SE/select.wav", 0},			// �I��
	{"data/SE/ok.wav", 0},				// ����
	{"data/SE/gamestart.wav", 0},		// �Q�[���X�^�[�g
	{"data/SE/clear.wav", 0},			// �~�j�Q�[���N���A
	{"data/SE/footstep_1.wav", 0},		// ����SE
	{"data/SE/footstep_2.wav", 0},		// ����SE2

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
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
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
	UINT32 numChannels = details.InputChannels; // �X�s�[�J�[�̃`�����l�������擾

	// X3DAudio �̏�����
	X3DAudioInitialize(numChannels, X3DAUDIO_SPEED_OF_SOUND, g_X3DInstance);

	// ���X�i�[�i�v���C���[�̏����ʒu�j
	g_Listener.Position = { 0.0f, 0.0f, 0.0f };   // ����
	g_Listener.OrientFront = { 0.0f, 0.0f, 1.0f }; // �O����
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
	g_Emitters[label].Position = { 0.0f, 0.0f, 0.0f };
	g_Emitters[label].Velocity = { 0.0f, 0.0f, 0.0f };
	g_Emitters[label].ChannelCount = 1;
	g_Emitters[label].CurveDistanceScaler = 100.0f;  // �K�؂ȋ���������ݒ�

	// 3D�I�[�f�B�I�v�Z�p�̃o�b�t�@
	X3DAUDIO_DSP_SETTINGS dspSettings = {};
	FLOAT32 matrix[2];
	dspSettings.SrcChannelCount = 1;
	dspSettings.DstChannelCount = 2;
	dspSettings.pMatrixCoefficients = matrix;

	// 3D�����v�Z�����s
	X3DAudioCalculate(
		g_X3DInstance,
		&g_Listener,
		&g_Emitters[label],
		X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_DOPPLER,
		&dspSettings
	);

	// �p���j���O�l���N���b�v
	for (int i = 0; i < 2; i++)
	{
		if (matrix[i] > 1.0f)
		{
			matrix[i] = 1.0f;
		}
		if (matrix[i] < 0.5f)
		{
			matrix[i] = 0.5f;
		}
	}

	// �v�Z���ʂ�K�p
	g_apSourceVoice[label]->SetOutputMatrix(NULL, 1, 2, matrix);

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
	{
		return S_OK; // ���łɖ��Ă���Ȃ牽�����Ȃ�
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
// �����̈ʒu�X�V
//=============================================================================
void UpdateSoundPosition(SOUND_LABEL label)
{
	Enemy* pEnemy = GetEnemy();

	if (label < 0 || label >= SOUND_LABEL_MAX)
	{
		return;
	}

	// �G�̌��݈ʒu��K�p
	g_Emitters[label].Position = { pEnemy->pos.x, pEnemy->pos.y, pEnemy->pos.z };

	// 3D�I�[�f�B�I�v�Z
	X3DAUDIO_DSP_SETTINGS dspSettings = {};
	FLOAT32 matrix[2];
	dspSettings.SrcChannelCount = 1;
	dspSettings.DstChannelCount = 2;
	dspSettings.pMatrixCoefficients = matrix;

	X3DAudioCalculate(
		g_X3DInstance,
		&g_Listener,
		&g_Emitters[label],
		X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_LPF_DIRECT,
		&dspSettings
	);

	// �p���j���O�l���N���b�v
	for (int i = 0; i < 2; i++)
	{
		if (matrix[i] > 1.0f)
		{
			matrix[i] = 1.0f;
		}
		if (matrix[i] < 0.1f)
		{
			matrix[i] = 0.1f;
		}
	}

	// ���̃p���j���O���X�V
	g_apSourceVoice[label]->SetOutputMatrix(NULL, 1, 2, matrix);
}
//=============================================================================
// ���X�i�[(�v���C���[)�̈ʒu�X�V
//=============================================================================
void UpdateListenerPosition(float x, float y, float z)
{
	// ���X�i�[(�v���C���[)�̈ʒu
	g_Listener.Position = { x, y, z };
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
