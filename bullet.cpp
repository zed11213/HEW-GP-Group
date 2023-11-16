//===================================================
//�e(bullet.cpp)
//Auhor:�n� �C	Date:2023.8.28
//===================================================
#include "bullet.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "dead.h"
#include "main.h"
#include "tile.h"
#include "camera.h"
#include "tile.h"
#include "hit_spark.h"
#include "enemy.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
//static��t����ƃt�@�C���̒��̃O���[�o���ϐ��ɂȂ�
static int g_TexNo;
static int g_SE_bulletHit;
static int g_SE_move;
static int g_SE_drop;
static float g_UW;
static float g_VH;
static float g_AnimeSkipFrameFloat;
static BULLET g_Bullet[BULLET_MAX];
static TILE_DATA* p_Tile;
static CAMERA* p_Camera;
static ENEMY* p_Enemy;
static bool g_Reverse;
static bool g_playSoundTrigger;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitBullet(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Bullet.png");
	//���ʉ��쐬
	char se1[] =
	{
		"data\\SE\\se_bulletHit.wav"
	};
	g_SE_bulletHit = LoadSound(&se1[0]);

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

	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].use = false;
		g_Bullet[i].pos.x = SCREEN_WIDTH / 2;
		g_Bullet[i].pos.y = SCREEN_HEIGHT / 4;
		g_Bullet[i].oldPos = D3DXVECTOR2(0, 0);
		g_Bullet[i].goalPos = D3DXVECTOR2(0, 0);
		g_Bullet[i].vel.x = 0;
		g_Bullet[i].vel.y = 0;
		g_Bullet[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Bullet[i].size = D3DXVECTOR2(BULLET_WIDTH, BULLET_HEIGHT);
		g_Bullet[i].rot = 0.0f;
		g_Bullet[i].sp = 0;
		g_Bullet[i].uv = D3DXVECTOR2(0, 0);
		g_Bullet[i].animePattern = 0;
		g_Bullet[i].animeWidthPattern = BULLET_WIDTH_PATTERN;
		g_Bullet[i].animeBasePattern = 1;
		g_Bullet[i].animeSkipFrame = 0;
		g_Bullet[i].bulletType = BULLET_TYPE_NORMAL;

		for (int j = 0; j < ENEMY_MAX; j++)
		{
			g_Bullet[i].hetList[j] = false;
		}
	}

	//�O���[�o���ϐ�������
	g_UW = 1.0f / BULLET_WIDTH_PATTERN;
	g_VH = 1.0f / BULLET_HEIGHT_PATTERN;
	g_Reverse = false;
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].oldPos = g_Bullet[i].pos;

		D3DXVECTOR2 vel = g_Bullet[i].vel;
		//�x�N�g���̐��K��
		D3DXVec2Normalize(&g_Bullet[i].vel, &g_Bullet[i].vel);
		g_Bullet[i].vel *= g_Bullet[i].sp;//�ړI�̃X�s�[�h�ɂ��邽�߂ɃX�s�[�h����Z����
		//�ړI�n�̍��W���Z�o
		g_Bullet[i].goalPos = g_Bullet[i].pos;
		g_Bullet[i].goalPos += g_Bullet[i].vel;

		if (g_Bullet[i].use)
		{
			p_Enemy = GetEnemy();

			while (true)
			{

				for (int j = 0; j < ENEMY_MAX; j++)
				{
					//�e���G�Ƀq�b�g�����Ƃ�
					if (
						p_Enemy[j].use && 
						!p_Enemy[j].unbeatable &&
						CollisionRot(g_Bullet[i].pos.x, g_Bullet[i].pos.y, p_Enemy[j].pos.x, p_Enemy[j].pos.y, BULLET_HITBOX_WIDTH, BULLET_HITBOX_HEIGHT, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, g_Bullet[i].rot)
						)
					{
						if (g_Bullet[i].hetList[j]) continue;

						//�G�̃m�b�N�o�b�N�ݒ�
						float degrees = 0;
						if (g_Bullet[i].vel.x < 0) degrees = 0;
						if (g_Bullet[i].vel.x > 0) degrees = 180;

						SetEnemyKnockBack(j, 20, degrees * 3.14159f / 180.0f);//���W�A���Ƀ΂𑫂��Ĕ��]

						EnemyHpDown(j, 1);
						SetHitSpark(g_Bullet[i].pos.x, g_Bullet[i].pos.y, 0);
						g_Bullet[i].hetList[j] = true;
						break;
					}
				}

				//�ǂ̏Փ˔���
				DIRECTION dir = TileHit(g_Bullet[i].pos, 0, 0, BULLET_HITBOX_WIDTH, BULLET_HITBOX_HEIGHT);
				if (dir.left || dir.right || dir.up || dir.down)
				{
					SetHitSpark(g_Bullet[i].pos.x, g_Bullet[i].pos.y, 0);
					PlaySound(g_SE_bulletHit, 0);
					g_playSoundTrigger = true;
					g_Bullet[i].use = false;
					break;
				}

				//�e��������Ȃ�������q�b�g�{�b�N�X���ړ�������
				////�x�N�g���̐��K��
				D3DXVec2Normalize(&vel, &vel);
				vel *= 30;//�����̃X�s�[�h���i�񂾏ꍇ�̓����蔻����s���Ă���
				g_Bullet[i].pos += vel;

				//�ڕW�n�_�𒴂����ꍇ
				if (
					//�E��ɒe���i��ł���ꍇ
					(vel.x > 0 && vel.y < 0 && g_Bullet[i].goalPos.x < g_Bullet[i].pos.x && g_Bullet[i].goalPos.y > g_Bullet[i].pos.y) ||
					//�E���ɒe���i��ł���ꍇ
					(vel.x > 0 && vel.y > 0 && g_Bullet[i].goalPos.x < g_Bullet[i].pos.x && g_Bullet[i].goalPos.y < g_Bullet[i].pos.y) ||
					//�����ɒe���i��ł���ꍇ
					(vel.x < 0 && vel.y > 0 && g_Bullet[i].goalPos.x > g_Bullet[i].pos.x && g_Bullet[i].goalPos.y < g_Bullet[i].pos.y) ||
					//����ɒe���i��ł���ꍇ
					(vel.x < 0 && vel.y < 0 && g_Bullet[i].goalPos.x > g_Bullet[i].pos.x && g_Bullet[i].goalPos.y > g_Bullet[i].pos.y)
					)
				{
					g_Bullet[i].pos = g_Bullet[i].goalPos;
					break;
				}
			}

			// �X�e�[�W���[�v����
			if (g_Bullet[i].pos.x > STAGE_SIZE)
			{
				g_Bullet[i].pos.x -= STAGE_SIZE;
			}
			else if (g_Bullet[i].pos.x < 0)
			{
				g_Bullet[i].pos.x += STAGE_SIZE;
			}

			//��ʂ���o�������
			if (OffScreenJudge(g_Bullet[i].pos.x, g_Bullet[i].pos.y, BULLET_WIDTH, BULLET_HEIGHT))
			{
				g_Bullet[i].use = false;
			}
		}
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use)
		{
			//�A�j���[�V����
			g_Bullet[i].uv = SetAnimation(g_Bullet[i].animeBasePattern, g_Bullet[i].animePattern, BULLET_WIDTH_PATTERN, BULLET_HEIGHT_PATTERN, g_Bullet[i].animeWidthPattern, g_Reverse);

			g_Bullet[i].animeSkipFrame = Counter(g_Bullet[i].animeSkipFrame, BULLET_FRAME_SPAN);

			if (g_Bullet[i].animeSkipFrame == 0)
			{
				g_Bullet[i].animePattern = Counter(g_Bullet[i].animePattern, BULLET_FRAME_MAX);
				if (g_Bullet[i].animePattern == 0)g_Bullet[i].animeWidthPattern = 1;//�A�j�������[�v�����Ȃ�
			}

			DrawSpriteColorRotateCamera(g_TexNo,
				g_Bullet[i].pos.x,
				g_Bullet[i].pos.y,
				g_Bullet[i].size.x, g_Bullet[i].size.y,	//���A����
				g_Bullet[i].uv.x, g_Bullet[i].uv.y,		//���SUV���W
				g_UW, g_VH,		//�e�N�X�`�����A����
				g_Bullet[i].color.r, g_Bullet[i].color.g, g_Bullet[i].color.b, g_Bullet[i].color.a,
				g_Bullet[i].rot
			);
		}
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitBullet(void)
{
	delete[] p_Tile;
}

