//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _CRANESCORE_H_
#define _CRANESCORE_H_

#include "main.h"

//マクロ
#define MAX_NUM_SCORE (4)
#define PASSPOSX (560.0f)
#define PASSPOSY (260.0f)

//パスワードの構造体
typedef struct
{
	bool buse;
	int nCountCranePassCounter;
}CranePass;

//プロト
void InitCranePass(void);				//　パスワードの初期化
void UninitCranePass(void);				//　終了
void UpdateCranePass(void);				//　更新
void DrawCranePass(void);				//　描画
void SetCranePass(int nCraneAPass);		//　設置
int CranePassCounter(int nCranePass);	//　カウンター

#endif // !_SCORE_H_
