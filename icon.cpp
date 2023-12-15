//===================================================
//アイコン改修版(icon.cpp)
//Auhor:名倉 彪		Date:2023/12/15
//===================================================
#include <fstream>
#include <iostream>
#include "main.h"
#include "icon.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "text_create.h"
#include "input.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
static ICON g_Icon[ICON_MAX];
static int g_TexIcon;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static PLAYER* p_Player;
static ICON_DATA g_IconInfo[ICON_FRAME_MAX] =
{
	//左上座標とマップチップ属性の設定
	//ここに追加していく////////////////////////////////////////////////////////////////////////////
	{ ICON_NONE, 0, 0, 0, g_TexIcon},	//{属性名, 画像インデックス, 横パターン数, 縦パターン数}
	{ ICON_HEART, 0, 1, 1, g_TexIcon},	//1ハート
	{ ICON_HEART, 2, 1, 1, g_TexIcon},	//2ハート(消失)
	{ ICON_COIN, 4, 1, 1, g_TexIcon},	//3コイン
	////////////////////////////////////////////////////////////////////////////////////////////////
};


static char g_IconMap[ICON_SCREEN_SIZE_Y][ICON_SCREEN_SIZE_X] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0
	{0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0}, //2
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //9
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //9
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
//	 4,3,2,1,0,9,8,7,6,5,4,3,2,1,0,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4
//                           |                       |  					 |
};

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitIcon()
{
	//テクスチャ作成
	g_TexIcon = LoadTexture((char*)"data/TEXTURE/Icon.png");

	for (int i = 0; i < ICON_MAX; i++)
	{
		g_Icon[i].use = false;
		g_Icon[i].name = ICON_NONE;
		g_Icon[i].pos.x = 0;
		g_Icon[i].pos.y = 0;
		g_Icon[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Icon[i].animePattern = 0;
		g_Icon[i].animeSkipFrame = 0;
		g_Icon[i].anumeFrameSpan = 0;
		g_Icon[i].size = D3DXVECTOR2(ICON_WIDTH, ICON_HEIGHT);
		g_Icon[i].scale = 0;
	}

	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / ICON_WIDTH_PATTERN;
	g_VH = 1.0f / ICON_HEIGHT_PATTERN;
	int hpNum = 0;
	int mapNum = 0;

	for (int y = 0; y < ICON_SCREEN_SIZE_Y; y++)
	{
		for (int x = 0; x < ICON_SCREEN_SIZE_X; x++)
		{
			if (g_IconMap[y][x] != 0)
			{
				
				ICON_DATA iconChip = g_IconInfo[g_IconMap[y][x]];
				//ここに追加していく////////////////////////////////////////////////////////////////////////////
				switch (iconChip.attrib)
				{
				case ICON_HEART:
					hpNum++;
					SetIconData(iconChip, "PlayerHP" + std::to_string(hpNum), g_TexIcon, x * ICON_MAP_WIDTH, y * ICON_MAP_HEIGHT);
					break;

				case ICON_COIN:
					SetIconData(iconChip, "PlayerCoin", g_TexIcon, x * ICON_MAP_WIDTH, y * ICON_MAP_HEIGHT);
					break;


				default:
					break;
				}
				////////////////////////////////////////////////////////////////////////////////////////////////

			}
		}
	}
	
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateIcon()
{
	//体力表示
	p_Player = GetPlayer();

	for (int i = 0; i < PLAYER_INIT_HP; i++)
	{
		if (p_Player[0].hp > i)
		{
			ChangeIcon("PlayerHP" + std::to_string(i + 1), g_IconInfo[1], false);
		}
		else
		{
			ChangeIcon("PlayerHP" + std::to_string(i + 1), g_IconInfo[2], false);
		}
	}

	//コイン枚数表示
	SetDrawTextCreate(std::to_string(p_Player[0].coin), 200, 40, 4.0f, 1.4f);

}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawIcon()
{
	for (int i = 0; i < ICON_MAX; i++)
	{
		if (g_Icon[i].use)
		{
			g_Icon[i].iconData.animeFrameMax = g_Icon[i].iconData.animeWidthPattern * g_Icon[i].iconData.animeHeightPattern;

			D3DXVECTOR2 uv = SetAnimation(g_Icon[i].iconData.animeBasePattern, g_Icon[i].animePattern, ICON_WIDTH_PATTERN, ICON_HEIGHT_PATTERN, g_Icon[i].iconData.animeWidthPattern);

			g_U = uv.x;
			g_V = uv.y;

			if (g_Icon[i].anime)
			{
				g_Icon[i].animeSkipFrame = Counter(g_Icon[i].animeSkipFrame, g_Icon[i].anumeFrameSpan);

				if (g_Icon[i].animeSkipFrame == 0)
				{
					g_Icon[i].animePattern = Counter(g_Icon[i].animePattern, g_Icon[i].iconData.animeFrameMax);
				}
			}

			DrawSpriteColorRotate(g_TexIcon,
				g_Icon[i].pos.x,
				g_Icon[i].pos.y,
				g_Icon[i].size.x, g_Icon[i].size.y,	//幅、高さ
				g_U, g_V,		//中心UV座標
				g_UW, g_VH,		//テクスチャ幅、高さ
				g_Icon[i].color.r, g_Icon[i].color.g, g_Icon[i].color.b, g_Icon[i].color.a,
				0.0f
			);
		}
	}
}
//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitIcon()
{

}

//---------------------------------------------------
// セット
//---------------------------------------------------
void SetIconData(ICON_DATA iconData, std::string name, int texture, float posX, float posY, float sizeX, float sizeY, bool anime, int frameSpan)
{
	for (int i = 0; i < ICON_MAX; i++)
	{
		if (!g_Icon[i].use)
		{
			g_Icon[i].iconData = iconData;
			g_Icon[i].name = name;
			g_Icon[i].pos.x = posX;
			g_Icon[i].pos.y = posY;
			g_Icon[i].anime = anime;
			g_Icon[i].anumeFrameSpan = frameSpan;
			g_Icon[i].size = D3DXVECTOR2(sizeX, sizeY);
			g_Icon[i].texture = texture;
			g_Icon[i].use = true;
			break;
		}
	}
}

//---------------------------------------------------
//アイコン変更
//---------------------------------------------------
void ChangeIcon(std::string name, ICON_DATA iconData, bool anime, int frameSpan)
{
	for (int i = 0; i < ICON_MAX; i++)
	{
		if (g_Icon[i].name == name && g_Icon[i].use)
		{
			g_Icon[i].iconData = iconData;
			g_Icon[i].anime = anime;
			g_Icon[i].anumeFrameSpan = frameSpan;
			break;
		}
	}
}

//=============================================================================
// U座標をセット(引数 : 左上端を0その右隣りを1,2,3...としたときの数)
//=============================================================================
float GetIconU(int index)
{
	return ((index % ICON_WIDTH_PATTERN) * (1.0f / ICON_WIDTH_PATTERN));
}

//=============================================================================
// V座標をセット(引数 : 左上端を0その右隣りを1,2,3...としたときの数)
//=============================================================================
float GetIconV(int index)
{
	return ((index / ICON_WIDTH_PATTERN) * (1.0f / ICON_HEIGHT_PATTERN));
}

//=============================================================================
// UV座標をセット(引数 : 左上端を0その右隣りを1,2,3...としたときの数)
//=============================================================================
D3DXVECTOR2 GetIconUV(int index)
{
	D3DXVECTOR2 UV = D3DXVECTOR2(GetIconU(index), GetIconV(index));
	return UV;
}

