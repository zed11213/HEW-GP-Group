//===================================================
//�e(gun.h)
//Auhor:�n� �C	Date:2023.8.27
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define GUN_MAX			(1)//�L�����N�^�[�̐�
#define GUN_WIDTH		(DEFAULT_TILE_SIZE*0.5)//�摜����
#define GUN_HEIGHT		(DEFAULT_TILE_SIZE*0.5)//�摜�c����
#define GUN_WIDTH_PATTERN	(3)//���A�j���p�^�[����
#define GUN_HEIGHT_PATTERN	(1)//�c�A�j���p�^�[����
#define GUN_FRAME_MAX	((GUN_WIDTH_PATTERN * GUN_HEIGHT_PATTERN) -1)//�t���[����
#define GUN_FRAME_SPAN	(1)//�A�j���[�V�����̃X�p��
#define GUN_SHOT_DELAY	(1)
#define GUN_BULLET_OFFSET (30)

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------
typedef enum
{
	GUN_TYPE_INIT,
	GUN_TYPE_FULL_AUTO,
	GUN_TYPE_SEMI_AUTO,
	GUN_TYPE_CHARGE_FULL_AUTO,
}GUN_TYPE;

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct GUN {
	int type;
	int oldType;
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXCOLOR color;	//���_�J���[
	bool use;			//�g�p���t���O
	D3DXVECTOR2 size;	//�T�C�Y
	float rot;
	int firingDelay;
	int recoil;
	int controlleRangle;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeBasePattern;
	int animePattern;
	bool anime;
	int shotDelay;
	int shotCou;
	int charge;
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitGun(void);
void UninitGun(void);
void UpdateGun(void);
void DrawGun(void);

GUN* GetGun();
void ChangeGun(int type);