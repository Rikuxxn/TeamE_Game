//=======================================
//
//モーション読み込み処理[motion.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MOTION_H_//このマクロ定義がされていなかったら
#define _MOTION_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_WORD (1024)//最大文字数

#define MAX_ENEMY_PARTS (16)						// 敵のパーツ数
#define MAX_PARTS (15)								// プレイヤーパーツ数

#define MAX_KEY (30)								// キーの最大数

#define MOTIONPATH_1 ("data/motion.txt")
#define MOTIONPATH_2 ("data/enemymotion.txt")

//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	// プレイヤー:待機
	MOTIONTYPE_MOVE,		// プレイヤー:移動
	MOTIONTYPE_ACTION,		// プレイヤー:アクション

	MOTIONTYPE_MAX
}MOTIONTYPE;

//モーションの種類
typedef enum
{
	ENEMYMOTIONTYPE_NEUTRAL = 0,	// プレイヤー:待機 / 敵:通常移動
	ENEMYMOTIONTYPE_MOVE,		// プレイヤー:移動 / 敵:追跡
	ENEMYMOTIONTYPE_ACTION,		// プレイヤー:アクション / 敵:攻撃
	ENEMYMOTIONTYPE_SEARCH,		// 敵:索敵

	ENEMYMOTIONTYPE_MAX
}ENEMYMOTIONTYPE;

//キー構造体
typedef struct
{
	float fPosX;					//位置(X)
	float fPosY;					//位置(Y)
	float fPosZ;					//位置(Z)

	float fRotX;					//向き(X)
	float fRotY;					//向き(Y)
	float fRotZ;					//向き(Z)
}KEY;

//敵のキー構造体
typedef struct
{
	float fPosX;					//位置(X)
	float fPosY;					//位置(Y)
	float fPosZ;					//位置(Z)

	float fRotX;					//向き(X)
	float fRotY;					//向き(Y)
	float fRotZ;					//向き(Z)
}ENEMYKEY;

//キー情報構造体
typedef struct
{
	int nFrame;						//再生フレーム
	KEY aKey[MAX_PARTS];			//各パーツのキー要素

}KEY_INFO;

//キー情報構造体
typedef struct
{
	int nFrame;							//再生フレーム
	KEY aKey[MAX_ENEMY_PARTS];			//各パーツのキー要素

}ENEMYKEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;						//ループするかどうか
	int nNumKey;					//キーの総数
	KEY_INFO aKeyInfo[MAX_KEY];		//キー情報
	int startKey, startFrame;
}MOTION_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;						//ループするかどうか
	int nNumKey;					//キーの総数
	ENEMYKEY_INFO aEnemyKeyInfo[MAX_KEY];		//キー情報
	int startKey, startFrame;
}ENEMYMOTION_INFO;

typedef struct
{
	Model aModel[MAX_PARTS];				//モデル(パーツ)
	int nNumModel;							//モデル(パーツ)の総数
	MOTION_INFO aMotionInfo[MOTIONTYPE_MAX];//モーション情報
	MOTIONTYPE motionType;					//モーションの種類
	int nNumMotion;							//モーション総数
	bool bLoopMotion;						//ループするかどうか
	int nNumKey;							//キーの総数
	int nKey;								//現在のキーNo.
	int nCounterMotion;						//モーションのカウンター
	MOTIONTYPE pMotion;
}Motion;

typedef struct
{
	Model aModel[MAX_ENEMY_PARTS];				//モデル(パーツ)
	int nNumModel;							//モデル(パーツ)の総数
	ENEMYMOTION_INFO aEnemyMotionInfo[ENEMYMOTIONTYPE_MAX];//モーション情報
	ENEMYMOTIONTYPE EnemymotionType;					//モーションの種類
	int nNumMotion;							//モーション総数
	bool bLoopMotion;						//ループするかどうか
	int nNumKey;							//キーの総数
	int nKey;								//現在のキーNo.
	int nCounterMotion;						//モーションのカウンター
	ENEMYMOTIONTYPE pMotionEnemy;
}EnemyMotion;

//プロトタイプ宣言
void LoadPlayerTEXT(void);
void LoadEnemyTEXT(void);

#endif
