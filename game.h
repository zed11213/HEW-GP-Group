//===================================================
//�Q�[�����(game.h)
//Auhor:�n� �C	Date:2023.8.4
//===================================================
#pragma once
#ifndef GAME_H_
#define GAME_H_

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------
typedef enum
{
	GAME_STATE_IDLE_1,
	GAME_STATE_READY,
	GAME_STATE_IDLE_2,
	GAME_STATE_START,
	GAME_STATE_PLAY,
	GAME_STATE_OVER,
	GAME_STATE_CLEAR,
}GAME_STATE;

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitGame();
void UninitGame();
void UpdateGame();
void DrawGame();

#endif