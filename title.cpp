//===================================================
//タイトル画面(title.cpp)
//Auhor:渡邉 修	Date:2023.8.4
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "title.h"
#include "title_logo.h"
#include "tile.h"
#include "title_tomato.h"
#include "game_option.h"
#include "cursor.h"
#include "fade.h"
#include "sound.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
unsigned int g_TitleTexture;
static int g_TILEM;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitTitle()
{
	char tilem[] =
	{
		"data\\TILEM\\nc309629.wav"
	};
	g_TILEM = LoadSound(&tilem[0]);
	PlaySound(g_TILEM, -1);
	InitTile();
	InitTitleTomato();
	InitTitleLogo();
	InitCursor();
	InitGameOption();
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateTitle()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//なんか適当な色をセット
		SetFadeTime(30.0f);//time:何フレームでフェード処理を完了したいか？
		SetFade(FADE_STATE_IN);
	}
	UpdateTile();
	UpdateTitleTomato();
	UpdateTitleLogo();
	UpdateCursor();
	UpdateGameOption();
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawTitle()
{
	DrawTile();
	DrawTitleTomato();
	DrawTitleLogo();
	DrawCursor();
	DrawGameOption();
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitTitle()
{
	UninitTile();
	UninitTitleTomato();
	UninitTitleLogo();
	UninitCursor();
	UninitGameOption();
	StopSoundAll();
}
