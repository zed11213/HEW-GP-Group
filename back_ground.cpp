//===================================================
//背景(back_ground.cpp)
//Auhor:渡邉 修	Date:2023.9.3
//===================================================
#include "back_ground.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "dead.h"
#include "main.h"
#include "tile.h"
#include "camera.h"
#include "tile.h"
#include "hit_spark.h"
#include "player.h"
#include <time.h>

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_Tex0_sky;
static int g_Tex1_clouds1;
static int g_Tex2_clouds2;
static int g_Tex3_clouds3;
static int g_Tex4_mapGb;
static int g_Tex5_fg_bush;
static int g_Tex6_fg;
static int g_Tex7_tree;
static int g_Tex8_lightFilter;
static float g_UW;
static float g_VH;
static float g_AnimeSkipFrameFloat;
static BACK_GROUND g_BackGround[BACK_GROUND_MAX][BACK_GROUND_COPY_MAX];
static TILE_DATA* p_Tile;
static CAMERA* p_Camera;
static PLAYER* p_Player;
static bool g_Reverse;

static D3DXCOLOR g_BackgroundColor;
static float transitionDuration;
static float currentTime;
static float deltaTime;
static float timeCount;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitBackGround(void)
{
	g_Tex0_sky = LoadTexture((char*)"data/TEXTURE/0_sky.png");
	g_Tex1_clouds1 = LoadTexture((char*)"data/TEXTURE/1_clouds1.png");
	g_Tex2_clouds2 = LoadTexture((char*)"data/TEXTURE/2_clouds2.png");
	g_Tex3_clouds3 = LoadTexture((char*)"data/TEXTURE/3_clouds3.png");
	g_Tex4_mapGb = LoadTexture((char*)"data/TEXTURE/mapBg.png");
	g_Tex7_tree = LoadTexture((char*)"data/TEXTURE/Tree.png");
	g_Tex8_lightFilter = LoadTexture((char*)"data/TEXTURE/LightFilter.png");
	

	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
		{
			g_BackGround[i][j].use = false;
			g_BackGround[i][j].pos.x = SCREEN_WIDTH / 2;
			g_BackGround[i][j].pos.y = SCREEN_HEIGHT / 4;
			g_BackGround[i][j].vel.x = BACK_GROUND_SPEED;
			g_BackGround[i][j].vel.y = BACK_GROUND_SPEED;
			//ベクトルの正規化
			D3DXVec2Normalize(&g_BackGround[i][j].vel, &g_BackGround[i][j].vel);
			g_BackGround[i][j].vel *= BACK_GROUND_SPEED;//目的のスピードにするためにスピードを乗算する
			g_BackGround[i][j].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_BackGround[i][j].size = D3DXVECTOR2(BACK_GROUND_WIDTH, BACK_GROUND_HEIGHT);
			g_BackGround[i][j].rot = 0.0f;
			g_BackGround[i][j].uv = D3DXVECTOR2(0, 0);
			g_BackGround[i][j].animePattern = 0;
			g_BackGround[i][j].animeWidthPattern = BACK_GROUND_WIDTH_PATTERN;
			g_BackGround[i][j].animeBasePattern = 1;
			g_BackGround[i][j].animeSkipFrame = 0;
			g_BackGround[i][j].texNo = 0;
			g_BackGround[i][j].moveSp = 0;
			g_BackGround[i][j].moveCou = 0;
			g_BackGround[i][j].autoScroll = false;
			g_BackGround[i][j].lighting = false;
		}
	}

	//グローバル変数初期化
	g_UW = 1.0f / BACK_GROUND_WIDTH_PATTERN;
	g_VH = 1.0f / BACK_GROUND_HEIGHT_PATTERN;
	g_Reverse = false;

	SetBackGround(g_Tex0_sky, 0);
	SetBackGround(g_Tex1_clouds1, 1, 0.5f, true);
	SetBackGround(g_Tex2_clouds2, 2, 1.5f, true);
	SetBackGround(g_Tex3_clouds3, 3, 3.8f, true);
	SetBackGround(g_Tex4_mapGb, 2, 0.0f, false, LAYER_HIGH);
	SetBackGround(g_Tex7_tree, 5, 0.5f, false);
	SetBackGround(g_Tex8_lightFilter, 1, 0.0f, false, LAYER_HIGH, true);

	transitionDuration = 10.0f;
	currentTime = 0.0f;
	deltaTime = 0.01f;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateBackGround(void)
{
	p_Camera = GetCamera();
	p_Player = GetPlayer();

	if (p_Player[0].use)
	{
		float notLoopPos = p_Camera[0].notLoopPos.x;
		float oldNotLoopPos = p_Camera[0].oldNotLoopPos.x;

		for (int i = 0; i < BACK_GROUND_MAX; i++)
		{
			for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
			{
				if (!g_BackGround[i][j].autoScroll)
				{
					//背景の移動
					float vel = (notLoopPos - oldNotLoopPos) * g_BackGround[i][j].moveSp;
					g_BackGround[i][j].pos.x -= vel;
					g_BackGround[i][j].moveCou += vel;
				}
				else
				{
					//オートスクロールの場合
					g_BackGround[i][j].pos.x -= g_BackGround[i][j].moveSp;
					g_BackGround[i][j].moveCou += g_BackGround[i][j].moveSp;
				}

				//カメラの位置によって背景も移動させる
				if (g_BackGround[i][j].moveCou > BACK_GROUND_WIDTH)
				{
					g_BackGround[i][j].pos.x += BACK_GROUND_WIDTH;
					g_BackGround[i][j].moveCou = 0;
				}

				if (g_BackGround[i][j].moveCou < -BACK_GROUND_WIDTH)
				{
					g_BackGround[i][j].pos.x -= BACK_GROUND_WIDTH;
					g_BackGround[i][j].moveCou = 0;
				}

				//昼夜フィルター
				if (g_BackGround[i][j].lighting)
				{
					timeCount += 0.02;
					double value = sin(2 * D3DX_PI * 0.01 * timeCount);
					;
					g_BackGround[i][j].color.a = 0.3f;
					g_BackGround[i][j].color.r = value;
					g_BackGround[i][j].color.g = value;
					g_BackGround[i][j].color.b = value;
				}
			}
		}
	}
	//UpdateBackGroundColor();
}

