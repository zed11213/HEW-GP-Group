#include "EnemyBullet.h"
#include "EnemybulletSpawn.h"
#include  "texture.h"

void EnemyBulletInit()
{
	unsigned int texNo = LoadTexture((char*)"data/TEXTURE/Bullet.png");
	for (int i = 0; i < 50; i++)
	{
		EBULLET->SBullet[i].Init();
		EBULLET->SBullet[i]._texNo=texNo;
	}
}

void EnemyBulletUpdate()
{
	for (int i = 0; i < 50; i++)
	{
		EBULLET->SBullet[i].Update();
	}
}

void EnemyBulletDraw()
{
	for (int i = 0; i < 50; i++)
	{
		EBULLET->SBullet[i].Draw();
	}
}

void EnemyBulletUnInit()
{
	for (int i = 0; i < 50; i++)
	{
		EBULLET->SBullet[i].Uninit();
	}
}
