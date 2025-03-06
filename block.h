//=======================================
//
// ブロック配置処理 [block.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _BLOCK_H_//このマクロ定義がされていなかったら
#define _BLOCK_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_BLOCK (256)									// ブロックの使う数
#define MAX_BLOCKTEXTURE (64)							// ブロックの最大テクスチャ

// ブロックの種類
typedef enum
{
	BLOCKTYPE_WALL = 0,
	BLOCKTYPE_WALL_TATE,
	BLOCKTYPE_WALL_EXITTOP,
	BLOCKTYPE_UFOCATCHER1,
	BLOCKTYPE_UFOCATCHER2,
	BLOCKTYPE_BALLPOOL,
	BLOCKTYPE_ARCADE1,
	BLOCKTYPE_ARCADE2,
	BLOCKTYPE_ARCADE_BOARD,
	BLOCKTYPE_CRANE_BOARD,
	BLOCKTYPE_PARK_BOARD,
	BLOCKTYPE_GASYAPON1,
	BLOCKTYPE_RACEGAME,
	BLOCKTYPE_EXCHANGE,

	BLOCKTYPE_PARKROOF,
	BLOCKTYPE_PARKENTRANCE_R,
	BLOCKTYPE_PARKENTRANCE_L,
	BLOCKTYPE_PARKWALL,
	BLOCKTYPE_SLIDE_PILLAR,
	BLOCKTYPE_SLIDE,
	BLOCKTYPE_SLIDE_LADDER,
	BLOCKTYPE_SLIDE_TOP,
	BLOCKTYPE_SLIDE_STAIRS,

	BLOCKTYPE_BENCH,
	BLOCKTYPE_ROCKET,
	BLOCKTYPE_SLOT,
	BLOCKTYPE_SLOT_CHAIR,
	BLOCKTYPE_PURIKURA,
	BLOCKTYPE_AIRHOCKEY,
	BLOCKTYPE_SHOOTING,
	BLOCKTYPE_VENDING,
	BLOCKTYPE_UFOCATCHER_MINI,
	BLOCKTYPE_TITLEBOARD,
	BLOCKTYPE_EXIT,
	BLOCKTYPE_EXIT_SIGN,
	BLOCKTYPE_KEYPAD,
	BLOCKTYPE_TUTORIALBOARD,
	BLOCKTYPE_FUSE,
	BLOCKTYPE_FUSEBOX,
	BLOCKTYPE_FUSEBOX_CMP,
	BLOCKTYPE_BALL,
	BLOCKTYPE_BEAR,
	BLOCKTYPE_EXIT2,
	BLOCKTYPE_CLEAR,

	BLOCKTYPE_MAX
}BLOCKTYPE;

// ブロックの情報
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[MAX_BLOCKTEXTURE];		// テクスチャへのポインタ
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;								// マテリアルへのポインタ
	DWORD dwNumMat;										// マテリアル数
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
}Blockinfo;

// フラグメント構造体
typedef struct
{
	bool bFog;						// 霧の有効・無効
	bool bExit;						// 出口に入ったか
	bool bArcade;					// アーケードゲームの判定
	bool bCatcher;					// UFOキャッチャーの判定
	bool bBall;						// ボールプールの判定
	bool bKeypad;					// キーパッドの判定
	bool bFuse;						// ヒューズの判定
	bool bFusebox;					// ヒューズボックスの判定
	bool bFuseGet;					// ヒューズ獲得判定
	bool bFuseCmp;					// ヒューズをつけた
	bool bHintBall;					// ヒントボール
	bool bHintBear;					// ヒントくまさん
	bool bSet;						// ブロック設置したかどうか1
	bool bSet2;						// ブロック設置したかどうか2
	bool bSet3;						// ブロック(クリアブロック)設置したかどうか3
}Flags;

// ブロック構造体
typedef struct
{
	D3DXVECTOR3 pos;									// 位置(オフセット)
	D3DXVECTOR3 move;									// 移動量
	D3DXVECTOR3 rot;									// 向き
	D3DXVECTOR3 size;									// サイズ
	int nType;											// タイプ 
	bool bUse;											// 使用しているかどうか
	D3DXMATRIX mtxWorld;								// ワールドマトリックス
	bool bScoreAdded;									// スコア加算済みかどうか
	bool bSoundPlayed;									// 音を再生済みかどうか
	bool bInsight;										// 範囲に入ったかどうか
	Blockinfo blockinfo[BLOCKTYPE_MAX];
}Block;

