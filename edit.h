//=======================================
//
// �G�f�B�b�g����[edit.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _EDIT_H_//���̃}�N����`������Ă��Ȃ�������
#define _EDIT_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define BLOCKPATH_1 ("data/block.txt")
#define WALLPATH_1 ("data/wall.txt")
#define MAX_EDITWORD (4096)

//�e�N�X�`���\����
typedef struct
{
    LPDIRECT3DTEXTURE9 apTexture[MAX_BLOCKTEXTURE]; //�e�N�X�`���ւ̃|�C���^
    LPD3DXMESH pMesh;
    LPD3DXBUFFER pBuffMat;				//	�}�e���A���ւ̃|�C���^
    DWORD dwNumMat;						//	�}�e���A����
}BlockTex;

//�\����
typedef struct
{
    D3DXVECTOR3 pos;					// �ʒu(�I�t�Z�b�g)
    D3DXVECTOR3 move;					// �ړ���
    D3DXVECTOR3 rot;					// ����
    //D3DXVECTOR3 size;
    int nType;
    bool bUse;
    D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X
    BlockTex blockTex[BLOCKTYPE_MAX];
}Editinfo;

//�v���g�^�C�v�錾
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);
void SaveBlockData(void);
void SaveWallData(void);
void LoadBlockData(void);
void LoadWallData(void);

#endif
