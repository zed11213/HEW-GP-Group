//===================================================
//僄僱儈乕(enemy.cpp)
//Auhor:搉绯 廋	Date:2023.9.4
//===================================================
#include "enemy.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "dead.h"
#include "main.h"
#include "hit_spark.h"
#include "bullet.h"
#include "player.h"
#include "particle.h"
#include "item.h"
#include "FsmBase/FsmBase.h"
#include "Enemy_Spider.h"

//---------------------------------------------------
//僌儘乕僶儖曄悢
//---------------------------------------------------
//static傪晅偗傞偲僼傽僀儖偺拞偺僌儘乕僶儖曄悢偵側傞
static int g_TexNo1;
static int g_TexNo2;
static int g_TexNo3;
static int g_TexNo4;
static int g_SE_landing;
static int g_SE_enemyDown;
static int g_SE_drop;

static Enemy* g_Enemy[ENEMY_MAX];
static PLAYER* p_Player;
static bool g_playSoundTrigger;

//---------------------------------------------------
//弶婜壔
//---------------------------------------------------
void InitEnemy(void)
{
	g_TexNo1 = LoadTexture((char*)"data/TEXTURE/Enemy1.png");
	g_TexNo2 = LoadTexture((char*)"data/TEXTURE/Enemy2.png");
	g_TexNo3 = LoadTexture((char*)"data/TEXTURE/Enemy3.png");
	g_TexNo4 = LoadTexture((char*)"data/TEXTURE/Tree.png");
	for (int  i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i] = new Enemy_Spider();
		g_Enemy[i]->_textureNo = g_TexNo1;
	}
	SetEnemy(1000, 600);

	//岠壥壒嶌惉
	char se1[] =
	{
		"data\\SE\\se_landing.wav"
	};
	g_SE_landing = LoadSound(&se1[0]);

	char se2[] =
	{
		"data\\SE\\se_enemyDown.wav"
	};
	g_SE_enemyDown = LoadSound(&se2[0]);

	char se3[] =
	{
		"data\\SE\\drop.wav"
	};
	g_SE_drop = LoadSound(&se3[0]);


	//僌儘乕僶儖曄悢弶婜壔
	
	g_playSoundTrigger = false;
}

//---------------------------------------------------
//峏怴
//---------------------------------------------------
void UpdateEnemy(void)
{
	g_playSoundTrigger = false;
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i]->_use == true) 
		{
			g_Enemy[i]->Update();
		}
	}
	//		//抏偲偺摉偨傝敾掕
	//		//p_Bullet = GetBullet();
	//		
	//		//float bulletRadian = 0;
	//		//for (int j = 0; j < BULLET_MAX; j++)
	//		//{
	//		//	if (!p_Bullet[j].use)continue;

	//		//	if (!g_Enemy[i].unbeatable && CollisionRot(g_Enemy[i].pos.x, g_Enemy[i].pos.y, p_Bullet[j].pos.x, p_Bullet[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, BULLET_HITBOX_WIDTH, BULLET_HITBOX_HEIGHT, 0.0f))
	//		//	{
	//		//		g_Enemy[i].hp--;
	//		//		bulletRadian = PointDirectionRadian(g_Enemy[i].pos.x, g_Enemy[i].pos.y, p_Bullet[j].pos.x, p_Bullet[j].pos.y);
	//		//		break;
	//		//	}
	//		//}
	
}

//---------------------------------------------------
//昤夋
//---------------------------------------------------
void DrawEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i]->_use == true)
		{
			g_Enemy[i]->Draw();
		}
	}
}

//---------------------------------------------------
//廔椆張棟
//---------------------------------------------------
void UninitEnemy(void)
{
	delete[]g_Enemy;
	//delete[] p_Tile;
}

//---------------------------------------------------
// 僄僱儈乕庢摼張棟
//---------------------------------------------------
Enemy* GetEnemy()
{
	return g_Enemy[0];
}

