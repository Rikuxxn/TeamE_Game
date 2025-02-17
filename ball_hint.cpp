//---------------------------------------------------------
// ボールプール
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "ball_hint.h"
#include "ball_hint_bg.h"
#include "ball_score.h"
#include "password_game.h"

// 初期化処理
void InitBallHint(void)
{
	InitBallHintBG();
	InitBallPass();
	SetBallPass(GetAnum3());
}
// 終了処理
void UninitBallHint(void)
{
	UninitBallHintBG();
	UninitBallPass();
}
// 更新処理
void UpdateBallHint(void)
{
	UpdateBallHintBG();
	UpdateBallPass();
}
// 描画処理
void DrawBallHint(void)
{
	DrawBallHintBG();
	DrawBallPass();
}