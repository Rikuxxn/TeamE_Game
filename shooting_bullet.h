#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER=0,//�v���C���[�̒e
	BULLETTYPE_ENEMY,//�G�̒e
	BULLETTYPE_MAX
}BULLETTYPE;

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//�p�x
	int nLife;//����
	BULLETTYPE type;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
	float fAngle;//
	float fLength;//
	int nBulletType;//�e�̎��
}Bullet;


//�v���g
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
BULLETTYPE *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move ,BULLETTYPE type,int nLife,int nBulletType);//, D3DXVECTOR3 rot, float fLength);//���ˈʒu�ƈړ���
#endif