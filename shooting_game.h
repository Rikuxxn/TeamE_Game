#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

typedef enum
{
	GAMESTATE_NONE = 0,//�������Ă��Ȃ����
	GAMESTATE_NORMAL,//�ʏ��ԁi�Q�[���i�s���j
	GAMESTATE_END,//�I����ԁi�G�S�ŁA�v���C���[���A�^�C���I�[�o�[�Ȃǁj
	GAMESTATE_MAX
}SHOOTINGGAMESTATE;

//�}�N��
void InitShootingGame(void);
void UninitShootingGame(void);
void UpdateShootingGame(void);
void DrawShootingGame(void);
void SetShootingGameState(SHOOTINGGAMESTATE state);
SHOOTINGGAMESTATE GetGameState(void);


#endif // !1