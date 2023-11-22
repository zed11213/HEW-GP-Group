//===================================================
//����(dead.h)
//Auhor:�n� �C	Date:2023.8.1
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define DEAD_WIDTH		(27 * 4)//�摜����(���摜27�s�N�Z���̉摜��4�{�ɂ��Ďg�p)
#define DEAD_HEIGHT		(27 * 4)//�摜�c����
#define DEAD_WIDTH_PATTERN	(4)//���A�j���p�^�[����
#define DEAD_HEIGHT_PATTERN	(1)//�c�A�j���p�^�[����
#define DEAD_MAX			(1)//�L�����N�^�[�̐�
#define DEAD_FRAME_MAX	((DEAD_WIDTH_PATTERN * DEAD_HEIGHT_PATTERN) -1)//�t���[����
#define DEAD_FRAME_SPAN	(5)//�A�j���[�V�����̃X�p��
#define DEAD_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define DEAD_SPEED		(1.0f)//���̂̈ړ����x
#define DEAD_WIDTH_MAX	(DEAD_WIDTH * 4)
#define DEAD_HEIGHT_MAX	(DEAD_HEIGHT * 4)
#define DEAD_BASE_ZOOM_RATE	(0.01f)	//��{�̎�O�ɗ��鑬��
#define DEAD_ADD_ZOOM_RATE	(8.5f)	//��O�ɗ������̑����̑�����
#define DEAD_DIS_SPEED_RATE	(10)	//�����ɂ��X�s�[�h�̑���

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct DEAD {
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2		oldPos;	//�O�t���[���̈ʒu�x�N�g��
	D3DXVECTOR2		vel;	//���x�x�N�g��
	D3DXCOLOR		color;	//���_�J���[
	int				dir;	//����
	bool			use;	//�g�p���t���O
	D3DXVECTOR2		size;	//�T�C�Y
	float			dis;	//���ߋ���
	int				BufferIndex;//�����O�o�b�t�@�̎Q�ƃC���f�N�X
	D3DXVECTOR2		initSize;	//�����T�C�Y
	float			disRate;	//0(�ŉ�)�`1(�őO)
	float			speed;
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitDead(void);
void UninitDead(void);
void UpdateDead(void);
void DrawDead(void);

DEAD* GetDead();
void SetDead(D3DXVECTOR2 pos);
