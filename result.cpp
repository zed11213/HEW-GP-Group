//===================================================
//���U���g���(result.cpp)
//Auhor:�n� �C	Date:2023.8.8
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "result.h"
#include "tile.h"
#include "game_option.h"
#include "cursor.h"
#include "score.h"
#include "fade.h"
#include "sound.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
unsigned int g_ResultTexture;
static int g_TILEM;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitResult()
{
	char tilem[] =
	{
		"data\\TILEM\\nc293887.wav"
	};
	g_TILEM = LoadSound(&tilem[0]);
	PlaySound(g_TILEM, 0);
	InitTile();
	InitGameOption();
	InitCursor();
	InitScore();

}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateResult()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//�Ȃ񂩓K���ȐF���Z�b�g
		SetFadeTime(30.0f);//time:���t���[���Ńt�F�[�h�������������������H
		SetFade(FADE_STATE_IN);
	}
	UpdateTile();
	UpdateGameOption();
	UpdateCursor();
	UpdateScore();
	
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawResult()
{
	DrawTile();
	DrawGameOption();
	DrawCursor();
	DrawScore();
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitResult()
{
	UninitTile();
	UninitGameOption();
	UninitCursor();
	UninitScore();
	StopSoundAll();
}
