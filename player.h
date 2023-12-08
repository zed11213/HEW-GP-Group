//===================================================
//�v���C���[(player.h)
//Auhor:�n� �C	Date:2023.8.25
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define PLAYER_MAX			(1)//�L�����N�^�[�̐�
#define PLAYER_WIDTH		(DEFAULT_TILE_SIZE)//�摜����
#define PLAYER_HEIGHT		(DEFAULT_TILE_SIZE)//�摜�c����
#define PLAYER_HITBOX_WIDTH		(PLAYER_WIDTH * 0.5f)//�v���C���[�̃q�b�g�{�b�N�X��
#define PLAYER_HITBOX_HEIGHT	(PLAYER_HEIGHT)//�v���C���[�̃q�b�g�{�b�N�X�c
#define PLAYER_WIDTH_PATTERN	(17)//���A�j���p�^�[����
#define PLAYER_HEIGHT_PATTERN	(4)//�c�A�j���p�^�[����
#define PLAYER_FRAME_MAX	((PLAYER_WIDTH_PATTERN * PLAYER_HEIGHT_PATTERN) -1)//�t���[����
#define PLAYER_FRAME_SPAN	(2)//�A�j���[�V�����̃X�p��
#define PLAYER_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define PLAYER_SPEED		(8.0f)//�v���C���[�̈ړ����x
#define PLAYER_INIT_HP		(3)//�����̗�
#define PLAYER_UNBEATABLE_TEME (180)//���G����

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------
typedef enum
{
	STATE_IDLE,
	STATE_WALK,
	STATE_RISE,
	STATE_FALL
}PLAYER_STATE;

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct PLAYER {
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXVECTOR2	oldPos;	//�ʒu�x�N�g��
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

	PLAYER_STATE state; 
	PLAYER_STATE oldState;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeFrameMax;

	float hp;
	float oldHp;
	bool unbeatable;
	int unbeatableCou;
	int unbeatableTime;

	int score;
	D3DXVECTOR2 notLoopPos;
	int loopTrigger;
	int coin;

	int gun;
	float maxHp;
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER* GetPlayer();

void SetPlayerGunKick(float power, float radian);
void SetPlayerKnockBack(float power, float radian);
void SetPlayer(float posX, float posY);
void SetPlayerScore(int add);
