//=======================================
//
//�u���b�N�z�u����[block.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _BLOCK_H_//���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_BLOCK (100)	// �u���b�N�̎g����
#define MAX_BLOCKTEXTURE (256)//�u���b�N�̍ő�e�N�X�`��

// �u���b�N�̎��
typedef enum
{
	BLOCKTYPE_WALL = 0,
	BLOCKTYPE_WALL_TATE,
	BLOCKTYPE_UFOCATCHER1,
	BLOCKTYPE_UFOCATCHER2,
	BLOCKTYPE_BALLPOOL,
	BLOCKTYPE_ARCADE1,
	BLOCKTYPE_ARCADE2,
	BLOCKTYPE_SWEETLAND,
	BLOCKTYPE_GASYAPON1,

	BLOCKTYPE_MAX
}BLOCKTYPE;

//�u���b�N�̏��
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[MAX_BLOCKTEXTURE];	//	�e�N�X�`���ւ̃|�C���^
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;				//	�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;						//	�}�e���A����
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
}Blockinfo;

// �u���b�N�\����
typedef struct
{
	D3DXVECTOR3 pos;					//	�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 move;					//�ړ���
	D3DXVECTOR3 rot;					//	����
	D3DXVECTOR3 size;
	int nType;
	bool bUse;
	D3DXMATRIX mtxWorld;				//	���[���h�}�g���b�N�X
	bool bScoreAdded;					// �X�R�A���Z�ς݂��ǂ���
	bool bSoundPlayed;					// �����Đ��ς݂��ǂ���
	Blockinfo blockinfo[BLOCKTYPE_MAX];
}Block;

static const char* BLOCK[BLOCKTYPE_MAX] =
{
	"data/MODEL/wall.x",				//	�c��
	"data/MODEL/wall_tate.x",			//	����
	"data/MODEL/Crane_game000.x",		// �N���[���Q�[��1
	"data/MODEL/UFO.x",					// �N���[���Q�[��2
	"data/MODEL/Ball_pool.x",			// �{�[���v�[��
	"data/MODEL/arcade.x",				// �A�[�P�[�h1
	"data/MODEL/Fightng_game000.x",		// �A�[�P�[�h2
	"data/MODEL/SweetLand.x",			// �X�C�[�g�����h
	"data/MODEL/gasyapon00.x",			// �K�V���|��

};

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
void CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3* pPosOld,D3DXVECTOR3* pMove, D3DXVECTOR3* pSize);//�����蔻��
Block* GetBlock(void);
bool GetExit(void);

#endif

