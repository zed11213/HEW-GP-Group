//===================================================
//�^�C�g�����S(title_logo.h)
//Auhor:�n� �C	Date:2023.8.5
//===================================================
#pragma once

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define TITLE_LOGO_WIDTH		(220*8)//�摜����
#define TITLE_LOGO_HEIGHT		(48*8)//�摜�c����
#define TITLE_LOGO_WIDTH_PATTERN	(2)//���A�j���p�^�[����
#define TITLE_LOGO_HEIGHT_PATTERN	(5)//�c�A�j���p�^�[����
#define TITLE_LOGO_MAX			(1)//�L�����N�^�[�̐�
#define TITLE_LOGO_FRAME_MAX	((TITLE_LOGO_WIDTH_PATTERN * TITLE_LOGO_HEIGHT_PATTERN) -1)//�t���[����
#define TITLE_LOGO_FRAME_SPAN	(8)//�A�j���[�V�����̃X�p��
#define TITLE_LOGO_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitTitleLogo(void);
void UpdateTitleLogo(void);
void DrawTitleLogo(void);
void UninitTitleLogo(void);
