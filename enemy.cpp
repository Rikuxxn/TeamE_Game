//=======================================
//
// 敵の処理 [enemy.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "fade.h"
#include "block.h"
#include "sound.h"
#include "shadow.h"
#include "light.h"
#include <stdio.h>

// 巡回ポイント配列
D3DXVECTOR3 patrolPoints[] =
{
	D3DXVECTOR3(-1050.0f, 0.0f, -800.0f),	// 0
	D3DXVECTOR3(-1070.0f, 0.0f, -610.0f),	// 1
	D3DXVECTOR3(-1040.0f, 0.0f, -420.0f),	// 2
	D3DXVECTOR3(-1030.0f, 0.0f, -200.0f),	// 3
	D3DXVECTOR3(-1035.0f, 0.0f, -40.0f),	// 4
	D3DXVECTOR3(-1025.0f, 0.0f, 255.0f),	// 5
	D3DXVECTOR3(-1015.0f, 0.0f, 515.0f),	// 6
	D3DXVECTOR3(-975.0f, 0.0f, 805.0f),		// 7
	D3DXVECTOR3(-750.0f, 0.0f, 855.0f),		// 8
	D3DXVECTOR3(-485.0f, 0.0f, 850.0f),		// 9
	D3DXVECTOR3(-180.0f, 0.0f, 850.0f),		// 10
	D3DXVECTOR3(60.0f, 0.0f, 815.0f),		// 11
	D3DXVECTOR3(310.0f, 0.0f, 800.0f),		// 12
	D3DXVECTOR3(700.0f, 0.0f, 765.0f),		// 13
	D3DXVECTOR3(850.0f, 0.0f, 665.0f),		// 14
	D3DXVECTOR3(820.0f, 0.0f, 470.0f),		// 15
	D3DXVECTOR3(970.0f, 0.0f, 430.0f),		// 16
	D3DXVECTOR3(1000.0f, 0.0f, 270.0f),		// 17
	D3DXVECTOR3(1000.0f, 0.0f, 110.0f),		// 18
	D3DXVECTOR3(620.0f, 0.0f, 140.0f),		// 19
	D3DXVECTOR3(345.0f, 0.0f, 200.0f),		// 20
	D3DXVECTOR3(155.0f, 0.0f, 225.0f),		// 21
	D3DXVECTOR3(105.0f, 0.0f, -40.0f),		// 22
	D3DXVECTOR3(130.0f, 0.0f, -330.0f),		// 23
	D3DXVECTOR3(-35.0f, 0.0f, -260.0f),		// 24
	D3DXVECTOR3(-30.0f, 0.0f, -435.0f),		// 25
	D3DXVECTOR3(20.0f, 0.0f, -655.0f),		// 26
	D3DXVECTOR3(-15.0f, 0.0f, -790.0f),		// 27
	D3DXVECTOR3(-320.0f, 0.0f, -815.0f),	// 28
	D3DXVECTOR3(-525.0f, 0.0f, -805.0f),	// 29
	D3DXVECTOR3(-795.0f, 0.0f, -795.0f),	// 30
	D3DXVECTOR3(-705.0f, 0.0f, -435.0f),	// 31
	D3DXVECTOR3(-520.0f, 0.0f, -405.0f),	// 32
	D3DXVECTOR3(-435.0f, 0.0f, -410.0f),	// 33
	D3DXVECTOR3(-230.0f, 0.0f, -430.0f),	// 34
	D3DXVECTOR3(-695.0f, 0.0f, -40.0f),		// 35
	D3DXVECTOR3(-460.0f, 0.0f, -50.0f),		// 36
	D3DXVECTOR3(-225.0f, 0.0f, -50.0f),		// 37
	D3DXVECTOR3(-230.0f, 0.0f, -185.0f),	// 38
	D3DXVECTOR3(-895.0f, 0.0f, 240.0f),		// 39
	D3DXVECTOR3(-710.0f, 0.0f, 305.0f),		// 40
	D3DXVECTOR3(-690.0f, 0.0f, 505.0f),		// 41
	D3DXVECTOR3(-565.0f, 0.0f, 505.0f),		// 42
	D3DXVECTOR3(-430.0f, 0.0f, 490.0f),		// 43
	D3DXVECTOR3(-360.0f, 0.0f, 290.0f),		// 44
	D3DXVECTOR3(-555.0f, 0.0f, 315.0f),		// 45
	D3DXVECTOR3(-120.0f, 0.0f, 265.0f),		// 46
	D3DXVECTOR3(-120.0f, 0.0f, 455.0f),		// 47
	D3DXVECTOR3(655.0f, 0.0f, 435.0f),		// 48
	D3DXVECTOR3(360.0f, 0.0f, 480.0f),		// 49
	D3DXVECTOR3(-225.0f, 0.0f, 580.0f),		// 50
	D3DXVECTOR3(-520.0f, 0.0f, -615.0f),	// 51
	D3DXVECTOR3(185.0f, 0.0f, -700.0f),		// 52
	D3DXVECTOR3(380.0f, 0.0f, -710.0f),		// 53
	D3DXVECTOR3(480.0f, 0.0f, -700.0f),		// 54
	D3DXVECTOR3(470.0f, 0.0f, -485.0f),		// 55
	D3DXVECTOR3(520.0f, 0.0f, -120.0f),		// 56
	D3DXVECTOR3(690.0f, 0.0f, -120.0f),		// 57
	D3DXVECTOR3(245.0f, 0.0f, -380.0f),		// 58
	D3DXVECTOR3(280.0f, 0.0f, -130.0f),		// 59
	D3DXVECTOR3(305.0f, 0.0f, -600.0f),		// 60
	D3DXVECTOR3(-935.0f, 0.0f, 90.0f),		// 61
	D3DXVECTOR3(-145.0f, 0.0f, -590.0f),	// 62
	D3DXVECTOR3(330.0f, 0.0f, 325.0f),		// 63
};

