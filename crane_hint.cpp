//---------------------------------------------------------
// ボールプール
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "crane_hint.h"
#include "crane_hint_bg.h"
#include "crane_score.h"
#include "password_game.h"

void InitCraneHint(void)
{
	InitCraneHintBG();
	InitCranePass();
	SetCranePass(GetAnum());
}
void UninitCraneHint(void)
{
	UninitCraneHintBG();
	UninitCranePass();
}
void UpdateCraneHint(void)
{
	UpdateCraneHintBG();
	UpdateCranePass();
}
void DrawCraneHint(void)
{
	DrawCraneHintBG();
	DrawCranePass();
}