//===================================================
//���q(particle.h)
//Auhor:�n� �C	Date:2023.9.9
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define PARTICLE_MAX			(1000)//�L�����N�^�[�̐�
#define PARTICLE_WIDTH		(40)//�摜����
#define PARTICLE_HEIGHT		(40)//�摜�c����
#define PARTICLE_HITBOX_WIDTH		(DEFAULT_TILE_SIZE * 0.3f)//���q�̃q�b�g�{�b�N�X��
#define PARTICLE_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE * 0.3f)//���q�̃q�b�g�{�b�N�X�c
#define PARTICLE_WIDTH_PATTERN	(1)//���A�j���p�^�[����
#define PARTICLE_HEIGHT_PATTERN	(1)//�c�A�j���p�^�[����
#define PARTICLE_FRAME_MAX	(PARTICLE_WIDTH_PATTERN * PARTICLE_HEIGHT_PATTERN)//�t���[����
#define PARTICLE_FRAME_SPAN	(2)//�A�j���[�V�����̃X�p��
#define PARTICLE_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct PARTICLE {
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
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
	float releaseX;
	float releaseY;
	float grv;
	D3DXVECTOR2 scale;
	D3DXCOLOR color255;
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);

PARTICLE* GetParticle();
void SetParticle(float posX, float posY, int num, float r = 172, float g = 50, float b = 50);
void SetParticleRelease(int index, float power, float radian);

