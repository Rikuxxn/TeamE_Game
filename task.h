//=============================================================================
//
// タスク処理 [task.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _TASK_H_
#define _TASK_H_

#include "main.h"

// マクロ定義
#define MAX_TASK (256)      //タスクUIの最大数

//タスクUIの種類
typedef enum
{
	TASKTYPE_ONE = 0,
	TASKTYPE_TWO,
	TASKTYPE_THREE,
	
	TASKTYPE_SUB1,
	TASKTYPE_SUB2,
	TASKTYPE_SUB1_CMP,
	TASKTYPE_SUB2_CMP,

	TASKTYPE_SUB3,
	TASKTYPE_SUB4,
	TASKTYPE_SUB5,
	TASKTYPE_SUB3_CMP,
	TASKTYPE_SUB4_CMP,
	TASKTYPE_SUB5_CMP,

	TASKTYPE_SUB6,
	TASKTYPE_SUB6_CMP,

	TASKTYPE_MAX
}TASKTYPE;


//タスク構造体
typedef struct
{
	D3DXVECTOR3 pos;	//タスクの位置
	D3DXVECTOR3 move;	//タスクの移動量
	float fWidth;		//タスクの幅
	float fHeight;		//タスクの高さ
	int nType;			//タスクの種類
	bool bUse;
}TASK;


static const char* TASK_TEXTURE[TASKTYPE_MAX] =		// タスクのテクスチャの設定
{
	"data\\TEXTURE\\mission1.png",			// メインミッション1
	"data\\TEXTURE\\mission2.png",			// メインミッション2
	"data\\TEXTURE\\mission3.png",			// メインミッション3

	"data\\TEXTURE\\Task1.png",				// サブミッション1 (ヒューズを見つける)
	"data\\TEXTURE\\Task2.png",				// サブミッション2 (ヒューズを配電盤に付ける)
	"data\\TEXTURE\\TaskC1.png",			// サブミッション1 完了 (ヒューズを見つける)
	"data\\TEXTURE\\TaskC2.png",			// サブミッション2 完了 (ヒューズを配電盤に付ける)

	"data\\TEXTURE\\Task3.png",				// サブミッション3 (クレーンゲームを調べる)
	"data\\TEXTURE\\Task4.png",				// サブミッション4 (アーケードゲームを調べる)
	"data\\TEXTURE\\Task5.png",				// サブミッション5 (ボールプールを調べる)
	"data\\TEXTURE\\TaskC3.png",			// サブミッション3 完了 (クレーンゲームを調べる)
	"data\\TEXTURE\\TaskC4.png",			// サブミッション4 完了 (アーケードゲームを調べる)
	"data\\TEXTURE\\TaskC5.png",			// サブミッション5 完了 (ボールプールを調べる)

	"data\\TEXTURE\\Task6.png",				// サブミッション6 (暗証番号を入力する)
	"data\\TEXTURE\\TaskC6.png",			// サブミッション6 完了 (暗証番号を入力する)

};

// プロトタイプ宣言
void InitTask(void);
void UninitTask(void);
void UpdateTask(void);
void DrawTask(void);
void SetTask(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);

#endif