void UpdateBackGroundColor(void)
{
	D3DXCOLOR dayColor(0.75f, 0.55f, 0.69f, 1.0f);
	D3DXCOLOR nightColor(0.98f, 0.84f, 0.63f, 1.0f);

	currentTime += deltaTime;

	float transitionRatio = currentTime / transitionDuration;
	if (currentTime >= transitionDuration)
	{
		currentTime = transitionDuration;
		deltaTime = -deltaTime;
	}

	else if (currentTime <= 0.0f)
	{
		deltaTime = -deltaTime;
	}

	D3DXCOLOR lerpedColor;
	D3DXColorLerp(&lerpedColor, &dayColor, &nightColor, transitionRatio);

	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
		{
			g_BackGround[i][j].color = lerpedColor;
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawBackGroundLow(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
		{
			if (g_BackGround[i][j].use && g_BackGround[i][j].layerWhole == LAYER_LOW)
			{
				//アニメーション
				g_BackGround[i][j].uv = SetAnimation(g_BackGround[i][j].animeBasePattern, g_BackGround[i][j].animePattern, BACK_GROUND_WIDTH_PATTERN, BACK_GROUND_HEIGHT_PATTERN, g_BackGround[i][j].animeWidthPattern, g_Reverse);

				g_BackGround[i][j].animeSkipFrame = Counter(g_BackGround[i][j].animeSkipFrame, BACK_GROUND_FRAME_SPAN);

				if (g_BackGround[i][j].animeSkipFrame == 0)
				{
					g_BackGround[i][j].animePattern = Counter(g_BackGround[i][j].animePattern, BACK_GROUND_FRAME_MAX);
				}

				DrawSpriteColorRotate(g_BackGround[i][j].texNo,
					g_BackGround[i][j].pos.x,
					g_BackGround[i][j].pos.y,
					g_BackGround[i][j].size.x, 
					g_BackGround[i][j].size.y,	//幅、高さ
					g_BackGround[i][j].uv.x, 
					g_BackGround[i][j].uv.y,		//中心UV座標
					g_UW, g_VH,		//テクスチャ幅、高さ
					g_BackGround[i][j].color.r, g_BackGround[i][j].color.g, g_BackGround[i][j].color.b, g_BackGround[i][j].color.a,
					g_BackGround[i][j].rot
				);
			}
		}
	}
}

void DrawBackGroundHigh(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
		{
			if (g_BackGround[i][j].use && g_BackGround[i][j].layerWhole == LAYER_HIGH)
			{
				//アニメーション
				g_BackGround[i][j].uv = SetAnimation(g_BackGround[i][j].animeBasePattern, g_BackGround[i][j].animePattern, BACK_GROUND_WIDTH_PATTERN, BACK_GROUND_HEIGHT_PATTERN, g_BackGround[i][j].animeWidthPattern, g_Reverse);

				g_BackGround[i][j].animeSkipFrame = Counter(g_BackGround[i][j].animeSkipFrame, BACK_GROUND_FRAME_SPAN);

				if (g_BackGround[i][j].animeSkipFrame == 0)
				{
					g_BackGround[i][j].animePattern = Counter(g_BackGround[i][j].animePattern, BACK_GROUND_FRAME_MAX);
				}

				DrawSpriteColorRotate(g_BackGround[i][j].texNo,
					g_BackGround[i][j].pos.x,
					g_BackGround[i][j].pos.y,
					g_BackGround[i][j].size.x, g_BackGround[i][j].size.y,	//幅、高さ
					g_BackGround[i][j].uv.x, g_BackGround[i][j].uv.y,		//中心UV座標
					g_UW, g_VH,		//テクスチャ幅、高さ
					g_BackGround[i][j].color.r, g_BackGround[i][j].color.g, g_BackGround[i][j].color.b, g_BackGround[i][j].color.a,
					g_BackGround[i][j].rot
				);
			}
		}
	}
}



