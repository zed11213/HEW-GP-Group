/*==============================================================================

   ���_�Ǘ� [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon.h"
#include "texture.h"
#include "sprite.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
struct POLYGON{
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2		vel;	//���x�x�N�g��
	D3DXCOLOR		color;	//���_�J���[
};

static POLYGON g_Polygon;
static int g_TexNo;

static float g_U = 0.0f;
static float g_V = 0.0f;
static int g_AnimePattern = 0;
static int g_AnimeSkipFrame = 0;

static float g_AnimeSkipFrameFloat = 0;


//=============================================================================
// ����������
//=============================================================================
void InitPolygon(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/runningman002.png");

	//������
	g_Polygon.pos.x = SCREEN_WIDTH / 2;
	g_Polygon.pos.y = SCREEN_HEIGHT / 2;




	g_Polygon.vel.x = 2.0f;
	g_Polygon.vel.y = 2.0f;

	//�x�N�g���̐��K��
	D3DXVec2Normalize(&g_Polygon.vel, &g_Polygon.vel);
	g_Polygon.vel *= 2.0f;//�ړI�̃X�s�[�h�ɂ��邽�߂ɃX�s�[�h����Z����


	g_Polygon.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_U = 0.0f;
	g_V = 0.0f;
	g_AnimePattern = 0;
	g_AnimeSkipFrame = 0;	
	g_AnimeSkipFrameFloat = 0;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{        //      w             N % 5
	g_U = (1.0f / 5.0f) * (g_AnimePattern % 5);	//���̍��W�v�Z
	     //     H              N / 5
	g_V = (1.0f / 2.0f) * (g_AnimePattern / 5); //�c�̍��W�v�Z
	g_AnimeSkipFrame++;


	////�J�E���^�[��float�ł��ꍇ�̗�
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

	//�J�E���^�[�𐮐��ł��ꍇ�̗�1
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

	////�J�E���^�[�𐮐��ł��ꍇ�̗�2
	//g_AnimeSkipFrame++;
	//if ( (g_AnimeSkipFrame % 10) == 0)//10�̔{���Ȃ�0�ɂȂ�
	//{
	//	g_AnimePattern++;
	//	//g_AnimeSkipFrame = 0;//���Z�b�g���Ȃ�
	//	if (g_AnimePattern > 9)
	//	{
	//		g_AnimePattern = 0;
	//	}
	//}


	//�L�����N�^�[�̈ړ�
	g_Polygon.pos += g_Polygon.vel;

	static float kakudo1 = 0;
	static float kakudo2 = 0;
	g_Polygon.pos.x = cosf(kakudo1) * 130.0f + (SCREEN_WIDTH / 2);
	g_Polygon.pos.y = sinf(kakudo2) * 200.0f + (SCREEN_HEIGHT / 2);
	kakudo1 += D3DXToRadian(3.0f);
	kakudo2 += D3DXToRadian(5.0f);






}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	// �|���S���`��
	DrawSprite(g_TexNo, g_Polygon.pos.x, g_Polygon.pos.y, 400.0f, 400.0f, g_U, g_V, (1.0f/5), (1.0f/2));
}