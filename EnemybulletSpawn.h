/*******************************************************************************************************
 Classname : EnemyBulletSpawn
 Autor : マ　コウリュウ
 Data : 2023.12.15
********************************************************************************************************/
#pragma once
#include "main.h"
#include "SpiderBullet.h"
#include "texture.h"
#define	EBULLET				EnemyBulletSpawn::Instance()

class EnemyBulletSpawn
{
public:
	static EnemyBulletSpawn* Instance()
	{	
		static EnemyBulletSpawn p;
		return &p;
	}

	//------------------------------------------
	//[in]startPoint : ｰkﾉ莊・       
	//[in]targetPoint : ﾄｿ侏ｵ・
	//[in]high : ｸﾟ､ｵ
	//[in]time : ・ﾐﾐ瓶馮(ﾃ・
	//-----------------------------------------
	void SetBullet(D3DXVECTOR2 startPoint,D3DXVECTOR2 targetPoint,int high=200,float time=2.0f);
	SpiderBullet SBullet[50];
private:
	EnemyBulletSpawn() {; }
	~EnemyBulletSpawn() { ; }
};
