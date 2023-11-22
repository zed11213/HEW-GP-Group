//===================================================
//����(dead.cpp)
//Auhor:�n� �C	Date:2023.8.1
//===================================================
#include "dead.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "player.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
//static��t����ƃt�@�C���̒��̃O���[�o���ϐ��ɂȂ�
static int g_TexNo;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimePattern;
static int g_AnimeBasePattern;//�A�j���[�V�����ԍ��̕������Ƃ̃x�[�X�l
static int g_AnimeSkipFrame;
static float g_AnimeSkipFrameFloat;
static bool g_hit;
static DEAD	g_Dead[DEAD_MAX];
static PLAYER* p_Player;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitDead(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/crushed_tomato.png");

	//������
	for (int i = 0; i <DEAD_MAX; i++)
	{
		g_Dead[i].pos.x = SCREEN_WIDTH / 2;
		g_Dead[i].pos.y = SCREEN_HEIGHT / 2;
		g_Dead[i].oldPos.x = g_Dead[i].pos.x;
		g_Dead[i].oldPos.y = g_Dead[i].pos.y;
		g_Dead[i].dir = 4;//������
		g_Dead[i].vel.x =DEAD_SPEED;
		g_Dead[i].vel.y =DEAD_SPEED;
		//�x�N�g���̐��K��
		D3DXVec2Normalize(&g_Dead[i].vel, &g_Dead[i].vel);
		g_Dead[i].vel *=DEAD_SPEED;//�ړI�̃X�s�[�h�ɂ��邽�߂ɃX�s�[�h����Z����
		g_Dead[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Dead[i].dis = 1.0f;
		g_Dead[i].BufferIndex = i *DEAD_FOLLOW_SPAN;//�����O�o�b�t�@�̎Q�Əꏊ��������
		g_Dead[i].disRate = 1.0f;
		g_Dead[i].initSize = D3DXVECTOR2(0.0f, 0.0f);
		g_Dead[i].size = D3DXVECTOR2(200.0f, 200.0f);
		g_Dead[i].use = false;
	}

	//�O���[�o���ϐ�������
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
//�X�V
//---------------------------------------------------
void UpdateDead(void)
{
	for (int i = 0; i < DEAD_MAX; i++)
	{
		if (g_Dead[i].use)
		{
			p_Player = GetPlayer();

			//UV�A�j���[�V����
			//      w             N % ���̃p�^�[����
			g_U = (1.0f / DEAD_WIDTH_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) % DEAD_WIDTH_PATTERN);	//���̍��W�v�Z
			//     H              N / ���̃p�^�[����
			g_V = (1.0f / DEAD_HEIGHT_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) / DEAD_WIDTH_PATTERN); //�c�̍��W�v�Z

			//�J�E���^�[�𐮐��ł��ꍇ�̗�1
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
//�`��
//---------------------------------------------------
void DrawDead(void)
{
	
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitDead(void)
{

}

//---------------------------------------------------
// ���̎擾����
//---------------------------------------------------
DEAD* GetDead()
{
	return &g_Dead[0];
}

//---------------------------------------------------
// ���̐ݒu
//---------------------------------------------------
void SetDead(D3DXVECTOR2 pos)
{
	for (int i = 0; i < DEAD_MAX; i++)
	{
		if (g_Dead[i].use != TRUE)//���g�p�̔z�������
		{
			g_Dead[i].pos = pos;//�\�����W
			g_Dead[i].use = TRUE;//�g�p���ɂ���
			break;//�I��
		}
	}
}