// 各巡回ポイントから行ける次のポイント（-1 は接続なし）
int patrolGraph[NUM_PATROL_POINTS][MAX_CONNECTIONS] = 
{
	{1, -1, -1},	// 0 → 1
	{2, -1, -1},	// 1 → 2
	{3, 31, -1},	// 2 → 3 or 31 (分岐)
	{4, -1, -1},	// 3 → 4
	{5, 35, -1},	// 4 → 5 or 35 (分岐)
	{6, -1, -1},	// 5 → 6 or 39 (分岐)
	{7, -1, -1},	// 6 → 7
	{8, -1, -1},	// 7 → 8
	{9, -1, -1},	// 8 → 9
	{10, -1, -1},	// 9 → 10
	{11, 50, -1},	// 10 → 11 or 50 (分岐)
	{12, -1, -1},	// 11 → 12
	{13, -1, -1},	// 12 → 13
	{14, 49, -1},	// 13 → 14
	{15, -1, -1},	// 14 → 15
	{16, 48, -1},	// 15 → 16 or 48 (分岐)
	{17, -1, -1},	// 16 → 17
	{18, -1, -1},	// 17 → 18
	{19, -1, -1},	// 18 → 19
	{20, -1, -1},	// 19 → 20
	{21, -1, -1},	// 20 → 21
	{22, -1, -1},	// 21 → 22
	{23, -1, -1},	// 22 → 23
	{24, 25, -1},	// 23 → 24 or 25 (分岐)
	{23, -1, -1},	// 24 → 23
	{26, -1, -1},	// 25 → 26
	{27, -1, -1},	// 26 → 27
	{28, -1, -1},	// 27 → 28
	{29, -1, -1},	// 28 → 29
	{30, -1, -1},	// 29 → 30
	{0, -1, -1},	// 30 → 0
	{32, 32, -1},	// 31 → 32
	{33, 51, -1},	// 32 → 33 or 51 (分岐)
	{34, -1, -1},	// 33 → 34
	{25, -1, -1},	// 34 → 25
	{36, -1, -1},	// 35 → 36
	{37, -1, -1},	// 36 → 37
	{38, -1, -1},	// 37 → 38
	{34, -1, -1},	// 38 → 34
	{40, -1, -1},	// 39 → 40
	{41, 45, -1},	// 40 → 41 or 45 (分岐)
	{42, -1, -1},	// 41 → 42
	{43, -1, -1},	// 42 → 43
	{44, -1, -1},	// 43 → 44
	{46, -1, -1},	// 44 → 46
	{44, -1, -1},	// 45 → 44
	{21, -1, -1},	// 46 → 21
	{46, -1, -1},	// 47 → 46
	{49, -1, -1},	// 48 → 49
	{63, -1, -1},	// 49 → 63
	{47, -1, -1},	// 50 → 47
	{29, -1, -1},	// 51 → 29
	{26, -1, -1},	// 52 → 26
	{52, -1, -1},	// 53 → 52
	{53, -1, -1},	// 54 → 53
	{54, -1, -1},	// 55 → 54
	{55, -1, -1},	// 56 → 55
	{57, -1, -1},	// 57 → 56
	{25, -1, -1},	// 58 → 25
	{22, -1, -1},	// 59 → 22
	{52, -1, -1},	// 60 → 52
	{4, -1, -1},	// 61 → 4
	{26, -1, -1},	// 62 → 26
	{21, -1, -1},	// 63 → 21
};

// グローバル変数
Enemy g_aEnemy;							// 敵情報
bool g_bEnd;							// 捕まった判定
bool g_bEndMotion;
bool Inside;							// 視界に入ったか
bool isPlayerInSightPrev;
bool isReversePatrol;					// 巡回の方向（false: 順回り, true: 逆回り）

int currentPatrolPoint;					// 現在の巡回ポイント
int g_nIdxShadowEnemy;

bool SoundRange = false;				// 前フレームで範囲内だったか
float soundTimer = 0.0f;				// 心音のタイマー
const float minInterval = 0.67f;		// 心音の最速間隔（プレイヤーが超接近時）
const float maxInterval = 1.2f;			// 心音の最遅間隔（遠い時）
const float closeDistance = 420.0f;		// 近いと判定する距離（ここに近づくと最速の心音）
const float farDistance = 900.0f;		// 遠いと判定する距離（ここでは最遅の心音）

int chaseTimer = 0;
PathNode openList[MAX_PATH_LENGTH];
PathNode closedList[MAX_PATH_LENGTH];
int map[GRID_X][GRID_Z] = // 0: 移動可能, 1: 障害物
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

Node path[MAX_PATH_LENGTH];				// A*で計算したルート
int pathLength = 0;						// ルートの長さ

// 近傍8方向の移動
int dx[MAX_PATH_DIRECTION] = { 1, -1,  0,  0,  1, -1,  1, -1 };
int dz[MAX_PATH_DIRECTION] = { 0,  0,  1, -1,  1, -1, -1,  1 };

