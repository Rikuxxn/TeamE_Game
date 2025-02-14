//=========================================================
// 
// �~�j�}�b�v�\������[map.h]
// Author:TANEKAWA RIKU
// 
//=========================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

// �}�N����`
#define MINIMAP_LEFT (300.0f)
#define MINIMAP_RIGHT (940.0f)
#define MINIMAP_TOP (100.0f)
#define MINIMAP_UNDER (450.0f)

// �v���g�^�C�v�錾
void InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);
#endif