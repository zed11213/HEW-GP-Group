//===================================================
//死体(dead.cpp)
//Auhor:渡邉 修	Date:2023.8.1
//===================================================
#include "dead.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "player.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_TexNo;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimePattern;
static int g_AnimeBasePattern;//アニメーション番号の方向ごとのベース値
static int g_AnimeSkipFrame;
static float g_AnimeSkipFrameFloat;
static bool g_hit;
static DEAD	g_Dead[DEAD_MAX];
static PLAYER* p_Player;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitDead(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/crushed_tomato.png");

	//初期化
	for (int i = 0; i <DEAD_MAX; i++)
	{
		g_Dead[i].pos.x = SCREEN_WIDTH / 2;
		g_Dead[i].pos.y = SCREEN_HEIGHT / 2;
		g_Dead[i].oldPos.x = g_Dead[i].pos.x;
		g_Dead[i].oldPos.y = g_Dead[i].pos.y;
		g_Dead[i].dir = 4;//下向き
		g_Dead[i].vel.x =DEAD_SPEED;
		g_Dead[i].vel.y =DEAD_SPEED;
		//ベクトルの正規化
		D3DXVec2Normalize(&g_Dead[i].vel, &g_Dead[i].vel);
		g_Dead[i].vel *=DEAD_SPEED;//目的のスピードにするためにスピードを乗算する
		g_Dead[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Dead[i].dis = 1.0f;
		g_Dead[i].BufferIndex = i *DEAD_FOLLOW_SPAN;//リングバッファの参照場所を初期化
		g_Dead[i].disRate = 1.0f;
		g_Dead[i].initSize = D3DXVECTOR2(0.0f, 0.0f);
		g_Dead[i].size = D3DXVECTOR2(200.0f, 200.0f);
		g_Dead[i].use = false;
	}

	//グローバル変数初期化
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / DEAD_WIDTH_PATTERN;
	g_VH = 1.0f / DEAD_HEIGHT_PATTERN;
	g_AnimePattern = 0;
	g_AnimeSkipFrame = 0;
	g_AnimeSkipFrameFloat = 0;
	g_hit = false;
	g_AnimeBasePattern = 0;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateDead(void)
{
	for (int i = 0; i < DEAD_MAX; i++)
	{
		if (g_Dead[i].use)
		{
			p_Player = GetPlayer();

			//UVアニメーション
			//      w             N % 横のパターン数
			g_U = (1.0f / DEAD_WIDTH_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) % DEAD_WIDTH_PATTERN);	//横の座標計算
			//     H              N / 横のパターン数
			g_V = (1.0f / DEAD_HEIGHT_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) / DEAD_WIDTH_PATTERN); //縦の座標計算

			//カウンターを整数でやる場合の例1
			g_AnimeSkipFrame++;

			if (g_AnimeSkipFrame > DEAD_FRAME_SPAN)
			{
				g_AnimeSkipFrame = 0;
				g_AnimePattern++;

				if (g_AnimePattern > DEAD_FRAME_MAX)
				{
					g_AnimePattern = DEAD_FRAME_MAX;
				}
			}
		}
	}

}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawDead(void)
{
	
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitDead(void)
{

}

//---------------------------------------------------
// 死体取得処理
//---------------------------------------------------
DEAD* GetDead()
{
	return &g_Dead[0];
}

//---------------------------------------------------
// 死体設置
//---------------------------------------------------
void SetDead(D3DXVECTOR2 pos)
{
	for (int i = 0; i < DEAD_MAX; i++)
	{
		if (g_Dead[i].use != TRUE)//未使用の配列を処理
		{
			g_Dead[i].pos = pos;//表示座標
			g_Dead[i].use = TRUE;//使用中にする
			break;//終了
		}
	}
}