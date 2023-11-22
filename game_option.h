//===================================================
//�I������(game_option.h)
//Auhor:�n� �C	Date:2023.8.5
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define GAME_OPTION_START_WIDTH		(45*8-1)//�摜����(-1�Ŏ���ɏo�鍕�����������Ă܂�)
#define GAME_OPTION_START_HEIGHT	(10*8-1)//�摜�c����
#define GAME_OPTION_EXIT_WIDTH		(37*8-1)//�摜����
#define GAME_OPTION_EXIT_HEIGHT		(10*8-1)//�摜�c����
#define GAME_OPTION_RETRY_WIDTH		(45*8-1)//�摜����
#define GAME_OPTION_RETRY_HEIGHT	(10*8-1)//�摜�c����
#define GAME_OPTION_WIDTH_PATTERN	(1)//���A�j���p�^�[����
#define GAME_OPTION_HEIGHT_PATTERN	(1)//�c�A�j���p�^�[����
#define GAME_OPTION_MAX			(30)//�L�����N�^�[�̐�
#define GAME_OPTION_FRAME_MAX	((GAME_OPTION_WIDTH_PATTERN * GAME_OPTION_HEIGHT_PATTERN) -1)//�t���[����
#define GAME_OPTION_FRAME_SPAN	(15)//�A�j���[�V�����̃X�p��
#define GAME_OPTION_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------
typedef enum
{
	MESSAGE_NONE,
	MESSAGE_START,
	MESSAGE_EXIT,
	MESSAGE_RETRY,
}MESSAGE_PATTERN;

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct GAME_OPTION {
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	bool			use;	//�g�p���t���O
	MESSAGE_PATTERN		messagePattern;
	D3DXCOLOR		color;	//���_�J���[
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitGameOption(void);
void UpdateGameOption(void);
void DrawGameOption(void);
void UninitGameOption(void);

D3DXVECTOR2 GetGameOptionPos(MESSAGE_PATTERN MessagePattern);
void UseGameOption(MESSAGE_PATTERN MessagePattern);
void SetGameOption(MESSAGE_PATTERN MessagePattern, D3DXVECTOR2 pos);