//===================================================
//選択項目(game_option.cpp)
//Auhor:渡邉 修	Date:2023.8.5
//===================================================
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "game_option.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
static int g_TexNoStart;
static int g_TexNoExit;
static int g_TexNoRetry;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
GAME_OPTION g_gameOption[GAME_OPTION_MAX];

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitGameOption(void)
{
	for (int i = 0; i < GAME_OPTION_MAX; i++)
	{
		g_gameOption[i].messagePattern = MESSAGE_NONE;
		g_gameOption[i].pos = D3DXVECTOR2(0, 0);
		g_gameOption[i].use = false;
		g_gameOption[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	g_TexNoStart = LoadTexture((char*)"data/TEXTURE/start.png");
	g_TexNoExit = LoadTexture((char*)"data/TEXTURE/exit.png");
	g_TexNoRetry = LoadTexture((char*)"data/TEXTURE/retry.png");

	//グローバル変数初期化
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / GAME_OPTION_WIDTH_PATTERN;
	g_VH = 1.0f / GAME_OPTION_HEIGHT_PATTERN;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateGameOption(void)
{
	switch (GetScene())//遷移後のシーンの初期化処理
	{
	case SCENE_TITLE:
		SetGameOption(MESSAGE_START, D3DXVECTOR2(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF + (SCREEN_HEIGHT_HALF * 0.5f)));
		SetGameOption(MESSAGE_EXIT, D3DXVECTOR2(SCREEN_WIDTH_HALF, 100 + SCREEN_HEIGHT_HALF + (SCREEN_HEIGHT_HALF * 0.5f)));
		break;

	case SCENE_RESULT:
		SetGameOption(MESSAGE_RETRY, D3DXVECTOR2(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF + (SCREEN_HEIGHT_HALF * 0.5f)));
		SetGameOption(MESSAGE_EXIT, D3DXVECTOR2(SCREEN_WIDTH_HALF, 100 + SCREEN_HEIGHT_HALF + (SCREEN_HEIGHT_HALF * 0.5f)));
		break;

	default:
		break;
	}

}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawGameOption(void)
{
	for (int i = 0; i < GAME_OPTION_MAX; i++)
	{
		if (g_gameOption[i].use)
		{
			switch (g_gameOption[i].messagePattern)
			{
			case MESSAGE_START:
				DrawSpriteColor(g_TexNoStart,
					g_gameOption[i].pos.x,
					g_gameOption[i].pos.y,
					GAME_OPTION_START_WIDTH, GAME_OPTION_START_HEIGHT,	//幅、高さ
					g_U, g_V,		//中心UV座標
					g_UW, g_VH,
					g_gameOption[i].color.r, g_gameOption[i].color.g, g_gameOption[i].color.b, g_gameOption[i].color.a
				);
				break;

			case MESSAGE_EXIT:
				DrawSpriteColor(g_TexNoExit,
					g_gameOption[i].pos.x,
					g_gameOption[i].pos.y,
					GAME_OPTION_EXIT_WIDTH, GAME_OPTION_EXIT_HEIGHT,	//幅、高さ
					g_U, g_V,		//中心UV座標
					g_UW, g_VH,
					g_gameOption[i].color.r, g_gameOption[i].color.g, g_gameOption[i].color.b, g_gameOption[i].color.a
				);
				break;

			case MESSAGE_RETRY:
				DrawSpriteColor(g_TexNoRetry,
					g_gameOption[i].pos.x,
					g_gameOption[i].pos.y,
					GAME_OPTION_RETRY_WIDTH, GAME_OPTION_RETRY_HEIGHT,	//幅、高さ
					g_U, g_V,		//中心UV座標
					g_UW, g_VH,
					g_gameOption[i].color.r, g_gameOption[i].color.g, g_gameOption[i].color.b, g_gameOption[i].color.a
				);
				break;

			default:
				break;
			}
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitGameOption(void)
{

}

//---------------------------------------------------
//指定したメッセージの若い番号のポジションを返す
//---------------------------------------------------
D3DXVECTOR2 GetGameOptionPos(MESSAGE_PATTERN MessagePattern)
{
	for (int i = 0; i < GAME_OPTION_MAX; i++)
	{
		if (g_gameOption[i].messagePattern == MessagePattern && g_gameOption[i].use)
		{
			return g_gameOption[i].pos;
		}
	}
	return D3DXVECTOR2(0.0f, 0.0f);
}

//---------------------------------------------------
//指定したメッセージの表示、非表示切り替え
//---------------------------------------------------
void UseGameOption(MESSAGE_PATTERN MessagePattern)
{
	for (int i = 0; i < GAME_OPTION_MAX; i++)
	{
		if (g_gameOption[i].messagePattern == MessagePattern)
		{
			if (g_gameOption[i].color.a == 1.0f)
			{
				g_gameOption[i].color.a = 0.0f;
			}
			else
			{
				g_gameOption[i].color.a = 1.0f;
			}
		}
	}
}

//---------------------------------------------------
//セット(メッセージパターン, ポジション)
//---------------------------------------------------
void SetGameOption(MESSAGE_PATTERN MessagePattern, D3DXVECTOR2 pos)
{
	for (int i = 0; i < GAME_OPTION_MAX; i++)
	{
		if (!g_gameOption[i].use)
		{
			g_gameOption[i].messagePattern = MessagePattern;
			g_gameOption[i].pos = pos;
			g_gameOption[i].use = true;
			break;
		}
	}
}



