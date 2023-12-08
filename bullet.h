//===================================================
//�e(bullet.h)
//Auhor:�n� �C	Date:2023.8.28
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"
#include "enemy.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define BULLET_MAX			(100)//�L�����N�^�[�̐�
#define BULLET_WIDTH		(40)//�摜����
#define BULLET_HEIGHT		(40)//�摜�c����
#define BULLET_HITBOX_WIDTH		(40 * 0.3f)//�e�̃q�b�g�{�b�N�X��
#define BULLET_HITBOX_HEIGHT	(40 * 0.3f)//�e�̃q�b�g�{�b�N�X�c
#define BULLET_WIDTH_PATTERN	(2)//���A�j���p�^�[����
#define BULLET_HEIGHT_PATTERN	(1)//�c�A�j���p�^�[����
#define BULLET_FRAME_MAX	(BULLET_WIDTH_PATTERN * BULLET_HEIGHT_PATTERN)//�t���[����
#define BULLET_FRAME_SPAN	(2)//�A�j���[�V�����̃X�p��
#define BULLET_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------
typedef enum
{
	BULLET_TYPE_NORMAL = 0,
	BULLET_TYPE_MISSILE,
}BULLET_TYPE;

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct BULLET {
	int bulletType;
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXVECTOR2	oldPos;
	D3DXVECTOR2 goalPos;
	D3DXVECTOR2	vel;	//���x�x�N�g��
	D3DXCOLOR color;	//���_�J���[
	bool use;			//�g�p���t���O
	D3DXVECTOR2 size;	//�T�C�Y
	float rot;
	float sp;
	D3DXVECTOR2 uv;
	int animePattern;
	int animeWidthPattern;
	int animeBasePattern;
	int animeSkipFrame;
	bool hetList[ENEMY_MAX];
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET* GetBullet();
void SetBullet(int type, float posX, float posY, float velX, float velY, float rot, float sp);
void DeleteBullet(int index);

