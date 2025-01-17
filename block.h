//=======================================
//
//�u���b�N�z�u����[block.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _BLOCK_H_//���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_BLOCK (20)	// �u���b�N�̎g����
//#define MAX_TEXTUREBLOCK (128)

// �u���b�N�̎��
typedef enum
{
	BLOCKTYPE_NORMAL = 0,
	BLOCKTYPE_DOOR,
	BLOCKTYPE_MAX
}BLOCKTYPE;

//�u���b�N�̏��
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[BLOCKTYPE_MAX];	//	�e�N�X�`���ւ̃|�C���^
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;				//	�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;						//	�}�e���A����
}Blockinfo;

// �u���b�N�\����
typedef struct
{
	D3DXVECTOR3 pos;					//	�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 move;					//�ړ���
	D3DXVECTOR3 rot;					//	����
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
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
	"data/MODEL/wall.x",				//	��
	"data/MODEL/door.x",				//	�h�A
};

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
void CollisionBlock(void);//�����蔻��
Block* GetBlock(void);
bool GetExit(void);

#endif

