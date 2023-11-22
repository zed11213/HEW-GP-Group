//===================================================
//�^�C�g�����S(title_logo.cpp)
//Auhor:�n� �C	Date:2023.8.5
//===================================================
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "title_logo.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
static int g_TexNo;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static D3DXVECTOR2 g_pos;
static int g_AnimePattern;
static int g_AnimeBasePattern;//�A�j���[�V�����ԍ��̕������Ƃ̃x�[�X�l
static int g_AnimeSkipFrame;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitTitleLogo(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/title_logo.png");

	//�O���[�o���ϐ�������
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / TITLE_LOGO_WIDTH_PATTERN;
	g_VH = 1.0f / TITLE_LOGO_HEIGHT_PATTERN;
	g_pos = D3DXVECTOR2(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF * 0.5f);
	g_AnimePattern = TITLE_LOGO_FRAME_MAX;
	g_AnimeBasePattern = 0;
	g_AnimeSkipFrame = 0;
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateTitleLogo(void)
{
	//UV�A�j���[�V����
	//      w             N % ���̃p�^�[����
	g_U = (1.0f / TITLE_LOGO_WIDTH_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) % TITLE_LOGO_WIDTH_PATTERN);	//���̍��W�v�Z
	//     H              N / ���̃p�^�[����
	g_V = (1.0f / TITLE_LOGO_HEIGHT_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) / TITLE_LOGO_WIDTH_PATTERN); //�c�̍��W�v�Z

	//�J�E���^�[�𐮐��ł��ꍇ�̗�1
	g_AnimeSkipFrame++;
	if (g_AnimeSkipFrame > TITLE_LOGO_FRAME_SPAN)
	{
		g_AnimeSkipFrame = 0;
		g_AnimePattern++;

		if (g_AnimePattern > TITLE_LOGO_FRAME_MAX)
		{
			g_AnimePattern = 0;
		}
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawTitleLogo(void)
{
	DrawSprite(g_TexNo,
		g_pos.x,
		g_pos.y,
		TITLE_LOGO_WIDTH, TITLE_LOGO_HEIGHT,	//���A����
		g_U, g_V,		//���SUV���W
		g_UW, g_VH	//�e�N�X�`�����A����
	);
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitTitleLogo(void)
{

}




