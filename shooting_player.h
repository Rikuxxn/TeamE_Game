//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#ifndef _SHOOTINGPLAYER_H_//このマクロ定義がされてなかったら
#define _SHOOTINGPLAYER_H_//２重インクルード防止のマクロ定義

// マクロ定義
#define WIDTH (20.0f)		// 幅
#define HEIGHT (35.0f)		// 高さ
#define BULLET_INTERVAL (10)// 発射間隔
#define BULLET_COOL (20)	// クールタイム
#define BULLET_MAX (3)		// 1度の射撃数

// プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	// 出現状態（点滅）
	PLAYERSTATE_NORMAL,		// 通常
	PLAYERSTATE_DAMAGE,		// ダメージ
	PLAYERSTATE_DEATH,		// 脂肪
	PLAYERSTATE_MAX
}PLAYERSTATE;

// プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;	// プレイヤーの位置
	D3DXVECTOR3 move;	// 移動量
	PLAYERSTATE state;	// 状態
	int nCounterState;	// 状態管理カウンター
	bool bDisp;			// 表示
	D3DXVECTOR3 rot;	// 向き
	D3DXVECTOR3 Bullet; // 弾の速さ
	float Length;		// 対角線の長さ
	float Angle;		// 対角線の角度
	bool bUse;			// 使っているか
	bool bHit;			// あたりはんてぇ
	int nCntAnimState;	// 状態をカウント
	int nLife;			// 命
	int nBulletType;	// 弾の切り替え
	int nBulletCnt;		// 弾カウント
	int nBulletCool;	// クールタイム
	int nBulletMax;		// 1度の発射数
}ShootingPlayer;

//プロト
void InitShootingPlayer(void);
void UninitShootingPlayer(void);
void UpdateShootingPlayer(void);
void DrawShootingPlayer(void);
ShootingPlayer* GetShootingPlayer(void);
void HitShootingPlayer(int nDamage);				 //あたりはんてぇ

#endif