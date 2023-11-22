//===================================================
//�w�i(back_ground.h)
//Auhor:�n� �C	Date:2023.9.3
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define BACK_GROUND_MAX			(7)//�L�����N�^�[�̐�
#define BACK_GROUND_COPY_MAX	(5)//�w�i����ׂ鐔
#define BACK_GROUND_WIDTH		(SCREEN_WIDTH * 1)//�摜����
#define BACK_GROUND_HEIGHT		(SCREEN_HEIGHT)//�摜�c����
#define BACK_GROUND_WIDTH_PATTERN	(1)//���A�j���p�^�[����
#define BACK_GROUND_HEIGHT_PATTERN	(1)//�c�A�j���p�^�[����
#define BACK_GROUND_FRAME_MAX	(BACK_GROUND_WIDTH_PATTERN * BACK_GROUND_HEIGHT_PATTERN)//�t���[����
#define BACK_GROUND_FRAME_SPAN	(5)//�A�j���[�V�����̃X�p��
#define BACK_GROUND_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define BACK_GROUND_SPEED		(8.0f)//�w�i�̈ړ����x

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct BACK_GROUND {
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXVECTOR2	vel;	//���x�x�N�g��
	D3DXCOLOR color;	//���_�J���[
	bool use;			//�g�p���t���O
	D3DXVECTOR2 size;	//�T�C�Y
	float rot;
	D3DXVECTOR2 uv;
	int animePattern;
	int animeWidthPattern;
	int animeBasePattern;
	int animeSkipFrame;
	int texNo;
	float moveSp;
	float moveCou;
	bool autoScroll;
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitBackGround(void);
void UninitBackGround(void);
void UpdateBackGround(void);
void DrawBackGround(void);

BACK_GROUND* GetBackGround();
void SetBackGround(int texNo, int layer, float moveSp = 0.0f, bool autoScroll = false);


