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
#define MAX_EDITWORD (4096)


//�\����
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
    Blockinfo blockinfo[BLOCKTYPE_MAX];
}Editinfo;

//�v���g�^�C�v�錾
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);
void SaveBlockData(void);
void LoadBlockData(void);

#endif
