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

#define MAX_EDITWORD (4096)
#define MAX_SPEED (6.0f)                               // �G�f�B�^�[��̃u���b�N�̈ړ���

// �t�@�C���p�X�̎��
typedef enum
{
    PATH_BLOCK=0,
    PATH_WALL,
    PATH_TITLE,
    PATH_TEST,

    PATH_MAX
}PathType;

//�e�N�X�`���\����
typedef struct
{
    LPDIRECT3DTEXTURE9 apTexture[MAX_BLOCKTEXTURE];     // �e�N�X�`���ւ̃|�C���^
    LPD3DXMESH pMesh;                                   // ���b�V���ւ̃|�C���^
    LPD3DXBUFFER pBuffMat;				                // �}�e���A���ւ̃|�C���^
    DWORD dwNumMat;						                // �}�e���A����
}BlockTex;

//�G�f�B�^�[�\����
typedef struct
{
    D3DXVECTOR3 pos;					                // �ʒu(�I�t�Z�b�g)
    D3DXVECTOR3 move;					                // �ړ���
    D3DXVECTOR3 rot;					                // ����
    int nType;                                          // ���
    int nPathType;                                          // �t�@�C���p�X�̎��
    bool bUse;                                          // �g�p����Ă��邩�ǂ���
    D3DXMATRIX mtxWorld;				                // ���[���h�}�g���b�N�X
    BlockTex blockTex[BLOCKTYPE_MAX];
}Editinfo;

// �t�@�C���p�X
static const char* PATH[PATH_MAX] =
{
    "data/block.txt",				
    "data/wall.txt",
    "data/title.txt",
    "data/test.txt",
};

//�v���g�^�C�v�錾
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);

void SaveBlockData(void);
void LoadBlockData(void);
void LoadParticular(int nPathType);
void SelectBlockByMouse(void);
void MoveEditBlock(void);
void TurnEditBlock(void);
void OperationEdit(void);
void NormalizeEditBlock(void);
const char* GetCurrentSaveFilePath(void);
const char* GetCurrentLoadFilePath(void);

#endif
