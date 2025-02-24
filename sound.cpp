//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "sound.h"
#include<x3daudio.h>
#include "enemy.h"
#include "player.h"

//*****************************************************************************
// サウンド情報の構造体定義
//*****************************************************************************
typedef struct
{	
	const char *pFilename;	// ファイル名
	int nCntLoop;			// ループカウント
} SOUNDINFO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
IXAudio2 *g_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// マスターボイス
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

// 3Dオーディオ用の変数
X3DAUDIO_HANDLE g_X3DInstance;       // X3DAudio インスタンス
X3DAUDIO_LISTENER g_Listener = {};   // リスナー（プレイヤーの位置）
X3DAUDIO_EMITTER g_Emitters[SOUND_LABEL_MAX] = {}; // 各サウンドの音源

// サウンドの情報
SOUNDINFO g_aSoundInfo[SOUND_LABEL_MAX] =
{

	{"data/BGM/gameBGM.wav", -1},		// ゲームBGM
	{"data/BGM/gameoverBGM.wav", -1},	// ゲームオーバーBGM
	{"data/BGM/titleBGM.wav", -1},		// タイトルBGM
	{"data/SE/insight.wav", 0},			// プレイヤーを発見
	{"data/SE/wandering.wav", 0},		// 敵の徘徊
	{"data/SE/footstep_1.wav", 0},		// 足音SE
	{"data/SE/footstep_2.wav", 0},		// 足音SE2
	{"data/SE/heart.wav", 0},			// 心音
	{"data/SE/heart_quick.wav", 0},		// 心音(速)
	{"data/SE/ballcatch.wav", 0},		// ボールを掴む
	{"data/SE/ballget.wav", 0},			// ボールを手に入れる
	{"data/SE/ballclear.wav", 0},		// ボールプールクリア
	{"data/SE/ClaneDown.wav", 0},		// クレーンを下げる
	{"data/SE/ClaneUP.wav", 0},			// クレーンを上げる
	{"data/SE/Claneget.wav", 0},		// 景品ゲット
	{"data/SE/stshot.wav", 0},			// シューティング射撃
	{"data/SE/sthit.wav", 0},			// ヒット音
	{"data/SE/stdead.wav", 0},			// 撃破音
	{"data/SE/stclear.wav", 0},			// シューティングクリア
	{"data/SE/Passpush.wav", 0},		// パスワード入力
	{"data/SE/Passwrong.wav", 0},		// パスワードが違う
	{"data/SE/Passcorrect.wav", 0},		// パスワードがあっている
	{"data/SE/fuseget.wav", 0},			// ヒューズをゲット
	{"data/SE/fuseset.wav", 0},			// ヒューズをセット
	{"data/SE/ikigire.wav", 0},			// 息切れ
	{"data/SE/opendoor.wav", 0},		// ドアが開く
	{"data/SE/enemychase.wav", 0},		// ピエロに追われている
	{"data/SE/Check.wav", 0},			// タスク完了
	{"data/SE/select.wav", 0},			// 選択
	{"data/SE/ok.wav", 0},				// 決定
	{"data/SE/gamestart.wav", 0},		// ゲームスタート
	{"data/SE/clear.wav", 0},			// ミニゲームクリア
	{"data/SE/footstep_1.wav", 0},		// 足音SE
	{"data/SE/footstep_2.wav", 0},		// 足音SE2

};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}
	
	// マスターボイスの生成
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if(g_pXAudio2 != NULL)
		{
			// XAudio2オブジェクトの開放
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// スピーカー設定を取得
	XAUDIO2_VOICE_DETAILS details;
	g_pMasteringVoice->GetVoiceDetails(&details);
	UINT32 numChannels = details.InputChannels; // スピーカーのチャンネル数を取得

	// X3DAudio の初期化
	X3DAudioInitialize(numChannels, X3DAUDIO_SPEED_OF_SOUND, g_X3DInstance);

	// リスナー（プレイヤーの初期位置）
	g_Listener.Position = { 0.0f, 0.0f, 0.0f };   // 中央
	g_Listener.OrientFront = { 0.0f, 0.0f, 1.0f }; // 前方向
	g_Listener.OrientTop = { 0.0f, 1.0f, 0.0f };   // 上方向
	g_Listener.Velocity = { 0.0f, 0.0f, 0.0f };

	// サウンドデータの初期化
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;


		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));


		// サウンドデータファイルの生成
		hFile = CreateFile(g_aSoundInfo[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// ソースボイスの生成
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = g_aSoundInfo[nCntSound].nCntLoop;

		// オーディオバッファの登録
		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// ファイルをクローズ
		CloseHandle(hFile);
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitSound(void)
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// ソースボイスの破棄
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// オーディオデータの開放
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// マスターボイスの破棄
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2 != NULL)
	{
		// XAudio2オブジェクトの開放
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COMライブラリの終了処理
	CoUninitialize();
}
//=============================================================================
// セグメント再生(再生中なら停止)
//=============================================================================
HRESULT PlaySound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = g_aSoundInfo[label].nCntLoop;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
// セグメント3D再生(再生中なら停止)
//=============================================================================
HRESULT PlaySound3D(SOUND_LABEL label)
{
	Enemy* pEnemy = GetEnemy();

	if (!g_apSourceVoice[label])
	{
		return E_FAIL;
	}

	// 敵の位置を取得して音源（エミッター）に設定
	g_Emitters[label].Position = { 0.0f, 0.0f, 0.0f };
	g_Emitters[label].Velocity = { 0.0f, 0.0f, 0.0f };
	g_Emitters[label].ChannelCount = 1;
	g_Emitters[label].CurveDistanceScaler = 100.0f;  // 適切な距離減衰を設定

	// 3Dオーディオ計算用のバッファ
	X3DAUDIO_DSP_SETTINGS dspSettings = {};
	FLOAT32 matrix[2];
	dspSettings.SrcChannelCount = 1;
	dspSettings.DstChannelCount = 2;
	dspSettings.pMatrixCoefficients = matrix;

	// 3D音響計算を実行
	X3DAudioCalculate(
		g_X3DInstance,
		&g_Listener,
		&g_Emitters[label],
		X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_DOPPLER,
		&dspSettings
	);

	// パンニング値をクリップ
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

	// 計算結果を適用
	g_apSourceVoice[label]->SetOutputMatrix(NULL, 1, 2, matrix);

	// バッファ設定
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer = {};
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = 0;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{
		return S_OK; // すでに鳴っているなら何もしない
	}

	// オーディオバッファの登録
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
// 音源の位置更新
//=============================================================================
void UpdateSoundPosition(SOUND_LABEL label)
{
	Enemy* pEnemy = GetEnemy();

	if (label < 0 || label >= SOUND_LABEL_MAX)
	{
		return;
	}

	// 敵の現在位置を適用
	g_Emitters[label].Position = { pEnemy->pos.x, pEnemy->pos.y, pEnemy->pos.z };

	// 3Dオーディオ計算
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

	// パンニング値をクリップ
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

	// 音のパンニングを更新
	g_apSourceVoice[label]->SetOutputMatrix(NULL, 1, 2, matrix);
}
//=============================================================================
// リスナー(プレイヤー)の位置更新
//=============================================================================
void UpdateListenerPosition(float x, float y, float z)
{
	// リスナー(プレイヤー)の位置
	g_Listener.Position = { x, y, z };
}
//=============================================================================
// セグメント停止(ラベル指定)
//=============================================================================
void StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}
//=============================================================================
// セグメント停止(全て)
//=============================================================================
void StopSound(void)
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}
//=============================================================================
// チャンクのチェック
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
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
// チャンクデータの読み込み
//=============================================================================
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}
