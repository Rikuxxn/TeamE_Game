//---------------------------------------------------------
// �{�[���v�[��
// Author:Yoshida Atsushi
//---------------------------------------------------------
#include "ball_hint.h"
#include "ball_hint_bg.h"
#include "ball_score.h"
#include "password_game.h"

// ����������
void InitBallHint(void)
{
	InitBallHintBG();
	InitBallPass();
	SetBallPass(GetAnum3());
}
// �I������
void UninitBallHint(void)
{
	UninitBallHintBG();
	UninitBallPass();
}
// �X�V����
void UpdateBallHint(void)
{
	UpdateBallHintBG();
	UpdateBallPass();
}
// �`�揈��
void DrawBallHint(void)
{
	DrawBallHintBG();
	DrawBallPass();
}