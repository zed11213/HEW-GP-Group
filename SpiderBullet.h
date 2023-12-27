#pragma once
#include "EnemyBullet.h"

class SpiderBullet:public EnemyBullet
{
public:
	SpiderBullet() { ; }
	~SpiderBullet() { ; }
	float _a, _b, _c = 0;

	void Init();
	void Update() ;
	void Draw() ;
	void Uninit() ;
};