//---------------------------------------------------
// �e�擾����
//---------------------------------------------------
BULLET* GetBullet()
{
	return &g_Bullet[0];
}

//---------------------------------------------------
// �e�z�u����
//---------------------------------------------------
void SetBullet(int type, float posX, float posY, float velX, float velY, float rot, float sp)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!g_Bullet[i].use)
		{
			g_Bullet[i].bulletType = type;
			g_Bullet[i].pos = D3DXVECTOR2(posX, posY);
			g_Bullet[i].vel = D3DXVECTOR2(velX, velY);
			g_Bullet[i].rot = rot;
			g_Bullet[i].sp = sp;
			g_Bullet[i].uv = D3DXVECTOR2(0, 0);
			g_Bullet[i].animePattern = 0;
			g_Bullet[i].animeWidthPattern = BULLET_WIDTH_PATTERN;
			g_Bullet[i].animeBasePattern = 1;
			g_Bullet[i].animeSkipFrame = 0;

			for (int j = 0; j < ENEMY_MAX; j++)
			{
				g_Bullet[i].hetList[j] = false;
			}

			g_Bullet[i].use = true;
			break;
		}
	}
}

//---------------------------------------------------
// �m�[�}���e�z�u����
//---------------------------------------------------
void SetBulletNormal(float posX, float posY, float velX, float velY, float rot, float sp)
{
	SetBullet(BULLET_TYPE_NORMAL, posX, posY, velX, velY, rot, sp);
}

//---------------------------------------------------
// �~�T�C���z�u����
//---------------------------------------------------
void SetBulletMissile(float posX, float posY, float velX, float velY, float rot, float sp)
{
	SetBullet(BULLET_TYPE_MISSILE, posX, posY, velX, velY, rot, sp);
}

//---------------------------------------------------
// �e�폜
//---------------------------------------------------
void DeleteBullet(int index)
{
	g_Bullet[index].use = false;
	SetHitSpark(g_Bullet[index].pos.x, g_Bullet[index].pos.y, 0);
}