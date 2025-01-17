//=======================================
//
//���f������[model.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MODEL_H_//���̃}�N����`������Ă��Ȃ�������
#define _MODEL_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_MODEL (1)	//	���f���̎g����
#define MAX_TEXTUREMODEL (128)

//�ǂ̎��
typedef enum
{
	WALLTYPE_NORMAL=0,
	WALLTYPE_MAX
}WALLTYPE;

//���f���\����
typedef struct
{
	D3DXVECTOR3 pos;					//	�ʒu(�I�t�Z�b�g)
	LPDIRECT3DTEXTURE9 apTexture[MAX_TEXTUREMODEL];	//	�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 move;					//�ړ���
	D3DXVECTOR3 rot;					//	����
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 size;
	int nType;
	int Index;
	bool bUse;
	LPD3DXMESH pMesh;			
	LPD3DXBUFFER pBuffMat;				//	�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;						//	�}�e���A����
	int nIdxModelParent;				//	�e���f���̃C���f�b�N�X
	D3DXMATRIX mtxWorld;				//	���[���h�}�g���b�N�X
	D3DXVECTOR3 Offpos;
	D3DXVECTOR3 Offrot;
	bool bScoreAdded;					// �X�R�A���Z�ς݂��ǂ���
	bool bSoundPlayed;					// �����Đ��ς݂��ǂ���
}Model;

static const char* MODEL[MAX_MODEL] =
{

	"data/MODEL/wall.x",				//	��

};

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void SetModel(D3DXVECTOR3 pos, int nType);
void CollisionModel(void);//�����蔻��

#endif

