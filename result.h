//=============================================================================
//
// リザルト処理 [result.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _RESULT_H_//このマクロ定義がされていなかったら
#define _RESULT_H_//2重インクルード防止のマクロ定義

//マクロ定義
#define MAX_RESULT_TIMEDIGIT (2)	//桁の最大数

//マクロ定義
#define MAX_CLEAR (1)			// clear選択項目数
#define MAX_GAMEOVER (2)		// gameover選択項目数

#define CLEAR_MIN_SCALE (1.0f)
#define CLEAR_MAX_SCALE (1.2f)
#define CLEAR_SCALE_SPEED (0.02f)
#define CLEAR_ALPHA_SPEED (0.05f)

#define GAMEOVER_MIN_SCALE (1.0f)
#define GAMEOVER_MAX_SCALE (1.2f)
#define GAMEOVER_SCALE_SPEED (0.02f)
#define GAMEOVER_ALPHA_SPEED (0.05f)

// clearの選択項目の種類
typedef enum
{
	CLEAR_MENU_TITLE = 0,        // タイトルに戻る
	CLEAR_MENU_MAX
}CLEAR_MENU;

// gameoverの選択項目の種類
typedef enum
{
	GAMEOVER_MENU_RETRY = 0,        //リトライ
	GAMEOVER_MENU_TITLE,			//タイトルに戻る
	GAMEOVER_MENU_MAX
}GAMEOVER_MENU;

static const char* CLEAR_TEXTURE[MAX_CLEAR] =
{
	"data\\TEXTURE\\titleback.png",
};

static const char* GAMEOVER_TEXTURE[MAX_GAMEOVER] =
{
	"data\\TEXTURE\\retry1.png",
	"data\\TEXTURE\\titleback.png",
};


//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

void InitResultTime(void);
void UninitResultTime(void);
void UpdateResultTime(void);
void DrawResultTime(void);

#endif

