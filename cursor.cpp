//===================================================
//�J�[�\��(cursor.cpp)
//Auhor:�n� �C	Date:2023.8.9
//===================================================
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "cursor.h"
#include "main.h"
#include "game_option.h"
#include "fade.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
static int g_TexNo;
int g_SE_cursor_move; //�T�E���h�f�[�^�̃C���f�b�N�X
int g_SE_decision; //�T�E���h�f�[�^�̃C���f�b�N�X
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static D3DXVECTOR2 g_posL;
static D3DXVECTOR2 g_posR;
static int g_AnimePattern;
static int g_AnimeBasePattern;//�A�j���[�V�����ԍ��̕������Ƃ̃x�[�X�l
static int g_AnimeSkipFrame;
static int g_CursorCou;
static int g_Cursor;
static int g_FrameCou;
static int g_LoopCou;
static bool g_Select;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitCursor(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/cursor.png");

	char se1[] =
	{
		"data\\SE\\cursor_move.wav"
	};
	g_SE_cursor_move = LoadSound(&se1[0]);
	
	char se2[] =
	{
		"data\\SE\\decision.wav"
	};
	g_SE_decision = LoadSound(&se2[0]);

	//�O���[�o���ϐ�������
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / CURSOR_WIDTH_PATTERN;
	g_VH = 1.0f / CURSOR_HEIGHT_PATTERN;
	g_posL = D3DXVECTOR2(0.0f, 0.0f);
	g_posR = D3DXVECTOR2(0.0f, 0.0f);
	g_AnimePattern = CURSOR_FRAME_MAX;
	g_AnimeBasePattern = 0;//�A�j���[�V�����ԍ��̕������Ƃ̃x�[�X�l
	g_AnimeSkipFrame = 0;
	g_CursorCou = 0;
	g_Cursor = -1;
	g_FrameCou = 0;
	g_LoopCou = 0;
	g_Select = false;
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateCursor(void)
{
	//UV�A�j���[�V����
	//      w             N % ���̃p�^�[����
	g_U = (1.0f / CURSOR_WIDTH_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) % CURSOR_WIDTH_PATTERN);	//���̍��W�v�Z
	//     H              N / ���̃p�^�[����
	g_V = (1.0f / CURSOR_HEIGHT_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) / CURSOR_WIDTH_PATTERN); //�c�̍��W�v�Z

	//�J�E���^�[�𐮐��ł��ꍇ�̗�1
	g_AnimeSkipFrame++;
	if (g_AnimeSkipFrame > CURSOR_FRAME_SPAN)
	{
		g_AnimeSkipFrame = 0;
		g_AnimePattern++;

		if (g_AnimePattern > CURSOR_FRAME_MAX)
		{
			g_AnimePattern = 0;
		}
	}

	//�����t
	if (!g_Select)
	{
		if (GetKeyboardTrigger(DIK_W))
		{
			PlaySound(g_SE_cursor_move, 0);
			g_CursorCou--;
		}

		if (GetKeyboardTrigger(DIK_S))
		{
			PlaySound(g_SE_cursor_move, 0);
			g_CursorCou++;
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		PlaySound(g_SE_decision, 0);
		g_Select = true;
	}

	//����{�^�����������Ƃ�
	if (g_Select)
	{
		switch (GetScene())
		{
		case SCENE_TITLE:
			switch (g_Cursor)//�V�[�����Ƃ̕���
			{
			case TITLE_START:
				SelectFlash(MESSAGE_START, SCENE_GAME);
				break;

			case TITLE_EXIT:
				SelectFlash(MESSAGE_EXIT, SCENE_EXIT);
				break;

			default:
				break;
			}
			break;

		case SCENE_RESULT:
			switch (g_Cursor)//�V�[�����Ƃ̕���
			{
			case RESULT_RETRY:
				SelectFlash(MESSAGE_RETRY, SCENE_GAME);
				break;

			case RESULT_EXIT:
				SelectFlash(MESSAGE_EXIT, SCENE_TITLE);
				break;

			default:
				break;
			}
			break;
		}
		
	}

	//�J�[�\���ړ�
	switch (GetScene())
	{
	case SCENE_TITLE:
		switch (abs(g_CursorCou % 2))//�V�[�����Ƃ̕���
		{
		case 0:
			g_Cursor = TITLE_START;
			g_posL = GetGameOptionPos(MESSAGE_START);
			g_posL.x -= GAME_OPTION_START_WIDTH * 0.5 + CURSOR_SPACE;
			g_posR = GetGameOptionPos(MESSAGE_START);
			g_posR.x += GAME_OPTION_START_WIDTH * 0.5 + CURSOR_SPACE;
			break;

		case 1:
			g_Cursor = TITLE_EXIT;
			g_posL = GetGameOptionPos(MESSAGE_EXIT);
			g_posL.x -= GAME_OPTION_EXIT_WIDTH * 0.5 + CURSOR_SPACE;
			g_posR = GetGameOptionPos(MESSAGE_EXIT);
			g_posR.x += GAME_OPTION_EXIT_WIDTH * 0.5 + CURSOR_SPACE;
			break;

		default:
			break;
		}
		break;

	case SCENE_RESULT:
		switch (abs(g_CursorCou % 2))//�V�[�����Ƃ̕���
		{
		case 0:
			g_Cursor = RESULT_RETRY;
			g_posL = GetGameOptionPos(MESSAGE_RETRY);
			g_posL.x -= GAME_OPTION_START_WIDTH * 0.5 + CURSOR_SPACE;
			g_posR = GetGameOptionPos(MESSAGE_RETRY);
			g_posR.x += GAME_OPTION_START_WIDTH * 0.5 + CURSOR_SPACE;
			break;

		case 1:
			g_Cursor = RESULT_EXIT;
			g_posL = GetGameOptionPos(MESSAGE_EXIT);
			g_posL.x -= GAME_OPTION_EXIT_WIDTH * 0.5 + CURSOR_SPACE;
			g_posR = GetGameOptionPos(MESSAGE_EXIT);
			g_posR.x += GAME_OPTION_EXIT_WIDTH * 0.5 + CURSOR_SPACE;
			break;

		default:
			break;
		}
		break;
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawCursor(void)
{
	DrawSprite(g_TexNo,
		g_posL.x,
		g_posL.y,
		CURSOR_WIDTH, CURSOR_HEIGHT,	//���A����
		g_U, g_V,		//���SUV���W
		g_UW, g_VH
	);

	DrawSprite(g_TexNo,
		g_posR.x,
		g_posR.y,
		CURSOR_WIDTH, CURSOR_HEIGHT,	//���A����
		g_U, g_V,		//���SUV���W
		g_UW, g_VH
	);
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitCursor(void)
{

}

//---------------------------------------------------
//�_�ł��Ď��̃V�[���Ɉڍs
//---------------------------------------------------
void SelectFlash(MESSAGE_PATTERN MessagePattern, SCENE Scene)
{
	g_FrameCou++;

	if (g_FrameCou > 3)
	{
		UseGameOption(MessagePattern);
		g_FrameCou = 0;
		g_LoopCou++;
	}

	if (g_LoopCou == 10)
	{
		g_FrameCou = 0;
		g_Select = false;
		//�Q�[���I��
		if (SCENE_EXIT == Scene)
		{
			PostQuitMessage(0);
		}
		//�w��V�[���Ɉڍs
		SetFade(FADE_STATE_OUT);//�t�F�[�h�A�E�g�J�n���N�G�X�g
		SceneTransition(Scene);
	}
}