static const char* BLOCK[BLOCKTYPE_MAX] =
{
	"data/MODEL/wall.x",								// 縦壁
	"data/MODEL/wall_tate.x",							// 横壁
	"data/MODEL/wall_exittop.x",						// 出口上壁
	"data/MODEL/Crane_game000.x",						// クレーンゲーム1
	"data/MODEL/UFO.x",									// クレーンゲーム2
	"data/MODEL/Ball_pool.x",							// ボールプール
	"data/MODEL/arcade.x",								// アーケード1
	"data/MODEL/Fightng_game000.x",						// アーケード2
	"data/MODEL/arcade_board.x",						// アーケードエリア看板
	"data/MODEL/crane_board.x",							// クレーンエリア看板
	"data/MODEL/park_board.x",							// キッズパーク看板
	"data/MODEL/gasyapon00.x",							// ガシャポン
	"data/MODEL/Racing_game.x",							// レースゲーム
	"data/MODEL/ExChange.x",							// 両替機
	"data/MODEL/Kids_park_Entrance_roof.x",				// キッズパーク入口の屋根
	"data/MODEL/Kids_park_Entrance_R.x",				// キッズパーク入口右
	"data/MODEL/Kids_park_Entrance_L.x",				// キッズパーク入口左
	"data/MODEL/Kids_park_wall000.x",					// キッズパーク壁
	"data/MODEL/suberidai_hasira.x",					// 滑り台の柱
	"data/MODEL/suberidai_suberidai.x",					// 滑り台本体
	"data/MODEL/suberidai_hasigo.x",					// 滑り台のはしご
	"data/MODEL/suberidai_uenokai.x",					// 滑り台の上
	"data/MODEL/suberidai_kaidan.x",					// 滑り台の階段
	"data/MODEL/tablebench.x",							// ベンチ
	"data/MODEL/Kids_ride_Roket.x",						// ロケット
	"data/MODEL/Slot.x",								// スロット
	"data/MODEL/Chair.x",								// スロットのいす
	"data/MODEL/Purikura.x",							// プリクラ
	"data/MODEL/Airhockey.x",							// エアホッケー
	"data/MODEL/Shootinggame.x",						// シューティングゲーム
	"data/MODEL/Vending.x",								// 自販機
	"data/MODEL/UFO_mini.x",							// UFOキャッチャーミニ
	"data/MODEL/title_board.x",							// タイトルロゴ表示用ボード
	"data/MODEL/exit.x",								// 出口ドア左
	"data/MODEL/exit_sign.x",							// 非常口看板
	"data/MODEL/keypad.x",								// キーパッド
	"data/MODEL/tutorial_board.x",						// チュートリアル表示用ボード
	"data/MODEL/huzu.x",								// ヒューズ
	"data/MODEL/fusebox.x",								// ヒューズボックス
	"data/MODEL/fusebox_cmp.x",							// ヒューズボックス完全体
	"data/MODEL/ball.x",								// ボール
	"data/MODEL/bear.x",								// くまさん
	"data/MODEL/exit.x",								// 出口ドア右
	"data/MODEL/clear_block.x",							// クリア判定ブロック

};

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);
void CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3* pPosOld,D3DXVECTOR3* pMove, D3DXVECTOR3* pSize);//当たり判定

// OBB 衝突判定関数のプロトタイプ宣言
bool CheckOBBCollision(const D3DXMATRIX& world1, const D3DXVECTOR3& size1,
	const D3DXMATRIX& world2, const D3DXVECTOR3& size2);
bool OverlapOnAxis(const D3DXVECTOR3& center1, const D3DXVECTOR3 axes1[3], const D3DXVECTOR3& size1,
	const D3DXVECTOR3& center2, const D3DXVECTOR3 axes2[3], const D3DXVECTOR3& size2, const D3DXVECTOR3& axis);
float GetProjectionRadius(const D3DXVECTOR3& size, const D3DXVECTOR3 axes[3], const D3DXVECTOR3& axis);

// イベント判定用関数のプロトタイプ宣言
void CheckBlocksInCenter(void);

void MeshcylinderOnBlock(int targetType);
bool GetBlockPosition(D3DXVECTOR3* outPosition);

Block* GetBlock(void);
Flags* GetFlag();

#endif

