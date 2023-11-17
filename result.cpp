//===================================================
//リザルト画面(result.cpp)
//Auhor:渡邉 修	Date:2023.8.8
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
//グローバル変数
//---------------------------------------------------
unsigned int g_ResultTexture;
static int g_TILEM;

//---------------------------------------------------
//初期化
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
//更新
//---------------------------------------------------
void UpdateResult()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//なんか適当な色をセット
		SetFadeTime(30.0f);//time:何フレームでフェード処理を完了したいか？
		SetFade(FADE_STATE_IN);
	}
	UpdateTile();
	UpdateGameOption();
	UpdateCursor();
	UpdateScore();
	
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawResult()
{
	DrawTile();
	DrawGameOption();
	DrawCursor();
	DrawScore();
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitResult()
{
	UninitTile();
	UninitGameOption();
	UninitCursor();
	UninitScore();
	StopSoundAll();
}
