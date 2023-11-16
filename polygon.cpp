/*==============================================================================

   頂点管理 [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon.h"
#include "texture.h"
#include "sprite.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
struct POLYGON{
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		vel;	//速度ベクトル
	D3DXCOLOR		color;	//頂点カラー
};

static POLYGON g_Polygon;
static int g_TexNo;

static float g_U = 0.0f;
static float g_V = 0.0f;
static int g_AnimePattern = 0;
static int g_AnimeSkipFrame = 0;

static float g_AnimeSkipFrameFloat = 0;


//=============================================================================
// 初期化処理
//=============================================================================
void InitPolygon(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/runningman002.png");

	//初期化
	g_Polygon.pos.x = SCREEN_WIDTH / 2;
	g_Polygon.pos.y = SCREEN_HEIGHT / 2;




	g_Polygon.vel.x = 2.0f;
	g_Polygon.vel.y = 2.0f;

	//ベクトルの正規化
	D3DXVec2Normalize(&g_Polygon.vel, &g_Polygon.vel);
	g_Polygon.vel *= 2.0f;//目的のスピードにするためにスピードを乗算する


	g_Polygon.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_U = 0.0f;
	g_V = 0.0f;
	g_AnimePattern = 0;
	g_AnimeSkipFrame = 0;	
	g_AnimeSkipFrameFloat = 0;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{        //      w             N % 5
	g_U = (1.0f / 5.0f) * (g_AnimePattern % 5);	//横の座標計算
	     //     H              N / 5
	g_V = (1.0f / 2.0f) * (g_AnimePattern / 5); //縦の座標計算
	g_AnimeSkipFrame++;


	////カウンターをfloatでやる場合の例
	//g_AnimeSkipFrameFloat += 0.7f;
	//if (g_AnimeSkipFrameFloat >= 1.0f)
	//{
	//	g_AnimeSkipFrameFloat -= 1.0f;//
	//	g_AnimePattern++;
	//	if (g_AnimePattern > 9)
	//	{
	//		g_AnimePattern = 0;
	//	}
	//}

	//カウンターを整数でやる場合の例1
	g_AnimeSkipFrame++;
	if (g_AnimeSkipFrame > 10)
	{
		g_AnimePattern++;
		g_AnimeSkipFrame = 0;
		if (g_AnimePattern > 9)
		{
			g_AnimePattern = 0;
		}
	}

	////カウンターを整数でやる場合の例2
	//g_AnimeSkipFrame++;
	//if ( (g_AnimeSkipFrame % 10) == 0)//10の倍数なら0になる
	//{
	//	g_AnimePattern++;
	//	//g_AnimeSkipFrame = 0;//リセットしない
	//	if (g_AnimePattern > 9)
	//	{
	//		g_AnimePattern = 0;
	//	}
	//}


	//キャラクターの移動
	g_Polygon.pos += g_Polygon.vel;

	static float kakudo1 = 0;
	static float kakudo2 = 0;
	g_Polygon.pos.x = cosf(kakudo1) * 130.0f + (SCREEN_WIDTH / 2);
	g_Polygon.pos.y = sinf(kakudo2) * 200.0f + (SCREEN_HEIGHT / 2);
	kakudo1 += D3DXToRadian(3.0f);
	kakudo2 += D3DXToRadian(5.0f);






}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	// ポリゴン描画
	DrawSprite(g_TexNo, g_Polygon.pos.x, g_Polygon.pos.y, 400.0f, 400.0f, g_U, g_V, (1.0f/5), (1.0f/2));
}