//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitBackGround(void)
{

}

//---------------------------------------------------
// 背景取得処理
//---------------------------------------------------
BACK_GROUND* GetBackGround()
{
	return &g_BackGround[0][0];
}

//---------------------------------------------------
// 背景配置処理
//---------------------------------------------------
void SetBackGround(int texNo, int layer, float moveSp, bool autoScroll, LAYER_WHOLE layerWhole, bool lighting)
{
	p_Camera = GetCamera();
	for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
	{
		g_BackGround[layer][j].texNo = texNo;
		g_BackGround[layer][j].pos = D3DXVECTOR2(p_Camera[0].pos.x - (BACK_GROUND_WIDTH * 2) + (BACK_GROUND_WIDTH * j), SCREEN_HEIGHT * 0.5f);
		g_BackGround[layer][j].uv = D3DXVECTOR2(0, 0);
		g_BackGround[layer][j].animePattern = 0;
		g_BackGround[layer][j].animeWidthPattern = BACK_GROUND_WIDTH_PATTERN;
		g_BackGround[layer][j].animeBasePattern = 1;
		g_BackGround[layer][j].animeSkipFrame = 0;
		g_BackGround[layer][j].moveSp = moveSp;
		g_BackGround[layer][j].autoScroll = autoScroll;
		g_BackGround[layer][j].layerWhole = layerWhole;
		g_BackGround[layer][j].lighting = lighting;
		g_BackGround[layer][j].use = true;
	}
}
