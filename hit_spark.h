//===================================================
//�q�b�g�G�t�F�N�g(hit_spark.h)
//Auhor:�n� �C	Date:2023.9.3
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define HIT_SPARK_MAX			(100)//�L�����N�^�[�̐�
#define HIT_SPARK_WIDTH		(DEFAULT_TILE_SIZE)//�摜����
#define HIT_SPARK_HEIGHT	(DEFAULT_TILE_SIZE)//�摜�c����
#define HIT_SPARK_HITBOX_WIDTH		(DEFAULT_TILE_SIZE)//�q�b�g�G�t�F�N�g�̃q�b�g�{�b�N�X��
#define HIT_SPARK_HITBOX_HEIGHT		(DEFAULT_TILE_SIZE)//�q�b�g�G�t�F�N�g�̃q�b�g�{�b�N�X�c
#define HIT_SPARK_WIDTH_PATTERN	(5)//���A�j���p�^�[����
#define HIT_SPARK_HEIGHT_PATTERN	(1)//�c�A�j���p�^�[����
#define HIT_SPARK_FRAME_MAX	(HIT_SPARK_WIDTH_PATTERN * HIT_SPARK_HEIGHT_PATTERN)//�t���[����
#define HIT_SPARK_FRAME_SPAN	(5)//�A�j���[�V�����̃X�p��
#define HIT_SPARK_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define HIT_SPARK_SPEED		(8.0f)//�q�b�g�G�t�F�N�g�̈ړ����x

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct HIT_SPARK {
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXCOLOR color;	//���_�J���[
	bool use;			//�g�p���t���O
	D3DXVECTOR2 size;	//�T�C�Y
	float rot;
	D3DXVECTOR2 uv;
	int animePattern;
	int animeWidthPattern;
	int animeBasePattern;
	int animeSkipFrame;
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitHitSpark(void);
void UninitHitSpark(void);
void UpdateHitSpark(void);
void DrawHitSpark(void);

HIT_SPARK* GetHitSpark();
void SetHitSpark(float posX, float posY, float rot, float r = 0.0f, float g = 0.0f, float b = 0.0f);




