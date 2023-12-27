#pragma once
#include "..\state.h"
#include "..\FsmBase.h"
class EnemyDead:public State
{
public:
	EnemyDead()
	{
		Init();
	}

	~EnemyDead() { ; }
	// ͨ�� State �̳�
	void Init() override;

	void EnterState(FSMBase* fsm) override;

	void StayState(FSMBase* fsm) override;

	void ExitState(FSMBase* fsm) override;

};
