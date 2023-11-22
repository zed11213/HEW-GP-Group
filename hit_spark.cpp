//===================================================
//�q�b�g�G�t�F�N�g(hit_spark.cpp)
//Auhor:�n� �C	Date:2023.9.3
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
//�O���[�o���ϐ�
//---------------------------------------------------
//static��t����ƃt�@�C���̒��̃O���[�o���ϐ��ɂȂ�
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
//������
//---------------------------------------------------
void InitHitSpark(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/HitSpark.png");
	//���ʉ��쐬
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

	//�O���[�o���ϐ�������
	g_UW = 1.0f / HIT_SPARK_WIDTH_PATTERN;
	g_VH = 1.0f / HIT_SPARK_HEIGHT_PATTERN;
	g_Reverse = false;
}

//---------------------------------------------------
//�X�V
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
//�`��
//---------------------------------------------------
void DrawHitSpark(void)
{
	for (int i = 0; i < HIT_SPARK_MAX; i++)
	{
		if (g_HitSpark[i].use)
		{
			//�A�j���[�V����
			g_HitSpark[i].uv = SetAnimation(g_HitSpark[i].animeBasePattern, g_HitSpark[i].animePattern, HIT_SPARK_WIDTH_PATTERN, HIT_SPARK_HEIGHT_PATTERN, g_HitSpark[i].animeWidthPattern, g_Reverse);

			g_HitSpark[i].animeSkipFrame = Counter(g_HitSpark[i].animeSkipFrame, HIT_SPARK_FRAME_SPAN);

			if (g_HitSpark[i].animeSkipFrame == 0)
			{
				g_HitSpark[i].animePattern = Counter(g_HitSpark[i].animePattern, HIT_SPARK_FRAME_MAX);
				if (g_HitSpark[i].animePattern == 0)g_HitSpark[i].animeWidthPattern = 1;//�A�j�������[�v�����Ȃ�
			}


			DrawSpriteColorRotateCamera(g_TexNo,
				g_HitSpark[i].pos.x,
				g_HitSpark[i].pos.y,
				g_HitSpark[i].size.x, g_HitSpark[i].size.y,	//���A����
				g_HitSpark[i].uv.x, g_HitSpark[i].uv.y,		//���SUV���W
				g_UW, g_VH,		//�e�N�X�`�����A����
				g_HitSpark[i].color.r, g_HitSpark[i].color.g, g_HitSpark[i].color.b, g_HitSpark[i].color.a,
				g_HitSpark[i].rot
			);
		}
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitHitSpark(void)
{

}

//---------------------------------------------------
// �q�b�g�G�t�F�N�g�擾����
//---------------------------------------------------
HIT_SPARK* GetHitSpark()
{
	return &g_HitSpark[0];
}

//---------------------------------------------------
// �q�b�g�G�t�F�N�g�z�u����
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
