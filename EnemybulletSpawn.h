/*******************************************************************************************************
 Classname : EnemyBulletSpawn
 Autor : �}�@�R�E�����E
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
	//[in]startPoint : �k���        
	//[in]targetPoint : Ŀ�˵�
	//[in]high : �ߤ�
	//[in]time : �w�Еr�g(��)
	//-----------------------------------------
	void SetBullet(D3DXVECTOR2 startPoint,D3DXVECTOR2 targetPoint,int high=200,float time=2.0f);
	SpiderBullet SBullet[50];
private:
	EnemyBulletSpawn() {; }
	~EnemyBulletSpawn() { ; }
};
