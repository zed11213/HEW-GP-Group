//===================================================
//フェード(fade.cpp)
//Auhor:渡邉 修	Date:2023.7.5
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
static int	g_TexNo;
FADE_STATE	g_FadeState;
SCENE		g_FadeNextScene;
D3DXCOLOR	g_FadeColor;		//フェード色
float		g_FadeTime;			//フェード終了までの時間

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitFade()
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	g_FadeState = FADE_STATE_NONE;
	g_FadeNextScene = SCENE_NONE;
	g_FadeColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//デフォルト白
	g_FadeTime = 1.0f / 60.0f;//60フレーム(1秒)でフェード終了
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateFade()
{

	if (g_FadeState == FADE_STATE_OUT)
	{
		if (g_FadeColor.a >= 1.0f)//フェードアウト終了
		{
			g_FadeColor.a = 1.0f;//アルファ値をリセット
			g_FadeState = FADE_STATE_IN;//フェードインへ移る
			SetScene(g_FadeNextScene);
		}

		g_FadeColor.a += g_FadeTime;//アルファ値を増やす（不透明化）

	}
	else if (g_FadeState == FADE_STATE_IN)
	{

		if (g_FadeColor.a <= 0.0f)//フェードイン終了
		{
			g_FadeColor.a = 0.0f;//アルファ値をリセット
			g_FadeState = FADE_STATE_NONE;//何もしない状態へ移る
		}

		g_FadeColor.a -= g_FadeTime;//アルファ値を減らす（透明化）
	}

}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawFade()
{
	if (g_FadeState == FADE_STATE_NONE)//何もしない状態のときは表示なし
		return;

	//画面サイズポリ後表示
	DrawSpriteColor(g_TexNo, 960.0f, 540.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		g_FadeColor.r, g_FadeColor.g, g_FadeColor.b, g_FadeColor.a);
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitFade()
{

}

//フェードアウトしてシーン切り替え
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

//フェード色を設定
void SetFadeColor(float r, float g, float b)
{
	float alpha = g_FadeColor.a;
	g_FadeColor = D3DXCOLOR(r, g, b, alpha);
}


//フェード処理リクエスト
void SetFade(FADE_STATE st)
{
	//フェード処理中？
	if (g_FadeState != FADE_STATE_NONE)
	{
		return;//何もしない
	}

	//フラグをセットする
	switch (st)
	{
		case FADE_STATE_IN:
			g_FadeColor.a = 1.0f;//アルファ値をリセット
			g_FadeState = FADE_STATE_IN;//フラグをセット

		case FADE_STATE_OUT:
			g_FadeColor.a = 0.0f;//アルファ値をリセット
			g_FadeState = FADE_STATE_OUT;//フラグをセット

	}

}


//time:何フレームでフェード処理を完了したいか？をセット
void SetFadeTime(float time)
{
	g_FadeTime = 1.0f / time;
}


