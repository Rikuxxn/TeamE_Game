#ifndef _BALLGAME_H_
#define _BALLGAME_H_

#include "main.h"

// �}�N��
#define BALLPOS (530.0f)// ��820.0f

typedef enum
{
	BALLGAMESTATE_NONE = 0,	// �������Ă��Ȃ����
	BALLGAMESTATE_NORMAL,	// �ʏ��ԁi�Q�[���i�s���j
	BALLGAMESTATE_END,		// �I����ԁi�G�S�ŁA�v���C���[���A�^�C���I�[�o�[�Ȃǁj
	BALLGAMESTATE_MAX
}BALLGAMESTATE;

// �}�N��
void InitBallGame(void);
void UninitBallGame(void);
void UpdateBallGame(void);
void DrawBallGame(void);
void SetBallGameState(BALLGAMESTATE state);
BALLGAMESTATE GetBallGameState(void);

#endif // !1