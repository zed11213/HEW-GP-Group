//===================================================
//�J�[�\��(cursor.h)
//Auhor:�n� �C	Date:2023.8.5
//===================================================
#pragma once
#include "main.h"
#include "game_option.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define CURSOR_WIDTH		(32*5)//�摜����
#define CURSOR_HEIGHT		(32*5)//�摜�c����
#define CURSOR_WIDTH_PATTERN	(1)//���A�j���p�^�[����
#define CURSOR_HEIGHT_PATTERN	(1)//�c�A�j���p�^�[����
#define CURSOR_MAX			(1)//�L�����N�^�[�̐�
#define CURSOR_FRAME_MAX	((CURSOR_WIDTH_PATTERN * CURSOR_HEIGHT_PATTERN) -1)//�t���[����
#define CURSOR_FRAME_SPAN	(15)//�A�j���[�V�����̃X�p��
#define CURSOR_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define CURSOR_SPACE	(80)//���E�̃J�[�\���̕�

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------
typedef enum
{
	TITLE_START,
	TITLE_EXIT,
}TITLE_CURSOR;

typedef enum
{
	RESULT_RETRY,
	RESULT_EXIT,
}RESULT_CURSOR;

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitCursor(void);
void UpdateCursor(void);
void DrawCursor(void);
void UninitCursor(void);
void SelectFlash(MESSAGE_PATTERN MessagePattern, SCENE Scene);