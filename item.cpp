//===================================================
//�A�C�e��(item.cpp)
//Auhor:�n� �C	Date:2023.9.15
//===================================================
#include "item.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "dead.h"
#include "main.h"
#include "tile.h"
#include "hit_spark.h"
#include "bullet.h"
#include "player.h"
#include "particle.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
//static��t����ƃt�@�C���̒��̃O���[�o���ϐ��ɂȂ�
static int g_TexNo;
static int g_SE_landing;
static int g_SE_itemDown;
static int g_SE_drop;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimePattern;
static ITEM g_Item[ITEM_MAX];
static TILE_DATA* p_Tile;
static BULLET* p_Bullet;
static PLAYER* p_Player;
static bool g_playSoundTrigger;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitItem(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Item.png");

	////���ʉ��쐬
	//char se1[] =
	//{
	//	"data\\SE\\se_landing.wav"
	//};
	//g_SE_landing = LoadSound(&se1[0]);

	//char se2[] =
	//{
	//	"data\\SE\\se_itemDown.wav"
	//};
	//g_SE_itemDown = LoadSound(&se2[0]);

	//char se3[] =
	//{
	//	"data\\SE\\drop.wav"
	//};
	//g_SE_drop = LoadSound(&se3[0]);

	for (int i = 0; i < ITEM_MAX; i++)
	{
		g_Item[i].use = false;
		g_Item[i].pos.x = SCREEN_WIDTH / 2;
		g_Item[i].pos.y = SCREEN_HEIGHT / 4;
		g_Item[i].vel.x = 0;
		g_Item[i].vel.y = 0;
		g_Item[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Item[i].hsp = 0;
		g_Item[i].vsp = 0;
		g_Item[i].grv = 0.3f;
		g_Item[i].walksp = 0;
		g_Item[i].controller = true;
		g_Item[i].hascontrol = false;
		g_Item[i].canjump = 0;
		g_Item[i].knockBackX = 0;
		g_Item[i].knockBackY = 0;
		g_Item[i].ground = false;
		g_Item[i].state = ITEM_STATE_IDLE;
		g_Item[i].oldState = ITEM_STATE_IDLE;
		g_Item[i].animeWidthPattern = 1;
		g_Item[i].animeHeightPattern = 1;
		g_Item[i].animeFrameMax = 0;
		g_Item[i].anime = false;
		g_Item[i].size = D3DXVECTOR2(ITEM_WIDTH, ITEM_HEIGHT);
		g_Item[i].leftMove = false;
		g_Item[i].rightMove = false;
		g_Item[i].jump = false;
		g_Item[i].move = 0;
		g_Item[i].stateCou = 0;
		g_Item[i].animeBasePattern = 0;
		g_Item[i].animePattern = 0;
		g_Item[i].animeSkipFrame = 0;
		g_Item[i].reverse = false;
		g_Item[i].type = ITEM_TYPE_PAPER;
		g_Item[i].animeLoop = false;
		g_Item[i].gunType = GUN_TYPE_SEMI_AUTO;
		g_Item[i].fadeOut = false;
	}

	//�O���[�o���ϐ�������
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / ITEM_WIDTH_PATTERN;
	g_VH = 1.0f / ITEM_HEIGHT_PATTERN;
	g_AnimePattern = 0;
	g_playSoundTrigger = false;
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateItem(void)
{
	g_playSoundTrigger = false;

	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (g_Item[i].use)
		{
			g_Item[i].oldState = g_Item[i].state;

			//���������Ă��Ȃ�����A,D�𗼕������Ă�Ƃ���0(false)��Ԃ�
			g_Item[i].move = g_Item[i].rightMove - g_Item[i].leftMove;
			//�ړ������Ƒ��x
			g_Item[i].hsp = (g_Item[i].move * g_Item[i].walksp) + g_Item[i].knockBackX;
			g_Item[i].knockBackX *= 0.5f;
			if (g_Item[i].knockBackX < 0.9f)g_Item[i].knockBackX = 0;

			//�d��
			g_Item[i].vsp = (g_Item[i].vsp + g_Item[i].grv) + g_Item[i].knockBackY;

			//�ǂ̏Փ˔���
			p_Tile = GetMapInfo(g_Item[i].pos);

			for (int j = 0; j < 9; j++)
			{
				if (p_Tile[j].attrib == MAP_ATTRIB_STOP)
				{
					//���ɕǂ�����ꍇ
					if (CollisionRot(g_Item[i].pos.x + g_Item[i].hsp, g_Item[i].pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, ITEM_HITBOX_WIDTH, ITEM_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
					{
						//�ǂɓ�����܂łP�s�N�Z���ǂɋ߂Â���
						while (!CollisionRot(g_Item[i].pos.x + Sign(g_Item[i].hsp), g_Item[i].pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, ITEM_HITBOX_WIDTH, ITEM_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
						{
							g_Item[i].pos.x = g_Item[i].pos.x + Sign(g_Item[i].hsp);
						}
						g_Item[i].hsp = 0;
					}

					//�c�ɕǂ�����ꍇ
					if (CollisionRot(g_Item[i].pos.x, g_Item[i].pos.y + g_Item[i].vsp, p_Tile[j].pos.x, p_Tile[j].pos.y, ITEM_HITBOX_WIDTH, ITEM_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
					{
						//�ǂɓ�����܂łP�s�N�Z���ǂɋ߂Â���
						while (!CollisionRot(g_Item[i].pos.x, g_Item[i].pos.y + Sign(g_Item[i].vsp), p_Tile[j].pos.x, p_Tile[j].pos.y, ITEM_HITBOX_WIDTH, ITEM_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
						{
							g_Item[i].pos.y = g_Item[i].pos.y + Sign(g_Item[i].vsp);
						}
						g_Item[i].vsp = 0;

						if (g_Item[i].ground == false)
						{
							if (!g_playSoundTrigger)
							{
								//��ʓ��Ȃ�炷
								if (!OffScreenJudge(g_Item[i].pos.x, g_Item[i].pos.y, ITEM_WIDTH, ITEM_HEIGHT))
								{
									//PlaySound(g_SE_landing, 0);
								}
								g_playSoundTrigger = false;
							}
						}
					}
				}
			}

			//���ړ�
			g_Item[i].pos.x += g_Item[i].hsp;

			////��ʒ[���[�v����
			//if (g_Item[i].pos.x > MAP_SIZE_X * MAPCHIP_SIZE)
			//{
			//	g_Item[i].pos.x -= MAP_SIZE_X * MAPCHIP_SIZE;
			//}
			//if (g_Item[i].pos.x < 0)
			//{
			//	g_Item[i].pos.x += MAP_SIZE_X * MAPCHIP_SIZE;
			//}

			//�c�ړ�
			g_Item[i].pos.y += g_Item[i].vsp;

			//�m�b�N�o�b�N�����Z����Ă����̂����
			if (g_Item[i].vsp != 0)g_Item[i].vsp -= g_Item[i].knockBackY;
			g_Item[i].knockBackY *= 0.5f;
			if (g_Item[i].knockBackY < 0.9f)g_Item[i].knockBackY = 0;

			p_Tile = GetMapInfo(g_Item[i].pos);

			//�����n�ʂ̏ꍇ
			for (int j = 0; j < 9; j++)
			{
				if ((p_Tile[j].attrib == MAP_ATTRIB_STOP) && (j == 6 || j == 7 || j == 8))
				{
					//�n�ʂɐG��Ă��邩�̏���
					if (CollisionRot(g_Item[i].pos.x, g_Item[i].pos.y + 1, p_Tile[j].pos.x, p_Tile[j].pos.y, ITEM_HITBOX_WIDTH, ITEM_HITBOX_HEIGHT, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, 0.0f))
					{
						g_Item[i].ground = true;
						break;
					}
					else
					{
						g_Item[i].ground = false;
					}
				}
			}

			if (g_Item[i].rightMove == true) g_Item[i].reverse = false;//�i�s�����
			else if (g_Item[i].leftMove == true) g_Item[i].reverse = true;

			//�n�ʂɐG��Ă���ꍇ
			if (g_Item[i].ground)
			{
				g_Item[i].canjump = 10;

				//�~�܂��Ă���Ƃ��̏���
				if (g_Item[i].hsp == 0)
				{
					g_Item[i].state = ITEM_STATE_IDLE;
				}
				//�����Ă���Ƃ��̏���
				else
				{
					g_Item[i].state = ITEM_STATE_WALK;
				}
			}
			//�n�ʂɐG��Ă��Ȃ��ꍇ
			else
			{
				//�㏸���Ă��邩���~���Ă��邩�̔���
				if (Sign(g_Item[i].vsp) > 0)
				{
					g_Item[i].state = ITEM_STATE_FALL;
				}
				else
				{
					g_Item[i].state = ITEM_STATE_RISE;
				}
			}

			//�t�F�[�h�A�E�g����
			if (g_Item[i].fadeOut)
			{
				g_Item[i].color.a -= 0.01f;
			}

			//�A���t�@�l0�ŏ���
			if (g_Item[i].color.a <= 0)g_Item[i].use = false;

			//�͈͊O�ŏ���
			if (g_Item[i].pos.y > SCREEN_HEIGHT)
			{
				g_Item[i].use = false;
				SetHitSpark(g_Item[i].pos.x, g_Item[i].pos.y, 0);
			}
		}
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawItem(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//�e�N�X�`���̃t�B���^�[��OFF
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (g_Item[i].use)
		{
			g_Item[i].animeFrameMax = g_Item[i].animeWidthPattern * g_Item[i].animeHeightPattern;

			D3DXVECTOR2 uv = SetAnimation(g_Item[i].animeBasePattern, g_Item[i].animePattern, ITEM_WIDTH_PATTERN, ITEM_HEIGHT_PATTERN, g_Item[i].animeWidthPattern, 1);
			g_U = uv.x;
			g_V = uv.y;

			if (g_Item[i].anime)
			{
				g_Item[i].animeSkipFrame = Counter(g_Item[i].animeSkipFrame, ITEM_FRAME_SPAN);

				if (g_Item[i].animeSkipFrame == 0)
				{
					g_Item[i].animePattern = Counter(g_Item[i].animePattern, g_Item[i].animeFrameMax);
				}
				//�A�j���[�V�����I��
				if (g_Item[i].animeLoop == false && g_Item[i].animePattern == g_Item[i].animeFrameMax - 1)g_Item[i].anime = false;
			}

			DrawSpriteColorRotateCamera(g_TexNo,
				g_Item[i].pos.x,
				g_Item[i].pos.y,
				g_Item[i].size.x, g_Item[i].size.y,	//���A����
				g_U, g_V,		//���SUV���W
				g_UW, g_VH,		//�e�N�X�`�����A����
				g_Item[i].color.r, g_Item[i].color.g, g_Item[i].color.b, g_Item[i].color.a,
				0.0f
			);
		}
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitItem(void)
{
	delete[] p_Tile;
}

//---------------------------------------------------
// �A�C�e���擾����
//---------------------------------------------------
ITEM* GetItem()
{
	return &g_Item[0];
}

//---------------------------------------------------
// �m�b�N�o�b�N�ݒ� [����]index: �z��ԍ�
//---------------------------------------------------
void SetItemKnockBack(int index, float power)
{
	// ���W�A����x�ɕϊ�
	double degrees = -90;

	float radian = degrees * 3.14159f / 180.0f;

	D3DXVECTOR2 vector = CalculateVector(-power, radian);

	if (g_Item[index].use)
	{
		g_Item[index].knockBackY = vector.y;
	}
}

//---------------------------------------------------
// ������ݒ� [����]index: �z��ԍ�
//---------------------------------------------------
void SetItemGunKick(int index, float power, float radian)
{
	D3DXVECTOR2 vector = CalculateVector(-power, radian);

	if (g_Item[index].use)
	{
		g_Item[index].knockBackX = vector.x;
		g_Item[index].knockBackY = vector.y;
	}
}

//---------------------------------------------------
// �A�C�e����z�u
//---------------------------------------------------
int SetItem(float posX, float posY, ITEM_TYPE type)
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (!g_Item[i].use)
		{
			g_Item[i].leftMove = false;
			g_Item[i].rightMove = false;
			g_Item[i].jump = false;
			g_Item[i].pos.x = posX;
			g_Item[i].pos.y = posY;
			g_Item[i].stateCou = 0;
			g_Item[i].reverse = true;
			g_Item[i].color.a = 1.0f;
			g_Item[i].grv = 1.0f;
			g_Item[i].animePattern = 0;
			g_Item[i].animeSkipFrame = 0;
			g_Item[i].vsp = -20;
			g_Item[i].animeLoop = true;
			g_Item[i].type = type;
			g_Item[i].fadeOut = false;

			switch (g_Item[i].type)
			{
			case ITEM_TYPE_PAPER:
				g_Item[i].animeBasePattern = ITEM_WIDTH_PATTERN * 0;
				g_Item[i].anime = true;
				g_Item[i].animeWidthPattern = 1;
				break;

			case ITEM_TYPE_PAPER2:
				g_Item[i].animeBasePattern = ITEM_WIDTH_PATTERN * 1;
				g_Item[i].anime = true;
				g_Item[i].animeWidthPattern = 1;
				break;

			case ITEM_TYPE_PAPER3:
				g_Item[i].animeBasePattern = ITEM_WIDTH_PATTERN * 2;
				g_Item[i].anime = false;
				g_Item[i].animeWidthPattern = 1;
				break;

			default:
				break;
			}

			g_Item[i].use = true;

			return i;
		}
	}
}

//---------------------------------------------------
// �����z�u
//---------------------------------------------------
void SetWeapon(float posX, float posY, GUN_TYPE type)
{
	int index = SetItem(posX, posY, ITEM_TYPE_WEAPON);
	g_Item[index].gunType = type;

	switch (g_Item[index].gunType)
	{
	case GUN_TYPE_SEMI_AUTO:
		g_Item[index].animeBasePattern = ITEM_WIDTH_PATTERN * 3;
		g_Item[index].anime = false;
		g_Item[index].animeWidthPattern = 1;
		break;

	case GUN_TYPE_FULL_AUTO:
		g_Item[index].animeBasePattern = ITEM_WIDTH_PATTERN * 4;
		g_Item[index].anime = false;
		g_Item[index].animeWidthPattern = 1;
		break;

	case GUN_TYPE_CHARGE_FULL_AUTO:
		g_Item[index].animeBasePattern = ITEM_WIDTH_PATTERN * 5;
		g_Item[index].anime = false;
		g_Item[index].animeWidthPattern = 1;
		break;

	default:
		break;
	}
}

//---------------------------------------------------
// �A�C�e�����A�j���[�V����
//---------------------------------------------------
void ItemAnime(int index)
{
	if (g_Item[index].use)
	{
		g_Item[index].anime = true;
		g_Item[index].animeLoop = false;
	}
}

//---------------------------------------------------
// �A�C�e�����t�F�[�h�A�E�g
//---------------------------------------------------
void ItemFadeOut(int index)
{
	if (g_Item[index].use)
	{
		g_Item[index].fadeOut = true;
	}
}

//---------------------------------------------------
// �A�C�e����S�ď���
//---------------------------------------------------
void ItemAllDelete()
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		g_Item[i].use = false;
	}
}