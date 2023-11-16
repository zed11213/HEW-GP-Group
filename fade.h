//===================================================
//�t�F�[�h(fade.h)
//Auhor:�n� �C	Date:2023.8.11
//===================================================
#pragma once
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------
typedef enum
{
	FADE_STATE_NONE = 0,
	FADE_STATE_IN,
	FADE_STATE_OUT
}FADE_STATE;

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
typedef struct 
{


}Fade;

//---------------------------------------------------
//�v���g�^�C�v�錾
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