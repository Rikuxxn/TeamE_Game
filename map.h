#ifndef _MAP_H_
#define _MAP_H_


#include "main.h"

// マクロ定義
#define MINIMAP_LEFT (280.0f)//幅720.0f
#define MINIMAP_RIGHT (1000.0f)
#define MINIMAP_TOP (50.0f)//高さ400.0f
#define MINIMAP_UNDER (450.0f)

//プロト
void InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);
#endif