//=============================
// 敵の初期化処理
//=============================
void InitEnemy(void)
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

    //初期化
    g_aEnemy.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置を初期化する
    g_aEnemy.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前の位置を初期化する
	g_aEnemy.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    g_aEnemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量を初期化する
    g_aEnemy.enemymotion.bLoopMotion = false;
    g_aEnemy.enemymotion.nCounterMotion = 0;
	g_aEnemy.RadiusEnemy = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	g_aEnemy.posRadiusEnemy = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	g_aEnemy.state = ENEMYSTATE_PATROLLING;
	g_aEnemy.bUse = false;
	g_aEnemy.bCaughtSound = false;
	g_aEnemy.sightRange = 340.0f;							//視界距離
	g_aEnemy.sightAngle = D3DXToRadian(90.0f);				//視界範囲
	g_aEnemy.nEndCnt = 0;
	g_bEnd = false;
	g_bEndMotion = false;
	Inside = false;
	isPlayerInSightPrev = false;
	isReversePatrol = false;
	currentPatrolPoint = 0;

	LoadEnemyTEXT();

	//g_nIdxShadowEnemy = SetShadow(D3DXVECTOR3(g_aEnemy.pos.x, g_aEnemy.pos.y, g_aEnemy.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//オフセット考慮
	for (int nCntOff = 0; nCntOff < g_aEnemy.enemymotion.nNumModel; nCntOff++)
	{
		g_aEnemy.enemymotion.aModel[nCntOff].Offpos = g_aEnemy.enemymotion.aModel[nCntOff].pos;
		g_aEnemy.enemymotion.aModel[nCntOff].Offrot = g_aEnemy.enemymotion.aModel[nCntOff].rot;
	}

	for (int nCntVtx = 0; nCntVtx < MAX_PARTS; nCntVtx++)
	{

		int nNumVtx;//頂点数
		DWORD sizeFVF;//頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->GetNumVertices();

		//頂点フォーマットの取得
		sizeFVF = D3DXGetFVFVertexSize(g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->GetFVF());

		//頂点バッファのロック
		g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値最大値を取得
			if (vtx.x < g_aEnemy.vtxMin.x)
			{
				g_aEnemy.vtxMin.x = vtx.x;
			}
			else if (vtx.y < g_aEnemy.vtxMin.y)
			{
				g_aEnemy.vtxMin.y = vtx.y;
			}
			else if (vtx.z < g_aEnemy.vtxMin.z)
			{
				g_aEnemy.vtxMin.z = vtx.z;
			}

			if (vtx.x > g_aEnemy.vtxMax.x)
			{
				g_aEnemy.vtxMax.x = vtx.x;
			}
			else if (vtx.y > g_aEnemy.vtxMax.y)
			{
				g_aEnemy.vtxMax.y = vtx.y;
			}
			else if (vtx.z > g_aEnemy.vtxMax.z)
			{
				g_aEnemy.vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		g_aEnemy.size.x = (g_aEnemy.vtxMax.x - g_aEnemy.vtxMin.x);
		g_aEnemy.size.y = (g_aEnemy.vtxMax.y - g_aEnemy.vtxMin.y);
		g_aEnemy.size.z = (g_aEnemy.vtxMax.z - g_aEnemy.vtxMin.z);

		//頂点バッファのアンロック
		g_aEnemy.enemymotion.aModel[nCntVtx].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_aEnemy.enemymotion.aModel[nCntVtx].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aEnemy.enemymotion.aModel[nCntVtx].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャファイルが存在する

				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aEnemy.enemymotion.aModel[nCntVtx].apTexture[nCntMat]);

			}
		}

	}

}
//=============================
// 敵の終了処理
//=============================
void UninitEnemy(void)
{
	StopSound(SOUND_LABEL_INSIGHT);
	StopSound(SOUND_LABEL_ENEMYSTEP1);
	StopSound(SOUND_LABEL_ENEMYSTEP2);

	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		for (int nCntMat = 0; nCntMat < (int)g_aEnemy.enemymotion.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			//テクスチャの破棄
			if (g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat] != NULL)
			{
				g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat]->Release();
				g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat] = NULL;
			}
		}

		//メッシュの破棄
		if (g_aEnemy.enemymotion.aModel[nCntModel].pMesh != NULL)
		{
			g_aEnemy.enemymotion.aModel[nCntModel].pMesh->Release();
			g_aEnemy.enemymotion.aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat != NULL)	
		{
			g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat->Release();
			g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}
