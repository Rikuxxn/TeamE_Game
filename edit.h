//=======================================
//
// �G�f�B�b�g����[edit.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _EDIT_H_//���̃}�N����`������Ă��Ȃ�������
#define _EDIT_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "block.h"

#define BLOCKPATH_1 ("data/block.txt")
#define WALLPATH_1 ("data/wall.txt")
#define TITLEPATH_1 ("data/title.txt")

#define MAX_EDITWORD (4096)
#define MAX_SPEED (10.0f)                               // �G�f�B�^�[��̃u���b�N�̈ړ���

//�e�N�X�`���\����
typedef struct
{
    LPDIRECT3DTEXTURE9 apTexture[MAX_BLOCKTEXTURE];     // �e�N�X�`���ւ̃|�C���^
    LPD3DXMESH pMesh;                                   // ���b�V���ւ̃|�C���^
    LPD3DXBUFFER pBuffMat;				                // �}�e���A���ւ̃|�C���^
    DWORD dwNumMat;						                // �}�e���A����
}BlockTex;

//�\����
typedef struct
{
    D3DXVECTOR3 pos;					                // �ʒu(�I�t�Z�b�g)
    D3DXVECTOR3 move;					                // �ړ���
    D3DXVECTOR3 rot;					                // ����
    int nType;                                          // ���
    bool bUse;                                          // �g�p����Ă��邩�ǂ���
    D3DXMATRIX mtxWorld;				                // ���[���h�}�g���b�N�X
    BlockTex blockTex[BLOCKTYPE_MAX];
}Editinfo;

//�v���g�^�C�v�錾
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);

void SaveBlockData(void);
void SaveWallData(void);
void SaveTitleData(void);

void LoadBlockData(void);
void LoadWallData(void);
void LoadTitleData(void);

#endif
