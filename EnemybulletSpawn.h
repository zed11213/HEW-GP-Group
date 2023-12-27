/*******************************************************************************************************
 Classname : EnemyBulletSpawn
 Autor : 儅丂僐僂儕儏僂
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
	//[in]startPoint : 発射点        
	//[in]targetPoint : 目標点
	//[in]high : 高さ
	//[in]time : 飛行時間(秒)
	//-----------------------------------------
	void SetBullet(D3DXVECTOR2 startPoint,D3DXVECTOR2 targetPoint,int high=200,float time=2.0f);
	SpiderBullet SBullet[50];
private:
	EnemyBulletSpawn() {; }
	~EnemyBulletSpawn() { ; }
};
