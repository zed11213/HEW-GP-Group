//===================================================
//�^�C�g���g�}�g(title_tomato.h)
//Auhor:�n� �C	Date:2023.8.5
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define TITLE_TOMATO_WIDTH		(600*1.5)//�摜����
#define TITLE_TOMATO_HEIGHT		(600*1.5)//�摜�c����
#define TITLE_TOMATO_WIDTH_PATTERN	(11)//���A�j���p�^�[����
#define TITLE_TOMATO_HEIGHT_PATTERN	(1)//�c�A�j���p�^�[����
#define TITLE_TOMATO_MAX			(1)//�L�����N�^�[�̐�
#define TITLE_TOMATO_FRAME_MAX	((TITLE_TOMATO_WIDTH_PATTERN * TITLE_TOMATO_HEIGHT_PATTERN) -1)//�t���[����
#define TITLE_TOMATO_FRAME_SPAN	(15)//�A�j���[�V�����̃X�p��
#define TITLE_TOMATO_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitTitleTomato(void);
void UpdateTitleTomato(void);
void DrawTitleTomato(void);
void UninitTitleTomato(void);
