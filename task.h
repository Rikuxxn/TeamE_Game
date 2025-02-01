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
	"data\\TEXTURE\\mission1.png",			//1
	"data\\TEXTURE\\mission2.png",			//1
	"data\\TEXTURE\\mission3.png",			//1

};

// プロトタイプ宣言
void InitTask(void);
void UninitTask(void);
void UpdateTask(void);
void DrawTask(void);
void SetTask(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);


#endif