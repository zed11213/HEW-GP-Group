//===================================================
//ヒットエフェクト(hit_spark.cpp)
//Auhor:渡邉 修	Date:2023.9.3
//===================================================
#include "hit_spark.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "dead.h"
#include "main.h"
#include "tile.h"
#include "camera.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_TexNo;
static int g_SE_crushed_tomato;
static int g_SE_move;
static int g_SE_drop;
static float g_UW;
static float g_VH;
static float g_AnimeSkipFrameFloat;
static HIT_SPARK g_HitSpark[HIT_SPARK_MAX];
static TILE_DATA* p_Tile;
static CAMERA* p_Camera;
static bool g_Reverse;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitHitSpark(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/HitSpark.png");
	//効果音作成
	char se1[] =
	{
		"data\\SE\\crushed_tomato.wav"
	};
	g_SE_crushed_tomato = LoadSound(&se1[0]);

	char se2[] =
	{
		"data\\SE\\move.wav"
	};
	g_SE_move = LoadSound(&se2[0]);

	char se3[] =
	{
		"data\\SE\\drop.wav"
	};
	g_SE_drop = LoadSound(&se3[0]);

	for (int i = 0; i < HIT_SPARK_MAX; i++)
	{
		g_HitSpark[i].use = false;
		g_HitSpark[i].pos.x = SCREEN_WIDTH / 2;
		g_HitSpark[i].pos.y = SCREEN_HEIGHT / 4;
		g_HitSpark[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_HitSpark[i].size = D3DXVECTOR2(HIT_SPARK_WIDTH, HIT_SPARK_HEIGHT);
		g_HitSpark[i].rot = 0.0f;
		g_HitSpark[i].uv = D3DXVECTOR2(0, 0);
		g_HitSpark[i].animePattern = 0;
		g_HitSpark[i].animeWidthPattern = HIT_SPARK_WIDTH_PATTERN;
		g_HitSpark[i].animeBasePattern = 1;
		g_HitSpark[i].animeSkipFrame = 0;
	}

	//グローバル変数初期化
	g_UW = 1.0f / HIT_SPARK_WIDTH_PATTERN;
	g_VH = 1.0f / HIT_SPARK_HEIGHT_PATTERN;
	g_Reverse = false;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateHitSpark(void)
{
	for (int i = 0; i < HIT_SPARK_MAX; i++)
	{
		if (g_HitSpark[i].use)
		{
			if (g_HitSpark[i].animeWidthPattern == 1)g_HitSpark[i].use = false;
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawHitSpark(void)
{
	for (int i = 0; i < HIT_SPARK_MAX; i++)
	{
		if (g_HitSpark[i].use)
		{
			//アニメーション
			g_HitSpark[i].uv = SetAnimation(g_HitSpark[i].animeBasePattern, g_HitSpark[i].animePattern, HIT_SPARK_WIDTH_PATTERN, HIT_SPARK_HEIGHT_PATTERN, g_HitSpark[i].animeWidthPattern, g_Reverse);

			g_HitSpark[i].animeSkipFrame = Counter(g_HitSpark[i].animeSkipFrame, HIT_SPARK_FRAME_SPAN);

			if (g_HitSpark[i].animeSkipFrame == 0)
			{
				g_HitSpark[i].animePattern = Counter(g_HitSpark[i].animePattern, HIT_SPARK_FRAME_MAX);
				if (g_HitSpark[i].animePattern == 0)g_HitSpark[i].animeWidthPattern = 1;//アニメをループさせない
			}


			DrawSpriteColorRotateCamera(g_TexNo,
				g_HitSpark[i].pos.x,
				g_HitSpark[i].pos.y,
				g_HitSpark[i].size.x, g_HitSpark[i].size.y,	//幅、高さ
				g_HitSpark[i].uv.x, g_HitSpark[i].uv.y,		//中心UV座標
				g_UW, g_VH,		//テクスチャ幅、高さ
				g_HitSpark[i].color.r, g_HitSpark[i].color.g, g_HitSpark[i].color.b, g_HitSpark[i].color.a,
				g_HitSpark[i].rot
			);
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitHitSpark(void)
{

}

//---------------------------------------------------
// ヒットエフェクト取得処理
//---------------------------------------------------
HIT_SPARK* GetHitSpark()
{
	return &g_HitSpark[0];
}

//---------------------------------------------------
// ヒットエフェクト配置処理
//---------------------------------------------------
void SetHitSpark(float posX, float posY, float rot, float r, float g, float b)
{
	for (int i = 0; i < HIT_SPARK_MAX; i++)
	{
		if (!g_HitSpark[i].use)
		{
			g_HitSpark[i].pos = D3DXVECTOR2(posX, posY);
			g_HitSpark[i].rot = rot;
			g_HitSpark[i].uv = D3DXVECTOR2(0, 0);
			g_HitSpark[i].animePattern = 0;
			g_HitSpark[i].animeWidthPattern = HIT_SPARK_WIDTH_PATTERN;
			g_HitSpark[i].animeBasePattern = 0;
			g_HitSpark[i].animeSkipFrame = 0;
			g_HitSpark[i].use = true;
			float R = r / 255;
			float G = g / 255;
			float B = b / 255;
			g_HitSpark[i].color = D3DXCOLOR(R, G, B, 1.0f);
			break;
		}
	}
}
