//===================================================
//�G�l�~�[(enemy.h)
//Auhor:�n� �C	Date:2023.9.4
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define ENEMY_MAX			(1000)//�L�����N�^�[�̐�
#define ENEMY_WIDTH		(DEFAULT_TILE_SIZE)//�摜����
#define ENEMY_HEIGHT		(DEFAULT_TILE_SIZE)//�摜�c����
#define ENEMY_HITBOX_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//�G�l�~�[�̃q�b�g�{�b�N�X��
#define ENEMY_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE)//�G�l�~�[�̃q�b�g�{�b�N�X�c
#define ENEMY_WIDTH_PATTERN	(4)//���A�j���p�^�[����
#define ENEMY_HEIGHT_PATTERN	(5)//�c�A�j���p�^�[����
#define ENEMY_FRAME_MAX	((ENEMY_WIDTH_PATTERN * ENEMY_HEIGHT_PATTERN) -1)//�t���[����
#define ENEMY_FRAME_SPAN	(8)//�A�j���[�V�����̃X�p��
#define ENEMY_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define ENEMY_SPEED		(8.0f)//�G�l�~�[�̈ړ����x
#define ENEMY_UNBEATABLE_TEME (20)//���G����

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------
typedef enum
{
	ENEMY_STATE_IDLE,
	ENEMY_STATE_WALK,
	ENEMY_STATE_RISE,
	ENEMY_STATE_FALL,
	ENEMY_STATE_DEAD
}ENEMY_STATE;

typedef enum
{
	ENEMY_TYPE_1,
	ENEMY_TYPE_2,
	ENEMY_TYPE_3,
}ENEMY_TYPE;

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct ENEMY {
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXVECTOR2	vel;	//���x�x�N�g��
	D3DXCOLOR color;	//���_�J���[
	bool use;			//�g�p���t���O
	D3DXVECTOR2 size;	//�T�C�Y

	float hsp;
	float vsp;
	float grv;
	float walksp;
	float controller;
	bool hascontrol;
	float canjump;
	float knockBackX;
	float knockBackY;
	bool ground;
	bool oldGround;

	ENEMY_STATE state;
	ENEMY_STATE oldState;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeFrameMax;
	int animeBasePattern;
	int animePattern;
	int animeSkipFrame;

	bool leftMove;
	bool rightMove;
	bool jump;
	int move;
	int stateCou;
	bool reverse;

	int hp;
	int oldHp;
	bool unbeatable;
	int unbeatableTime;
	int unbeatableCou;

	int score;
	ENEMY_TYPE type;
	int textureNo;
	int jumpPower;
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY* GetEnemy();
void SetEnemyGunKick(int index, float power, float radian);
void SetEnemyKnockBack(int index, float power, float radian);
void SetEnemy(float posX, float posY, ENEMY_TYPE type);
void EnemyAllDelete();
void EnemyHpDown(int index, int damage);