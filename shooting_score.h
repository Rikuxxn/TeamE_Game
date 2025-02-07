//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _SHOOTINGSCORE_H_
#define _SHOOTINGSCORE_H_

#include "main.h"

//マクロ
#define MAX_NUM_SCORE (4)
#define PASSPOSX (560.0f)
#define PASSPOSY (260.0f)

//パスワードの構造体
typedef struct
{
	bool buse;
	int nCountSTPassCounter;
}STPass;

//プロト
void InitSTPass(void);				//パスワードの初期化
void UninitSTPass(void);				//終了
void UpdateSTPass(void);				//更新
void DrawSTPass(void);				//描画
void SetSTPass(int nSTAPass);		//設置
int STPassCounter(int nSTPass);	//カウンター

#endif // !_SCORE_H_
