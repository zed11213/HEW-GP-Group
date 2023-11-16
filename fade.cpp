//===================================================
//�t�F�[�h(fade.cpp)
//Auhor:�n� �C	Date:2023.7.5
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
static int	g_TexNo;
FADE_STATE	g_FadeState;
SCENE		g_FadeNextScene;
D3DXCOLOR	g_FadeColor;		//�t�F�[�h�F
float		g_FadeTime;			//�t�F�[�h�I���܂ł̎���

//---------------------------------------------------
//������
//---------------------------------------------------
void InitFade()
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	g_FadeState = FADE_STATE_NONE;
	g_FadeNextScene = SCENE_NONE;
	g_FadeColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�f�t�H���g��
	g_FadeTime = 1.0f / 60.0f;//60�t���[��(1�b)�Ńt�F�[�h�I��
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateFade()
{

	if (g_FadeState == FADE_STATE_OUT)
	{
		if (g_FadeColor.a >= 1.0f)//�t�F�[�h�A�E�g�I��
		{
			g_FadeColor.a = 1.0f;//�A���t�@�l�����Z�b�g
			g_FadeState = FADE_STATE_IN;//�t�F�[�h�C���ֈڂ�
			SetScene(g_FadeNextScene);
		}

		g_FadeColor.a += g_FadeTime;//�A���t�@�l�𑝂₷�i�s�������j

	}
	else if (g_FadeState == FADE_STATE_IN)
	{

		if (g_FadeColor.a <= 0.0f)//�t�F�[�h�C���I��
		{
			g_FadeColor.a = 0.0f;//�A���t�@�l�����Z�b�g
			g_FadeState = FADE_STATE_NONE;//�������Ȃ���Ԃֈڂ�
		}

		g_FadeColor.a -= g_FadeTime;//�A���t�@�l�����炷�i�������j
	}

}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawFade()
{
	if (g_FadeState == FADE_STATE_NONE)//�������Ȃ���Ԃ̂Ƃ��͕\���Ȃ�
		return;

	//��ʃT�C�Y�|����\��
	DrawSpriteColor(g_TexNo, 960.0f, 540.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		g_FadeColor.r, g_FadeColor.g, g_FadeColor.b, g_FadeColor.a);
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitFade()
{

}

//�t�F�[�h�A�E�g���ăV�[���؂�ւ�
void SceneTransition(SCENE NextScene)
{

	g_FadeNextScene = NextScene;

	g_FadeState = FADE_STATE_OUT;

}

void SceneFadeIn(SCENE nextScene)
{
	g_FadeColor.a = 1.0f;
	g_FadeState = FADE_STATE_IN;
	SetScene(nextScene);
}


FADE_STATE GetFadeState()
{
	return g_FadeState;
}

//�t�F�[�h�F��ݒ�
void SetFadeColor(float r, float g, float b)
{
	float alpha = g_FadeColor.a;
	g_FadeColor = D3DXCOLOR(r, g, b, alpha);
}


//�t�F�[�h�������N�G�X�g
void SetFade(FADE_STATE st)
{
	//�t�F�[�h�������H
	if (g_FadeState != FADE_STATE_NONE)
	{
		return;//�������Ȃ�
	}

	//�t���O���Z�b�g����
	switch (st)
	{
		case FADE_STATE_IN:
			g_FadeColor.a = 1.0f;//�A���t�@�l�����Z�b�g
			g_FadeState = FADE_STATE_IN;//�t���O���Z�b�g

		case FADE_STATE_OUT:
			g_FadeColor.a = 0.0f;//�A���t�@�l�����Z�b�g
			g_FadeState = FADE_STATE_OUT;//�t���O���Z�b�g

	}

}


//time:���t���[���Ńt�F�[�h�������������������H���Z�b�g
void SetFadeTime(float time)
{
	g_FadeTime = 1.0f / time;
}