//---------------------------------------------------
// 僲僢僋僶僢僋愝掕 [堷悢]index: 攝楍斣崋
//---------------------------------------------------
void SetEnemyKnockBack(int index, float power, float radian)
{
	 //儔僕傾儞傪搙偵曄姺
	double degrees = radian * 180.0f / 3.14159f;

	//忋偵偺傒挼傇傛偆偵偡傞(忋敿墌偑塃傪0亱偲偟0乣-180丄壓敿墌偑嵍傪180亱偲偟180乣0)
	if (abs(degrees) < 90.0f) degrees = 45;
	if (abs(degrees) > 90.0f) degrees = 135;

	float radianA = degrees * 3.14159f / 180.0f;

	D3DXVECTOR2 vector = CalculateVector(-power, radianA);

	if (g_Enemy[index]->_use)
	{
		g_Enemy[index]->_knockBackX = vector.x;
		g_Enemy[index]->_knockBackY = vector.y;
	}
}

//---------------------------------------------------
// 斀摦傪愝掕 [堷悢]index: 攝楍斣崋
//---------------------------------------------------
void SetEnemyGunKick(int index, float power, float radian)
{
	D3DXVECTOR2 vector = CalculateVector(-power, radian);

	if (g_Enemy[index]->_use)
	{
		g_Enemy[index]->_knockBackX = vector.x;
		g_Enemy[index]->_knockBackY = vector.y;
	}
}

//---------------------------------------------------
// 僄僱儈乕傪攝抲
//---------------------------------------------------
void SetEnemy(float posX, float posY)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!g_Enemy[i]->_use)
		{
			g_Enemy[i]->_leftMove = false;
			g_Enemy[i]->_rightMove = false;
			g_Enemy[i]->_jump = false;
			g_Enemy[i]->_pos.x = posX;
			g_Enemy[i]->_pos.y = posY;
			g_Enemy[i]->_hsp = 0;
			g_Enemy[i]->_vsp = 0;
			g_Enemy[i]->_stateCou = 0;
			g_Enemy[i]->_reverse = true;
			g_Enemy[i]->_oldHp = 0;
			g_Enemy[i]->_unbeatable = false;
			g_Enemy[i]->_unbeatableTime = ENEMY_UNBEATABLE_TEME;
			g_Enemy[i]->_unbeatableCou = 0;
			g_Enemy[i]->_color.a = 1.0f;
			g_Enemy[i]->_grv = 0.3f;
			g_Enemy[i]->_animeBasePattern = 0;
			g_Enemy[i]->_animePattern = 0;
			g_Enemy[i]->_animeSkipFrame = 0;
			g_Enemy[i]->_jumpPower = -15;
			g_Enemy[i]->_animeSkipFrame = 0;
			g_Enemy[i]->_animePattern = 0;
			g_Enemy[i]->_animeBasePattern = 0;
			g_Enemy[i]->_animeWidthPattern = 4;
			g_Enemy[i]->_canjump = 0;
			g_Enemy[i]->_walksp = ENEMY_SPEED;
			g_Enemy[i]->_knockBackX = 0;
			g_Enemy[i]->_knockBackY = 0;
			g_Enemy[i]->_use = true;
			g_Enemy[i]->fsm->ConfigFSM();
			break;
		}
	}
}

//---------------------------------------------------
// 僄僱儈乕慡嶍彍
//---------------------------------------------------
void EnemyAllDelete()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i]->_use)
		{
			if (!OffScreenJudge(g_Enemy[i]->_pos.x, g_Enemy[i]->_pos.y, ENEMY_WIDTH, ENEMY_HEIGHT))
			{
				SetParticle(g_Enemy[i]->_pos.x, g_Enemy[i]->_pos.y, 30, 0, 0, 0);
			}

			g_Enemy[i]->_use = false;
		}
	}
}

//---------------------------------------------------
// 僄僱儈乕偺懱椡憹尭
//---------------------------------------------------
void EnemyHpDown(int index, int damage)
{
	g_Enemy[index]->_hp -= damage;
}