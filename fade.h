//===================================================
//フェード(fade.h)
//Auhor:渡邉 修	Date:2023.8.11
//===================================================
#pragma once
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------

//---------------------------------------------------
//列挙体宣言
//---------------------------------------------------
typedef enum
{
	FADE_STATE_NONE = 0,
	FADE_STATE_IN,
	FADE_STATE_OUT
}FADE_STATE;

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
typedef struct 
{


}Fade;

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();
void SetFade(FADE_STATE st);
void SetFadeTime(float time);
void SceneTransition(SCENE NextScene);
void SceneFadeIn(SCENE nextScene);
void SetFadeColor(float r, float g, float b);
FADE_STATE GetFadeState();

#endif