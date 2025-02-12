//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _BALLSCORE_H_
#define _BALLSCORE_H_

#include "main.h"

//マクロ
#define MAX_NUM_SCORE (4)
#define PASSPOSX (530.0f)
#define PASSPOSY (260.0f)

//パスワードの構造体
typedef struct
{
	bool buse;
	int nCountBallPassCounter;
}BallPass;

//プロト
void InitBallPass(void);				//パスワードの初期化
void UninitBallPass(void);				//終了
void UpdateBallPass(void);				//更新
void DrawBallPass(void);				//描画
void SetBallPass(int nBallAPass);		//設置
int BallPassCounter(int nBallPass);	//カウンター

#endif // !_SCORE_H_
