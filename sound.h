//=============================================================================
//
// サウンド処理 [sound.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_GAMEBGM = 0,	// ゲームBGM
	SOUND_LABEL_GAMEOVERBGM,	// ゲームオーバーBGM
	SOUND_LABEL_TITLEBGM,		// タイトルBGM
	SOUND_LABEL_INSIGHT,		// プレイヤーを発見
	SOUND_LABEL_ENEMYWANDERING,	// 敵が徘徊しているときの音
	SOUND_LABEL_ENEMYATTACK,	// 敵の攻撃
	SOUND_LABEL_ENEMYCAUGHT,	// 敵に捕まった
	SOUND_LABEL_ENEMYSTEP1,		// 敵の足音SE
	SOUND_LABEL_ENEMYSTEP2,		// 敵の足音SE2
	SOUND_LABEL_PLAYERSTEP1,	// 足音SE
	SOUND_LABEL_PLAYERSTEP2,	// 足音SE2
	SOUND_LABEL_HEART,			// 心音
	SOUND_LABEL_HEARTQUICK,		// 心音(速)
	SOUND_LABEL_BALLTUTO,		// ボールプールのチュートリアル説明
	SOUND_LABEL_BALLFADE,		// ボールプールのフェード
	SOUND_LABEL_BALLCATCH,		// ボールを掴む
	SOUND_LABEL_BALLGET,		// ボールを手に入れる
	SOUND_LABEL_BALLCLEAR,		// ボールプールクリア
	SOUND_LABEL_CRANEMOVE,		// クレーンの移動
	SOUND_LABEL_CRANEDOWN,		// クレーンを下げる
	SOUND_LABEL_CRANEUP,		// クレーンを上げる
	SOUND_LABEL_CRANEGET,		// 景品ゲット
	SOUND_LABEL_DROPHINT,		// ヒントが落ちた
	SOUND_LABEL_HINTWATCH,		// ヒントの確認
	SOUND_LABEL_STSHOT,			// シューティング射撃
	SOUND_LABEL_STHIT,			// ヒット音
	SOUND_LABEL_STDEAD,			// 撃破音
	SOUND_LABEL_STCLEAR,		// シューティングクリア
	SOUND_LABEL_PASSPUSH,		// パスワード入力
	SOUND_LABEL_PASSWRONG,		// パスワードが違う
	SOUND_LABEL_PASSCORRECT,	// パスワードがあっている
	SOUND_LABEL_FUSEGET,		// ヒューズをゲット
	SOUND_LABEL_FUSESET,		// ヒューズをセット
	SOUND_LABEL_EMPTYBREATH,	// 息切れ
	SOUND_LABEL_OPENDOOR,		// ドアが開く
	SOUND_LABEL_TASKOK,			// タスク完了
	SOUND_LABEL_MENUOPEN,		// メニューオープン
	SOUND_LABEL_SELECT,			// 選択
	SOUND_LABEL_OK,				// 決定
	SOUND_LABEL_RANK,			// リザルトのランク表示
	SOUND_LABEL_GAMESTART,		// ゲームスタート
	SOUND_LABEL_MINICLEAR,		// ミニゲームクリア

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
HRESULT PlaySound3D(SOUND_LABEL label);
void UpdateSoundPosition(SOUND_LABEL label, float x, float y, float z);
void CalculateCustomPanning(SOUND_LABEL label, FLOAT32* matrix);
void UpdateListener(float x, float y, float z);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif