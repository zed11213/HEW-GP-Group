#pragma once
#include "enemy.h"
#include "FsmBase/FsmBase.h"
class Enemy_Spider:public Enemy
{
public:
	Enemy_Spider()
	{
		Init();
		fsm= new FSMBase(this);
		fsm->ConfigFSM();
	}

	~Enemy_Spider()override
	{
		delete fsm;
		delete _Tile;
	}

	// ͨ�� Enemy �̳�
	void Dropitems() override;

	void Dead() override;

	void Attack(D3DXVECTOR2 targetPos) override;


	// ͨ�� Enemy �̳�
	void Draw() override;


	// ͨ�� Enemy �̳�
	void Update() override;

};
