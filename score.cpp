//===================================================
//�X�R�A(score.cpp)
//Auhor:�n� �C	Date:2023.9.13
//===================================================
#include <fstream>
#include <iostream>
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "score.h"
#include "sound.h"
#include "player.h"
#include "text_create.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
static int g_ScoreList[SCORE_MAX];
static int g_Score;
static int g_DrawScore;
static int g_OldScore;
unsigned int g_ScoreTexture;
static float g_scale;
static float g_easingFactor;
static bool g_fanfare;
static int g_SE_waveUp;
static bool g_upSeCheck;
static int g_Wave;
static int g_OldWave;
static bool g_WaveUp;
static float g_WaveAlpha;
static bool g_WaveAlphaDown;
static D3DXCOLOR g_color;
static PLAYER* p_Player;

//�N�C�b�N�\�[�g�Ŏg�p
int cmpScore(const void* n1, const void* n2)
{
	int value1 = *((const int*)n1);
	int value2 = *((const int*)n2);

	if (value1 < value2)
	{
		return 1;
	}
	else if (value1 > value2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

//---------------------------------------------------
//������
//---------------------------------------------------
void InitScore()
{
	for (int i = 0; i < SCORE_MAX; i++)
	{
		g_ScoreList[i] = 0;
	}

	//�Q�[����ʂɈڍs���鎞����������
	switch (GetScene())
	{
	case SCENE_GAME:
		g_Score = SCORE_INIT_SCORE;
		break;

	case SCENE_RESULT:
		LoadScore();
		SaveScore();
		break;

	default:
		break;
	}

	//�e�N�X�`���쐬
	g_ScoreTexture = LoadTexture((char*)"data/TEXTURE/number.png");

	//���ʉ��쐬
	char se1[] =
	{
		"data\\SE\\se_waveUp.wav"
	};
	g_SE_waveUp = LoadSound(&se1[0]);

	g_scale = 0.0f;
	g_easingFactor = 1.0f;
	g_fanfare = false;
	g_upSeCheck = false;
	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Wave = 0;
	g_OldScore = 0;
	g_OldWave = g_Wave;
	g_WaveUp = false; 
	g_WaveAlpha = 1;
	g_WaveAlphaDown = false;
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateScore()
{
	p_Player = GetPlayer();
	g_OldWave = g_Wave;
	g_WaveUp = false;
	g_Score = p_Player[0].score;
	
	g_DrawScore += max(1, (g_Score - g_DrawScore) / 25);
	if (g_DrawScore > g_Score)g_DrawScore = g_Score;

	//�Q�[���I�[�p�[�ɂȂ�����E�F�[�u�����Z�b�g
	if (!p_Player[0].use)
	{
		g_Wave = 0;
		g_OldScore = 0;
	}

	//���̃X�R�A�ɂȂ邽�тɎ��s
	if (p_Player[0].use && (g_Score / WAVE_UP_SCORE > g_OldScore / WAVE_UP_SCORE || g_Wave == 0))
	{
		g_OldScore = g_Score;
		g_Wave++;
	}

	//�E�F�[�u���Ɏ��s
	if (g_OldWave != g_Wave)
	{
		g_WaveAlphaDown = false;
		g_WaveAlpha = 0.9f;
		g_WaveUp = true;
		PlaySound(g_SE_waveUp, 0);
	}

	////�A���t�@���グ��
	//if (g_WaveUp && !g_WaveAlphaDown)
	//{
	//	g_WaveAlpha += 0.0005f;
	//	if (g_WaveAlpha >= 1)
	//	{
	//		g_WaveAlpha = 1;
	//		g_WaveAlphaDown = true;
	//	}
	//		
	//}
	////�A���t�@��������
	//else if(g_WaveAlphaDown && g_WaveAlpha > 0)
	//{
	//	g_WaveAlpha -= 0.01f;
	//	if (g_WaveAlpha < 0)
	//	{
	//		g_WaveAlpha = 0;
	//		g_WaveAlphaDown = false;
	//		g_WaveUp = false;
	//	}
	//		
	//}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawScore()
{
	switch (GetScene())
	{
	case SCENE_GAME:
		SetDrawTextCreate("SCORE", SCREEN_WIDTH * 0.5f, 25, 5, 1);
		SetDrawTextCreate(std::to_string(g_DrawScore), SCREEN_WIDTH * 0.5f, 90, 10, 2);

		//�E�F�[�u���Ɏ��s
		if (g_WaveUp && p_Player[0].use)
		{
			SetDrawTextCreate("WAVE" + std::to_string(g_Wave), SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 10, 4, 300, 0.01f, 0.02f);
		}
		

		break;

	case SCENE_RESULT:
		SetDrawScore(g_Score, SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.1f, 80, 88 * 1.5, 1.0f);
		for (int i = 0; i < 9; i++)
		{
			SetDrawRank(i + 1, SCREEN_WIDTH_HALF - 80 * 2.5f, SCREEN_HEIGHT * 0.2f + (((80 * 0.5f) + 20) * i), 77, 88 * 0.5f);
			SetDrawScore(g_ScoreList[i], SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.2f + (((80 * 0.5f) + 20) * i) , 80 * 0.5f, 88 * 0.5f, 1.0f);
		}
		break;

	default:
		break;
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitScore()
{

}

//---------------------------------------------------
//�X�R�A�𑝂₷
//---------------------------------------------------
void AddScore(int Score)
{
	g_Score += Score;
}

//---------------------------------------------------
//�v���C���[�����t�@�C���֏�������
//---------------------------------------------------
bool SaveScore()
{
	//�t�@�C���I�[�v��
	std::ofstream ofs("score.txt");

	//�t�@�C�����I�[�v���ł��Ȃ�������
	if (ofs.fail())
	{
		return false;
	}
	
	//�\�[�g���ď�������
	//���X�g�̈�ԏ������X�R�A���傫����Ώ�������
	SortScore();
	if (g_ScoreList[SCORE_MAX - 1] < g_Score)
	{
		g_ScoreList[SCORE_MAX - 1] = g_Score;
		SortScore();
	}

	//���X�g�̏�������
	for (int i = 0; i < SCORE_MAX; i++)
	{
		ofs << g_ScoreList[i] << std::endl;
	}

	//�t�@�C���̃N���[�Y
	ofs.close();

	return false;
}

//---------------------------------------------------
//�v���C���[�����t�@�C������ǂݍ���
//---------------------------------------------------
bool LoadScore()
{
	//�t�@�C���I�[�v��
	std::ifstream ifs("score.txt");

	//�t�@�C�����I�[�v���ł��Ȃ�������
	if (ifs.fail())
	{
		return false;
	}

	//�v���C���[�f�[�^�̏�������
	for (int i = 0; i < SCORE_MAX; i++)
	{
		//�v���C���[�f�[�^��ǂݍ���
		ifs >> g_ScoreList[i];
	}

	SortScore();

	//�t�@�C���̃N���[�Y
	ifs.close();

	return false;
}

//---------------------------------------------------
//�N�C�b�N�\�[�g
//---------------------------------------------------
void SortScore()
{
	qsort(g_ScoreList, SCORE_MAX, sizeof(int), cmpScore);//�N�C�b�N�\�[�g
}

//---------------------------------------------------
//�X�R�A�\��
//---------------------------------------------------
void SetDrawScore(int score, float posX, float posY, float sizeX, float sizeY, float scale)
{
	for (int i = 0; i < SCORE_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = score % 10;
		tx = (n % 10) * 0.1f;
		ty = (n / 10) * 1.0f;

		score /= 10;

		float sx, sy;
		sx = (posX - (sizeX * SCORE_FIGURE * 0.5f * scale)) + ((sizeX * 0.5f * scale) * (SCORE_FIGURE * 2 - (i + i + 1)));
		sy = posY;

		switch (GetScene())
		{
		case SCENE_GAME:
			DrawSpriteColorRotateScale(g_ScoreTexture, sx, sy, sizeX, sizeY,
				0.0f, 0.0f,
				tx, ty, 0.1f, 1.0f,
				g_color.r, g_color.g, g_color.b, g_color.a,
				0.0f,
				scale, scale);
			break;

		case SCENE_RESULT:
			DrawSpriteColorRotateScale(g_ScoreTexture, sx, sy, sizeX, sizeY,
				0.0f, 0.0f,
				tx, ty, 0.1f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f,
				scale, scale);
			break;

		default:
			break;
		}

	}
}

//---------------------------------------------------
//���ʕ\��
//---------------------------------------------------
void SetDrawRank(int score, float posX, float posY, float sizeX, float sizeY)
{
	for (int i = 0; i < RANK_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = score % 10;
		tx = (n % 10) * 0.1f;
		ty = (n / 10) * 1.0f;

		score /= 10;

		float sx, sy;
		sx = (posX - (sizeX * RANK_FIGURE * 0.5f)) + ((sizeX * 0.5f) * (RANK_FIGURE * 2 - (i + i + 1)));
		sy = posY;

		DrawSprite(g_ScoreTexture, sx, sy, sizeX, sizeY,
			tx, ty, 0.1f, 1.0f);
	}
}

//---------------------------------------------------
//�X�R�A���擾
//---------------------------------------------------
int GetScore()
{
	return g_Score;
}

//---------------------------------------------------
//�J�[�u��`���l���擾
//---------------------------------------------------
float EaseInOut(float t)
{
	// �x�W�F�Ȑ��⑼�̃C�[�W���O�֐����g�p���āA���� t �̕�Ԓl���v�Z����
	return t * t + (1 - t) * (1 - t);
}

//---------------------------------------------------
//�X�R�A���`�ɂ���
//---------------------------------------------------
void SetScore(int Score)
{
	g_Score = Score;
}

//---------------------------------------------------
//�E�F�[�u�擾
//---------------------------------------------------
int GetWave()
{
	return g_Wave;
}

//---------------------------------------------------
//�E�F�[�u�ݒ�
//---------------------------------------------------
void SetWave(int wave)
{
	g_Wave = wave;
}