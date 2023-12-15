//===================================================
//�~�j�}�b�v�\��	(minimap.cpp)
//Author:���q �V		Date:2023/12/15
//===================================================
#include <fstream>
#include <iostream>
#include "main.h"
#include "minimap.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "text_create.h"
#include "input.h"

//========================================================
//�O���[�o���ϐ�
//========================================================
static MINIMAP g_minimap[MINIMAP_MAX];
static int g_TexMinimap;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static PLAYER* p_Player;
static MINIMAP_DATA g_MinimapInfo[MINIMAP_FRAME_MAX] =
{
	//������W�ƃ}�b�v�`�b�v�����̐ݒ�
	//�����ɒǉ����Ă���////////////////////////////////////////////////////////////////////////////
	{ MINIMAP_NONE, 0, 0, 0, g_TexMinimap},			//{������, �摜�C���f�b�N�X, ���p�^�[����, �c�p�^�[����}
	{ MINIMAP_ADLE, 0, 1, 1, g_TexMinimap},			//�ʏ���
	{ MINIMAP_TURN_RIGHT, 4, 4, 1, g_TexMinimap},	//�E��]
	{ MINIMAP_TURN_LEFT, 8, 4, 1, g_TexMinimap},	//����]
	////////////////////////////////////////////////////////////////////////////////////////////////
};


static char g_IconMap[MINIMAP_SCREEN_SIZE_Y][MINIMAP_SCREEN_SIZE_X] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0
	{0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}, //5
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
//������
//---------------------------------------------------
void InitMinimap()
{
	//�e�N�X�`���쐬
	g_TexMinimap = LoadTexture((char*)"data/TEXTURE/miniMap.png");

	for (int i = 0; i < MINIMAP_MAX; i++)
	{
		g_minimap[i].use = false;
		g_minimap[i].name = MINIMAP_NONE;
		g_minimap[i].pos.x = 0;
		g_minimap[i].pos.y = 0;
		g_minimap[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_minimap[i].animePattern = 0;
		g_minimap[i].animeSkipFrame = 0;
		g_minimap[i].anumeFrameSpan = 0;
		g_minimap[i].size = D3DXVECTOR2(MINIMAP_WIDTH, MINIMAP_HEIGHT);
		g_minimap[i].scale = 0;
	}

	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / MINIMAP_WIDTH_PATTERN;
	g_VH = 1.0f / MINIMAP_HEIGHT_PATTERN;
	int hpNum = 0;
	int mapNum = 0;

	for (int y = 0; y < MINIMAP_SCREEN_SIZE_Y; y++)
	{
		for (int x = 0; x < MINIMAP_SCREEN_SIZE_X; x++)
		{
			if (g_IconMap[y][x] != 0)
			{

				MINIMAP_DATA iconChip = g_MinimapInfo[g_IconMap[y][x]];
				//�����ɒǉ����Ă���////////////////////////////////////////////////////////////////////////////
				switch (iconChip.attrib)
				{
				case MINIMAP_ADLE:
					mapNum++;
					SetMinimapData(iconChip, "Map" + std::to_string(mapNum), g_TexMinimap, x * MINIMAP_MAP_WIDTH + 80, y * MINIMAP_MAP_HEIGHT, 320, 300);
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
//�X�V
//---------------------------------------------------
void UpdateMinimap()
{
	//�~�j�}�b�v�\��
	if (GetKeyboardTrigger(DIK_1))
	{
		ChangeMinimap("Map1", g_MinimapInfo[5], true, 30);
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		ChangeMinimap("Map2", g_MinimapInfo[6], true, 30);
	}
	if (GetKeyboardTrigger(DIK_3))
	{
		ChangeMinimap("Map3", g_MinimapInfo[5], true, 30);
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawMinimap()
{
	for (int i = 0; i < MINIMAP_MAX; i++)
	{
		if (g_minimap[i].use)
		{
			g_minimap[i].minimapData.animeFrameMax = g_minimap[i].minimapData.animeWidthPattern * g_minimap[i].minimapData.animeHeightPattern;

			D3DXVECTOR2 uv = SetAnimation(g_minimap[i].minimapData.animeBasePattern, g_minimap[i].animePattern, 4, 3, g_minimap[i].minimapData.animeWidthPattern);

			g_U = uv.x;
			g_V = uv.y;

			if (g_minimap[i].anime)
			{
				g_minimap[i].animeSkipFrame = Counter(g_minimap[i].animeSkipFrame, g_minimap[i].anumeFrameSpan);

				if (g_minimap[i].animeSkipFrame == 0)
				{
					g_minimap[i].animePattern = Counter(g_minimap[i].animePattern, g_minimap[i].minimapData.animeFrameMax);
				}
			}

			DrawSpriteColorRotate(g_minimap[i].texture,
				g_minimap[i].pos.x,
				g_minimap[i].pos.y,
				g_minimap[i].size.x, g_minimap[i].size.y,	//���A����
				g_U, g_V,		//���SUV���W
				g_UW, g_VH,		//�e�N�X�`�����A����
				g_minimap[i].color.r, g_minimap[i].color.g, g_minimap[i].color.b, g_minimap[i].color.a,
				0.0f
			);
		}
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitMinimap()
{

}

//---------------------------------------------------
// �Z�b�g
//---------------------------------------------------
void SetMinimapData(MINIMAP_DATA iconData, std::string name, int texture, float posX, float posY, float sizeX, float sizeY, bool anime, int frameSpan)
{
	for (int i = 0; i < MINIMAP_MAX; i++)
	{
		if (!g_minimap[i].use)
		{
			g_minimap[i].minimapData = iconData;
			g_minimap[i].name = name;
			g_minimap[i].pos.x = posX;
			g_minimap[i].pos.y = posY;
			g_minimap[i].anime = anime;
			g_minimap[i].anumeFrameSpan = frameSpan;
			g_minimap[i].size = D3DXVECTOR2(sizeX, sizeY);
			g_minimap[i].texture = texture;
			g_minimap[i].use = true;
			break;
		}
	}
}

//---------------------------------------------------
//�A�C�R���ύX
//---------------------------------------------------
void ChangeMinimap(std::string name, MINIMAP_DATA iconData, bool anime, int frameSpan)
{
	for (int i = 0; i < MINIMAP_MAX; i++)
	{
		if (g_minimap[i].name == name && g_minimap[i].use)
		{
			g_minimap[i].minimapData = iconData;
			g_minimap[i].anime = anime;
			g_minimap[i].anumeFrameSpan = frameSpan;
			break;
		}
	}
}

//=============================================================================
// U���W���Z�b�g(���� : ����[��0���̉E�ׂ��1,2,3...�Ƃ����Ƃ��̐�)
//=============================================================================
float GetMinimapU(int index)
{
	return ((index % MINIMAP_WIDTH_PATTERN) * (1.0f / MINIMAP_WIDTH_PATTERN));
}

//=============================================================================
// V���W���Z�b�g(���� : ����[��0���̉E�ׂ��1,2,3...�Ƃ����Ƃ��̐�)
//=============================================================================
float GetMinimapV(int index)
{
	return ((index / MINIMAP_WIDTH_PATTERN) * (1.0f / MINIMAP_HEIGHT_PATTERN));
}

//=============================================================================
// UV���W���Z�b�g(���� : ����[��0���̉E�ׂ��1,2,3...�Ƃ����Ƃ��̐�)
//=============================================================================
D3DXVECTOR2 GetMinimapUV(int index)
{
	D3DXVECTOR2 UV = D3DXVECTOR2(GetMinimapU(index), GetMinimapV(index));
	return UV;
}

