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
	// Í¨¹ý State ¼Ì³Ð
	void Init() override;

	void EnterState(FSMBase* fsm) override;

	void StayState(FSMBase* fsm) override;

	void ExitState(FSMBase* fsm) override;

};
