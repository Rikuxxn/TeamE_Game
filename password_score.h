//========================
//|パスワード			 |
//|Author:Yoshida Atsushi|
//========================
#ifndef _PASSWORDSCORE_H_
#define _PASSWORDSCORE_H_

#include "main.h"

//マクロ
#define MAX_NUM_SCORE (4)
#define PASSWORDPOS (500.0f)

//パスワードの構造体
typedef struct
{
	bool buse;
	int nCountPasswordCounter;
}Password;

//プロト
void InitPassword(void);		// パスワードの初期化
void UninitPassword(void);		// 終了
void UpdatePassword(void);		// 更新
void DrawPassword(void);		// 描画

void SetPassword(int nPass,int nA, bool bAnswer);	// 設置
void AddPassword(int nValue);	// 追加

int PasswordCounter(int nPass);	// カウンター
int GetPassword(void);			// 取得
int GetPassword2(void);
int GetPassword3(void);
int GetPassword4(void);
bool GetPush1(void);
bool GetPush2(void);
bool GetPush3(void);
bool GetPush4(void);
int GetCntCounter(void);
bool GetJudge(void);			// 判定

#endif // !_SCORE_H_
