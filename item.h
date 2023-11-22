//===================================================
//�A�C�e��(item.h)
//Auhor:�n� �C	Date:2023.9.15
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"
#include "gun.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define ITEM_MAX			(100)//�L�����N�^�[�̐�
#define ITEM_WIDTH		(DEFAULT_TILE_SIZE)//�摜����
#define ITEM_HEIGHT		(DEFAULT_TILE_SIZE)//�摜�c����
#define ITEM_HITBOX_WIDTH	(DEFAULT_TILE_SIZE * 0.5f)//�A�C�e���̃q�b�g�{�b�N�X��
#define ITEM_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE)//�A�C�e���̃q�b�g�{�b�N�X�c
#define ITEM_WIDTH_PATTERN	(14)//���A�j���p�^�[����
#define ITEM_HEIGHT_PATTERN	(6)//�c�A�j���p�^�[����
#define ITEM_FRAME_MAX	((ITEM_WIDTH_PATTERN * ITEM_HEIGHT_PATTERN) -1)//�t���[����
#define ITEM_FRAME_SPAN	(5)//�A�j���[�V�����̃X�p��
#define ITEM_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------
typedef enum
{
	ITEM_STATE_IDLE,
	ITEM_STATE_WALK,
	ITEM_STATE_RISE,
	ITEM_STATE_FALL,
	ITEM_STATE_DEAD
}ITEM_STATE;

typedef enum
{
	ITEM_TYPE_COIN,
	ITEM_TYPE_TMATO,
	ITEM_TYPE_TREASURE_BOX,
	ITEM_TYPE_WEAPON,
}ITEM_TYPE;

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct ITEM {
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

	ITEM_STATE state;
	ITEM_STATE oldState;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeFrameMax;
	int animeBasePattern;
	int animePattern;
	int animeSkipFrame;
	bool anime;

	bool leftMove;
	bool rightMove;
	bool jump;
	int move;
	int stateCou;
	bool reverse;

	ITEM_TYPE type;
	bool animeLoop;
	GUN_TYPE gunType;
	bool fadeOut;
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

ITEM* GetItem();
void SetItemGunKick(int index, float power);
void SetItemKnockBack(int index, float power);
int SetItem(float posX, float posY, ITEM_TYPE type);
void SetWeapon(float posX, float posY, GUN_TYPE type);
void ItemAnime(int index);
void ItemFadeOut(int index);
void ItemAllDelete();
