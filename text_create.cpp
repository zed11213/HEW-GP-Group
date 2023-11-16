//===================================================
//テキスト(text_create.cpp)
//Auhor:渡邉 修	Date:2023.9.9
//===================================================
#include <fstream>
#include <iostream>
#include "main.h"
#include "text_create.h"
#include "sprite.h"
#include "texture.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
static TEXT_CREATE g_TextCreate[TEXT_CREATE_MAX];
static int g_TexNo;
static float g_UW;
static float g_VH;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitTextCreate()
{
	//テクスチャ作成
	g_TexNo = LoadTexture((char*)"data/TEXTURE/font001.png");

	for (int i = 0; i < TEXT_CREATE_MAX; i++)
	{
		g_TextCreate[i].blankSize = 0;
		g_TextCreate[i].color = D3DXCOLOR(0, 0, 0, 0);
		g_TextCreate[i].pos = D3DXVECTOR2(0, 0);
		g_TextCreate[i].scale = 0;
		g_TextCreate[i].text = "NULL";
		g_TextCreate[i].use = false;
		g_TextCreate[i].fadeOutSpeed = 0.0f;
		g_TextCreate[i].fadeInSpeed = 0.0f;
		g_TextCreate[i].displayTime = 0;
		g_TextCreate[i].displayTimeCou = 0;
		g_TextCreate[i].state = TEXT_CREATE_DISPLAY;
	}

	g_UW = 1.0f / TEXT_CREATE_WIDTH_PATTERN;
	g_VH = 1.0f / TEXT_CREATE_HEIGHT_PATTERN;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateTextCreate()
{
	for (int i = 0; i < TEXT_CREATE_MAX; i++)
	{
		if (!g_TextCreate[i].use)continue;

		if (g_TextCreate[i].state == TEXT_CREATE_FADE_IN)
		{
			
			g_TextCreate[i].color.a += g_TextCreate[i].fadeInSpeed;
			if (g_TextCreate[i].color.a >= 1.0f)g_TextCreate[i].state = TEXT_CREATE_DISPLAY;
		}
		else if (g_TextCreate[i].state == TEXT_CREATE_DISPLAY)
		{
			g_TextCreate[i].displayTimeCou = Counter(g_TextCreate[i].displayTimeCou, g_TextCreate[i].displayTime);
			if (g_TextCreate[i].displayTimeCou == 0)g_TextCreate[i].state = TEXT_CREATE_FADE_OUT;
		}
		else if (g_TextCreate[i].state == TEXT_CREATE_FADE_OUT)
		{
			g_TextCreate[i].color.a -= g_TextCreate[i].fadeOutSpeed;
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawTextCreate()
{
	for (int i = 0; i < TEXT_CREATE_MAX; i++)
	{
		if (!g_TextCreate[i].use)continue;
		//文字数取得
		int length = g_TextCreate[i].text.length();
		int n = 0;
		float textBoxSizeX = ((TEXT_CREATE_WIDTH * length) + (g_TextCreate[i].blankSize * (length - 1))) * g_TextCreate[i].scale;
		float tx = 0;
		float ty = 0;
		float sx = 0;
		float sy = 0;

		for (int j = 0; j < length; j++)
		{
			char ch = g_TextCreate[i].text[j];

			for (int k = 0; k < 26; k++)
			{
				if (ch >= 'A' && ch <= 'Z')
				{
					if (ch == 'A' + k)
					{
						n = k;
						break;
					}
				}
				else if (ch >= '0' && ch <= '9')
				{
					if (ch == '0' + k)
					{
						n = k + 26;//アルファベット分プラス

						break;
					}
				}
				else if (ch == ' ')
				{
					n = 36;
					break;
				}
			}

			tx = 1.0f / TEXT_CREATE_WIDTH_PATTERN * (n % TEXT_CREATE_WIDTH_PATTERN);
			ty = 1.0f / TEXT_CREATE_HEIGHT_PATTERN * (n / TEXT_CREATE_WIDTH_PATTERN);

			sx = g_TextCreate[i].pos.x - (textBoxSizeX * 0.5f - (TEXT_CREATE_WIDTH * 0.5f * g_TextCreate[i].scale)) + TEXT_CREATE_WIDTH * j * g_TextCreate[i].scale;

			sx += g_TextCreate[i].blankSize * j * g_TextCreate[i].scale; //文字間
			sy = g_TextCreate[i].pos.y;

			DrawSpriteColorRotateScale(g_TexNo, sx, sy, TEXT_CREATE_WIDTH, TEXT_CREATE_HEIGHT,
				0.0f, 0.0f,
				tx, ty, g_UW, g_VH,
				g_TextCreate[i].color.r, g_TextCreate[i].color.g, g_TextCreate[i].color.b, g_TextCreate[i].color.a,
				0.0f,
				g_TextCreate[i].scale, g_TextCreate[i].scale);
		}

		if (g_TextCreate[i].color.a < 0.0f || g_TextCreate[i].displayTime == 0)
		{
			g_TextCreate[i].use = false;
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitTextCreate()
{

}

//---------------------------------------------------
//テキスト表示
//---------------------------------------------------
void SetDrawTextCreate(
	std::string text, float posX, float posY, float blankSize, float scale,
	int displayTime, float fadeInSpeed, float fadeOutSpeed,
	float r, float g, float b
)
{
	for (int i = 0; i < TEXT_CREATE_MAX; i++)
	{
		if (g_TextCreate[i].use)continue;
		g_TextCreate[i].text = text;
		g_TextCreate[i].pos = D3DXVECTOR2(posX, posY);
		g_TextCreate[i].blankSize = blankSize;
		g_TextCreate[i].scale = scale;
		g_TextCreate[i].displayTime = displayTime;
		g_TextCreate[i].displayTimeCou = 0;
		g_TextCreate[i].fadeInSpeed = fadeInSpeed;
		g_TextCreate[i].fadeOutSpeed = fadeOutSpeed;
		g_TextCreate[i].state = TEXT_CREATE_DISPLAY;
		float R = r / 255;
		float G = g / 255;
		float B = b / 255;
		float A = 1.0f;
		if (g_TextCreate[i].fadeInSpeed != 0.0f)
		{
			A = 0.0f;
			g_TextCreate[i].state = TEXT_CREATE_FADE_IN;
		}

		g_TextCreate[i].color = D3DXCOLOR(R, G, B, A);

		g_TextCreate[i].use = true;
		break;
	}
}

//---------------------------------------------------
//テキストを取得
//---------------------------------------------------
TEXT_CREATE GetTextCreate()
{
	return *g_TextCreate;
}
