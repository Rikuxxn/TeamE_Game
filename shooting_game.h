#ifndef _SHHOTINGGAME_H_
#define _SHHOTINGGAME_H_

#include "main.h"

typedef enum
{
	STGSTATE_NONE = 0,//�������Ă��Ȃ����
	STGSTATE_NORMAL,//�ʏ��ԁi�Q�[���i�s���j
	STGSTATE_END,//�I����ԁi�G�S�ŁA�v���C���[���A�^�C���I�[�o�[�Ȃǁj
	STGSTATE_MAX
}STGSTATE;

//�}�N��
void InitShootingGame(void);
void UninitShootingGame(void);
void UpdateShootingGame(void);
void DrawShootingGame(void);
void SetShootingGameState(STGSTATE state);
STGSTATE GetShootingGameState(void);


#endif // !1