//=============================
// 敵の更新処理
//=============================
void UpdateEnemy(void)
{
	if (g_aEnemy.bUse == true)
	{
		bool isPlayerInSightNow = isPlayerInSight(); // 現在の視界判定

		// 視界外から視界内に変化した瞬間
		if (isPlayerInSightNow && !isPlayerInSightPrev)
		{
			// プレイヤーが視界に入った瞬間
			PlaySound(SOUND_LABEL_INSIGHT); // SEを再生
		}
		
		// フラグを更新して次のフレームに備える
		isPlayerInSightPrev = isPlayerInSightNow;

		Player* pPlayer = GetPlayer();

		//移動量を更新(減衰させる)
		g_aEnemy.move.x += (0.0f - g_aEnemy.move.x) * 0.25f;
		g_aEnemy.move.z += (0.0f - g_aEnemy.move.z) * 0.25f;
		g_aEnemy.move.y += (0.0f - g_aEnemy.move.y) * 0.1f;

		//前回の位置を更新
		g_aEnemy.posOld = g_aEnemy.pos;

		//位置を更新
		g_aEnemy.pos.x += g_aEnemy.move.x;
		g_aEnemy.pos.z += g_aEnemy.move.z;
		g_aEnemy.pos.y += g_aEnemy.move.y;


		//CollisionModel();

		CollisionBlock(&g_aEnemy.pos,&g_aEnemy.posOld,&g_aEnemy.move,&g_aEnemy.size);


		D3DXVECTOR3 PlayerRadius(40.0f, 40.0f, 40.0f);				// 捕まる距離
		D3DXVECTOR3 PlayerInsightRadius(120.0f, 120.0f, 120.0f);	// バレる距離
		D3DXVECTOR3 SoundRadius1(600.0f, 600.0f, 600.0f);			// 心音の鳴る距離

		float fDistance =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadius =
			(g_aEnemy.RadiusEnemy.x + PlayerRadius.x) * (g_aEnemy.RadiusEnemy.x + PlayerRadius.x) +
			(g_aEnemy.RadiusEnemy.y + PlayerRadius.y) * (g_aEnemy.RadiusEnemy.y + PlayerRadius.y) +
			(g_aEnemy.RadiusEnemy.z + PlayerRadius.z) * (g_aEnemy.RadiusEnemy.z + PlayerRadius.z);


		// 捕まった
		if (fDistance <= fRadius)
		{
			if (g_aEnemy.bCaughtSound == false)
			{
				PlaySound(SOUND_LABEL_ENEMYCAUGHT);
				g_aEnemy.bCaughtSound = true;
			}
			pPlayer->pos = pPlayer->posOld;
			g_aEnemy.pos = g_aEnemy.posOld;
			g_bEndMotion = true;
		}

		if (g_bEndMotion == true)
		{
			g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_ACTION;

			g_aEnemy.nEndCnt++;

			//キルモーションが終わったら
			if (g_aEnemy.nEndCnt >= 240)
			{
				g_bEnd = true;
			}
		}

		float fDistance2 =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadius2 =
			(g_aEnemy.RadiusEnemy.x + PlayerInsightRadius.x) * (g_aEnemy.RadiusEnemy.x + PlayerInsightRadius.x) +
			(g_aEnemy.RadiusEnemy.y + PlayerInsightRadius.y) * (g_aEnemy.RadiusEnemy.y + PlayerInsightRadius.y) +
			(g_aEnemy.RadiusEnemy.z + PlayerInsightRadius.z) * (g_aEnemy.RadiusEnemy.z + PlayerInsightRadius.z);


		// 追跡モードにする
		if (fDistance2 <= fRadius2)
		{
			g_aEnemy.state = ENEMYSTATE_CHASING;
		}

		float fDistanceSound1 =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadiusSound1 =
			(g_aEnemy.RadiusEnemy.x + SoundRadius1.x) * (g_aEnemy.RadiusEnemy.x + SoundRadius1.x) +
			(g_aEnemy.RadiusEnemy.y + SoundRadius1.y) * (g_aEnemy.RadiusEnemy.y + SoundRadius1.y) +
			(g_aEnemy.RadiusEnemy.z + SoundRadius1.z) * (g_aEnemy.RadiusEnemy.z + SoundRadius1.z);

		// 2乗距離を通常の距離に変換
		float distance = sqrtf(fDistanceSound1);

		bool SoundRangeNow = (fDistanceSound1 <= fRadiusSound1);

		// intervalを距離に応じて変化させる
		float dynamicInterval = maxInterval;

		if (distance < farDistance)
		{
			float t = (distance - closeDistance) / (farDistance - closeDistance);	// 0.0 ~ 1.0 の範囲に正規化
			t = max(0.0f, min(1.0f, t));											// 範囲を超えないように
			dynamicInterval = minInterval + (maxInterval - minInterval) * t;		// 線形補間
		}

		// 範囲内にいる間は一定間隔で音を鳴らす
		if (SoundRangeNow)
		{
			soundTimer += 0.016f;						// 前フレームからの経過時間を加算

			if (soundTimer >= dynamicInterval)
			{
				PlaySound(SOUND_LABEL_HEART);
				soundTimer = 0.0f;						// タイマーをリセット
			}
		}

		// 範囲外に出た瞬間はタイマーをリセット
		if (!SoundRangeNow && SoundRange)
		{
			soundTimer = 0.0f;							// タイマーをリセット
		}

		// フラグを更新
		SoundRange = SoundRangeNow;


		D3DXVECTOR3 posPlayerRadius(1.0f, 1.0f, 1.0f);

		float fDistancePlayer =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		float fRadiusPlayer =
			(g_aEnemy.posRadiusEnemy.x + posPlayerRadius.x) * (g_aEnemy.posRadiusEnemy.x + posPlayerRadius.x) +
			(g_aEnemy.posRadiusEnemy.y + posPlayerRadius.y) * (g_aEnemy.posRadiusEnemy.y + posPlayerRadius.y) +
			(g_aEnemy.posRadiusEnemy.z + posPlayerRadius.z) * (g_aEnemy.posRadiusEnemy.z + posPlayerRadius.z);


		if (isPlayerInSight())
		{
			Inside = true;
		}
		else
		{
			Inside = false;
		}

		if (g_aEnemy.pos.y <= 0)
		{
			g_aEnemy.pos.y = 0.0f;
		}

		//SetPositionShadow(g_nIdxShadowEnemy, D3DXVECTOR3(g_aEnemy.pos.x, 0.0f, g_aEnemy.pos.z));

		//敵の足音
		if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_NEUTRAL && g_aEnemy.enemymotion.nKey == 1 && 
			g_aEnemy.enemymotion.nCounterMotion == 10)
		{
			PlaySound3D(SOUND_LABEL_ENEMYSTEP1);
		}
		else if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_NEUTRAL && g_aEnemy.enemymotion.nKey == 3 &&
			g_aEnemy.enemymotion.nCounterMotion == 5)
		{
			PlaySound3D(SOUND_LABEL_ENEMYSTEP2);
		}

		if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_MOVE && g_aEnemy.enemymotion.nKey == 1 &&
			g_aEnemy.enemymotion.nCounterMotion == 9)
		{
			PlaySound3D(SOUND_LABEL_ENEMYSTEP1);
		}
		else if (g_aEnemy.enemymotion.EnemymotionType == ENEMYMOTIONTYPE_MOVE && g_aEnemy.enemymotion.nKey == 3 && 
			g_aEnemy.enemymotion.nCounterMotion == 5)
		{
			PlaySound3D(SOUND_LABEL_ENEMYSTEP2);
		}

		//全モデルの更新
		for (int nCntModel = 0; nCntModel < g_aEnemy.enemymotion.nNumModel; nCntModel++)
		{
			int nNextKey = (g_aEnemy.enemymotion.nKey + 1) % g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].nNumKey;

			// 境界チェック
			if (g_aEnemy.enemymotion.nKey >= g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].nNumKey ||
				nNextKey >= g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].nNumKey)
			{
				g_aEnemy.enemymotion.nKey = 0;
			}

			D3DXVECTOR3 Mpos, Mrot;
			D3DXVECTOR3 MAnswer, MAnswer2;//計算結果用

			//キー情報から位置・向きを算出
			Mpos.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fPosX - 
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosX;
			Mpos.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fPosY -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosY;
			Mpos.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fPosZ -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosZ;

			Mrot.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fRotX -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotX;
			Mrot.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fRotY -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotY;
			Mrot.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[nNextKey].aKey[nCntModel].fRotZ -
				g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotZ;

			//補間係数を計算
			float t = (float)g_aEnemy.enemymotion.nCounterMotion / g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].nFrame;

			//求める値
			MAnswer.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosX + Mpos.x * t;
			MAnswer.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosY + Mpos.y * t;
			MAnswer.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fPosZ + Mpos.z * t;

			MAnswer2.x = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotX + Mrot.x * t;
			MAnswer2.y = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotY + Mrot.y * t;
			MAnswer2.z = g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].aKey[nCntModel].fRotZ + Mrot.z * t;


			//全パーツの位置・向きを設定
			g_aEnemy.enemymotion.aModel[nCntModel].pos = g_aEnemy.enemymotion.aModel[nCntModel].Offpos + MAnswer;

			g_aEnemy.enemymotion.aModel[nCntModel].rot = g_aEnemy.enemymotion.aModel[nCntModel].Offrot + MAnswer2;

		}

		g_aEnemy.enemymotion.nCounterMotion++;//再生フレーム数に達したら現在のキーを1つ進める

		if (g_aEnemy.enemymotion.nCounterMotion >= g_aEnemy.enemymotion.aEnemyMotionInfo[g_aEnemy.enemymotion.EnemymotionType].aEnemyKeyInfo[g_aEnemy.enemymotion.nKey].nFrame)
		{
			g_aEnemy.enemymotion.nCounterMotion = 0;

			g_aEnemy.enemymotion.nKey++;
		}

		// 状態遷移
		switch (g_aEnemy.state)
		{
		case ENEMYSTATE_PATROLLING:
			// 巡回モード
			Patrol();

			break;

		case ENEMYSTATE_CHASING:
			// 追跡モード
			Chase();

			break;

		case ENEMYSTATE_SEARCHING:
			// 捜索モード
			Search();

			break;
		}
	}
}
//=============================
// 敵の描画処理
//=============================
void DrawEnemy(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (g_aEnemy.bUse == true)
	{
		//計算用マトリックス
		D3DXMATRIX mtxRot, mtxTrans, mtxSize;

		D3DMATERIAL9 matDef;//現在のマテリアル保存用

		D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aEnemy.mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy.rot.y, g_aEnemy.rot.x, g_aEnemy.rot.z);
		D3DXMatrixMultiply(&g_aEnemy.mtxWorld, &g_aEnemy.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aEnemy.pos.x, g_aEnemy.pos.y, g_aEnemy.pos.z);
		D3DXMatrixMultiply(&g_aEnemy.mtxWorld, &g_aEnemy.mtxWorld, &mtxTrans);

		//ワールドマトリックスを設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy.mtxWorld);

		//現在のマテリアルの取得
		pDevice->GetMaterial(&matDef);

		//全モデル(パーツ)の描画
		for (int nCntModel = 0; nCntModel < g_aEnemy.enemymotion.nNumModel; nCntModel++)
		{

			D3DXMATRIX mtxRotModel, mtxTransModel;//計算用マトリックス

			D3DXMATRIX mtxParent;//親のマトリックス

			//パーツのワールドマトリックスも初期化
			D3DXMatrixIdentity(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy.enemymotion.aModel[nCntModel].rot.y, g_aEnemy.enemymotion.aModel[nCntModel].rot.x, g_aEnemy.enemymotion.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_aEnemy.enemymotion.aModel[nCntModel].pos.x, g_aEnemy.enemymotion.aModel[nCntModel].pos.y, g_aEnemy.enemymotion.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの親のマトリックスを設定
			if (g_aEnemy.enemymotion.aModel[nCntModel].nIdxModelParent != -1)
			{//親モデルがある場合

				mtxParent = g_aEnemy.enemymotion.aModel[g_aEnemy.enemymotion.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//親モデルがない場合

				mtxParent = g_aEnemy.mtxWorld;
			}

			//算出したパーツのワールドマトリックスと親のマトリックスをかけ合わせる
			D3DXMatrixMultiply(&g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld, &mtxParent);

			//パーツのワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy.enemymotion.aModel[nCntModel].mtxWorld);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aEnemy.enemymotion.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aEnemy.enemymotion.aModel[nCntModel].dwNumMat; nCntMat++)
			{

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_aEnemy.enemymotion.aModel[nCntModel].apTexture[nCntMat]);

				//モデル(パーツ)の描画
				g_aEnemy.enemymotion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);

			}

		}

		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}
