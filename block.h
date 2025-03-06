//=======================================
//
// �u���b�N�z�u���� [block.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _BLOCK_H_//���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_BLOCK (256)									// �u���b�N�̎g����
#define MAX_BLOCKTEXTURE (64)							// �u���b�N�̍ő�e�N�X�`��

// �u���b�N�̎��
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

// �u���b�N�̏��
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[MAX_BLOCKTEXTURE];		// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;								// �}�e���A���ւ̃|�C���^
	DWORD dwNumMat;										// �}�e���A����
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
}Blockinfo;

// �t���O�����g�\����
typedef struct
{
	bool bFog;						// ���̗L���E����
	bool bExit;						// �o���ɓ�������
	bool bArcade;					// �A�[�P�[�h�Q�[���̔���
	bool bCatcher;					// UFO�L���b�`���[�̔���
	bool bBall;						// �{�[���v�[���̔���
	bool bKeypad;					// �L�[�p�b�h�̔���
	bool bFuse;						// �q���[�Y�̔���
	bool bFusebox;					// �q���[�Y�{�b�N�X�̔���
	bool bFuseGet;					// �q���[�Y�l������
	bool bFuseCmp;					// �q���[�Y������
	bool bHintBall;					// �q���g�{�[��
	bool bHintBear;					// �q���g���܂���
	bool bSet;						// �u���b�N�ݒu�������ǂ���1
	bool bSet2;						// �u���b�N�ݒu�������ǂ���2
	bool bSet3;						// �u���b�N(�N���A�u���b�N)�ݒu�������ǂ���3
}Flags;

// �u���b�N�\����
typedef struct
{
	D3DXVECTOR3 pos;									// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 move;									// �ړ���
	D3DXVECTOR3 rot;									// ����
	D3DXVECTOR3 size;									// �T�C�Y
	int nType;											// �^�C�v 
	bool bUse;											// �g�p���Ă��邩�ǂ���
	D3DXMATRIX mtxWorld;								// ���[���h�}�g���b�N�X
	bool bScoreAdded;									// �X�R�A���Z�ς݂��ǂ���
	bool bSoundPlayed;									// �����Đ��ς݂��ǂ���
	bool bInsight;										// �͈͂ɓ��������ǂ���
	Blockinfo blockinfo[BLOCKTYPE_MAX];
}Block;

static const char* BLOCK[BLOCKTYPE_MAX] =
{
	"data/MODEL/wall.x",								// �c��
	"data/MODEL/wall_tate.x",							// ����
	"data/MODEL/wall_exittop.x",						// �o�����
	"data/MODEL/Crane_game000.x",						// �N���[���Q�[��1
	"data/MODEL/UFO.x",									// �N���[���Q�[��2
	"data/MODEL/Ball_pool.x",							// �{�[���v�[��
	"data/MODEL/arcade.x",								// �A�[�P�[�h1
	"data/MODEL/Fightng_game000.x",						// �A�[�P�[�h2
	"data/MODEL/arcade_board.x",						// �A�[�P�[�h�G���A�Ŕ�
	"data/MODEL/crane_board.x",							// �N���[���G���A�Ŕ�
	"data/MODEL/park_board.x",							// �L�b�Y�p�[�N�Ŕ�
	"data/MODEL/gasyapon00.x",							// �K�V���|��
	"data/MODEL/Racing_game.x",							// ���[�X�Q�[��
	"data/MODEL/ExChange.x",							// ���֋@
	"data/MODEL/Kids_park_Entrance_roof.x",				// �L�b�Y�p�[�N�����̉���
	"data/MODEL/Kids_park_Entrance_R.x",				// �L�b�Y�p�[�N�����E
	"data/MODEL/Kids_park_Entrance_L.x",				// �L�b�Y�p�[�N������
	"data/MODEL/Kids_park_wall000.x",					// �L�b�Y�p�[�N��
	"data/MODEL/suberidai_hasira.x",					// �����̒�
	"data/MODEL/suberidai_suberidai.x",					// �����{��
	"data/MODEL/suberidai_hasigo.x",					// �����̂͂���
	"data/MODEL/suberidai_uenokai.x",					// �����̏�
	"data/MODEL/suberidai_kaidan.x",					// �����̊K�i
	"data/MODEL/tablebench.x",							// �x���`
	"data/MODEL/Kids_ride_Roket.x",						// ���P�b�g
	"data/MODEL/Slot.x",								// �X���b�g
	"data/MODEL/Chair.x",								// �X���b�g�̂���
	"data/MODEL/Purikura.x",							// �v���N��
	"data/MODEL/Airhockey.x",							// �G�A�z�b�P�[
	"data/MODEL/Shootinggame.x",						// �V���[�e�B���O�Q�[��
	"data/MODEL/Vending.x",								// ���̋@
	"data/MODEL/UFO_mini.x",							// UFO�L���b�`���[�~�j
	"data/MODEL/title_board.x",							// �^�C�g�����S�\���p�{�[�h
	"data/MODEL/exit.x",								// �o���h�A��
	"data/MODEL/exit_sign.x",							// �����Ŕ�
	"data/MODEL/keypad.x",								// �L�[�p�b�h
	"data/MODEL/tutorial_board.x",						// �`���[�g���A���\���p�{�[�h
	"data/MODEL/huzu.x",								// �q���[�Y
	"data/MODEL/fusebox.x",								// �q���[�Y�{�b�N�X
	"data/MODEL/fusebox_cmp.x",							// �q���[�Y�{�b�N�X���S��
	"data/MODEL/ball.x",								// �{�[��
	"data/MODEL/bear.x",								// ���܂���
	"data/MODEL/exit.x",								// �o���h�A�E
	"data/MODEL/clear_block.x",							// �N���A����u���b�N

};

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);
void CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3* pPosOld,D3DXVECTOR3* pMove, D3DXVECTOR3* pSize);//�����蔻��

// OBB �Փ˔���֐��̃v���g�^�C�v�錾
bool CheckOBBCollision(const D3DXMATRIX& world1, const D3DXVECTOR3& size1,
	const D3DXMATRIX& world2, const D3DXVECTOR3& size2);
bool OverlapOnAxis(const D3DXVECTOR3& center1, const D3DXVECTOR3 axes1[3], const D3DXVECTOR3& size1,
	const D3DXVECTOR3& center2, const D3DXVECTOR3 axes2[3], const D3DXVECTOR3& size2, const D3DXVECTOR3& axis);
float GetProjectionRadius(const D3DXVECTOR3& size, const D3DXVECTOR3 axes[3], const D3DXVECTOR3& axis);

// �C�x���g����p�֐��̃v���g�^�C�v�錾
void CheckBlocksInCenter(void);

void MeshcylinderOnBlock(int targetType);
bool GetBlockPosition(D3DXVECTOR3* outPosition);

Block* GetBlock(void);
Flags* GetFlag();

#endif