//=============================
// 敵の設定処理
//=============================
void SetEnemy(D3DXVECTOR3 pos)
{
	if (g_aEnemy.bUse == false)
	{
		g_aEnemy.pos = pos;
		g_aEnemy.bUse = true;
	}
}
//============================================
// 敵の取得
//============================================
Enemy* GetEnemy(void)
{
	return &g_aEnemy;
}
//=============================
// 視界内判定
//=============================
bool isPlayerInSight(void) 
{
	Player* pPlayer = GetPlayer();

	// 敵の正面ベクトルを計算
	D3DXVECTOR3 enemyFront;

	enemyFront.x = sinf(g_aEnemy.rot.y);
	enemyFront.y = 0.0f;
	enemyFront.z = cosf(g_aEnemy.rot.y);

	// プレイヤーとの方向ベクトル
	D3DXVECTOR3 toPlayer;

	toPlayer.x = pPlayer->pos.x - g_aEnemy.pos.x;
	toPlayer.y = 0.0f;
	toPlayer.z = pPlayer->pos.z - g_aEnemy.pos.z;

	// プレイヤー方向ベクトルを正規化
	D3DXVec3Normalize(&toPlayer, &toPlayer);

	// 敵の正面ベクトルも正規化
	D3DXVec3Normalize(&enemyFront, &enemyFront);

	// ベクトルの内積を計算
	float dotProduct = D3DXVec3Dot(&enemyFront, &toPlayer);

	// 内積から視野内か判定(0.5fはしきい値)
	if (dotProduct > cosf(g_aEnemy.sightAngle * 0.5f)) 
	{// 視野角の半分で判定 1 → 完全に同じ方向（正面）0 → 直角（真横）- 1 → 真逆（背後）

		// プレイヤーとの距離を計算
		float distanceSquared =
			(g_aEnemy.pos.x - pPlayer->pos.x) * (g_aEnemy.pos.x - pPlayer->pos.x) +
			(g_aEnemy.pos.y - pPlayer->pos.y) * (g_aEnemy.pos.y - pPlayer->pos.y) +
			(g_aEnemy.pos.z - pPlayer->pos.z) * (g_aEnemy.pos.z - pPlayer->pos.z);

		if (distanceSquared <= g_aEnemy.sightRange * g_aEnemy.sightRange)
		{
			return true; // プレイヤーは視界内
		}
	}

	return false; // 視界外
}
//======================================================
// 一番近い巡回ポイントの算出処理
//======================================================
int GetNearestPatrolPoint(D3DXVECTOR3 currentPos) 
{
	float minDistance = FLT_MAX; // 非常に大きな値で初期化
	int nearestPoint  = 0;

	for (int nCnt = 0; nCnt < sizeof(patrolPoints) / sizeof(patrolPoints[0]); nCnt++)
	{
		float distance = sqrtf
		(
			(patrolPoints[nCnt].x - currentPos.x) * (patrolPoints[nCnt].x - currentPos.x) +
			(patrolPoints[nCnt].y - currentPos.y) * (patrolPoints[nCnt].y - currentPos.y) +
			(patrolPoints[nCnt].z - currentPos.z) * (patrolPoints[nCnt].z - currentPos.z)
		);

		if (distance < minDistance) 
		{
			minDistance = distance;
			nearestPoint = nCnt;
		}
	}

	return nearestPoint; // 最も近い巡回ポイントのインデックスを返す
}
//======================================================
// ランダムな次の巡回ポイントを取得
//======================================================
int GetNextPatrolPoint(int currentPoint)
{
	int options[MAX_CONNECTIONS];
	int count = 0;

	// 有効な巡回ポイントをリストアップ
	for (int i = 0; i < MAX_CONNECTIONS; i++) 
	{
		if (patrolGraph[currentPoint][i] != -1) 
		{
			options[count++] = patrolGraph[currentPoint][i];
		}
	}

	// ランダムで次のポイントを選択
	if (count > 0) 
	{
		int randomIndex = rand() % count;
		return options[randomIndex];
	}

	return currentPoint; // もし移動できるポイントがなければ現在地を返す
}
//======================================================
// 巡回処理
//======================================================
void Patrol(void)
{
	g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_NEUTRAL;

	float moveSpeed			= 0.4f;		// 巡回速度
	float distanceToTarget  = 0.0f;		// 目標までの距離
	float rotationSpeed		= 0.07f;	// 回転速度

	D3DXVECTOR3 target = patrolPoints[currentPatrolPoint];

	distanceToTarget = sqrtf(
		(target.x - g_aEnemy.pos.x) * (target.x - g_aEnemy.pos.x) +
		(target.z - g_aEnemy.pos.z) * (target.z - g_aEnemy.pos.z)
	);

	// 目標角度を計算
	float fAngleToTarget = atan2f(target.x - g_aEnemy.pos.x, target.z - g_aEnemy.pos.z);

	// 角度の差分を正規化
	float angleDiff = NormalizeAngle(fAngleToTarget - g_aEnemy.rot.y);

	// 補間回転
	g_aEnemy.rot.y += angleDiff * rotationSpeed;

	// 近づく
	if (distanceToTarget > 5.0f)
	{
		g_aEnemy.move.x += sinf(g_aEnemy.rot.y) * moveSpeed;
		g_aEnemy.move.z += cosf(g_aEnemy.rot.y) * moveSpeed;
	}
	else
	{
		// 到達したら次のポイントをランダムに選択
		currentPatrolPoint = GetNextPatrolPoint(currentPatrolPoint);
	}

	// プレイヤーを視界内で検出したら追跡に切り替える
	if (isPlayerInSight())
	{
		g_aEnemy.state = ENEMYSTATE_CHASING;
	}
}
//======================================================
// 追跡処理
//======================================================
void Chase(void)
{
	Player* pPlayer = GetPlayer();

	g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_MOVE;

	static int lostSightTimer = 0;				// 視界外タイマー
	float rotationSpeed		  = 0.1f;			// 回転速度
	float chaseSpeed		  = 1.12f;			// 追跡速度

	float fAngleToTarget = atan2f(pPlayer->pos.x - g_aEnemy.pos.x, pPlayer->pos.z - g_aEnemy.pos.z);
	
	// 角度の差分を正規化
	float angleDiff = NormalizeAngle(fAngleToTarget - g_aEnemy.rot.y);

	// 補間回転
	g_aEnemy.rot.y += angleDiff * rotationSpeed;

	g_aEnemy.move.x += sinf(fAngleToTarget) * chaseSpeed;
	g_aEnemy.move.z += cosf(fAngleToTarget) * chaseSpeed;

	// プレイヤーが視界外に出たら捜索状態に切り替える
	if (!isPlayerInSight())
	{
		g_aEnemy.state = ENEMYSTATE_SEARCHING; // 捜索状態へ
	}

	if (!isPlayerInSight())
	{
		lostSightTimer++;

		if (lostSightTimer > 180)
		{ // 180フレーム経過
			currentPatrolPoint = GetNearestPatrolPoint(g_aEnemy.pos);

			g_aEnemy.state = ENEMYSTATE_PATROLLING;

			lostSightTimer = 0; // タイマーをリセット
		}
	}
	else
	{
		lostSightTimer = 0; // 視界内に戻ったらタイマーをリセット
	}
}
//void Chase(void)
//{
//	Player* pPlayer = GetPlayer();
//
//	g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_MOVE;
//
//	// CHASE モードになったらタイマーを増やす
//	chaseTimer++;
//
//	Node start = WorldToGrid(g_aEnemy.pos);
//	Node goal = WorldToGrid(pPlayer->pos);
//
//	if (FindPath(start, goal) && pathLength > 0)
//	{
//		Node next = path[pathLength - 1]; // 次の移動先
//
//		D3DXVECTOR3 nextPos = GridToWorld(next);
//
//		float rotationSpeed = 0.1f;
//		float chaseSpeed = 1.1f;
//
//		float fAngleToTarget = atan2f(nextPos.x - g_aEnemy.pos.x, nextPos.z - g_aEnemy.pos.z);
//
//		float angleDiff = NormalizeAngle(fAngleToTarget - g_aEnemy.rot.y);
//
//		g_aEnemy.rot.y += angleDiff * rotationSpeed;
//
//		g_aEnemy.move.x += sinf(fAngleToTarget) * chaseSpeed;
//		g_aEnemy.move.z += cosf(fAngleToTarget) * chaseSpeed;
//	}
//
//	// 視界内ならタイマーをリセット
//	if (isPlayerInSight())
//	{
//		chaseTimer = 0;
//	}
//
//	// 視界外
//	if (!isPlayerInSight() && chaseTimer >= 240)
//	{
//		chaseTimer = 0;  // タイマーリセット
//		g_aEnemy.state = ENEMYSTATE_SEARCHING;
//	}
//}
//======================================================
// 探索処理
//======================================================
void Search(void)
{
	g_aEnemy.enemymotion.EnemymotionType = ENEMYMOTIONTYPE_SEARCH;

	static int searchTimer = 0;

	// もしプレイヤーが視界に入ったら CHASE に戻る
	if (isPlayerInSight()) 
	{
		g_aEnemy.state = ENEMYSTATE_CHASING;
		return;
	}

	// 一定時間探索したら PATROL に戻る
	searchTimer++;
	if (searchTimer > 180)
	{  // 180フレーム（3秒）探索後に巡回に戻る
		currentPatrolPoint = GetNearestPatrolPoint(g_aEnemy.pos);
		g_aEnemy.state = ENEMYSTATE_PATROLLING;
		searchTimer = 0;
	}
}
//======================================================
// 角度の正規化 (-π ～ π)
//======================================================
float NormalizeAngle(float angle)
{
	while (angle > D3DX_PI)
	{
		angle -= D3DX_PI * 2.0f;
	}
	while (angle < -D3DX_PI)
	{
		angle += D3DX_PI * 2.0f;
	}

	return angle;
}
//======================================================
// マップデータの読み込み
//======================================================
void LoadMapInfo(const char* filename)
{
	FILE* pFile = fopen(filename, "r");

	if (pFile != NULL)
	{
		for (int y = 0; y < GRID_Z; y++)
		{
			for (int x = 0; x < GRID_X; x++) 
			{
				char c = fgetc(pFile);

				if (c == '1') 
				{
					map[x][y] = 1; // 壁
				}
				else if (c == '0') 
				{
					map[x][y] = 0; // 移動可能
				}
			}
			fgetc(pFile); // 改行を読み飛ばす
		}
		fclose(pFile);
	}
}
//======================================================
// ヒューリスティック関数
//======================================================
float Heuristic(Node a, Node b)
{
	return fabsf(a.x - b.x) + fabsf(a.z - b.z);
}
//======================================================
// ワールド座標をグリッド座標に変換する関数
//======================================================
Node WorldToGrid(D3DXVECTOR3 pos) 
{
	Node grid;
	grid.x = (int)((pos.x - MIN_X) / GRID_SIZE);
	grid.z = (int)((pos.z - MIN_Z) / GRID_SIZE);

	return grid;
}
//======================================================
// グリッド座標をワールド座標に変換する関数
//======================================================
D3DXVECTOR3 GridToWorld(Node node)
{
	return
	{
		MIN_X + node.x * GRID_SIZE + GRID_SIZE * 0.5f,
		0.0f,
		MIN_Z + node.z * GRID_SIZE + GRID_SIZE * 0.5f
	};
}
//======================================================
// A* の経路探索処理
//======================================================
bool FindPath(Node start, Node goal) 
{
	int iterationCount = 0;

	// 20グリッド以内を探索
	if (abs(start.x - goal.x) > MAX_PATH_DISTANCE || abs(start.z - goal.z) > MAX_PATH_DISTANCE)
	{
		return false;
	}

	pathLength = 0;

	int openCount = 0, closedCount = 0;

	// Openリストに開始ノードを追加
	openList[openCount++] = { start.x, start.z, 0, 0, Heuristic(start, goal), true, false, {-1, -1} };

	while (openCount > 0)
	{
		// openListが大きくなりすぎた
		if (iterationCount++ > MAX_SEARCH_ITERATIONS)
		{
			char msg[256];
			sprintf(msg, "WARNING: openList too large!\nopenCount=%d", openCount);
			MessageBoxA(NULL, msg, "A* Pathfinding Warning", MB_OK | MB_ICONWARNING);

			return false;
		}

		// MAX_SEARCH_ITERATIONS に達したときに、最適なノードを使う
		if (iterationCount++ > MAX_SEARCH_ITERATIONS) 
		{
			if (openCount > 0) 
			{
				// ゴールに最も近いノードを選ぶ
				int bestIndex = 0;
				for (int i = 1; i < openCount; i++)
				{
					if (openList[i].f < openList[bestIndex].f) 
					{
						bestIndex = i;
					}
				}

				pathLength = 0;
				PathNode current = openList[bestIndex];

				while (current.parent.x != -1)
				{
					path[pathLength++] = { current.x, current.z };

					for (int i = 0; i < closedCount; i++)
					{
						if (closedList[i].x == current.parent.x && closedList[i].z == current.parent.z)
						{
							current = closedList[i];
							break;
						}
					}
				}

				return true;  // 途中までの経路を使う
			}

			return false;  // 経路が見つからなかった場合
		}

		// 最も f が小さいノードを探す
		int bestIndex = 0;
		for (int i = 1; i < openCount; i++) 
		{
			if (openList[i].f < openList[bestIndex].f) 
			{
				bestIndex = i;
			}
		}

		// 現在のノードを取り出す
		PathNode current = openList[bestIndex];

		SortDirectionsGoal(goal.x, goal.z, current.x, current.z);

		// ゴールに到達したら終了
		if (current.x == goal.x && current.z == goal.z) 
		{
			pathLength = 0;
			while (current.parent.x != -1) 
			{
				path[pathLength++] = { current.x, current.z };

				for (int i = 0; i < closedCount; i++)
				{
					if (closedList[i].x == current.parent.x && closedList[i].z == current.parent.z)
					{
						current = closedList[i];
						break;
					}
				}
			}
			return true;
		}

		// Openリストから削除し、Closedリストに追加
		closedList[closedCount++] = current;

		if (bestIndex != openCount - 1)
		{
			openList[bestIndex] = openList[openCount - 1]; // 最後の要素を現在の場所にコピー
		}
		openCount--; // カウントを減らす

		// 近傍のノードを探索
		for (int i = 0; i < MAX_PATH_DIRECTION; i++)
		{
			int nx = current.x + dx[i];
			int nz = current.z + dz[i];

			// マップ範囲外 or 壁ならスキップ
			if (nx < 0 || nz < 0 || nx >= GRID_X || nz >= GRID_Z || map[nx][nz] == 1)
			{
				continue;
			}

			// 既に Closed にあるならスキップ
			bool inClosed = false;
			for (int j = 0; j < closedCount; j++) 
			{
				if (closedList[j].x == nx && closedList[j].z == nz)
				{
					inClosed = true;
					break;
				}
			}
			if (inClosed)
			{
				continue;
			}

			float g = current.g + ((i < 4) ? 1.0f : 1.414f); // 直線1.0, 斜め1.414
			float h = Heuristic({ nx, nz }, goal);
			float f = g + h;

			// 既に Open にある場合、より良い経路なら更新
			bool inOpen = false;
			for (int j = 0; j < openCount; j++)
			{
				if (openList[j].x == nx && openList[j].z == nz)
				{
					inOpen = true;
					if (g < openList[j].g)
					{
						openList[j].g = g;
						openList[j].f = f;
						openList[j].parent = { current.x, current.z };
					}
					break;
				}
			}
			if (!inOpen) 
			{
				openList[openCount++] = { nx, nz, f, g, h, true, false, { current.x, current.z } };
			}
		}
	}
	return false; // 経路なし
}
//======================================================
// 目標地点に近い方向を優先する処理(ソート)
//======================================================
void SortDirectionsGoal(int goalX, int goalZ, int currentX, int currentZ) 
{
	float distances[MAX_PATH_DIRECTION];
	int order[MAX_PATH_DIRECTION] = { 0,1,2,3,4,5,6,7 };

	for (int i = 0; i < MAX_PATH_DIRECTION; i++)
	{
		int nx = currentX + dx[i];
		int nz = currentZ + dz[i];
		distances[i] = fabsf(nx - goalX) + fabsf(nz - goalZ);
	}

	// 近い順に並べ替え（バブルソート）
	for (int i = 0; i < 7; i++)
	{
		for (int j = i + 1; j < MAX_PATH_DIRECTION; j++)
		{
			if (distances[i] > distances[j])
			{
				float tempDist = distances[i];
				distances[i] = distances[j];
				distances[j] = tempDist;

				int tempOrder = order[i];
				order[i] = order[j];
				order[j] = tempOrder;
			}
		}
	}

	// 並び替えた結果を dx, dz に適用
	int newDx[MAX_PATH_DIRECTION], newDz[MAX_PATH_DIRECTION];

	for (int i = 0; i < MAX_PATH_DIRECTION; i++)
	{
		newDx[i] = dx[order[i]];
		newDz[i] = dz[order[i]];
	}
	memcpy(dx, newDx, sizeof(dx));
	memcpy(dz, newDz, sizeof(dz));
}
//======================================================
// 捕まった判定
//======================================================
bool GetEnd(void)
{
	return g_bEnd;
}
//======================================================
// キルモーション判定
//======================================================
bool GetEndMotion(void)
{
	return g_bEndMotion;
}
//======================================================
// 視界に入ったか判定
//======================================================
bool GetInside(void)
{
	return Inside;
}